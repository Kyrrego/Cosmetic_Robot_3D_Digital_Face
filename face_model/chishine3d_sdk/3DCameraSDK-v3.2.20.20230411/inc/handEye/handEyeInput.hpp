/*****************************************************************************
*  3DCamera SDK header
*
*
*  @file     HandEyeInput.hpp
*  @brief    3DCamera sdk header
*
*  @version  1.0
*  @date     2020 / 05 / 09
*
*****************************************************************************/
#ifndef __HANDEYEINPUT_HPP__
#define __HANDEYEINPUT_HPP__

#include <vector>
#include "hpp/APIExport.hpp"

namespace cs
{
/**
* \ingroup HandEye
* @{
*/

/**
* @~chinese
* @brief ö��: ��ǰλ�˷���ı�ʾ����
* @~english
* @brief enumeration: The type of direction
**/
typedef enum RobotPoseType
{
	POSE_TYPE_EULER_ZYZ = 0,	/**< @~chinese ŷ��ZYZ		@~english EULER ZYZ*/ 
	POSE_TYPE_EULER_XYZ = 1,	/**< @~chinese ŷ��XYZ		@~english EULER XYZ*/ 
	POSE_TYPE_EULER_ZYX = 2,	/**< @~chinese ŷ��ZYX		@~english EULER ZYX*/ 
	POSE_TYPE_RPY		= 3,	/**< @~chinese RPY			@~english RPY*/ 
	POSE_TYPE_QUATERNION = 4,	/**< @~chinese ��Ԫ����ʾ��	@~english Quaternion*/
	POSE_TYPE_XYZAB		= 5,	/**< @~chinese �����������	@~english used by 5-axis machine*/
	POSE_TYPE_ROTATE_VECTOR = 6,/**< @~chinese ��תʸ��		@~english rotate vector*/
    POSE_TYPE_EULER_ZXZ = 7,	/**< @~chinese ŷ��ZXZ		@~english EULER ZXZ*/
	POSE_TYPE_EULER_ZYX_PANASONIC = 8,	/**< @~chinese ���»�����ŷ��ZYX		@~english use for panasonic robot*/
}RobotPoseType;

/**
* @~chinese
* @brief ö��: ��ǰλ�˷���ı�ʾ��λ
* @~english
* @brief enumeration: The unit of direction
**/
typedef enum RobotPoseUnit
{
	POSE_UNIT_RADIAN = 0,	/**<@~chinese ����	@~english in radian */
	POSE_UNIT_DEGREE		/**<@~chinese �Ƕ�	@~english in degree */
}RobotPoseUnit;

/**
* @~chinese
* @brief ������λ��
* @~english
* @brief pose in hand
**/
typedef struct RobotPose
{
	float x;        /**<@~chinese ��λ����	@~english unit mm */
	float y;        /**<@~chinese ��λ����	@~english unit mm */
	float z;        /**<@~chinese ��λ����	@~english unit mm */
	float alfa;     /**<@~chinese ��̬��ʾԪ��1	@~english pose representation element 1 */
	float beta;     /**<@~chinese ��̬��ʾԪ��2	@~english pose representation element 2 */
	float gamma;    /**<@~chinese ��̬��ʾԪ��3	@~english pose representation element 3 */
	float theta;    /**<@~chinese ��̬��ʾԪ��4	@~english pose representation element 4 */
}RobotPose;

#ifndef POINT3F
#define POINT3F
typedef struct Point3f {
	float x;
	float y;
	float z;
}Point3f;
#endif

#ifndef POINT2F
#define POINT2F
typedef struct Point2f {
	float x;
	float y;
}Point2f;
#endif

#ifndef VECTOR3F
#define VECTOR3F
typedef struct Vector3f {
	float x;
	float y;
	float z;
}Vector3f;
#endif

class CS_API Matrix4f
{
public:
    Matrix4f();
    Matrix4f(float r00, float r01, float r02, float tx,
        float r10, float r11, float r12, float ty,
        float r20, float r21, float r22, float tz,
        float zero0, float zero1, float zero2, float one);
	virtual ~Matrix4f(){};
	float *data();

