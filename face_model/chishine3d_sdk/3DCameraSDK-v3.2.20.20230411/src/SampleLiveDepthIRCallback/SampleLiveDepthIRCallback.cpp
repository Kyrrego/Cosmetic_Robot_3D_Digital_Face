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
#include <fcntl.h>
#include "BmpUtil.hpp"

// save depth data as depth-stream callback
void depthCallback(cs::IFramePtr frame, void *usrData)
{
	printf("Get one frame!\n");
	char path[128];
	int width = 0;
	int height = 0;

	width = frame->getWidth();
	height = frame->getHeight();

	if (frame->getData(FRAME_DATA_FORMAT_IR_LEFT))
	{
		cs::saveBmp((const char *)frame->getData(FRAME_DATA_FORMAT_IR_LEFT), frame->getWidth(), frame->getHeight(), 1, "DepthIRCallback-IRLeft.bmp");
	}

	if (frame->getData(FRAME_DATA_FORMAT_Z16))
	{
		cs::colorizer color;
		std::vector<unsigned char> rgb;
		int length = frame->getHeight() * frame->getWidth();
		rgb.resize(length*3);
		cs::ICameraPtr *camera = (cs::ICameraPtr *)usrData;
		PropertyExtension v;
		float scale = 0.1f;
		if (camera->get()->getPropertyExtension(PROPERTY_EXT_DEPTH_SCALE, v))
			scale = v.depthScale;
		color.process((unsigned short *)frame->getData(FRAME_DATA_FORMAT_Z16), scale, rgb.data(), length);
		cs::saveBmp((const char *)rgb.data(), frame->getWidth(), frame->getHeight(), 3, "DepthIRCallback-Depth.bmp");
	}

	if (frame->getData(FRAME_DATA_FORMAT_IR_RIGHT))
	{
		cs::saveBmp((const char *)frame->getData(FRAME_DATA_FORMAT_IR_RIGHT), frame->getWidth(), frame->getHeight(), 1, "DepthIRCallback-IRRight.bmp");
	}
}

int main()
{
	printf( "This is SampleLiveDepthIRCallback sample!\n\n");
	ERROR_CODE ret;

	// get camera pointer and connect a valid camera
	cs::ISystemPtr system = cs::getSystemPtr();

	//找一个相机连接
	CameraInfo info;
	while (true)
	{
		std::vector<CameraInfo> cameras;
		// query cameras
		printf("queryCameras \n");

		ERROR_CODE ret = system->queryCameras(cameras);
		if (ret == SUCCESS && cameras.size() > 0)
		{
			info = cameras[0];
			printf("select the first camera serial:%s\n", info.serial);
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	//连接相机
	std::shared_ptr<cs::ICamera> camera = cs::getCameraPtr();

	if (camera->connect(info) != SUCCESS)
	{
		printf("fail to connect the camera %s\n", info.serial);
		return 0;
	}

	// display informations of camera
	printf("%20s  :  %s\n", "name", info.name);
	printf("%20s  :  %s\n", "serial", info.serial);
	printf("%20s  :  %s\n", "unique id", info.uniqueId);
	printf("%20s  :  %s\n", "firmware version", info.firmwareVersion);
	printf("%20s  :  %s\n", "algorithm version", info.algorithmVersion);
	printf("\n");
	
	// get  informations of depth-stream 
	std::vector<StreamInfo> streamInfos;
	ret = camera->getStreamInfos(STREAM_TYPE_DEPTH,  streamInfos);
	if(ret != SUCCESS)
	{
		printf("camera get stream info failed(%d)!\n", ret);
		return -1;
	}

	// display  informations of depth-stream 
	for (auto streamInfo : streamInfos)
	{
		printf("depth format:%2d, width:%4d, height:%4d, fps:%2.1f\n", streamInfo.format, streamInfo.width, streamInfo.height, streamInfo.fps);
	}
	printf("\n");

	// start depth-stream in second information of depth-stream, callback mode
	bool bStart = false;
	for (auto streamInfo : streamInfos)
	{
		//if (streamInfo.format == STREAM_FORMAT_Z16Y8Y8)
		if (streamInfo.format == STREAM_FORMAT_PAIR)
		{
			ret = camera->startStream(STREAM_TYPE_DEPTH, streamInfo, depthCallback, &camera);
			if (ret != SUCCESS)
			{
				printf("camera start depth stream failed(%d)!\n", ret);
				return -1;
			}
			else
			{
				bStart = true;
				printf("start depth format:%2d, width:%4d, height:%4d, fps:%2.1f\n", streamInfo.format, streamInfo.width, streamInfo.height, streamInfo.fps);
			}
			break;
		}
	}

	if (bStart)
	{
		// test depth-stream for 10 second
		std::this_thread::sleep_for(std::chrono::seconds(1000));
	}
	else
	{
		printf("do not found the stream to start\n");
	}

	// stop depth-stream
	ret = camera->stopStream(STREAM_TYPE_DEPTH);
	if(ret != SUCCESS)
	{
		printf("camera stop depth stream failed(%d)!\n", ret);
		return -1;
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

