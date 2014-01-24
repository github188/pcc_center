// PCC_CenterSessionWrapper.cpp
//
// 注意: 此文件为工具生成，请不要修改

#include "StdAfx.h"
#include "PCC_CenterSession.h"
#include "ScopeGuard.h"
#include "ipcvt.h"
#include "ILocker.h"
#include "ModuleInfo.h"
#include "smlib.h"
#include "NPTime.h"
#include "TaskMan.h"
#include "nplog.h"
#include "iscm_smart_container.h"
#include "iscm_posting_caller.h"

//////////////////////////////////////////////////////////////
// PCC_CenterSessionMaker
static void RegisterLocalSessionMakeFunction_(const IPP& serveIPP, PCC_CenterSessionMaker& sessionMaker);
static void UnregisterLocalSessionMakeFunction_(const IPP& serveIPP);

PCC_CenterSessionMaker::PCC_CenterSessionMaker(void* userParameter /*= NULL*/)
	: m_userParameter(userParameter)
	, m_lock(3)
	, m_serveMan(NULL)
	, m_sessionCount(0)
{
}

PCC_CenterSessionMaker::~PCC_CenterSessionMaker()
{
	while(m_localSessionsSet.size() > 0)
	{
		iscm_ILocalCallbackBase* session = *(m_localSessionsSet.begin());
		ASSERT(session);
		session->CloseSession_(); // 服务退出时，关闭进程内还未关闭的客户端
	}
	ASSERT(0 == m_sessionCount);
}

int PCC_CenterSessionMaker::GetSessionObjSize() const
	{	return sizeof(PCC_CenterSession);	}
void PCC_CenterSessionMaker::MakeSessionObj(void* session)
	{	::new(session) PCC_CenterSession(*this);	}

void PCC_CenterSessionMaker::OnServiceCreated(
				IN const IPP& serveIPP,
				IN iscm_IRPCServeMan* rpcMan
				)
{
	ASSERT(NULL==m_serveMan && rpcMan);
	m_serveMan = rpcMan->GetTcpsServeMan();
	RegisterLocalSessionMakeFunction_(serveIPP, *this);
}

void PCC_CenterSessionMaker::OnServiceClose(
				IN const IPP& serveIPP,
				IN iscm_IRPCServeMan* rpcMan
				)
{
	UnregisterLocalSessionMakeFunction_(serveIPP);
	(void)rpcMan;
	m_serveMan = NULL;
}

void PCC_CenterSessionMaker::RegisterLocalSession_(iscm_ILocalCallbackBase* session)
{
	ASSERT(session);
	CNPAutoLock locker(m_lock);
	VERIFY(m_localSessionsSet.insert(session).second);
}

void PCC_CenterSessionMaker::UnregisterLocalSession_(iscm_ILocalCallbackBase* session)
{
	ASSERT(session);
	CNPAutoLock locker(m_lock);
	VERIFY(1 == m_localSessionsSet.erase(session));
}

void PCC_CenterSessionMaker::OnSessionConnect_(INT32* nextSessionKey /*= NULL*/, INT32& sessionCount)
{
	CNPAutoLock locker(m_lock);
	if(nextSessionKey)
	{
		if(m_serveMan)
			*nextSessionKey = m_serveMan->GetNextSessionKey();
		else
			*nextSessionKey = m_sessionKeyGenerater.GetNext();
	}
	ASSERT(m_sessionCount >= 0);
	sessionCount = ++m_sessionCount;
}

void PCC_CenterSessionMaker::OnSessionClosed_()
{
	CNPAutoLock locker(m_lock);
	ASSERT(m_sessionCount > 0);
	--m_sessionCount;
}

//////////////////////////////////////////////////////////////
// PCC_CenterSession
#if defined(_MSC_VER)
	#pragma warning(disable: 4702) // unreachable code
#endif

//[[begin_session_wrap_body]]

INT32 PCC_CenterSession::GetSessionKey() const
{
	tcps_ISession* bindedSession = m_bindedSession;
	if(NULL == bindedSession)
		return 0;
	INT32 sessionKey = 0;
	bindedSession->GetInfos(NULL, NULL, NULL, NULL, &sessionKey);
//	ASSERT(0 != sessionKey);
	return sessionKey;
}

void PCC_CenterSession::CloseSession_(
				IN TCPSError cause /*= TCPS_OK*/
				)
{
	iscm_IRPCServeMan* const serveMan = m_serveMan;
	if(NULL == serveMan)
		return;
	INT32 const sessionKey = GetSessionKey();
	if(0 != sessionKey)
	{
		char sid[16];
		itoa_Traits(sid, sessionKey);
		TCPSError errClose = serveMan->CloseSessionEx(sid, sessionKey, cause);
		(void)errClose;
	}
	if(0 != m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().CloseSession(m_postingProxy.callerKey_);
}

inline PCC_CenterSession::FTVMap_& PCC_CenterSession::GetFTVMap_()
	{	LOCAL_SAFE_STATIC_OBJ(PCC_CenterSession::FTVMap_);	}
PCC_CenterSession::FTVMap_* PCC_CenterSession::sm_FTVMap = NULL;

inline PCC_CenterSession::MethodCallMap_& PCC_CenterSession::GetMethodCallMap_()
	{	LOCAL_SAFE_STATIC_OBJ(PCC_CenterSession::MethodCallMap_);	}
PCC_CenterSession::MethodCallMap_* PCC_CenterSession::sm_methodCallMap = NULL;

void PCC_CenterSession::InitFTVMap_()
{
	if(sm_FTVMap)
		return;

	IscmRPCGlobalLocker locker;
	if(sm_FTVMap)
		return;

	FTVMap_& ftvMap = GetFTVMap_();
	ASSERT(0 == ftvMap.size());
	MethodCallMap_& mdCallMap = GetMethodCallMap_();
	ASSERT(0 == mdCallMap.size());
	//[[begin_init_method_map]]
	VERIFY(ftvMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center"), ftv_PCC_Center)).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::UDPLink_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Center_UDPLink_, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::UDPLinkConfirm_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Center_UDPLinkConfirm_, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::SetTimeout_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Center_SetTimeout_, true))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::SetSessionBufferSize_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Center_SetSessionBufferSize_, true))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::MethodCheck_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Center_MethodCheck_, false))).second);
	VERIFY(ftvMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy"), ftv_PCC_Deploy)).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::Login"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_Login, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::Logout"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_Logout, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::CreateTrunk"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_CreateTrunk, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::RemoveTrunk"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_RemoveTrunk, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::ListTrunk"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_ListTrunk, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::AddAuthCenter"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_AddAuthCenter, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::RemoveAuthCenter"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_RemoveAuthCenter, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::ListAuthCenter"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_ListAuthCenter, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::FindAuthCenter"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_FindAuthCenter, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::AddModule"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_AddModule, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::AddModuleFile"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_AddModuleFile, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::RemoveModule"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_RemoveModule, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::RemoveModuleFiles"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_RemoveModuleFiles, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::ListModules"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_ListModules, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::AddModel"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_AddModel, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::ListModels"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_ListModels, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::DelModel"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_DelModel, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::SetTimeout_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_SetTimeout_, true))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::SetSessionBufferSize_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_SetSessionBufferSize_, true))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::MethodCheck_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_Deploy_MethodCheck_, false))).second);
	VERIFY(ftvMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User"), ftv_PCC_User)).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::GetPccProperty"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_GetPccProperty, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::ListNodes"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_ListNodes, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::GetNodeDynamicContext"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_GetNodeDynamicContext, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::ListModules"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_ListModules, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::Execute"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_Execute, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::QueryJobs"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_QueryJobs, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::CancelJob"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_CancelJob, true))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::UDPLink_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_UDPLink_, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::UDPLinkConfirm_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_UDPLinkConfirm_, false))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::SetTimeout_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_SetTimeout_, true))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::SetSessionBufferSize_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_SetSessionBufferSize_, true))).second);
	VERIFY(mdCallMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::MethodCheck_"), MethodSite_(&PCC_CenterSession::Wrap_PCC_User_MethodCheck_, false))).second);
	//[[end_init_method_map]]
	sm_methodCallMap = &mdCallMap;
	sm_FTVMap = &ftvMap;
}

PCC_CenterSession::PCC_CenterSession(PCC_CenterSessionMaker& sessionMaker)
	: m_sessionMaker(sessionMaker), m_postingProxy(*this)
{
	m_serveMan = NULL;
	m_bindedSession = NULL;
	m_sessionCount = 0;
	m_sessionDummyPtr = NULL;
	DEBUG_EXP(m_closingPromptTime = INVALID_UTC_MSEL);
	DEBUG_EXP(m_callingPostingTaskTID = INVALID_OSTHREADID);

	// 初始化方法表
	InitFTVMap_();
}

PCC_CenterSession::~PCC_CenterSession()
{
	ASSERT(NULL == m_sessionDummyPtr);
	ASSERT(NULL == m_callbackRequester.face_);
	ASSERT(NULL==m_serveMan && !m_serveIPP.IsValid() && !m_peerIPP.IsValid() && NULL==m_bindedSession);
	ASSERT(0 == m_postingProxy.callerKey_);
}

TCPSError PCC_CenterSession::OnConnected(
				IN iscm_IRPCServeMan* serveMan,
				IN tcps_ISession* bindedSession,
				IN const IPP& serveIPP,
				IN const IPP& peerIPP,
				IN INT32 sessionKey,
				IN INT32 sessionCount,
				IN tcps_ITrusteeParameter* trusteeParam /*= NULL*/
				)
{
	ASSERT(NULL == m_callbackRequester.face_);
	ASSERT(!m_udpSite.IsOn());
	ASSERT(NULL == m_sessionDummyPtr);
	ASSERT(NULL==m_serveMan && !m_peerIPP.IsValid() && NULL==m_bindedSession);
	ASSERT(0 == m_postingProxy.callerKey_);
	ASSERT(serveMan && bindedSession);
	ASSERT(!m_peerID_IPP.IsValid() && m_bindedInterface.IsEmpty());
	ASSERT(INVALID_UTC_MSEL==m_closingPromptTime && INVALID_OSTHREADID==m_callingPostingTaskTID);
	(void)sessionKey; (void)sessionCount; (void)trusteeParam;
	m_serveMan = serveMan;
	m_bindedSession = bindedSession;
	m_serveIPP = serveIPP;
	m_peerIPP = peerIPP;
	m_sessionCount = sessionCount;
	m_sessionMaker.m_sessionRegister.BaseRegister_(this);
	return TCPS_OK;
}

void PCC_CenterSession::OnPrepareClose(
				IN TCPSError cause
				)
{
	(void)cause;
	iscm_IRequester* const rpcRequester = m_callbackRequester.face_;
	if(rpcRequester)
		rpcRequester->PrepareDisconnect();
	if(0 != m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().CloseSession(m_postingProxy.callerKey_);
	m_serveMan = NULL;
	DEBUG_EXP(m_closingPromptTime = GetMsel()+1);
}

BOOL PCC_CenterSession::IsSessionBusying() const
{
	// 一定是处于待关闭态的会话（调用过OnPrepareClose()的会话）
	ASSERT(NULL==m_serveMan && m_bindedSession);
	ASSERT(m_postingMethods.callingCount >= 0);
	BOOL const busying = (m_postingMethods.callingCount>0 || m_postingProxy.callerKey_!=0);
#ifdef _DEBUG
	if(busying)
	{
		LTMSEL ltNow = GetMsel();
		if(ltNow-m_closingPromptTime >= 1000*2)
		{
			m_closingPromptTime = ltNow;
			NPLogWarning(("任务线程[%s|0x%08X|%d]执行中，会话[0x%08X]无法关闭"
						, INT64_TO_STR_A(m_callingPostingTaskTID)
						, (UINT32)m_callingPostingTaskTID
						, (int)m_callingPostingTaskTID_int
						, (UINT32)(UINT_PTR)m_sessionDummyPtr
						));
		}
	}
#endif
	return busying;
}

void PCC_CenterSession::OnClose(
				IN TCPSError cause
				)
{
	// 不再assert，压力测试时，当posting会话还未建立时，整个会话开始进入关闭状态，而在过程中，
	// 客户端又发来了posting会话建立请求，此种情况，OnPrepareClose()和IsSessionBusying()保证
	// 不了m_postingProxy.callerKey_一定为0
	//ASSERT(0 == m_postingProxy.callerKey_);

	// ISCM会调用OnPrepareClose()和IsSessionBusying()，保证了不再有任务会执行
	ASSERT(0==m_postingMethods.callingsDataBytes && 0==m_postingMethods.callingCount);

	INT32 const sessionKey = GetSessionKey(); // 必须在m_bindedSession = NULL;之前
	ASSERT(0 != sessionKey);

	// 在OnPrepareClose()中已提前置为NULL
	ASSERT(NULL == m_serveMan);
	// 再赋为NULL（容错）
	m_serveMan = NULL;

	m_bindedSession = NULL;

	ASSERT(NULL==m_postingMethods.head && NULL==m_postingMethods.tail);
	m_sessionMaker.m_sessionRegister.BaseUnregister_(this);

	if(!m_bindedInterface.IsEmpty())
	{
		ASSERT(m_peerID_IPP.IsValid());
		m_sessionMaker.m_sessionRegister.UpdateFaceStat_(iscm_SessionRegister::ufst_remove, m_peerID_IPP, m_bindedInterface);

		ASSERT(sm_FTVMap);
		FTVMap_::iterator itFTV = sm_FTVMap->find(m_bindedInterface.Get());
		ASSERT(itFTV != sm_FTVMap->end());
		FaceTypeValue const ftv = itFTV->second;
		switch(ftv)
		{
		//[[begin_OnClose]]
			case ftv_PCC_Center:
			{
				ASSERT(m_pCC_Center && "PCC_Center"==m_bindedInterface);
				m_sessionMaker.m_sessionRegister.Unregister(m_pCC_Center);
				ISCM_BEGIN_TRY_()
					if(TCPS_OK!=cause && TCPS_ERR_SESSION_DROPED!=cause && TCPS_ERR_EXITING!=cause && TCPS_ERR_SERVE_EXITING!=cause)
						m_pCC_Center->OnPeerBroken(sessionKey, m_peerID_IPP, cause);
					m_pCC_Center->OnClose(sessionKey, m_peerID_IPP, cause);
				ISCM_END_TRY_()
				ISCM_BEGIN_CATCH_ALL_()
				ISCM_END_CATCH_ALL_()
				m_pCC_Center->~PCC_Center_S();
				tcps_Free(m_pCC_Center);
				m_pCC_Center = NULL;
			}
			break;

			case ftv_PCC_Deploy:
			{
				ASSERT(m_pCC_Deploy && "PCC_Deploy"==m_bindedInterface);
				m_sessionMaker.m_sessionRegister.Unregister(m_pCC_Deploy);
				ISCM_BEGIN_TRY_()
					if(TCPS_OK!=cause && TCPS_ERR_SESSION_DROPED!=cause && TCPS_ERR_EXITING!=cause && TCPS_ERR_SERVE_EXITING!=cause)
						m_pCC_Deploy->OnPeerBroken(sessionKey, m_peerID_IPP, cause);
					m_pCC_Deploy->OnClose(sessionKey, m_peerID_IPP, cause);
				ISCM_END_TRY_()
				ISCM_BEGIN_CATCH_ALL_()
				ISCM_END_CATCH_ALL_()
				m_pCC_Deploy->~PCC_Deploy_S();
				tcps_Free(m_pCC_Deploy);
				m_pCC_Deploy = NULL;
			}
			break;

			case ftv_PCC_User:
			{
				ASSERT(m_pCC_User && "PCC_User"==m_bindedInterface);
				m_sessionMaker.m_sessionRegister.Unregister(m_pCC_User);
				ISCM_BEGIN_TRY_()
					if(TCPS_OK!=cause && TCPS_ERR_SESSION_DROPED!=cause && TCPS_ERR_EXITING!=cause && TCPS_ERR_SERVE_EXITING!=cause)
						m_pCC_User->OnPeerBroken(sessionKey, m_peerID_IPP, cause);
					m_pCC_User->OnClose(sessionKey, m_peerID_IPP, cause);
				ISCM_END_TRY_()
				ISCM_BEGIN_CATCH_ALL_()
				ISCM_END_CATCH_ALL_()
				m_pCC_User->~PCC_User_S();
				tcps_Free(m_pCC_User);
				m_pCC_User = NULL;
			}
			break;
		//[[end_OnClose]]
			default:
			ASSERT(false);
			break;
		}
		m_sessionMaker.OnSessionClosed_();

		if(SockValid(m_udpSite.sock_))
			VERIFY(0 == SockClose(m_udpSite.sock_));
		if(m_udpSite.IsOn())
			iscm_FetchUDPServeMan().CloseSession(sessionKey);
		m_udpSite.localPort_ = -1;
		m_udpSite.sock_ = INVALID_SOCKET;
	}
	else
	{
		// 程序运行到此处，一般是此会话转化为了回调通道
	//	ASSERT(TCPS_ERR_SESSION_DROPED == cause);
		ASSERT(!m_peerID_IPP.IsValid());
		ASSERT(NULL == m_sessionDummyPtr);
		ASSERT(-1==m_udpSite.localPort_ && !SockValid(m_udpSite.sock_));
	}

	m_callbackRequester.Release();

	m_sessionDummyPtr = NULL; // 容错处理
	DEBUG_EXP(m_closingPromptTime = INVALID_UTC_MSEL);
	DEBUG_EXP(m_callingPostingTaskTID = INVALID_OSTHREADID);
	m_serveIPP = INVALID_IPP;
	m_peerIPP = INVALID_IPP;
	m_sessionCount = 0;
	m_peerID_IPP = INVALID_IPP;
	m_bindedInterface.Release();
}

void PCC_CenterSession::OnPrepareCall(
				IN const iscm_RPCReq& req,
				IN const void* data,
				OUT BOOL& notifyByTaskPool /*= true*/
				)
{
	(void)req; (void)data; (void)notifyByTaskPool;
	ASSERT(RPCCT_SET_BINDED_INTERFACE == req.cmd
		|| RPCCT_TO_CALLBACK == req.cmd
		|| RPCCT_TO_POSTING_CHANNEL == req.cmd
		|| RPCCT_RPC == req.cmd);
	ASSERT(notifyByTaskPool);
}

TCPSError PCC_CenterSession::OnCall(
				OUT BOOL& requireReplyData /*= true*/,
				OUT BOOL& destroySession /*= false*/,
				IN const iscm_RPCReq& req,
				IN const void* data,
				OUT BOOL& dataTransferred /*= false*/,
				IN iscm_IRPCOutfiter* outfiter
				)
{
#ifdef _DEBUG
	ASSERT(requireReplyData && !destroySession);
	ASSERT(req.len >= (int)sizeof(iscm_RPCReq));
	if(req.len > (int)sizeof(iscm_RPCReq))
		ASSERT(data);
	ASSERT(outfiter);
#endif

	if(RPCCT_RPC == req.cmd)
	{
		ASSERT(req.len > (int)sizeof(iscm_RPCReq));
		TCPSError err;
		while(true)
		{
			err = OnRPCCall_(this, NULL, requireReplyData, data, dataTransferred, req.len-sizeof(iscm_RPCReq), outfiter);
			if(TCPS_ERR_POSTING_PENDING_FULL == err)
			{
				ASSERT(!dataTransferred);
				Sleep(1);
				continue;
			}
			else
				break;
		}
		return err;
	}
	else if(RPCCT_SET_BINDED_INTERFACE == req.cmd)
	{
		if(req.len < (int)(sizeof(req) + sizeof(INT16)*2 + sizeof(IPP) + sizeof(INT32)+1)) // 标识IPP + 字符串interfaceName
		{
			NPLogError(("RPCCT_SET_BINDED_INTERFACE: %s(%d)", tcps_GetErrTxt(TCPS_ERR_MALFORMED_REQ), TCPS_ERR_MALFORMED_REQ));
			destroySession = true;
			return TCPS_ERR_MALFORMED_REQ;
		}
		if(m_peerID_IPP.IsValid() || !m_bindedInterface.IsEmpty())
		{
			NPLogError(("RPCCT_SET_BINDED_INTERFACE: %s(%d)", tcps_GetErrTxt(TCPS_ERR_FUNCTION_RUNNING), TCPS_ERR_FUNCTION_RUNNING));
			destroySession = true;
			return TCPS_ERR_FUNCTION_RUNNING;
		}

		const BYTE* inPar = (const BYTE*)data;
		INT16 protocolVer = *(INT16*)inPar;
		inPar += sizeof(INT16);
		INT16 localPeerFlag = *(INT16*)inPar;
		inPar += sizeof(INT16);
		if(0!=protocolVer || 0!=localPeerFlag)
		{
			NPLogError(("RPCCT_SET_BINDED_INTERFACE: Invalid network protocol version"));
			destroySession = true;
			return TCPS_ERR_MALFORMED_REQ;
		}

		const IPP& peerID_IPP = *(IPP*)inPar;
		inPar += sizeof(IPP);
		INT32 faceNameLen = *(INT32*)inPar;
		inPar += sizeof(INT32);
		const char* faceName = (const char*)inPar;
		inPar += faceNameLen+1;
		if(req.len-(int)sizeof(req) != inPar-(const BYTE*)data
			|| !peerID_IPP.IsValid() || 0 != faceName[faceNameLen])
		{
			NPLogError(("RPCCT_SET_BINDED_INTERFACE: %s(%d)", tcps_GetErrTxt(TCPS_ERR_MALFORMED_REQ), TCPS_ERR_MALFORMED_REQ));
			destroySession = true;
			return TCPS_ERR_MALFORMED_REQ;
		}

		INT32 const sessionKey = GetSessionKey();
		ASSERT(0 != sessionKey);
		char sid[16];
		itoa_Traits(sid, sessionKey);
		TCPSError err = m_bindedSession->SetSessionID(sid);
		if(TCPS_OK != err)
		{
			NPLogError(("设置会话ID失败，接口名: '%s', 错误号: %d(%s)", faceName, err, tcps_GetErrTxt(err)));
			destroySession = true;
			return err;
		}

		ASSERT(sm_FTVMap);
		FTVMap_::iterator itFTV = sm_FTVMap->find(faceName);
		if(itFTV == sm_FTVMap->end())
		{
			NPLogError(("接口'%s'未定义, from '%s'", faceName, IPP_TO_STR_A(m_peerIPP)));
			destroySession = true;
			return TCPS_ERR_INVALID_INTERFACE;
		}

		INT32 sessionCount2;
		m_sessionMaker.OnSessionConnect_(NULL, sessionCount2);

		FaceTypeValue const ftv = itFTV->second;
		switch(ftv)
		{
		//[[begin_OnConnected]]
			case ftv_PCC_Center:
			{
				ASSERT(NULL==m_pCC_Center && 0==strcmp("PCC_Center", faceName));
				m_pCC_Center = tcps_NewEx(PCC_Center_S, (m_sessionMaker, this, NULL));
				TCPSError err = TCPS_ERROR;
				try
				{
					err = m_pCC_Center->OnConnected(sessionKey, peerID_IPP, sessionCount2);
				}
				catch(TCPSError ret)
				{
					ASSERT(TCPS_OK != ret);
					err = ret;
				}
				catch(int ret)
				{
					ASSERT(TCPS_OK != ret);
					err = (TCPSError)ret;
				}
				catch(std::bad_alloc)
				{
					NPLogError(("PCC_Center_S::OnConnected(), Out of memory"));
					err = TCPS_ERR_OUT_OF_MEMORY;
				}
				ISCM_BEGIN_CATCH_ALL_()
					NPLogError(("PCC_Center_S::OnConnected(), Unknown exception"));
					err = TCPS_ERR_UNKNOWN_EXCEPTION;
				ISCM_END_CATCH_ALL_()
				if(TCPS_OK != err)
				{
					ISCM_BEGIN_TRY_()
						m_pCC_Center->OnClose(sessionKey, peerID_IPP, err);
					ISCM_END_TRY_()
					ISCM_BEGIN_CATCH_ALL_()
					ISCM_END_CATCH_ALL_()
					m_sessionMaker.OnSessionClosed_();
					m_pCC_Center->~PCC_Center_S();
					tcps_Free(m_pCC_Center);
					m_pCC_Center = NULL;
					destroySession = true;
					return err;
				}
			}
			break;

			case ftv_PCC_Deploy:
			{
				ASSERT(NULL==m_pCC_Deploy && 0==strcmp("PCC_Deploy", faceName));
				m_pCC_Deploy = tcps_NewEx(PCC_Deploy_S, (m_sessionMaker, this, NULL));
				TCPSError err = TCPS_ERROR;
				try
				{
					err = m_pCC_Deploy->OnConnected(sessionKey, peerID_IPP, sessionCount2);
				}
				catch(TCPSError ret)
				{
					ASSERT(TCPS_OK != ret);
					err = ret;
				}
				catch(int ret)
				{
					ASSERT(TCPS_OK != ret);
					err = (TCPSError)ret;
				}
				catch(std::bad_alloc)
				{
					NPLogError(("PCC_Deploy_S::OnConnected(), Out of memory"));
					err = TCPS_ERR_OUT_OF_MEMORY;
				}
				ISCM_BEGIN_CATCH_ALL_()
					NPLogError(("PCC_Deploy_S::OnConnected(), Unknown exception"));
					err = TCPS_ERR_UNKNOWN_EXCEPTION;
				ISCM_END_CATCH_ALL_()
				if(TCPS_OK != err)
				{
					ISCM_BEGIN_TRY_()
						m_pCC_Deploy->OnClose(sessionKey, peerID_IPP, err);
					ISCM_END_TRY_()
					ISCM_BEGIN_CATCH_ALL_()
					ISCM_END_CATCH_ALL_()
					m_sessionMaker.OnSessionClosed_();
					m_pCC_Deploy->~PCC_Deploy_S();
					tcps_Free(m_pCC_Deploy);
					m_pCC_Deploy = NULL;
					destroySession = true;
					return err;
				}
			}
			break;

			case ftv_PCC_User:
			{
				ASSERT(NULL==m_pCC_User && 0==strcmp("PCC_User", faceName));
				m_pCC_User = tcps_NewEx(PCC_User_S, (m_sessionMaker, this, NULL));
				TCPSError err = TCPS_ERROR;
				try
				{
					err = m_pCC_User->OnConnected(sessionKey, peerID_IPP, sessionCount2);
				}
				catch(TCPSError ret)
				{
					ASSERT(TCPS_OK != ret);
					err = ret;
				}
				catch(int ret)
				{
					ASSERT(TCPS_OK != ret);
					err = (TCPSError)ret;
				}
				catch(std::bad_alloc)
				{
					NPLogError(("PCC_User_S::OnConnected(), Out of memory"));
					err = TCPS_ERR_OUT_OF_MEMORY;
				}
				ISCM_BEGIN_CATCH_ALL_()
					NPLogError(("PCC_User_S::OnConnected(), Unknown exception"));
					err = TCPS_ERR_UNKNOWN_EXCEPTION;
				ISCM_END_CATCH_ALL_()
				if(TCPS_OK != err)
				{
					ISCM_BEGIN_TRY_()
						m_pCC_User->OnClose(sessionKey, peerID_IPP, err);
					ISCM_END_TRY_()
					ISCM_BEGIN_CATCH_ALL_()
					ISCM_END_CATCH_ALL_()
					m_sessionMaker.OnSessionClosed_();
					m_pCC_User->~PCC_User_S();
					tcps_Free(m_pCC_User);
					m_pCC_User = NULL;
					destroySession = true;
					return err;
				}
			}
			break;
		//[[end_OnConnected]]
			default:
			ASSERT(false);
			break;
		}

		m_peerID_IPP = peerID_IPP;
		m_bindedInterface = faceName;
		BYTE* replyData = (BYTE*)tcps_Alloc(sizeof(INT64)+sizeof(INT32));
		*(INT64*)replyData = (INT64)this;
		*(INT32*)(replyData+sizeof(INT64)) = sessionKey;
		outfiter->Push(replyData, sizeof(INT64)+sizeof(INT32), true, NULL);
		m_sessionMaker.m_sessionRegister.UpdateFaceStat_(iscm_SessionRegister::ufst_add, m_peerID_IPP, m_bindedInterface);
		return TCPS_OK;
	}
	else if(RPCCT_TO_CALLBACK == req.cmd)
	{
		if(m_sessionDummyPtr)
		{
			NPLogError(("RPCCT_TO_CALLBACK: %s(%d)", tcps_GetErrTxt(TCPS_ERR_REFUSED), TCPS_ERR_REFUSED));
			destroySession = true;
			return TCPS_ERR_REFUSED;
		}
		if(req.len != (int)(sizeof(req)+sizeof(INT64)+sizeof(INT32)))
		{
			NPLogError(("RPCCT_TO_CALLBACK: %s(%d)", tcps_GetErrTxt(TCPS_ERR_MALFORMED_REQ), TCPS_ERR_MALFORMED_REQ));
			destroySession = true;
			return TCPS_ERR_MALFORMED_REQ;
		}
		char peerIPPTxt[32];
		GetIPPortTxt(m_peerIPP, peerIPPTxt);

		iscm_IRPCServeMan* const serveMan = m_serveMan;
		if(NULL == serveMan)
			return TCPS_ERR_SESSION_NOT_CONNECTED;
		SOCKET sock;
		TCPSError err = serveMan->DropSession(this, sock);
		if(TCPS_OK != err)
		{
			NPLogError(("PCC_CenterSession::DropSession(%s) failed, %s(%d)", peerIPPTxt, tcps_GetErrTxt(err), err));
			destroySession = true;
			return err;
		}

		INT64 const bindedSessionID = *(INT64*)data;
		INT32 const bindedSessionKey = *(INT32*)((BYTE*)data + sizeof(INT64));
		if(0==bindedSessionID || 0==bindedSessionKey)
		{
			// 容错处理
			NPLogError(("PCC_CenterSession::BindCallbackSocket(%s) failed, bindedSessionID is NULL", peerIPPTxt));
			VERIFY(0 == SockClose(sock));
			destroySession = true;
			return TCPS_ERR_INVALID_PARAM;
		}

		PCC_CenterSession* const bindedSession = (PCC_CenterSession*)bindedSessionID;
		INT32 const sessionKey = bindedSession->GetSessionKey();
		if(0 == sessionKey)
			err = TCPS_ERR_SESSION_NOT_CONNECTED;
		else if(sessionKey != bindedSessionKey)
			err = TCPS_ERR_SESSION_NOT_EXISTED;
		else
			err = m_sessionMaker.m_sessionRegister.BindCallbackSocket_(bindedSession, sock, peerIPPTxt);
		if(TCPS_OK != err)
		{
#if defined(__linux__) && (32==NPR_SYS_BITS)
			NPLogError(("%s::BindCallbackSocket(%s, 0x%08X%08X) failed, %s(%d)"
						, m_bindedInterface.Get()
						, peerIPPTxt
						, (UINT)((UINT64)bindedSessionID >> 32)
						, (UINT)bindedSessionID
						, tcps_GetErrTxt(err), err
						));
#else
			NPLogError(("%s::BindCallbackSocket(%s, 0x%08X%08X) failed, %s(%d)"
						, m_bindedInterface.Get()
						, peerIPPTxt
						, (DWORD)((UINT64)bindedSessionID >> 32)
						, (DWORD)bindedSessionID
						, tcps_GetErrTxt(err), err
						));
#endif
			// 发送准确的错误信息给客户端
			iscm_RPCReply reply;
			reply.len = sizeof(reply);
			reply.ret = err;
			DWORD timeoutMSELs = iscm_GetDefaultSendTimeout();
			SockMustWriteByTime(sock, &reply, sizeof(reply), timeoutMSELs);
			VERIFY(0 == SockSetLinger(sock, true, timeoutMSELs)); // 设置关闭延迟发送超时，以使客户端收到准确错误信息
			VERIFY(0 == SockClose(sock));
			destroySession = true;
			return err;
		}

		return TCPS_ERR_SESSION_DROPED;
	}
	else if(RPCCT_TO_POSTING_CHANNEL == req.cmd)
	{
		if(m_sessionDummyPtr)
		{
			NPLogError(("RPCCT_TO_POSTING_CHANNEL: %s(%d)", tcps_GetErrTxt(TCPS_ERR_REFUSED), TCPS_ERR_REFUSED));
			destroySession = true;
			return TCPS_ERR_REFUSED;
		}
		if(req.len != (int)(sizeof(req)+sizeof(INT64)+sizeof(INT32)))
		{
			NPLogError(("RPCCT_TO_POSTING_CHANNEL: %s(%d)", tcps_GetErrTxt(TCPS_ERR_MALFORMED_REQ), TCPS_ERR_MALFORMED_REQ));
			destroySession = true;
			return TCPS_ERR_MALFORMED_REQ;
		}
		char peerIPPTxt[32];
		IPPToString(m_peerIPP, peerIPPTxt);

		iscm_IRPCServeMan* const serveMan = m_serveMan;
		if(NULL == serveMan)
			return TCPS_ERR_SESSION_NOT_CONNECTED;
		SOCKET sock;
		TCPSError err = serveMan->DropSession(this, sock);
		if(TCPS_OK != err)
		{
			NPLogError(("PCC_CenterSession::DropSession(%s) failed, %s(%d)", peerIPPTxt, tcps_GetErrTxt(err), err));
			destroySession = true;
			return err;
		}

		INT64 const bindedSessionID = *(INT64*)data;
		INT32 const bindedSessionKey = *(INT32*)((BYTE*)data + sizeof(INT64));
		if(0==bindedSessionID || 0==bindedSessionKey)
		{
			// 容错处理
			NPLogError(("PCC_CenterSession::BindPostingSocket(%s) failed, bindedSessionID is NULL", peerIPPTxt));
			VERIFY(0 == SockClose(sock));
			destroySession = true;
			return TCPS_ERR_INVALID_PARAM;
		}

		PCC_CenterSession* const bindedSession = (PCC_CenterSession*)bindedSessionID;
		INT32 const sessionKey = bindedSession->GetSessionKey();
		if(0 == sessionKey)
			err = TCPS_ERR_SESSION_NOT_CONNECTED;
		else if(sessionKey != bindedSessionKey)
			err = TCPS_ERR_SESSION_NOT_EXISTED;
		else
			err = m_sessionMaker.m_sessionRegister.BindPostingSocket_(bindedSession, sock, peerIPPTxt);
		if(TCPS_OK != err)
		{
#if defined(__linux__) && (32==NPR_SYS_BITS)
			NPLogError(("%s::BindPostingSocket(%s, 0x%08X%08X) failed, %s(%d)"
						, m_bindedInterface.Get()
						, peerIPPTxt
						, (UINT)((UINT64)bindedSessionID >> 32)
						, (UINT)bindedSessionID
						, tcps_GetErrTxt(err), err
						));
#else
			NPLogError(("%s::BindPostingSocket(%s, 0x%08X%08X) failed, %s(%d)"
						, m_bindedInterface.Get()
						, peerIPPTxt
						, (DWORD)((UINT64)bindedSessionID >> 32)
						, (DWORD)bindedSessionID
						, tcps_GetErrTxt(err), err
						));
#endif
			// 发送准确的错误信息给客户端
			iscm_RPCReply reply;
			reply.len = sizeof(reply);
			reply.ret = err;
			DWORD timeoutMSELs = iscm_GetDefaultSendTimeout();
			SockMustWriteByTime(sock, &reply, sizeof(reply), timeoutMSELs);
			VERIFY(0 == SockSetLinger(sock, true, timeoutMSELs)); // 设置关闭延迟发送超时，以使客户端收到准确错误信息
			VERIFY(0 == SockClose(sock));
			destroySession = true;
			return err;
		}

		return TCPS_ERR_SESSION_DROPED;
	}

	NPLogWarning(("PCC_CenterSession::OnCall(), Invalid cmd %d from '%s'", req.cmd, IPP_TO_STR_A(m_peerIPP)));
	destroySession = true;
	return TCPS_ERR_NOT_SUPPORTED;
}

iscm_IRPCServeMan* PCC_CenterSession::GetServeMan() const
	{	return m_serveMan;	}

void PCC_CenterSession::OnUDPCall(
				IN tcps_Binary& frame
				)
{
	ASSERT(frame.Length() > 0);
	while(true)
	{
		BOOL requireReplyData = true;
		const void* inParamsData = frame.Get();
		BOOL dataTransferred = false;
		INT_PTR inParamsDataLen = frame.Length();
		TCPSError err = OnRPCCall_(this, NULL, requireReplyData, inParamsData, dataTransferred, inParamsDataLen, NULL/*outfiter*/);
		ASSERT(TCPS_OK!=err || !requireReplyData);
		if(TCPS_ERR_POSTING_PENDING_FULL == err)
		{
			ASSERT(!dataTransferred);
			Sleep(1);
			continue;
		}
		else
		{
			if(dataTransferred)
				frame.Drop();
			break;
		}
	}
}

TCPSError PCC_CenterSession::BindCallbackSocket_(
				IN SOCKET sock,
				IN const char* peerIPPTxt
				)
{
	ASSERT(SockValid(sock));
	if(NULL == m_serveMan)
		return TCPS_ERR_SESSION_NOT_CONNECTED; // 客户端正在做异步重连恢复，此时又发生了客户端对象被关闭动作

	if(NULL == m_callbackRequester.face_)
	{
		m_callbackRequester.face_ = iscm_MakeRequester(false);
		if(NULL == m_callbackRequester.face_)
		{
			ASSERT(false);
			return TCPS_ERR_CALLBACK_BIND_FAILED; // 容错处理
		}
	}

	// 肯定可以成功转化为回调通道，在AttachSocket()之前发送成功回应码，
	// 以避免若马上转化为异步并行发送模式，可能发生发送的普通数据被当回应码的问题。
	iscm_RPCReply reply;
	reply.len = sizeof(reply);
	reply.ret = TCPS_OK;
	if((int)sizeof(reply) != SockWriteAllByTime(sock, &reply, sizeof(reply), iscm_GetDefaultSendTimeout()))
		NPLogError(("PCC_CenterSession::BindCallbackSocket_(%s), send reply failed", peerIPPTxt));
	else
		ASSERT(true); // NPLogInfo(("PCC_CenterSession::BindCallbackSocket_(%s) ok", peerIPPTxt));

	TCPSError err = m_callbackRequester.face_->AttachSocket(sock);
	ASSERT(TCPS_OK == err);

	ASSERT(sm_FTVMap);
	FTVMap_::iterator itFTV = sm_FTVMap->find(m_bindedInterface.Get());
	if(itFTV != sm_FTVMap->end())
	{
		switch(itFTV->second)
		{
		//[[begin_OnCallbackReady]]
			case ftv_PCC_Center:
				m_pCC_Center->OnCallbackReady();
				break;
			case ftv_PCC_Deploy:
				m_pCC_Deploy->OnCallbackReady();
				break;
			case ftv_PCC_User:
				m_pCC_User->OnCallbackReady();
				break;
		//[[end_OnCallbackReady]]
			default:
				ASSERT(false);
				break;
		}
	}

	return err;
}

TCPSError PCC_CenterSession::BindPostingSocket_(
				IN SOCKET sock,
				IN const char* peerIPPTxt
				)
{
	ASSERT(SockValid(sock));
	ASSERT(0 == m_postingProxy.callerKey_);
	if(NULL == m_serveMan)
		return TCPS_ERR_SESSION_NOT_CONNECTED; // 客户端正在做异步重连恢复，此时又发生了客户端对象被关闭动作

	// 肯定可以成功转化为回调通道，在AddSession()之前发送成功回应码，
	// 以避免若马上转化为异步发送模式，可能发生发送的普通数据被当回应码的问题。
	iscm_RPCReply reply;
	reply.len = sizeof(reply);
	reply.ret = TCPS_OK;
	if((int)sizeof(reply) != SockMustWriteByTime(sock, &reply, sizeof(reply), iscm_GetDefaultSendTimeout()))
		NPLogError(("PCC_CenterSession::BindCallbackSocket_(%s), send reply failed", peerIPPTxt));
	else
		ASSERT(true); // NPLogInfo(("PCC_CenterSession::BindCallbackSocket_(%s) ok", peerIPPTxt));

	TCPSError err = iscm_FetchPostingCallerMan().AddSession(m_postingProxy.callerKey_, sock, true, &m_postingProxy);
	ASSERT(TCPS_OK==err /*&& 0!=m_postingProxy.callerKey_*/);
	if(0 == m_postingProxy.callerKey_)
		return err; // 极端情况处理（可能此时立即又发生了网络断线，m_postingProxy.callerKey_已被清理为0）

	ASSERT(sm_FTVMap);
	FTVMap_::iterator itFTV = sm_FTVMap->find(m_bindedInterface.Get());
	if(itFTV != sm_FTVMap->end())
	{
		switch(itFTV->second)
		{
		//[[begin_OnPostingCallReady]]
			case ftv_PCC_Center:
				if(!m_pCC_Center->m_postingSendParam.IsDefault())
					iscm_FetchPostingCallerMan().SetBufferingParam(m_postingProxy.callerKey_, m_pCC_Center->m_postingSendParam.maxSendingBytes_, m_pCC_Center->m_postingSendParam.maxSendings_);
				m_pCC_Center->OnPostingCallReady();
				break;
			case ftv_PCC_Deploy:
				if(!m_pCC_Deploy->m_postingSendParam.IsDefault())
					iscm_FetchPostingCallerMan().SetBufferingParam(m_postingProxy.callerKey_, m_pCC_Deploy->m_postingSendParam.maxSendingBytes_, m_pCC_Deploy->m_postingSendParam.maxSendings_);
				m_pCC_Deploy->OnPostingCallReady();
				break;
			case ftv_PCC_User:
				if(!m_pCC_User->m_postingSendParam.IsDefault())
					iscm_FetchPostingCallerMan().SetBufferingParam(m_postingProxy.callerKey_, m_pCC_User->m_postingSendParam.maxSendingBytes_, m_pCC_User->m_postingSendParam.maxSendings_);
				m_pCC_User->OnPostingCallReady();
				break;
		//[[end_OnPostingCallReady]]
			default:
				ASSERT(false);
				break;
		}
	}

	return err;
}

void PCC_CenterSession::PostingTask_::OnPoolTask()
{
	ASSERT(baseInParamsData_ && inParamsData_ && inParamsDataLen_>=0);
	ASSERT((INT_PTR)(inParamsData_ - (const BYTE*)baseInParamsData_) > 0);
	INT_PTR const inParamsDataLen_t = inParamsDataLen_;
	if(session_.m_serveMan)
	{
		CNPAutoLock locker(session_.m_methodCallLock);
		ASSERT(INVALID_OSTHREADID == session_.m_callingPostingTaskTID);
		DEBUG_EXP(session_.m_callingPostingTaskTID = OSThreadSelf());
		TCPSError err = (*handler_)(
								&session_,
								NULL,
								peerCallFlags_,
								inParamsData_,
								inParamsDataLen_,
								NULL/*outfiter*/
								);
		DEBUG_EXP(session_.m_callingPostingTaskTID = INVALID_OSTHREADID);
		ASSERT(TCPS_OK!=err || 0==inParamsDataLen_);
		(void)err;
	}
	else
		ASSERT(true); // 处于退出等待状态

	tcps_Free(baseInParamsData_);
	PCC_CenterSession& session = session_;
	tcps_Delete(this);

	CNPAutoLock locker(session.m_postingMethods.lock);
	ASSERT(session.m_postingMethods.callingsDataBytes >= inParamsDataLen_t);
	session.m_postingMethods.callingsDataBytes -= inParamsDataLen_t;
	ASSERT(session.m_postingMethods.callingCount > 0);
	--(session.m_postingMethods.callingCount);
	if(NULL == session.m_postingMethods.head)
	{
		ASSERT(0 == session.m_postingMethods.callingCount);
		return; // 队列处理完毕
	}
	else
		ASSERT(session.m_postingMethods.callingCount > 0);

	NPBaseTask* task = session.m_postingMethods.head;
	if(session.m_postingMethods.head == session.m_postingMethods.tail)
		session.m_postingMethods.head = session.m_postingMethods.tail = NULL;
	else
		session.m_postingMethods.head = task->m_nextPoolTask;
	FetchTaskPool()->Push(task);
}

TCPSError PCC_CenterSession::OnRPCCall_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				OUT BOOL& requireReplyData /*= true*/,
				IN const void* inParamsData,
				OUT BOOL& dataTransferred /*= false*/,
				IN INT_PTR inParamsDataLen,
				OUT iscm_IRPCOutfiter* outfiter
				)
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	ASSERT(requireReplyData && inParamsData && inParamsDataLen>0/* && outfiter*/);
	const BYTE* ptrInParams = (const BYTE*)inParamsData;
	INT_PTR ptrInParamsLen = inParamsDataLen;

	if(ptrInParamsLen < (int)sizeof(iscm_PeerCallFlags))
		return TCPS_ERR_MALFORMED_REQ;
	iscm_PeerCallFlags peerCallFlags = *(iscm_PeerCallFlags*)ptrInParams;
	if((int)sizeof(BOOL) != peerCallFlags.sizeofBOOL_req)
		return TCPS_ERR_MALFORMED_REQ;
	if((int)sizeof(DummyEnumType) != peerCallFlags.sizeofEnum_req)
		return TCPS_ERR_MALFORMED_REQ;
	ptrInParams += sizeof(iscm_PeerCallFlags);
	ptrInParamsLen -= sizeof(iscm_PeerCallFlags);

	if(ptrInParamsLen < (int)sizeof(INT32))
		return TCPS_ERR_MALFORMED_REQ;
	INT32 call_id_len = *(INT32*)ptrInParams;
	ptrInParams += sizeof(INT32);
	ptrInParamsLen -= sizeof(INT32);
	if(ptrInParamsLen < call_id_len+1)
		return TCPS_ERR_MALFORMED_REQ;
	const char* call_id = (const char*)ptrInParams;
	ptrInParams += call_id_len+1;
	ptrInParamsLen -= call_id_len+1;
	const char* call_id_sep = strstr(call_id, "::");
	if(NULL == call_id_sep)
		return TCPS_ERR_INVALID_PARAM;
	if(thisObj)
	{
		//ASSERT(!thisObj->m_bindedInterface.IsEmpty());
		if(thisObj->m_bindedInterface.Length() != call_id_sep-call_id
			|| 0 != strncmp(thisObj->m_bindedInterface.Get(), call_id, call_id_sep-call_id))
			return TCPS_ERR_METHOD_NOT_MATCH;
	}

	InitFTVMap_();
	ASSERT(sm_methodCallMap);
	MethodCallMap_::const_iterator cit = sm_methodCallMap->find(call_id, call_id_len);
	if(sm_methodCallMap->end() == cit)
		return TCPS_ERR_NOT_SUPPORTED;

	// posting方法/回调
	if(cit->second.isPosting)
	{
		if(thisObj && NULL==thisObj->m_serveMan)
			return TCPS_ERR_EXITING;

		// 当缓存的未决调用小于1个时，直接调用
		if(NULL==thisObj || thisObj->m_postingPendingParam.maxPendings_<=1)
		{
			TCPSError errIscm;
			if(thisObj)
			{
				CNPAutoLock locker(thisObj->m_methodCallLock);
				errIscm = (*(cit->second.handler))(thisObj, faceObj, peerCallFlags, ptrInParams, ptrInParamsLen, NULL/*outfiter*/);
			}
			else
			{
				errIscm = (*(cit->second.handler))(thisObj, faceObj, peerCallFlags, ptrInParams, ptrInParamsLen, NULL/*outfiter*/);
			}

#ifdef _DEBUG
			if(TCPS_OK == errIscm)
			{
				ASSERT(ptrInParams-(const BYTE*)inParamsData == inParamsDataLen);
				ASSERT(0 == ptrInParamsLen);
			}
#else
			(void)errIscm;
#endif
		//	ASSERT(!peerCallFlags.requireReply); // ??
			requireReplyData = false;
			ASSERT(!dataTransferred);
			return TCPS_OK;
		}

		// 投递一个task，异步执行
		ASSERT(thisObj);
		if(thisObj->m_postingMethods.callingsDataBytes >= thisObj->m_postingPendingParam.maxPendingBytes_
			|| thisObj->m_postingMethods.callingCount >= thisObj->m_postingPendingParam.maxPendings_
			)
		{
		//	NPLogWarning(("Posting calling lost: ([total, %s bytes] >= [max, %s bytes] || [total, %d calls] >= [max, %d calls])"
		//				, INT64_TO_STR_A(thisObj->m_postingMethods.callingsDataBytes), INT64_TO_STR_A(thisObj->m_postingPendingParam.maxPendingBytes_)
		//				, thisObj->m_postingMethods.callingCount, thisObj->m_postingPendingParam.maxPendings_
		//				));
			return TCPS_ERR_POSTING_PENDING_FULL;
		}
		PostingTask_* task = tcps_NewEx(PostingTask_, (*thisObj));
		task->peerCallFlags_ = peerCallFlags;
		task->baseInParamsData_ = (void*)inParamsData;
		task->inParamsData_ = ptrInParams;
		task->inParamsDataLen_ = ptrInParamsLen;
		task->handler_ = cit->second.handler;
		{
			CNPAutoLock locker(thisObj->m_postingMethods.lock);
			thisObj->m_postingMethods.callingsDataBytes += ptrInParamsLen;
			++(thisObj->m_postingMethods.callingCount);
			if(thisObj->m_postingMethods.callingCount > 1)
			{
				task->m_nextPoolTask = NULL;
				if(thisObj->m_postingMethods.tail)
				{
					thisObj->m_postingMethods.tail->m_nextPoolTask = task;
					thisObj->m_postingMethods.tail = task;
				}
				else
					thisObj->m_postingMethods.head = thisObj->m_postingMethods.tail = task;
			}
			else
			{
				ASSERT(NULL==thisObj->m_postingMethods.head && NULL==thisObj->m_postingMethods.tail);
				ASSERT(ptrInParamsLen==thisObj->m_postingMethods.callingsDataBytes && 1==thisObj->m_postingMethods.callingCount);
				FetchTaskPool()->Push(task);
			}
		}

		if(peerCallFlags.requireReply)
		{
			// 给outfiter填充内置返回参数
			struct PostOutParamWrapSite
			{
				iscm_RPCReplyPrefix replyPrefix;
				PostOutParamWrapSite() { replyPrefix.Init(); }
				static void FreeAction(void* p)
				{
					PostOutParamWrapSite* ptr = (PostOutParamWrapSite*)((BYTE*)p - offset_of(PostOutParamWrapSite, replyPrefix));
					ptr->~PostOutParamWrapSite();
					tcps_Free(ptr);
				}
			};
			PostOutParamWrapSite* opWrapper = tcps_New(PostOutParamWrapSite);
			Set_BaseType_(outfiter, opWrapper->replyPrefix, PostOutParamWrapSite::FreeAction);
		}
		else
		{
			// 指示不需要发送回应数据了
			requireReplyData = false;
		}

		dataTransferred = true; // 指示输入参数数据指针inParamsData被转移
		return TCPS_OK; // 立即返回成功
	}

	// 非posting方法/回调
	TCPSError errTcps;
	if(thisObj)
	{
		CNPAutoLock locker(thisObj->m_methodCallLock);
		errTcps = (*(cit->second.handler))(thisObj, faceObj, peerCallFlags, ptrInParams, ptrInParamsLen, outfiter);
	}
	else
	{
		errTcps = (*(cit->second.handler))(thisObj, faceObj, peerCallFlags, ptrInParams, ptrInParamsLen, outfiter);
	}
