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

using namespace cs;
#define FALSE false
#define TRUE true

// save depth data as depth-stream callback
void depthCallback(cs::IFramePtr frame, void *usrData)
{
	printf("Get one frame!\n");
	//cs::colorizer color;
	std::vector<unsigned char> rgb;
	int length = frame->getHeight() * frame->getWidth();
	rgb.resize(length * 3);
	cs::ICameraPtr *camera = (cs::ICameraPtr *)usrData;
	PropertyExtension v;
	float scale = 0.1f;
	if (camera->get()->getPropertyExtension(PROPERTY_EXT_DEPTH_SCALE, v))
		scale = v.depthScale;
	//color.process((unsigned short *)frame->getData(FRAME_DATA_FORMAT_Z16), scale, rgb.data(), length);
	//cs::saveBmp((const char *)rgb.data(), frame->getWidth(), frame->getHeight(), 3, "SoftTrigger.bmp");
};

int triggerModeTest()
{
	printf("This is SampleSoftTrigger sample!\n\n");
	ERROR_CODE ret;

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
		return FALSE;
	}



	// display informations of camera
	printf("%20s  :  %s\n", "name", info.name);
	printf("%20s  :  %s\n", "serial", info.serial);
	printf("%20s  :  %s\n", "unique id", info.uniqueId);
	printf("%20s  :  %s\n", "firmware version", info.firmwareVersion);
	printf("%20s  :  %s\n", "algorithm version", info.algorithmVersion);
	printf("\n");

	// get  informations of depth-stream 
	std::vector<StreamInfo> depthStreamInfos;
	ret = camera->getStreamInfos(STREAM_TYPE_DEPTH, depthStreamInfos);
	if (ret != SUCCESS)
	{
		printf("camera get stream info failed(%d)!\n", ret);
		return -1;
	}

	// display  informations of depth-stream 
	for (int i = 0; i < depthStreamInfos.size(); i++)
	{
		printf("depth format:%2d, width:%4d, height:%4d, fps:%2.1f\n", depthStreamInfos[i].format, depthStreamInfos[i].width, depthStreamInfos[i].height, depthStreamInfos[i].fps);
	}
	printf("\n");

	// start depth-stream in second information of depth-stream, callback mode
	for (auto streamInfo : depthStreamInfos)
	{
		if (streamInfo.format == STREAM_FORMAT_Z16 )
		{
			ret = camera->startStream(STREAM_TYPE_DEPTH, streamInfo, NULL, NULL);
			if (ret != SUCCESS)
			{
				printf("camera start depth stream failed(%d)!\n", ret);
				return -1;
			}
			else
			{
				printf("start depth format:%2d, width:%4d, height:%4d, fps:%2.1f\n", streamInfo.format, streamInfo.width, streamInfo.height, streamInfo.fps);
			}
			break;
		}
	}

	std::vector<StreamInfo> rgbStreamInfos;
	ret = camera->getStreamInfos(STREAM_TYPE_RGB, rgbStreamInfos);
	if (ret != SUCCESS)
	{
		printf("camera get stream info failed(%d)!\n", ret);
		return -1;
	}

	// display  informations of depth-stream 
	for (int i = 0; i < rgbStreamInfos.size(); i++)
	{
		printf("rgb format:%2d, width:%4d, height:%4d, fps:%2.1f\n", rgbStreamInfos[i].format, rgbStreamInfos[i].width, rgbStreamInfos[i].height, rgbStreamInfos[i].fps);
	}
	printf("\n");

	// start rgb-stream in second information of rgb-stream, callback mode
	for (auto streamInfo : rgbStreamInfos)
	{
		if (streamInfo.format == STREAM_FORMAT_RGB8 
			//|| streamInfo.format == STREAM_FORMAT_MJPG
			)
		{
			ret = camera->startStream(STREAM_TYPE_RGB, streamInfo, NULL, NULL);
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

	//设置增益
	ret = camera->setProperty(STREAM_TYPE_DEPTH, PROPERTY_GAIN, 1.0f);
	if (ret != SUCCESS)
	{
		printf("Camera set expsoure failed!(errorcode:%d)\n", ret);
	}

	//设置帧时间
	ret = camera->setProperty(STREAM_TYPE_DEPTH, PROPERTY_FRAMETIME, 10000.0f);
	if (ret != SUCCESS)
	{
		printf("Camera set frametime failed!(errorcode:%d)\n", ret);
	}

	//设置曝光
	ret = camera->setProperty(STREAM_TYPE_DEPTH, PROPERTY_EXPOSURE, 8000.0f);
	if (ret != SUCCESS)
	{
		printf("Camera set expsoure failed!(errorcode:%d)\n", ret);
	}

	

	// set camera in soft-trigger mode
	PropertyExtension triggerMode;
	triggerMode.triggerMode = TRIGGER_MODE_SOFTWAER;
	ret = camera->setPropertyExtension(PROPERTY_EXT_TRIGGER_MODE, triggerMode);
	if (ret != SUCCESS)
	{
		printf("camera set soft trigger mode failed(%d)!\n", ret);
		return -1;
	}
	else
	{
		printf("camera set soft trigger mode success!\n");
	}

	//设置深度范围
	PropertyExtension value;
	value.depthRange.min = 460;
	value.depthRange.max = 520;
	camera->setPropertyExtension(PROPERTY_EXT_DEPTH_RANGE, value);

	//设置RGB和深度的匹配阈值
	PropertyExtension matchParam;
	matchParam.depthRgbMatchParam.iRgbOffset = 0;
	matchParam.depthRgbMatchParam.iDifThreshold = 0;
	camera->setPropertyExtension(PROPERTY_EXT_DEPTH_RGB_MATCH_PARAM, matchParam);

	int iSuccessNum = 0;
	int iFailedNum = 0;

	for (int i = 0;; i++)
	{
		// soft trigger 1 frame
		ret = camera->softTrigger();
		if (ret != SUCCESS)
		{
			iFailedNum++;
			printf("camera soft trigger failed(%d)!\n", iFailedNum);
			continue;
		}

		cs::IFramePtr depthFrame, rgbFrame;
		if (camera->getPairedFrame(depthFrame,rgbFrame, 3000) != SUCCESS)
		{
			iFailedNum++;
			printf("camera get frame failed(%d),successNum(%d)!\n", iFailedNum, iSuccessNum);
			continue;
		}

		saveFrameData("./imgs",depthFrame, i);
		saveFrameData("./imgs",rgbFrame, i);

		depthFrame->getData(FRAME_DATA_FORMAT_IR_LEFT);
		depthFrame->getData(FRAME_DATA_FORMAT_IR_RIGHT);

		iSuccessNum++;
		printf("soft trigger success %d times,failed %d times,frame data:%d\n"
			, iSuccessNum, iFailedNum
			, depthFrame->getSize()
		);
	}

	// stop depth-stream
	ret = camera->stopStream(STREAM_TYPE_DEPTH);
	if (ret != SUCCESS)
	{
		printf("camera stop depth stream failed(%d)!\n", ret);
		return -1;
	}

	// disconnect camera
	ret = camera->disconnect();
	if (ret != SUCCESS)
	{
		printf("camera disconnect failed(%d)!\n", ret);
		return -1;
	}

	return 0;
}


int main()
{
	printf("This is SampleSoftTrigger sample!\n\n");
	int iSuccessNum = 0;
	int iFailedNum = 0;

	for (int i = 0; i < 10000; i++)
	{
		try
		{
			if (triggerModeTest())
			{
				iSuccessNum++;
			}
			else
			{
				iFailedNum++;
			}
		}
		catch (...)
		{
			printf("TriggerModeTestMain catch error");
		}


		printf("TriggerModeTest %d times,success %d times,failed %d times\n"
			, i + 1, iSuccessNum, iFailedNum);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}

	return 0;
}

