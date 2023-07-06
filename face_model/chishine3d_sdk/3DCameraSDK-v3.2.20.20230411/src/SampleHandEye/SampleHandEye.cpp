
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
#include "handEye.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include "../Utils/BmpUtil.hpp"


#define cheeseBoardHorizontalPoints    9
#define cheeseBoardVerticalPoints      6

bool g_bCaptureFlag = false;
bool g_bDetectedFlag = false;
std::ofstream f_pose;
std::ofstream f_points;

// save depth data as depth-stream callback
void depth_callback(cs::IFramePtr frame, void *usrData)
{
	if(g_bCaptureFlag == true)
	{
		ERROR_CODE ret = SUCCESS;
		std::vector<cs::Point3f> points;
		cs::ICameraPtr camera = *((cs::ICameraPtr *)usrData);
		const char *imageL = frame->getData(FRAME_DATA_FORMAT_IR_LEFT);
		const char *imageR = frame->getData(FRAME_DATA_FORMAT_IR_RIGHT);
		if (imageL)
		{
			cs::saveBmp(imageL, frame->getWidth(), frame->getHeight(), 1, "HandEyeLeft.bmp");
		}
		if (imageR)
		{
			cs::saveBmp(imageR, frame->getWidth(), frame->getHeight(), 1, "HandEyeRight.bmp");
		}
		points.reserve(cheeseBoardHorizontalPoints*cheeseBoardVerticalPoints);
		ret = reconstructChessboardPoints(camera, frame, points, cheeseBoardHorizontalPoints, cheeseBoardVerticalPoints);
		if(ret == SUCCESS)
		{
			g_bDetectedFlag = true;
			std::ofstream resultPoints;
			resultPoints.open("resultpoints.txt");
			for(auto point : points)
			{
				f_points << point.x << " " << point.y << " " << point.z << "\n";
				resultPoints << point.x << " " << point.y << " " << point.z << "\n";
			}

			resultPoints.close();
		}
		else
		{
			g_bDetectedFlag = false;
		}
		g_bCaptureFlag = false;
	}
}

// capture frame and detecte cheese board corners
int capture_frame()
{
	g_bCaptureFlag = true;
	while(g_bCaptureFlag)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
	if(g_bDetectedFlag == true)
	{
		g_bDetectedFlag = false;
		return 0;
	}
	else
	{
		return -1;
	}
}

// get robot pose by manul input
void input_pose()
{
	std::cout << "Please input x y z o a t\n";
	float x,y,z,o,a,t;
	
	std::cin >> x >> y >> z >> o >> a >> t;
	f_pose << x << " " << y << " " << z << " " << o << " " << a << " " << t << "\n";
}

