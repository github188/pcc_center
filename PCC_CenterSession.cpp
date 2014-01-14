// PCC_CenterSession.cpp
//
// 注意: 此文件为工具生成，请小心修改

#include "StdAfx.h"
#include "PCC_CenterSession.h"
#include "ipcvt.h"
#include "nplog.h"
#include "nodemanage.h"
#include "singleton.h"
/////////////////////////////////////////////////////////////////////
// interface PCC_Center

PCC_Center_S::PCC_Center_S(PCC_CenterSessionMaker& sessionMaker, PCC_CenterSession* sessionR, IPCC_Center_LocalCallback* sessionL)
	: m_sessionMaker(sessionMaker), m_sessionR(sessionR), m_sessionL(sessionL)
{
	NPR_ASSERT((NULL==sessionR) != (NULL==sessionL)); // 有且只能为一种模式
	// TODO: 请添加PCC_Center的构造处理
}

PCC_Center_S::~PCC_Center_S()
{
	// TODO: 请添加PCC_Center的析构处理
}

TCPSError PCC_Center_S::OnConnected(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN INT32 sessionCount
				)
{
	// TODO: 请添加接口PCC_Center的连接后处理

	m_skey = sessionKey;
	NPLogInfo(("PCC_Center_S::OnConnected(%d, %s, %d)", sessionKey, IPP_TO_STR_A(peerID_IPP), sessionCount));
	return TCPS_OK;
}

void PCC_Center_S::OnCallbackReady()
{
	// TODO: 请添加接口PCC_Center的回调就绪处理

	NPLogInfo(("PCC_Center_S::OnCallbackReady()"));
}

void PCC_Center_S::OnPostingCallReady()
{
	// TODO: 请添加接口PCC_Center的posting回调就绪处理
	pgrid_util::Singleton<CNodeManage>::instance().pushNode(m_skey,this);
	NPLogInfo(("PCC_Center_S::OnPostingCallReady()"));
}

void PCC_Center_S::OnPeerBroken(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_Center_S::OnPeerBroken(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: 请添加接口PCC_Center的对端断线处理
}

void PCC_Center_S::OnClose(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_Center_S::OnClose(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: 请添加接口PCC_Center的连接关闭处理
	pgrid_util::Singleton<CNodeManage>::instance().diableNode(sessionKey);
}

/////////////////////////////////////////////////////////////////////
// interface PCC_User

PCC_User_S::PCC_User_S(PCC_CenterSessionMaker& sessionMaker, PCC_CenterSession* sessionR, IPCC_User_LocalCallback* sessionL)
	: m_sessionMaker(sessionMaker), m_sessionR(sessionR), m_sessionL(sessionL)
{
	NPR_ASSERT((NULL==sessionR) != (NULL==sessionL)); // 有且只能为一种模式
	// TODO: 请添加PCC_User的构造处理
}

PCC_User_S::~PCC_User_S()
{
	// TODO: 请添加PCC_User的析构处理
}

TCPSError PCC_User_S::OnConnected(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN INT32 sessionCount
				)
{
	// TODO: 请添加接口PCC_User的连接后处理

	NPLogInfo(("PCC_User_S::OnConnected(%d, %s, %d)", sessionKey, IPP_TO_STR_A(peerID_IPP), sessionCount));
	return TCPS_OK;
}

void PCC_User_S::OnCallbackReady()
{
	// TODO: 请添加接口PCC_User的回调就绪处理

	NPLogInfo(("PCC_User_S::OnCallbackReady()"));
}

void PCC_User_S::OnPostingCallReady()
{
	// TODO: 请添加接口PCC_User的posting回调就绪处理

	NPLogInfo(("PCC_User_S::OnPostingCallReady()"));
}

void PCC_User_S::OnPeerBroken(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_User_S::OnPeerBroken(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: 请添加接口PCC_User的对端断线处理
}

void PCC_User_S::OnClose(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_User_S::OnClose(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: 请添加接口PCC_User的连接关闭处理
}

TCPSError PCC_User_S::GetPccProperty(
				OUT PCCProperty& pccProp
				) method
{
	// TODO: 请实现此函数
	PCC_Center_T::PCCProperty prop; 
	pgrid_util::Singleton<CNodeManage>::instance().GetPccProperty(prop);
	memcpy(&pccProp,&prop,sizeof(PCCProperty));
	return TCPS_OK;
}

TCPSError PCC_User_S::ListNodes(
				OUT tcps_Array<NodeDesc>& nodes
				) method
{
	// TODO: 请实现此函数
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::GetNodeDynamicContext(
				IN const tcps_String& nodeName,
				OUT DynamicContext& dynamicContext
				) method
{
	// TODO: 请实现此函数
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::ListModules(
				IN const tcps_String& regex,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method
{
	// TODO: 请实现此函数
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::Execute(
				IN INT64 moduleKey,
				IN const tcps_String& inputUrl,
				IN const tcps_String& outputUrl,
				IN const tcps_Binary& moduleParams,
				OUT INT64& jobKey
				) method
{
	// TODO: 请实现此函数
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::QueryJobs(
				IN const tcps_Array<INT64>& jobsKey,
				OUT tcps_Array<ExecuteState>& jobsState
				) method
{
	// TODO: 请实现此函数
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::CancelJob(
				IN INT64 jobKey
				) posting_method
{
	// TODO: 请实现此函数
	return TCPS_ERR_NOT_IMPLEMENTED;
}
