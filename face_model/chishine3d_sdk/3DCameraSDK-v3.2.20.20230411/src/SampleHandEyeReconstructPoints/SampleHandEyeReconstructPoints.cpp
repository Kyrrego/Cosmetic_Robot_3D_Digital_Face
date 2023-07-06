
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

int main()
{
	std::shared_ptr<cs::ICamera> camera = cs::getCameraPtr();
	if (camera->connect() != SUCCESS)
	{
		printf("no camera to connect\n");
		getchar();
		return EXIT_SUCCESS;
	}

	std::vector<cs::Point2f> leftPoints;
	std::vector<cs::Point2f> rightPoints;

#if 0
	float leftPoses[] = { 364.36,173.42 };
	float rightPoses[] = { 379.44 ,114.27 };

	for (int i = 0; i < 1; i++)
	{
		cs::Point2f lp;
		lp.x = leftPoses[2 * i];
		lp.y = leftPoses[2 * i + 1];
		leftPoints.push_back(lp);

		lp.x = rightPoses[2 * i];
		lp.y = rightPoses[2 * i + 1];
		rightPoints.push_back(lp);
	}
#else
	for (int i = 0; i < 10; i++)
	{
		cs::Point2f lp;
		lp.x = (i + 1) * 10;
		lp.y = (i + 2) * 15;
		leftPoints.push_back(lp);

		lp.x = (i + 1) * 8;
		lp.y = (i + 2) * 12;
		rightPoints.push_back(lp);
	}

#endif
	std::vector<cs::Point3f> points;
	reconstructPoints(camera, leftPoints, rightPoints, points);

	for (int i = 0; i < points.size(); i++)
	{
		printf("reconstruct points(%d)  (%f,%f,%f)\n", i, points[i].x, points[i].y, points[i].z);
	}

	printf("complete reconstructpoints\n");
	getchar();

	return EXIT_SUCCESS;
}

