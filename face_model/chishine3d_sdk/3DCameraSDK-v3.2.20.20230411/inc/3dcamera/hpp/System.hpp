 /*****************************************************************************
*  3DCamera SDK header
*
*
*  @file     System.hpp
*  @brief    3DCamera sdk header
*
*  @version  1.0
*  @date     2019 / 08 / 17
*
*****************************************************************************/
#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <vector>
#include <memory>
#include "Types.hpp"
#include "hpp/APIExport.hpp"
#include "hpp/Camera.hpp"

namespace cs
{
class ISystem;

/**
* @~chinese
* \defgroup System ����������
* @brief ���������������������б�䶯
* @{
* @~english
* \defgroup System Camera monitor
* @brief Discover camera, monitor camera change
* @{
*/

/** @brief camera state change callback */
typedef void (*CameraChangeCallback)(std::vector<CameraInfo>& addedCameras, std::vector<CameraInfo>& removedCameras, void * userData);

/**
* @~chinese
* \defgroup System ����������
* @brief �ϱ����������Ϣͨ��
* @param[in]	jsonData	�ϱ����ݣ�json���ݸ�ʽ
* @param[in]	iDataLen	json���ݳ���
* @param[in]	userData	�ص��û����ݣ������ûص�ʱ����
* @{
* @~english
* \defgroup System Camera monitor
* @brief reporting channel of camera alarm informattion
* @param[in]	jsonData	report data,orgainze the data in json form
* @param[in]	iDataLen	length of report data content
* @param[in]	userData	context parameter of callback,which is the context passed in when setting
* @{
*/

/** @brief camera state change callback */
typedef void(*CameraAlarmCallback)(const char* jsonData,int iDataLen, void * userData);

/**
* @~chinese
* @brief     ISystem�����ָ�����Ͷ���
* @~english
* @brief     ISytem object point type define
**/
typedef std::shared_ptr<ISystem> ISystemPtr;

/*!\class ISystem
* @~chinese
* @brief System�ӿڳ�����
* @~english 
* @brief System interface
**/
class CS_API ISystem
{
public:

	virtual ~ISystem() {};

	/**
	* @~chinese
	* @brief      ��ѯ��ǰ�ѽ�������豸
	* @param[out] cameras �ѽ�������豸��Ϣ�б�
	* @param[in]  timeout	��ʱʱ��
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Query valid 3d cameras
	* @param[out] cameras		    :return valid 3d cameras
	* @param[in]	timeout			:timeout in ms
	* @return success:return SUCCESS, fail:other error code
	**/
    virtual ERROR_CODE queryCameras(std::vector<CameraInfo> &cameras,int timeout=0) = 0;

	/**
	* @~chinese
	* @brief      �����������״̬�䶯�ص�
	* @param[in]  callback		�䶯�ص�����
	* @param[in]  userData		�ص������û�����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Set camera state change callback
	* @param[in]  callback		camera state change callback
	* @param[in]  userData		pointer of user data
	* @return success:return SUCCESS, fail:other error code
	**/ 
    virtual ERROR_CODE setCameraChangeCallback(CameraChangeCallback callback, void *userData) = 0;

	/**
	* @~chinese
	* @brief      �����������ص�����
	* @param[in]  callback		����ص�����
	* @param[in]  userData		�ص������û�����
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      Set camera alarm reporting channel
	* @param[in]  callback		report alarm callback
	* @param[in]  userData		pointer of user data
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE setCameraAlarmCallback(CameraAlarmCallback callback, void *userData) = 0;

	/**
	* @~chinese
	* @brief      ����һ��usb���ӵ�����ļ�������,��׿�Խӻ�ʹ��
	* @param[in]  iFd		�ļ�������
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief     add a usb camera fd,used in android.
	* @param[in]  iFd		usb fd
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE addUsbCameraFd(int iFd) = 0;

	/**
	* @~chinese
	* @brief      ɾ��һ��usb���ӵ�����ļ�������,��׿�Խӻ�ʹ��
	* @param[in]  iFd		�ļ�������
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief     remove a usb camera fd,used in android.
	* @param[in]  iFd		usb fd
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE removeUsbCameraFd(int iFd) = 0;

	/**
	* @~chinese
	* @brief      ���緽ʽ̽�����,��׿�Խӻ�ʹ��
	* @param[in]  emPT		̽��״̬
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	* @~english
	* @brief      stop net probe,used in android.
	* @param[in]  emPT       probe state
	* @return success:return SUCCESS, fail:other error code
	**/
	virtual ERROR_CODE netProbeCtrl(ProbeType emPT) = 0;

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
	* @brief      ��ȡ���������ָ��
	* @return     ���������ָ��
	* @~english
	* @brief		get the shared pointer of camera.
	* @return  shared pointer of camera.
	*/
	virtual ICameraPtr getCameraPtr() = 0;
};

/**
* @~chinese
* @brief     ��ȡSystem��������ָ��
* @~english
* @brief     Get System object smart point
**/
CS_API std::shared_ptr<ISystem> getSystemPtr();

/**
* @~chinese
* @brief     ��ȡ����豸����״̬
* @~english
* @brief     judge whether the camera is connected.
**/
CS_API CAMERA_STATUS getCameraStatus(const char* pcSerial);

/**
* @~chinese
* @brief     ��ȡSDK�汾
* @~english
* @brief     Get SDK verison
**/
CS_API ERROR_CODE getSdkVersion(CS_SDK_VERSION** ppCsSdkVersion);

/**
* @~chinese
* @brief     ����SDK��־��������Ϣ
* @~english
* @brief     Set SDK server infomation
**/
CS_API void setSdkLogServerInfo(const char* logServerIp, unsigned short wLogServerPort);

/**
* @~chinese
* @brief     ����SDK��UVC�Ƿ����
* @~english
* @brief     Set SDK libuvc enable
**/
CS_API void setSdkEnableLibuvc(bool isEnableLibuvc);

/**
* @~chinese
* @brief     ����SDK�������Ƿ����
* @~english
* @brief     Set SDK networking enable
**/
CS_API void setSdkEnableNetworking(bool isEnableNetWorking);

/**
* @~chinese
* @brief     ������־�ļ�����·��
* @~english
* @brief     Set log file save path
**/
CS_API void setLogSavePath(const char* savePath);

/**
* @~chinese
* @brief     ��ȡ��־�ļ�����·��
* @~english
* @brief     Get log file save path
**/
CS_API const char* getLogSavePath();

/**
* @~chinese
* @brief     ��־����
* @~english
* @brief     Log enable
**/
CS_API void enableLoging(bool enableLoging);

/**
* @~chinese
* @brief     ͨ��SN��ȡ�������
* @~english
* @brief     Get camera type by SN
**/
CS_API CameraType getCameraTypeBySN(const char* sn);

/**
* @~chinese
* @brief     ͨ��������ͻ�ȡ����
* @~english
* @brief     get camera type name by cameraType
**/
CS_API const char* getCameraTypeName(CameraType tCt);

/**
* @~chinese
* @brief     ���繦�ܿ���
* @~english
* @brief     ���繦�ܿ���
**/
CS_API void setEnableNetworking(bool bEnable);
CS_API bool getEnableNetworking();

/**
*		get error string
*/
CS_API const char* getCameraErrorString(ERROR_CODE code);


/**
*   set check inited enable or not
*/
CS_API void setCheckedCameraInited(bool enable);

/*
*   set check inited state
*/
CS_API bool getCheckedCameraInited();

}

#endif
