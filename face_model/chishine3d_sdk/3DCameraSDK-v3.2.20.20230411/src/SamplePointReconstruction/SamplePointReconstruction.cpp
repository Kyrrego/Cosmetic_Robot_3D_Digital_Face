/*******************************************************************************
 * This file is part of the 3D Camera API Sample
 *
 * Copyright 2015-2020 (C) Chishine3D AS
 * All rights reserved.
 * 
 * Chishine3D Software License, v1.0
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of Chishine3D AS nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 * 
 * 4. This software, with or without modification, must not be used with any
 * other 3D camera than from Chishine3D AS.
 * 
 * 5. Any software provided in binary form under this license must not be
 * reverse engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY CHISHINE3D AS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CHISHINE3D AS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact: Chishine3D Support <support@chishine3d.com>
 * Info:    http://www.chishine3d.com
 ******************************************************************************/
#include "3DCamera.hpp"
#include <chrono>
#include <thread>
#include "BmpUtil.hpp"

cs::float3  getZ16ToPoint(int x,int y,unsigned short * z16Data, int iWidth, int iHeight, float depthScale, Intrinsics *intrinsicsDepth, Intrinsics *intrinsicsRgb, Extrinsics *extrinsics)
{
	Intrinsics intrDepth;
	memcpy(&intrDepth, intrinsicsDepth, sizeof(Intrinsics));
	intrDepth.fx *= float(iWidth) / intrinsicsDepth->width;
	intrDepth.cx *= float(iWidth) / intrinsicsDepth->width;
	intrDepth.fy *= float(iHeight) / intrinsicsDepth->height;
	intrDepth.cy *= float(iHeight) / intrinsicsDepth->height;

	cs::float3 point;
	int index = y*iWidth + x;
	float z = z16Data[index] * depthScale;
	if (z > 0.f)
	{
		point.x = (x - intrDepth.cx) * z / intrDepth.fx;
		point.y = (y - intrDepth.cy) * z / intrDepth.fy;
		point.z = z;
	}
	else
	{
		point.x = point.y = point.z = 0.0;
	}

	return point;
}

