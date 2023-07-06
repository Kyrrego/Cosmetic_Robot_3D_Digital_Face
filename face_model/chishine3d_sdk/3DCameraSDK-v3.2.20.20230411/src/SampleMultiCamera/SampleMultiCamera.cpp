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
#include <map>
#include <mutex>
#include <thread>

std::map<std::string, cs::ICameraPtr> g_cameraPtrs;
std::mutex g_mutex;

void addDevice(CameraInfo info)
{
	std::string serial_number = info.serial;
	std::lock_guard<std::mutex> lock(g_mutex);

	if (g_cameraPtrs.find(serial_number) != g_cameraPtrs.end())
	{
		return; //already in
	}
	
	auto camera = cs::getCameraPtr();
	ERROR_CODE error = camera->connect(info);
	if (error != SUCCESS)
	{
		printf("connect failed\n");
		return;
	}
	CameraInfo connectedInfo;
	camera->getInfo(connectedInfo);
	printf("Connected a new camera success\n");
	printf("%20s  :  %s\n", "name", connectedInfo.name);
	printf("%20s  :  %s\n", "serial", connectedInfo.serial);
	printf("%20s  :  %s\n", "unique id", connectedInfo.uniqueId);
	printf("%20s  :  %s\n", "firmware version", connectedInfo.firmwareVersion);
	printf("%20s  :  %s\n", "algorithm version", connectedInfo.algorithmVersion);
	printf("\n");
	//start stream
	std::vector<StreamInfo> streamInfos;
	camera->getStreamInfos(STREAM_TYPE_DEPTH, streamInfos);
	for (auto streamInfo : streamInfos)
	{
		if (streamInfo.format == STREAM_FORMAT_Z16)
		{
			//start stream
			ERROR_CODE ret = camera->startStream(STREAM_TYPE_DEPTH, streamInfo);
			if (ret != SUCCESS)
			{
				printf("camera start depth stream failed(%d)!\n", ret);
				return;
			}
			g_cameraPtrs.emplace(serial_number, camera);
			break;
		}
	}
}

void removeDevice(CameraInfo& info)
{
	std::lock_guard<std::mutex> lock(g_mutex);
	// Go over the list of devices and check if it was disconnected
	auto itr = g_cameraPtrs.begin();
	while (itr != g_cameraPtrs.end())
	{
		if (info.serial == itr->first)
		{
			itr = g_cameraPtrs.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void cameraChangedCallback(std::vector<CameraInfo>& added, std::vector<CameraInfo>& removed, void *user)
{
	printf("--------------camera list change callback start-------------------\n");
	if (removed.size())
	{
		for (auto&& dev : removed)
		{
			printf("Camera pull out,serial number = %s\n\n", dev.serial);
			removeDevice(dev);
		}
	}
	if (added.size())
	{
		for (auto&& dev : added)
		{
			printf("Found a new camera,serial number = %s\n", dev.serial);
			addDevice(dev);
		}
	}
	printf("--------------camera list change callback end---------------------\n\n\n");
}

int main()
{
	printf( "This is SampleMultiCamera sample!\n\n");
	ERROR_CODE ret;

	// get system pointer
	cs::ISystemPtr system = cs::getSystemPtr();
	
	std::vector<CameraInfo> cameras;

	// query cameras and connect all cameras
	ret = system->queryCameras(cameras);
	if(ret == SUCCESS)
	{
		printf("queryCameras found %ld cameras\n", cameras.size());
		for (int i = 0; i < cameras.size(); i++)
		{
			printf("Connect to a camera,serial number = %s\n", cameras[i].serial);
			addDevice(cameras[i]);
		}
	}

	system->setCameraChangeCallback(cameraChangedCallback, nullptr);

	//wait for camera list change callback
	while (true)
	{
		
		for (auto&& item : g_cameraPtrs)
		{
			std::lock_guard<std::mutex> lock(g_mutex);
			// Ask each pipeline if there are new frames available
			cs::IFramePtr frame;
			if (SUCCESS == item.second->getFrame(STREAM_TYPE_DEPTH, frame))
			{
				printf("%s Get one frame!\n", item.first.c_str());
			}
			else
			{
				printf("%s Get frame fail!\n", item.first.c_str());
			}
		}
		//to do something
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
	return 0;	
}