#ifdef _DEBUG
	if(TCPS_OK == errTcps)
	{
		ASSERT(ptrInParams-(const BYTE*)inParamsData == inParamsDataLen);
		ASSERT(0 == ptrInParamsLen);
	}
#endif
	return errTcps;
}

//[[begin_method_wrap_body]]

static const char* s_PCC_Center_AddModelCenter_TypeInfo_ = NULL;
static int s_PCC_Center_AddModelCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Center_DelModelCenter_TypeInfo_ = NULL;
static int s_PCC_Center_DelModelCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Center_GetStaticContext_TypeInfo_ = NULL;
static int s_PCC_Center_GetStaticContext_TypeInfo_len_ = 0;

static const char* s_PCC_Center_GetDynamicContext_TypeInfo_ = NULL;
static int s_PCC_Center_GetDynamicContext_TypeInfo_len_ = 0;

static const char* s_PCC_Center_AddModel_TypeInfo_ = NULL;
static int s_PCC_Center_AddModel_TypeInfo_len_ = 0;

static const char* s_PCC_Center_DelModel_TypeInfo_ = NULL;
static int s_PCC_Center_DelModel_TypeInfo_len_ = 0;

static const char* s_PCC_Center_UDPLink__TypeInfo_ = NULL;
static int s_PCC_Center_UDPLink__TypeInfo_len_ = 0;

static const char* s_PCC_Center_UDPLinkConfirm__TypeInfo_ = NULL;
static int s_PCC_Center_UDPLinkConfirm__TypeInfo_len_ = 0;

static const char* s_PCC_Center_SetRedirect__TypeInfo_ = NULL;
static int s_PCC_Center_SetRedirect__TypeInfo_len_ = 0;

static const char* s_PCC_Center_SetTimeout__TypeInfo_ = NULL;
static int s_PCC_Center_SetTimeout__TypeInfo_len_ = 0;

static const char* s_PCC_Center_SetSessionBufferSize__TypeInfo_ = NULL;
static int s_PCC_Center_SetSessionBufferSize__TypeInfo_len_ = 0;

static const char* s_PCC_Center_MethodCheck__TypeInfo_ = NULL;
static int s_PCC_Center_MethodCheck__TypeInfo_len_ = 0;

static const char* s_PCC_Center_CallbackCheck__TypeInfo_ = NULL;
static int s_PCC_Center_CallbackCheck__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_Login_TypeInfo_ = NULL;
static int s_PCC_Deploy_Login_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_Logout_TypeInfo_ = NULL;
static int s_PCC_Deploy_Logout_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_CreateTrunk_TypeInfo_ = NULL;
static int s_PCC_Deploy_CreateTrunk_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_RemoveTrunk_TypeInfo_ = NULL;
static int s_PCC_Deploy_RemoveTrunk_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_ListTrunk_TypeInfo_ = NULL;
static int s_PCC_Deploy_ListTrunk_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_AddAuthCenter_TypeInfo_ = NULL;
static int s_PCC_Deploy_AddAuthCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_RemoveAuthCenter_TypeInfo_ = NULL;
static int s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_ListAuthCenter_TypeInfo_ = NULL;
static int s_PCC_Deploy_ListAuthCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_FindAuthCenter_TypeInfo_ = NULL;
static int s_PCC_Deploy_FindAuthCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_AddModule_TypeInfo_ = NULL;
static int s_PCC_Deploy_AddModule_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_AddModuleFile_TypeInfo_ = NULL;
static int s_PCC_Deploy_AddModuleFile_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_RemoveModule_TypeInfo_ = NULL;
static int s_PCC_Deploy_RemoveModule_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_RemoveModuleFiles_TypeInfo_ = NULL;
static int s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_ListModules_TypeInfo_ = NULL;
static int s_PCC_Deploy_ListModules_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_AddModel_TypeInfo_ = NULL;
static int s_PCC_Deploy_AddModel_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_ListModels_TypeInfo_ = NULL;
static int s_PCC_Deploy_ListModels_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_DelModel_TypeInfo_ = NULL;
static int s_PCC_Deploy_DelModel_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_SetRedirect__TypeInfo_ = NULL;
static int s_PCC_Deploy_SetRedirect__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_SetTimeout__TypeInfo_ = NULL;
static int s_PCC_Deploy_SetTimeout__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_SetSessionBufferSize__TypeInfo_ = NULL;
static int s_PCC_Deploy_SetSessionBufferSize__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_MethodCheck__TypeInfo_ = NULL;
static int s_PCC_Deploy_MethodCheck__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_CallbackCheck__TypeInfo_ = NULL;
static int s_PCC_Deploy_CallbackCheck__TypeInfo_len_ = 0;

static const char* s_PCC_User_GetPccProperty_TypeInfo_ = NULL;
static int s_PCC_User_GetPccProperty_TypeInfo_len_ = 0;

static const char* s_PCC_User_ListNodes_TypeInfo_ = NULL;
static int s_PCC_User_ListNodes_TypeInfo_len_ = 0;

static const char* s_PCC_User_GetNodeDynamicContext_TypeInfo_ = NULL;
static int s_PCC_User_GetNodeDynamicContext_TypeInfo_len_ = 0;

static const char* s_PCC_User_ListModules_TypeInfo_ = NULL;
static int s_PCC_User_ListModules_TypeInfo_len_ = 0;

static const char* s_PCC_User_Execute_TypeInfo_ = NULL;
static int s_PCC_User_Execute_TypeInfo_len_ = 0;

static const char* s_PCC_User_OnExecuted_TypeInfo_ = NULL;
static int s_PCC_User_OnExecuted_TypeInfo_len_ = 0;

static const char* s_PCC_User_OnExecuted1_TypeInfo_ = NULL;
static int s_PCC_User_OnExecuted1_TypeInfo_len_ = 0;

static const char* s_PCC_User_QueryJobs_TypeInfo_ = NULL;
static int s_PCC_User_QueryJobs_TypeInfo_len_ = 0;

static const char* s_PCC_User_CancelJob_TypeInfo_ = NULL;
static int s_PCC_User_CancelJob_TypeInfo_len_ = 0;

static const char* s_PCC_User_UDPLink__TypeInfo_ = NULL;
static int s_PCC_User_UDPLink__TypeInfo_len_ = 0;

static const char* s_PCC_User_UDPLinkConfirm__TypeInfo_ = NULL;
static int s_PCC_User_UDPLinkConfirm__TypeInfo_len_ = 0;

static const char* s_PCC_User_SetRedirect__TypeInfo_ = NULL;
static int s_PCC_User_SetRedirect__TypeInfo_len_ = 0;

static const char* s_PCC_User_SetTimeout__TypeInfo_ = NULL;
static int s_PCC_User_SetTimeout__TypeInfo_len_ = 0;

static const char* s_PCC_User_SetSessionBufferSize__TypeInfo_ = NULL;
static int s_PCC_User_SetSessionBufferSize__TypeInfo_len_ = 0;

static const char* s_PCC_User_MethodCheck__TypeInfo_ = NULL;
static int s_PCC_User_MethodCheck__TypeInfo_len_ = 0;

static const char* s_PCC_User_CallbackCheck__TypeInfo_ = NULL;
static int s_PCC_User_CallbackCheck__TypeInfo_len_ = 0;