int main()
{
	printf( "This is SamplePointReconstruction sample!\n\n");
	ERROR_CODE ret;

	// get camera pointer and connect a valid camera
	cs::ICameraPtr camera = cs::getCameraPtr();
	ret = camera->connect();
	if(ret != SUCCESS)
	{
		printf("camera connect failed(%d)!\n", ret);
		return -1;
	}
	//start depth stream
	std::vector<StreamInfo> streamInfos;
	camera->getStreamInfos(STREAM_TYPE_DEPTH, streamInfos); 
	for (auto streamInfo : streamInfos)
	{
		if (streamInfo.format == STREAM_FORMAT_Z16)
		{
			printf("start depth stream width:%d,height:%d,fps:%f\n"
					, streamInfo.width, streamInfo.height, streamInfo.fps);
			//start stream
			ERROR_CODE ret = camera->startStream(STREAM_TYPE_DEPTH, streamInfo);
			if (ret != SUCCESS)
			{
				printf("camera start depth stream failed(%d)!\n", ret);
				return -1;
			}
			break;
		}
	}
	//start rgb stream
	camera->getStreamInfos(STREAM_TYPE_RGB, streamInfos);
	for (auto info : streamInfos)
	{
		if (info.format == STREAM_FORMAT_RGB8)
		{
			printf("start rgb stream width:%d,height:%d,fps:%f\n"
				, info.width, info.height, info.fps);
			ret = camera->startStream(STREAM_TYPE_RGB, info);
			if (ret != SUCCESS)
			{
				printf("camera start rgb stream failed(%d)!\n", ret);
				return -1;
			}
			break;
		}
	}
	Intrinsics intr;
	camera->getIntrinsics(STREAM_TYPE_DEPTH, intr);
	Intrinsics intrColor;
	camera->getIntrinsics(STREAM_TYPE_RGB, intrColor);
	Extrinsics extrColor;
	camera->getExtrinsics(extrColor);

	//set extensional properties
	PropertyExtension value;
	value.depthRange.min = 50;
	value.depthRange.max = 500;
	camera->setPropertyExtension(PROPERTY_EXT_DEPTH_RANGE, value);

	//set the threshold of algorithm
	value.algorithmContrast = 5;
	camera->setPropertyExtension(PROPERTY_EXT_CONTRAST_MIN, value);

	int count = 10;
	while (count-- > 0)
	{
		cs::IFramePtr frameDepth, frameRgb;
		if (SUCCESS != camera->getFrame(STREAM_TYPE_DEPTH, frameDepth)) 
			continue;
		printf("Get a new Frame!\n");
		cs::Pointcloud pc;
		float scale = 0.1f;
		PropertyExtension value;
		if (SUCCESS == camera->getPropertyExtension(PROPERTY_EXT_DEPTH_SCALE, value))
		{
			scale = value.depthScale;
		}
		if (SUCCESS == camera->getFrame(STREAM_TYPE_RGB, frameRgb))
		{
			//generate point cloud with color
			printf("Get a new rgb Frame!\n");	
			
			//generate depth show image
			std::vector<unsigned char> depthShow;
			int length = frameDepth->getHeight() * frameDepth->getWidth();
			depthShow.resize(length * 3);
			cs::colorizer color;
			color.process((unsigned short *)frameDepth->getData(FRAME_DATA_FORMAT_Z16), scale, depthShow.data(), length);
			
			pc.generatePoints((unsigned short *)frameDepth->getData(), frameDepth->getWidth(), frameDepth->getHeight(), scale, &intr, &intrColor, &extrColor);
			pc.exportToFile("./pc.ply", (unsigned char *)frameRgb->getData(), frameRgb->getWidth(), frameRgb->getHeight(), true);
			
			//get coordinates of depth map according to coordinates of rgb image
			std::map<int, int> rgbToDepth;
			pc.generateTextureToDepthMap(frameDepth->getWidth(), frameDepth->getHeight(), rgbToDepth);
			
			int depthX, depthY;
			int rgbWidth = frameRgb->getWidth();
			int rgbY = 0.4*frameRgb->getHeight();
			for (int rgbX = 0; rgbX < rgbWidth; ++rgbX)
			{
				if (pc.getDepthCoordFromMap(rgbToDepth, rgbX, rgbY,
					frameRgb->getWidth(), frameRgb->getHeight(), frameDepth->getWidth(), frameDepth->getHeight(), depthX, depthY))
				{
					printf("rgb[%d, %d]->depth[%d, %d]\n", rgbY, rgbX, depthY, depthX);
					int rgbIndex = 3 * (rgbX + rgbY*rgbWidth);
					int depthIndex = 3 * (depthX + depthY* frameDepth->getWidth());
					((char *)frameRgb->getData())[rgbIndex] = 0xff;
					((char *)frameRgb->getData())[rgbIndex] = 0;
					((char *)frameRgb->getData())[rgbIndex] = 0;
					depthShow[depthIndex] = 0xff;
					depthShow[depthIndex + 1] = 0;
					depthShow[depthIndex + 2] = 0;
				}
			}

			//save images
			cs::saveBmp(frameRgb->getData(), frameRgb->getWidth(), frameRgb->getHeight(), 3, "pc_texture.bmp");
			cs::saveBmp((const char *)depthShow.data(), frameDepth->getWidth(), frameDepth->getHeight(), 3, "pc_depth.bmp");
			break;
		}
		else
		{
			//generate point cloud without color
			pc.generatePoints((unsigned short *)frameDepth->getData(), frameDepth->getWidth(), frameDepth->getHeight(), scale, &intr, nullptr, nullptr);
			pc.exportToFile("./pc.ply", nullptr, 0, 0, true);
		}
	}

	// disconnect camera
	ret = camera->disconnect();
	if(ret != SUCCESS)
	{
		printf("camera disconnect failed(%d)!\n", ret);
		return -1;
	}
	
	return 0;	
}

