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

void printCameraInfo(CameraInfo& info)
{
	printf("%20s  :  %s\n", "name", info.name);
	printf("%20s  :  %s\n", "serial", info.serial);
	printf("%20s  :  %s\n", "unique id", info.uniqueId);
	printf("%20s  :  %s\n", "firmware version", info.firmwareVersion);
	printf("%20s  :  %s\n", "algorithm version", info.algorithmVersion);
	printf("\n");
}

void callback(std::vector<CameraInfo>& added, std::vector<CameraInfo>& removed, void *user)
{
	printf("--------------camera list change callback start-------------------\n");
	if (removed.size())
	{
		for (auto&& dev : removed)
		{
			printf("Camera pull out,serial number = %s\n\n", dev.serial);
			printCameraInfo(dev);
		}
	}
	if (added.size())
	{
		for (auto&& dev : added)
		{
			printf("Found a new camera,serial number = %s\n", dev.serial);
			printCameraInfo(dev);
		}
	}
	printf("--------------camera list change callback end---------------------\n\n\n");
}

int main()
{
	printf( "This is SampleSystemQueryCameras sample!\n\n");
	int ret;

	// get system pointer
	cs::ISystemPtr system = cs::getSystemPtr();
	system->setCameraChangeCallback(callback, nullptr);

	std::vector<CameraInfo> cameras;

	// query cameras,try 10 times.
	for (int i=0;i<10;i++)
	{
		ret = system->queryCameras(cameras);
		if (ret == SUCCESS)
		{
			printf("queryCameras found %ld cameras\n", cameras.size());

			if (cameras.size() > 0)
			{
				// display camera information
				for (int i = 0; i < cameras.size(); i++)
				{
					printCameraInfo(cameras[i]);
				}
				break;
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			
		}
		else
		{
			printf("queryCameras failed\n");
			break;
		}
	}
	

	//wait for camera list change callback
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
	return 0;	
}
