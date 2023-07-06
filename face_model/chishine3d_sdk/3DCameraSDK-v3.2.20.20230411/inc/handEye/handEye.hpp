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
* \defgroup HandEye ���۱궨
* @brief �ṩ���۱궨���ݲɼ����������㣬��ʹ�ñ궨�����������ϵ�µĵ��������ת�����ֵ�����ϵ��
* @{
* @~english
* \defgroup HandEye HandEye Calibration
* @brief Provide functions for eye-hand calibration
* @{
*/

/**
* @~chinese
* @brief ö��: ���߷����������������
* @~english
* @brief enumeration: The baseline direction
**/
typedef enum
{
	BASELINE_HORIZONTAL  = 0x00,	/**< @~chinese ˮƽ����		@~english baseline is horizontal*/ 
	BASELINE_VERTICAL    = 0x01,	/**< @~chinese ��ֱ����		@~english baseline is vertical*/ 
}BASELINE_TYPE;

/**
* @~chinese
* @brief         �����ؽ��궨���õ�������������浽ָ��Ŀ¼
* @param[in]     camera                      : �����ӳɹ������ָ��
* @param[in]     cameraParamPath             : ����������ļ���·��
* @return �ɹ�:SUCCESS, ʧ��:����������
* @~english
* @brief         download params of camera��save to the specified folder
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     cameraParamPath             : the absolute path of the specified folder
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE downloadCameraParams(ICameraPtr camera, const char* cameraParamPath);

/**
* @~chinese
* @brief         �ؽ����̸�궨��ǵ�����
* @param[in]     cameraParamPath             : �������������·��
* @param[in]     imageLeft                   : �����ͼ��
* @param[in]     imageRight                  : �����ͼ��
* @param[in]     width	                     : ͼ����
* @param[in]     height						 : ͼ��߶�
* @param[out]    points                      : �ؽ��ı궨��ǵ����
* @param[out]    constraintPoints            : ����������ϵ�µ������㣨�궨����ĸ��ǣ�
* @param[in]     chessboardHorizontalPoints  : ����궨��ǵ���
* @param[in]     chessboardVerticalPoints    : ����궨��ǵ���
* @param[in]     chessboardGridSize          : �궨����ӿ��
* @param[out]    error                       : ����ؽ����
* @return     �ɹ�:SUCCESS, ʧ��:����������
* @~english
* @brief         reconstruct chessboard points
* @param[in]     cameraParamPath             : the absolute path of the camera params
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[out]    constraintPoints            : output the reconstructed constraint points in eye��At the four corners of chessboard��
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
* @brief         �ؽ�Բ����궨���Բ������
* @param[in]     cameraParamPath             : �������������·��
* @param[in]     imageLeft                   : �����ͼ��
* @param[in]     imageRight                  : �����ͼ��
* @param[in]     width	                     : ͼ����
* @param[in]     height						 : ͼ��߶�
* @param[out]    points                      : �ؽ��ı궨��ǵ����
* @param[out]    constraintPoints            : ����������ϵ�µ������㣨4��ʮ�ֽ���㣩
* @param[in]     boardHorizontalPoints       : ����궨��ǵ���
* @param[in]     boardVerticalPoints         : ����궨��ǵ���
* @param[in]     boardGridSize               : Բ�ļ���
* @param[in]     circleRadius                : СԲ�뾶
* @param[in]     bigCircleSetting            : ��Բλ��
* @return     �ɹ�:SUCCESS, ʧ��:����������
* @~english
* @brief         reconstruct the center of circles on the circleboard
* @param[in]     cameraParamPath             : the absolute path of the camera params
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[out]    constraintPoints            : output the reconstructed constraint points in eye��four crosses on circleboard��
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
* @brief         �ؽ����̸�궨��ǵ�����
* @param[in]     camera                      : �����ӳɹ������ָ��
* @param[in]     imageLeft                   : �����ͼ��
* @param[in]     imageRight                  : �����ͼ��
* @param[in]     width	                     : ͼ����
* @param[in]     height						 : ͼ��߶�
* @param[out]    points                      : �ؽ��ı궨��ǵ����
* @param[out]    constraintPoints            : ����������ϵ�µ������㣨�궨����ĸ��ǣ�
* @param[in]     boardHorizontalPoints       : ����궨��ǵ���
* @param[in]     boardVerticalPoints         : ����궨��ǵ���
* @param[in]     boardGridSize               : �궨����ӿ��
* @param[out]    error                       : ����ؽ����
* @return     �ɹ�:SUCCESS, ʧ��:����������
* @~english
* @brief         reconstruct chessboard points
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[out]    constraintPoints            : output the reconstructed constraint points in eye��At the four corners of chessboard��
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
* @brief         �ؽ�Բ����궨���Բ������
* @param[in]     camera                      : �����ӳɹ������ָ��
* @param[in]     imageLeft                   : �����ͼ��
* @param[in]     imageRight                  : �����ͼ��
* @param[in]     width	                     : ͼ����
* @param[in]     height						 : ͼ��߶�
* @param[out]    points                      : �ؽ��ı궨��ǵ����
* @param[out]    constraintPoints            : ����������ϵ�µ������㣨4��ʮ�ֽ���㣩
* @param[in]     boardHorizontalPoints       : ����궨��ǵ���
* @param[in]     boardVerticalPoints         : ����궨��ǵ���
* @param[in]     boardGridSize               : Բ�ļ���
* @param[in]     circleRadius                : СԲ�뾶
* @param[in]     bigCircleSetting            : ��Բλ��
* @return     �ɹ�:SUCCESS, ʧ��:����������
* @~english
* @brief         reconstruct the center of circles on the circleboard
* @param[in]     camera                      : camera pointer, @see ICameraPtr
* @param[in]     imageLeft                   : left image
* @param[in]     imageRight                  : right image
* @param[in]     width	                     : the width of image
* @param[in]     height						 : the height of image
* @param[out]    points                      : output the reconstructed chessboard points
* @param[out]    constraintPoints            : output the reconstructed constraint points in eye��four crosses on circleboard��
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
* @brief         �����װ�ڻ������ⲿʱ������תƽ�ƾ���
* @param[in]     input           : ����ڻ������ⲿʱ�ı궨����
* @param[out]    matrix          : ������۵��־���
* @param[out]    error           : ������
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ����̶��ڻ�������ʱ������תƽ�ƾ��󣨲���Ҫ���������㣩
* @param[in]     input           : ����̶��ڻ�������ʱ�ı궨����
* @param[out]    matrix          : ������۵��־���
* @param[out]    error           : ������
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ʹ�����̸�궨�壬����̶��ڻ�������ʱ������תƽ�ƾ�����Ҫ�����ĸ��ǵĽǵ㣩
* @param[in]     input                       : ����ڻ������ⲿʱ�ı궨����
* @param[in]     constraintPoints            : �궨���ĸ��ǵ��ڻ���������ϵ������
* @param[out]    matrix                      : ������۵��־���
* @param[out]    error                       : ������
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ʹ��Բ����궨�壬����̶��ڻ�������ʱ������תƽ�ƾ�����Ҫ�����ĸ�ʮ�������㣩
* @param[in]     inputs                      : ����ڻ������ⲿʱ�ı궨����
* @param[in]     constraintPoints            : �궨���ĸ�ʮ�ֽ�����ڻ���������ϵ�µ�����
* @param[out]    matrix                      : ������۵��־���
* @param[out]    error                       : ������
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ���������ϵ�µĵ�ת������������ϵ
* @param[in]     pose           : �����˵�ǰλ��
* @param[in]     inputPoint     : �������ϵ�µĵ�
* @param[in]     matrix         : �۵��־���calibrateEyeToHand/calibrateEyeInHand����õ�
* @param[out]    outPoint       : ���������������ϵ�µĵ�
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ���������ϵ�µ�����ת������������ϵ
* @param[in]     pose           : �����˵�ǰλ��
* @param[in]     inputVector    : �������ϵ�µ�����
* @param[in]     matrix         : �۵��־���calibrateEyeToHand/calibrateEyeInHand����õ�
* @param[out]    outVector      : ���������������ϵ�µ�����
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ���������ϵ�µ�λ��ת������������ϵ
* @param[in]     toolPose       : �����˵�ǰλ��
* @param[in]     poseInEye      : �������ϵ�µ�λ��
* @param[in]     matrix         : �۵��־���calibrateEyeToHand/calibrateEyeInHand����õ�
* @param[in]	 poseType		�����λ�˱�ʾ����
* @param[in]	 poseUnit		: �����̬��ʾ��λ�Ƕ�/����
* @param[out]    outPoseInHand  : ���λ��
* @return �ɹ�:SUCCESS, ʧ��:����������
* @~english
* @brief         transform point to the coordinate system of hand
* @param[in]     toolPose       : the pose of robot
* @param[in]     poseInEye      : the input point in eye
* @param[in]     matrix         : the matrix eye to hand, returned by calibrateEyeToHand/calibrateEyeInHand
* @param[in]	 poseType		��type of output pose
* @param[in]	 poseUnit		: unit of output direction(radian/degree)
* @param[out]    outPoseInHand  : the output pose in hand
* @return success:return SUCCESS, fail:other error code
**/
CS_API ERROR_CODE transformPoseFromEyeToHand(RobotPoseMatrix4f toolPose, RobotPoseMatrix4f poseInEye, HandEyeMatrix matrix,
											  RobotPoseType poseType, RobotPoseUnit poseUnit, RobotPose& outPoseInHand);

/**
* @~chinese
* @brief         ���������ϵ�µ�λ��ת������������ϵ
* @param[in]     toolPose       : �����˵�ǰλ��
* @param[in]     poseInEye      : �������ϵ�µ�λ��
* @param[in]     matrix         : �۵��־���calibrateEyeToHand/calibrateEyeInHand����õ�
* @param[out]    outMatrixInHand  : ���λ��
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ������������ϵ�µĵ�ת���������ϵ
* @param[in]     pose           : �����˵�ǰλ��
* @param[in]     inputPoint     : ����������ϵ�µĵ�
* @param[in]     matrix         : �۵��־���calibrateEyeToHand/calibrateEyeInHand����õ�
* @param[out]    outPoint       : ����������ϵ�µĵ�
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ������������ϵ�µ�����ת���������ϵ
* @param[in]     pose           : �����˵�ǰλ��
* @param[in]     inputVector    : ����������ϵ�µ�����
* @param[in]     matrix         : �۵��־���calibrateEyeToHand/calibrateEyeInHand����õ�
* @param[out]    outVector      : ���������������ϵ�µ�����
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         ͨ���������ͼƬ����ȡ��������������㵽��ά������
* @param[in]     camera                      : �����ӳɹ������ָ��
* @param[in]     leftPoints                  : �����ͼƬ����ȡ������������
* @param[in]     rightPoints                 : �����ͼƬ����ȡ������������
* @param[out]    points                      : �ؽ��������ά������
* @param[in]     type                        : ��������
* @return �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         �ؽ��궨������
* @param[in]     camera                      : �����ӳɹ������ָ��
* @param[in]     pairFrame                   : ��ʽ��STREAM_FORMAT_PAIR��֡����
* @param[out]    points                      : �ؽ��ı궨��ǵ����
* @param[in]     chessboardHorizontalPoints  : ����궨��ǵ���
* @param[in]     chessboardVerticalPoints    : ����궨��ǵ���
* @param[in]     type                        : ���߷���, @�μ� BASELINE_TYPE
* @return     �ɹ�:SUCCESS, ʧ��:����������
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
* @brief         �ؽ��궨������
* @param[in]     camera                      : �����ӳɹ������ָ��
* @param[in]     imageLeft                   : �����ͼ��
* @param[in]     imageRight                  : �����ͼ��
* @param[in]     width	                     : ͼ����
* @param[in]     height						 : ͼ��߶�
* @param[out]    points                      : �ؽ��ı궨��ǵ����
* @param[in]     chessboardHorizontalPoints  : ����궨��ǵ���
* @param[in]     chessboardVerticalPoints    : ����궨��ǵ���
* @param[in]     type                        : ���߷���, @�μ� BASELINE_TYPE
* @return     �ɹ�:SUCCESS, ʧ��:����������
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
