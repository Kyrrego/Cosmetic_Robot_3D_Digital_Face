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
#include <BmpUtil.hpp>

int saveFlag = -1;
// Callback of stream in format MJPG
void Callback(cs::IFramePtr frame, void *usrData)
{
	if (saveFlag >= 0)
	{
		char path[64];
		sprintf(path, "RgbAutoExposure%d.jpg", saveFlag++);
		cs::saveBmp(frame->getData(), frame->getWidth(), frame->getHeight(), 3, path);
		saveFlag = -1;
	}
	//printf("Get a new mjpg frame! It has saved as \'%s\'\n",path);
}

int main()
{
	printf( "This is SampleLiveRgbAutoExposure sample!\n\n");
	ERROR_CODE ret;

	// get camera pointer and connect a valid camera
	cs::ICameraPtr camera = cs::getCameraPtr();
	ret = camera->connect();
	if(ret != SUCCESS)
	{
		printf("camera connect failed(%d)!\n", ret);
		return -1;
	}

	// get  informations of camera
	CameraInfo info;
	ret = camera->getInfo(info);
	if(ret != SUCCESS)
	{
		printf("camera get info failed(%d)!\n", ret);
		return -1;
	}

	// display informations of camera
	printf("%20s  :  %s\n", "name", info.name);
	printf("%20s  :  %s\n", "serial", info.serial);
	printf("%20s  :  %s\n", "unique id", info.uniqueId);
	printf("%20s  :  %s\n", "firmware version", info.firmwareVersion);
	printf("%20s  :  %s\n", "algorithm version", info.algorithmVersion);
	printf("\n");
	
	// get  informations of rgb-stream 
	std::vector<StreamInfo> streamInfos;
	ret = camera->getStreamInfos(STREAM_TYPE_RGB,  streamInfos);
	if(ret != SUCCESS)
	{
		printf("camera get stream info failed(%d)!\n", ret);
		return -1;
	}

	// display  informations of depth-stream 
	for (auto streamInfo : streamInfos)
	{
		printf("format:%2d, width:%4d, height:%4d, fps:%2.1f\n", streamInfo.format, streamInfo.width, streamInfo.height, streamInfo.fps);
	}
	printf("\n");
	
	// start rgb-stream 
	for (auto streamInfo : streamInfos)
	{
		if (streamInfo.format == STREAM_FORMAT_RGB8)
		{
			ret = camera->startStream(STREAM_TYPE_RGB, streamInfo, Callback, NULL);
			if (ret != SUCCESS)
			{
				printf("camera start rgb stream failed(%d)!\n", ret);
				return -1;
			}
			else
			{
				printf("start rgb format:%2d, width:%4d, height:%4d, fps:%2.1f\n", streamInfo.format, streamInfo.width, streamInfo.height, streamInfo.fps);
			}
			break;
		}
	}
	saveFlag = 0;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	//Manually set the exposure time
	ret = camera->setProperty(STREAM_TYPE_RGB, PROPERTY_ENABLE_AUTO_EXPOSURE, 0);
	ret = camera->setProperty(STREAM_TYPE_RGB, PROPERTY_EXPOSURE, 7000);
	//Set auto exposure
	std::this_thread::sleep_for(std::chrono::seconds(2));
	saveFlag = 1;
	ret = camera->setProperty(STREAM_TYPE_RGB, PROPERTY_ENABLE_AUTO_EXPOSURE, 1);
	if(ret != SUCCESS)
	{
		printf("camera enable auto exposure failed!(ret:%d)\n",ret);
	}
	else
	{
		printf("camera enable auto exposure success\n");
	}
	
	float auto_exposure = 0;
	ret = camera->getProperty(STREAM_TYPE_RGB, PROPERTY_ENABLE_AUTO_EXPOSURE, auto_exposure);
	if(ret != SUCCESS)
	{
		printf("camera get auto exposure mode failed!(ret:%d)\n",ret);
	}
	else
	{
		printf("camera get auto exposure mode %f\n", auto_exposure);
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	saveFlag = 2;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	ret = camera->setProperty(STREAM_TYPE_RGB, PROPERTY_ENABLE_AUTO_EXPOSURE, 0);
	if(ret != SUCCESS)
	{
		printf("camera disable auto exposure failed!(ret:%d)\n",ret);
	}
	else
	{
	   printf("camera disable auto exposure\n");
	}
	
	ret = camera->getProperty(STREAM_TYPE_RGB, PROPERTY_ENABLE_AUTO_EXPOSURE, auto_exposure);
	if(ret != SUCCESS)
	{
		printf("camera get auto exposure mode failed!(ret:%d)\n",ret);
	}
	else
	{
		printf("camera get auto exposure mode %f\n", auto_exposure);
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));

	// stop rgb-stream
 	ret = camera->stopStream(STREAM_TYPE_RGB);
	if(ret != SUCCESS)
	{
		printf("camera stop rgb stream failed(%d)!\n", ret);
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

