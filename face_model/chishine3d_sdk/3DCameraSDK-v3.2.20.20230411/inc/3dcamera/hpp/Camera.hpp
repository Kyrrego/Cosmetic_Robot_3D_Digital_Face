 /*****************************************************************************
*  3DCamera SDK header
*
*
*  @file     Camera.hpp
*  @brief    3DCamera sdk header
*
*  @version  1.0
*  @date     2019 / 08 / 17
*
*****************************************************************************/
#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <vector>
#include <queue>
#include <memory>
#include <string>
#include "Frame.hpp"
#include "hpp/APIExport.hpp"

namespace cs
{
class ICamera;

/**
* @~chinese
* \defgroup Camera �������
* @brief �ṩ������ӣ������������������ԣ���ȡ�����ȹ���
* @{
* @~english
* \defgroup Camera Camera operations
* @brief Provide functions for camera connection, start stream, set properties, read parameters and other functions
* @{
*/

/**
* @~chinese
* @brief ���֡���ݻص�����
* @~english
* @brief callback of get frame
*/
typedef void (*FrameCallback)(IFramePtr frame, void *usrData);

/**
* @~chinese
* @brief �������Ĺ���ָ��
* @~english
* @brief the shared pointer of camera
*/
typedef std::shared_ptr<ICamera> ICameraPtr;
	
/*!\class ICamera
* @~chinese
* @brief ����ӿ�
* @~english
* @brief Camera interface
*/
class CS_API ICamera
{
public:

	virtual ~ICamera() {};

	/**
	* @~chinese
	* @brief     ��������һ�����
	* @return    �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief     Connect to any camera
	* @return    success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE connect() = 0;
	
	/**
	* @~chinese
	* @brief     ����ָ����Ϣ�����
	* @param[in] info			:ָ���������Ϣ����ͨ��ISystem::queryCameras�ӿڻ����Ϣ�б�
	* @return    �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief     Connect to the specified camera
	* @param[in] info			:the information of specified camera��you can get the infomations by ISystem::queryCameras
	* @return    success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE connect(CameraInfo info) = 0;

    /**
	* @~chinese
	* @brief	  ��ȡ��ǰ�����������Ϣ���������кţ��汾��Ϣ����ʶId
	* @param[out] info			:���շ��ص������Ϣ
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief	  Get the information of 3DCamera,include serial number, version, unique id
	* @param[out] info			:information of connected camera
	* @return     success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE getInfo(CameraInfo &info) = 0;

	/** 
	* @~chinese 
	* @brief	  �Ͽ��������
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english 
	* @brief	  Disconnect to camera
	* @return     success:return SUCCESS, fail:other error code
	*/
    virtual ERROR_CODE disconnect() = 0;
    
    /**
	* @~chinese
	* @brief      ��ȡָ�����͵���������֧�ֵ�����ʽ��Ϣ�б�
	* @param[in]  streamType		��������
	* @param[out] streamInfos		�����ص�����ʽ��Ϣ�б�
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english 
	* @brief      Get all supported stream informations of the specified stream 
	* @param[in]  streamType		��the type of stream
	* @param[out] streamInfos		��return the list of supported stream informations
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE getStreamInfos(STREAM_TYPE streamType, std::vector<StreamInfo> &streamInfos) = 0;

    /**
	* @~chinese
	* @brief      ����������ͨ���ص���������֡����
	* @param[in]  streamType		����Ҫ�򿪵������ͣ� ��STREAM_TYPE
	* @param[in]  info				����Ҫ�򿪵�����ʽ��Ϣ, ����getStreamInfos����
	* @param[in]  callback          : ����֡���ݵĻص�����
	* @param[in]  userData          : �û�����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Start stream and return frame by callback
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[out] info      		��stream information, returned by getStreamInfos
	* @param[in]  callback          : frame callback
	* @param[in]  userData          : the user data
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE startStream(STREAM_TYPE streamType, StreamInfo info, FrameCallback callback, void *userData) = 0;

	/**
	* @~chinese
	* @brief      ����������ͨ��getFrame������ȡ֡����
	* @param[in]  streamType		����Ҫ�򿪵������ͣ� ��STREAM_TYPE
	* @param[in]  info				����Ҫ�򿪵�����ʽ��Ϣ, ����getStreamInfos����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Start stream without callback, you should get frame by getFrame
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[out] info      		��stream information, returned by getStreamInfos
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE startStream(STREAM_TYPE streamType, StreamInfo info) = 0;

    /**
	* @~chinese
	* @brief      ֹͣ������
	* @param[in]  streamType		����Ҫֹͣ�������ͣ� ��STREAM_TYPE
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Stop stream
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE stopStream(STREAM_TYPE streamType) = 0;

	/**
	* @~chinese
	* @brief      ��ͣ������
	* @param[in]  streamType		����Ҫ��ͣ�������ͣ� ��STREAM_TYPE
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Pause stream
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE pauseStream(STREAM_TYPE streamType) = 0;

	/**
	* @~chinese
	* @brief      �ָ�������
	* @param[in]  streamType		����Ҫֹͣ�������ͣ� ��STREAM_TYPE
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Resume stream
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE resumeStream(STREAM_TYPE streamType) = 0;

	/**
	* @~chinese
	* @brief      �������Ļص�ͨ��
	* @param[in]  streamType		����Ҫ�򿪵������ͣ� ��STREAM_TYPE
	* @param[in]  callback          : ����֡���ݵĻص�����
	* @param[in]  userData          : �û�����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      setting the stream callback
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[in]  callback          : frame callback
	* @param[in]  userData          : the user data
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE setStreamCallback(STREAM_TYPE streamType, FrameCallback callback, void* userData) = 0;

	/**
	* @~chinese
	* @brief      ������ȡ��ǰ�������֡����
	* @param[in]  streamType		����Ҫ��ȡ��������
	* @param[out] frame				������֡����
	* @param[in]  timeout_ms		����ʱʱ�䣬��λΪ����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get frame manually
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[out] frame				��return the captured frame
	* @param[in]  timeout_ms		��timeout in millisecond
	* @return success:return SUCCESS, fail:other error code
	**/   
    virtual ERROR_CODE getFrame(STREAM_TYPE streamType, IFramePtr &frame, int timeout_ms = 5000) = 0;