static INT_PTR InitializeAllCallsTypeInfo_()
{
	// BOOL和枚举类型长度必须为4字节（网络协议已规定为固定4字节）
	STATIC_ASSERT(4 == sizeof(BOOL));
	STATIC_ASSERT(4 == sizeof(DummyEnumType));

	BEGIN_LOCAL_SAFE_STATIC_OBJ(INT_PTR, dummyVar);

	{
		BYTE const chZipped[] =
		{
			0x19,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x61,0x00,
			0x00,0x83,0xBD,0x09,0x35,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_AddModelCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_AddModelCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x19,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x61,0x00,
			0x00,0x83,0xBD,0x09,0x35,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_DelModelCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_DelModelCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x0A,0x01,0x00,0x80,0x78,0x01,0x4D,0x4F,0xCB,0x0A,0xC2,0x30,0x10,0xF4,0x5F,0xF4,
			0x98,0x83,0x68,0x29,0x82,0xF4,0x50,0x9A,0xCB,0x82,0x4D,0x42,0x93,0xD0,0xDE,0x42,
			0x1A,0x83,0x8A,0x45,0xC5,0x7A,0x11,0xFA,0xF1,0xE6,0xD1,0x87,0x97,0x61,0xE7,0xB1,
			0xCB,0x2C,0x2B,0x0A,0x55,0x30,0x29,0xBE,0x2F,0xBB,0x66,0x71,0x56,0xCD,0x21,0x55,
			0x4D,0x9A,0x64,0x5B,0x34,0x29,0x79,0x55,0x66,0x33,0x29,0x81,0xF1,0x0C,0x1D,0xBD,
			0x47,0x9E,0x67,0x8B,0x6D,0x6F,0x36,0xFD,0xE7,0x7D,0x7B,0x5C,0xA6,0x88,0xBF,0x86,
			0x80,0x88,0x34,0xF1,0xB8,0xDF,0x2D,0x18,0x15,0x87,0x7E,0x9B,0xF2,0x10,0x1C,0x77,
			0x63,0x32,0x9C,0x8D,0x46,0xE8,0x43,0xB9,0xAA,0x81,0x60,0x5A,0xF3,0xB1,0x8E,0x13,
			0x4E,0x40,0x64,0x13,0xFB,0x38,0x26,0x09,0x2C,0x24,0x27,0xB8,0xA2,0x80,0x67,0x13,
			0xA8,0xAF,0x6A,0xB4,0xB9,0x5A,0xDD,0x76,0x56,0x19,0xDD,0x75,0xAD,0x36,0xF7,0x81,
			0x4A,0x31,0xFC,0x7F,0x80,0x56,0x3F,0x0C,0xE3,0x52,0x1A,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_GetStaticContext_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_GetStaticContext_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x47,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x77,0xA9,0xCC,0x4B,0xCC,0xCD,
			0x4C,0x76,0xCE,0xCF,0x2B,0x49,0xAD,0x28,0x51,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0x41,
			0x26,0xAD,0x93,0x13,0x73,0x72,0x92,0x12,0x93,0xB3,0x6B,0xFC,0x43,0x43,0x6A,0x02,
			0x30,0xB4,0xE8,0x30,0x00,0x00,0x51,0x7B,0x17,0xDB,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_GetDynamicContext_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_GetDynamicContext_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xB8,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x49,0xCD,0x71,
			0xCB,0xCC,0x49,0x55,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x49,0xCA,0xCC,0x4B,0x2C,
			0xAA,0xD4,0xB1,0x0E,0x80,0x49,0x06,0x14,0xE5,0x17,0xA4,0x16,0x95,0x54,0xAA,0x80,
			0x44,0x42,0x12,0xD3,0x75,0xA0,0x0A,0x7D,0x42,0x7C,0x83,0x5D,0x7D,0x20,0x0A,0x81,
			0xC2,0x30,0xFD,0x20,0x55,0x61,0xA9,0x45,0xC5,0x99,0xF9,0x79,0x10,0x39,0x28,0x47,
			0xC5,0xD3,0x2F,0xC4,0xD8,0x48,0x07,0x99,0xB4,0x4E,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,
			0xCE,0xAE,0xF1,0xF4,0xAB,0xC1,0xB0,0x0F,0xA8,0xB4,0x26,0xB1,0xA8,0x28,0xB1,0xD2,
			0x06,0x2E,0x05,0x72,0xA7,0x9D,0x0E,0x03,0x00,0x12,0xE2,0x3F,0x3A,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_AddModel_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_AddModel_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x50,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x49,0x4C,0x57,0x29,0x2E,
			0x29,0xCA,0xCC,0x4B,0xD7,0x09,0x00,0x72,0xC3,0x52,0x8B,0x8A,0x33,0xF3,0xF3,0x74,
			0xAC,0x91,0x38,0x2A,0x9E,0x7E,0x21,0xC6,0x46,0x3A,0xC8,0xA4,0x75,0x72,0x62,0x4E,
			0x4E,0x52,0x62,0x72,0x76,0x8D,0xA7,0x5F,0x0D,0x48,0x29,0xD0,0x18,0x1D,0x06,0x00,
			0x34,0xB0,0x19,0xE2,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_DelModel_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_DelModel_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x1C,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0x0F,0x0D,
			0xA9,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0x41,0xB0,0x18,0x00,0x91,0x83,0x08,0xDE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_UDPLink__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_UDPLink__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x08,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0x61,0x00,0x00,
			0x0E,0xD3,0x02,0xFE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_UDPLinkConfirm__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_UDPLinkConfirm__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x23,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x01,0x52,
			0x49,0x99,0x79,0x89,0x45,0x95,0x3A,0x0C,0x00,0xF8,0x4D,0x0C,0xF9,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_SetRedirect__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_SetRedirect__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_SetTimeout__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_SetTimeout__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_SetSessionBufferSize__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_SetSessionBufferSize__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3A,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,0xC1,0x10,
			0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,0x9A,0x78,
			0x15,0x41,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_MethodCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_MethodCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3C,0x00,0x00,0x80,0x78,0x01,0x4B,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,
			0xF4,0xAB,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,
			0xC1,0x10,0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,
			0xC2,0xD8,0x15,0xED,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_CallbackCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_CallbackCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x12,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x61,0x00,0x00,0x46,0x0C,0x06,0xD4,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_Login_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_Login_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x08,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0x61,0x00,0x00,
			0x0E,0xD3,0x02,0xFE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_Logout_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_Logout_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x12,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x61,0x00,0x00,0x46,0x0C,0x06,0xD4,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_CreateTrunk_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_CreateTrunk_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x12,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x61,0x00,0x00,0x46,0x0C,0x06,0xD4,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_RemoveTrunk_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_RemoveTrunk_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x1A,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0x0F,0x0D,
			0xA9,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,0x61,
			0x00,0x00,0x8D,0xB9,0x09,0xCE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_ListTrunk_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_ListTrunk_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x94,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x29,0xCD,0x49,
			0x75,0xCB,0xCC,0x49,0x55,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x49,0xCA,0xCC,0x4B,
			0x2C,0xAA,0xD4,0x71,0xF2,0xF7,0xF7,0xD1,0xB1,0x0E,0x00,0x2A,0x09,0x49,0x4C,0x87,
			0xC9,0x81,0xB8,0x61,0xA9,0x45,0xC5,0x99,0xF9,0x79,0x10,0x39,0x28,0x47,0xC5,0xD3,
			0x2F,0xC4,0xD8,0x48,0x07,0x99,0xB4,0xCE,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,
			0xAB,0x81,0x1A,0x0C,0x64,0x41,0x8D,0x03,0x2A,0xAC,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,
			0x01,0x09,0x20,0x9C,0x60,0xA7,0xC3,0x00,0x00,0xC2,0x86,0x32,0x45,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_AddAuthCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_AddAuthCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x58,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x49,0x4C,0x57,0x29,0x2E,
			0x29,0xCA,0xCC,0x4B,0xD7,0x09,0x00,0x72,0xC3,0x52,0x8B,0x8A,0x33,0xF3,0xF3,0x74,
			0xAC,0x91,0x38,0x2A,0x9E,0x7E,0x21,0xC6,0x46,0x3A,0xC8,0xA4,0x75,0x6E,0x6A,0x49,
			0x46,0x7E,0x4A,0x8D,0xA7,0x5F,0x0D,0x54,0x33,0x90,0x05,0xD2,0x02,0x34,0x4E,0x87,
			0x01,0x00,0x1D,0x3E,0x1D,0x0C,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_RemoveAuthCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x60,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x49,0x4C,0x57,0x29,0x2E,
			0x29,0xCA,0xCC,0x4B,0xD7,0x09,0x00,0x72,0xC3,0x52,0x8B,0x8A,0x33,0xF3,0xF3,0x74,
			0xAC,0x91,0x38,0x2A,0x9E,0x7E,0x21,0xC6,0x46,0x3A,0xC8,0xA4,0x75,0x6E,0x6A,0x49,
			0x46,0x7E,0x4A,0x8D,0xA7,0x5F,0x0D,0x54,0xB3,0x7F,0x68,0x48,0x4D,0x62,0x51,0x51,
			0x62,0xA5,0x0D,0x48,0x27,0xD0,0x54,0x3B,0x1D,0x06,0x00,0x1B,0x60,0x20,0x06,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_ListAuthCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_ListAuthCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x58,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x49,0x4C,0x57,0x29,0x2E,
			0x29,0xCA,0xCC,0x4B,0xD7,0x09,0x00,0x72,0xC3,0x52,0x8B,0x8A,0x33,0xF3,0xF3,0x74,
			0xAC,0x91,0x38,0x2A,0x9E,0x7E,0x21,0xC6,0x46,0x3A,0xC8,0xA4,0x75,0x6E,0x6A,0x49,
			0x46,0x7E,0x4A,0x8D,0xA7,0x5F,0x0D,0x54,0x33,0x90,0x05,0xD2,0x02,0x34,0x4E,0x87,
			0x01,0x00,0x1D,0x3E,0x1D,0x0C,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_FindAuthCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_FindAuthCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x5C,0x01,0x00,0x80,0x78,0x01,0x65,0x90,0x4F,0x0B,0x82,0x40,0x10,0xC5,0xFB,0x2E,
			0x79,0x9C,0x43,0x59,0x74,0x31,0x03,0x13,0x0B,0x61,0x75,0x45,0xB7,0xA0,0x93,0x6C,
			0xB9,0x98,0x60,0x1A,0xEB,0x76,0x10,0xFC,0xF0,0xED,0x96,0x7F,0xF1,0xB2,0x30,0xBF,
			0x99,0xF7,0xE6,0xCD,0x06,0xB6,0x1D,0x7B,0x65,0xF2,0xC9,0xD9,0x29,0xCB,0x99,0x56,
			0x09,0x9E,0x15,0x29,0xDC,0xB3,0x82,0xF2,0x1A,0x8E,0x18,0x23,0x30,0x82,0x7E,0x04,
			0x51,0xC1,0x8A,0x47,0xBD,0x54,0x04,0x59,0xC4,0xF1,0xED,0x5B,0x1C,0x79,0x16,0x42,
			0xE6,0x0A,0xC6,0xCC,0xC7,0xA1,0xA4,0xE6,0x7A,0x02,0x91,0x15,0x9E,0x1D,0x53,0x1F,
			0xFB,0x05,0xBC,0x7C,0x33,0x2E,0x6A,0x4D,0x89,0x09,0x4D,0xC1,0xF5,0xC9,0x46,0x9F,
			0xBC,0xB3,0xE5,0xD0,0x46,0x94,0xA3,0xBB,0x2D,0x20,0xE2,0x45,0x0E,0x52,0x0A,0x59,
			0xFC,0x92,0x4A,0x9B,0xEE,0x0A,0xA5,0xBD,0x32,0x5E,0x65,0x65,0xF1,0xEF,0xB5,0x85,
			0x36,0x5F,0x63,0xBC,0x98,0x78,0x96,0x49,0xE3,0xFA,0x4D,0xEF,0x2F,0x0B,0xE5,0x2A,
			0xD1,0x10,0xA2,0x4B,0xAC,0x28,0xE5,0x9C,0xD6,0xFB,0xA1,0xA7,0x3E,0xF0,0x00,0xF8,
			0x42,0x5A,0xE1,0xE2,0x0B,0xD3,0xC0,0x71,0x56,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_AddModule_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_AddModule_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xC1,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x29,0xCD,0x49,
			0x75,0xCB,0xCC,0x49,0x55,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x49,0xCA,0xCC,0x4B,
			0x2C,0xAA,0xD4,0x71,0xF2,0xF7,0xF7,0xD1,0xB1,0x0E,0x40,0x51,0x12,0x52,0x59,0x90,
			0xAA,0x0C,0x16,0xF2,0x77,0x09,0xF5,0x71,0x8D,0xF7,0x75,0x74,0xF6,0xF0,0xF4,0x73,
			0x8D,0x0F,0x72,0x0C,0xB7,0x35,0xD4,0x41,0x92,0x70,0xF6,0xF7,0x0B,0x09,0xF2,0xF7,
			0xB1,0x35,0x42,0x16,0xF4,0x08,0xF1,0xF5,0xB1,0x35,0xD1,0xB1,0xCE,0x4D,0x2D,0xC9,
			0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,0x81,0xDA,0x08,0x64,0x79,0xFA,0x85,0x98,0x99,0xE8,
			0x00,0x19,0x98,0x16,0x82,0x44,0x13,0x8B,0x8A,0x12,0x2B,0x6D,0x50,0xE5,0xEC,0x74,
			0x18,0x00,0x48,0x5C,0x40,0x2C,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_AddModuleFile_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_AddModuleFile_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x1B,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x01,0xB2,0x3C,0xFD,0x42,0xCC,0x4C,0x74,0x18,
			0x00,0x94,0x3B,0x09,0x68,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_RemoveModule_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_RemoveModule_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x24,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x01,0xB2,0x3C,0xFD,0x42,0xCC,0x4C,0xA0,0x0C,
			0x63,0x23,0x1D,0x06,0x00,0xF9,0x8C,0x0B,0xF7,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_RemoveModuleFiles_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x4E,0x01,0x00,0x80,0x78,0x01,0x5D,0x8F,0x4D,0x0B,0x82,0x30,0x18,0xC7,0xFB,0x2E,
			0x79,0xDC,0xA1,0x2C,0xBA,0x98,0x81,0x0C,0x09,0x69,0x4E,0xD1,0x55,0x74,0x92,0x91,
			0x23,0x85,0x72,0x31,0xD7,0x61,0xE0,0x87,0x6F,0xD3,0x81,0x2F,0x97,0x07,0xF6,0xE3,
			0xFF,0xB6,0x14,0xC2,0x22,0xE6,0xE5,0xEF,0xCD,0x10,0x95,0xAC,0x79,0xAA,0x75,0xAA,
			0x09,0x0A,0x48,0x88,0xE1,0xA3,0xC8,0xE3,0x00,0x21,0x7F,0x03,0xA6,0x0C,0x27,0x99,
			0xA6,0xFE,0x76,0x06,0x51,0x90,0x9D,0x43,0xDF,0x05,0x9E,0x51,0x0E,0x79,0xA9,0xE0,
			0xDF,0x7B,0x2D,0xAB,0x0B,0x53,0x4E,0x84,0xC9,0x61,0x0F,0x86,0x3B,0x57,0x30,0x21,
			0xD5,0xD2,0x65,0x98,0x63,0x64,0x84,0xBE,0x8C,0x69,0xE7,0xCE,0xEE,0x18,0x60,0x27,
			0x83,0x56,0x8A,0xBA,0xE9,0xA5,0xBA,0x05,0x91,0x38,0x0F,0x91,0x2D,0xEB,0xF7,0xE8,
			0x18,0xC7,0x4A,0x8C,0xF7,0xC6,0x44,0x5B,0xF3,0x66,0x68,0xB5,0x0F,0xB3,0x70,0x51,
			0xE3,0x7D,0x98,0xAC,0x78,0xD9,0x45,0xB8,0xB3,0xE6,0xE4,0x4A,0x3A,0x2A,0x04,0x55,
			0xC7,0x71,0xC2,0xE4,0x97,0x27,0xB0,0xFA,0x03,0x33,0x92,0x6D,0x1D,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_ListModules_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_ListModules_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xB6,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x49,0xCD,0x71,
			0xCB,0xCC,0x49,0x55,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x49,0xCA,0xCC,0x4B,0x2C,
			0xAA,0xD4,0xB1,0x0E,0x80,0x49,0x06,0x14,0xE5,0x17,0xA4,0x16,0x95,0x54,0xAA,0x80,
			0x44,0x42,0x12,0xD3,0x75,0xA0,0x0A,0x7D,0x42,0x7C,0x83,0x5D,0x7D,0x20,0x0A,0x81,
			0xC2,0x30,0xFD,0x20,0x55,0x61,0xA9,0x45,0xC5,0x99,0xF9,0x79,0x10,0x39,0x28,0x47,
			0xC5,0xD3,0x2F,0xC4,0xD8,0x48,0x07,0x99,0xB4,0xCE,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,
			0xF1,0xF4,0xAB,0xC1,0xB0,0x0D,0xA8,0xB0,0x26,0xB1,0xA8,0x28,0xB1,0xD2,0x06,0x2E,
			0x05,0x72,0xA5,0x9D,0x0E,0x03,0x00,0x97,0x3F,0x3E,0x8E,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_AddModel_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_AddModel_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xBA,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x49,0xCD,0x09,
			0x28,0xCA,0x2F,0x08,0xCF,0x2C,0xC9,0xF0,0x4E,0xAD,0x54,0xF1,0xF4,0x0B,0x31,0x33,
			0xD1,0x09,0x40,0x96,0x4A,0x2D,0x2A,0xA9,0xD4,0xB1,0xC6,0x10,0x52,0x01,0x89,0x84,
			0x24,0xA6,0xEB,0x14,0x97,0x14,0x65,0xE6,0xA5,0xEB,0xF8,0x84,0xF8,0x06,0xBB,0xFA,
			0x40,0x14,0x02,0x85,0x55,0xA0,0xC2,0x20,0x55,0x61,0xA9,0x45,0xC5,0x99,0xF9,0x79,
			0x10,0x39,0x28,0x07,0x64,0x93,0xB1,0x91,0x0E,0x32,0x69,0x9D,0x9B,0x5A,0x92,0x91,
			0x9F,0x52,0xE3,0x1F,0x1A,0x52,0x93,0x58,0x54,0x94,0x58,0x69,0x83,0x62,0x29,0xD4,
			0x89,0x76,0x3A,0x0C,0x00,0x79,0x6D,0x3F,0xB5,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_ListModels_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_ListModels_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x11,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,
			0xA2,0x10,0x33,0x13,0x1D,0x06,0x00,0x3A,0x7C,0x05,0x92,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_DelModel_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_DelModel_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x23,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x01,0x52,
			0x49,0x99,0x79,0x89,0x45,0x95,0x3A,0x0C,0x00,0xF8,0x4D,0x0C,0xF9,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_SetRedirect__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_SetRedirect__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_SetTimeout__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_SetTimeout__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_SetSessionBufferSize__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_SetSessionBufferSize__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3A,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,0xC1,0x10,
			0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,0x9A,0x78,
			0x15,0x41,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_MethodCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_MethodCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3C,0x00,0x00,0x80,0x78,0x01,0x4B,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,
			0xF4,0xAB,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,
			0xC1,0x10,0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,
			0xC2,0xD8,0x15,0xED,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_CallbackCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_CallbackCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x36,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x2D,0x4E,0x2D,0xB2,0xB2,
			0x0A,0x70,0x76,0x0E,0x28,0xCA,0x2F,0x48,0x2D,0x2A,0xA9,0x54,0x29,0x2E,0x29,0xCA,
			0xCC,0x4B,0xD7,0xB1,0xCE,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0x0F,0x0D,0xA9,0x41,
			0x92,0xD6,0x61,0x00,0x00,0x15,0xA5,0x13,0x7E,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_GetPccProperty_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_GetPccProperty_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x05,0x01,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x77,0x0E,0x08,0x0D,0xA9,0x2C,
			0x48,0x55,0x0E,0x80,0xB0,0xE3,0x23,0x2C,0xCC,0xE2,0x23,0xCC,0x4C,0x6C,0x0D,0x74,
			0x60,0x22,0x8E,0x41,0xBE,0xB6,0x70,0x8E,0xAF,0x67,0x40,0xB0,0xAD,0x8E,0x35,0x48,
			0xCE,0x2F,0x3F,0x25,0xD5,0x25,0xB5,0x38,0x59,0xA5,0xB8,0xA4,0x28,0x33,0x2F,0x1D,
			0xA6,0x04,0x64,0x9A,0x8E,0xA7,0x5F,0x88,0x99,0x09,0x88,0x34,0x36,0x42,0x90,0x10,
			0x11,0x20,0x09,0xD2,0xED,0x1F,0x0C,0x56,0x08,0xD5,0x0B,0x51,0x09,0x36,0x16,0x22,
			0x01,0x76,0x8F,0x7F,0x70,0x7C,0xB8,0xA7,0x9F,0x8B,0x7F,0x78,0x30,0xD4,0x39,0x40,
			0x01,0x1F,0x4F,0xBF,0xD0,0x08,0x88,0x7B,0x80,0xBC,0x50,0x3F,0x4F,0x04,0xC7,0xD1,
			0xCF,0x25,0xC8,0xDF,0xD3,0x05,0x2E,0xE9,0xE9,0x0F,0x72,0x6A,0x6E,0x6A,0x49,0x46,
			0x7E,0x4A,0x8D,0x7F,0x68,0x48,0x4D,0x62,0x51,0x51,0x62,0xA5,0x0D,0xB2,0xDB,0xED,
			0x74,0x18,0x00,0x74,0x50,0x50,0x20,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_ListNodes_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_ListNodes_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x4F,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x77,0xA9,0xCC,0x4B,0xCC,0xCD,
			0x4C,0x76,0xCE,0xCF,0x2B,0x49,0xAD,0x28,0x51,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0x41,
			0x26,0xAD,0x73,0x53,0x4B,0x32,0xF2,0x53,0x6A,0x3C,0xFD,0x6A,0x8A,0x4B,0x8A,0x32,
			0xF3,0xD2,0x75,0xFC,0x43,0x43,0x6A,0x02,0x30,0xB4,0xEA,0x30,0x00,0x00,0x28,0x51,
			0x1B,0x05,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_GetNodeDynamicContext_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_GetNodeDynamicContext_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xB1,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x29,0xCD,0x49,
			0xF5,0xCC,0x4B,0xCB,0x57,0xF1,0xF4,0x0B,0x31,0x33,0xD1,0x09,0x00,0x0A,0x86,0x24,
			0xA6,0xEB,0x00,0x79,0xC6,0x46,0x50,0xB2,0xB8,0xA4,0x28,0x33,0x0F,0x55,0xC8,0x27,
			0xC4,0x37,0xD8,0xD5,0x07,0x24,0x0F,0xD4,0x63,0x0D,0xD5,0xA4,0x02,0x55,0x08,0xE2,
			0x86,0xA5,0x16,0x15,0x67,0xE6,0xE7,0x41,0xE4,0xA0,0x1C,0x90,0x15,0x70,0x43,0x21,
			0x6C,0xEB,0xDC,0xD4,0x92,0x8C,0xFC,0x94,0x1A,0x4F,0xBF,0x1A,0xA8,0x66,0xFF,0xD0,
			0x90,0x9A,0xC4,0xA2,0xA2,0xC4,0x4A,0x1B,0x90,0x31,0x08,0xF7,0xD9,0xE9,0x30,0x00,
			0x00,0x21,0xEA,0x38,0x91,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_ListModules_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_ListModules_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x39,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,
			0xA2,0x10,0x33,0x13,0x1D,0x20,0xA3,0xB8,0xA4,0x28,0x33,0x2F,0x1D,0x95,0x95,0x94,
			0x99,0x97,0x58,0x54,0xA9,0xE3,0x1F,0x1A,0x02,0x55,0xC7,0x00,0x00,0x5E,0xC4,0x13,
			0xF7,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_Execute_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_Execute_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x2E,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0x03,0xA2,0x10,0x33,0x13,0x1D,0x20,
			0x23,0xB5,0xA8,0x28,0xBF,0x08,0xC4,0x48,0xCA,0xCC,0x4B,0x2C,0xAA,0xD4,0x61,0x00,
			0x00,0x9D,0x70,0x10,0xCE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_OnExecuted_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_OnExecuted_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3F,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0x03,0xA2,0x10,0x33,0x13,0x1D,0x20,
			0x23,0xB5,0xA8,0x28,0xBF,0x08,0xC4,0x48,0xCA,0xCC,0x4B,0x2C,0xAA,0x04,0xB1,0x12,
			0x8B,0x8A,0x12,0x2B,0x6D,0x20,0x7C,0x3B,0x1D,0x06,0x00,0xFC,0x3B,0x17,0x2B,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_OnExecuted1_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_OnExecuted1_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x44,0x00,0x00,0x80,0x78,0x01,0x73,0xAD,0x48,0x4D,0x2E,0x2D,0x49,0x0D,0x2E,0x49,
			0x2C,0x49,0x55,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0xB1,0xCE,0x4D,0x2D,0xC9,0xC8,0x4F,
			0xA9,0xF1,0xF4,0xAB,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x01,0x0A,0x9B,0x99,0xD8,0xE9,
			0xF8,0x87,0x86,0x40,0x05,0x5C,0x91,0x34,0xD9,0xE9,0x30,0x00,0x00,0x43,0xDB,0x17,
			0xE7,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_QueryJobs_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_QueryJobs_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x19,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x33,0x13,0x1D,0x06,0x00,0x83,
			0xB1,0x08,0xF5,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_CancelJob_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_CancelJob_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x1C,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0x0F,0x0D,
			0xA9,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0x41,0xB0,0x18,0x00,0x91,0x83,0x08,0xDE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_UDPLink__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_UDPLink__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x08,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0x61,0x00,0x00,
			0x0E,0xD3,0x02,0xFE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_UDPLinkConfirm__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_UDPLinkConfirm__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x23,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x01,0x52,
			0x49,0x99,0x79,0x89,0x45,0x95,0x3A,0x0C,0x00,0xF8,0x4D,0x0C,0xF9,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_SetRedirect__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_SetRedirect__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_SetTimeout__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_SetTimeout__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_SetSessionBufferSize__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_SetSessionBufferSize__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3A,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,0xC1,0x10,
			0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,0x9A,0x78,
			0x15,0x41,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_MethodCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_MethodCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3C,0x00,0x00,0x80,0x78,0x01,0x4B,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,
			0xF4,0xAB,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,
			0xC1,0x10,0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,
			0xC2,0xD8,0x15,0xED,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_CallbackCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_CallbackCheck__TypeInfo_len_ = bin.Length()-1;
	}

	END_LOCAL_SAFE_STATIC_OBJ(dummyVar);
}

struct PCC_Center_AllMethodCallsTypeInfo_
{
	const char* typeInfos[24];
};
static PCC_Center_AllMethodCallsTypeInfo_& PCC_Center_GetAllMethodCallsTypeInfo_Impl_(
				OUT INT_PTR& methods
				)
{
	methods = 24;
	BEGIN_LOCAL_SAFE_STATIC_OBJ(PCC_Center_AllMethodCallsTypeInfo_, infosObj);
	InitializeAllCallsTypeInfo_();
	infosObj.typeInfos[0] = s_PCC_Deploy_Login_TypeInfo_;
	infosObj.typeInfos[1] = s_PCC_Deploy_Logout_TypeInfo_;
	infosObj.typeInfos[2] = s_PCC_Deploy_CreateTrunk_TypeInfo_;
	infosObj.typeInfos[3] = s_PCC_Deploy_RemoveTrunk_TypeInfo_;
	infosObj.typeInfos[4] = s_PCC_Deploy_ListTrunk_TypeInfo_;
	infosObj.typeInfos[5] = s_PCC_Deploy_AddAuthCenter_TypeInfo_;
	infosObj.typeInfos[6] = s_PCC_Deploy_RemoveAuthCenter_TypeInfo_;
	infosObj.typeInfos[7] = s_PCC_Deploy_ListAuthCenter_TypeInfo_;
	infosObj.typeInfos[8] = s_PCC_Deploy_FindAuthCenter_TypeInfo_;
	infosObj.typeInfos[9] = s_PCC_Deploy_AddModule_TypeInfo_;
	infosObj.typeInfos[10] = s_PCC_Deploy_AddModuleFile_TypeInfo_;
	infosObj.typeInfos[11] = s_PCC_Deploy_RemoveModule_TypeInfo_;
	infosObj.typeInfos[12] = s_PCC_Deploy_RemoveModuleFiles_TypeInfo_;
	infosObj.typeInfos[13] = s_PCC_Deploy_ListModules_TypeInfo_;
	infosObj.typeInfos[14] = s_PCC_Deploy_AddModel_TypeInfo_;
	infosObj.typeInfos[15] = s_PCC_Deploy_ListModels_TypeInfo_;
	infosObj.typeInfos[16] = s_PCC_Deploy_DelModel_TypeInfo_;
	infosObj.typeInfos[17] = s_PCC_User_GetPccProperty_TypeInfo_;
	infosObj.typeInfos[18] = s_PCC_User_ListNodes_TypeInfo_;
	infosObj.typeInfos[19] = s_PCC_User_GetNodeDynamicContext_TypeInfo_;
	infosObj.typeInfos[20] = s_PCC_User_ListModules_TypeInfo_;
	infosObj.typeInfos[21] = s_PCC_User_Execute_TypeInfo_;
	infosObj.typeInfos[22] = s_PCC_User_QueryJobs_TypeInfo_;
	infosObj.typeInfos[23] = s_PCC_User_CancelJob_TypeInfo_;
	END_LOCAL_SAFE_STATIC_OBJ(infosObj);
}
const char** PCC_Center_GetAllMethodCallsTypeInfo_(
				OUT INT_PTR& methods
				)
{
	PCC_Center_AllMethodCallsTypeInfo_& infosObj = PCC_Center_GetAllMethodCallsTypeInfo_Impl_(methods);
	return infosObj.typeInfos;
}

const char* PCC_Center_GetCallbackCallTypeInfo_(
				IN const char* faceName,
				IN const char* callbackName
				)
{
	if(NULL==faceName || NULL==callbackName)
	{
		ASSERT(false);
		return "";
	}
	InitializeAllCallsTypeInfo_();

	if(0 == strcmp("PCC_Center", faceName))
	{
		if(0 == strcmp("AddModelCenter", callbackName))
			return s_PCC_Center_AddModelCenter_TypeInfo_;
		else if(0 == strcmp("DelModelCenter", callbackName))
			return s_PCC_Center_DelModelCenter_TypeInfo_;
		else if(0 == strcmp("GetStaticContext", callbackName))
			return s_PCC_Center_GetStaticContext_TypeInfo_;
		else if(0 == strcmp("GetDynamicContext", callbackName))
			return s_PCC_Center_GetDynamicContext_TypeInfo_;
		else if(0 == strcmp("AddModel", callbackName))
			return s_PCC_Center_AddModel_TypeInfo_;
		else if(0 == strcmp("DelModel", callbackName))
			return s_PCC_Center_DelModel_TypeInfo_;
	}

	else if(0 == strcmp("PCC_Deploy", faceName))
	{
	}

	else if(0 == strcmp("PCC_User", faceName))
	{
		if(0 == strcmp("OnExecuted", callbackName))
			return s_PCC_User_OnExecuted_TypeInfo_;
		else if(0 == strcmp("OnExecuted1", callbackName))
			return s_PCC_User_OnExecuted1_TypeInfo_;
	}

	return "";
}

TCPSError MakeLocalSession_PCC_Center__(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_Center_LocalMethod*& methodHandler,
			IN IPCC_Center_LocalCallback* callbackHandler
			);
TCPSError MakeLocalSession_PCC_Deploy__(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_Deploy_LocalMethod*& methodHandler,
			IN IPCC_Deploy_LocalCallback* callbackHandler
			);
TCPSError MakeLocalSession_PCC_User__(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_User_LocalMethod*& methodHandler,
			IN IPCC_User_LocalCallback* callbackHandler
			);

static void RegisterLocalSessionMakeFunction_(const IPP& serveIPP, PCC_CenterSessionMaker& sessionMaker)
{
	NPR_ASSERT(TCPS_OK == iscm_RegisterFunction(serveIPP, "MakeLocalSession_PCC_Center", (PROC)MakeLocalSession_PCC_Center__, &sessionMaker));
	NPR_ASSERT(TCPS_OK == iscm_RegisterFunction(serveIPP, "MakeLocalSession_PCC_Deploy", (PROC)MakeLocalSession_PCC_Deploy__, &sessionMaker));
	NPR_ASSERT(TCPS_OK == iscm_RegisterFunction(serveIPP, "MakeLocalSession_PCC_User", (PROC)MakeLocalSession_PCC_User__, &sessionMaker));
}

static void UnregisterLocalSessionMakeFunction_(const IPP& serveIPP)
{
	NPR_ASSERT(TCPS_OK == iscm_UnregisterFunction(serveIPP, "MakeLocalSession_PCC_Center"));
	NPR_ASSERT(TCPS_OK == iscm_UnregisterFunction(serveIPP, "MakeLocalSession_PCC_Deploy"));
	NPR_ASSERT(TCPS_OK == iscm_UnregisterFunction(serveIPP, "MakeLocalSession_PCC_User"));
}
//[[end_method_wrap_body]]

#if defined(_MSC_VER)
	#pragma warning(default: 4702) // unreachable code
#endif

TCPSError PCC_CenterSession::Wrap_PCC_Center_UDPLink_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Center_S::UDPLink_() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT INT32 servePort;
		OUT INT32 linkKey;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Center_S* pCC_CenterObj_wrap;
		if(thisObj)
			pCC_CenterObj_wrap = thisObj->m_pCC_Center;
		else
			pCC_CenterObj_wrap = (PCC_Center_S*)faceObj;
		ASSERT(pCC_CenterObj_wrap);
		errTcps = pCC_CenterObj_wrap->UDPLink_(
			opWrapper->servePort,
			opWrapper->linkKey
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Center_S::UDPLink_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Center_S::UDPLink_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT INT32 servePort
	OUT const INT32& servePort_wrap = opWrapper->servePort;
	Set_BaseType_(outfiter, servePort_wrap);

	// OUT INT32 linkKey
	OUT const INT32& linkKey_wrap = opWrapper->linkKey;
	Set_BaseType_(outfiter, linkKey_wrap);

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Center_UDPLinkConfirm_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Center_S::UDPLinkConfirm_() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Center_S* pCC_CenterObj_wrap;
		if(thisObj)
			pCC_CenterObj_wrap = thisObj->m_pCC_Center;
		else
			pCC_CenterObj_wrap = (PCC_Center_S*)faceObj;
		ASSERT(pCC_CenterObj_wrap);
		errTcps = pCC_CenterObj_wrap->UDPLinkConfirm_(
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Center_S::UDPLinkConfirm_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Center_S::UDPLinkConfirm_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Center_SetTimeout_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT32 recvTimeout
	IN INT32 recvTimeout_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, recvTimeout_wrap);

	// IN INT32 sendTimeout
	IN INT32 sendTimeout_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, sendTimeout_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Center_S::SetTimeout_() posting_method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Center_S* pCC_CenterObj_wrap;
		if(thisObj)
			pCC_CenterObj_wrap = thisObj->m_pCC_Center;
		else
			pCC_CenterObj_wrap = (PCC_Center_S*)faceObj;
		ASSERT(pCC_CenterObj_wrap);
		errTcps = pCC_CenterObj_wrap->SetTimeout_(
			recvTimeout_wrap,
			sendTimeout_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Center_S::SetTimeout_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Center_S::SetTimeout_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Center_SetSessionBufferSize_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT32 recvBufBytes
	IN INT32 recvBufBytes_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, recvBufBytes_wrap);

	// IN INT32 sendBufBytes
	IN INT32 sendBufBytes_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, sendBufBytes_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Center_S::SetSessionBufferSize_() posting_method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Center_S* pCC_CenterObj_wrap;
		if(thisObj)
			pCC_CenterObj_wrap = thisObj->m_pCC_Center;
		else
			pCC_CenterObj_wrap = (PCC_Center_S*)faceObj;
		ASSERT(pCC_CenterObj_wrap);
		errTcps = pCC_CenterObj_wrap->SetSessionBufferSize_(
			recvBufBytes_wrap,
			sendBufBytes_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Center_S::SetSessionBufferSize_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Center_S::SetSessionBufferSize_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Center_MethodCheck_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_Array<tcps_String> methods
	IN tcps_Array<tcps_String> methods_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	methods_wrap.Resize(array_len);
	for(int idx1=0; idx1<methods_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = methods_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	// IN tcps_Array<tcps_String> methodTypeInfos
	IN tcps_Array<tcps_String> methodTypeInfos_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	methodTypeInfos_wrap.Resize(array_len);
	for(int idx1=0; idx1<methodTypeInfos_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = methodTypeInfos_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Center_S::MethodCheck_() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<BOOL> matchingFlags;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Center_S* pCC_CenterObj_wrap;
		if(thisObj)
			pCC_CenterObj_wrap = thisObj->m_pCC_Center;
		else
			pCC_CenterObj_wrap = (PCC_Center_S*)faceObj;
		ASSERT(pCC_CenterObj_wrap);
		errTcps = pCC_CenterObj_wrap->MethodCheck_(
			methods_wrap,
			methodTypeInfos_wrap,
			opWrapper->matchingFlags
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Center_S::MethodCheck_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Center_S::MethodCheck_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<BOOL> matchingFlags
	OUT const tcps_Array<BOOL>& matchingFlags_wrap = opWrapper->matchingFlags;
	Set_PODArray_(outfiter, matchingFlags_wrap);

	return TCPS_OK;
}

PCC_Center_S::CallbackMatchingFlag::CallbackMatchingFlag()
{
	Reset();
	cbmap_.insert(std::make_pair(CPtrStrA("AddModelCenter", 14), Info(&matching_AddModelCenter, true)));
	cbmap_.insert(std::make_pair(CPtrStrA("DelModelCenter", 14), Info(&matching_DelModelCenter, true)));
	cbmap_.insert(std::make_pair(CPtrStrA("GetStaticContext", 16), Info(&matching_GetStaticContext, false)));
	cbmap_.insert(std::make_pair(CPtrStrA("GetDynamicContext", 17), Info(&matching_GetDynamicContext, false)));
	cbmap_.insert(std::make_pair(CPtrStrA("AddModel", 8), Info(&matching_AddModel, false)));
	cbmap_.insert(std::make_pair(CPtrStrA("DelModel", 8), Info(&matching_DelModel, false)));
	cbmap_.insert(std::make_pair(CPtrStrA("SetRedirect_", 12), Info(&matching_SetRedirect_, true)));
}

void PCC_Center_S::CallbackMatchingFlag::Reset()
{
	matching_AddModelCenter = false;
	matching_DelModelCenter = false;
	matching_GetStaticContext = false;
	matching_GetDynamicContext = false;
	matching_AddModel = false;
	matching_DelModel = false;
	matching_SetRedirect_ = false;
}

TCPSError PCC_Center_S::UpdateCallbackMatchingFlag_()
{
	if(!m_callbackMatchingUpdatedFlag.needUpdate)
		return TCPS_OK;
	InitializeAllCallsTypeInfo_();
	tcps_String callbacks_ar[7];
	IN tcps_Array<tcps_String> callbacks;
	callbacks.Attach(xat_bind, callbacks_ar, 7);
	tcps_String callbackTypeInfos_ar[7];
	IN tcps_Array<tcps_String> callbackTypeInfos;
	callbackTypeInfos.Attach(xat_bind, callbackTypeInfos_ar, 7);
	callbacks_ar[0].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("AddModelCenter"));
	callbackTypeInfos_ar[0].Attach(xat_bind, (char*)s_PCC_Center_AddModelCenter_TypeInfo_, s_PCC_Center_AddModelCenter_TypeInfo_len_);
	callbacks_ar[1].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("DelModelCenter"));
	callbackTypeInfos_ar[1].Attach(xat_bind, (char*)s_PCC_Center_DelModelCenter_TypeInfo_, s_PCC_Center_DelModelCenter_TypeInfo_len_);
	callbacks_ar[2].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("GetStaticContext"));
	callbackTypeInfos_ar[2].Attach(xat_bind, (char*)s_PCC_Center_GetStaticContext_TypeInfo_, s_PCC_Center_GetStaticContext_TypeInfo_len_);
	callbacks_ar[3].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("GetDynamicContext"));
	callbackTypeInfos_ar[3].Attach(xat_bind, (char*)s_PCC_Center_GetDynamicContext_TypeInfo_, s_PCC_Center_GetDynamicContext_TypeInfo_len_);
	callbacks_ar[4].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("AddModel"));
	callbackTypeInfos_ar[4].Attach(xat_bind, (char*)s_PCC_Center_AddModel_TypeInfo_, s_PCC_Center_AddModel_TypeInfo_len_);
	callbacks_ar[5].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("DelModel"));
	callbackTypeInfos_ar[5].Attach(xat_bind, (char*)s_PCC_Center_DelModel_TypeInfo_, s_PCC_Center_DelModel_TypeInfo_len_);
	callbacks_ar[6].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetRedirect_"));
	callbackTypeInfos_ar[6].Attach(xat_bind, (char*)s_PCC_Center_SetRedirect__TypeInfo_, s_PCC_Center_SetRedirect__TypeInfo_len_);
	OUT tcps_Array<BOOL> matchingFlags;
	TCPSError err = this->CallbackCheck_(callbacks, callbackTypeInfos, matchingFlags);
	if(TCPS_OK == err)
	{
		if(matchingFlags.Length() == callbacks.Length())
		{
			m_callbackMatchingUpdatedFlag.needUpdate = false;
			const BOOL* const matchingFlags_p = matchingFlags.Get();
			m_callbackMatchingFlag.matching_AddModelCenter = matchingFlags_p[0];
			m_callbackMatchingFlag.matching_DelModelCenter = matchingFlags_p[1];
			m_callbackMatchingFlag.matching_GetStaticContext = matchingFlags_p[2];
			m_callbackMatchingFlag.matching_GetDynamicContext = matchingFlags_p[3];
			m_callbackMatchingFlag.matching_AddModel = matchingFlags_p[4];
			m_callbackMatchingFlag.matching_DelModel = matchingFlags_p[5];
			m_callbackMatchingFlag.matching_SetRedirect_ = matchingFlags_p[6];
		}
		else
		{
			ASSERT(false);
			err = TCPS_ERR_MALFORMED_REPLY;
		}
	}
	if(m_callbackMatchingUpdatedFlag.needUpdate)
		m_callbackMatchingFlag.Reset();
	return err;
}