// get left and right ir image and robot pose for calibrating
int captureCalibrationImageAndGetRobotPose()
{
	int ret;

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
	for (auto streamInfo : streamInfos)
	{
		if (streamInfo.format == STREAM_FORMAT_PAIR)
		{
			ret = camera->startStream(STREAM_TYPE_DEPTH, streamInfo, depth_callback, (void *)&camera);
			printf("format: %d, width: %d, height: %d, fps: %f\n", streamInfo.format, streamInfo.width, streamInfo.height, streamInfo.fps);
			if (ret != SUCCESS)
			{
				printf("camera start depth stream failed(%d)!\n", ret);
				return -1;
			}
			break;
		}
	}

	// set depth-stream gain 2x
	ret = camera->setProperty(STREAM_TYPE_DEPTH, PROPERTY_GAIN, 2);
	if (ret != SUCCESS)
	{
		printf("camera set gain failed(%d)!\n", ret);
		return -1;
	}
	
	
	// set depth-stream exposure 88ms
	ret = camera->setProperty(STREAM_TYPE_DEPTH, PROPERTY_EXPOSURE, 15000);
	if (ret != SUCCESS)
	{
		printf("camera set exposure failed(%d)!\n", ret);
		return -1;
	}
	

	f_pose.open("pose.txt");
	f_points.open("points.txt");
	
	// capture frame and reconstruct chessboard cornner points
	for(;;)
	{
		static int image_count = 0;
		std::cin.clear();
		
		printf( "C - capture frame.\n");
		printf( "X - exit.\n");
		
		char key;
		std::cin >> key;
		
		if(key == 'C' || key == 'c')
		{
			// capture cheese board corners
			if(capture_frame() == 0)
			{
				// get current robot pose
				input_pose();
				printf("capture frame(%d) and detected chessboard points successs\n", image_count++);
			}
		}
		else if( key == 'X' || key == 'x')
		{
			break;
		}
	}

	f_pose.close();
	f_points.close();
	
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

// calibrate hand in eye matrix
int calibrateEyeInHand()
{
	std::ifstream fin_pose;
	std::ifstream fin_points;
	std::vector<cs::RobotPose> poses;
	std::vector<cs::HandEyeCalibrationInput> inputs;
	cs::Point3f point;
	cs::HandEyeMatrix matrix;
	
	// get robot poses by file `pose.txt`
	fin_pose.open("pose.txt");
	char str_pose[1024];
	if(fin_pose.is_open())
	{
		while(!fin_pose.eof())
		{
			fin_pose.getline(str_pose,sizeof(str_pose));
			cs::RobotPose pose;
			
			if(sscanf(str_pose, "%f %f %f %f %f %f\n", &pose.x, &pose.y, &pose.z, &pose.alfa, &pose.beta, &pose.gamma) < 0)
				break;
			
			poses.push_back(pose);
		}
	}
	fin_pose.close();

	// get cheese board points in every pose by file `points.txt`
	fin_points.open("points.txt");
	char str_point[1024];
	if(fin_points.is_open())
	{
		for(int i = 0; i < poses.size(); i ++)
		{
			std::vector<cs::Point3f> points;
			for(int j = 0; j < cheeseBoardHorizontalPoints * cheeseBoardVerticalPoints; j++)
			{
				fin_points.getline(str_point,sizeof(str_point));
				sscanf(str_point, "%f %f %f\n", &point.x, &point.y, &point.z);
				points.push_back(point);
			}
			cs::HandEyeCalibrationInput input(cs::RobotPoseMatrix4f(poses[i], cs::POSE_TYPE_RPY, cs::POSE_UNIT_DEGREE), points);
			inputs.push_back(input);
		}
	}
	fin_points.close();
	
	// calculate eye in hand matrix
	double error;
	cs::calibrateEyeInHand(inputs, matrix, &error);
	
	printf("eye in hand matrix :\n");
	printf("[%.4f\t%.4f\t%.4f\t%.4f \n",matrix.r00, matrix.r01, matrix.r02, matrix.tx);
	printf(" %.4f\t%.4f\t%.4f\t%.4f \n",matrix.r10, matrix.r11, matrix.r12, matrix.ty);
	printf(" %.4f\t%.4f\t%.4f\t%.4f \n",matrix.r20, matrix.r21, matrix.r22, matrix.tz);
	printf(" %.4f\t%.4f\t%.4f\t%.4f]\n",matrix.zero0, matrix.zero1, matrix.zero2, matrix.one);
	printf("error: %.4f\n", float(error));

	// save hand-eye matrix to `matrix_para.txt"`
	std::ofstream matrix_para;
	matrix_para.open("matrix_para.txt");
	if (matrix_para.is_open())
	{
		matrix_para << matrix.r00 << " " << matrix.r01 << " " << matrix.r02 << " " << matrix.tx << " " <<
			matrix.r10 << " " << matrix.r11 << " " << matrix.r12 << " " << matrix.ty << " " <<
			matrix.r20 << " " << matrix.r21 << " " << matrix.r22 << " " << matrix.tz << " " <<
			matrix.zero0 << " " << matrix.zero1 << " " << matrix.zero2 << " " << matrix.one << "\n";
	}
	matrix_para.close();

	return 0;
}

int main()
{
	cs::enableLoging(true);
	
	printf( "This is SampleHandEye sample!\n");
	printf( "This sample only support robots in Euler RPY coordinate system !\n\n");
	
	for(;;)
	{
		std::cin.clear();
		
		printf( "1 - capture image and get robot pose.\n");
		printf( "2 - calibrate eye in hand matrix.\n");
		printf( "0 - exit\n");
		
		char key;
		std::cin >> key;
		if(key == '1')
		{
			captureCalibrationImageAndGetRobotPose();
		}
		else if( key == '2')
		{
			calibrateEyeInHand();
		}
		else if( key == '0')
		{
			break;
		}
		
	}
	return 0;	
}

