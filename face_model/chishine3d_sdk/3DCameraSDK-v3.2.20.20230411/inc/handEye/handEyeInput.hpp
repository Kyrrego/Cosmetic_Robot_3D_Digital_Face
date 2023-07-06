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
* @brief 枚举: 当前位姿方向的表示方法
* @~english
* @brief enumeration: The type of direction
**/
typedef enum RobotPoseType
{
	POSE_TYPE_EULER_ZYZ = 0,	/**< @~chinese 欧拉ZYZ		@~english EULER ZYZ*/ 
	POSE_TYPE_EULER_XYZ = 1,	/**< @~chinese 欧拉XYZ		@~english EULER XYZ*/ 
	POSE_TYPE_EULER_ZYX = 2,	/**< @~chinese 欧拉ZYX		@~english EULER ZYX*/ 
	POSE_TYPE_RPY		= 3,	/**< @~chinese RPY			@~english RPY*/ 
	POSE_TYPE_QUATERNION = 4,	/**< @~chinese 四元数表示法	@~english Quaternion*/
	POSE_TYPE_XYZAB		= 5,	/**< @~chinese 用于五轴机床	@~english used by 5-axis machine*/
	POSE_TYPE_ROTATE_VECTOR = 6,/**< @~chinese 旋转矢量		@~english rotate vector*/
    POSE_TYPE_EULER_ZXZ = 7,	/**< @~chinese 欧拉ZXZ		@~english EULER ZXZ*/
	POSE_TYPE_EULER_ZYX_PANASONIC = 8,	/**< @~chinese 松下机器人欧拉ZYX		@~english use for panasonic robot*/
}RobotPoseType;

/**
* @~chinese
* @brief 枚举: 当前位姿方向的表示单位
* @~english
* @brief enumeration: The unit of direction
**/
typedef enum RobotPoseUnit
{
	POSE_UNIT_RADIAN = 0,	/**<@~chinese 弧度	@~english in radian */
	POSE_UNIT_DEGREE		/**<@~chinese 角度	@~english in degree */
}RobotPoseUnit;

/**
* @~chinese
* @brief 机器人位姿
* @~english
* @brief pose in hand
**/
typedef struct RobotPose
{
	float x;        /**<@~chinese 单位毫米	@~english unit mm */
	float y;        /**<@~chinese 单位毫米	@~english unit mm */
	float z;        /**<@~chinese 单位毫米	@~english unit mm */
	float alfa;     /**<@~chinese 姿态表示元素1	@~english pose representation element 1 */
	float beta;     /**<@~chinese 姿态表示元素2	@~english pose representation element 2 */
	float gamma;    /**<@~chinese 姿态表示元素3	@~english pose representation element 3 */
	float theta;    /**<@~chinese 姿态表示元素4	@~english pose representation element 4 */
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
* @brief 机器人位姿的4x4矩阵表示
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
	* @brief      通过机器人当前的位姿及位姿表示类型构造4x4矩阵
	* @param[in]  pose				：输入当前位姿
	* @param[in]  type				：位姿表示类型
	* @param[in]  unit				: 位姿表示角度/弧度
	* @~english
	* @brief      Start stream and return frame by callback
	* @param[in]  pose				：input pose
	* @param[in]  type				：type of pose
	* @param[in]  unit				: unit of direction(radian/degree)
	**/
	RobotPoseMatrix4f(RobotPose pose, RobotPoseType type, RobotPoseUnit unit);
	
};

/**
* @~chinese
* @brief 手眼标定矩阵
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
	* @brief      从文件中读取手眼标定矩阵
	* @param[in]  path				：读取文件路径
	* @param[in]  userInfo			：传出文件中的附加信息
	* @param[in]  userInfoSize		：保存附加信息的内存字节数
	* @~english
	* @brief      Read the hand-eye calibration matrix from the file
	* @param[in]  path				：load file path
	* @param[in]  userInfo			：read the additional string from file
	* @param[in]  userInfoSize		：the size of memory holding additional information
	**/
	bool load(const char* path, char* userInfo, int userInfoSize);
	/**
	* @~chinese
	* @brief      将手眼标定矩阵保存到文件中
	* @param[in]  path				：保存文件路径
	* @param[in]  userInfo			：需要保存的附加信息(字符串)
	* @~english
	* @brief      Save the hand-eye calibration matrix in the file
	* @param[in]  path				：save file path
	* @param[in]  userInfo			：additional information to save
	**/
	bool save(const char* path, const char* userInfo);
	
};

/*!\class HandEyeCalibrationInput
* @~chinese
* @brief 手眼标定输入类
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
	* @brief      通过机器人当前的位姿构造手眼标定输入
	* @param[in]  pose				: 4x4矩阵表示的当前位姿
	* @param[in]  points			: 相机坐标系下标定板角点坐标
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
