 /*****************************************************************************
*  3DCamera SDK implementations
*
*
*  @file     cs_system.hpp
*  @brief    System class interface
*
*  @version  v1.0
*  @date     2020 / 03 / 17
*
*****************************************************************************/
#ifndef __RPC_INTERFACE_HPP__
#define __RPC_INTERFACE_HPP__
#include "APIExport.hpp"
#include "Types.hpp"

#ifdef __cplusplus
extern "C" {
#endif
	/**
	* @~chinese
	* @brief      ����RpcServer
	* @param[in]  listenPort	�������˿�
	* @return     �ɹ�:SUCCESS, ʧ��:����������
	**/
	CS_API ERROR_CODE startRpcServer(unsigned short listenPort);

	/**
	* @~chinese
	* @brief     ֹͣRpcServer
	* @return    �ɹ�:SUCCESS, ʧ��:����������
	**/
	CS_API ERROR_CODE stopRpcServer();

	/**
	*	����RPC client����ָ���ķ�������IP��ַ�Ͷ˿ں�
	*@pcRpcServerIp		����Ŀ���IP��ַ
	*@usRpcServerPort	����Ŀ��ļ����˿ں�
	*/
	CS_API ERROR_CODE setRpcConnectInfo(const char* pcRpcServerIp, unsigned short usRpcServerPort);

	CS_API ERROR_CODE getRpcConnectInfo(OUT char acRpcServerIp[30], OUT unsigned short& usRpcServerPort);

#ifdef __cplusplus
}
#endif

#endif
                                                                                                                                                             