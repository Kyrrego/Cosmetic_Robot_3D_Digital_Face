#ifndef LIB_3DCAMERA_CAMERA_H
#define LIB_3DCAMERA_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../hpp/Types.hpp"
#include "types.h"

	/** @brief frame callback */
	typedef void(*CFrameCallback)(CFrame *frame, void *usrData);

/**
* Get support stream info list of connected camera
*\param[in] camera			Handle of connected camera
*\param[out] infolist		Return pointer of stream info list
*\param[out] count			Return count of stream info list
*/
	CS_API StreamInfo* cameraCreateStreamInfoList(const CCamera* camera, STREAM_TYPE type, int* count);

/**
* Delete support stream info list of connected camera
*\param[in] infolist	Pointer of stream info list
*/
	CS_API void cameraDeleteStreamInfoList(StreamInfo* infolist);

/**
* Start the stream streaming 
*/
	CS_API CStream* cameraStartStream(const CCamera* camera, STREAM_TYPE type, const StreamInfo info, CFrameCallback on_frame, void* user);

/**
* Stop the stream streaming.
* The stream stops delivering samples to the attached computer vision modules and processing blocks, stops the device streaming
* and releases the device resources used by the stream. It is the application's responsibility to release any frame reference it owns.
* The method takes effect only after \c start() was called, otherwise an exception is raised.
* \param[in] sp  stream
*/
	CS_API void cameraStopStream(CStream* sp);

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
	CS_API ERROR_CODE cameraPauseStream(CStream* sp);

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
	CS_API ERROR_CODE cameraResumeStream(CStream* sp);

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
	CS_API ERROR_CODE camerasetStreamCallback(CStream* sp, CFrameCallback on_frame, void* user);

/**
* @~chinese
* @brief      ������ȡ��ǰ�������֡����
* @param[in]  streamType		����Ҫ��ȡ��������
* @param[out] frame				������֡����
* @param[in]  timeout_ms		����ʱʱ�䣬��λΪ����
* @return     �ɹ�:SUCCESS, ʧ��:����������
* @notes		��ȡ��frame����ͨ��cameraReleaseFrame�ͷ�
* @~english
* @brief      Get frame manually
* @param[in]  streamType		��stream type, @see STREAM_TYPE
* @param[out] frame				��return the captured frame
* @param[in]  timeout_ms		��timeout in millisecond
* @return success:return SUCCESS, fail:other error code
* @notes	the got frame must be release by cameraReleaseFrame;
**/
	CS_API ERROR_CODE cameraGetFrame(CStream* sp, CFrame* &frame, int timeout_ms/* = 5000*/);

/**
* @~chinese
* @brief      ��ȡ�ɶԵ���Ⱥ�RGB֡
* @param[out] depthFrame		���������֡
* @param[out] rgbFrame			: ����RGB֡
* @param[in]  timeout_ms		����ʱʱ�䣬��λΪ����
* @return     �ɹ�:SUCCESS, ʧ��:����������
* @notes		��ȡ��frame����ͨ��cameraReleaseFrame�ͷ�
* @~english
* @brief      Get the paired frame of depth and rgb
* @param[in]  depthFrame		��return the paired depth frame
* @param[out] frame				��return the paired rgb frame
* @param[in]  timeout_ms		��timeout in millisecond
* @return success:return SUCCESS, fail:other error code
* @notes	the got frame must be release by cameraReleaseFrame;
**/
	CS_API ERROR_CODE cameraGetPairedFrame(CStream* sp, CFrame* &depthFrame, CFrame* &rgbFrame, int timeout_ms /*= 5000*/);

	/**
	* Releases the frame handle
	* \param[in] frame handle returned from a callback
	*/
	CS_API ERROR_CODE cameraReleaseFrame(CStream* sp, CFrame* frame);

	CS_API ERROR_CODE cameraSoftwareTrigger(const CCamera* device, int count);

	CS_API ERROR_CODE cameraGetPropertyRange(const CCamera* device, STREAM_TYPE type, PROPERTY_TYPE property, float* min, float* max, float* step);

	CS_API ERROR_CODE cameraGetProperty(const CCamera* device, STREAM_TYPE type, PROPERTY_TYPE p, float* value);

	CS_API ERROR_CODE cameraSetProperty(const CCamera* device, STREAM_TYPE type, PROPERTY_TYPE p, float value);


	CS_API ERROR_CODE cameraGetPropertyExtension(const CCamera* device, PROPERTY_TYPE_EXTENSION property, PropertyExtension* value);

	CS_API ERROR_CODE cameraSetPropertyExtension(const CCamera* device, PROPERTY_TYPE_EXTENSION property, PropertyExtension value);

	CS_API ERROR_CODE cameraGetStreamIntrinsics(const CCamera* device, STREAM_TYPE type, Intrinsics *intr);

	CS_API ERROR_CODE cameraGetStreamExtrinsics(const CCamera* device, Extrinsics *extr);

	CS_API ERROR_CODE cameraGetStreamDistort(const CCamera* device, STREAM_TYPE type, Distort *distort);

	/**
	* Send hardware reset request to the camera.
	*\param[in] camera			Handle of connected camera
	*/
	CS_API ERROR_CODE cameraReset(const CCamera* camera);

	CS_API ERROR_CODE cameraSetUserData(const CCamera* camera, char *userData, int length);

	CS_API ERROR_CODE cameraGetUserData(const CCamera* camera, char *userData, int *length);

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
	CS_API ERROR_CODE cameraInitCamera(const CCamera* camera,const char* code);

#ifdef __cplusplus
}
#endif
#endif