const PCC_Center_S::CallbackMatchingFlag& PCC_Center_S::GetCallbackMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	TCPSError ret = UpdateCallbackMatchingFlag_();
	if(err)
		*err = ret;
	return m_callbackMatchingFlag;
}

TCPSError PCC_Center_S::OnStreamedCall_L_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	INT_PTR inParamsDataLen = sizeof(iscm_PeerCallFlags);
	inParamsDataLen += 12; // "PCC_Center::"
	if(nameLen < 0)
		nameLen = strlen(methodName);
	inParamsDataLen += sizeof(INT32)+nameLen+1;
	inParamsDataLen += dataLen;
	BYTE* const inParamsData = (BYTE*)tcps_Alloc(inParamsDataLen);
	if(NULL == inParamsData)
		return TCPS_ERR_OUT_OF_MEMORY;

	BYTE* p = inParamsData;
	iscm_PeerCallFlags& peerCallFlags = *(iscm_PeerCallFlags*)p;
	peerCallFlags.sizeofBOOL_req = sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1; // ??
	peerCallFlags.dummy_15 = 0;
	p += sizeof(iscm_PeerCallFlags);
	*(INT32*)p = 12+(INT32)nameLen;
	p += sizeof(INT32);
	strncpy((char*)p, "PCC_Center::", 12);
	p += 12;
	strncpy((char*)p, methodName, nameLen);
	p += nameLen;
	*(char*)p = 0;
	p += 1;
	memcpy(p, data, dataLen);
	p += dataLen;
	ASSERT(p-inParamsData == inParamsDataLen);

	BOOL requireReplyData = true;
	BOOL dataTransferred = false;
	iscm_RPCDataOutfiter outfiter;
	ASSERT(NULL==m_sessionR && m_sessionL);
	TCPSError err = PCC_CenterSession::OnRPCCall_(NULL, this, requireReplyData, inParamsData, dataTransferred, inParamsDataLen, &outfiter);
	tcps_Free(inParamsData);
	if(TCPS_OK != err)
		return err;
	// outfiter.swbBufs_[0]总指向iscm_RPCDataOutfiter::reply_
	// outfiter.swbBufs_[1]为iscm_RPCReplyPrefix replyPrefix
	ASSERT(outfiter.swbBufs_.size()==1 || outfiter.swbBufs_.size()>=2);
	if(outfiter.swbBufs_.size() >= 2)
	{
		ASSERT(replyData && replyLen);
		*replyLen = SockTotalizeWriteBufVec(outfiter.swbBufs_.Get()+2, outfiter.swbBufs_.size()-2);
		*replyData = tcps_Alloc(*replyLen);
		BYTE* q = (BYTE*)*replyData;
		for(INT_PTR i=2; i<(INT_PTR)outfiter.swbBufs_.size(); ++i)
		{
			const SockWriteBuf& swb = outfiter.swbBufs_[i];
			memcpy(q, swb.data, swb.len);
			q += swb.len;
		}
		ASSERT(q-(BYTE*)*replyData == *replyLen);
	}
	return err;
}

TCPSError PCC_Center_S::StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;
	if(NULL==callbackName || 0==nameLen)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if(nameLen < 0)
		nameLen = strlen(callbackName);

	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnOnStreamedCallback_L_;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("OnStreamedCallback_L_", -1, NULL, 0);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_Center_LocalCallback::FN_OnStreamedCallback_L_)callbackFuncL)(
					m_sessionL,
					callbackName,
					nameLen,
					data,
					dataLen,
					replyData,
					replyLen
					);
	}
	else if(m_sessionR)
	{
		iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
		if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
			return TCPS_ERR_CALLBACK_NOT_READY;
		DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;
		iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
		ASSERT(0 == m_dataOutfiter.bufs_.size());

		TCPSError errUpdate = UpdateCallbackMatchingFlag_();
		if(TCPS_OK != errUpdate)
			return errUpdate;
		CallbackMatchingFlag::CallbackMap::const_iterator itCallback = m_callbackMatchingFlag.cbmap_.find(callbackName, nameLen);
		if(m_callbackMatchingFlag.cbmap_.end() == itCallback)
			return TCPS_ERR_CALLBACK_NOT_MATCH;
		ASSERT(itCallback->second.pMatchingVar);
		if(!*(itCallback->second.pMatchingVar))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

		// 填充基本类型数据到outfiter
		iscm_PeerCallFlags peerCallFlags;
		peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
		peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
		peerCallFlags.requireReply = !(itCallback->second.isPosting);
		peerCallFlags.dummy_15 = 0;
		m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

		INT32 call_id_len = (INT32)(12+nameLen);
		CSmartBuf<char, 256> call_id_buf(call_id_len+1);
		strncpy(call_id_buf.Get(), "PCC_Center::", 12);
		StrAssign(call_id_buf.Get()+12, callbackName, nameLen);
		m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
		m_dataOutfiter.Push(call_id_buf.Get(), call_id_len+1);

		// 填充IN参数到outfiter
		if(dataLen > 0)
			m_dataOutfiter.Push(data, dataLen);

		// 调用PRCCall()
		if(peerCallFlags.requireReply) // callback
		{
			const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
			int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
			int replyBytes = 0;
			TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
			if(TCPS_OK != err)
				return err;

			iscm_RPCReplyPrefix replyPrefix;
			err = m_rpcRequester->RecvD(&replyPrefix, sizeof(replyPrefix));
			if(TCPS_OK != err)
			{
				this->OnNetworkMalformed_();
				return err;
			}

			INT_PTR leftReplyLen = replyBytes - sizeof(replyPrefix);
			ASSERT(leftReplyLen >= 0);
			if(leftReplyLen > 0)
			{
				ASSERT(replyData && replyLen);
				tcps_Binary replied_data;
				if(!replied_data.Resize(leftReplyLen))
				{
					this->OnNetworkMalformed_();
					return err;
				}
				err = m_rpcRequester->RecvD(replied_data.Get(), (int)leftReplyLen);
				if(TCPS_OK != err)
				{
					this->OnNetworkMalformed_();
					return err;
				}
				if(NULL==replyData || NULL==replyLen)
				{
					ASSERT(false);
					return TCPS_ERR_INVALID_PARAM;
				}
				INT32 bytes = 0;
				*replyData = replied_data.Drop(&bytes);
				*replyLen = bytes;
			}
		}
		else // posting callback
		{
			const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
			int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
			if(m_sessionR->m_udpSite.IsLinked())
			{
				int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
				BYTE* p = (BYTE*)tcps_Alloc(total);
				if(NULL == p)
				{
					ASSERT(false);
					return TCPS_ERR_OUT_OF_MEMORY;
				}
				BYTE* q = p;
				for(int i=0; i<reqBufVecCount; ++i)
				{
					const SockWriteBuf& swb = reqBufVec[i];
					memcpy(q, swb.data, swb.len);
					q += swb.len;
				}
				ASSERT((int)(q-p) == total);
				SockWriteBuf swb_udp;
				swb_udp.data = p;
				swb_udp.len = total;
				INT32 sessionID;
				m_rpcRequester->GetPeerSessionKey(sessionID);
				iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
				udpServer.SendSessionData(sessionID, &swb_udp, 1);
			}
			else if(0 != m_sessionR->m_postingProxy.callerKey_)
			{
				INT_PTR queueFullIndexes = -1;
				INT_PTR queueFullCount = 0;
				TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
				if(TCPS_OK != err)
					return err;
				ASSERT(0==queueFullCount || 1==queueFullCount);
				if(1 == queueFullCount)
					return TCPS_ERR_POSTING_PENDING_FULL;
			}
			else
			{
				TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
				if(TCPS_OK != err)
					return err;
			}
		}
	}
	else
	{
		ASSERT(false);
		return TCPS_ERR_INTERNAL_BUG;
	}

	return TCPS_OK;
}

