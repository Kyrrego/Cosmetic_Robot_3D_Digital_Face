
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
#include <chrono>
#include <iostream>
#include "3DCamera.hpp"
#include "stdio.h"
#include "handEye.hpp"
#include "../Utils/BmpUtil.hpp"

void printMatrix(cs::HandEyeMatrix& matrix)
{
	printf("[%.4f\t%.4f\t%.4f\t%.4f \n", matrix.r00, matrix.r01, matrix.r02, matrix.tx);
	printf(" %.4f\t%.4f\t%.4f\t%.4f \n", matrix.r10, matrix.r11, matrix.r12, matrix.ty);
	printf(" %.4f\t%.4f\t%.4f\t%.4f \n", matrix.r20, matrix.r21, matrix.r22, matrix.tz);
	printf(" %.4f\t%.4f\t%.4f\t%.4f]\n", matrix.zero0, matrix.zero1, matrix.zero2, matrix.one);

}

int main()
{
	printf( "This is SampleHandEye sample!\n");
	
#ifdef DOWNLOAD_PARAM_ONLINE
    // get camera pointer and connect a valid camera
    cs::ICameraPtr camera = cs::getCameraPtr();
    auto ret = camera->connect();
    if (ret != SUCCESS)
    {
        printf("camera connect failed(%d)!\n", ret);
        return -1;
    }
    cs::downloadCameraParams(camera, ".");
#endif

    std::cout << "step 1: get images and reconstruct points" << std::endl;
    //config board 
    int horizontalPoints = 11;
    int verticalPoints = 9;
    float gridSize = 15;
    float circleRadius = 4.5; 
    std::vector<std::pair<int, int>> bigCircleSetting =
    { { 4,2 },{ 5,2 },{ 2,4 },{ 8,4 },{ 5,6 } };

    //config robot pose type
    cs::RobotPoseType poseType = cs::POSE_TYPE_EULER_XYZ;
    cs::RobotPoseUnit poseUnit = cs::POSE_UNIT_DEGREE;

    //read input image and pose
    std::vector<cs::HandEyeCalibrationInput> inputs = {};
    {
        std::fstream fs("data/pose.txt");
        if (!fs.is_open())
        {
            return -2;
        }
        char imageL[1024];
        char imageR[1024];
        int index = 0;
        std::vector<char> bgrL, bgrR;
        std::vector<char> grayL, grayR;
        int width, height;
        while (!fs.eof())
        {
            cs::RobotPose pose;
            fs >> pose.x;
            fs >> pose.y;
            fs >> pose.z;
            fs >> pose.alfa;
            fs >> pose.beta;
            fs >> pose.gamma;
            if (fabs(pose.x) < 1e-6 && fabs(pose.y) < 1e-6 && fabs(pose.z) < 1e-6)
                break;
            sprintf(imageL, "data/imageL%d.bmp", index);
            sprintf(imageR, "data/imageR%d.bmp", index);

            if (cs::readBmp(imageL, bgrL, width, height) && cs::convertBgrToGray(bgrL, width, height, grayL)
                && cs::readBmp(imageR, bgrR, width, height) && cs::convertBgrToGray(bgrR, width, height, grayR))
            {
                std::vector<cs::Point3f> points;
                std::vector<cs::Point3f> constraintPoints;
                float error;
                if (cs::reconstructCircleboardPoints("data/camparam", (const unsigned char*)grayL.data(), (const unsigned char*)grayR.data(), width, height,
                    points, constraintPoints, horizontalPoints, verticalPoints, gridSize,
                    circleRadius, bigCircleSetting, error) == SUCCESS)
                {
                    cs::HandEyeCalibrationInput input(cs::RobotPoseMatrix4f(pose, poseType, poseUnit), points);
                    inputs.push_back(input);
                    std::cout << "image" << index << " reconstruct success! error=" << error << std::endl;
                }
                else
                {
                    std::cout << "image" << index << " reconstruct failed!" << std::endl;
                }
            }
          
            index++;
        }
        fs.close();
    }

    //calculate hand eye matrix
    std::cout << std::endl << "step 2: calculate hand eye matrix" << std::endl;
    cs::HandEyeMatrix handeyeMatrix;
    double handeyeError;
    cs::calibrateEyeInHand(inputs, handeyeMatrix, &handeyeError);
    std::cout << "calculate hand eye matrix success! error=" << handeyeError << std::endl;
    printMatrix(handeyeMatrix);

    //read constraint points
    std::vector<cs::Point3f> constraintPoints;
    {
        std::fstream fs("data/constraintPoints.txt");
        if (!fs.is_open())
        {
            return -3;
        }

        while (!fs.eof())
        {
            cs::Point3f point;
            fs >> point.x;
            fs >> point.y;
            fs >> point.z;
            constraintPoints.push_back(point);
        }

    }

    if (!constraintPoints.size())
        return -4;

    //calculate and save handeye matrix with constraint points
    cs::calibrateEyeInHandWithCircleboardConstraintPoints(inputs, constraintPoints, horizontalPoints,verticalPoints, gridSize, handeyeMatrix, &handeyeError);
    std::cout << "calculate hand eye matrix with constraint points success! error=" << handeyeError << std::endl;
    printMatrix(handeyeMatrix);
    char usrInfo[100];
    sprintf(usrInfo, "%d %d", poseType, poseUnit);
    handeyeMatrix.save("data/handeye.yaml", usrInfo);

    //sample for load handeye matrix
    cs::HandEyeMatrix testMatrix;
    testMatrix.load("data/handeye.yaml", nullptr, 0);
    std::cout << "loaded matrix :\n";
    printMatrix(testMatrix);

    //sample for transform point from eye to hand
    cs::RobotPose testPose = { 100, 100, 100, 45, 45, 45 };
    cs::RobotPoseMatrix4f pose(testPose, poseType, poseUnit);
    cs::Point3f testPoint = {100, 100, 100};
    cs::Point3f outputPoint;
    transformPointFromEyeToHand(pose, testPoint, testMatrix, outputPoint);
    system("pause");
	return 0;	
}