    float r00;
    float r01;
    float r02;
    float tx;
    float r10;
    float r11;
    float r12;
    float ty;
    float r20;
    float r21;
    float r22;
    float tz;
    float zero0;
    float zero1;
    float zero2;
    float one;
};
/*!\class RobotPoseMatrix4f
* @~chinese
* @brief ������λ�˵�4x4�����ʾ
* @~english
* @brief pose of robot in matrix 4x4
**/
class CS_API RobotPoseMatrix4f : public Matrix4f
{
public:
	RobotPoseMatrix4f();
	RobotPoseMatrix4f(float r00, float r01, float r02, float tx,
		float r10, float r11, float r12, float ty,
		float r20, float r21, float r22, float tz,
		float zero0, float zero1, float zero2, float one);
	virtual ~RobotPoseMatrix4f() {};
	/**
	* @~chinese
	* @brief      ͨ�������˵�ǰ��λ�˼�λ�˱�ʾ���͹���4x4����
	* @param[in]  pose				�����뵱ǰλ��
	* @param[in]  type				��λ�˱�ʾ����
	* @param[in]  unit				: λ�˱�ʾ�Ƕ�/����
	* @~english
	* @brief      Start stream and return frame by callback
	* @param[in]  pose				��input pose
	* @param[in]  type				��type of pose
	* @param[in]  unit				: unit of direction(radian/degree)
	**/
	RobotPoseMatrix4f(RobotPose pose, RobotPoseType type, RobotPoseUnit unit);
	
};

/**
* @~chinese
* @brief ���۱궨����
* @~english
* @brief eye to hand matrix
**/
class CS_API HandEyeMatrix : public Matrix4f
{
public:
	HandEyeMatrix();
	HandEyeMatrix(float r00, float r01, float r02, float tx,
		float r10, float r11, float r12, float ty,
		float r20, float r21, float r22, float tz,
		float zero0, float zero1, float zero2, float one);
	virtual ~HandEyeMatrix() {};

	/**
	* @~chinese
	* @brief      ���ļ��ж�ȡ���۱궨����
	* @param[in]  path				����ȡ�ļ�·��
	* @param[in]  userInfo			�������ļ��еĸ�����Ϣ
	* @param[in]  userInfoSize		�����渽����Ϣ���ڴ��ֽ���
	* @~english
	* @brief      Read the hand-eye calibration matrix from the file
	* @param[in]  path				��load file path
	* @param[in]  userInfo			��read the additional string from file
	* @param[in]  userInfoSize		��the size of memory holding additional information
	**/
	bool load(const char* path, char* userInfo, int userInfoSize);
	/**
	* @~chinese
	* @brief      �����۱궨���󱣴浽�ļ���
	* @param[in]  path				�������ļ�·��
	* @param[in]  userInfo			����Ҫ����ĸ�����Ϣ(�ַ���)
	* @~english
	* @brief      Save the hand-eye calibration matrix in the file
	* @param[in]  path				��save file path
	* @param[in]  userInfo			��additional information to save
	**/
	bool save(const char* path, const char* userInfo);
	
};

/*!\class HandEyeCalibrationInput
* @~chinese
* @brief ���۱궨������
* @~english
* @brief calibration input
**/
class CS_API HandEyeCalibrationInput
{
public:
	RobotPoseMatrix4f m_pose;
	std::vector<Point3f> m_points;
public:
	HandEyeCalibrationInput(HandEyeCalibrationInput&& other);

	HandEyeCalibrationInput& operator=(HandEyeCalibrationInput other);

	HandEyeCalibrationInput(const HandEyeCalibrationInput& other);

	~HandEyeCalibrationInput();
	/**
	* @~chinese
	* @brief      ͨ�������˵�ǰ��λ�˹������۱궨����
	* @param[in]  pose				: 4x4�����ʾ�ĵ�ǰλ��
	* @param[in]  points			: �������ϵ�±궨��ǵ�����
	* @~english
	* @brief      construction HandEyeCalibrationInput from current hand pose and chessboard points in eye
	* @param[in]  pose				: current hand pose in 4x4 matrix
	* @param[in]  points			: chessboard points in eye
	**/
	HandEyeCalibrationInput(RobotPoseMatrix4f pose, std::vector<Point3f>& points);
};
/*@} */
}
#endif