	/**
	* @~chinese
	* @brief      ��ȡ�ɶԵ���Ⱥ�RGB֡
	* @param[out] depthFrame		���������֡
	* @param[out] rgbFrame			: ����RGB֡
	* @param[in]  timeout_ms		����ʱʱ�䣬��λΪ����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the paired frame of depth and rgb 
	* @param[in]  depthFrame		��return the paired depth frame
	* @param[out] frame				��return the paired rgb frame 
	* @param[in]  timeout_ms		��timeout in millisecond
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE getPairedFrame(IFramePtr &depthFrame, IFramePtr &rgbFrame, int timeout_ms = 5000) = 0;

	/**
	* @~chinese
	* @brief      ����ģʽ�´���N֡����ʱֻ֧��1֡��
	* @param[in]  count				������֡��
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Trigger N frames in software trigger mode (only one frame is supported temporarily)
	* @param[in]  count				��the count of trigger times
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE softTrigger(int count = 1) = 0;

	/**
	* @~chinese
	* @brief      ��ȡָ������ָ�����Է�Χ
	* @param[in]  streamType		��ָ��������������
	* @param[in]  propertyType		����������
	* @param[out] min				�����Ե���Сֵ
	* @param[out] max				�����Ե����ֵ
	* @param[out] step				�����Ե���ʱ�Ľ�����ڲ���
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the value range of property
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[in]  propertyType		��property type, @see PROPERTY_TYPE
	* @param[out] min				��the minimum of the property
	* @param[out] max				��the minimum of the property
	* @param[out] step				��the step of the property
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE getPropertyRange(STREAM_TYPE streamType, PROPERTY_TYPE propertyType, float &min, float &max, float &step) = 0;	

	/**
	* @~chinese
	* @brief      ��ȡָ����������ֵ
	* @param[in]  streamType		��ָ��������������
	* @param[in]  propertyType		����������
	* @param[out] value				�����Ե�ǰֵ
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the value of property
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[in]  propertyType		��property type, @see PROPERTY_TYPE
	* @param[out] value				��the value of the property
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE getProperty(STREAM_TYPE streamType, PROPERTY_TYPE propertyType, float &value) = 0;

	/**
	* @~chinese
	* @brief      �޸�ָ����������ֵ
	* @param[in]  streamType		��ָ��������������
	* @param[in]  propertyType		����������
	* @param[in]  value				����Ҫ���õ�����ֵ
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Set the value of property
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[in]  propertyType		��property type, @see PROPERTY_TYPE
	* @param[in]  value				��the value of property
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE setProperty(STREAM_TYPE streamType, PROPERTY_TYPE propertyType, float value) = 0;	

	/**
	* @~chinese
	* @brief      �޸���չ����ֵ
	* @param[in]  propertyType		����������
	* @param[in]  value				����Ҫ���õ�����ֵ
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Set the value of extensional property
	* @param[in]  propertyType		��property type, @see PROPERTY_TYPE_EXTENSION
	* @param[in]  value				��the value of extensional property
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE setPropertyExtension(PROPERTY_TYPE_EXTENSION propertyType, PropertyExtension value) = 0;

	/**
	* @~chinese
	* @brief      ��ȡ��չ���Եĵ�ǰֵ
	* @param[in]  propertyType		����������
	* @param[out] value				�����ص�ֵ
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the value of extensional property
	* @param[in]  propertyType		��property type, @see PROPERTY_TYPE_EXTENSION
	* @param[out] value				��return the value of extensional property
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE getPropertyExtension(PROPERTY_TYPE_EXTENSION propertyType, PropertyExtension &value) = 0;

	/**
	* @~chinese
	* @brief      ��ȡָ���������������ڲ�
	* @param[in]  streamType		��ָ��������������
	* @param[out] intrinsics		�������ڲ�
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the intrinsic of specified stream
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[out] intrinsics		��return the intrinsic of specified stream
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE getIntrinsics(STREAM_TYPE streamType, Intrinsics &intrinsics) = 0;
    
	/**
	* @~chinese
	* @brief      ��ȡ���������RGB������תƽ�Ʋ���
	* @param[out] extrinsics		���������
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the extrinsics from depth stream to RGB stream
	* @param[out] extrinsics		��return the extrinsics
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE getExtrinsics(Extrinsics &extrinsics) = 0;
    
	/**
	* @~chinese
	* @brief      ��ȡָ�������������Ļ������
	* @param[in]  streamType		��ָ��������������
	* @param[out] distort			�������ڲ�
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the distort of the specified stream
	* @param[in]  streamType		��stream type, @see STREAM_TYPE
	* @param[out] distort			��return the distort of the specified stream
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE getDistort(STREAM_TYPE streamType, Distort &distort) = 0;

	/**
	* @~chinese
	* @brief	  �������
	* @return �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief	  reboot camera
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE restart() = 0;

	/**
	* @~chinese
	* @brief      д���û��Զ������ݣ����ȱ���ҪС��1024�ֽ�
	* @param[in]  userData			��д������ָ��
	* @param[in]  length			��д�����ݳ���
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Write the user defined data to camera, at most 1024 bytes
	* @param[in]  userData			��the pointer of user defined data
	* @param[in]  length			��the length of user defined data
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE setUserData(char *userData, int length) = 0;

	/**
	* @~chinese
	* @brief      ��ȡ�û��Զ������ݣ����ȱ���ҪС��1024�ֽ�
	* @param[in]  userData			��������������ָ��
	* @param[in out] length			������ΪuserData��Size������Ϊ���ݳ���
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Write the user defined data to camera, at most 1024 bytes
	* @param[in]  userData			��the pointer of buffer to save user defined data
	* @param[in]  length			��size of input paramer 'userData',return the length of user defined data
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE getUserData(char *userData, int &inputBufSizeAndOutLen) = 0;

	/**
	 * @~chinese
	 * @brief      ��ʼ������
	 * @code		��ʼ�����к�
	 * @return     �ɹ�:SUCCESS, ʧ��:����������
	 * @~english	
	 * @brief		initializate the driver
	 * @code	the initializate code of driver
	 * @return  success:return SUCCESS, fail:other error code
	 */
	virtual ERROR_CODE initDriver(const char* code) = 0;

