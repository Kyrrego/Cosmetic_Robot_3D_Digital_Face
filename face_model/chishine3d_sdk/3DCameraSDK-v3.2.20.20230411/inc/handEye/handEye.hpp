/*****************************************************************************
*  3DCamera SDK header
*
*
*  @file     HandEye.hpp
*  @brief    3DCamera sdk header
*
*  @version  1.0
*  @date     2020 / 05 / 09
*
*****************************************************************************/
#ifndef __HANDEYE_HPP__
#define __HANDEYE_HPP__

#include <vector>
#include "handEyeInput.hpp"
#include "hpp/Camera.hpp"
#include "hpp/Frame.hpp"
#include "hpp/APIExport.hpp"

namespace cs
{
/**
* @~chinese
* \defgroup HandEye 手眼标定
* @brief 提供手眼标定数据采集，参数计算，并使用标定结果将眼坐标系下的点或者向量转换到手的坐标系下
* @{
* @~english
* \defgroup HandEye HandEye Calibration
* @brief Provide functions for eye-hand calibration
* @{
*/

/**
* @~chinese
* @brief 枚举: 基线方向，请参照例子设置
* @~english
* @brief enumeration: The baseline direction
**/
typedef enum
{
	BASELINE_HORIZONTAL  = 0x00,	/**< @~chinese 水平基线		@~english baseline is horizontal*/ 
	BASELINE_VERTICAL    = 0x01,	/**< @~chinese 垂直基线		@~english baseline is vertical*/ 
}BASELINE_TYPE;

/**
* @~chinese
* @brief         下载重建标定板用的相机参数，保存到指定目录
* @param[in]     camera                      : 已连接成功的相机指针
* @param[in]     cameraParamPath             : 保存参数的文件夹路径
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         download params of camera，save to the specified folder
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     cameraParamPath             : the absolute path of the specified folder
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE downloadCameraParams(ICameraPtr camera, const char* cameraParamPath);

/**
* @~chinese
* @brief         重建棋盘格标定板角点坐标
* @param[in]     cameraParamPath             : 保存相机参数的路径
* @param[in]     imageLeft                   : 左相机图像
* @param[in]     imageRight                  : 右相机图像
* @param[in]     width	                     : 图像宽度
* @param[in]     height						 : 图像高度
* @param[out]    points                      : 重建的标定板角点输出
* @param[out]    constraintPoints            : 输出相机坐标系下的特征点（标定板的四个角）
* @param[in]     chessboardHorizontalPoints  : 横向标定板角点数
* @param[in]     chessboardVerticalPoints    : 竖向标定板角点数
* @param[in]     chessboardGridSize          : 标定板格子宽度
* @param[out]    error                       : 输出重建误差
* @return     成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         reconstruct chessboard points
* @param[in]     cameraParamPath             : the absolute path of the camera params
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[out]    constraintPoints            : output the reconstructed constraint points in eye（At the four corners of chessboard）
* @param[in]     chessboardHorizontalPoints	 : number of horizontal chessboard points
* @param[in]     chessboardVerticalPoints    : number of vertical chessboard points
* @param[in]     chessboardGridSize          : the grid width of chessboard
* @param[out]    error                       : output the reconstruction error
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE reconstructChessboardPoints(const char* cameraParamPath, const unsigned char* imageLeft, const unsigned char* imageRight, int width, int height,
    std::vector<cs::Point3f> &points, std::vector<cs::Point3f> &constraintPoints,
    int chessboardHorizontalPoints, int chessboardVerticalPoints, float chessboardGridSize, float &error);

/**
* @~chinese
* @brief         重建圆点阵标定板的圆心坐标
* @param[in]     cameraParamPath             : 保存相机参数的路径
* @param[in]     imageLeft                   : 左相机图像
* @param[in]     imageRight                  : 右相机图像
* @param[in]     width	                     : 图像宽度
* @param[in]     height						 : 图像高度
* @param[out]    points                      : 重建的标定板角点输出
* @param[out]    constraintPoints            : 输出相机坐标系下的特征点（4个十字交叉点）
* @param[in]     boardHorizontalPoints       : 横向标定板角点数
* @param[in]     boardVerticalPoints         : 竖向标定板角点数
* @param[in]     boardGridSize               : 圆心间间距
* @param[in]     circleRadius                : 小圆半径
* @param[in]     bigCircleSetting            : 大圆位置
* @return     成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         reconstruct the center of circles on the circleboard
* @param[in]     cameraParamPath             : the absolute path of the camera params
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[out]    constraintPoints            : output the reconstructed constraint points in eye（four crosses on circleboard）
* @param[in]     boardHorizontalPoints	     : number of horizontal chessboard points
* @param[in]     boardVerticalPoints         : number of vertical chessboard points
* @param[in]     boardGridSize               : the distance between the circles
* @param[in]     circleRadius                : radius of circle
* @param[in]     bigCircleSetting            : position setting of big circle
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE reconstructCircleboardPoints(const char* cameraParamPath, const unsigned char* imageLeft, const unsigned char* imageRight, int width, int height,
    std::vector<cs::Point3f> &points, std::vector<cs::Point3f> &constraintPoints, int boardHorizontalPoints, int boardVerticalPoints,
    float boardGridSize, float circleRadius, std::vector<std::pair<int, int>> bigCircleSetting, float &error);

/**
* @~chinese
* @brief         重建棋盘格标定板角点坐标
* @param[in]     camera                      : 已连接成功的相机指针
* @param[in]     imageLeft                   : 左相机图像
* @param[in]     imageRight                  : 右相机图像
* @param[in]     width	                     : 图像宽度
* @param[in]     height						 : 图像高度
* @param[out]    points                      : 重建的标定板角点输出
* @param[out]    constraintPoints            : 输出相机坐标系下的特征点（标定板的四个角）
* @param[in]     boardHorizontalPoints       : 横向标定板角点数
* @param[in]     boardVerticalPoints         : 竖向标定板角点数
* @param[in]     boardGridSize               : 标定板格子宽度
* @param[out]    error                       : 输出重建误差
* @return     成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         reconstruct chessboard points
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[out]    constraintPoints            : output the reconstructed constraint points in eye（At the four corners of chessboard）
* @param[in]     boardHorizontalPoints	     : number of horizontal chessboard points
* @param[in]     boardVerticalPoints         : number of vertical chessboard points
* @param[in]     boardGridSize               : the grid width of chessboard
* @param[out]    error                       : output the reconstruction error
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE reconstructChessboardPoints(ICameraPtr camera, const unsigned char* imageLeft, const unsigned char* imageRight, int width, int height,
    std::vector<cs::Point3f> &points, std::vector<cs::Point3f> &constraintPoints,
    int boardHorizontalPoints, int boardVerticalPoints, float boardGridSize, float &error);

/**
* @~chinese
* @brief         重建圆点阵标定板的圆心坐标
* @param[in]     camera                      : 已连接成功的相机指针
* @param[in]     imageLeft                   : 左相机图像
* @param[in]     imageRight                  : 右相机图像
* @param[in]     width	                     : 图像宽度
* @param[in]     height						 : 图像高度
* @param[out]    points                      : 重建的标定板角点输出
* @param[out]    constraintPoints            : 输出相机坐标系下的特征点（4个十字交叉点）
* @param[in]     boardHorizontalPoints       : 横向标定板角点数
* @param[in]     boardVerticalPoints         : 竖向标定板角点数
* @param[in]     boardGridSize               : 圆心间间距
* @param[in]     circleRadius                : 小圆半径
* @param[in]     bigCircleSetting            : 大圆位置
* @return     成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         reconstruct the center of circles on the circleboard
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[out]    constraintPoints            : output the reconstructed constraint points in eye（four crosses on circleboard）
* @param[in]     boardHorizontalPoints	     : number of horizontal chessboard points
* @param[in]     boardVerticalPoints         : number of vertical chessboard points
* @param[in]     boardGridSize               : the distance between the circles
* @param[in]     circleRadius                : radius of circle
* @param[in]     bigCircleSetting            : position setting of big circle
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE reconstructCircleboardPoints(ICameraPtr camera, const unsigned char* imageLeft, const unsigned char* imageRight, int width, int height, 
    std::vector<cs::Point3f> &points, std::vector<cs::Point3f> &constraintPoints, int boardHorizontalPoints, int boardVerticalPoints,
    float boardGridSize, float circleRadius, std::vector<std::pair<int, int>> bigCircleSetting, float &error);

/**
* @~chinese
* @brief         相机安装在机器人外部时计算旋转平移矩阵
* @param[in]     input           : 相机在机器人外部时的标定输入
* @param[out]    matrix          : 输出的眼到手矩阵
* @param[out]    error           : 输出误差
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         calculate eye to hand matrix when camera is installed outside the robot
* @param[in]     input           : eye to hand calibration input
* @param[out]    matrix          : output eye to hand matrix
* @param[out]    error           : output convergence error
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE calibrateEyeToHand(std::vector<HandEyeCalibrationInput>& input, HandEyeMatrix& matrix, double* error = NULL);

/**
* @~chinese
* @brief         相机固定在机器人上时计算旋转平移矩阵（不需要触碰特征点）
* @param[in]     input           : 相机固定在机器人上时的标定输入
* @param[out]    matrix          : 输出的眼到手矩阵
* @param[out]    error           : 输出误差
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         calculate eye to hand matrix when camera is installed on the robot and without touch the feature points
* @param[in]     input           : eye in hand calibration input
* @param[out]    matrix          : output eye to hand matrix
* @param[out]    error           : output convergence error
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE calibrateEyeInHand(std::vector<HandEyeCalibrationInput>& input, HandEyeMatrix& matrix, double* error = NULL);

/**
* @~chinese
* @brief         使用棋盘格标定板，相机固定在机器人上时计算旋转平移矩阵（需要触碰四个角的角点）
* @param[in]     input                       : 相机在机器人外部时的标定输入
* @param[in]     constraintPoints            : 标定板四个角点在机器人坐标系的坐标
* @param[out]    matrix                      : 输出的眼到手矩阵
* @param[out]    error                       : 输出误差
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         calibrate with chessboard.
*                calculate eye to hand matrix when camera is installed on the robot and need touch the four corner points of chessboard
* @param[in]     input                       : eye to hand calibration input
* @param[in]     constraintPoints            : Coordinates of four corner points of calibration plate in robot coordinate system
* @param[out]    matrix                      : output eye to hand matrix
* @param[out]    error                       : output convergence error
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE calibrateEyeInHandWithChessboardConstraintPoints(std::vector<HandEyeCalibrationInput>& input,
	std::vector<cs::Point3f>& constraintPoints, HandEyeMatrix &matrix, double* error = NULL);

/**
* @~chinese
* @brief         使用圆点阵标定板，相机固定在机器人上时计算旋转平移矩阵（需要触碰四个十字特征点）
* @param[in]     inputs                      : 相机在机器人外部时的标定输入
* @param[in]     constraintPoints            : 标定板四个十字交叉点在机器人坐标系下的坐标
* @param[out]    matrix                      : 输出的眼到手矩阵
* @param[out]    error                       : 输出误差
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         calibrate with circleboard.
*                calculate eye to hand matrix when camera is installed on the robot and need touch the four crosses on the circleboard
* @param[in]     inputs                      : eye to hand calibration input
* @param[in]     constraintPoints            : Coordinates of four crosses on the circleboard in robot coordinate system
* @param[out]    matrix                      : output eye to hand matrix
* @param[out]    error                       : output convergence error
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE calibrateEyeInHandWithCircleboardConstraintPoints(std::vector<HandEyeCalibrationInput>& inputs,
	std::vector<cs::Point3f>& constraintPoints, int boardHorizontalPoints, int boardVerticalPoints, float boardGridSize, HandEyeMatrix &matrix, double* error);

/**
* @~chinese
* @brief         将相机坐标系下的点转到机器人坐标系
* @param[in]     pose           : 机器人当前位姿
* @param[in]     inputPoint     : 相机坐标系下的点
* @param[in]     matrix         : 眼到手矩阵，calibrateEyeToHand/calibrateEyeInHand计算得到
* @param[out]    outPoint       : 输出到机器人坐标系下的点
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         transform point to the coordinate system of hand
* @param[in]     pose           : the pose of robot
* @param[in]     inputPoint     : the input point in eye
* @param[in]     matrix         : the matrix eye to hand, returned by calibrateEyeToHand/calibrateEyeInHand
* @param[out]    outPoint       : output the point in hand
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE transformPointFromEyeToHand(RobotPoseMatrix4f pose, Point3f inputPoint, HandEyeMatrix matrix, Point3f& outPoint);

/**
* @~chinese
* @brief         将相机坐标系下的向量转到机器人坐标系
* @param[in]     pose           : 机器人当前位姿
* @param[in]     inputVector    : 相机坐标系下的向量
* @param[in]     matrix         : 眼到手矩阵，calibrateEyeToHand/calibrateEyeInHand计算得到
* @param[out]    outVector      : 输出到机器人坐标系下的向量
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         transform vector to the coordinate system of hand
* @param[in]     pose           : the pose of robot
* @param[in]     inputVector    : the input vector in eye
* @param[in]     matrix         : the matrix eye to hand, returned by calibrateEyeToHand/calibrateEyeInHand
* @param[out]    outVector      : output the vector in hand
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE transformVectorFromEyeToHand(RobotPoseMatrix4f pose, Vector3f inputVector, HandEyeMatrix matrix, Vector3f& outVector);

/**
* @~chinese
* @brief         将相机坐标系下的位姿转到机器人坐标系
* @param[in]     toolPose       : 机器人当前位姿
* @param[in]     poseInEye      : 相机坐标系下的位姿
* @param[in]     matrix         : 眼到手矩阵，calibrateEyeToHand/calibrateEyeInHand计算得到
* @param[in]	 poseType		：输出位姿表示类型
* @param[in]	 poseUnit		: 输出姿态表示单位角度/弧度
* @param[out]    outPoseInHand  : 输出位姿
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         transform point to the coordinate system of hand
* @param[in]     toolPose       : the pose of robot
* @param[in]     poseInEye      : the input point in eye
* @param[in]     matrix         : the matrix eye to hand, returned by calibrateEyeToHand/calibrateEyeInHand
* @param[in]	 poseType		：type of output pose
* @param[in]	 poseUnit		: unit of output direction(radian/degree)
* @param[out]    outPoseInHand  : the output pose in hand
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE transformPoseFromEyeToHand(RobotPoseMatrix4f toolPose, RobotPoseMatrix4f poseInEye, HandEyeMatrix matrix,
											  RobotPoseType poseType, RobotPoseUnit poseUnit, RobotPose& outPoseInHand);

/**
* @~chinese
* @brief         将相机坐标系下的位姿转到机器人坐标系
* @param[in]     toolPose       : 机器人当前位姿
* @param[in]     poseInEye      : 相机坐标系下的位姿
* @param[in]     matrix         : 眼到手矩阵，calibrateEyeToHand/calibrateEyeInHand计算得到
* @param[out]    outMatrixInHand  : 输出位姿
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         transform point to the coordinate system of hand
* @param[in]     toolPose       : the pose of robot
* @param[in]     poseInEye      : the input point in eye
* @param[in]     matrix         : the matrix eye to hand, returned by calibrateEyeToHand/calibrateEyeInHand
* @param[out]    outMatrixInHand  : the output matrix in hand
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE transformPoseFromEyeToHand(RobotPoseMatrix4f toolPose, RobotPoseMatrix4f poseInEye, HandEyeMatrix matrix,
	RobotPoseMatrix4f outMatrixInHand);

/**
* @~chinese
* @brief         将机器人坐标系下的点转到相机坐标系
* @param[in]     pose           : 机器人当前位姿
* @param[in]     inputPoint     : 机器人坐标系下的点
* @param[in]     matrix         : 眼到手矩阵，calibrateEyeToHand/calibrateEyeInHand计算得到
* @param[out]    outPoint       : 输出相机坐标系下的点
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         transform point to the coordinate system of eye
* @param[in]     pose           : the pose of robot
* @param[in]     inputPoint     : the input point in hand
* @param[in]     matrix         : the matrix eye to hand, returned by calibrateEyeToHand/calibrateEyeInHand
* @param[out]    outPoint       : output the point in eye
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE transformPointFromHandToEye(cs::RobotPoseMatrix4f pose, cs::Point3f inputPoint, cs::HandEyeMatrix matrix, cs::Point3f& outPoint);

/**
* @~chinese
* @brief         将机器人坐标系下的向量转到相机坐标系
* @param[in]     pose           : 机器人当前位姿
* @param[in]     inputVector    : 机器人坐标系下的向量
* @param[in]     matrix         : 眼到手矩阵，calibrateEyeToHand/calibrateEyeInHand计算得到
* @param[out]    outVector      : 输出到相机相机坐标系下的向量
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         transform vector to the coordinate system of hand
* @param[in]     pose           : the pose of robot
* @param[in]     inputVector    : the input vector in eye
* @param[in]     matrix         : the matrix eye to hand, returned by calibrateEyeToHand/calibrateEyeInHand
* @param[out]    outVector      : output the vector in hand
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE transformVectorFromHandToEye(cs::RobotPoseMatrix4f pose, cs::Vector3f inputVector, cs::HandEyeMatrix matrix, cs::Vector3f& outVector);

/**
* @deprecated
* @~chinese
* @brief         通过左右相机图片中提取的特征点坐标计算到三维点坐标
* @param[in]     camera                      : 已连接成功的相机指针
* @param[in]     leftPoints                  : 左相机图片中提取的特征点坐标
* @param[in]     rightPoints                 : 右相机图片中提取的特征点坐标
* @param[out]    points                      : 重建输出的三维点坐标
* @param[in]     type                        : 基线类型
* @return 成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         reconstruct feature points
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     leftPoints                  : left picture feature points
* @param[in]     rightPoints                 : right picture feature points
* @param[out]    points                      : reconstructed points
* @param[in]     type                        : baseline type, @see BASELINE_TYPE
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE reconstructPoints(ICameraPtr camera, std::vector<Point2f> leftPoints, std::vector<Point2f> rightPoints, std::vector<Point3f> &points, BASELINE_TYPE type = BASELINE_HORIZONTAL);

/**
* @deprecated
* @~chinese
* @brief         重建标定板坐标
* @param[in]     camera                      : 已连接成功的相机指针
* @param[in]     pairFrame                   : 格式是STREAM_FORMAT_PAIR的帧数据
* @param[out]    points                      : 重建的标定板角点输出
* @param[in]     chessboardHorizontalPoints  : 横向标定板角点数
* @param[in]     chessboardVerticalPoints    : 竖向标定板角点数
* @param[in]     type                        : 基线方向, @参见 BASELINE_TYPE
* @return     成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         reconstruct chessboard points
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     pairFrame                   : the frame which format is STREAM_FORMAT_PAIR
* @param[out]    points                      : output the reconstructed chessboard points
* @param[in]     chessboardHorizontalPoints	 : number of horizontal chessboard points
* @param[in]     chessboardVerticalPoints    : number of vertical chessboard points
* @param[in]     type                        : baseline type, @see BASELINE_TYPE
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE reconstructChessboardPoints(ICameraPtr camera, IFramePtr pairFrame, std::vector<Point3f> &points, int chessboardHorizontalPoints = 9, int chessboardVerticalPoints = 6, BASELINE_TYPE type = BASELINE_HORIZONTAL);

/**
* @deprecated
* @~chinese
* @brief         重建标定板坐标
* @param[in]     camera                      : 已连接成功的相机指针
* @param[in]     imageLeft                   : 左相机图像
* @param[in]     imageRight                  : 右相机图像
* @param[in]     width	                     : 图像宽度
* @param[in]     height						 : 图像高度
* @param[out]    points                      : 重建的标定板角点输出
* @param[in]     chessboardHorizontalPoints  : 横向标定板角点数
* @param[in]     chessboardVerticalPoints    : 竖向标定板角点数
* @param[in]     type                        : 基线方向, @参见 BASELINE_TYPE
* @return     成功:SUCCESS, 失败:其他错误码
* @~english
* @brief         reconstruct chessboard points
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[in]     chessboardHorizontalPoints	 : number of horizontal chessboard points
* @param[in]     chessboardVerticalPoints    : number of vertical chessboard points
* @param[in]     type                        : baseline type, @see BASELINE_TYPE
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE reconstructChessboardPoints(ICameraPtr camera, const unsigned char* imageLeft, const unsigned char* imageRight, int width, int height, std::vector<cs::Point3f> &points, int chessboardHorizontalPoints = 9, int chessboardVerticalPoints = 6, BASELINE_TYPE type = BASELINE_HORIZONTAL);

/*@} */
}

#endif
