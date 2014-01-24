// PCC_CenterSession.h
//
// 注意: 此文件为工具生成，请小心修改

#ifndef _PCC_CenterSession_h_
#define _PCC_CenterSession_h_

#if defined(_MSC_VER) && (_MSC_VER > 1000)
	#pragma once
#endif

#include "ILocker.h"
#include "npmap.h"
#include "QuickStringMap.h"
#include "AutoInterface.h"
#include "rpc_serve.h"
#include "iscm_requester.h"
#include "iscm_posting_caller.h"
#include "iscm_udp_serve.h"
#include "iscm_helper.h"
#include "iscm_smart_container.h"
#include "PCC_CenterTypesDefine.h"
#include "trunkmanage.h"
#include "griduser/MY_NP_GridUserClient.h"//权宜之计
class PCC_CenterSession;

//[[begin_iscm]]

class PCC_Center;
class PCC_Center_LS;
class PCC_Center_S : public PCC_Center_T
{
	friend class PCC_Center;
	friend class PCC_CenterSession;
	friend class PCC_Center_LS;
private:
	PCC_Center_S(const PCC_Center_S&);
	PCC_Center_S& operator= (const PCC_Center_S&);

	typedef PCC_Center_S* PPCC_Center_S_;

public:
	// TODO: 可以在此处添加PCC_Center的自定义成员
   INT32 m_skey;
private:
	PCC_Center_S(PCC_CenterSessionMaker& sessionMaker, PCC_CenterSession* sessionR, IPCC_Center_LocalCallback* sessionL);
	~PCC_Center_S();
	TCPSError OnConnected(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN INT32 sessionCount
				);
	void OnCallbackReady();
	void OnPostingCallReady();
	void OnPeerBroken(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				);
	void OnClose(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				);

public:
	// 主动关闭会话
	void CloseSession(
				IN TCPSError cause = TCPS_OK
				);

	// 获取对端IPP
	// peerID用于返回对端的peerID_IPP
	IPP GetPeerIPP(
				OUT IPP* peerID = NULL
				) const;

	// 对端是否为进程内客户端
	BOOL IsLocalPeer() const;

	// 判断回调连接是否就绪
	BOOL CallbackIsReady() const;

	// 设置回调调用网络超时，INFINITE表示使用默认值，回调未就绪时返回失败
	TCPSError SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	TCPSError GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				);

	// 设置同步调用网络缓冲大小，<0表示不改变此项，==0表示恢复默认值
	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	// 设置posting执行端参数
	// @maxPendingBytes[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_PENDING_BUFFER_SIZE）
	// @maxPendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_PENDINGS）
	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

	// 设置posting调用端参数
	// @maxBufferingSize[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_SEND_BUFFER_SIZE）
	// @maxSendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_SENDINGS）
	void SetPostingSendParameters(
				IN INT32 maxBufferingSize /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxBufferingSize /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// 清理会话的posting回调发送队列
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_Center_S_* sessions,
				IN INT_PTR sessionsCount
				);

	// 回调匹配检查支持
public:
	struct CallbackMatchingFlag
	{
		struct Info
		{
			BOOL* pMatchingVar;
			BOOL isPosting;
			Info(BOOL* p, BOOL is) : pMatchingVar(p), isPosting(is) {}
		};
		typedef tcps_QuickStringMap<CPtrStrA, Info, 7> CallbackMap;
		CallbackMap cbmap_;
		BOOL matching_AddModelCenter;
		BOOL matching_DelModelCenter;
		BOOL matching_GetStaticContext;
		BOOL matching_GetDynamicContext;
		BOOL matching_AddModel;
		BOOL matching_DelModel;
		BOOL matching_SetRedirect_;
		void Reset();
		CallbackMatchingFlag();
	};
public:
	// 获取本地与对端回调匹配信息
	const CallbackMatchingFlag& GetCallbackMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// 下面流式调用定义仅用于非C++语言的辅助实现
private:
	TCPSError OnStreamedCall_L_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

public:
	TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

public:
	TCPSError AddModelCenter(
				IN const IPP& centerIPP
				) posting_callback;

