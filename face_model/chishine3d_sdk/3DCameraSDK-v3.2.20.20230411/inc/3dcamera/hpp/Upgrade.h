#ifndef UPGRADE_H_
#define UPGRADE_H_
/* Include the libailook C header files */
#include "hpp/Types.hpp"



#ifdef __cplusplus
extern "C" {
#endif

#ifndef HANDLE_DEF
#define HANDLE_DEF
	typedef void* HANDLE;
#endif

/**
* @~chinese
* @brief      ��������(�첽�ӿ�)
* @param[in]  cInfo				ָ����Ҫ�������豸��Ϣ�������ָ���򽫱����ÿ�
* @param[in]  upExeDir			ָ�������Ŀ�ִ���ļ�Ŀ¼���ڴ�Ŀ¼��Ҫ�ܹ��ҵ�up��up2��adb������ִ���ļ�
* @param[in]  upgradePackage		�������ı���·��
* @param[in]  upgradePackageMd5			����������md5ֵ��������֤���ļ���������
* @return     �ɹ�:�������, ʧ��:nullptr
* @~english
* @brief     upgrade device firmware,cannot terminate after startup
* @param[in]  cInfo				specify the device information to be upgraded.if not specified,set the variable to null
* @param[in]  upExeDir			specify the directory of executable file to be upgraded.in this directory,can find the up\up2\adb executable files.
* @param[in]  upgradePackage		: local path of upgrade firmware package
* @param[in]  upgradePackageMd5			��the md5 of upgradePackage,to check the package is ok.
* @return success:return SUCCESS, fail:other error code
**/
CS_API HANDLE upgradeCamera(CameraInfo cInfo,const char* upExeDir,const char* upgradePackage, const char* upgradePackageMd5);

/**
 * @~chinese
 * @brief      ��ȡ��ǰ��������(�첽�ӿ�)
 * @hUpgrade	���������ͨ��upgradeCamera����
 * @return     �ɹ�:[0,100],��ʾ���ȵİٷֱ�, ʧ��:0xff
 * @~english
 * @brief	get the progress of upgrade firmware
 * @hUpgrade	the upgrade handle,create by upgradeCamera.
 * @return  success:the value of [0,100],represents the percentage of progress, 
 *			fail:0xff
 **/
CS_API int getUpgradeCameraProgress(HANDLE hUpgrade);


 /**
 * @~chinese
 * @brief      ����������ͷ��������
 * @hUpgrade	���������ͨ��upgradeCamera����
 * @return     
 * @~english
 * @brief		finish the upgrading,release the handle 
 * @hUpgrade	the upgrade handle,create by upgradeCamera.
 * @return  
 **/
CS_API void releaseUpgradeCamera(HANDLE hUpgrade);

/**
 *		�ж��Ƿ�������״̬
 */
CS_API bool isInUsbUpgradeMode(OUT char acSerial[30],const char* upExeDir="./");


/**
*		��������ģʽ(recovery mode)
*@pcSerial		��Ҫ���������к�(��ǰ�ӿ��ڲ�û��ʹ��)
*/
CS_API bool enterRecoveryMode(const char* pcSerial,const char* upExeDir="./");

/**
*		leave recovery mode(enter normal mode)
*@cInfo	camera info.
*/
CS_API bool leaveRecoveryMode(CameraInfo cInfo,const char* upExeDir="./");


#ifdef __cplusplus
}
#endif


#endif