    /**
    * @~chinese
    * @brief      �ж�����Ƿ�֧��ָ��������
    * @param[in]  streamType		��������
    * @param[out] support		    �������жϽ��
    * @return     �ɹ�:SUCCESS, ʧ��:����������
    * @~english
    * @brief      judge whether the camera supports the specified type of stream
    * @param[in]  streamType		��the type of stream
    * @param[out] support		    ��return the judgment result
    * @return success:return SUCCESS, fail:other error code
    **/
    virtual ERROR_CODE isStreamSupport(STREAM_TYPE streamType, bool& support) = 0;

	/**
	* @~chinese
	* @brief          �������ؽ�
	* @param[in]      frame		            ��������(��֧�֣�Z16Y8Y8)
	* @param[in/out]  leftFeaturePoints		������������㼯��, ���ƥ���������㼯��
	* @param[in/out]  rightFeaturePoints    ������������㼯�ϣ����ƥ���������㼯��
	* @param[out]     reconstructPoints	    ���ؽ������㼯��
	* @return         �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief          Feature point reconstruction
	* @param[in]      frame		            ��stream data(only support: Z16Y8Y8)
	* @param[in/out]  leftFeaturePoints		��Left camera feature point collection�� output the matched feature points
	* @param[in/out]  rightFeaturePoints    ��Right camera feature point collection, output the matched feature points
	* @param[out]     reconstructPoints     ��return the reconstruct point collection
	* @return         success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE featureReconstruct(IFramePtr frame, std::vector<Point2f>& leftFeaturePoints, std::vector<Point2f>& rightFeaturePoints, std::vector<Point3f>& reconstructPoints) = 0;

	/**
	* @~chinese
	* @brief          �������ؽ�
	* @param[in]      frame		            ��������(��֧�֣�Z16Y8Y8)
	* @param[in/out]  leftFeaturePoints		������������㼯��, ���ƥ���������㼯��
	* @param[in/out]  rightFeaturePoints    ������������㼯�ϣ����ƥ���������㼯��
	* @param[in]      confidenceThreshold   �����Ŷ���ֵ, ֵ��[0,1], ���Ŷ�С��confidenceThreshold��ƥ��������ᱻ�Ƴ�
	* @param[out]     reconstructPoints	    ���ؽ������㼯��
	* @return         �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief          Feature point reconstruction
	* @param[in]      frame		            ��stream data(only support: Z16Y8Y8)
	* @param[in/out]  leftFeaturePoints		��Left camera feature point collection�� output the matched feature points
	* @param[in/out]  rightFeaturePoints    ��Right camera feature point collection, output the matched feature points
	* @param[in]      confidenceThreshold   ��Confidence threshold, value range: [0,1], matching feature points smaller than confidenceThreshold will be removed
	* @param[out]     reconstructPoints     ��return the reconstruct point collection
	* @return         success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE featureReconstruct(IFramePtr frame, std::vector<Point2f>& leftFeaturePoints, std::vector<Point2f>& rightFeaturePoints, float confidenceThreshold
		, std::vector<Point3f>& reconstructPoints) = 0;

	/**
	* @~chinese
	* @brief      ƥ����������ؽ�
	* @param[in]  frame		                    �������ݣ���֧�֣�Z16Y8Y8��
	* @param[in]  matchedLeftFeaturePoints		��ƥ�������������㼯��
	* @param[in]  matchedRightFeaturePoints     ��ƥ�������������㼯��
	* @param[out] reconstructPoints	            ���ؽ������㼯��
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Matched feature point reconstruction
	* @param[in]  frame		                    ��stream data(only support: Z16Y8Y8)
	* @param[in]  matchedLeftFeaturePoints		��Matched left camera feature point collection
	* @param[in]  matchedRightFeaturePoints     ��Matched right camera feature point collection
	* @param[out] reconstructPoints             ��return the reconstruct point collection
	* @return     success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE matchedFeatureReconstruct(IFramePtr frame, const std::vector<Point2f>& matchedLeftFeaturePoints, const std::vector<Point2f>& matchedRightFeaturePoints
		, std::vector<Point3f>& reconstructPoints) = 0;

	/**
	* @~chinese
	* @brief      ��ȡ͸�ӱ任���� (Q ����)
	* @param[out] matrix		��͸�ӱ任����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the perspective transformation matrix (Q matrix)
	* @param[out] matrix		��return the perspective transformation matrix
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE getPerspectiveTransformationMatrix(PerspectiveTransformationMatrix& matrix) = 0;

	/**
	* @~chinese
	* @brief      ����IMU�궨
	* @param[in] imuCalibrationPlane		��ָ��IMU�궨ƽ��
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      start imu calibration
	* @param[in] imuCalibrationPlane		��specifi plane of imu calibration
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE startIMUCalibration(IMU_CALIBRATTION_PLANE imuCalibrationPlane) = 0;

	/**
	* @~chinese
	* @brief      ��ȡimu�궨״̬
	* @param[in] imuCalibrationPlane		��ָ��IMU�궨ƽ��
	* @param[out] imuCalibrationState		���궨״̬
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get the perspective transformation matrix (Q matrix)
	* @param[in] imuCalibrationPlane		��specifi plane of imu calibration
	* @param[out] imuCalibrationState		��state of imu calibration
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE getIMUCalibrationState(IMU_CALIBRATTION_PLANE imuCalibrationPlane, IMU_CALIBRATTION_STATE& imuCalibrationState) = 0;

	/**
	* @~chinese
	* @brief      ֹͣIMU�궨
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      stop imu calibration
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE stopIMUCalibration() = 0;

	/**
	* @~chinese
	* @brief      ����IMU�궨����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Set IMU calibration date
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE setIMUCalibrationDate(const std::string& calibrationDate) = 0;

	/**
	* @~chinese
	* @brief      ��ȡIMU�궨����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Get IMU calibration date
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE getIMUCalibrationDate(std::string& calibrationDate) = 0;
};

CS_API ICameraPtr getCameraPtr();

CS_API ICamera* createCamera();

CS_API void freeCamera(ICamera* pobjIC);

/*@} */
}
#endif