public:
	static TCPSError AddModelCenter_Batch(
				IN const PPCC_Center_S_* sessions,
				IN INT_PTR sessionsCount,
				IN const IPP& centerIPP,
				OUT PPCC_Center_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback;

public:
	TCPSError DelModelCenter(
				IN const IPP& centerIPP
				) posting_callback;

public:
	static TCPSError DelModelCenter_Batch(
				IN const PPCC_Center_S_* sessions,
				IN INT_PTR sessionsCount,
				IN const IPP& centerIPP,
				OUT PPCC_Center_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback;

public:
	TCPSError GetStaticContext(
				OUT PCC_NodeDesc& staticContext
				) cacheable_callback;

public:
	TCPSError GetDynamicContext(
				OUT PCC_DynamicContext& dynamicContext
				) callback;

public:
	TCPSError AddModel(
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback;
	TCPSError AddModel(
				IN const PCC_ModelProperty& moduleProperty,
				IN const PCC_ModelFile* modelFiles, IN INT32 modelFiles_count
				) callback
		{	return this->AddModel(
							moduleProperty,
							tcps_Array<PCC_ModelFile>(xat_bind, (PCC_ModelFile*)modelFiles, modelFiles_count)
							);
		}

public:
	TCPSError DelModel(
				IN const PCC_Tag& tag
				) callback;

public:
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const void* redirectParam, IN INT32 redirectParam_len
				) posting_callback;
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
		{	return this->SetRedirect_(
							redirectIPP,
							redirectParam.Get(), redirectParam.Length()
							);
		}

public:
	static TCPSError SetRedirect__Batch(
				IN const PPCC_Center_S_* sessions,
				IN INT_PTR sessionsCount,
				IN const IPP& redirectIPP,
				IN const void* redirectParam, IN INT32 redirectParam_len,
				OUT PPCC_Center_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback;
	static inline TCPSError SetRedirect__Batch(
				IN const PPCC_Center_S_* sessions,
				IN INT_PTR sessionsCount,
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam,
				OUT PPCC_Center_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback
		{	return PCC_Center_S::SetRedirect__Batch(
							sessions, sessionsCount,
							redirectIPP,
							redirectParam.Get(), redirectParam.Length(),
							sendFaileds, failedCount
							);
		}

	/////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 /////
private:
	void OnNetworkMalformed_()
		{	this->CloseSession();	}

public:
	PCC_CenterSessionMaker& m_sessionMaker;
	PCC_CenterSession* const m_sessionR;
	IPCC_Center_LocalCallback* const m_sessionL;
	struct TIDFlag_
	{
		OSThreadID tid;
		TIDFlag_() : tid(INVALID_OSTHREADID) {}
	};
	TIDFlag_ m_closingTID_L;

private:
	iscm_PostingSendParam m_postingSendParam;

private:
	struct CallSiteL_
	{
		struct TFunc
		{
			PROC fnOnStreamedCallback_L_;
			PROC fnAddModelCenter;
			PROC fnDelModelCenter;
			PROC fnGetStaticContext;
			PROC fnGetDynamicContext;
			PROC fnAddModel;
			PROC fnDelModel;
			TFunc()
				: fnOnStreamedCallback_L_(NULL)
				, fnAddModelCenter(NULL)
				, fnDelModelCenter(NULL)
				, fnGetStaticContext(NULL)
				, fnGetDynamicContext(NULL)
				, fnAddModel(NULL)
				, fnDelModel(NULL)
				{}
		};
		TFunc* func_;
		CallSiteL_() : func_(NULL) {}
		~CallSiteL_() { if(func_) tcps_Delete(func_); }
	};
	CallSiteL_ m_callSiteL; // m_sessionL!=NULL时有效

private:
	iscm_MatchingUpdateFlag m_callbackMatchingUpdatedFlag;
	CallbackMatchingFlag m_callbackMatchingFlag;
	TCPSError UpdateCallbackMatchingFlag_();

private:
	struct TCache_GetStaticContext
	{
		BOOL needUpdate;
		TCPSError lastRet;
		PCC_NodeDesc staticContext_c_;
		TCache_GetStaticContext()
			: needUpdate(true), lastRet(TCPS_ERROR)
			{}
	};
	TCache_GetStaticContext m_cache_GetStaticContext;

private:
	TCPSError UDPLink_(
				OUT INT32& servePort,
				OUT INT32& linkKey
				) method;

private:
	TCPSError UDPLinkConfirm_(
				) method;

private:
	TCPSError SetTimeout_(
				IN INT32 recvTimeout,
				IN INT32 sendTimeout
				) posting_method;

private:
	TCPSError SetSessionBufferSize_(
				IN INT32 recvBufBytes,
				IN INT32 sendBufBytes
				) posting_method;

private:
	TCPSError MethodCheck_(
				IN const tcps_Array<tcps_String>& methods,
				IN const tcps_Array<tcps_String>& methodTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) method;

private:
	TCPSError CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback;
};

class PCC_Deploy;
class PCC_Deploy_LS;
class PCC_Deploy_S : public PCC_Deploy_T
{
	friend class PCC_Deploy;
	friend class PCC_CenterSession;
	friend class PCC_Deploy_LS;
private:
	PCC_Deploy_S(const PCC_Deploy_S&);
	PCC_Deploy_S& operator= (const PCC_Deploy_S&);

	typedef PCC_Deploy_S* PPCC_Deploy_S_;

public:
	// TODO: 可以在此处添加PCC_Deploy的自定义成员
	CNPDeploy m_deploy;
private:
	PCC_Deploy_S(PCC_CenterSessionMaker& sessionMaker, PCC_CenterSession* sessionR, IPCC_Deploy_LocalCallback* sessionL);
	~PCC_Deploy_S();
	TCPSError OnConnected(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN INT32 sessionCount
				);
	void OnCallbackReady();
	void OnPostingCallReady();
	void OnPeerBroken(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				);
	void OnClose(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				);

public:
	// 主动关闭会话
	void CloseSession(
				IN TCPSError cause = TCPS_OK
				);

	// 获取对端IPP
	// peerID用于返回对端的peerID_IPP
	IPP GetPeerIPP(
				OUT IPP* peerID = NULL
				) const;

	// 对端是否为进程内客户端
	BOOL IsLocalPeer() const;

	// 判断回调连接是否就绪
	BOOL CallbackIsReady() const;

	// 设置回调调用网络超时，INFINITE表示使用默认值，回调未就绪时返回失败
	TCPSError SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	TCPSError GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				);

	// 设置同步调用网络缓冲大小，<0表示不改变此项，==0表示恢复默认值
	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	// 设置posting执行端参数
	// @maxPendingBytes[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_PENDING_BUFFER_SIZE）
	// @maxPendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_PENDINGS）
	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

	// 设置posting调用端参数
	// @maxBufferingSize[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_SEND_BUFFER_SIZE）
	// @maxSendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_SENDINGS）
	void SetPostingSendParameters(
				IN INT32 maxBufferingSize /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxBufferingSize /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// 清理会话的posting回调发送队列
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_Deploy_S_* sessions,
				IN INT_PTR sessionsCount
				);

	// 回调匹配检查支持
public:
	struct CallbackMatchingFlag
	{
		struct Info
		{
			BOOL* pMatchingVar;
			BOOL isPosting;
			Info(BOOL* p, BOOL is) : pMatchingVar(p), isPosting(is) {}
		};
		typedef tcps_QuickStringMap<CPtrStrA, Info, 1> CallbackMap;
		CallbackMap cbmap_;
		BOOL matching_SetRedirect_;
		void Reset();
		CallbackMatchingFlag();
	};
public:
	// 获取本地与对端回调匹配信息
	const CallbackMatchingFlag& GetCallbackMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// 下面流式调用定义仅用于非C++语言的辅助实现
private:
	TCPSError OnStreamedCall_L_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

public:
	TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

private:
	TCPSError Login(
				IN const tcps_String& ticket
				) method;

private:
	TCPSError Logout(
				) method;

private:
	TCPSError CreateTrunk(
				IN const tcps_String& trunk
				) method;

private:
	TCPSError RemoveTrunk(
				IN const tcps_String& trunk
				) method;

private:
	TCPSError ListTrunk(
				OUT tcps_Array<tcps_String>& trunks
				) method;

private:
	TCPSError AddAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag,
				IN const tcps_Array<PCC_ModuleFile>& files
				) method;

private:
	TCPSError RemoveAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method;

private:
	TCPSError ListAuthCenter(
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_Tag>& authTags
				) method;

private:
	TCPSError FindAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method;

private:
	TCPSError AddModule(
				IN const tcps_String& trunk,
				IN INT64 modelKey,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles,
				OUT INT64& moduleKey
				) method;

private:
	TCPSError AddModuleFile(
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles
				) method;

private:
	TCPSError RemoveModule(
				IN const tcps_String& trunk,
				IN INT64 moduleKey
				) method;

private:
	TCPSError RemoveModuleFiles(
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN INT32 fileType
				) method;

private:
	TCPSError ListModules(
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo
				) method;

private:
	TCPSError AddModel(
				IN const PCC_ModelProperty& modelProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) method;

private:
	TCPSError ListModels(
				OUT tcps_Array<PCC_ModelPropWithKey>& modelsInfo
				) method;

private:
	TCPSError DelModel(
				IN INT64 modelKey
				) method;

public:
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const void* redirectParam, IN INT32 redirectParam_len
				) posting_callback;
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
		{	return this->SetRedirect_(
							redirectIPP,
							redirectParam.Get(), redirectParam.Length()
							);
		}

public:
	static TCPSError SetRedirect__Batch(
				IN const PPCC_Deploy_S_* sessions,
				IN INT_PTR sessionsCount,
				IN const IPP& redirectIPP,
				IN const void* redirectParam, IN INT32 redirectParam_len,
				OUT PPCC_Deploy_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback;
	static inline TCPSError SetRedirect__Batch(
				IN const PPCC_Deploy_S_* sessions,
				IN INT_PTR sessionsCount,
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam,
				OUT PPCC_Deploy_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback
		{	return PCC_Deploy_S::SetRedirect__Batch(
							sessions, sessionsCount,
							redirectIPP,
							redirectParam.Get(), redirectParam.Length(),
							sendFaileds, failedCount
							);
		}

	/////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 /////
private:
	void OnNetworkMalformed_()
		{	this->CloseSession();	}

public:
	PCC_CenterSessionMaker& m_sessionMaker;
	PCC_CenterSession* const m_sessionR;
	IPCC_Deploy_LocalCallback* const m_sessionL;
	struct TIDFlag_
	{
		OSThreadID tid;
		TIDFlag_() : tid(INVALID_OSTHREADID) {}
	};
	TIDFlag_ m_closingTID_L;

private:
	iscm_PostingSendParam m_postingSendParam;

private:
	struct CallSiteL_
	{
		struct TFunc
		{
			PROC fnOnStreamedCallback_L_;
			TFunc()
				: fnOnStreamedCallback_L_(NULL)
				{}
		};
		TFunc* func_;
		CallSiteL_() : func_(NULL) {}
		~CallSiteL_() { if(func_) tcps_Delete(func_); }
	};
	CallSiteL_ m_callSiteL; // m_sessionL!=NULL时有效

private:
	iscm_MatchingUpdateFlag m_callbackMatchingUpdatedFlag;
	CallbackMatchingFlag m_callbackMatchingFlag;
	TCPSError UpdateCallbackMatchingFlag_();

private:
	TCPSError SetTimeout_(
				IN INT32 recvTimeout,
				IN INT32 sendTimeout
				) posting_method;

private:
	TCPSError SetSessionBufferSize_(
				IN INT32 recvBufBytes,
				IN INT32 sendBufBytes
				) posting_method;

private:
	TCPSError MethodCheck_(
				IN const tcps_Array<tcps_String>& methods,
				IN const tcps_Array<tcps_String>& methodTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) method;

private:
	TCPSError CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback;
};

class PCC_User;
class PCC_User_LS;
class PCC_User_S : public PCC_User_T
{
	friend class PCC_User;
	friend class PCC_CenterSession;
	friend class PCC_User_LS;
private:
	PCC_User_S(const PCC_User_S&);
	PCC_User_S& operator= (const PCC_User_S&);

	typedef PCC_User_S* PPCC_User_S_;

public:
	// TODO: 可以在此处添加PCC_User的自定义成员
	MY_NP_GridUserClient m_gridConn;
	IPP m_client_ipp;
private:
	PCC_User_S(PCC_CenterSessionMaker& sessionMaker, PCC_CenterSession* sessionR, IPCC_User_LocalCallback* sessionL);
	~PCC_User_S();
	TCPSError OnConnected(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN INT32 sessionCount
				);
	void OnCallbackReady();
	void OnPostingCallReady();
	void OnPeerBroken(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				);
	void OnClose(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				);

public:
	// 主动关闭会话
	void CloseSession(
				IN TCPSError cause = TCPS_OK
				);

	// 获取对端IPP
	// peerID用于返回对端的peerID_IPP
	IPP GetPeerIPP(
				OUT IPP* peerID = NULL
				) const;

	// 对端是否为进程内客户端
	BOOL IsLocalPeer() const;

	// 判断回调连接是否就绪
	BOOL CallbackIsReady() const;

	// 设置回调调用网络超时，INFINITE表示使用默认值，回调未就绪时返回失败
	TCPSError SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	TCPSError GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				);

	// 设置同步调用网络缓冲大小，<0表示不改变此项，==0表示恢复默认值
	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	// 设置posting执行端参数
	// @maxPendingBytes[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_PENDING_BUFFER_SIZE）
	// @maxPendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_PENDINGS）
	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

	// 设置posting调用端参数
	// @maxBufferingSize[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_SEND_BUFFER_SIZE）
	// @maxSendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_SENDINGS）
	void SetPostingSendParameters(
				IN INT32 maxBufferingSize /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxBufferingSize /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// 清理会话的posting回调发送队列
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount
				);

	// 回调匹配检查支持
public:
	struct CallbackMatchingFlag
	{
		struct Info
		{
			BOOL* pMatchingVar;
			BOOL isPosting;
			Info(BOOL* p, BOOL is) : pMatchingVar(p), isPosting(is) {}
		};
		typedef tcps_QuickStringMap<CPtrStrA, Info, 3> CallbackMap;
		CallbackMap cbmap_;
		BOOL matching_OnExecuted;
		BOOL matching_OnExecuted1;
		BOOL matching_SetRedirect_;
		void Reset();
		CallbackMatchingFlag();
	};
public:
	// 获取本地与对端回调匹配信息
	const CallbackMatchingFlag& GetCallbackMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// 下面流式调用定义仅用于非C++语言的辅助实现
private:
	TCPSError OnStreamedCall_L_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

public:
	TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

private:
	TCPSError GetPccProperty(
				OUT PCCProperty& pccProp
				) method;

private:
	TCPSError ListNodes(
				OUT tcps_Array<PCC_NodeDesc>& nodes
				) method;

private:
	TCPSError GetNodeDynamicContext(
				IN const tcps_String& nodeName,
				OUT PCC_DynamicContext& dynamicContext
				) method;

private:
	TCPSError ListModules(
				IN const tcps_String& regex,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method;

private:
	TCPSError Execute(
				IN INT64 moduleKey,
				IN const tcps_String& inputUrl,
				IN const tcps_String& outputUrl,
				IN const tcps_Binary& moduleParams,
				OUT INT64& jobKey
				) method;

public:
	TCPSError OnExecuted(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const void* context, IN INT32 context_len
				) posting_callback;
	TCPSError OnExecuted(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context
				) posting_callback
		{	return this->OnExecuted(
							jobKey,
							errorCode,
							context.Get(), context.Length()
							);
		}

public:
	static TCPSError OnExecuted_Batch(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const void* context, IN INT32 context_len,
				OUT PPCC_User_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback;
	static inline TCPSError OnExecuted_Batch(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context,
				OUT PPCC_User_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback
		{	return PCC_User_S::OnExecuted_Batch(
							sessions, sessionsCount,
							jobKey,
							errorCode,
							context.Get(), context.Length(),
							sendFaileds, failedCount
							);
		}

public:
	TCPSError OnExecuted1(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const void* context, IN INT32 context_len,
				IN const tcps_Array<tcps_Binary>& outArgs
				) posting_callback;
	TCPSError OnExecuted1(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context,
				IN const tcps_Array<tcps_Binary>& outArgs
				) posting_callback
		{	return this->OnExecuted1(
							jobKey,
							errorCode,
							context.Get(), context.Length(),
							outArgs
							);
		}
	TCPSError OnExecuted1(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const void* context, IN INT32 context_len,
				IN const tcps_Binary* outArgs, IN INT32 outArgs_count
				) posting_callback
		{	return this->OnExecuted1(
							jobKey,
							errorCode,
							context, context_len,
							tcps_Array<tcps_Binary>(xat_bind, (tcps_Binary*)outArgs, outArgs_count)
							);
		}

public:
	static TCPSError OnExecuted1_Batch(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const void* context, IN INT32 context_len,
				IN const tcps_Array<tcps_Binary>& outArgs,
				OUT PPCC_User_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback;
	static inline TCPSError OnExecuted1_Batch(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context,
				IN const tcps_Array<tcps_Binary>& outArgs,
				OUT PPCC_User_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback
		{	return PCC_User_S::OnExecuted1_Batch(
							sessions, sessionsCount,
							jobKey,
							errorCode,
							context.Get(), context.Length(),
							outArgs,
							sendFaileds, failedCount
							);
		}
	static inline TCPSError OnExecuted1_Batch(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const void* context, IN INT32 context_len,
				IN const tcps_Binary* outArgs, IN INT32 outArgs_count,
				OUT PPCC_User_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback
		{	return PCC_User_S::OnExecuted1_Batch(
							sessions, sessionsCount,
							jobKey,
							errorCode,
							context, context_len,
							tcps_Array<tcps_Binary>(xat_bind, (tcps_Binary*)outArgs, outArgs_count),
							sendFaileds, failedCount
							);
		}

private:
	TCPSError QueryJobs(
				IN const tcps_Array<INT64>& jobsKey,
				OUT tcps_Array<ExecuteState>& jobsState
				) method;

private:
	TCPSError CancelJob(
				IN INT64 jobKey
				) posting_method;

public:
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const void* redirectParam, IN INT32 redirectParam_len
				) posting_callback;
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
		{	return this->SetRedirect_(
							redirectIPP,
							redirectParam.Get(), redirectParam.Length()
							);
		}

public:
	static TCPSError SetRedirect__Batch(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount,
				IN const IPP& redirectIPP,
				IN const void* redirectParam, IN INT32 redirectParam_len,
				OUT PPCC_User_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback;
	static inline TCPSError SetRedirect__Batch(
				IN const PPCC_User_S_* sessions,
				IN INT_PTR sessionsCount,
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam,
				OUT PPCC_User_S_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_callback
		{	return PCC_User_S::SetRedirect__Batch(
							sessions, sessionsCount,
							redirectIPP,
							redirectParam.Get(), redirectParam.Length(),
							sendFaileds, failedCount
							);
		}

	/////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 /////
private:
	void OnNetworkMalformed_()
		{	this->CloseSession();	}

public:
	PCC_CenterSessionMaker& m_sessionMaker;
	PCC_CenterSession* const m_sessionR;
	IPCC_User_LocalCallback* const m_sessionL;
	struct TIDFlag_
	{
		OSThreadID tid;
		TIDFlag_() : tid(INVALID_OSTHREADID) {}
	};
	TIDFlag_ m_closingTID_L;

private:
	iscm_PostingSendParam m_postingSendParam;

private:
	struct CallSiteL_
	{
		struct TFunc
		{
			PROC fnOnStreamedCallback_L_;
			PROC fnOnExecuted;
			PROC fnOnExecuted1;
			TFunc()
				: fnOnStreamedCallback_L_(NULL)
				, fnOnExecuted(NULL)
				, fnOnExecuted1(NULL)
				{}
		};
		TFunc* func_;
		CallSiteL_() : func_(NULL) {}
		~CallSiteL_() { if(func_) tcps_Delete(func_); }
	};
	CallSiteL_ m_callSiteL; // m_sessionL!=NULL时有效

private:
	iscm_MatchingUpdateFlag m_callbackMatchingUpdatedFlag;
	CallbackMatchingFlag m_callbackMatchingFlag;
	TCPSError UpdateCallbackMatchingFlag_();

private:
	TCPSError UDPLink_(
				OUT INT32& servePort,
				OUT INT32& linkKey
				) method;

private:
	TCPSError UDPLinkConfirm_(
				) method;

private:
	TCPSError SetTimeout_(
				IN INT32 recvTimeout,
				IN INT32 sendTimeout
				) posting_method;

private:
	TCPSError SetSessionBufferSize_(
				IN INT32 recvBufBytes,
				IN INT32 sendBufBytes
				) posting_method;

private:
	TCPSError MethodCheck_(
				IN const tcps_Array<tcps_String>& methods,
				IN const tcps_Array<tcps_String>& methodTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) method;

private:
	TCPSError CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback;
};

//[[end_iscm]]

//[[begin_session_wrap]]

//////////////////////////////////////////////////////////////
// PCC_CenterSessionMaker
class BaseFacet_S;
class PCC_CenterSessionMaker : public iscm_IRPCSessionMaker
{
	friend class iscm_SessionRegister;
	friend class PCC_CenterSession;
	friend class BaseFacet_S;
private:
	PCC_CenterSessionMaker(const PCC_CenterSessionMaker&);
	PCC_CenterSessionMaker& operator= (const PCC_CenterSessionMaker&);

public:
	void* const m_userParameter;

public:
	explicit PCC_CenterSessionMaker(void* userParameter = NULL);
	virtual ~PCC_CenterSessionMaker();

public:
	/// 获取某客户端，某接口对象的当前连接数量
	///	注：进程内连接在此未做统计
	/// @clientID_IPP[in] 客户端标识IPP，INVALID_IPP表示查询所有连接
	/// @faceName[in] 接口对象名，NULL表示查询所有接口对象
	/// @return 接口对象数量
	int GetSessionCount(const IPP& clientID_IPP = INVALID_IPP, const char* faceName = NULL)
		{	return m_sessionRegister.GetFaceObjsCount_(clientID_IPP, faceName);	}

public:
	/// 注册会话
	template<typename SESSION>
	TCPSError Register(SESSION* session)
		{	return m_sessionRegister.Register(session);	}

	/// 撤销注册（ISCM框架在会话关闭前会自动撤销已注册的会话）
	template<typename SESSION>
	TCPSError Unregister(SESSION* session)
		{	return m_sessionRegister.Unregister(session);	}

	///////// 下面这些公共成员函数为框架程序使用，请勿直接使用 ////////
public:
	virtual int GetSessionObjSize() const;
	virtual void MakeSessionObj(void* session);
	virtual void OnServiceCreated(
				IN const IPP& serveIPP,
				IN iscm_IRPCServeMan* rpcMan
				);
	virtual void OnServiceClose(
				IN const IPP& serveIPP,
				IN iscm_IRPCServeMan* rpcMan
				);

public:
	void RegisterLocalSession_(iscm_ILocalCallbackBase* session);
	void UnregisterLocalSession_(iscm_ILocalCallbackBase* session);

public:
	CLocker& GetUserRegisteredLock__()
		{	return m_sessionRegister.GetLock__();	}
	iscm_SessionRegister::SessionMap& GetUserRegisteredMap__()
		{	return m_sessionRegister.GetUserRegisteredMap__();	}

public:
	void OnSessionConnect_(INT32* nextSessionKey /*= NULL*/, INT32& sessionCount);
	void OnSessionClosed_();

private:
	mutable CLocker m_lock;
	typedef tcps_set<iscm_ILocalCallbackBase*> LocalSessionsSet;
	LocalSessionsSet m_localSessionsSet; /// 进程内服务会话对象指针表
	iscm_SessionRegister m_sessionRegister;

	tcps_IServeMan* m_serveMan;
	IntSerialKeyGenerater<CNullLocker, INT32> m_sessionKeyGenerater;
	INT32 m_sessionCount;
};

/////////////////////////////////////////////////////////////////////
///////// 本头文件在此之后的代码为框架程序使用，请勿直接使用 ////////
class PCC_CenterSession : public iscm_IRPCSession, public iscm_IUDPSession
{
	friend class iscm_SessionRegister;
	//[[begin_face_friend]]
	friend class PCC_Center_S;
	friend class PCC_Deploy_S;
	friend class PCC_User_S;
	//[[end_face_friend]]

private:
	PCC_CenterSession(const PCC_CenterSession&);
	PCC_CenterSession& operator= (const PCC_CenterSession&);

public:
	explicit PCC_CenterSession(PCC_CenterSessionMaker& sessionMaker);
	virtual ~PCC_CenterSession();

	// 下面一组函数用于实现接口iscm_IRPCSession
	// ISCM内部使用
private:
	virtual TCPSError OnConnected(
				IN iscm_IRPCServeMan* serveMan,
				IN tcps_ISession* bindedSession,
				IN const IPP& serveIPP,
				IN const IPP& peerIPP,
				IN INT32 sessionKey,
				IN INT32 sessionCount,
				IN tcps_ITrusteeParameter* trusteeParam /*= NULL*/
				);
	virtual void OnPrepareClose(
				IN TCPSError cause
				);
	virtual BOOL IsSessionBusying() const;
	virtual void OnClose(
				IN TCPSError cause
				);
	virtual void OnPrepareCall(
				IN const iscm_RPCReq& req,
				IN const void* data,
				OUT BOOL& notifyByTaskPool /*= true*/
				);
	virtual TCPSError OnCall(
				OUT BOOL& requireReplyData /*= true*/,
				OUT BOOL& destroySession /*= false*/,
				IN const iscm_RPCReq& req,
				IN const void* data,
				OUT BOOL& dataTransferred /*= false*/,
				IN iscm_IRPCOutfiter* outfiter
				);
	virtual iscm_IRPCServeMan* GetServeMan() const;

private:
	virtual void OnUDPCall(
				IN tcps_Binary& frame
				);

private:
	TCPSError BindCallbackSocket_(
				IN SOCKET sock,
				IN const char* peerIPPTxt
				);
	TCPSError BindPostingSocket_(
				IN SOCKET sock,
				IN const char* peerIPPTxt
				);
	static TCPSError OnRPCCall_(
				IN PCC_CenterSession* thisObj /*= NULL*/,
				IN void* faceObj /*= NULL*/,
				OUT BOOL& requireReplyData /*= true*/,
				IN const void* inParamsData,
				OUT BOOL& dataTransferred /*= false*/,
				IN INT_PTR inParamsDataLen,
				OUT iscm_IRPCOutfiter* outfiter
				);

private:
	//[[begin_method_wrap]]
	static TCPSError Wrap_PCC_Center_UDPLink_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Center_UDPLinkConfirm_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Center_SetTimeout_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_method;
	static TCPSError Wrap_PCC_Center_SetSessionBufferSize_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_method;
	static TCPSError Wrap_PCC_Center_MethodCheck_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_Login(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_Logout(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_CreateTrunk(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_RemoveTrunk(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_ListTrunk(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_AddAuthCenter(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_RemoveAuthCenter(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_ListAuthCenter(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_FindAuthCenter(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_AddModule(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_AddModuleFile(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_RemoveModule(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_RemoveModuleFiles(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_ListModules(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_AddModel(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_ListModels(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_DelModel(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_Deploy_SetTimeout_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_method;
	static TCPSError Wrap_PCC_Deploy_SetSessionBufferSize_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_method;
	static TCPSError Wrap_PCC_Deploy_MethodCheck_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_GetPccProperty(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_ListNodes(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_GetNodeDynamicContext(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_ListModules(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_Execute(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_QueryJobs(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_CancelJob(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_method;
	static TCPSError Wrap_PCC_User_UDPLink_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_UDPLinkConfirm_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	static TCPSError Wrap_PCC_User_SetTimeout_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_method;
	static TCPSError Wrap_PCC_User_SetSessionBufferSize_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_method;
	static TCPSError Wrap_PCC_User_MethodCheck_(PCC_CenterSession*, void*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) method;
	//[[end_method_wrap]]

private:
	PCC_CenterSessionMaker& m_sessionMaker;
	iscm_IRPCServeMan* m_serveMan;	///< 本会话所属的服务管理器（NULL表示本会话为未连接态，或为待关闭态）
	tcps_ISession* m_bindedSession;
	IPP m_serveIPP;
	IPP m_peerIPP;
	INT32 m_sessionCount;			///< 记录初始化本会话对象时，已经成功连接的会话数量（包括本会话）
	IPP m_peerID_IPP;				///< 对端标识IPP，为对方的ISCM服务IPP（若为普通ISCM客户端程序，则端口为0）
	tcps_String m_bindedInterface;	///< 与本会话绑定的接口类型名

	// 下面一组变量用于支持反向回调（callback）
private:
	DataOutfiter m_callbackOutfiter;
	// 用于向client端进行callback调用
	// m_callbackRequester.face_为NULL或处于未连接状态，表示无callback调用，或者client还未启动callback
	AutoDeleteInterface<iscm_IRequester> m_callbackRequester;

	struct UDPSite_
	{
		INT32 localPort_;
		SOCKET sock_;		///< listen UDP socket，临时记录，握手完成后由iscm_IUDPServeMan管理
		UDPSite_() : localPort_(-1), sock_(INVALID_SOCKET) {}
		BOOL IsOn() const
		{
			BOOL is = localPort_>0;
			ASSERT(is || !SockValid(sock_));
			return is;
		}
		BOOL IsLinking() const
			{	return localPort_>0 && SockValid(sock_);	}
		BOOL IsLinked() const
			{	return localPort_>0 && !SockValid(sock_);	}
	};
	UDPSite_ m_udpSite;

private:
	struct PostingProxy_ : public iscm_IPostingCallerMan::INotifier
	{
		PCC_CenterSession& session_;
		INT32 callerKey_; // 为iscm_IPostingCallerMan中的会话标识

		explicit PostingProxy_(PCC_CenterSession& session)
			: session_(session), callerKey_(0)
			{}

		virtual void OnSessionClose(
					IN INT32 callerKey,
					IN TCPSError cause
					)
		{
			(void)callerKey;
			ASSERT(callerKey_ == callerKey);
			callerKey_ = 0;
			session_.CloseSession_(cause);
		}

		virtual void OnSessionPost(
					IN INT32 callerKey,
					IN const void* data,
					IN INT_PTR dataLen,
					OUT BOOL& dataTransferred /*= false*/
					)
		{
			(void)callerKey;
			ASSERT(callerKey_ == callerKey);
			while(true)
			{
				BOOL requireReplyData = true;
				TCPSError err = OnRPCCall_(&session_, NULL, requireReplyData, data, dataTransferred, dataLen, NULL);
				ASSERT(TCPS_OK!=err || !requireReplyData);
				if(TCPS_ERR_POSTING_PENDING_FULL == err)
				{
					ASSERT(!dataTransferred);
					Sleep(1);
					continue;
				}
				else
					break;
			}
		}
	};
	friend struct PostingProxy_;
	PostingProxy_ m_postingProxy;

private:
	//[[begin_face_member]]
	enum FaceTypeValue
	{
		ftv_InvalidFace,
		ftv_PCC_Center,
		ftv_PCC_Deploy,
		ftv_PCC_User,
	};
	union
	{
		void* m_sessionDummyPtr;
		PCC_Center_S* m_pCC_Center;
		PCC_Deploy_S* m_pCC_Deploy;
		PCC_User_S* m_pCC_User;
	};
public:
	PCC_Center_S* GetPCC_Center()
		{	return ("PCC_Center"==m_bindedInterface ? m_pCC_Center : NULL);	}
	PCC_Deploy_S* GetPCC_Deploy()
		{	return ("PCC_Deploy"==m_bindedInterface ? m_pCC_Deploy : NULL);	}
	PCC_User_S* GetPCC_User()
		{	return ("PCC_User"==m_bindedInterface ? m_pCC_User : NULL);	}
	//[[end_face_member]]

public:
	// 获取会话流水标识号（0为无效号）
	INT32 GetSessionKey() const;

private:
	void CloseSession_(
				IN TCPSError cause /*= TCPS_OK*/
				);
	void OnNetworkMalformed_()
		{	this->CloseSession_(TCPS_ERR_NETWORK_MALFORMED);	}

	// 下面流式调用定义仅用于非C++语言的辅助实现
private:
	iscm_ServerStreamedCallSite m_streamedCallSite;

private:
	typedef tcps_QuickStringMap<CPtrStrA, FaceTypeValue> FTVMap_;
	static FTVMap_& GetFTVMap_();
	static FTVMap_* sm_FTVMap;
	static void InitFTVMap_();

private:
	typedef TCPSError (*FMethodHandler_)(IN PCC_CenterSession* thisObj, IN void* faceObj, IN iscm_PeerCallFlags peerCallFlags, IN OUT const BYTE*& ptrInParams, IN OUT INT_PTR& ptrInParamsLen, OUT iscm_IRPCOutfiter* outfiter);
	struct MethodSite_
	{
		FMethodHandler_ handler;
		BOOL isPosting; // 是否为 posting 修饰的方法/回调
		explicit MethodSite_(FMethodHandler_ hd = NULL, BOOL pst = false)
			: handler(hd), isPosting(pst)
			{}
	};
	typedef tcps_QuickStringMap<CPtrStrA, MethodSite_> MethodCallMap_;
	static MethodCallMap_& GetMethodCallMap_();
	static MethodCallMap_* sm_methodCallMap;

private:
	mutable CLocker m_methodCallLock;
	struct PostingTask_ : public NPBaseTask
	{
		PCC_CenterSession& session_;
		iscm_PeerCallFlags peerCallFlags_;
		void* baseInParamsData_;
		const BYTE* inParamsData_;
		INT_PTR inParamsDataLen_;
		FMethodHandler_ handler_;

		explicit PostingTask_(PCC_CenterSession& session) : session_(session) {}
		virtual ~PostingTask_() {}
		virtual void OnPoolTask();
	};
	friend struct PostingTask_;
	struct PostingTaskSite_
	{
		mutable CLocker lock;
		INT_PTR callingsDataBytes;
		INT32 callingCount;
		NPBaseTask* head;
		NPBaseTask* tail;
		PostingTaskSite_() : callingsDataBytes(0), callingCount(0), head(NULL), tail(NULL) {}
	};
	PostingTaskSite_ m_postingMethods;

// 下面一组变量用于查错和调试
#ifdef _DEBUG
private:
	LTMSEL mutable m_closingPromptTime;	///< 上一次关闭警告打印时间（INVALID_UTC_MSEL表示不处于正关闭态）
	union
	{
	OSThreadID m_callingPostingTaskTID;	///< 正在调用本会话posting method的线程ID
	void* m_callingPostingTaskTID_hex;
	INT_PTR m_callingPostingTaskTID_int;
	};
#endif

private:
	iscm_PostingPendingParam m_postingPendingParam;
};
//[[end_session_wrap]]

#endif	// #ifndef _PCC_CenterSession_h_
