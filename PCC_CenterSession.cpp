// PCC_CenterSession.cpp
//
// ע��: ���ļ�Ϊ�������ɣ���С���޸�

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
	NPR_ASSERT((NULL==sessionR) != (NULL==sessionL)); // ����ֻ��Ϊһ��ģʽ
	// TODO: �����PCC_Center�Ĺ��촦��
}

PCC_Center_S::~PCC_Center_S()
{
	// TODO: �����PCC_Center����������
}

TCPSError PCC_Center_S::OnConnected(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN INT32 sessionCount
				)
{
	// TODO: ����ӽӿ�PCC_Center�����Ӻ���

	m_skey = sessionKey;
	NPLogInfo(("PCC_Center_S::OnConnected(%d, %s, %d)", sessionKey, IPP_TO_STR_A(peerID_IPP), sessionCount));
	return TCPS_OK;
}

void PCC_Center_S::OnCallbackReady()
{
	// TODO: ����ӽӿ�PCC_Center�Ļص���������

	NPLogInfo(("PCC_Center_S::OnCallbackReady()"));
}

void PCC_Center_S::OnPostingCallReady()
{
	// TODO: ����ӽӿ�PCC_Center��posting�ص���������
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
	// TODO: ����ӽӿ�PCC_Center�ĶԶ˶��ߴ���
}

void PCC_Center_S::OnClose(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_Center_S::OnClose(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: ����ӽӿ�PCC_Center�����ӹرմ���
	pgrid_util::Singleton<CNodeManage>::instance().diableNode(sessionKey);
}

/////////////////////////////////////////////////////////////////////
// interface PCC_User

PCC_User_S::PCC_User_S(PCC_CenterSessionMaker& sessionMaker, PCC_CenterSession* sessionR, IPCC_User_LocalCallback* sessionL)
	: m_sessionMaker(sessionMaker), m_sessionR(sessionR), m_sessionL(sessionL)
{
	NPR_ASSERT((NULL==sessionR) != (NULL==sessionL)); // ����ֻ��Ϊһ��ģʽ
	// TODO: �����PCC_User�Ĺ��촦��
}

PCC_User_S::~PCC_User_S()
{
	// TODO: �����PCC_User����������
}

TCPSError PCC_User_S::OnConnected(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN INT32 sessionCount
				)
{
	// TODO: ����ӽӿ�PCC_User�����Ӻ���

	NPLogInfo(("PCC_User_S::OnConnected(%d, %s, %d)", sessionKey, IPP_TO_STR_A(peerID_IPP), sessionCount));
	return TCPS_OK;
}

void PCC_User_S::OnCallbackReady()
{
	// TODO: ����ӽӿ�PCC_User�Ļص���������

	NPLogInfo(("PCC_User_S::OnCallbackReady()"));
}

void PCC_User_S::OnPostingCallReady()
{
	// TODO: ����ӽӿ�PCC_User��posting�ص���������

	NPLogInfo(("PCC_User_S::OnPostingCallReady()"));
}

void PCC_User_S::OnPeerBroken(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_User_S::OnPeerBroken(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: ����ӽӿ�PCC_User�ĶԶ˶��ߴ���
}

void PCC_User_S::OnClose(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_User_S::OnClose(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: ����ӽӿ�PCC_User�����ӹرմ���
}

TCPSError PCC_User_S::GetPccProperty(
				OUT PCCProperty& pccProp
				) method
{
	// TODO: ��ʵ�ִ˺���
	PCC_Center_T::PCCProperty prop; 
	pgrid_util::Singleton<CNodeManage>::instance().GetPccProperty(prop);
	memcpy(&pccProp,&prop,sizeof(PCCProperty));
	return TCPS_OK;
}

TCPSError PCC_User_S::ListNodes(
				OUT tcps_Array<NodeDesc>& nodes
				) method
{
	// TODO: ��ʵ�ִ˺���
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::GetNodeDynamicContext(
				IN const tcps_String& nodeName,
				OUT DynamicContext& dynamicContext
				) method
{
	// TODO: ��ʵ�ִ˺���
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::ListModules(
				IN const tcps_String& regex,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method
{
	// TODO: ��ʵ�ִ˺���
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
	// TODO: ��ʵ�ִ˺���
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::QueryJobs(
				IN const tcps_Array<INT64>& jobsKey,
				OUT tcps_Array<ExecuteState>& jobsState
				) method
{
	// TODO: ��ʵ�ִ˺���
	return TCPS_ERR_NOT_IMPLEMENTED;
}

TCPSError PCC_User_S::CancelJob(
				IN INT64 jobKey
				) posting_method
{
	// TODO: ��ʵ�ִ˺���
	return TCPS_ERR_NOT_IMPLEMENTED;
}