TCPSError PCC_Center_S::AddModelCenter(
				IN const IPP& centerIPP_wrap
				) posting_callback
{
	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnAddModelCenter;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("AddModelCenter", 14, s_PCC_Center_AddModelCenter_TypeInfo_, s_PCC_Center_AddModelCenter_TypeInfo_len_);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_Center_LocalCallback::FN_AddModelCenter)callbackFuncL)(
					m_sessionL,
					centerIPP_wrap
					);
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_AddModelCenter)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 26;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::AddModelCenter", call_id_len+1);

	// 填充IN参数到outfiter

	// IN IPP centerIPP
	Put_BaseType_(&m_dataOutfiter, centerIPP_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_sessionR->m_udpSite.IsLinked())
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID = m_sessionR->GetSessionKey();
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_sessionR->m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_S::AddModelCenter_Batch(
				IN const PPCC_Center_S_* wrap_sessions,
				IN INT_PTR wrap_sessionsCount,
				IN const IPP& centerIPP_wrap,
				OUT PPCC_Center_S_* wrap_sendFaileds /*= NULL*/,
				OUT INT_PTR* wrap_failedCount /*= NULL*/
				) posting_callback
{
	if(wrap_failedCount)
		*wrap_failedCount= 0;

	if(NULL==wrap_sessions || wrap_sessionsCount<=0)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if((!!wrap_sendFaileds) != (!!wrap_failedCount))
	{
		ASSERT(false); // wrap_sendFaileds、wrap_failedCount要么都为NULL，要么都不为NULL
		return TCPS_ERR_INVALID_PARAM;
	}

	INT_PTR notReadies = 0;
	tcps_SmartArray<PPCC_Center_S_, 256> iscm_sessions_ar_;
	for(INT_PTR i=0; i<wrap_sessionsCount; ++i)
	{
		if(NULL == wrap_sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(wrap_sessions[i]->m_sessionL)
		{
			wrap_sessions[i]->AddModelCenter(
					centerIPP_wrap
					);
			continue;
		}
		if(TCPS_OK != wrap_sessions[i]->UpdateCallbackMatchingFlag_())
			continue;
		if(!wrap_sessions[i]->m_callbackMatchingFlag.matching_AddModelCenter)
		{
			IPP peerIPP = wrap_sessions[i]->m_sessionR->m_peerIPP;
			NPLogWarning(("The 'PCC_Center::AddModelCenter()' of '%s' is not matched!", IPP_TO_STR_A(peerIPP)));
			continue;
		}
		if(0 == wrap_sessions[i]->m_sessionR->m_postingProxy.callerKey_)
		{
			if(wrap_sendFaileds)
			{
				wrap_sendFaileds[notReadies] = wrap_sessions[i];
				++notReadies;
			}
			continue;
		}
		iscm_sessions_ar_.push_back(wrap_sessions[i]);
	}
	if(0 == iscm_sessions_ar_.size())
		return TCPS_OK;

	// 准备调用数据
	tcps_SmartArray<SockWriteBuf, 256> iscm_swb_ar_;
	SockWriteBuf iscm_swb_;

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	iscm_swb_.data = &peerCallFlags;
	iscm_swb_.len = sizeof(peerCallFlags);
	iscm_swb_ar_.push_back(iscm_swb_);

	INT32 call_id_len = 26;
	iscm_swb_.data = &call_id_len;
	iscm_swb_.len = sizeof(call_id_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	iscm_swb_.data = "PCC_Center::AddModelCenter";
	iscm_swb_.len = call_id_len+1;
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN IPP centerIPP
	iscm_swb_.data = &centerIPP_wrap;
	iscm_swb_.len = sizeof(centerIPP_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> iscm_callerKey_ar_;
	iscm_callerKey_ar_.resize(iscm_sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)iscm_sessions_ar_.size(); ++i)
		iscm_callerKey_ar_[i] = iscm_sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	if(NULL == wrap_sendFaileds)
	{
		return callerMan.BatchPosting(
							iscm_callerKey_ar_.Get(),
							iscm_callerKey_ar_.size(),
							iscm_swb_ar_.Get(),
							iscm_swb_ar_.size(),
							NULL,
							NULL
							);
	}

	ASSERT(wrap_failedCount);
	tcps_SmartArray<INT_PTR, 256> iscm_queueFullIndexesAr;
	iscm_queueFullIndexesAr.resize(iscm_callerKey_ar_.size());
	TCPSError err = callerMan.BatchPosting(
						iscm_callerKey_ar_.Get(),
						iscm_callerKey_ar_.size(),
						iscm_swb_ar_.Get(),
						iscm_swb_ar_.size(),
						iscm_queueFullIndexesAr.Get(),
						wrap_failedCount
						);
	ASSERT(0<=*wrap_failedCount && *wrap_failedCount<=(INT_PTR)iscm_queueFullIndexesAr.size());
	for(INT_PTR i=0; i<*wrap_failedCount; ++i)
		(wrap_sendFaileds+notReadies)[i] = iscm_sessions_ar_[iscm_queueFullIndexesAr[i]];
	*wrap_failedCount += notReadies;
	return err;
}

TCPSError PCC_Center_S::DelModelCenter(
				IN const IPP& centerIPP_wrap
				) posting_callback
{
	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnDelModelCenter;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("DelModelCenter", 14, s_PCC_Center_DelModelCenter_TypeInfo_, s_PCC_Center_DelModelCenter_TypeInfo_len_);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_Center_LocalCallback::FN_DelModelCenter)callbackFuncL)(
					m_sessionL,
					centerIPP_wrap
					);
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_DelModelCenter)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 26;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::DelModelCenter", call_id_len+1);

	// 填充IN参数到outfiter

	// IN IPP centerIPP
	Put_BaseType_(&m_dataOutfiter, centerIPP_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_sessionR->m_udpSite.IsLinked())
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID = m_sessionR->GetSessionKey();
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_sessionR->m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_S::DelModelCenter_Batch(
				IN const PPCC_Center_S_* wrap_sessions,
				IN INT_PTR wrap_sessionsCount,
				IN const IPP& centerIPP_wrap,
				OUT PPCC_Center_S_* wrap_sendFaileds /*= NULL*/,
				OUT INT_PTR* wrap_failedCount /*= NULL*/
				) posting_callback
{
	if(wrap_failedCount)
		*wrap_failedCount= 0;

	if(NULL==wrap_sessions || wrap_sessionsCount<=0)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if((!!wrap_sendFaileds) != (!!wrap_failedCount))
	{
		ASSERT(false); // wrap_sendFaileds、wrap_failedCount要么都为NULL，要么都不为NULL
		return TCPS_ERR_INVALID_PARAM;
	}

	INT_PTR notReadies = 0;
	tcps_SmartArray<PPCC_Center_S_, 256> iscm_sessions_ar_;
	for(INT_PTR i=0; i<wrap_sessionsCount; ++i)
	{
		if(NULL == wrap_sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(wrap_sessions[i]->m_sessionL)
		{
			wrap_sessions[i]->DelModelCenter(
					centerIPP_wrap
					);
			continue;
		}
		if(TCPS_OK != wrap_sessions[i]->UpdateCallbackMatchingFlag_())
			continue;
		if(!wrap_sessions[i]->m_callbackMatchingFlag.matching_DelModelCenter)
		{
			IPP peerIPP = wrap_sessions[i]->m_sessionR->m_peerIPP;
			NPLogWarning(("The 'PCC_Center::DelModelCenter()' of '%s' is not matched!", IPP_TO_STR_A(peerIPP)));
			continue;
		}
		if(0 == wrap_sessions[i]->m_sessionR->m_postingProxy.callerKey_)
		{
			if(wrap_sendFaileds)
			{
				wrap_sendFaileds[notReadies] = wrap_sessions[i];
				++notReadies;
			}
			continue;
		}
		iscm_sessions_ar_.push_back(wrap_sessions[i]);
	}
	if(0 == iscm_sessions_ar_.size())
		return TCPS_OK;

	// 准备调用数据
	tcps_SmartArray<SockWriteBuf, 256> iscm_swb_ar_;
	SockWriteBuf iscm_swb_;

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	iscm_swb_.data = &peerCallFlags;
	iscm_swb_.len = sizeof(peerCallFlags);
	iscm_swb_ar_.push_back(iscm_swb_);

	INT32 call_id_len = 26;
	iscm_swb_.data = &call_id_len;
	iscm_swb_.len = sizeof(call_id_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	iscm_swb_.data = "PCC_Center::DelModelCenter";
	iscm_swb_.len = call_id_len+1;
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN IPP centerIPP
	iscm_swb_.data = &centerIPP_wrap;
	iscm_swb_.len = sizeof(centerIPP_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> iscm_callerKey_ar_;
	iscm_callerKey_ar_.resize(iscm_sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)iscm_sessions_ar_.size(); ++i)
		iscm_callerKey_ar_[i] = iscm_sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	if(NULL == wrap_sendFaileds)
	{
		return callerMan.BatchPosting(
							iscm_callerKey_ar_.Get(),
							iscm_callerKey_ar_.size(),
							iscm_swb_ar_.Get(),
							iscm_swb_ar_.size(),
							NULL,
							NULL
							);
	}

	ASSERT(wrap_failedCount);
	tcps_SmartArray<INT_PTR, 256> iscm_queueFullIndexesAr;
	iscm_queueFullIndexesAr.resize(iscm_callerKey_ar_.size());
	TCPSError err = callerMan.BatchPosting(
						iscm_callerKey_ar_.Get(),
						iscm_callerKey_ar_.size(),
						iscm_swb_ar_.Get(),
						iscm_swb_ar_.size(),
						iscm_queueFullIndexesAr.Get(),
						wrap_failedCount
						);
	ASSERT(0<=*wrap_failedCount && *wrap_failedCount<=(INT_PTR)iscm_queueFullIndexesAr.size());
	for(INT_PTR i=0; i<*wrap_failedCount; ++i)
		(wrap_sendFaileds+notReadies)[i] = iscm_sessions_ar_[iscm_queueFullIndexesAr[i]];
	*wrap_failedCount += notReadies;
	return err;
}

TCPSError PCC_Center_S::GetStaticContext(
				OUT PCC_NodeDesc& staticContext_wrap
				) cacheable_callback
{
	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnGetStaticContext;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("GetStaticContext", 16, s_PCC_Center_GetStaticContext_TypeInfo_, s_PCC_Center_GetStaticContext_TypeInfo_len_);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_Center_LocalCallback::FN_GetStaticContext)callbackFuncL)(
					m_sessionL,
					staticContext_wrap
					);
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_GetStaticContext)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	if(!m_cache_GetStaticContext.needUpdate)
	{
		staticContext_wrap = m_cache_GetStaticContext.staticContext_c_;
		return m_cache_GetStaticContext.lastRet;
	}
	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 28;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::GetStaticContext", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			this->OnNetworkMalformed_();
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT PCC_NodeDesc staticContext
			PICK_STRING_Q(iscm_replied_picker, staticContext_wrap.name);
			PICK_BASETYPE_Q(iscm_replied_picker, staticContext_wrap.cpuType);
			PICK_BASETYPE_Q(iscm_replied_picker, staticContext_wrap.cpuFreq);
			PICK_BASETYPE_Q(iscm_replied_picker, staticContext_wrap.cpuProcessors);
			PICK_BASETYPE_Q(iscm_replied_picker, staticContext_wrap.cpuThreads);
			PICK_BASETYPE_Q(iscm_replied_picker, staticContext_wrap.totalMemoryBytes);
			PICK_BASETYPE_Q(iscm_replied_picker, staticContext_wrap.networkBandwidth);
			PICK_BASETYPE_Q(iscm_replied_picker, staticContext_wrap.osType);
			PICK_STRING_Q(iscm_replied_picker, staticContext_wrap.osDetail);
			PICK_BASETYPE_Q(iscm_replied_picker, staticContext_wrap.executeBits);
		if(iscm_replied_picker != iscm_replied_end)
		{
			NPLogError(("PCC_Center_S::GetStaticContext() cacheable_callback, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}

	m_cache_GetStaticContext.staticContext_c_ = staticContext_wrap;
	m_cache_GetStaticContext.lastRet = TCPS_OK;
	m_cache_GetStaticContext.needUpdate = false;
	return TCPS_OK;
}

TCPSError PCC_Center_S::GetDynamicContext(
				OUT PCC_DynamicContext& dynamicContext_wrap
				) callback
{
	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnGetDynamicContext;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("GetDynamicContext", 17, s_PCC_Center_GetDynamicContext_TypeInfo_, s_PCC_Center_GetDynamicContext_TypeInfo_len_);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_Center_LocalCallback::FN_GetDynamicContext)callbackFuncL)(
					m_sessionL,
					dynamicContext_wrap
					);
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_GetDynamicContext)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 29;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::GetDynamicContext", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			this->OnNetworkMalformed_();
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT PCC_DynamicContext dynamicContext
		PICK_BASETYPE_Q(iscm_replied_picker, dynamicContext_wrap);
		if(iscm_replied_picker != iscm_replied_end)
		{
			NPLogError(("PCC_Center_S::GetDynamicContext() callback, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_S::AddModel(
				IN const PCC_ModelProperty& moduleProperty_wrap,
				IN const tcps_Array<PCC_ModelFile>& modelFiles_wrap
				) callback
{
	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnAddModel;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("AddModel", 8, s_PCC_Center_AddModel_TypeInfo_, s_PCC_Center_AddModel_TypeInfo_len_);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_Center_LocalCallback::FN_AddModel)callbackFuncL)(
					m_sessionL,
					moduleProperty_wrap,
					modelFiles_wrap
					);
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_AddModel)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 20;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::AddModel", call_id_len+1);

	// 填充IN参数到outfiter

	// IN PCC_ModelProperty moduleProperty
			Put_String_(&m_dataOutfiter, moduleProperty_wrap.modelTag.name.Get(), moduleProperty_wrap.modelTag.name.LenRef());
			Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.modelTag.version);
		Put_String_(&m_dataOutfiter, moduleProperty_wrap.description.Get(), moduleProperty_wrap.description.LenRef());
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.addTime);

	// IN tcps_Array<PCC_ModelFile> modelFiles
	Put_BaseType_(&m_dataOutfiter, modelFiles_wrap.LenRef());
	for(int idx1=0; idx1<modelFiles_wrap.Length(); ++idx1)
	{
		const PCC_ModelFile& ref1 = modelFiles_wrap[idx1];
			Put_String_(&m_dataOutfiter, ref1.name.Get(), ref1.name.LenRef());
			Put_Binary_(&m_dataOutfiter, ref1.data.Get(), ref1.data.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			this->OnNetworkMalformed_();
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			NPLogError(("PCC_Center_S::AddModel() callback, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_S::DelModel(
				IN const PCC_Tag& tag_wrap
				) callback
{
	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnDelModel;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("DelModel", 8, s_PCC_Center_DelModel_TypeInfo_, s_PCC_Center_DelModel_TypeInfo_len_);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_Center_LocalCallback::FN_DelModel)callbackFuncL)(
					m_sessionL,
					tag_wrap
					);
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_DelModel)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 20;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::DelModel", call_id_len+1);

	// 填充IN参数到outfiter

	// IN PCC_Tag tag
		Put_String_(&m_dataOutfiter, tag_wrap.name.Get(), tag_wrap.name.LenRef());
		Put_BaseType_(&m_dataOutfiter, tag_wrap.version);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			this->OnNetworkMalformed_();
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			NPLogError(("PCC_Center_S::DelModel() callback, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_S::SetRedirect_(
				IN const IPP& redirectIPP_wrap,
				IN const void* redirectParam_wrap, IN INT32 redirectParam_wrap_len
				) posting_callback
{
	if(m_sessionL)
	{
		// ASSERT(false); // ??
		return TCPS_ERR_REFUSED;
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_SetRedirect_)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 24;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::SetRedirect_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN IPP redirectIPP
	Put_BaseType_(&m_dataOutfiter, redirectIPP_wrap);

	// IN tcps_Binary redirectParam
	if(redirectParam_wrap_len<0 || (redirectParam_wrap_len>0 && NULL==redirectParam_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	Put_Binary_(&m_dataOutfiter, redirectParam_wrap, redirectParam_wrap_len);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_sessionR->m_udpSite.IsLinked())
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID = m_sessionR->GetSessionKey();
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_sessionR->m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_S::SetRedirect__Batch(
				IN const PPCC_Center_S_* wrap_sessions,
				IN INT_PTR wrap_sessionsCount,
				IN const IPP& redirectIPP_wrap,
				IN const void* redirectParam_wrap, IN INT32 redirectParam_wrap_len,
				OUT PPCC_Center_S_* wrap_sendFaileds /*= NULL*/,
				OUT INT_PTR* wrap_failedCount /*= NULL*/
				) posting_callback
{
	if(wrap_failedCount)
		*wrap_failedCount= 0;

	if(NULL==wrap_sessions || wrap_sessionsCount<=0)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if((!!wrap_sendFaileds) != (!!wrap_failedCount))
	{
		ASSERT(false); // wrap_sendFaileds、wrap_failedCount要么都为NULL，要么都不为NULL
		return TCPS_ERR_INVALID_PARAM;
	}

	INT_PTR notReadies = 0;
	tcps_SmartArray<PPCC_Center_S_, 256> iscm_sessions_ar_;
	for(INT_PTR i=0; i<wrap_sessionsCount; ++i)
	{
		if(NULL == wrap_sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(wrap_sessions[i]->m_sessionL)
			continue;
		if(TCPS_OK != wrap_sessions[i]->UpdateCallbackMatchingFlag_())
			continue;
		if(!wrap_sessions[i]->m_callbackMatchingFlag.matching_SetRedirect_)
		{
			IPP peerIPP = wrap_sessions[i]->m_sessionR->m_peerIPP;
			NPLogWarning(("The 'PCC_Center::SetRedirect_()' of '%s' is not matched!", IPP_TO_STR_A(peerIPP)));
			continue;
		}
		if(0 == wrap_sessions[i]->m_sessionR->m_postingProxy.callerKey_)
		{
			if(wrap_sendFaileds)
			{
				wrap_sendFaileds[notReadies] = wrap_sessions[i];
				++notReadies;
			}
			continue;
		}
		iscm_sessions_ar_.push_back(wrap_sessions[i]);
	}
	if(0 == iscm_sessions_ar_.size())
		return TCPS_OK;

	// 准备调用数据
	tcps_SmartArray<SockWriteBuf, 256> iscm_swb_ar_;
	SockWriteBuf iscm_swb_;

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	iscm_swb_.data = &peerCallFlags;
	iscm_swb_.len = sizeof(peerCallFlags);
	iscm_swb_ar_.push_back(iscm_swb_);

	INT32 call_id_len = 24;
	iscm_swb_.data = &call_id_len;
	iscm_swb_.len = sizeof(call_id_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	iscm_swb_.data = "PCC_Center::SetRedirect_";
	iscm_swb_.len = call_id_len+1;
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN IPP redirectIPP
	iscm_swb_.data = &redirectIPP_wrap;
	iscm_swb_.len = sizeof(redirectIPP_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN tcps_Binary redirectParam
	if(redirectParam_wrap_len<0 || (redirectParam_wrap_len>0 && NULL==redirectParam_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	iscm_swb_.data = &redirectParam_wrap_len;
	iscm_swb_.len = sizeof(redirectParam_wrap_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	if(redirectParam_wrap_len > 0)
	{
		iscm_swb_.data = redirectParam_wrap;
		iscm_swb_.len = redirectParam_wrap_len;
		iscm_swb_ar_.push_back(iscm_swb_);
	}

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> iscm_callerKey_ar_;
	iscm_callerKey_ar_.resize(iscm_sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)iscm_sessions_ar_.size(); ++i)
		iscm_callerKey_ar_[i] = iscm_sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	if(NULL == wrap_sendFaileds)
	{
		return callerMan.BatchPosting(
							iscm_callerKey_ar_.Get(),
							iscm_callerKey_ar_.size(),
							iscm_swb_ar_.Get(),
							iscm_swb_ar_.size(),
							NULL,
							NULL
							);
	}

	ASSERT(wrap_failedCount);
	tcps_SmartArray<INT_PTR, 256> iscm_queueFullIndexesAr;
	iscm_queueFullIndexesAr.resize(iscm_callerKey_ar_.size());
	TCPSError err = callerMan.BatchPosting(
						iscm_callerKey_ar_.Get(),
						iscm_callerKey_ar_.size(),
						iscm_swb_ar_.Get(),
						iscm_swb_ar_.size(),
						iscm_queueFullIndexesAr.Get(),
						wrap_failedCount
						);
	ASSERT(0<=*wrap_failedCount && *wrap_failedCount<=(INT_PTR)iscm_queueFullIndexesAr.size());
	for(INT_PTR i=0; i<*wrap_failedCount; ++i)
		(wrap_sendFaileds+notReadies)[i] = iscm_sessions_ar_[iscm_queueFullIndexesAr[i]];
	*wrap_failedCount += notReadies;
	return err;
}

TCPSError PCC_Center_S::CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks_wrap,
				IN const tcps_Array<tcps_String>& callbackTypeInfos_wrap,
				OUT tcps_Array<BOOL>& matchingFlags_wrap
				) callback
{
	if(m_sessionL)
	{
		InitializeAllCallsTypeInfo_();
		ASSERT(callbacks_wrap.Length() == callbackTypeInfos_wrap.Length());
		matchingFlags_wrap.Resize(callbacks_wrap.Length());
		for(int i=0; i<callbacks_wrap.Length(); ++i)
		{
			const tcps_String& name = callbacks_wrap[i];
			const tcps_String& typeInfo = callbackTypeInfos_wrap[i];
			matchingFlags_wrap[i] = (NULL != m_sessionL->FindCallback_(name.Get(), name.Length(), typeInfo.Get(), typeInfo.Length()));
		}
		return TCPS_OK;
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 26;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::CallbackCheck_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_Array<tcps_String> callbacks
	Put_BaseType_(&m_dataOutfiter, callbacks_wrap.LenRef());
	for(int idx1=0; idx1<callbacks_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = callbacks_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// IN tcps_Array<tcps_String> callbackTypeInfos
	Put_BaseType_(&m_dataOutfiter, callbackTypeInfos_wrap.LenRef());
	for(int idx1=0; idx1<callbackTypeInfos_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = callbackTypeInfos_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_IRequester* iscm_replied_picker = m_rpcRequester;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<BOOL> matchingFlags
		PICK_PODARRAY_(iscm_replied_picker, matchingFlags_wrap);
	}
	return TCPS_OK;
}

TCPSError PCC_Center_S::UDPLink_(
			OUT INT32& servePort,
			OUT INT32& linkKey
			) method
{
	ASSERT(!m_sessionR->m_udpSite.IsOn());
	AutoSock udpSock;
	udpSock.sock_ = UDPNew();
	if(!SockValid(udpSock.sock_))
		return TCPS_ERR_SYSTEM_RESOURCE;

	INT32 port = 0;
	TCPSError err = tcps_AutoBindUDPPort(udpSock.sock_, m_sessionR->m_serveIPP.ip_, &port);
	if(TCPS_OK != err)
		return err;
	m_sessionR->m_udpSite.localPort_ = port;
	m_sessionR->m_udpSite.sock_ = udpSock.Drop();
	servePort = port;
	linkKey = m_sessionR->GetSessionKey();
	return TCPS_OK;
}

TCPSError PCC_Center_S::UDPLinkConfirm_(
			) method
{
	if(!m_sessionR->m_udpSite.IsLinking())
	{
		ASSERT(false);
		return TCPS_ERR_CALL_WAS_IGNORED;
	}
	ASSERT(SockValid(m_sessionR->m_udpSite.sock_));

	DWORD recvTimeout = INFINITE;
	this->GetTimeout(NULL, &recvTimeout, NULL);
	if(INFINITE == recvTimeout)
		recvTimeout = iscm_GetDefaultRecvTimeout();
	recvTimeout = min(recvTimeout, (DWORD)2000);
	int r = SockCheckRead(m_sessionR->m_udpSite.sock_, recvTimeout);
	if(1 != r)
		return TCPS_ERR_RECV;
	IPP peerIPP;
	CSmartBuf<BYTE, 1024> smBuf(ISCM_MAX_UDP_FRAG_BYTES);
	BYTE* buf = smBuf.Get();
	r = SockReceiveFrom(m_sessionR->m_udpSite.sock_, &peerIPP.ip_, &peerIPP.port_, buf, ISCM_MAX_UDP_FRAG_BYTES);
	if((int)sizeof(iscm_UDPFrag) != r)
		return TCPS_ERR_RECV;
	if(!peerIPP.IsValid() || peerIPP.ip_!=m_sessionR->m_peerIPP.ip_)
		return TCPS_ERR_MALFORMED_REQ;

	const iscm_UDPFrag& frag = *(const iscm_UDPFrag*)buf;
	if(ISCM_UDP_FRAG_LINK != frag.fragType)
		return TCPS_ERR_MALFORMED_REQ;
	INT32 linkKey = m_sessionR->GetSessionKey();
	if(linkKey != frag.sendKey)
		return TCPS_ERR_INVALID_UDP_LINK_KEY;

	if(0 != UDPConnect(m_sessionR->m_udpSite.sock_, peerIPP.ip_, peerIPP.port_))
		return TCPS_ERR_SYSTEM;

	iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
	udpServer.AddSession(linkKey, m_sessionR->m_udpSite.sock_, m_sessionR);
	m_sessionR->m_udpSite.sock_ = INVALID_SOCKET;

	return TCPS_OK;
}

TCPSError PCC_Center_S::SetTimeout_(
			IN INT32 recvTimeout,
			IN INT32 sendTimeout
			) posting_method
{
	this->SetTimeout(INFINITE, recvTimeout, sendTimeout);
	return TCPS_OK;
}

TCPSError PCC_Center_S::SetSessionBufferSize_(
			IN INT32 recvBufBytes,
			IN INT32 sendBufBytes
			) posting_method
{
	this->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	return TCPS_OK;
}

TCPSError PCC_Center_S::MethodCheck_(
			IN const tcps_Array<tcps_String>& methods,
			IN const tcps_Array<tcps_String>& methodTypeInfos,
			OUT tcps_Array<BOOL>& matchingFlags
			) method
{
	if(0==methods.Length() || methods.Length()!=methodTypeInfos.Length())
		return TCPS_ERR_INVALID_PARAM;

	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<4> > MethodMap_;
	static MethodMap_* s_mdMap = NULL;
	if(NULL == s_mdMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_mdMap)
		{
			static MethodMap_ s_mdMapObj;
			MethodMap_& mdMap = s_mdMapObj;
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("UDPLink_"), CPtrStrA(s_PCC_Center_UDPLink__TypeInfo_, s_PCC_Center_UDPLink__TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("UDPLinkConfirm_"), CPtrStrA(s_PCC_Center_UDPLinkConfirm__TypeInfo_, s_PCC_Center_UDPLinkConfirm__TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetTimeout_"), CPtrStrA(s_PCC_Center_SetTimeout__TypeInfo_, s_PCC_Center_SetTimeout__TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetSessionBufferSize_"), CPtrStrA(s_PCC_Center_SetSessionBufferSize__TypeInfo_, s_PCC_Center_SetSessionBufferSize__TypeInfo_len_))).second);
			s_mdMap = &mdMap;
		}
	}

	matchingFlags.Resize(methods.Length());
	for(int index=0; index<methods.Length(); ++index)
	{
		BOOL& flag = matchingFlags[index];
		const tcps_String& name = methods[index];
		const tcps_String& typeInfos = methodTypeInfos[index];
		MethodMap_::const_iterator cit = s_mdMap->find(name.Get(), name.Length());
		if(cit!=s_mdMap->end() && 0==typeInfos.Compare(cit->second.p, cit->second.len))
			flag = true;
		else
			flag = false;
	}
	return TCPS_OK;
}

void PCC_Center_S::CloseSession(
				IN TCPSError cause /*= TCPS_OK*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		m_sessionR->CloseSession_(cause);
	else if(m_sessionL)
	{
		AutoFlag<OSThreadID> autoClosingTID(m_closingTID_L.tid, OSThreadSelf());
		m_sessionL->CloseSession_();
	}
}

IPP PCC_Center_S::GetPeerIPP(
				OUT IPP* peerID /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
	{
		if(peerID)
			*peerID = m_sessionR->m_peerID_IPP;
		return m_sessionR->m_peerIPP;
	}

	if(m_sessionL)
	{
		if(peerID)
			*peerID = IPP((DWORD)0, (int)0);
		return IPP((DWORD)0, (int)0);
	}

	if(peerID)
		*peerID = INVALID_IPP;
	return INVALID_IPP;
}

BOOL PCC_Center_S::IsLocalPeer() const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	return (NULL != m_sessionL);
}

void PCC_Center_S::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		m_sessionR->m_postingPendingParam.Set(maxPendingBytes, maxPendings);
}

void PCC_Center_S::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(maxPendingBytes)
			*maxPendingBytes = 0;
		if(maxPendings)
			*maxPendings = 0;
		return;
	}
	m_sessionR->m_postingPendingParam.Get(maxPendingBytes, maxPendings);
}

BOOL PCC_Center_S::CallbackIsReady() const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		return (m_sessionR->m_callbackRequester.face_ && m_sessionR->m_callbackRequester.face_->IsConnected());
	return true;
}

TCPSError PCC_Center_S::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
		return TCPS_OK;
	if(NULL == m_sessionR->m_callbackRequester.face_)
		return TCPS_ERR_CALLBACK_NOT_READY;
	m_sessionR->m_callbackRequester.face_->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	return TCPS_OK;
}

TCPSError PCC_Center_S::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(connectTimeout)
			*connectTimeout = INFINITE;
		if(recvTimeout)
			*recvTimeout = INFINITE;
		if(sendTimeout)
			*sendTimeout = INFINITE;
		return TCPS_OK;
	}

	if(NULL == m_sessionR->m_callbackRequester.face_)
		return TCPS_ERR_CALLBACK_NOT_READY;
	m_sessionR->m_callbackRequester.face_->GetTimeout(connectTimeout, recvTimeout, sendTimeout);
	return TCPS_OK;
}

void PCC_Center_S::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
		return;

	if(recvBufBytes>=0 || sendBufBytes>=0)
	{
		SOCKET sock = INVALID_SOCKET;
		m_sessionR->m_bindedSession->GetInfos(NULL, &sock, NULL, NULL, NULL);
		ASSERT(SockValid(sock));
		if(recvBufBytes >= 0)
			SockSetReceiveBufSize(sock, (0==recvBufBytes ? TCPS_DEFAULT_RECVBUF_SIZE : recvBufBytes));
		if(sendBufBytes >= 0)
			SockSetSendBufSize(sock, (0==sendBufBytes ? TCPS_DEFAULT_SENDBUF_SIZE : sendBufBytes));
	}
	if(m_sessionR->m_callbackRequester.face_)
		m_sessionR->m_callbackRequester.face_->SetSessionBufferSize(recvBufBytes, sendBufBytes);
}

void PCC_Center_S::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(recvBufBytes)
			*recvBufBytes = 0;
		if(sendBufBytes)
			*sendBufBytes = 0;
		return;
	}

	if(NULL==recvBufBytes && NULL==sendBufBytes)
		return;
	if(m_sessionR->m_callbackRequester.face_)
	{
		m_sessionR->m_callbackRequester.face_->GetSessionBufferSize(recvBufBytes, sendBufBytes);
	}
	else
	{
		SOCKET sock = INVALID_SOCKET;
		m_sessionR->m_bindedSession->GetInfos(NULL, &sock, NULL, NULL, NULL);
		ASSERT(SockValid(sock));
		if(recvBufBytes)
			SockGetReceiveBufSize(sock, recvBufBytes);
		if(sendBufBytes)
			SockGetSendBufSize(sock, sendBufBytes);
	}
}

void PCC_Center_S::SetPostingSendParameters(
				IN INT32 maxBufferingSize,
				IN INT32 maxSendings
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR && 0!=m_sessionR->m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().SetBufferingParam(m_sessionR->m_postingProxy.callerKey_, maxBufferingSize, maxSendings);
	m_postingSendParam.Set(maxBufferingSize, maxSendings);
}

void PCC_Center_S::GetPostingSendParameters(
				OUT INT32* maxBufferingSize /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(maxBufferingSize)
			*maxBufferingSize = 0;
		if(maxSendings)
			*maxSendings = 0;
		return;
	}
	m_postingSendParam.Get(maxBufferingSize, maxSendings);
}

TCPSError PCC_Center_S::CleanPostingSendingQueue()
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(NULL==m_sessionR || 0==m_sessionR->m_postingProxy.callerKey_)
		return TCPS_ERR_CALL_WAS_IGNORED;
	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(&m_sessionR->m_postingProxy.callerKey_, 1);
}

TCPSError PCC_Center_S::CleanPostingSendingQueue(
				IN const PPCC_Center_S_* sessions,
				IN INT_PTR sessionsCount
				)
{
	tcps_SmartArray<PPCC_Center_S_, 256> sessions_ar_;
	for(INT_PTR i=0; i<sessionsCount; ++i)
	{
		if(NULL == sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(NULL==sessions[i]->m_sessionR || 0==sessions[i]->m_sessionR->m_postingProxy.callerKey_)
			continue;
		sessions_ar_.push_back(sessions[i]);
	}
	if(0 == sessions_ar_.size())
		return TCPS_OK;

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> callerKey_ar_;
	callerKey_ar_.resize(sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)sessions_ar_.size(); ++i)
		callerKey_ar_[i] = sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(callerKey_ar_.Get(), (int)callerKey_ar_.size());
}

class PCC_Center_LS : public IPCC_Center_LocalMethod
{
private:
	PCC_Center_LS(const PCC_Center_LS&);
	PCC_Center_LS& operator= (const PCC_Center_LS&);

private:
	PCC_CenterSessionMaker& m_sessionMaker;
	IPCC_Center_LocalCallback* const m_callback;
	PCC_Center_S* const m_method;
	TCPSError m_connectError;
	INT32 m_sessionKey;

public:
	TCPSError GetConnectError() const
		{	return m_connectError;	}

public:
	PCC_Center_LS(const IPP& clientID_IPP, PCC_CenterSessionMaker& sessionMaker, IPCC_Center_LocalCallback* callbackHandler)
		: m_sessionMaker(sessionMaker)
		, m_callback(callbackHandler)
		, m_method(tcps_NewEx(PCC_Center_S, (m_sessionMaker, NULL, callbackHandler)))
		, m_connectError(TCPS_ERROR)
		, m_sessionKey(0)
	{
		INT32 sessionCount;
		m_sessionMaker.OnSessionConnect_(&m_sessionKey, sessionCount);
		m_connectError = m_method->OnConnected(m_sessionKey, clientID_IPP, sessionCount);
		if(TCPS_OK == m_connectError)
		{
			if(m_callback)
				m_method->OnCallbackReady();
			m_method->OnPostingCallReady();
			m_sessionMaker.RegisterLocalSession_(m_callback);
		}
	}
	virtual ~PCC_Center_LS()
	{
		if(TCPS_OK == m_connectError)
			m_sessionMaker.UnregisterLocalSession_(m_callback);
		m_sessionMaker.Unregister(m_method);
		if(INVALID_OSTHREADID==m_method->m_closingTID_L.tid || m_method->m_closingTID_L.tid!=OSThreadSelf())
			m_method->OnPeerBroken(m_sessionKey, TCPS_ANY_IPP, m_connectError);
		m_method->OnClose(m_sessionKey, TCPS_ANY_IPP, m_connectError);
		m_sessionMaker.OnSessionClosed_();
		m_method->~PCC_Center_S();
		tcps_Free(m_method);
	}
	virtual void DeleteThis()
		{	tcps_Delete(this);	}

	virtual PROC FindMethod_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				)
	{
		if(NULL == name)
		{
			ASSERT(false);
			return NULL;
		}

		// 对OnStreamedCall_L_()特殊处理
		if(nameLen<0 && 0==strcmp("OnStreamedCall_L_", name))
			return (PROC)&OnStreamedCall_L_;

		if(NULL == type)
		{
			ASSERT(false);
			return NULL;
		}

		InitializeAllCallsTypeInfo_();
		typedef TwoItems<CPtrStrA, PROC> FuncPair;
		typedef CQuickStringMap<CPtrStrA, FuncPair, QSS_Traits<0> > MethodMap_;
		static MethodMap_* s_mdMap = NULL;
		if(NULL == s_mdMap)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == s_mdMap)
			{
				static MethodMap_ s_mdMapObj;
				MethodMap_& mdMap = s_mdMapObj;
				s_mdMap = &mdMap;
			}
		}

		MethodMap_::iterator it = s_mdMap->find(name, nameLen);
		if(s_mdMap->end() == it)
			return NULL;
		const CPtrStrA& ps = it->second.first;
		if(0 != ps.Compare(type, typeLen))
			return NULL;
		return it->second.second;
	}

private:
	static TCPSError OnStreamedCall_L_(
				IN void* sessionObj,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
	{	return ((PCC_Center_LS*)sessionObj)->m_method->OnStreamedCall_L_(
					methodName,
					nameLen,
					data,
					dataLen,
					replyData,
					replyLen
					);
	}

private:
};

TCPSError MakeLocalSession_PCC_Center__(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_Center_LocalMethod*& methodHandler,
			IN IPCC_Center_LocalCallback* callbackHandler
			)
{
	PCC_Center_LS* session = tcps_NewEx(PCC_Center_LS, (clientID_IPP, sessionMaker, callbackHandler));
	if(NULL == session)
		return TCPS_ERR_OUT_OF_MEMORY;
	TCPSError err = session->GetConnectError();
	if(TCPS_OK != err)
	{
		tcps_Delete(session);
		return err;
	}
	methodHandler = session;
	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_Login(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"Login",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String ticket
	IN tcps_String ticket_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ticket_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::Login() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->Login(
			ticket_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::Login(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::Login(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_Logout(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"Logout",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::Logout() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->Logout(
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::Logout(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::Logout(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_CreateTrunk(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"CreateTrunk",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::CreateTrunk() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->CreateTrunk(
			trunk_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::CreateTrunk(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::CreateTrunk(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_RemoveTrunk(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"RemoveTrunk",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::RemoveTrunk() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->RemoveTrunk(
			trunk_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::RemoveTrunk(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::RemoveTrunk(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_ListTrunk(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"ListTrunk",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::ListTrunk() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<tcps_String> trunks;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->ListTrunk(
			opWrapper->trunks
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::ListTrunk(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::ListTrunk(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<tcps_String> trunks
	OUT const tcps_Array<tcps_String>& trunks_wrap = opWrapper->trunks;
	Set_BaseType_(outfiter, trunks_wrap.LenRef());
	for(int idx1=0; idx1<trunks_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = trunks_wrap[idx1];
		Set_String_(outfiter, ref1);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_AddAuthCenter(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"AddAuthCenter",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	// IN PCC_Tag authTag
	IN PCC_Tag authTag_wrap;
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, authTag_wrap.name);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, authTag_wrap.version);

	// IN tcps_Array<PCC_ModuleFile> files
	IN tcps_Array<PCC_ModuleFile> files_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	files_wrap.Resize(array_len);
	for(int idx1=0; idx1<files_wrap.Length(); ++idx1)
	{
		PCC_ModuleFile& ref1 = files_wrap[idx1];
			GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.name);
			GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.data);
			GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.entry);
	}

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::AddAuthCenter() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->AddAuthCenter(
			trunk_wrap,
			authTag_wrap,
			files_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::AddAuthCenter(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::AddAuthCenter(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_RemoveAuthCenter(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"RemoveAuthCenter",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	// IN PCC_Tag authTag
	IN PCC_Tag authTag_wrap;
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, authTag_wrap.name);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, authTag_wrap.version);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::RemoveAuthCenter() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->RemoveAuthCenter(
			trunk_wrap,
			authTag_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::RemoveAuthCenter(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::RemoveAuthCenter(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_ListAuthCenter(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"ListAuthCenter",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::ListAuthCenter() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<PCC_Tag> authTags;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->ListAuthCenter(
			trunk_wrap,
			opWrapper->authTags
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::ListAuthCenter(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::ListAuthCenter(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<PCC_Tag> authTags
	OUT const tcps_Array<PCC_Tag>& authTags_wrap = opWrapper->authTags;
	Set_BaseType_(outfiter, authTags_wrap.LenRef());
	for(int idx1=0; idx1<authTags_wrap.Length(); ++idx1)
	{
		const PCC_Tag& ref1 = authTags_wrap[idx1];
			Set_String_(outfiter, ref1.name);
			Set_BaseType_(outfiter, ref1.version);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_FindAuthCenter(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"FindAuthCenter",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	// IN PCC_Tag authTag
	IN PCC_Tag authTag_wrap;
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, authTag_wrap.name);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, authTag_wrap.version);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::FindAuthCenter() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->FindAuthCenter(
			trunk_wrap,
			authTag_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::FindAuthCenter(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::FindAuthCenter(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_AddModule(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"AddModule",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	// IN INT64 modelKey
	IN INT64 modelKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, modelKey_wrap);

	// IN PCC_ModuleProperty moduleProperty
	IN PCC_ModuleProperty moduleProperty_wrap;
			GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.moduleTag.name);
			GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.moduleTag.version);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.modulePattern);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.moduleFileType);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.moduleType);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.moduleLatency);
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.description);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.modulePlatform);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.addTime);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.moduleSize);

	// IN tcps_Array<PCC_ModuleFile> moudleFiles
	IN tcps_Array<PCC_ModuleFile> moudleFiles_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	moudleFiles_wrap.Resize(array_len);
	for(int idx1=0; idx1<moudleFiles_wrap.Length(); ++idx1)
	{
		PCC_ModuleFile& ref1 = moudleFiles_wrap[idx1];
			GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.name);
			GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.data);
			GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.entry);
	}

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::AddModule() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT INT64 moduleKey;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->AddModule(
			trunk_wrap,
			modelKey_wrap,
			moduleProperty_wrap,
			moudleFiles_wrap,
			opWrapper->moduleKey
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::AddModule(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::AddModule(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT INT64 moduleKey
	OUT const INT64& moduleKey_wrap = opWrapper->moduleKey;
	Set_BaseType_(outfiter, moduleKey_wrap);

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_AddModuleFile(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"AddModuleFile",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	// IN INT64 moduleKey
	IN INT64 moduleKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleKey_wrap);

	// IN PCC_ModuleFileType fileType
	IN PCC_ModuleFileType fileType_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, fileType_wrap);

	// IN tcps_Array<PCC_ModuleFile> moduleFiles
	IN tcps_Array<PCC_ModuleFile> moduleFiles_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	moduleFiles_wrap.Resize(array_len);
	for(int idx1=0; idx1<moduleFiles_wrap.Length(); ++idx1)
	{
		PCC_ModuleFile& ref1 = moduleFiles_wrap[idx1];
			GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.name);
			GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.data);
			GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.entry);
	}

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::AddModuleFile() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->AddModuleFile(
			trunk_wrap,
			moduleKey_wrap,
			fileType_wrap,
			moduleFiles_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::AddModuleFile(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::AddModuleFile(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_RemoveModule(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"RemoveModule",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	// IN INT64 moduleKey
	IN INT64 moduleKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleKey_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::RemoveModule() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->RemoveModule(
			trunk_wrap,
			moduleKey_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::RemoveModule(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::RemoveModule(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_RemoveModuleFiles(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"RemoveModuleFiles",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	// IN INT64 moduleKey
	IN INT64 moduleKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleKey_wrap);

	// IN INT32 fileType
	IN INT32 fileType_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, fileType_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::RemoveModuleFiles() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->RemoveModuleFiles(
			trunk_wrap,
			moduleKey_wrap,
			fileType_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::RemoveModuleFiles(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::RemoveModuleFiles(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_ListModules(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"ListModules",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String trunk
	IN tcps_String trunk_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, trunk_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::ListModules() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<PCC_ModulePropWithKey> modulesInfo;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->ListModules(
			trunk_wrap,
			opWrapper->modulesInfo
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::ListModules(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::ListModules(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<PCC_ModulePropWithKey> modulesInfo
	OUT const tcps_Array<PCC_ModulePropWithKey>& modulesInfo_wrap = opWrapper->modulesInfo;
	Set_BaseType_(outfiter, modulesInfo_wrap.LenRef());
	for(int idx1=0; idx1<modulesInfo_wrap.Length(); ++idx1)
	{
		const PCC_ModulePropWithKey& ref1 = modulesInfo_wrap[idx1];
			Set_BaseType_(outfiter, ref1.key);
			Set_BaseType_(outfiter, ref1.model);
					Set_String_(outfiter, ref1.prop.moduleTag.name);
					Set_BaseType_(outfiter, ref1.prop.moduleTag.version);
				Set_BaseType_(outfiter, ref1.prop.modulePattern);
				Set_BaseType_(outfiter, ref1.prop.moduleFileType);
				Set_BaseType_(outfiter, ref1.prop.moduleType);
				Set_BaseType_(outfiter, ref1.prop.moduleLatency);
				Set_String_(outfiter, ref1.prop.description);
				Set_BaseType_(outfiter, ref1.prop.modulePlatform);
				Set_BaseType_(outfiter, ref1.prop.addTime);
				Set_BaseType_(outfiter, ref1.prop.moduleSize);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_AddModel(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"AddModel",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN PCC_ModelProperty modelProperty
	IN PCC_ModelProperty modelProperty_wrap;
			GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, modelProperty_wrap.modelTag.name);
			GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, modelProperty_wrap.modelTag.version);
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, modelProperty_wrap.description);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, modelProperty_wrap.addTime);

	// IN tcps_Array<PCC_ModelFile> modelFiles
	IN tcps_Array<PCC_ModelFile> modelFiles_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	modelFiles_wrap.Resize(array_len);
	for(int idx1=0; idx1<modelFiles_wrap.Length(); ++idx1)
	{
		PCC_ModelFile& ref1 = modelFiles_wrap[idx1];
			GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.name);
			GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.data);
	}

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::AddModel() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->AddModel(
			modelProperty_wrap,
			modelFiles_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::AddModel(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::AddModel(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_ListModels(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"ListModels",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::ListModels() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<PCC_ModelPropWithKey> modelsInfo;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->ListModels(
			opWrapper->modelsInfo
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::ListModels(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::ListModels(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<PCC_ModelPropWithKey> modelsInfo
	OUT const tcps_Array<PCC_ModelPropWithKey>& modelsInfo_wrap = opWrapper->modelsInfo;
	Set_BaseType_(outfiter, modelsInfo_wrap.LenRef());
	for(int idx1=0; idx1<modelsInfo_wrap.Length(); ++idx1)
	{
		const PCC_ModelPropWithKey& ref1 = modelsInfo_wrap[idx1];
			Set_BaseType_(outfiter, ref1.key);
					Set_String_(outfiter, ref1.prop.modelTag.name);
					Set_BaseType_(outfiter, ref1.prop.modelTag.version);
				Set_String_(outfiter, ref1.prop.description);
				Set_BaseType_(outfiter, ref1.prop.addTime);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_DelModel(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_Deploy",
					"DelModel",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT64 modelKey
	IN INT64 modelKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, modelKey_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::DelModel() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->DelModel(
			modelKey_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::DelModel(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::DelModel(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_SetTimeout_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT32 recvTimeout
	IN INT32 recvTimeout_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, recvTimeout_wrap);

	// IN INT32 sendTimeout
	IN INT32 sendTimeout_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, sendTimeout_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::SetTimeout_() posting_method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->SetTimeout_(
			recvTimeout_wrap,
			sendTimeout_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::SetTimeout_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::SetTimeout_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_SetSessionBufferSize_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT32 recvBufBytes
	IN INT32 recvBufBytes_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, recvBufBytes_wrap);

	// IN INT32 sendBufBytes
	IN INT32 sendBufBytes_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, sendBufBytes_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::SetSessionBufferSize_() posting_method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->SetSessionBufferSize_(
			recvBufBytes_wrap,
			sendBufBytes_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::SetSessionBufferSize_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::SetSessionBufferSize_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_Deploy_MethodCheck_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_Array<tcps_String> methods
	IN tcps_Array<tcps_String> methods_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	methods_wrap.Resize(array_len);
	for(int idx1=0; idx1<methods_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = methods_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	// IN tcps_Array<tcps_String> methodTypeInfos
	IN tcps_Array<tcps_String> methodTypeInfos_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	methodTypeInfos_wrap.Resize(array_len);
	for(int idx1=0; idx1<methodTypeInfos_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = methodTypeInfos_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_Deploy_S::MethodCheck_() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<BOOL> matchingFlags;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_Deploy_S* pCC_DeployObj_wrap;
		if(thisObj)
			pCC_DeployObj_wrap = thisObj->m_pCC_Deploy;
		else
			pCC_DeployObj_wrap = (PCC_Deploy_S*)faceObj;
		ASSERT(pCC_DeployObj_wrap);
		errTcps = pCC_DeployObj_wrap->MethodCheck_(
			methods_wrap,
			methodTypeInfos_wrap,
			opWrapper->matchingFlags
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_Deploy_S::MethodCheck_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_Deploy_S::MethodCheck_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<BOOL> matchingFlags
	OUT const tcps_Array<BOOL>& matchingFlags_wrap = opWrapper->matchingFlags;
	Set_PODArray_(outfiter, matchingFlags_wrap);

	return TCPS_OK;
}

PCC_Deploy_S::CallbackMatchingFlag::CallbackMatchingFlag()
{
	Reset();
	cbmap_.insert(std::make_pair(CPtrStrA("SetRedirect_", 12), Info(&matching_SetRedirect_, true)));
}

void PCC_Deploy_S::CallbackMatchingFlag::Reset()
{
	matching_SetRedirect_ = false;
}

TCPSError PCC_Deploy_S::UpdateCallbackMatchingFlag_()
{
	if(!m_callbackMatchingUpdatedFlag.needUpdate)
		return TCPS_OK;
	InitializeAllCallsTypeInfo_();
	tcps_String callbacks_ar[1];
	IN tcps_Array<tcps_String> callbacks;
	callbacks.Attach(xat_bind, callbacks_ar, 1);
	tcps_String callbackTypeInfos_ar[1];
	IN tcps_Array<tcps_String> callbackTypeInfos;
	callbackTypeInfos.Attach(xat_bind, callbackTypeInfos_ar, 1);
	callbacks_ar[0].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetRedirect_"));
	callbackTypeInfos_ar[0].Attach(xat_bind, (char*)s_PCC_Deploy_SetRedirect__TypeInfo_, s_PCC_Deploy_SetRedirect__TypeInfo_len_);
	OUT tcps_Array<BOOL> matchingFlags;
	TCPSError err = this->CallbackCheck_(callbacks, callbackTypeInfos, matchingFlags);
	if(TCPS_OK == err)
	{
		if(matchingFlags.Length() == callbacks.Length())
		{
			m_callbackMatchingUpdatedFlag.needUpdate = false;
			const BOOL* const matchingFlags_p = matchingFlags.Get();
			m_callbackMatchingFlag.matching_SetRedirect_ = matchingFlags_p[0];
		}
		else
		{
			ASSERT(false);
			err = TCPS_ERR_MALFORMED_REPLY;
		}
	}
	if(m_callbackMatchingUpdatedFlag.needUpdate)
		m_callbackMatchingFlag.Reset();
	return err;
}

const PCC_Deploy_S::CallbackMatchingFlag& PCC_Deploy_S::GetCallbackMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	TCPSError ret = UpdateCallbackMatchingFlag_();
	if(err)
		*err = ret;
	return m_callbackMatchingFlag;
}

TCPSError PCC_Deploy_S::OnStreamedCall_L_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	INT_PTR inParamsDataLen = sizeof(iscm_PeerCallFlags);
	inParamsDataLen += 12; // "PCC_Deploy::"
	if(nameLen < 0)
		nameLen = strlen(methodName);
	inParamsDataLen += sizeof(INT32)+nameLen+1;
	inParamsDataLen += dataLen;
	BYTE* const inParamsData = (BYTE*)tcps_Alloc(inParamsDataLen);
	if(NULL == inParamsData)
		return TCPS_ERR_OUT_OF_MEMORY;

	BYTE* p = inParamsData;
	iscm_PeerCallFlags& peerCallFlags = *(iscm_PeerCallFlags*)p;
	peerCallFlags.sizeofBOOL_req = sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1; // ??
	peerCallFlags.dummy_15 = 0;
	p += sizeof(iscm_PeerCallFlags);
	*(INT32*)p = 12+(INT32)nameLen;
	p += sizeof(INT32);
	strncpy((char*)p, "PCC_Deploy::", 12);
	p += 12;
	strncpy((char*)p, methodName, nameLen);
	p += nameLen;
	*(char*)p = 0;
	p += 1;
	memcpy(p, data, dataLen);
	p += dataLen;
	ASSERT(p-inParamsData == inParamsDataLen);

	BOOL requireReplyData = true;
	BOOL dataTransferred = false;
	iscm_RPCDataOutfiter outfiter;
	ASSERT(NULL==m_sessionR && m_sessionL);
	TCPSError err = PCC_CenterSession::OnRPCCall_(NULL, this, requireReplyData, inParamsData, dataTransferred, inParamsDataLen, &outfiter);
	tcps_Free(inParamsData);
	if(TCPS_OK != err)
		return err;
	// outfiter.swbBufs_[0]总指向iscm_RPCDataOutfiter::reply_
	// outfiter.swbBufs_[1]为iscm_RPCReplyPrefix replyPrefix
	ASSERT(outfiter.swbBufs_.size()==1 || outfiter.swbBufs_.size()>=2);
	if(outfiter.swbBufs_.size() >= 2)
	{
		ASSERT(replyData && replyLen);
		*replyLen = SockTotalizeWriteBufVec(outfiter.swbBufs_.Get()+2, outfiter.swbBufs_.size()-2);
		*replyData = tcps_Alloc(*replyLen);
		BYTE* q = (BYTE*)*replyData;
		for(INT_PTR i=2; i<(INT_PTR)outfiter.swbBufs_.size(); ++i)
		{
			const SockWriteBuf& swb = outfiter.swbBufs_[i];
			memcpy(q, swb.data, swb.len);
			q += swb.len;
		}
		ASSERT(q-(BYTE*)*replyData == *replyLen);
	}
	return err;
}

TCPSError PCC_Deploy_S::StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;
	if(NULL==callbackName || 0==nameLen)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if(nameLen < 0)
		nameLen = strlen(callbackName);

	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnOnStreamedCallback_L_;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("OnStreamedCallback_L_", -1, NULL, 0);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalCallback::FN_OnStreamedCallback_L_)callbackFuncL)(
					m_sessionL,
					callbackName,
					nameLen,
					data,
					dataLen,
					replyData,
					replyLen
					);
	}
	else if(m_sessionR)
	{
		iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
		if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
			return TCPS_ERR_CALLBACK_NOT_READY;
		DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;
		iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
		ASSERT(0 == m_dataOutfiter.bufs_.size());

		TCPSError errUpdate = UpdateCallbackMatchingFlag_();
		if(TCPS_OK != errUpdate)
			return errUpdate;
		CallbackMatchingFlag::CallbackMap::const_iterator itCallback = m_callbackMatchingFlag.cbmap_.find(callbackName, nameLen);
		if(m_callbackMatchingFlag.cbmap_.end() == itCallback)
			return TCPS_ERR_CALLBACK_NOT_MATCH;
		ASSERT(itCallback->second.pMatchingVar);
		if(!*(itCallback->second.pMatchingVar))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

		// 填充基本类型数据到outfiter
		iscm_PeerCallFlags peerCallFlags;
		peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
		peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
		peerCallFlags.requireReply = !(itCallback->second.isPosting);
		peerCallFlags.dummy_15 = 0;
		m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

		INT32 call_id_len = (INT32)(12+nameLen);
		CSmartBuf<char, 256> call_id_buf(call_id_len+1);
		strncpy(call_id_buf.Get(), "PCC_Deploy::", 12);
		StrAssign(call_id_buf.Get()+12, callbackName, nameLen);
		m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
		m_dataOutfiter.Push(call_id_buf.Get(), call_id_len+1);

		// 填充IN参数到outfiter
		if(dataLen > 0)
			m_dataOutfiter.Push(data, dataLen);

		// 调用PRCCall()
		if(peerCallFlags.requireReply) // callback
		{
			const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
			int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
			int replyBytes = 0;
			TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
			if(TCPS_OK != err)
				return err;

			iscm_RPCReplyPrefix replyPrefix;
			err = m_rpcRequester->RecvD(&replyPrefix, sizeof(replyPrefix));
			if(TCPS_OK != err)
			{
				this->OnNetworkMalformed_();
				return err;
			}

			INT_PTR leftReplyLen = replyBytes - sizeof(replyPrefix);
			ASSERT(leftReplyLen >= 0);
			if(leftReplyLen > 0)
			{
				ASSERT(replyData && replyLen);
				tcps_Binary replied_data;
				if(!replied_data.Resize(leftReplyLen))
				{
					this->OnNetworkMalformed_();
					return err;
				}
				err = m_rpcRequester->RecvD(replied_data.Get(), (int)leftReplyLen);
				if(TCPS_OK != err)
				{
					this->OnNetworkMalformed_();
					return err;
				}
				if(NULL==replyData || NULL==replyLen)
				{
					ASSERT(false);
					return TCPS_ERR_INVALID_PARAM;
				}
				INT32 bytes = 0;
				*replyData = replied_data.Drop(&bytes);
				*replyLen = bytes;
			}
		}
		else // posting callback
		{
			const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
			int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
			if(m_sessionR->m_udpSite.IsLinked())
			{
				int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
				BYTE* p = (BYTE*)tcps_Alloc(total);
				if(NULL == p)
				{
					ASSERT(false);
					return TCPS_ERR_OUT_OF_MEMORY;
				}
				BYTE* q = p;
				for(int i=0; i<reqBufVecCount; ++i)
				{
					const SockWriteBuf& swb = reqBufVec[i];
					memcpy(q, swb.data, swb.len);
					q += swb.len;
				}
				ASSERT((int)(q-p) == total);
				SockWriteBuf swb_udp;
				swb_udp.data = p;
				swb_udp.len = total;
				INT32 sessionID;
				m_rpcRequester->GetPeerSessionKey(sessionID);
				iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
				udpServer.SendSessionData(sessionID, &swb_udp, 1);
			}
			else if(0 != m_sessionR->m_postingProxy.callerKey_)
			{
				INT_PTR queueFullIndexes = -1;
				INT_PTR queueFullCount = 0;
				TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
				if(TCPS_OK != err)
					return err;
				ASSERT(0==queueFullCount || 1==queueFullCount);
				if(1 == queueFullCount)
					return TCPS_ERR_POSTING_PENDING_FULL;
			}
			else
			{
				TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
				if(TCPS_OK != err)
					return err;
			}
		}
	}
	else
	{
		ASSERT(false);
		return TCPS_ERR_INTERNAL_BUG;
	}

	return TCPS_OK;
}

TCPSError PCC_Deploy_S::SetRedirect_(
				IN const IPP& redirectIPP_wrap,
				IN const void* redirectParam_wrap, IN INT32 redirectParam_wrap_len
				) posting_callback
{
	if(m_sessionL)
	{
		// ASSERT(false); // ??
		return TCPS_ERR_REFUSED;
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_SetRedirect_)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 24;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::SetRedirect_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN IPP redirectIPP
	Put_BaseType_(&m_dataOutfiter, redirectIPP_wrap);

	// IN tcps_Binary redirectParam
	if(redirectParam_wrap_len<0 || (redirectParam_wrap_len>0 && NULL==redirectParam_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	Put_Binary_(&m_dataOutfiter, redirectParam_wrap, redirectParam_wrap_len);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
		if(TCPS_OK != err)
			return err;
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_S::SetRedirect__Batch(
				IN const PPCC_Deploy_S_* wrap_sessions,
				IN INT_PTR wrap_sessionsCount,
				IN const IPP& redirectIPP_wrap,
				IN const void* redirectParam_wrap, IN INT32 redirectParam_wrap_len,
				OUT PPCC_Deploy_S_* wrap_sendFaileds /*= NULL*/,
				OUT INT_PTR* wrap_failedCount /*= NULL*/
				) posting_callback
{
	if(wrap_failedCount)
		*wrap_failedCount= 0;

	if(NULL==wrap_sessions || wrap_sessionsCount<=0)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if((!!wrap_sendFaileds) != (!!wrap_failedCount))
	{
		ASSERT(false); // wrap_sendFaileds、wrap_failedCount要么都为NULL，要么都不为NULL
		return TCPS_ERR_INVALID_PARAM;
	}

	INT_PTR notReadies = 0;
	tcps_SmartArray<PPCC_Deploy_S_, 256> iscm_sessions_ar_;
	for(INT_PTR i=0; i<wrap_sessionsCount; ++i)
	{
		if(NULL == wrap_sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(wrap_sessions[i]->m_sessionL)
			continue;
		if(TCPS_OK != wrap_sessions[i]->UpdateCallbackMatchingFlag_())
			continue;
		if(!wrap_sessions[i]->m_callbackMatchingFlag.matching_SetRedirect_)
		{
			IPP peerIPP = wrap_sessions[i]->m_sessionR->m_peerIPP;
			NPLogWarning(("The 'PCC_Deploy::SetRedirect_()' of '%s' is not matched!", IPP_TO_STR_A(peerIPP)));
			continue;
		}
		if(0 == wrap_sessions[i]->m_sessionR->m_postingProxy.callerKey_)
		{
			if(wrap_sendFaileds)
			{
				wrap_sendFaileds[notReadies] = wrap_sessions[i];
				++notReadies;
			}
			continue;
		}
		iscm_sessions_ar_.push_back(wrap_sessions[i]);
	}
	if(0 == iscm_sessions_ar_.size())
		return TCPS_OK;

	// 准备调用数据
	tcps_SmartArray<SockWriteBuf, 256> iscm_swb_ar_;
	SockWriteBuf iscm_swb_;

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	iscm_swb_.data = &peerCallFlags;
	iscm_swb_.len = sizeof(peerCallFlags);
	iscm_swb_ar_.push_back(iscm_swb_);

	INT32 call_id_len = 24;
	iscm_swb_.data = &call_id_len;
	iscm_swb_.len = sizeof(call_id_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	iscm_swb_.data = "PCC_Deploy::SetRedirect_";
	iscm_swb_.len = call_id_len+1;
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN IPP redirectIPP
	iscm_swb_.data = &redirectIPP_wrap;
	iscm_swb_.len = sizeof(redirectIPP_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN tcps_Binary redirectParam
	if(redirectParam_wrap_len<0 || (redirectParam_wrap_len>0 && NULL==redirectParam_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	iscm_swb_.data = &redirectParam_wrap_len;
	iscm_swb_.len = sizeof(redirectParam_wrap_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	if(redirectParam_wrap_len > 0)
	{
		iscm_swb_.data = redirectParam_wrap;
		iscm_swb_.len = redirectParam_wrap_len;
		iscm_swb_ar_.push_back(iscm_swb_);
	}

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> iscm_callerKey_ar_;
	iscm_callerKey_ar_.resize(iscm_sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)iscm_sessions_ar_.size(); ++i)
		iscm_callerKey_ar_[i] = iscm_sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	if(NULL == wrap_sendFaileds)
	{
		return callerMan.BatchPosting(
							iscm_callerKey_ar_.Get(),
							iscm_callerKey_ar_.size(),
							iscm_swb_ar_.Get(),
							iscm_swb_ar_.size(),
							NULL,
							NULL
							);
	}

	ASSERT(wrap_failedCount);
	tcps_SmartArray<INT_PTR, 256> iscm_queueFullIndexesAr;
	iscm_queueFullIndexesAr.resize(iscm_callerKey_ar_.size());
	TCPSError err = callerMan.BatchPosting(
						iscm_callerKey_ar_.Get(),
						iscm_callerKey_ar_.size(),
						iscm_swb_ar_.Get(),
						iscm_swb_ar_.size(),
						iscm_queueFullIndexesAr.Get(),
						wrap_failedCount
						);
	ASSERT(0<=*wrap_failedCount && *wrap_failedCount<=(INT_PTR)iscm_queueFullIndexesAr.size());
	for(INT_PTR i=0; i<*wrap_failedCount; ++i)
		(wrap_sendFaileds+notReadies)[i] = iscm_sessions_ar_[iscm_queueFullIndexesAr[i]];
	*wrap_failedCount += notReadies;
	return err;
}

TCPSError PCC_Deploy_S::CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks_wrap,
				IN const tcps_Array<tcps_String>& callbackTypeInfos_wrap,
				OUT tcps_Array<BOOL>& matchingFlags_wrap
				) callback
{
	if(m_sessionL)
	{
		InitializeAllCallsTypeInfo_();
		ASSERT(callbacks_wrap.Length() == callbackTypeInfos_wrap.Length());
		matchingFlags_wrap.Resize(callbacks_wrap.Length());
		for(int i=0; i<callbacks_wrap.Length(); ++i)
		{
			const tcps_String& name = callbacks_wrap[i];
			const tcps_String& typeInfo = callbackTypeInfos_wrap[i];
			matchingFlags_wrap[i] = (NULL != m_sessionL->FindCallback_(name.Get(), name.Length(), typeInfo.Get(), typeInfo.Length()));
		}
		return TCPS_OK;
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 26;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::CallbackCheck_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_Array<tcps_String> callbacks
	Put_BaseType_(&m_dataOutfiter, callbacks_wrap.LenRef());
	for(int idx1=0; idx1<callbacks_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = callbacks_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// IN tcps_Array<tcps_String> callbackTypeInfos
	Put_BaseType_(&m_dataOutfiter, callbackTypeInfos_wrap.LenRef());
	for(int idx1=0; idx1<callbackTypeInfos_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = callbackTypeInfos_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_IRequester* iscm_replied_picker = m_rpcRequester;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<BOOL> matchingFlags
		PICK_PODARRAY_(iscm_replied_picker, matchingFlags_wrap);
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_S::SetTimeout_(
			IN INT32 recvTimeout,
			IN INT32 sendTimeout
			) posting_method
{
	this->SetTimeout(INFINITE, recvTimeout, sendTimeout);
	return TCPS_OK;
}

TCPSError PCC_Deploy_S::SetSessionBufferSize_(
			IN INT32 recvBufBytes,
			IN INT32 sendBufBytes
			) posting_method
{
	this->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	return TCPS_OK;
}

TCPSError PCC_Deploy_S::MethodCheck_(
			IN const tcps_Array<tcps_String>& methods,
			IN const tcps_Array<tcps_String>& methodTypeInfos,
			OUT tcps_Array<BOOL>& matchingFlags
			) method
{
	if(0==methods.Length() || methods.Length()!=methodTypeInfos.Length())
		return TCPS_ERR_INVALID_PARAM;

	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<19> > MethodMap_;
	static MethodMap_* s_mdMap = NULL;
	if(NULL == s_mdMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_mdMap)
		{
			static MethodMap_ s_mdMapObj;
			MethodMap_& mdMap = s_mdMapObj;
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Login"), CPtrStrA(s_PCC_Deploy_Login_TypeInfo_, s_PCC_Deploy_Login_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Logout"), CPtrStrA(s_PCC_Deploy_Logout_TypeInfo_, s_PCC_Deploy_Logout_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("CreateTrunk"), CPtrStrA(s_PCC_Deploy_CreateTrunk_TypeInfo_, s_PCC_Deploy_CreateTrunk_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveTrunk"), CPtrStrA(s_PCC_Deploy_RemoveTrunk_TypeInfo_, s_PCC_Deploy_RemoveTrunk_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListTrunk"), CPtrStrA(s_PCC_Deploy_ListTrunk_TypeInfo_, s_PCC_Deploy_ListTrunk_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddAuthCenter"), CPtrStrA(s_PCC_Deploy_AddAuthCenter_TypeInfo_, s_PCC_Deploy_AddAuthCenter_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveAuthCenter"), CPtrStrA(s_PCC_Deploy_RemoveAuthCenter_TypeInfo_, s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListAuthCenter"), CPtrStrA(s_PCC_Deploy_ListAuthCenter_TypeInfo_, s_PCC_Deploy_ListAuthCenter_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("FindAuthCenter"), CPtrStrA(s_PCC_Deploy_FindAuthCenter_TypeInfo_, s_PCC_Deploy_FindAuthCenter_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModule"), CPtrStrA(s_PCC_Deploy_AddModule_TypeInfo_, s_PCC_Deploy_AddModule_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModuleFile"), CPtrStrA(s_PCC_Deploy_AddModuleFile_TypeInfo_, s_PCC_Deploy_AddModuleFile_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveModule"), CPtrStrA(s_PCC_Deploy_RemoveModule_TypeInfo_, s_PCC_Deploy_RemoveModule_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveModuleFiles"), CPtrStrA(s_PCC_Deploy_RemoveModuleFiles_TypeInfo_, s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListModules"), CPtrStrA(s_PCC_Deploy_ListModules_TypeInfo_, s_PCC_Deploy_ListModules_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModel"), CPtrStrA(s_PCC_Deploy_AddModel_TypeInfo_, s_PCC_Deploy_AddModel_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListModels"), CPtrStrA(s_PCC_Deploy_ListModels_TypeInfo_, s_PCC_Deploy_ListModels_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("DelModel"), CPtrStrA(s_PCC_Deploy_DelModel_TypeInfo_, s_PCC_Deploy_DelModel_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetTimeout_"), CPtrStrA(s_PCC_Deploy_SetTimeout__TypeInfo_, s_PCC_Deploy_SetTimeout__TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetSessionBufferSize_"), CPtrStrA(s_PCC_Deploy_SetSessionBufferSize__TypeInfo_, s_PCC_Deploy_SetSessionBufferSize__TypeInfo_len_))).second);
			s_mdMap = &mdMap;
		}
	}

	matchingFlags.Resize(methods.Length());
	for(int index=0; index<methods.Length(); ++index)
	{
		BOOL& flag = matchingFlags[index];
		const tcps_String& name = methods[index];
		const tcps_String& typeInfos = methodTypeInfos[index];
		MethodMap_::const_iterator cit = s_mdMap->find(name.Get(), name.Length());
		if(cit!=s_mdMap->end() && 0==typeInfos.Compare(cit->second.p, cit->second.len))
			flag = true;
		else
			flag = false;
	}
	return TCPS_OK;
}

void PCC_Deploy_S::CloseSession(
				IN TCPSError cause /*= TCPS_OK*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		m_sessionR->CloseSession_(cause);
	else if(m_sessionL)
	{
		AutoFlag<OSThreadID> autoClosingTID(m_closingTID_L.tid, OSThreadSelf());
		m_sessionL->CloseSession_();
	}
}

IPP PCC_Deploy_S::GetPeerIPP(
				OUT IPP* peerID /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
	{
		if(peerID)
			*peerID = m_sessionR->m_peerID_IPP;
		return m_sessionR->m_peerIPP;
	}

	if(m_sessionL)
	{
		if(peerID)
			*peerID = IPP((DWORD)0, (int)0);
		return IPP((DWORD)0, (int)0);
	}

	if(peerID)
		*peerID = INVALID_IPP;
	return INVALID_IPP;
}

BOOL PCC_Deploy_S::IsLocalPeer() const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	return (NULL != m_sessionL);
}

void PCC_Deploy_S::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		m_sessionR->m_postingPendingParam.Set(maxPendingBytes, maxPendings);
}

void PCC_Deploy_S::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(maxPendingBytes)
			*maxPendingBytes = 0;
		if(maxPendings)
			*maxPendings = 0;
		return;
	}
	m_sessionR->m_postingPendingParam.Get(maxPendingBytes, maxPendings);
}

BOOL PCC_Deploy_S::CallbackIsReady() const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		return (m_sessionR->m_callbackRequester.face_ && m_sessionR->m_callbackRequester.face_->IsConnected());
	return true;
}

TCPSError PCC_Deploy_S::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
		return TCPS_OK;
	if(NULL == m_sessionR->m_callbackRequester.face_)
		return TCPS_ERR_CALLBACK_NOT_READY;
	m_sessionR->m_callbackRequester.face_->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	return TCPS_OK;
}

TCPSError PCC_Deploy_S::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(connectTimeout)
			*connectTimeout = INFINITE;
		if(recvTimeout)
			*recvTimeout = INFINITE;
		if(sendTimeout)
			*sendTimeout = INFINITE;
		return TCPS_OK;
	}

	if(NULL == m_sessionR->m_callbackRequester.face_)
		return TCPS_ERR_CALLBACK_NOT_READY;
	m_sessionR->m_callbackRequester.face_->GetTimeout(connectTimeout, recvTimeout, sendTimeout);
	return TCPS_OK;
}

void PCC_Deploy_S::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
		return;

	if(recvBufBytes>=0 || sendBufBytes>=0)
	{
		SOCKET sock = INVALID_SOCKET;
		m_sessionR->m_bindedSession->GetInfos(NULL, &sock, NULL, NULL, NULL);
		ASSERT(SockValid(sock));
		if(recvBufBytes >= 0)
			SockSetReceiveBufSize(sock, (0==recvBufBytes ? TCPS_DEFAULT_RECVBUF_SIZE : recvBufBytes));
		if(sendBufBytes >= 0)
			SockSetSendBufSize(sock, (0==sendBufBytes ? TCPS_DEFAULT_SENDBUF_SIZE : sendBufBytes));
	}
	if(m_sessionR->m_callbackRequester.face_)
		m_sessionR->m_callbackRequester.face_->SetSessionBufferSize(recvBufBytes, sendBufBytes);
}

void PCC_Deploy_S::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(recvBufBytes)
			*recvBufBytes = 0;
		if(sendBufBytes)
			*sendBufBytes = 0;
		return;
	}

	if(NULL==recvBufBytes && NULL==sendBufBytes)
		return;
	if(m_sessionR->m_callbackRequester.face_)
	{
		m_sessionR->m_callbackRequester.face_->GetSessionBufferSize(recvBufBytes, sendBufBytes);
	}
	else
	{
		SOCKET sock = INVALID_SOCKET;
		m_sessionR->m_bindedSession->GetInfos(NULL, &sock, NULL, NULL, NULL);
		ASSERT(SockValid(sock));
		if(recvBufBytes)
			SockGetReceiveBufSize(sock, recvBufBytes);
		if(sendBufBytes)
			SockGetSendBufSize(sock, sendBufBytes);
	}
}

void PCC_Deploy_S::SetPostingSendParameters(
				IN INT32 maxBufferingSize,
				IN INT32 maxSendings
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR && 0!=m_sessionR->m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().SetBufferingParam(m_sessionR->m_postingProxy.callerKey_, maxBufferingSize, maxSendings);
	m_postingSendParam.Set(maxBufferingSize, maxSendings);
}

void PCC_Deploy_S::GetPostingSendParameters(
				OUT INT32* maxBufferingSize /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(maxBufferingSize)
			*maxBufferingSize = 0;
		if(maxSendings)
			*maxSendings = 0;
		return;
	}
	m_postingSendParam.Get(maxBufferingSize, maxSendings);
}

TCPSError PCC_Deploy_S::CleanPostingSendingQueue()
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(NULL==m_sessionR || 0==m_sessionR->m_postingProxy.callerKey_)
		return TCPS_ERR_CALL_WAS_IGNORED;
	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(&m_sessionR->m_postingProxy.callerKey_, 1);
}

TCPSError PCC_Deploy_S::CleanPostingSendingQueue(
				IN const PPCC_Deploy_S_* sessions,
				IN INT_PTR sessionsCount
				)
{
	tcps_SmartArray<PPCC_Deploy_S_, 256> sessions_ar_;
	for(INT_PTR i=0; i<sessionsCount; ++i)
	{
		if(NULL == sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(NULL==sessions[i]->m_sessionR || 0==sessions[i]->m_sessionR->m_postingProxy.callerKey_)
			continue;
		sessions_ar_.push_back(sessions[i]);
	}
	if(0 == sessions_ar_.size())
		return TCPS_OK;

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> callerKey_ar_;
	callerKey_ar_.resize(sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)sessions_ar_.size(); ++i)
		callerKey_ar_[i] = sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(callerKey_ar_.Get(), (int)callerKey_ar_.size());
}

class PCC_Deploy_LS : public IPCC_Deploy_LocalMethod
{
private:
	PCC_Deploy_LS(const PCC_Deploy_LS&);
	PCC_Deploy_LS& operator= (const PCC_Deploy_LS&);

private:
	PCC_CenterSessionMaker& m_sessionMaker;
	IPCC_Deploy_LocalCallback* const m_callback;
	PCC_Deploy_S* const m_method;
	TCPSError m_connectError;
	INT32 m_sessionKey;

public:
	TCPSError GetConnectError() const
		{	return m_connectError;	}

public:
	PCC_Deploy_LS(const IPP& clientID_IPP, PCC_CenterSessionMaker& sessionMaker, IPCC_Deploy_LocalCallback* callbackHandler)
		: m_sessionMaker(sessionMaker)
		, m_callback(callbackHandler)
		, m_method(tcps_NewEx(PCC_Deploy_S, (m_sessionMaker, NULL, callbackHandler)))
		, m_connectError(TCPS_ERROR)
		, m_sessionKey(0)
	{
		INT32 sessionCount;
		m_sessionMaker.OnSessionConnect_(&m_sessionKey, sessionCount);
		m_connectError = m_method->OnConnected(m_sessionKey, clientID_IPP, sessionCount);
		if(TCPS_OK == m_connectError)
		{
			if(m_callback)
				m_method->OnCallbackReady();
			m_method->OnPostingCallReady();
			m_sessionMaker.RegisterLocalSession_(m_callback);
		}
	}
	virtual ~PCC_Deploy_LS()
	{
		if(TCPS_OK == m_connectError)
			m_sessionMaker.UnregisterLocalSession_(m_callback);
		m_sessionMaker.Unregister(m_method);
		if(INVALID_OSTHREADID==m_method->m_closingTID_L.tid || m_method->m_closingTID_L.tid!=OSThreadSelf())
			m_method->OnPeerBroken(m_sessionKey, TCPS_ANY_IPP, m_connectError);
		m_method->OnClose(m_sessionKey, TCPS_ANY_IPP, m_connectError);
		m_sessionMaker.OnSessionClosed_();
		m_method->~PCC_Deploy_S();
		tcps_Free(m_method);
	}
	virtual void DeleteThis()
		{	tcps_Delete(this);	}

	virtual PROC FindMethod_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				)
	{
		if(NULL == name)
		{
			ASSERT(false);
			return NULL;
		}

		// 对OnStreamedCall_L_()特殊处理
		if(nameLen<0 && 0==strcmp("OnStreamedCall_L_", name))
			return (PROC)&OnStreamedCall_L_;

		if(NULL == type)
		{
			ASSERT(false);
			return NULL;
		}

		InitializeAllCallsTypeInfo_();
		typedef TwoItems<CPtrStrA, PROC> FuncPair;
		typedef CQuickStringMap<CPtrStrA, FuncPair, QSS_Traits<17> > MethodMap_;
		static MethodMap_* s_mdMap = NULL;
		if(NULL == s_mdMap)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == s_mdMap)
			{
				static MethodMap_ s_mdMapObj;
				MethodMap_& mdMap = s_mdMapObj;
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Login"), FuncPair(CPtrStrA(s_PCC_Deploy_Login_TypeInfo_, s_PCC_Deploy_Login_TypeInfo_len_), (PROC)&Login)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Logout"), FuncPair(CPtrStrA(s_PCC_Deploy_Logout_TypeInfo_, s_PCC_Deploy_Logout_TypeInfo_len_), (PROC)&Logout)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("CreateTrunk"), FuncPair(CPtrStrA(s_PCC_Deploy_CreateTrunk_TypeInfo_, s_PCC_Deploy_CreateTrunk_TypeInfo_len_), (PROC)&CreateTrunk)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveTrunk"), FuncPair(CPtrStrA(s_PCC_Deploy_RemoveTrunk_TypeInfo_, s_PCC_Deploy_RemoveTrunk_TypeInfo_len_), (PROC)&RemoveTrunk)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListTrunk"), FuncPair(CPtrStrA(s_PCC_Deploy_ListTrunk_TypeInfo_, s_PCC_Deploy_ListTrunk_TypeInfo_len_), (PROC)&ListTrunk)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddAuthCenter"), FuncPair(CPtrStrA(s_PCC_Deploy_AddAuthCenter_TypeInfo_, s_PCC_Deploy_AddAuthCenter_TypeInfo_len_), (PROC)&AddAuthCenter)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveAuthCenter"), FuncPair(CPtrStrA(s_PCC_Deploy_RemoveAuthCenter_TypeInfo_, s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_), (PROC)&RemoveAuthCenter)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListAuthCenter"), FuncPair(CPtrStrA(s_PCC_Deploy_ListAuthCenter_TypeInfo_, s_PCC_Deploy_ListAuthCenter_TypeInfo_len_), (PROC)&ListAuthCenter)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("FindAuthCenter"), FuncPair(CPtrStrA(s_PCC_Deploy_FindAuthCenter_TypeInfo_, s_PCC_Deploy_FindAuthCenter_TypeInfo_len_), (PROC)&FindAuthCenter)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModule"), FuncPair(CPtrStrA(s_PCC_Deploy_AddModule_TypeInfo_, s_PCC_Deploy_AddModule_TypeInfo_len_), (PROC)&AddModule)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModuleFile"), FuncPair(CPtrStrA(s_PCC_Deploy_AddModuleFile_TypeInfo_, s_PCC_Deploy_AddModuleFile_TypeInfo_len_), (PROC)&AddModuleFile)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveModule"), FuncPair(CPtrStrA(s_PCC_Deploy_RemoveModule_TypeInfo_, s_PCC_Deploy_RemoveModule_TypeInfo_len_), (PROC)&RemoveModule)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveModuleFiles"), FuncPair(CPtrStrA(s_PCC_Deploy_RemoveModuleFiles_TypeInfo_, s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_), (PROC)&RemoveModuleFiles)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListModules"), FuncPair(CPtrStrA(s_PCC_Deploy_ListModules_TypeInfo_, s_PCC_Deploy_ListModules_TypeInfo_len_), (PROC)&ListModules)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModel"), FuncPair(CPtrStrA(s_PCC_Deploy_AddModel_TypeInfo_, s_PCC_Deploy_AddModel_TypeInfo_len_), (PROC)&AddModel)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListModels"), FuncPair(CPtrStrA(s_PCC_Deploy_ListModels_TypeInfo_, s_PCC_Deploy_ListModels_TypeInfo_len_), (PROC)&ListModels)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("DelModel"), FuncPair(CPtrStrA(s_PCC_Deploy_DelModel_TypeInfo_, s_PCC_Deploy_DelModel_TypeInfo_len_), (PROC)&DelModel)));
				s_mdMap = &mdMap;
			}
		}

		MethodMap_::iterator it = s_mdMap->find(name, nameLen);
		if(s_mdMap->end() == it)
			return NULL;
		const CPtrStrA& ps = it->second.first;
		if(0 != ps.Compare(type, typeLen))
			return NULL;
		return it->second.second;
	}

private:
	static TCPSError OnStreamedCall_L_(
				IN void* sessionObj,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
	{	return ((PCC_Deploy_LS*)sessionObj)->m_method->OnStreamedCall_L_(
					methodName,
					nameLen,
					data,
					dataLen,
					replyData,
					replyLen
					);
	}

private:
	static TCPSError Login(
				IN void* sessionObj_wrap,
				IN const tcps_String& ticket
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->Login(
					ticket
					);
	}

	static TCPSError Logout(
				IN void* sessionObj_wrap
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->Logout(
					);
	}

	static TCPSError CreateTrunk(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->CreateTrunk(
					trunk
					);
	}

	static TCPSError RemoveTrunk(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->RemoveTrunk(
					trunk
					);
	}

	static TCPSError ListTrunk(
				IN void* sessionObj_wrap,
				OUT tcps_Array<tcps_String>& trunks
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->ListTrunk(
					trunks
					);
	}

	static TCPSError AddAuthCenter(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag,
				IN const tcps_Array<PCC_ModuleFile>& files
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->AddAuthCenter(
					trunk,
					authTag,
					files
					);
	}

	static TCPSError RemoveAuthCenter(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->RemoveAuthCenter(
					trunk,
					authTag
					);
	}

	static TCPSError ListAuthCenter(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_Tag>& authTags
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->ListAuthCenter(
					trunk,
					authTags
					);
	}

	static TCPSError FindAuthCenter(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->FindAuthCenter(
					trunk,
					authTag
					);
	}

	static TCPSError AddModule(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN INT64 modelKey,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles,
				OUT INT64& moduleKey
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->AddModule(
					trunk,
					modelKey,
					moduleProperty,
					moudleFiles,
					moduleKey
					);
	}

	static TCPSError AddModuleFile(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->AddModuleFile(
					trunk,
					moduleKey,
					fileType,
					moduleFiles
					);
	}

	static TCPSError RemoveModule(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN INT64 moduleKey
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->RemoveModule(
					trunk,
					moduleKey
					);
	}

	static TCPSError RemoveModuleFiles(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN INT32 fileType
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->RemoveModuleFiles(
					trunk,
					moduleKey,
					fileType
					);
	}

	static TCPSError ListModules(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->ListModules(
					trunk,
					modulesInfo
					);
	}

	static TCPSError AddModel(
				IN void* sessionObj_wrap,
				IN const PCC_ModelProperty& modelProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->AddModel(
					modelProperty,
					modelFiles
					);
	}

	static TCPSError ListModels(
				IN void* sessionObj_wrap,
				OUT tcps_Array<PCC_ModelPropWithKey>& modelsInfo
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->ListModels(
					modelsInfo
					);
	}

	static TCPSError DelModel(
				IN void* sessionObj_wrap,
				IN INT64 modelKey
				) method
	{	return ((PCC_Deploy_LS*)sessionObj_wrap)->m_method->DelModel(
					modelKey
					);
	}
};

TCPSError MakeLocalSession_PCC_Deploy__(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_Deploy_LocalMethod*& methodHandler,
			IN IPCC_Deploy_LocalCallback* callbackHandler
			)
{
	PCC_Deploy_LS* session = tcps_NewEx(PCC_Deploy_LS, (clientID_IPP, sessionMaker, callbackHandler));
	if(NULL == session)
		return TCPS_ERR_OUT_OF_MEMORY;
	TCPSError err = session->GetConnectError();
	if(TCPS_OK != err)
	{
		tcps_Delete(session);
		return err;
	}
	methodHandler = session;
	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_GetPccProperty(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_User",
					"GetPccProperty",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::GetPccProperty() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT PCC_User_T::PCCProperty pccProp;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->GetPccProperty(
			opWrapper->pccProp
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::GetPccProperty(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::GetPccProperty(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT PCCProperty pccProp
	OUT const PCC_User_T::PCCProperty& pccProp_wrap = opWrapper->pccProp;
		Set_String_(outfiter, pccProp_wrap.version);

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_ListNodes(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_User",
					"ListNodes",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::ListNodes() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<PCC_NodeDesc> nodes;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->ListNodes(
			opWrapper->nodes
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::ListNodes(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::ListNodes(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<PCC_NodeDesc> nodes
	OUT const tcps_Array<PCC_NodeDesc>& nodes_wrap = opWrapper->nodes;
	Set_BaseType_(outfiter, nodes_wrap.LenRef());
	for(int idx1=0; idx1<nodes_wrap.Length(); ++idx1)
	{
		const PCC_NodeDesc& ref1 = nodes_wrap[idx1];
			Set_String_(outfiter, ref1.name);
			Set_BaseType_(outfiter, ref1.cpuType);
			Set_BaseType_(outfiter, ref1.cpuFreq);
			Set_BaseType_(outfiter, ref1.cpuProcessors);
			Set_BaseType_(outfiter, ref1.cpuThreads);
			Set_BaseType_(outfiter, ref1.totalMemoryBytes);
			Set_BaseType_(outfiter, ref1.networkBandwidth);
			Set_BaseType_(outfiter, ref1.osType);
			Set_String_(outfiter, ref1.osDetail);
			Set_BaseType_(outfiter, ref1.executeBits);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_GetNodeDynamicContext(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_User",
					"GetNodeDynamicContext",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String nodeName
	IN tcps_String nodeName_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, nodeName_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::GetNodeDynamicContext() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT PCC_DynamicContext dynamicContext;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->GetNodeDynamicContext(
			nodeName_wrap,
			opWrapper->dynamicContext
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::GetNodeDynamicContext(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::GetNodeDynamicContext(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT PCC_DynamicContext dynamicContext
	OUT const PCC_DynamicContext& dynamicContext_wrap = opWrapper->dynamicContext;
	Set_BaseType_(outfiter, dynamicContext_wrap);

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_ListModules(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_User",
					"ListModules",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_String regex
	IN tcps_String regex_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, regex_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::ListModules() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<PCC_ModuleInfo> modulesInfo;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->ListModules(
			regex_wrap,
			opWrapper->modulesInfo
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::ListModules(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::ListModules(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<PCC_ModuleInfo> modulesInfo
	OUT const tcps_Array<PCC_ModuleInfo>& modulesInfo_wrap = opWrapper->modulesInfo;
	Set_BaseType_(outfiter, modulesInfo_wrap.LenRef());
	for(int idx1=0; idx1<modulesInfo_wrap.Length(); ++idx1)
	{
		const PCC_ModuleInfo& ref1 = modulesInfo_wrap[idx1];
			Set_BaseType_(outfiter, ref1.moduleKey);
				Set_String_(outfiter, ref1.moduleTag.name);
				Set_BaseType_(outfiter, ref1.moduleTag.version);
			Set_BaseType_(outfiter, ref1.modulePattern);
			Set_BaseType_(outfiter, ref1.moduleType);
			Set_String_(outfiter, ref1.description);
			Set_BaseType_(outfiter, ref1.moduleFileType);
			Set_BaseType_(outfiter, ref1.moduleLatency);
			Set_BaseType_(outfiter, ref1.addTime);
			Set_BaseType_(outfiter, ref1.moduleSize);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_Execute(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_User",
					"Execute",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT64 moduleKey
	IN INT64 moduleKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleKey_wrap);

	// IN tcps_String inputUrl
	IN tcps_String inputUrl_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, inputUrl_wrap);

	// IN tcps_String outputUrl
	IN tcps_String outputUrl_wrap;
	GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, outputUrl_wrap);

	// IN tcps_Binary moduleParams
	IN tcps_Binary moduleParams_wrap;
	GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleParams_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::Execute() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT INT64 jobKey;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->Execute(
			moduleKey_wrap,
			inputUrl_wrap,
			outputUrl_wrap,
			moduleParams_wrap,
			opWrapper->jobKey
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::Execute(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::Execute(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT INT64 jobKey
	OUT const INT64& jobKey_wrap = opWrapper->jobKey;
	Set_BaseType_(outfiter, jobKey_wrap);

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_QueryJobs(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		void* replyData = NULL;
		INT_PTR replyLen = 0;
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_User",
					"QueryJobs",
					ptrInParams,
					ptrInParamsLen,
					&replyData,
					&replyLen
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		ASSERT(outfiter);
		iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
		replyPrefix->Init();
		outfiter->Push(replyPrefix, sizeof(*replyPrefix), true, NULL);
		if(replyLen > 0)
			outfiter->Push(replyData, replyLen, true, NULL);
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_Array<INT64> jobsKey
	IN tcps_Array<INT64> jobsKey_wrap;
	GET_PODARRAY_EX_(thisObj, ptrInParams, ptrInParamsLen, jobsKey_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::QueryJobs() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<ExecuteState> jobsState;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->QueryJobs(
			jobsKey_wrap,
			opWrapper->jobsState
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::QueryJobs(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::QueryJobs(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<ExecuteState> jobsState
	OUT const tcps_Array<ExecuteState>& jobsState_wrap = opWrapper->jobsState;
	Set_PODArray_(outfiter, jobsState_wrap);

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_CancelJob(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	if(thisObj && thisObj->m_streamedCallSite.func)
	{
		errTcps = thisObj->m_streamedCallSite.func(
					thisObj->m_streamedCallSite.serverObj,
					thisObj->m_streamedCallSite.sessionObj,
					"PCC_User",
					"CancelJob",
					ptrInParams,
					ptrInParamsLen,
					NULL,
					NULL
					);
		if(TCPS_OK == errTcps)
		{
			ptrInParams += ptrInParamsLen;
			ptrInParamsLen = 0;
		}
		return errTcps;
	}

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT64 jobKey
	IN INT64 jobKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, jobKey_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::CancelJob() posting_method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->CancelJob(
			jobKey_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::CancelJob(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::CancelJob(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_UDPLink_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::UDPLink_() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT INT32 servePort;
		OUT INT32 linkKey;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->UDPLink_(
			opWrapper->servePort,
			opWrapper->linkKey
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::UDPLink_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::UDPLink_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT INT32 servePort
	OUT const INT32& servePort_wrap = opWrapper->servePort;
	Set_BaseType_(outfiter, servePort_wrap);

	// OUT INT32 linkKey
	OUT const INT32& linkKey_wrap = opWrapper->linkKey;
	Set_BaseType_(outfiter, linkKey_wrap);

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_UDPLinkConfirm_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::UDPLinkConfirm_() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->UDPLinkConfirm_(
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::UDPLinkConfirm_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::UDPLinkConfirm_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_SetTimeout_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT32 recvTimeout
	IN INT32 recvTimeout_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, recvTimeout_wrap);

	// IN INT32 sendTimeout
	IN INT32 sendTimeout_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, sendTimeout_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::SetTimeout_() posting_method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->SetTimeout_(
			recvTimeout_wrap,
			sendTimeout_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::SetTimeout_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::SetTimeout_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_SetSessionBufferSize_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT32 recvBufBytes
	IN INT32 recvBufBytes_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, recvBufBytes_wrap);

	// IN INT32 sendBufBytes
	IN INT32 sendBufBytes_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, sendBufBytes_wrap);

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::SetSessionBufferSize_() posting_method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->SetSessionBufferSize_(
			recvBufBytes_wrap,
			sendBufBytes_wrap
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::SetSessionBufferSize_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::SetSessionBufferSize_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_CenterSession::Wrap_PCC_User_MethodCheck_(
				IN PCC_CenterSession* thisObj,
				IN void* faceObj,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) method
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_Array<tcps_String> methods
	IN tcps_Array<tcps_String> methods_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	methods_wrap.Resize(array_len);
	for(int idx1=0; idx1<methods_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = methods_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	// IN tcps_Array<tcps_String> methodTypeInfos
	IN tcps_Array<tcps_String> methodTypeInfos_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	methodTypeInfos_wrap.Resize(array_len);
	for(int idx1=0; idx1<methodTypeInfos_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = methodTypeInfos_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	if(0 != ptrInParamsLen)
	{
		NPLogError(("PCC_User_S::MethodCheck_() method, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<BOOL> matchingFlags;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的方法函数
	try
	{
		PCC_User_S* pCC_UserObj_wrap;
		if(thisObj)
			pCC_UserObj_wrap = thisObj->m_pCC_User;
		else
			pCC_UserObj_wrap = (PCC_User_S*)faceObj;
		ASSERT(pCC_UserObj_wrap);
		errTcps = pCC_UserObj_wrap->MethodCheck_(
			methods_wrap,
			methodTypeInfos_wrap,
			opWrapper->matchingFlags
			);
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		NPLogError(("PCC_User_S::MethodCheck_(), Out of memory"));
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		NPLogError(("PCC_User_S::MethodCheck_(), Unknown exception"));
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<BOOL> matchingFlags
	OUT const tcps_Array<BOOL>& matchingFlags_wrap = opWrapper->matchingFlags;
	Set_PODArray_(outfiter, matchingFlags_wrap);

	return TCPS_OK;
}

PCC_User_S::CallbackMatchingFlag::CallbackMatchingFlag()
{
	Reset();
	cbmap_.insert(std::make_pair(CPtrStrA("OnExecuted", 10), Info(&matching_OnExecuted, true)));
	cbmap_.insert(std::make_pair(CPtrStrA("OnExecuted1", 11), Info(&matching_OnExecuted1, true)));
	cbmap_.insert(std::make_pair(CPtrStrA("SetRedirect_", 12), Info(&matching_SetRedirect_, true)));
}

void PCC_User_S::CallbackMatchingFlag::Reset()
{
	matching_OnExecuted = false;
	matching_OnExecuted1 = false;
	matching_SetRedirect_ = false;
}

TCPSError PCC_User_S::UpdateCallbackMatchingFlag_()
{
	if(!m_callbackMatchingUpdatedFlag.needUpdate)
		return TCPS_OK;
	InitializeAllCallsTypeInfo_();
	tcps_String callbacks_ar[3];
	IN tcps_Array<tcps_String> callbacks;
	callbacks.Attach(xat_bind, callbacks_ar, 3);
	tcps_String callbackTypeInfos_ar[3];
	IN tcps_Array<tcps_String> callbackTypeInfos;
	callbackTypeInfos.Attach(xat_bind, callbackTypeInfos_ar, 3);
	callbacks_ar[0].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("OnExecuted"));
	callbackTypeInfos_ar[0].Attach(xat_bind, (char*)s_PCC_User_OnExecuted_TypeInfo_, s_PCC_User_OnExecuted_TypeInfo_len_);
	callbacks_ar[1].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("OnExecuted1"));
	callbackTypeInfos_ar[1].Attach(xat_bind, (char*)s_PCC_User_OnExecuted1_TypeInfo_, s_PCC_User_OnExecuted1_TypeInfo_len_);
	callbacks_ar[2].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetRedirect_"));
	callbackTypeInfos_ar[2].Attach(xat_bind, (char*)s_PCC_User_SetRedirect__TypeInfo_, s_PCC_User_SetRedirect__TypeInfo_len_);
	OUT tcps_Array<BOOL> matchingFlags;
	TCPSError err = this->CallbackCheck_(callbacks, callbackTypeInfos, matchingFlags);
	if(TCPS_OK == err)
	{
		if(matchingFlags.Length() == callbacks.Length())
		{
			m_callbackMatchingUpdatedFlag.needUpdate = false;
			const BOOL* const matchingFlags_p = matchingFlags.Get();
			m_callbackMatchingFlag.matching_OnExecuted = matchingFlags_p[0];
			m_callbackMatchingFlag.matching_OnExecuted1 = matchingFlags_p[1];
			m_callbackMatchingFlag.matching_SetRedirect_ = matchingFlags_p[2];
		}
		else
		{
			ASSERT(false);
			err = TCPS_ERR_MALFORMED_REPLY;
		}
	}
	if(m_callbackMatchingUpdatedFlag.needUpdate)
		m_callbackMatchingFlag.Reset();
	return err;
}

const PCC_User_S::CallbackMatchingFlag& PCC_User_S::GetCallbackMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	TCPSError ret = UpdateCallbackMatchingFlag_();
	if(err)
		*err = ret;
	return m_callbackMatchingFlag;
}

TCPSError PCC_User_S::OnStreamedCall_L_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	INT_PTR inParamsDataLen = sizeof(iscm_PeerCallFlags);
	inParamsDataLen += 10; // "PCC_User::"
	if(nameLen < 0)
		nameLen = strlen(methodName);
	inParamsDataLen += sizeof(INT32)+nameLen+1;
	inParamsDataLen += dataLen;
	BYTE* const inParamsData = (BYTE*)tcps_Alloc(inParamsDataLen);
	if(NULL == inParamsData)
		return TCPS_ERR_OUT_OF_MEMORY;

	BYTE* p = inParamsData;
	iscm_PeerCallFlags& peerCallFlags = *(iscm_PeerCallFlags*)p;
	peerCallFlags.sizeofBOOL_req = sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1; // ??
	peerCallFlags.dummy_15 = 0;
	p += sizeof(iscm_PeerCallFlags);
	*(INT32*)p = 10+(INT32)nameLen;
	p += sizeof(INT32);
	strncpy((char*)p, "PCC_User::", 10);
	p += 10;
	strncpy((char*)p, methodName, nameLen);
	p += nameLen;
	*(char*)p = 0;
	p += 1;
	memcpy(p, data, dataLen);
	p += dataLen;
	ASSERT(p-inParamsData == inParamsDataLen);

	BOOL requireReplyData = true;
	BOOL dataTransferred = false;
	iscm_RPCDataOutfiter outfiter;
	ASSERT(NULL==m_sessionR && m_sessionL);
	TCPSError err = PCC_CenterSession::OnRPCCall_(NULL, this, requireReplyData, inParamsData, dataTransferred, inParamsDataLen, &outfiter);
	tcps_Free(inParamsData);
	if(TCPS_OK != err)
		return err;
	// outfiter.swbBufs_[0]总指向iscm_RPCDataOutfiter::reply_
	// outfiter.swbBufs_[1]为iscm_RPCReplyPrefix replyPrefix
	ASSERT(outfiter.swbBufs_.size()==1 || outfiter.swbBufs_.size()>=2);
	if(outfiter.swbBufs_.size() >= 2)
	{
		ASSERT(replyData && replyLen);
		*replyLen = SockTotalizeWriteBufVec(outfiter.swbBufs_.Get()+2, outfiter.swbBufs_.size()-2);
		*replyData = tcps_Alloc(*replyLen);
		BYTE* q = (BYTE*)*replyData;
		for(INT_PTR i=2; i<(INT_PTR)outfiter.swbBufs_.size(); ++i)
		{
			const SockWriteBuf& swb = outfiter.swbBufs_[i];
			memcpy(q, swb.data, swb.len);
			q += swb.len;
		}
		ASSERT(q-(BYTE*)*replyData == *replyLen);
	}
	return err;
}

TCPSError PCC_User_S::StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;
	if(NULL==callbackName || 0==nameLen)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if(nameLen < 0)
		nameLen = strlen(callbackName);

	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnOnStreamedCallback_L_;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("OnStreamedCallback_L_", -1, NULL, 0);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_User_LocalCallback::FN_OnStreamedCallback_L_)callbackFuncL)(
					m_sessionL,
					callbackName,
					nameLen,
					data,
					dataLen,
					replyData,
					replyLen
					);
	}
	else if(m_sessionR)
	{
		iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
		if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
			return TCPS_ERR_CALLBACK_NOT_READY;
		DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;
		iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
		ASSERT(0 == m_dataOutfiter.bufs_.size());

		TCPSError errUpdate = UpdateCallbackMatchingFlag_();
		if(TCPS_OK != errUpdate)
			return errUpdate;
		CallbackMatchingFlag::CallbackMap::const_iterator itCallback = m_callbackMatchingFlag.cbmap_.find(callbackName, nameLen);
		if(m_callbackMatchingFlag.cbmap_.end() == itCallback)
			return TCPS_ERR_CALLBACK_NOT_MATCH;
		ASSERT(itCallback->second.pMatchingVar);
		if(!*(itCallback->second.pMatchingVar))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

		// 填充基本类型数据到outfiter
		iscm_PeerCallFlags peerCallFlags;
		peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
		peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
		peerCallFlags.requireReply = !(itCallback->second.isPosting);
		peerCallFlags.dummy_15 = 0;
		m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

		INT32 call_id_len = (INT32)(10+nameLen);
		CSmartBuf<char, 256> call_id_buf(call_id_len+1);
		strncpy(call_id_buf.Get(), "PCC_User::", 10);
		StrAssign(call_id_buf.Get()+10, callbackName, nameLen);
		m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
		m_dataOutfiter.Push(call_id_buf.Get(), call_id_len+1);

		// 填充IN参数到outfiter
		if(dataLen > 0)
			m_dataOutfiter.Push(data, dataLen);

		// 调用PRCCall()
		if(peerCallFlags.requireReply) // callback
		{
			const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
			int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
			int replyBytes = 0;
			TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
			if(TCPS_OK != err)
				return err;

			iscm_RPCReplyPrefix replyPrefix;
			err = m_rpcRequester->RecvD(&replyPrefix, sizeof(replyPrefix));
			if(TCPS_OK != err)
			{
				this->OnNetworkMalformed_();
				return err;
			}

			INT_PTR leftReplyLen = replyBytes - sizeof(replyPrefix);
			ASSERT(leftReplyLen >= 0);
			if(leftReplyLen > 0)
			{
				ASSERT(replyData && replyLen);
				tcps_Binary replied_data;
				if(!replied_data.Resize(leftReplyLen))
				{
					this->OnNetworkMalformed_();
					return err;
				}
				err = m_rpcRequester->RecvD(replied_data.Get(), (int)leftReplyLen);
				if(TCPS_OK != err)
				{
					this->OnNetworkMalformed_();
					return err;
				}
				if(NULL==replyData || NULL==replyLen)
				{
					ASSERT(false);
					return TCPS_ERR_INVALID_PARAM;
				}
				INT32 bytes = 0;
				*replyData = replied_data.Drop(&bytes);
				*replyLen = bytes;
			}
		}
		else // posting callback
		{
			const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
			int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
			if(m_sessionR->m_udpSite.IsLinked())
			{
				int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
				BYTE* p = (BYTE*)tcps_Alloc(total);
				if(NULL == p)
				{
					ASSERT(false);
					return TCPS_ERR_OUT_OF_MEMORY;
				}
				BYTE* q = p;
				for(int i=0; i<reqBufVecCount; ++i)
				{
					const SockWriteBuf& swb = reqBufVec[i];
					memcpy(q, swb.data, swb.len);
					q += swb.len;
				}
				ASSERT((int)(q-p) == total);
				SockWriteBuf swb_udp;
				swb_udp.data = p;
				swb_udp.len = total;
				INT32 sessionID;
				m_rpcRequester->GetPeerSessionKey(sessionID);
				iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
				udpServer.SendSessionData(sessionID, &swb_udp, 1);
			}
			else if(0 != m_sessionR->m_postingProxy.callerKey_)
			{
				INT_PTR queueFullIndexes = -1;
				INT_PTR queueFullCount = 0;
				TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
				if(TCPS_OK != err)
					return err;
				ASSERT(0==queueFullCount || 1==queueFullCount);
				if(1 == queueFullCount)
					return TCPS_ERR_POSTING_PENDING_FULL;
			}
			else
			{
				TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
				if(TCPS_OK != err)
					return err;
			}
		}
	}
	else
	{
		ASSERT(false);
		return TCPS_ERR_INTERNAL_BUG;
	}

	return TCPS_OK;
}

TCPSError PCC_User_S::OnExecuted(
				IN INT64 jobKey_wrap,
				IN TCPSError errorCode_wrap,
				IN const void* context_wrap, IN INT32 context_wrap_len
				) posting_callback
{
	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnOnExecuted;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("OnExecuted", 10, s_PCC_User_OnExecuted_TypeInfo_, s_PCC_User_OnExecuted_TypeInfo_len_);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_User_LocalCallback::FN_OnExecuted)callbackFuncL)(
					m_sessionL,
					jobKey_wrap,
					errorCode_wrap,
					tcps_Binary(xat_bind, (BYTE*)context_wrap, context_wrap_len)
					);
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_OnExecuted)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 20;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::OnExecuted", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT64 jobKey
	Put_BaseType_(&m_dataOutfiter, jobKey_wrap);

	// IN TCPSError errorCode
	Put_BaseType_(&m_dataOutfiter, errorCode_wrap);

	// IN tcps_Binary context
	if(context_wrap_len<0 || (context_wrap_len>0 && NULL==context_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	Put_Binary_(&m_dataOutfiter, context_wrap, context_wrap_len);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_sessionR->m_udpSite.IsLinked())
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID = m_sessionR->GetSessionKey();
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_sessionR->m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_S::OnExecuted_Batch(
				IN const PPCC_User_S_* wrap_sessions,
				IN INT_PTR wrap_sessionsCount,
				IN INT64 jobKey_wrap,
				IN TCPSError errorCode_wrap,
				IN const void* context_wrap, IN INT32 context_wrap_len,
				OUT PPCC_User_S_* wrap_sendFaileds /*= NULL*/,
				OUT INT_PTR* wrap_failedCount /*= NULL*/
				) posting_callback
{
	if(wrap_failedCount)
		*wrap_failedCount= 0;

	if(NULL==wrap_sessions || wrap_sessionsCount<=0)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if((!!wrap_sendFaileds) != (!!wrap_failedCount))
	{
		ASSERT(false); // wrap_sendFaileds、wrap_failedCount要么都为NULL，要么都不为NULL
		return TCPS_ERR_INVALID_PARAM;
	}

	INT_PTR notReadies = 0;
	tcps_SmartArray<PPCC_User_S_, 256> iscm_sessions_ar_;
	for(INT_PTR i=0; i<wrap_sessionsCount; ++i)
	{
		if(NULL == wrap_sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(wrap_sessions[i]->m_sessionL)
		{
			wrap_sessions[i]->OnExecuted(
					jobKey_wrap,
					errorCode_wrap,
					context_wrap, context_wrap_len
					);
			continue;
		}
		if(TCPS_OK != wrap_sessions[i]->UpdateCallbackMatchingFlag_())
			continue;
		if(!wrap_sessions[i]->m_callbackMatchingFlag.matching_OnExecuted)
		{
			IPP peerIPP = wrap_sessions[i]->m_sessionR->m_peerIPP;
			NPLogWarning(("The 'PCC_User::OnExecuted()' of '%s' is not matched!", IPP_TO_STR_A(peerIPP)));
			continue;
		}
		if(0 == wrap_sessions[i]->m_sessionR->m_postingProxy.callerKey_)
		{
			if(wrap_sendFaileds)
			{
				wrap_sendFaileds[notReadies] = wrap_sessions[i];
				++notReadies;
			}
			continue;
		}
		iscm_sessions_ar_.push_back(wrap_sessions[i]);
	}
	if(0 == iscm_sessions_ar_.size())
		return TCPS_OK;

	// 准备调用数据
	tcps_SmartArray<SockWriteBuf, 256> iscm_swb_ar_;
	SockWriteBuf iscm_swb_;

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	iscm_swb_.data = &peerCallFlags;
	iscm_swb_.len = sizeof(peerCallFlags);
	iscm_swb_ar_.push_back(iscm_swb_);

	INT32 call_id_len = 20;
	iscm_swb_.data = &call_id_len;
	iscm_swb_.len = sizeof(call_id_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	iscm_swb_.data = "PCC_User::OnExecuted";
	iscm_swb_.len = call_id_len+1;
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN INT64 jobKey
	iscm_swb_.data = &jobKey_wrap;
	iscm_swb_.len = sizeof(jobKey_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN TCPSError errorCode
	iscm_swb_.data = &errorCode_wrap;
	iscm_swb_.len = sizeof(errorCode_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN tcps_Binary context
	if(context_wrap_len<0 || (context_wrap_len>0 && NULL==context_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	iscm_swb_.data = &context_wrap_len;
	iscm_swb_.len = sizeof(context_wrap_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	if(context_wrap_len > 0)
	{
		iscm_swb_.data = context_wrap;
		iscm_swb_.len = context_wrap_len;
		iscm_swb_ar_.push_back(iscm_swb_);
	}

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> iscm_callerKey_ar_;
	iscm_callerKey_ar_.resize(iscm_sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)iscm_sessions_ar_.size(); ++i)
		iscm_callerKey_ar_[i] = iscm_sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	if(NULL == wrap_sendFaileds)
	{
		return callerMan.BatchPosting(
							iscm_callerKey_ar_.Get(),
							iscm_callerKey_ar_.size(),
							iscm_swb_ar_.Get(),
							iscm_swb_ar_.size(),
							NULL,
							NULL
							);
	}

	ASSERT(wrap_failedCount);
	tcps_SmartArray<INT_PTR, 256> iscm_queueFullIndexesAr;
	iscm_queueFullIndexesAr.resize(iscm_callerKey_ar_.size());
	TCPSError err = callerMan.BatchPosting(
						iscm_callerKey_ar_.Get(),
						iscm_callerKey_ar_.size(),
						iscm_swb_ar_.Get(),
						iscm_swb_ar_.size(),
						iscm_queueFullIndexesAr.Get(),
						wrap_failedCount
						);
	ASSERT(0<=*wrap_failedCount && *wrap_failedCount<=(INT_PTR)iscm_queueFullIndexesAr.size());
	for(INT_PTR i=0; i<*wrap_failedCount; ++i)
		(wrap_sendFaileds+notReadies)[i] = iscm_sessions_ar_[iscm_queueFullIndexesAr[i]];
	*wrap_failedCount += notReadies;
	return err;
}

TCPSError PCC_User_S::OnExecuted1(
				IN INT64 jobKey_wrap,
				IN TCPSError errorCode_wrap,
				IN const void* context_wrap, IN INT32 context_wrap_len,
				IN const tcps_Array<tcps_Binary>& outArgs_wrap
				) posting_callback
{
	if(m_sessionL)
	{
		if(NULL == m_callSiteL.func_)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == m_callSiteL.func_)
				m_callSiteL.func_ = tcps_New(CallSiteL_::TFunc);
		}
		PROC& callbackFuncL = m_callSiteL.func_->fnOnExecuted1;
		if(NULL == callbackFuncL)
		{
			InitializeAllCallsTypeInfo_();
			callbackFuncL = m_sessionL->FindCallback_("OnExecuted1", 11, s_PCC_User_OnExecuted1_TypeInfo_, s_PCC_User_OnExecuted1_TypeInfo_len_);
			if(NULL == callbackFuncL)
				return TCPS_ERR_CALLBACK_NOT_MATCH;
		}
		return ((IPCC_User_LocalCallback::FN_OnExecuted1)callbackFuncL)(
					m_sessionL,
					jobKey_wrap,
					errorCode_wrap,
					tcps_Binary(xat_bind, (BYTE*)context_wrap, context_wrap_len),
					outArgs_wrap
					);
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_OnExecuted1)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 21;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::OnExecuted1", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT64 jobKey
	Put_BaseType_(&m_dataOutfiter, jobKey_wrap);

	// IN TCPSError errorCode
	Put_BaseType_(&m_dataOutfiter, errorCode_wrap);

	// IN tcps_Binary context
	if(context_wrap_len<0 || (context_wrap_len>0 && NULL==context_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	Put_Binary_(&m_dataOutfiter, context_wrap, context_wrap_len);

	// IN tcps_Array<tcps_Binary> outArgs
	Put_BaseType_(&m_dataOutfiter, outArgs_wrap.LenRef());
	for(int idx1=0; idx1<outArgs_wrap.Length(); ++idx1)
	{
		const tcps_Binary& ref1 = outArgs_wrap[idx1];
		Put_Binary_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_sessionR->m_udpSite.IsLinked())
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID = m_sessionR->GetSessionKey();
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_sessionR->m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_S::OnExecuted1_Batch(
				IN const PPCC_User_S_* wrap_sessions,
				IN INT_PTR wrap_sessionsCount,
				IN INT64 jobKey_wrap,
				IN TCPSError errorCode_wrap,
				IN const void* context_wrap, IN INT32 context_wrap_len,
				IN const tcps_Array<tcps_Binary>& outArgs_wrap,
				OUT PPCC_User_S_* wrap_sendFaileds /*= NULL*/,
				OUT INT_PTR* wrap_failedCount /*= NULL*/
				) posting_callback
{
	if(wrap_failedCount)
		*wrap_failedCount= 0;

	if(NULL==wrap_sessions || wrap_sessionsCount<=0)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if((!!wrap_sendFaileds) != (!!wrap_failedCount))
	{
		ASSERT(false); // wrap_sendFaileds、wrap_failedCount要么都为NULL，要么都不为NULL
		return TCPS_ERR_INVALID_PARAM;
	}

	INT_PTR notReadies = 0;
	tcps_SmartArray<PPCC_User_S_, 256> iscm_sessions_ar_;
	for(INT_PTR i=0; i<wrap_sessionsCount; ++i)
	{
		if(NULL == wrap_sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(wrap_sessions[i]->m_sessionL)
		{
			wrap_sessions[i]->OnExecuted1(
					jobKey_wrap,
					errorCode_wrap,
					context_wrap, context_wrap_len,
					outArgs_wrap
					);
			continue;
		}
		if(TCPS_OK != wrap_sessions[i]->UpdateCallbackMatchingFlag_())
			continue;
		if(!wrap_sessions[i]->m_callbackMatchingFlag.matching_OnExecuted1)
		{
			IPP peerIPP = wrap_sessions[i]->m_sessionR->m_peerIPP;
			NPLogWarning(("The 'PCC_User::OnExecuted1()' of '%s' is not matched!", IPP_TO_STR_A(peerIPP)));
			continue;
		}
		if(0 == wrap_sessions[i]->m_sessionR->m_postingProxy.callerKey_)
		{
			if(wrap_sendFaileds)
			{
				wrap_sendFaileds[notReadies] = wrap_sessions[i];
				++notReadies;
			}
			continue;
		}
		iscm_sessions_ar_.push_back(wrap_sessions[i]);
	}
	if(0 == iscm_sessions_ar_.size())
		return TCPS_OK;

	// 准备调用数据
	tcps_SmartArray<SockWriteBuf, 256> iscm_swb_ar_;
	SockWriteBuf iscm_swb_;

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	iscm_swb_.data = &peerCallFlags;
	iscm_swb_.len = sizeof(peerCallFlags);
	iscm_swb_ar_.push_back(iscm_swb_);

	INT32 call_id_len = 21;
	iscm_swb_.data = &call_id_len;
	iscm_swb_.len = sizeof(call_id_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	iscm_swb_.data = "PCC_User::OnExecuted1";
	iscm_swb_.len = call_id_len+1;
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN INT64 jobKey
	iscm_swb_.data = &jobKey_wrap;
	iscm_swb_.len = sizeof(jobKey_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN TCPSError errorCode
	iscm_swb_.data = &errorCode_wrap;
	iscm_swb_.len = sizeof(errorCode_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN tcps_Binary context
	if(context_wrap_len<0 || (context_wrap_len>0 && NULL==context_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	iscm_swb_.data = &context_wrap_len;
	iscm_swb_.len = sizeof(context_wrap_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	if(context_wrap_len > 0)
	{
		iscm_swb_.data = context_wrap;
		iscm_swb_.len = context_wrap_len;
		iscm_swb_ar_.push_back(iscm_swb_);
	}

	// IN tcps_Array<tcps_Binary> outArgs
	iscm_swb_.data = &outArgs_wrap.LenRef();
	iscm_swb_.len = sizeof(outArgs_wrap.LenRef());
	iscm_swb_ar_.push_back(iscm_swb_);
	for(int idx1=0; idx1<outArgs_wrap.Length(); ++idx1)
	{
		const tcps_Binary& ref1 = outArgs_wrap[idx1];
		iscm_swb_.data = &ref1.LenRef();
		iscm_swb_.len = sizeof(ref1.LenRef());
		iscm_swb_ar_.push_back(iscm_swb_);
		if(ref1.Length() > 0)
		{
			iscm_swb_.data = ref1.Get();
			iscm_swb_.len = ref1.Length();
			iscm_swb_ar_.push_back(iscm_swb_);
		}
	}

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> iscm_callerKey_ar_;
	iscm_callerKey_ar_.resize(iscm_sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)iscm_sessions_ar_.size(); ++i)
		iscm_callerKey_ar_[i] = iscm_sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	if(NULL == wrap_sendFaileds)
	{
		return callerMan.BatchPosting(
							iscm_callerKey_ar_.Get(),
							iscm_callerKey_ar_.size(),
							iscm_swb_ar_.Get(),
							iscm_swb_ar_.size(),
							NULL,
							NULL
							);
	}

	ASSERT(wrap_failedCount);
	tcps_SmartArray<INT_PTR, 256> iscm_queueFullIndexesAr;
	iscm_queueFullIndexesAr.resize(iscm_callerKey_ar_.size());
	TCPSError err = callerMan.BatchPosting(
						iscm_callerKey_ar_.Get(),
						iscm_callerKey_ar_.size(),
						iscm_swb_ar_.Get(),
						iscm_swb_ar_.size(),
						iscm_queueFullIndexesAr.Get(),
						wrap_failedCount
						);
	ASSERT(0<=*wrap_failedCount && *wrap_failedCount<=(INT_PTR)iscm_queueFullIndexesAr.size());
	for(INT_PTR i=0; i<*wrap_failedCount; ++i)
		(wrap_sendFaileds+notReadies)[i] = iscm_sessions_ar_[iscm_queueFullIndexesAr[i]];
	*wrap_failedCount += notReadies;
	return err;
}

TCPSError PCC_User_S::SetRedirect_(
				IN const IPP& redirectIPP_wrap,
				IN const void* redirectParam_wrap, IN INT32 redirectParam_wrap_len
				) posting_callback
{
	if(m_sessionL)
	{
		// ASSERT(false); // ??
		return TCPS_ERR_REFUSED;
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateCallbackMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_callbackMatchingFlag.matching_SetRedirect_)
		return TCPS_ERR_CALLBACK_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 22;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::SetRedirect_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN IPP redirectIPP
	Put_BaseType_(&m_dataOutfiter, redirectIPP_wrap);

	// IN tcps_Binary redirectParam
	if(redirectParam_wrap_len<0 || (redirectParam_wrap_len>0 && NULL==redirectParam_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	Put_Binary_(&m_dataOutfiter, redirectParam_wrap, redirectParam_wrap_len);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_sessionR->m_udpSite.IsLinked())
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID = m_sessionR->GetSessionKey();
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_sessionR->m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_sessionR->m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_S::SetRedirect__Batch(
				IN const PPCC_User_S_* wrap_sessions,
				IN INT_PTR wrap_sessionsCount,
				IN const IPP& redirectIPP_wrap,
				IN const void* redirectParam_wrap, IN INT32 redirectParam_wrap_len,
				OUT PPCC_User_S_* wrap_sendFaileds /*= NULL*/,
				OUT INT_PTR* wrap_failedCount /*= NULL*/
				) posting_callback
{
	if(wrap_failedCount)
		*wrap_failedCount= 0;

	if(NULL==wrap_sessions || wrap_sessionsCount<=0)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if((!!wrap_sendFaileds) != (!!wrap_failedCount))
	{
		ASSERT(false); // wrap_sendFaileds、wrap_failedCount要么都为NULL，要么都不为NULL
		return TCPS_ERR_INVALID_PARAM;
	}

	INT_PTR notReadies = 0;
	tcps_SmartArray<PPCC_User_S_, 256> iscm_sessions_ar_;
	for(INT_PTR i=0; i<wrap_sessionsCount; ++i)
	{
		if(NULL == wrap_sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(wrap_sessions[i]->m_sessionL)
			continue;
		if(TCPS_OK != wrap_sessions[i]->UpdateCallbackMatchingFlag_())
			continue;
		if(!wrap_sessions[i]->m_callbackMatchingFlag.matching_SetRedirect_)
		{
			IPP peerIPP = wrap_sessions[i]->m_sessionR->m_peerIPP;
			NPLogWarning(("The 'PCC_User::SetRedirect_()' of '%s' is not matched!", IPP_TO_STR_A(peerIPP)));
			continue;
		}
		if(0 == wrap_sessions[i]->m_sessionR->m_postingProxy.callerKey_)
		{
			if(wrap_sendFaileds)
			{
				wrap_sendFaileds[notReadies] = wrap_sessions[i];
				++notReadies;
			}
			continue;
		}
		iscm_sessions_ar_.push_back(wrap_sessions[i]);
	}
	if(0 == iscm_sessions_ar_.size())
		return TCPS_OK;

	// 准备调用数据
	tcps_SmartArray<SockWriteBuf, 256> iscm_swb_ar_;
	SockWriteBuf iscm_swb_;

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	iscm_swb_.data = &peerCallFlags;
	iscm_swb_.len = sizeof(peerCallFlags);
	iscm_swb_ar_.push_back(iscm_swb_);

	INT32 call_id_len = 22;
	iscm_swb_.data = &call_id_len;
	iscm_swb_.len = sizeof(call_id_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	iscm_swb_.data = "PCC_User::SetRedirect_";
	iscm_swb_.len = call_id_len+1;
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN IPP redirectIPP
	iscm_swb_.data = &redirectIPP_wrap;
	iscm_swb_.len = sizeof(redirectIPP_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN tcps_Binary redirectParam
	if(redirectParam_wrap_len<0 || (redirectParam_wrap_len>0 && NULL==redirectParam_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	iscm_swb_.data = &redirectParam_wrap_len;
	iscm_swb_.len = sizeof(redirectParam_wrap_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	if(redirectParam_wrap_len > 0)
	{
		iscm_swb_.data = redirectParam_wrap;
		iscm_swb_.len = redirectParam_wrap_len;
		iscm_swb_ar_.push_back(iscm_swb_);
	}

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> iscm_callerKey_ar_;
	iscm_callerKey_ar_.resize(iscm_sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)iscm_sessions_ar_.size(); ++i)
		iscm_callerKey_ar_[i] = iscm_sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	if(NULL == wrap_sendFaileds)
	{
		return callerMan.BatchPosting(
							iscm_callerKey_ar_.Get(),
							iscm_callerKey_ar_.size(),
							iscm_swb_ar_.Get(),
							iscm_swb_ar_.size(),
							NULL,
							NULL
							);
	}

	ASSERT(wrap_failedCount);
	tcps_SmartArray<INT_PTR, 256> iscm_queueFullIndexesAr;
	iscm_queueFullIndexesAr.resize(iscm_callerKey_ar_.size());
	TCPSError err = callerMan.BatchPosting(
						iscm_callerKey_ar_.Get(),
						iscm_callerKey_ar_.size(),
						iscm_swb_ar_.Get(),
						iscm_swb_ar_.size(),
						iscm_queueFullIndexesAr.Get(),
						wrap_failedCount
						);
	ASSERT(0<=*wrap_failedCount && *wrap_failedCount<=(INT_PTR)iscm_queueFullIndexesAr.size());
	for(INT_PTR i=0; i<*wrap_failedCount; ++i)
		(wrap_sendFaileds+notReadies)[i] = iscm_sessions_ar_[iscm_queueFullIndexesAr[i]];
	*wrap_failedCount += notReadies;
	return err;
}

TCPSError PCC_User_S::CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks_wrap,
				IN const tcps_Array<tcps_String>& callbackTypeInfos_wrap,
				OUT tcps_Array<BOOL>& matchingFlags_wrap
				) callback
{
	if(m_sessionL)
	{
		InitializeAllCallsTypeInfo_();
		ASSERT(callbacks_wrap.Length() == callbackTypeInfos_wrap.Length());
		matchingFlags_wrap.Resize(callbacks_wrap.Length());
		for(int i=0; i<callbacks_wrap.Length(); ++i)
		{
			const tcps_String& name = callbacks_wrap[i];
			const tcps_String& typeInfo = callbackTypeInfos_wrap[i];
			matchingFlags_wrap[i] = (NULL != m_sessionL->FindCallback_(name.Get(), name.Length(), typeInfo.Get(), typeInfo.Length()));
		}
		return TCPS_OK;
	}

	// 准备回调相关变量
	iscm_IRequester* const m_rpcRequester = m_sessionR->m_callbackRequester.face_;
	if(NULL==m_rpcRequester || !m_rpcRequester->IsConnected())
		return TCPS_ERR_CALLBACK_NOT_READY;
	DataOutfiter& m_dataOutfiter = m_sessionR->m_callbackOutfiter;

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 24;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::CallbackCheck_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_Array<tcps_String> callbacks
	Put_BaseType_(&m_dataOutfiter, callbacks_wrap.LenRef());
	for(int idx1=0; idx1<callbacks_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = callbacks_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// IN tcps_Array<tcps_String> callbackTypeInfos
	Put_BaseType_(&m_dataOutfiter, callbackTypeInfos_wrap.LenRef());
	for(int idx1=0; idx1<callbackTypeInfos_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = callbackTypeInfos_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_IRequester* iscm_replied_picker = m_rpcRequester;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<BOOL> matchingFlags
		PICK_PODARRAY_(iscm_replied_picker, matchingFlags_wrap);
	}
	return TCPS_OK;
}

TCPSError PCC_User_S::UDPLink_(
			OUT INT32& servePort,
			OUT INT32& linkKey
			) method
{
	ASSERT(!m_sessionR->m_udpSite.IsOn());
	AutoSock udpSock;
	udpSock.sock_ = UDPNew();
	if(!SockValid(udpSock.sock_))
		return TCPS_ERR_SYSTEM_RESOURCE;

	INT32 port = 0;
	TCPSError err = tcps_AutoBindUDPPort(udpSock.sock_, m_sessionR->m_serveIPP.ip_, &port);
	if(TCPS_OK != err)
		return err;
	m_sessionR->m_udpSite.localPort_ = port;
	m_sessionR->m_udpSite.sock_ = udpSock.Drop();
	servePort = port;
	linkKey = m_sessionR->GetSessionKey();
	return TCPS_OK;
}

TCPSError PCC_User_S::UDPLinkConfirm_(
			) method
{
	if(!m_sessionR->m_udpSite.IsLinking())
	{
		ASSERT(false);
		return TCPS_ERR_CALL_WAS_IGNORED;
	}
	ASSERT(SockValid(m_sessionR->m_udpSite.sock_));

	DWORD recvTimeout = INFINITE;
	this->GetTimeout(NULL, &recvTimeout, NULL);
	if(INFINITE == recvTimeout)
		recvTimeout = iscm_GetDefaultRecvTimeout();
	recvTimeout = min(recvTimeout, (DWORD)2000);
	int r = SockCheckRead(m_sessionR->m_udpSite.sock_, recvTimeout);
	if(1 != r)
		return TCPS_ERR_RECV;
	IPP peerIPP;
	CSmartBuf<BYTE, 1024> smBuf(ISCM_MAX_UDP_FRAG_BYTES);
	BYTE* buf = smBuf.Get();
	r = SockReceiveFrom(m_sessionR->m_udpSite.sock_, &peerIPP.ip_, &peerIPP.port_, buf, ISCM_MAX_UDP_FRAG_BYTES);
	if((int)sizeof(iscm_UDPFrag) != r)
		return TCPS_ERR_RECV;
	if(!peerIPP.IsValid() || peerIPP.ip_!=m_sessionR->m_peerIPP.ip_)
		return TCPS_ERR_MALFORMED_REQ;

	const iscm_UDPFrag& frag = *(const iscm_UDPFrag*)buf;
	if(ISCM_UDP_FRAG_LINK != frag.fragType)
		return TCPS_ERR_MALFORMED_REQ;
	INT32 linkKey = m_sessionR->GetSessionKey();
	if(linkKey != frag.sendKey)
		return TCPS_ERR_INVALID_UDP_LINK_KEY;

	if(0 != UDPConnect(m_sessionR->m_udpSite.sock_, peerIPP.ip_, peerIPP.port_))
		return TCPS_ERR_SYSTEM;

	iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
	udpServer.AddSession(linkKey, m_sessionR->m_udpSite.sock_, m_sessionR);
	m_sessionR->m_udpSite.sock_ = INVALID_SOCKET;

	return TCPS_OK;
}

TCPSError PCC_User_S::SetTimeout_(
			IN INT32 recvTimeout,
			IN INT32 sendTimeout
			) posting_method
{
	this->SetTimeout(INFINITE, recvTimeout, sendTimeout);
	return TCPS_OK;
}

TCPSError PCC_User_S::SetSessionBufferSize_(
			IN INT32 recvBufBytes,
			IN INT32 sendBufBytes
			) posting_method
{
	this->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	return TCPS_OK;
}

TCPSError PCC_User_S::MethodCheck_(
			IN const tcps_Array<tcps_String>& methods,
			IN const tcps_Array<tcps_String>& methodTypeInfos,
			OUT tcps_Array<BOOL>& matchingFlags
			) method
{
	if(0==methods.Length() || methods.Length()!=methodTypeInfos.Length())
		return TCPS_ERR_INVALID_PARAM;

	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<11> > MethodMap_;
	static MethodMap_* s_mdMap = NULL;
	if(NULL == s_mdMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_mdMap)
		{
			static MethodMap_ s_mdMapObj;
			MethodMap_& mdMap = s_mdMapObj;
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetPccProperty"), CPtrStrA(s_PCC_User_GetPccProperty_TypeInfo_, s_PCC_User_GetPccProperty_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListNodes"), CPtrStrA(s_PCC_User_ListNodes_TypeInfo_, s_PCC_User_ListNodes_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetNodeDynamicContext"), CPtrStrA(s_PCC_User_GetNodeDynamicContext_TypeInfo_, s_PCC_User_GetNodeDynamicContext_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListModules"), CPtrStrA(s_PCC_User_ListModules_TypeInfo_, s_PCC_User_ListModules_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Execute"), CPtrStrA(s_PCC_User_Execute_TypeInfo_, s_PCC_User_Execute_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("QueryJobs"), CPtrStrA(s_PCC_User_QueryJobs_TypeInfo_, s_PCC_User_QueryJobs_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("CancelJob"), CPtrStrA(s_PCC_User_CancelJob_TypeInfo_, s_PCC_User_CancelJob_TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("UDPLink_"), CPtrStrA(s_PCC_User_UDPLink__TypeInfo_, s_PCC_User_UDPLink__TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("UDPLinkConfirm_"), CPtrStrA(s_PCC_User_UDPLinkConfirm__TypeInfo_, s_PCC_User_UDPLinkConfirm__TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetTimeout_"), CPtrStrA(s_PCC_User_SetTimeout__TypeInfo_, s_PCC_User_SetTimeout__TypeInfo_len_))).second);
			VERIFY(mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetSessionBufferSize_"), CPtrStrA(s_PCC_User_SetSessionBufferSize__TypeInfo_, s_PCC_User_SetSessionBufferSize__TypeInfo_len_))).second);
			s_mdMap = &mdMap;
		}
	}

	matchingFlags.Resize(methods.Length());
	for(int index=0; index<methods.Length(); ++index)
	{
		BOOL& flag = matchingFlags[index];
		const tcps_String& name = methods[index];
		const tcps_String& typeInfos = methodTypeInfos[index];
		MethodMap_::const_iterator cit = s_mdMap->find(name.Get(), name.Length());
		if(cit!=s_mdMap->end() && 0==typeInfos.Compare(cit->second.p, cit->second.len))
			flag = true;
		else
			flag = false;
	}
	return TCPS_OK;
}

void PCC_User_S::CloseSession(
				IN TCPSError cause /*= TCPS_OK*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		m_sessionR->CloseSession_(cause);
	else if(m_sessionL)
	{
		AutoFlag<OSThreadID> autoClosingTID(m_closingTID_L.tid, OSThreadSelf());
		m_sessionL->CloseSession_();
	}
}

IPP PCC_User_S::GetPeerIPP(
				OUT IPP* peerID /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
	{
		if(peerID)
			*peerID = m_sessionR->m_peerID_IPP;
		return m_sessionR->m_peerIPP;
	}

	if(m_sessionL)
	{
		if(peerID)
			*peerID = IPP((DWORD)0, (int)0);
		return IPP((DWORD)0, (int)0);
	}

	if(peerID)
		*peerID = INVALID_IPP;
	return INVALID_IPP;
}

BOOL PCC_User_S::IsLocalPeer() const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	return (NULL != m_sessionL);
}

void PCC_User_S::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		m_sessionR->m_postingPendingParam.Set(maxPendingBytes, maxPendings);
}

void PCC_User_S::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(maxPendingBytes)
			*maxPendingBytes = 0;
		if(maxPendings)
			*maxPendings = 0;
		return;
	}
	m_sessionR->m_postingPendingParam.Get(maxPendingBytes, maxPendings);
}

BOOL PCC_User_S::CallbackIsReady() const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR)
		return (m_sessionR->m_callbackRequester.face_ && m_sessionR->m_callbackRequester.face_->IsConnected());
	return true;
}

TCPSError PCC_User_S::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
		return TCPS_OK;
	if(NULL == m_sessionR->m_callbackRequester.face_)
		return TCPS_ERR_CALLBACK_NOT_READY;
	m_sessionR->m_callbackRequester.face_->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	return TCPS_OK;
}

TCPSError PCC_User_S::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(connectTimeout)
			*connectTimeout = INFINITE;
		if(recvTimeout)
			*recvTimeout = INFINITE;
		if(sendTimeout)
			*sendTimeout = INFINITE;
		return TCPS_OK;
	}

	if(NULL == m_sessionR->m_callbackRequester.face_)
		return TCPS_ERR_CALLBACK_NOT_READY;
	m_sessionR->m_callbackRequester.face_->GetTimeout(connectTimeout, recvTimeout, sendTimeout);
	return TCPS_OK;
}

void PCC_User_S::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
		return;

	if(recvBufBytes>=0 || sendBufBytes>=0)
	{
		SOCKET sock = INVALID_SOCKET;
		m_sessionR->m_bindedSession->GetInfos(NULL, &sock, NULL, NULL, NULL);
		ASSERT(SockValid(sock));
		if(recvBufBytes >= 0)
			SockSetReceiveBufSize(sock, (0==recvBufBytes ? TCPS_DEFAULT_RECVBUF_SIZE : recvBufBytes));
		if(sendBufBytes >= 0)
			SockSetSendBufSize(sock, (0==sendBufBytes ? TCPS_DEFAULT_SENDBUF_SIZE : sendBufBytes));
	}
	if(m_sessionR->m_callbackRequester.face_)
		m_sessionR->m_callbackRequester.face_->SetSessionBufferSize(recvBufBytes, sendBufBytes);
}

void PCC_User_S::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(recvBufBytes)
			*recvBufBytes = 0;
		if(sendBufBytes)
			*sendBufBytes = 0;
		return;
	}

	if(NULL==recvBufBytes && NULL==sendBufBytes)
		return;
	if(m_sessionR->m_callbackRequester.face_)
	{
		m_sessionR->m_callbackRequester.face_->GetSessionBufferSize(recvBufBytes, sendBufBytes);
	}
	else
	{
		SOCKET sock = INVALID_SOCKET;
		m_sessionR->m_bindedSession->GetInfos(NULL, &sock, NULL, NULL, NULL);
		ASSERT(SockValid(sock));
		if(recvBufBytes)
			SockGetReceiveBufSize(sock, recvBufBytes);
		if(sendBufBytes)
			SockGetSendBufSize(sock, sendBufBytes);
	}
}

void PCC_User_S::SetPostingSendParameters(
				IN INT32 maxBufferingSize,
				IN INT32 maxSendings
				)
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionR && 0!=m_sessionR->m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().SetBufferingParam(m_sessionR->m_postingProxy.callerKey_, maxBufferingSize, maxSendings);
	m_postingSendParam.Set(maxBufferingSize, maxSendings);
}

void PCC_User_S::GetPostingSendParameters(
				OUT INT32* maxBufferingSize /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(m_sessionL)
	{
		if(maxBufferingSize)
			*maxBufferingSize = 0;
		if(maxSendings)
			*maxSendings = 0;
		return;
	}
	m_postingSendParam.Get(maxBufferingSize, maxSendings);
}

TCPSError PCC_User_S::CleanPostingSendingQueue()
{
	ASSERT((NULL==m_sessionR) != (NULL==m_sessionL));
	if(NULL==m_sessionR || 0==m_sessionR->m_postingProxy.callerKey_)
		return TCPS_ERR_CALL_WAS_IGNORED;
	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(&m_sessionR->m_postingProxy.callerKey_, 1);
}

TCPSError PCC_User_S::CleanPostingSendingQueue(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount
				)
{
	tcps_SmartArray<PPCC_User_S_, 256> sessions_ar_;
	for(INT_PTR i=0; i<sessionsCount; ++i)
	{
		if(NULL == sessions[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(NULL==sessions[i]->m_sessionR || 0==sessions[i]->m_sessionR->m_postingProxy.callerKey_)
			continue;
		sessions_ar_.push_back(sessions[i]);
	}
	if(0 == sessions_ar_.size())
		return TCPS_OK;

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> callerKey_ar_;
	callerKey_ar_.resize(sessions_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)sessions_ar_.size(); ++i)
		callerKey_ar_[i] = sessions_ar_[i]->m_sessionR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(callerKey_ar_.Get(), (int)callerKey_ar_.size());
}

class PCC_User_LS : public IPCC_User_LocalMethod
{
private:
	PCC_User_LS(const PCC_User_LS&);
	PCC_User_LS& operator= (const PCC_User_LS&);

private:
	PCC_CenterSessionMaker& m_sessionMaker;
	IPCC_User_LocalCallback* const m_callback;
	PCC_User_S* const m_method;
	TCPSError m_connectError;
	INT32 m_sessionKey;

public:
	TCPSError GetConnectError() const
		{	return m_connectError;	}

public:
	PCC_User_LS(const IPP& clientID_IPP, PCC_CenterSessionMaker& sessionMaker, IPCC_User_LocalCallback* callbackHandler)
		: m_sessionMaker(sessionMaker)
		, m_callback(callbackHandler)
		, m_method(tcps_NewEx(PCC_User_S, (m_sessionMaker, NULL, callbackHandler)))
		, m_connectError(TCPS_ERROR)
		, m_sessionKey(0)
	{
		INT32 sessionCount;
		m_sessionMaker.OnSessionConnect_(&m_sessionKey, sessionCount);
		m_connectError = m_method->OnConnected(m_sessionKey, clientID_IPP, sessionCount);
		if(TCPS_OK == m_connectError)
		{
			if(m_callback)
				m_method->OnCallbackReady();
			m_method->OnPostingCallReady();
			m_sessionMaker.RegisterLocalSession_(m_callback);
		}
	}
	virtual ~PCC_User_LS()
	{
		if(TCPS_OK == m_connectError)
			m_sessionMaker.UnregisterLocalSession_(m_callback);
		m_sessionMaker.Unregister(m_method);
		if(INVALID_OSTHREADID==m_method->m_closingTID_L.tid || m_method->m_closingTID_L.tid!=OSThreadSelf())
			m_method->OnPeerBroken(m_sessionKey, TCPS_ANY_IPP, m_connectError);
		m_method->OnClose(m_sessionKey, TCPS_ANY_IPP, m_connectError);
		m_sessionMaker.OnSessionClosed_();
		m_method->~PCC_User_S();
		tcps_Free(m_method);
	}
	virtual void DeleteThis()
		{	tcps_Delete(this);	}

	virtual PROC FindMethod_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				)
	{
		if(NULL == name)
		{
			ASSERT(false);
			return NULL;
		}

		// 对OnStreamedCall_L_()特殊处理
		if(nameLen<0 && 0==strcmp("OnStreamedCall_L_", name))
			return (PROC)&OnStreamedCall_L_;

		if(NULL == type)
		{
			ASSERT(false);
			return NULL;
		}

		InitializeAllCallsTypeInfo_();
		typedef TwoItems<CPtrStrA, PROC> FuncPair;
		typedef CQuickStringMap<CPtrStrA, FuncPair, QSS_Traits<7> > MethodMap_;
		static MethodMap_* s_mdMap = NULL;
		if(NULL == s_mdMap)
		{
			IscmRPCGlobalLocker locker;
			if(NULL == s_mdMap)
			{
				static MethodMap_ s_mdMapObj;
				MethodMap_& mdMap = s_mdMapObj;
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetPccProperty"), FuncPair(CPtrStrA(s_PCC_User_GetPccProperty_TypeInfo_, s_PCC_User_GetPccProperty_TypeInfo_len_), (PROC)&GetPccProperty)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListNodes"), FuncPair(CPtrStrA(s_PCC_User_ListNodes_TypeInfo_, s_PCC_User_ListNodes_TypeInfo_len_), (PROC)&ListNodes)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetNodeDynamicContext"), FuncPair(CPtrStrA(s_PCC_User_GetNodeDynamicContext_TypeInfo_, s_PCC_User_GetNodeDynamicContext_TypeInfo_len_), (PROC)&GetNodeDynamicContext)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListModules"), FuncPair(CPtrStrA(s_PCC_User_ListModules_TypeInfo_, s_PCC_User_ListModules_TypeInfo_len_), (PROC)&ListModules)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Execute"), FuncPair(CPtrStrA(s_PCC_User_Execute_TypeInfo_, s_PCC_User_Execute_TypeInfo_len_), (PROC)&Execute)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("QueryJobs"), FuncPair(CPtrStrA(s_PCC_User_QueryJobs_TypeInfo_, s_PCC_User_QueryJobs_TypeInfo_len_), (PROC)&QueryJobs)));
				mdMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("CancelJob"), FuncPair(CPtrStrA(s_PCC_User_CancelJob_TypeInfo_, s_PCC_User_CancelJob_TypeInfo_len_), (PROC)&CancelJob)));
				s_mdMap = &mdMap;
			}
		}

		MethodMap_::iterator it = s_mdMap->find(name, nameLen);
		if(s_mdMap->end() == it)
			return NULL;
		const CPtrStrA& ps = it->second.first;
		if(0 != ps.Compare(type, typeLen))
			return NULL;
		return it->second.second;
	}

private:
	static TCPSError OnStreamedCall_L_(
				IN void* sessionObj,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
	{	return ((PCC_User_LS*)sessionObj)->m_method->OnStreamedCall_L_(
					methodName,
					nameLen,
					data,
					dataLen,
					replyData,
					replyLen
					);
	}

private:
	static TCPSError GetPccProperty(
				IN void* sessionObj_wrap,
				OUT PCCProperty& pccProp
				) method
	{	return ((PCC_User_LS*)sessionObj_wrap)->m_method->GetPccProperty(
					pccProp
					);
	}

	static TCPSError ListNodes(
				IN void* sessionObj_wrap,
				OUT tcps_Array<PCC_NodeDesc>& nodes
				) method
	{	return ((PCC_User_LS*)sessionObj_wrap)->m_method->ListNodes(
					nodes
					);
	}

	static TCPSError GetNodeDynamicContext(
				IN void* sessionObj_wrap,
				IN const tcps_String& nodeName,
				OUT PCC_DynamicContext& dynamicContext
				) method
	{	return ((PCC_User_LS*)sessionObj_wrap)->m_method->GetNodeDynamicContext(
					nodeName,
					dynamicContext
					);
	}

	static TCPSError ListModules(
				IN void* sessionObj_wrap,
				IN const tcps_String& regex,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method
	{	return ((PCC_User_LS*)sessionObj_wrap)->m_method->ListModules(
					regex,
					modulesInfo
					);
	}

	static TCPSError Execute(
				IN void* sessionObj_wrap,
				IN INT64 moduleKey,
				IN const tcps_String& inputUrl,
				IN const tcps_String& outputUrl,
				IN const tcps_Binary& moduleParams,
				OUT INT64& jobKey
				) method
	{	return ((PCC_User_LS*)sessionObj_wrap)->m_method->Execute(
					moduleKey,
					inputUrl,
					outputUrl,
					moduleParams,
					jobKey
					);
	}

	static TCPSError QueryJobs(
				IN void* sessionObj_wrap,
				IN const tcps_Array<INT64>& jobsKey,
				OUT tcps_Array<ExecuteState>& jobsState
				) method
	{	return ((PCC_User_LS*)sessionObj_wrap)->m_method->QueryJobs(
					jobsKey,
					jobsState
					);
	}

	static TCPSError CancelJob(
				IN void* sessionObj_wrap,
				IN INT64 jobKey
				) posting_method
	{	return ((PCC_User_LS*)sessionObj_wrap)->m_method->CancelJob(
					jobKey
					);
	}
};

TCPSError MakeLocalSession_PCC_User__(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_User_LocalMethod*& methodHandler,
			IN IPCC_User_LocalCallback* callbackHandler
			)
{
	PCC_User_LS* session = tcps_NewEx(PCC_User_LS, (clientID_IPP, sessionMaker, callbackHandler));
	if(NULL == session)
		return TCPS_ERR_OUT_OF_MEMORY;
	TCPSError err = session->GetConnectError();
	if(TCPS_OK != err)
	{
		tcps_Delete(session);
		return err;
	}
	methodHandler = session;
	return TCPS_OK;
}
