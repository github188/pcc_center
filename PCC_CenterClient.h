// PCC_CenterClient.h
//
// 注意: 此文件为工具生成，请不要修改

#ifndef _PCC_CenterClient_h_
#define _PCC_CenterClient_h_

#if defined(_MSC_VER) && (_MSC_VER > 1000)
	#pragma once
#endif

#include "iscm_helper.h"
#include "iscm_smart_container.h"
#include "PCC_CenterTypesDefine.h"

//[[begin_iscm]]

#ifndef PCC_Center_defined
#define PCC_Center_defined
class PCC_Center_S;
class PCC_Center_RC;
class PCC_Center : public IPCC_Center_LocalCallback
{
	friend class PCC_Center_S;
	friend class PCC_Center_RC;
private:
	PCC_Center(const PCC_Center&);
	PCC_Center& operator= (const PCC_Center&);

	typedef PCC_Center* PPCC_Center_;

public:
	// initNetworkSingletons，是否初始化网络相关单件（若只用于连接进程内服务，可传false）
	explicit PCC_Center(BOOL initNetworkSingletons = true);
	virtual ~PCC_Center();

protected:
	// 析构RPC请求对象
	// 注意：若有派生类，必须且只能在派生类的析构函数的最后调用，
	//		 以保证派生类对象继承的通知虚函数总被正确调用。
	void DestroyRequester();

	// 连接后通知虚函数
	// 若返回失败，则立即触发OnClose()，且继续异步尝试连接
	// TODO: 若需处理连接动作，请在派生类中重载OnConnected()
	virtual TCPSError OnConnected()
		{	return TCPS_OK;	}

	// 对端断线通知虚函数（在OnClose()之前被调用）
	// 注: 只有对端关闭或网络断线才会触发，Client对象被析构或设置INVALID_IPP不会触发
	// TODO: 若需处理此动作，请在派生类中重载OnPeerBroken()
	virtual void OnPeerBroken()
		{	}

	// 连接关闭通知虚函数（在OnPeerBroken()之后被调用）
	// 注: 所有关闭情况都会触发
	// TODO: 若需处理关闭动作，请在派生类中重载OnClose()
	virtual void OnClose()
		{	}

	// 连接超时通知虚函数
	// TODO: 若需处理连接超时动作，请在派生类中重载OnConnectTimeout()
	virtual void OnConnectTimeout(IN TCPSError cause)
		{	(void)cause;	}

public:
	// 设置正向服务参数
	// @serveIPP[in] 第一备选服务器IPP，INVALID_IPP表示取消连接
	// @sessionFlags[in] 会话标志，为以下值的位组合
	//		ISCMC_NO_CALLBACK、ISCMC_ASYNC_CONNECT、ISCMC_UDP_POSTING、ISCMC_NO_ASYNC_RECONNECT、ISCMC_NO_POSTING_CHANNEL
	// @clientID_IPP[in] 客户端标识IPP，INVALID_IPP使用自动值（标识端口使用0）
	// @secondaryServeIPP[in] 第二备选服务IPP（取消连接时本参数被忽略）
	// @tertiaryServeIPP[in] 第三备选服务IPP（取消连接时本参数被忽略）
	// @reconnectIntervalMSELs[in] 网络重建间隔时间
	TCPSError SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	IPP GetServeIPP() const;
	IPP GetServingIPP() const;
	BOOL IsConnected() const;

	// 设置连接保持标志
	//		注：调用SetServeIPP()时，若指定了ISCMC_NO_ASYNC_RECONNECT，
	//			则连接保持标志为false；否则为true
	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	// 对端是否为进程内服务
	BOOL IsLocalPeer() const;

	// 准备断开网络，在有巨量会话对象需要关闭网络时，先批量调用一次PrepareDisconnect()，
	// 调用PrepareDisconnect()后，再调用SetServeIPP(INVALID_IPP)，或析构接口对象
	void PrepareDisconnect();

	// 设置网络超时，INFINITE表示使用默认值（网络对端也会被设置）
	void SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	void GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const;

	// 设置同步调用网络缓冲大小，<0表示不改变此项，==0表示恢复默认值（网络对端也会被设置）
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
	// @maxSendingBytes[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_SEND_BUFFER_SIZE）
	// @maxSendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_SENDINGS）
	void SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// 清理客户端对象的posting方法发送队列
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_Center_* clients,
				IN INT_PTR clientsCount
				);

	// 方法匹配检查支持
public:
	struct MethodMatchingFlag
	{
		struct Info
		{
			BOOL* pMatchingVar;
			BOOL isPosting;
			Info(BOOL* p, BOOL is) : pMatchingVar(p), isPosting(is) {}
		};
		typedef tcps_QuickStringMap<CPtrStrA, Info, 4> MethodMap;
		MethodMap mmap_;
		BOOL matching_UDPLink_;
		BOOL matching_UDPLinkConfirm_;
		BOOL matching_SetTimeout_;
		BOOL matching_SetSessionBufferSize_;
		void Reset();
		MethodMatchingFlag();
	};
public:
	// 获取本地与对端方法匹配信息
	const MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// 下面流式调用定义仅用于非C++语言的辅助实现
public:
	TCPSError GetStreamedMethodTypeInfo_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo /*= NULL*/,
				OUT INT_PTR& infoLen /*= 0*/
				) const;

	virtual TCPSError GetStreamedCallbackTypeInfo_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo /*= NULL*/,
				OUT INT_PTR& infoLen /*= 0*/
				)
	{	// TODO: 请在派生类中重载此函数
		(void)callbackName; (void)nameLen;
		(void)typeInfo; (void)infoLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

	/// 流式方法调用
	/// @methodName[in] 方法名，必须提供
	/// @nameLen[in] 方法名长度，-1表示方法名是一'\0'结束符字符串
	/// @data[in] 方法参数数据（dataLen==0时可以为NULL）
	/// @dataLen[in] 方法参数数据长度（>=0）
	/// @replyData[out] 返回OUT型参数数据（无OUT参数的方法可以传NULL）
	///			注：若*replyData返回非NULL，则必须使用tcps_Free()释放
	/// @replyLen[out] 返回OUT型参数数据长度（无OUT参数的方法可以传NULL）
	/// @return TCPSError
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	/// 流式回调调用通知（在调用普通的回调函数之前被调用）
	/// @callbackName[in] 回调名，必须提供
	///		注：callbackName==NULL时，用于检测StreamedCallback_()是否被派生，
	///			派生类的StreamedCallback_()中，最前面总这样实现：
	///			{
	///				if(NULL == callbackName)
	///					return TCPS_ERR_INVALID_PARAM; // 必须返回非TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED
	///				...
	///			}
	/// @nameLen[in] 回调名长度，-1表示回调名为'\0'结束符字符串
	/// @data[in] 回调IN型参数数据（dataLen==0时可能为NULL）
	/// @dataLen[in] 回调IN型参数数据长度（>=0）
	/// @replyData[out] 返回OUT型参数数据，传入时已置为NULL，
	///			若返回非NULL，则必须使用tcps_Alloc()申请内存；无OUT参数的回调时可返回NULL
	/// @replyLen[out] 返回OUT型参数数据长度，传入时已置为0
	/// @return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED表示忽略此次流式回调调用，
	///			框架若收到此返回值，则会继续调用普通的回调函数；
	///			其它值，直接返回给服务器端。
	///			<<<注：若遇到IN型参数数据无法被正确解析，应该返回TCPS_ERR_MALFORMED_REQ>>>
	virtual TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT void*& replyData /*= NULL*/,
				OUT INT_PTR& replyLen /*= 0*/
				)
	{	// TODO: 请在派生类中重载此函数
		(void)callbackName; (void)nameLen;
		(void)data; (void)dataLen;
		(void)replyData; (void)replyLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError AddModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{	// TODO: 请在派生类中重载此函数
		(void)centerIPP;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError DelModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{	// TODO: 请在派生类中重载此函数
		(void)centerIPP;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError GetStaticContext(
				OUT PCC_NodeDesc& staticContext
				) cacheable_callback
	{	// TODO: 请在派生类中重载此函数
		(void)staticContext;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError GetDynamicContext(
				OUT PCC_DynamicContext& dynamicContext
				) callback
	{	// TODO: 请在派生类中重载此函数
		(void)dynamicContext;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError AddModel(
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback
	{	// TODO: 请在派生类中重载此函数
		(void)moduleProperty; (void)modelFiles;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError DelModel(
				IN const PCC_Tag& tag
				) callback
	{	// TODO: 请在派生类中重载此函数
		(void)tag;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	// 返回TCPS_OK允许重定向；返回非TCPS_OK禁止重定向
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{	// TODO: 请在派生类中重载此函数
		(void)redirectIPP; (void)redirectParam;
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 //////
private:
	void* m_base_v_tab_ptr;
	void* m_derived_v_tab_ptr;
	PCC_Center_RC* m_faceR;

private:
	struct CallSiteL_
	{
		BOOL needUpdateFlags;
		MethodMatchingFlag matchingFlags;
		PROC fnOnStreamedCall_L_;
		CallSiteL_()
			: needUpdateFlags(true)
			, fnOnStreamedCall_L_(NULL)
			{}
		void Reset()
		{
			needUpdateFlags = true;
			matchingFlags.Reset();
			fnOnStreamedCall_L_ = NULL;
		}
	};
	struct LocalMakingFlag_
	{
		BOOL making;
		BOOL failed;
		LocalMakingFlag_() : making(false), failed(false) {}
	};
	LocalMakingFlag_ m_localMakingFlag;	// 用于本地服务递归调用处理
	IPCC_Center_LocalMethod* m_faceL;
	CallSiteL_* m_callSiteL;	// m_faceL!=NULL时有效
	IPP m_localServeIPP;		// m_faceL!=NULL时有效

private:
	OSThreadID m_closingTID;	// 正在关闭会话的用户线程（即正析构Client对象或调用SetServeIPP(NEW_IPP/INVALID_IPP)的线程）

public:
	// 不要使用此函数，仅供框架使用
	OSThreadID GetClosingTID_() const
		{	return m_closingTID;	}

private:
	DWORD m_connectTimeout;
	DWORD m_recvTimeout;
	DWORD m_sendTimeout;
	tcps_SockRecvSendBufParam m_sockRecvSendBufParam;
	iscm_PostingPendingParam m_postingPendingParam;
	iscm_PostingSendParam m_postingSendParam;

private:
	CLocker m_lock;
	BOOL m_streamedCallbackMap_IsInited;
	typedef tcps_QuickStringMap<
				CPtrStrA/*callback_name*/,
				BOOL /*callback_is_matched*/,
				6> StreamedCallbackMap;
	StreamedCallbackMap m_streamedCallbackMap;

public:
	/// 判断流式回调方的回调版本是否匹配（本函数内部会调用this->GetStreamedCallbackTypeInfo_()）
	BOOL IsStreamedCallbackMatched_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/
				);

private:
	TCPSError SetServeIPP_(
				IN BOOL byLocalPeer,
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	void DestroyRequester_(
				IN BOOL byLocalPeer
				);

	void OnNetworkMalformed_();
	virtual void CloseSession_();

	virtual PROC FindCallback_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				);

	static TCPSError OnStreamedCallback_L_(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	static TCPSError Local_AddModelCenter(
				IN void* sessionObj_wrap,
				IN const IPP& centerIPP
				) posting_callback;

	static TCPSError Local_DelModelCenter(
				IN void* sessionObj_wrap,
				IN const IPP& centerIPP
				) posting_callback;

	static TCPSError Local_GetStaticContext(
				IN void* sessionObj_wrap,
				OUT PCC_NodeDesc& staticContext
				) cacheable_callback;

	static TCPSError Local_GetDynamicContext(
				IN void* sessionObj_wrap,
				OUT PCC_DynamicContext& dynamicContext
				) callback;

	static TCPSError Local_AddModel(
				IN void* sessionObj_wrap,
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback;

	static TCPSError Local_DelModel(
				IN void* sessionObj_wrap,
				IN const PCC_Tag& tag
				) callback;
};
#endif // #ifndef PCC_Center_defined

#ifndef PCC_Deploy_defined
#define PCC_Deploy_defined
class PCC_Deploy_S;
class PCC_Deploy_RC;
class PCC_Deploy : public IPCC_Deploy_LocalCallback
{
	friend class PCC_Deploy_S;
	friend class PCC_Deploy_RC;
private:
	PCC_Deploy(const PCC_Deploy&);
	PCC_Deploy& operator= (const PCC_Deploy&);

	typedef PCC_Deploy* PPCC_Deploy_;

public:
	// initNetworkSingletons，是否初始化网络相关单件（若只用于连接进程内服务，可传false）
	explicit PCC_Deploy(BOOL initNetworkSingletons = true);
	virtual ~PCC_Deploy();

protected:
	// 析构RPC请求对象
	// 注意：若有派生类，必须且只能在派生类的析构函数的最后调用，
	//		 以保证派生类对象继承的通知虚函数总被正确调用。
	void DestroyRequester();

	// 连接后通知虚函数
	// 若返回失败，则立即触发OnClose()，且继续异步尝试连接
	// TODO: 若需处理连接动作，请在派生类中重载OnConnected()
	virtual TCPSError OnConnected()
		{	return TCPS_OK;	}

	// 对端断线通知虚函数（在OnClose()之前被调用）
	// 注: 只有对端关闭或网络断线才会触发，Client对象被析构或设置INVALID_IPP不会触发
	// TODO: 若需处理此动作，请在派生类中重载OnPeerBroken()
	virtual void OnPeerBroken()
		{	}

	// 连接关闭通知虚函数（在OnPeerBroken()之后被调用）
	// 注: 所有关闭情况都会触发
	// TODO: 若需处理关闭动作，请在派生类中重载OnClose()
	virtual void OnClose()
		{	}

	// 连接超时通知虚函数
	// TODO: 若需处理连接超时动作，请在派生类中重载OnConnectTimeout()
	virtual void OnConnectTimeout(IN TCPSError cause)
		{	(void)cause;	}

public:
	// 设置正向服务参数
	// @serveIPP[in] 第一备选服务器IPP，INVALID_IPP表示取消连接
	// @sessionFlags[in] 会话标志，为以下值的位组合
	//		ISCMC_NO_CALLBACK、ISCMC_ASYNC_CONNECT、ISCMC_UDP_POSTING、ISCMC_NO_ASYNC_RECONNECT、ISCMC_NO_POSTING_CHANNEL
	// @clientID_IPP[in] 客户端标识IPP，INVALID_IPP使用自动值（标识端口使用0）
	// @secondaryServeIPP[in] 第二备选服务IPP（取消连接时本参数被忽略）
	// @tertiaryServeIPP[in] 第三备选服务IPP（取消连接时本参数被忽略）
	// @reconnectIntervalMSELs[in] 网络重建间隔时间
	TCPSError SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	IPP GetServeIPP() const;
	IPP GetServingIPP() const;
	BOOL IsConnected() const;

	// 设置连接保持标志
	//		注：调用SetServeIPP()时，若指定了ISCMC_NO_ASYNC_RECONNECT，
	//			则连接保持标志为false；否则为true
	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	// 对端是否为进程内服务
	BOOL IsLocalPeer() const;

	// 准备断开网络，在有巨量会话对象需要关闭网络时，先批量调用一次PrepareDisconnect()，
	// 调用PrepareDisconnect()后，再调用SetServeIPP(INVALID_IPP)，或析构接口对象
	void PrepareDisconnect();

	// 设置网络超时，INFINITE表示使用默认值（网络对端也会被设置）
	void SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	void GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const;

	// 设置同步调用网络缓冲大小，<0表示不改变此项，==0表示恢复默认值（网络对端也会被设置）
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
	// @maxSendingBytes[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_SEND_BUFFER_SIZE）
	// @maxSendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_SENDINGS）
	void SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// 清理客户端对象的posting方法发送队列
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_Deploy_* clients,
				IN INT_PTR clientsCount
				);

	// 方法匹配检查支持
public:
	struct MethodMatchingFlag
	{
		struct Info
		{
			BOOL* pMatchingVar;
			BOOL isPosting;
			Info(BOOL* p, BOOL is) : pMatchingVar(p), isPosting(is) {}
		};
		typedef tcps_QuickStringMap<CPtrStrA, Info, 19> MethodMap;
		MethodMap mmap_;
		BOOL matching_Login;
		BOOL matching_Logout;
		BOOL matching_CreateTrunk;
		BOOL matching_RemoveTrunk;
		BOOL matching_ListTrunk;
		BOOL matching_AddAuthCenter;
		BOOL matching_RemoveAuthCenter;
		BOOL matching_ListAuthCenter;
		BOOL matching_FindAuthCenter;
		BOOL matching_AddModule;
		BOOL matching_AddModuleFile;
		BOOL matching_RemoveModule;
		BOOL matching_RemoveModuleFiles;
		BOOL matching_ListModules;
		BOOL matching_AddModel;
		BOOL matching_ListModels;
		BOOL matching_DelModel;
		BOOL matching_SetTimeout_;
		BOOL matching_SetSessionBufferSize_;
		void Reset();
		MethodMatchingFlag();
	};
public:
	// 获取本地与对端方法匹配信息
	const MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// 下面流式调用定义仅用于非C++语言的辅助实现
public:
	TCPSError GetStreamedMethodTypeInfo_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo /*= NULL*/,
				OUT INT_PTR& infoLen /*= 0*/
				) const;

	virtual TCPSError GetStreamedCallbackTypeInfo_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo /*= NULL*/,
				OUT INT_PTR& infoLen /*= 0*/
				)
	{	// TODO: 请在派生类中重载此函数
		(void)callbackName; (void)nameLen;
		(void)typeInfo; (void)infoLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

	/// 流式方法调用
	/// @methodName[in] 方法名，必须提供
	/// @nameLen[in] 方法名长度，-1表示方法名是一'\0'结束符字符串
	/// @data[in] 方法参数数据（dataLen==0时可以为NULL）
	/// @dataLen[in] 方法参数数据长度（>=0）
	/// @replyData[out] 返回OUT型参数数据（无OUT参数的方法可以传NULL）
	///			注：若*replyData返回非NULL，则必须使用tcps_Free()释放
	/// @replyLen[out] 返回OUT型参数数据长度（无OUT参数的方法可以传NULL）
	/// @return TCPSError
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	/// 流式回调调用通知（在调用普通的回调函数之前被调用）
	/// @callbackName[in] 回调名，必须提供
	///		注：callbackName==NULL时，用于检测StreamedCallback_()是否被派生，
	///			派生类的StreamedCallback_()中，最前面总这样实现：
	///			{
	///				if(NULL == callbackName)
	///					return TCPS_ERR_INVALID_PARAM; // 必须返回非TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED
	///				...
	///			}
	/// @nameLen[in] 回调名长度，-1表示回调名为'\0'结束符字符串
	/// @data[in] 回调IN型参数数据（dataLen==0时可能为NULL）
	/// @dataLen[in] 回调IN型参数数据长度（>=0）
	/// @replyData[out] 返回OUT型参数数据，传入时已置为NULL，
	///			若返回非NULL，则必须使用tcps_Alloc()申请内存；无OUT参数的回调时可返回NULL
	/// @replyLen[out] 返回OUT型参数数据长度，传入时已置为0
	/// @return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED表示忽略此次流式回调调用，
	///			框架若收到此返回值，则会继续调用普通的回调函数；
	///			其它值，直接返回给服务器端。
	///			<<<注：若遇到IN型参数数据无法被正确解析，应该返回TCPS_ERR_MALFORMED_REQ>>>
	virtual TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT void*& replyData /*= NULL*/,
				OUT INT_PTR& replyLen /*= 0*/
				)
	{	// TODO: 请在派生类中重载此函数
		(void)callbackName; (void)nameLen;
		(void)data; (void)dataLen;
		(void)replyData; (void)replyLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

public:
	TCPSError Login(
				IN const char* ticket, IN INT32 ticket_len /*= -1*/
				) method;
	TCPSError Login(
				IN const char* ticket
				) method
		{	return this->Login(
							ticket, -1
							);
		}
	TCPSError Login(
				IN const tcps_String& ticket
				) method
		{	return this->Login(
							ticket.Get(), ticket.Length()
							);
		}

public:
	TCPSError Logout(
				) method;

public:
	TCPSError CreateTrunk(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/
				) method;
	TCPSError CreateTrunk(
				IN const char* trunk
				) method
		{	return this->CreateTrunk(
							trunk, -1
							);
		}
	TCPSError CreateTrunk(
				IN const tcps_String& trunk
				) method
		{	return this->CreateTrunk(
							trunk.Get(), trunk.Length()
							);
		}

public:
	TCPSError RemoveTrunk(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/
				) method;
	TCPSError RemoveTrunk(
				IN const char* trunk
				) method
		{	return this->RemoveTrunk(
							trunk, -1
							);
		}
	TCPSError RemoveTrunk(
				IN const tcps_String& trunk
				) method
		{	return this->RemoveTrunk(
							trunk.Get(), trunk.Length()
							);
		}

public:
	TCPSError ListTrunk(
				OUT tcps_Array<tcps_String>& trunks
				) method;

public:
	TCPSError AddAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN const PCC_Tag& authTag,
				IN const tcps_Array<PCC_ModuleFile>& files
				) method;
	TCPSError AddAuthCenter(
				IN const char* trunk,
				IN const PCC_Tag& authTag,
				IN const tcps_Array<PCC_ModuleFile>& files
				) method
		{	return this->AddAuthCenter(
							trunk, -1,
							authTag,
							files
							);
		}
	TCPSError AddAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag,
				IN const tcps_Array<PCC_ModuleFile>& files
				) method
		{	return this->AddAuthCenter(
							trunk.Get(), trunk.Length(),
							authTag,
							files
							);
		}
	TCPSError AddAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN const PCC_Tag& authTag,
				IN const PCC_ModuleFile* files, IN INT32 files_count
				) method
		{	return this->AddAuthCenter(
							trunk, trunk_len,
							authTag,
							tcps_Array<PCC_ModuleFile>(xat_bind, (PCC_ModuleFile*)files, files_count)
							);
		}

public:
	TCPSError RemoveAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN const PCC_Tag& authTag
				) method;
	TCPSError RemoveAuthCenter(
				IN const char* trunk,
				IN const PCC_Tag& authTag
				) method
		{	return this->RemoveAuthCenter(
							trunk, -1,
							authTag
							);
		}
	TCPSError RemoveAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method
		{	return this->RemoveAuthCenter(
							trunk.Get(), trunk.Length(),
							authTag
							);
		}

public:
	TCPSError ListAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				OUT tcps_Array<PCC_Tag>& authTags
				) method;
	TCPSError ListAuthCenter(
				IN const char* trunk,
				OUT tcps_Array<PCC_Tag>& authTags
				) method
		{	return this->ListAuthCenter(
							trunk, -1,
							authTags
							);
		}
	TCPSError ListAuthCenter(
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_Tag>& authTags
				) method
		{	return this->ListAuthCenter(
							trunk.Get(), trunk.Length(),
							authTags
							);
		}

public:
	TCPSError FindAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN const PCC_Tag& authTag
				) method;
	TCPSError FindAuthCenter(
				IN const char* trunk,
				IN const PCC_Tag& authTag
				) method
		{	return this->FindAuthCenter(
							trunk, -1,
							authTag
							);
		}
	TCPSError FindAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method
		{	return this->FindAuthCenter(
							trunk.Get(), trunk.Length(),
							authTag
							);
		}

public:
	TCPSError AddModule(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 modelKey,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles,
				OUT INT64& moduleKey
				) method;
	TCPSError AddModule(
				IN const char* trunk,
				IN INT64 modelKey,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles,
				OUT INT64& moduleKey
				) method
		{	return this->AddModule(
							trunk, -1,
							modelKey,
							moduleProperty,
							moudleFiles,
							moduleKey
							);
		}
	TCPSError AddModule(
				IN const tcps_String& trunk,
				IN INT64 modelKey,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles,
				OUT INT64& moduleKey
				) method
		{	return this->AddModule(
							trunk.Get(), trunk.Length(),
							modelKey,
							moduleProperty,
							moudleFiles,
							moduleKey
							);
		}
	TCPSError AddModule(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 modelKey,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const PCC_ModuleFile* moudleFiles, IN INT32 moudleFiles_count,
				OUT INT64& moduleKey
				) method
		{	return this->AddModule(
							trunk, trunk_len,
							modelKey,
							moduleProperty,
							tcps_Array<PCC_ModuleFile>(xat_bind, (PCC_ModuleFile*)moudleFiles, moudleFiles_count),
							moduleKey
							);
		}

public:
	TCPSError AddModuleFile(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles
				) method;
	TCPSError AddModuleFile(
				IN const char* trunk,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles
				) method
		{	return this->AddModuleFile(
							trunk, -1,
							moduleKey,
							fileType,
							moduleFiles
							);
		}
	TCPSError AddModuleFile(
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles
				) method
		{	return this->AddModuleFile(
							trunk.Get(), trunk.Length(),
							moduleKey,
							fileType,
							moduleFiles
							);
		}
	TCPSError AddModuleFile(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const PCC_ModuleFile* moduleFiles, IN INT32 moduleFiles_count
				) method
		{	return this->AddModuleFile(
							trunk, trunk_len,
							moduleKey,
							fileType,
							tcps_Array<PCC_ModuleFile>(xat_bind, (PCC_ModuleFile*)moduleFiles, moduleFiles_count)
							);
		}

public:
	TCPSError RemoveModule(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 moduleKey
				) method;
	TCPSError RemoveModule(
				IN const char* trunk,
				IN INT64 moduleKey
				) method
		{	return this->RemoveModule(
							trunk, -1,
							moduleKey
							);
		}
	TCPSError RemoveModule(
				IN const tcps_String& trunk,
				IN INT64 moduleKey
				) method
		{	return this->RemoveModule(
							trunk.Get(), trunk.Length(),
							moduleKey
							);
		}

public:
	TCPSError RemoveModuleFiles(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 moduleKey,
				IN INT32 fileType
				) method;
	TCPSError RemoveModuleFiles(
				IN const char* trunk,
				IN INT64 moduleKey,
				IN INT32 fileType
				) method
		{	return this->RemoveModuleFiles(
							trunk, -1,
							moduleKey,
							fileType
							);
		}
	TCPSError RemoveModuleFiles(
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN INT32 fileType
				) method
		{	return this->RemoveModuleFiles(
							trunk.Get(), trunk.Length(),
							moduleKey,
							fileType
							);
		}

public:
	TCPSError ListModules(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo
				) method;
	TCPSError ListModules(
				IN const char* trunk,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo
				) method
		{	return this->ListModules(
							trunk, -1,
							modulesInfo
							);
		}
	TCPSError ListModules(
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo
				) method
		{	return this->ListModules(
							trunk.Get(), trunk.Length(),
							modulesInfo
							);
		}

public:
	TCPSError AddModel(
				IN const PCC_ModelProperty& modelProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) method;
	TCPSError AddModel(
				IN const PCC_ModelProperty& modelProperty,
				IN const PCC_ModelFile* modelFiles, IN INT32 modelFiles_count
				) method
		{	return this->AddModel(
							modelProperty,
							tcps_Array<PCC_ModelFile>(xat_bind, (PCC_ModelFile*)modelFiles, modelFiles_count)
							);
		}

public:
	TCPSError ListModels(
				OUT tcps_Array<PCC_ModelPropWithKey>& modelsInfo
				) method;

public:
	TCPSError DelModel(
				IN INT64 modelKey
				) method;

protected:
	// 返回TCPS_OK允许重定向；返回非TCPS_OK禁止重定向
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{	// TODO: 请在派生类中重载此函数
		(void)redirectIPP; (void)redirectParam;
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 //////
private:
	void* m_base_v_tab_ptr;
	void* m_derived_v_tab_ptr;
	PCC_Deploy_RC* m_faceR;

private:
	struct CallSiteL_
	{
		BOOL needUpdateFlags;
		MethodMatchingFlag matchingFlags;
		PROC fnOnStreamedCall_L_;
		PROC fnLogin;
		PROC fnLogout;
		PROC fnCreateTrunk;
		PROC fnRemoveTrunk;
		PROC fnListTrunk;
		PROC fnAddAuthCenter;
		PROC fnRemoveAuthCenter;
		PROC fnListAuthCenter;
		PROC fnFindAuthCenter;
		PROC fnAddModule;
		PROC fnAddModuleFile;
		PROC fnRemoveModule;
		PROC fnRemoveModuleFiles;
		PROC fnListModules;
		PROC fnAddModel;
		PROC fnListModels;
		PROC fnDelModel;
		CallSiteL_()
			: needUpdateFlags(true)
			, fnOnStreamedCall_L_(NULL)
			, fnLogin(NULL)
			, fnLogout(NULL)
			, fnCreateTrunk(NULL)
			, fnRemoveTrunk(NULL)
			, fnListTrunk(NULL)
			, fnAddAuthCenter(NULL)
			, fnRemoveAuthCenter(NULL)
			, fnListAuthCenter(NULL)
			, fnFindAuthCenter(NULL)
			, fnAddModule(NULL)
			, fnAddModuleFile(NULL)
			, fnRemoveModule(NULL)
			, fnRemoveModuleFiles(NULL)
			, fnListModules(NULL)
			, fnAddModel(NULL)
			, fnListModels(NULL)
			, fnDelModel(NULL)
			{}
		void Reset()
		{
			needUpdateFlags = true;
			matchingFlags.Reset();
			fnOnStreamedCall_L_ = NULL;
			fnLogin = NULL;
			fnLogout = NULL;
			fnCreateTrunk = NULL;
			fnRemoveTrunk = NULL;
			fnListTrunk = NULL;
			fnAddAuthCenter = NULL;
			fnRemoveAuthCenter = NULL;
			fnListAuthCenter = NULL;
			fnFindAuthCenter = NULL;
			fnAddModule = NULL;
			fnAddModuleFile = NULL;
			fnRemoveModule = NULL;
			fnRemoveModuleFiles = NULL;
			fnListModules = NULL;
			fnAddModel = NULL;
			fnListModels = NULL;
			fnDelModel = NULL;
		}
	};
	struct LocalMakingFlag_
	{
		BOOL making;
		BOOL failed;
		LocalMakingFlag_() : making(false), failed(false) {}
	};
	LocalMakingFlag_ m_localMakingFlag;	// 用于本地服务递归调用处理
	IPCC_Deploy_LocalMethod* m_faceL;
	CallSiteL_* m_callSiteL;	// m_faceL!=NULL时有效
	IPP m_localServeIPP;		// m_faceL!=NULL时有效

private:
	OSThreadID m_closingTID;	// 正在关闭会话的用户线程（即正析构Client对象或调用SetServeIPP(NEW_IPP/INVALID_IPP)的线程）

public:
	// 不要使用此函数，仅供框架使用
	OSThreadID GetClosingTID_() const
		{	return m_closingTID;	}

private:
	DWORD m_connectTimeout;
	DWORD m_recvTimeout;
	DWORD m_sendTimeout;
	tcps_SockRecvSendBufParam m_sockRecvSendBufParam;
	iscm_PostingPendingParam m_postingPendingParam;
	iscm_PostingSendParam m_postingSendParam;

private:
	CLocker m_lock;
	BOOL m_streamedCallbackMap_IsInited;
	typedef tcps_QuickStringMap<
				CPtrStrA/*callback_name*/,
				BOOL /*callback_is_matched*/,
				0> StreamedCallbackMap;
	StreamedCallbackMap m_streamedCallbackMap;

public:
	/// 判断流式回调方的回调版本是否匹配（本函数内部会调用this->GetStreamedCallbackTypeInfo_()）
	BOOL IsStreamedCallbackMatched_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/
				);

private:
	TCPSError SetServeIPP_(
				IN BOOL byLocalPeer,
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	void DestroyRequester_(
				IN BOOL byLocalPeer
				);

	void OnNetworkMalformed_();
	virtual void CloseSession_();

	virtual PROC FindCallback_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				);

	static TCPSError OnStreamedCallback_L_(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);
};
#endif // #ifndef PCC_Deploy_defined

#ifndef PCC_User_defined
#define PCC_User_defined
class PCC_User_S;
class PCC_User_RC;
class PCC_User : public IPCC_User_LocalCallback
{
	friend class PCC_User_S;
	friend class PCC_User_RC;
private:
	PCC_User(const PCC_User&);
	PCC_User& operator= (const PCC_User&);

	typedef PCC_User* PPCC_User_;

public:
	// initNetworkSingletons，是否初始化网络相关单件（若只用于连接进程内服务，可传false）
	explicit PCC_User(BOOL initNetworkSingletons = true);
	virtual ~PCC_User();

protected:
	// 析构RPC请求对象
	// 注意：若有派生类，必须且只能在派生类的析构函数的最后调用，
	//		 以保证派生类对象继承的通知虚函数总被正确调用。
	void DestroyRequester();

	// 连接后通知虚函数
	// 若返回失败，则立即触发OnClose()，且继续异步尝试连接
	// TODO: 若需处理连接动作，请在派生类中重载OnConnected()
	virtual TCPSError OnConnected()
		{	return TCPS_OK;	}

	// 对端断线通知虚函数（在OnClose()之前被调用）
	// 注: 只有对端关闭或网络断线才会触发，Client对象被析构或设置INVALID_IPP不会触发
	// TODO: 若需处理此动作，请在派生类中重载OnPeerBroken()
	virtual void OnPeerBroken()
		{	}

	// 连接关闭通知虚函数（在OnPeerBroken()之后被调用）
	// 注: 所有关闭情况都会触发
	// TODO: 若需处理关闭动作，请在派生类中重载OnClose()
	virtual void OnClose()
		{	}

	// 连接超时通知虚函数
	// TODO: 若需处理连接超时动作，请在派生类中重载OnConnectTimeout()
	virtual void OnConnectTimeout(IN TCPSError cause)
		{	(void)cause;	}

public:
	// 设置正向服务参数
	// @serveIPP[in] 第一备选服务器IPP，INVALID_IPP表示取消连接
	// @sessionFlags[in] 会话标志，为以下值的位组合
	//		ISCMC_NO_CALLBACK、ISCMC_ASYNC_CONNECT、ISCMC_UDP_POSTING、ISCMC_NO_ASYNC_RECONNECT、ISCMC_NO_POSTING_CHANNEL
	// @clientID_IPP[in] 客户端标识IPP，INVALID_IPP使用自动值（标识端口使用0）
	// @secondaryServeIPP[in] 第二备选服务IPP（取消连接时本参数被忽略）
	// @tertiaryServeIPP[in] 第三备选服务IPP（取消连接时本参数被忽略）
	// @reconnectIntervalMSELs[in] 网络重建间隔时间
	TCPSError SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	IPP GetServeIPP() const;
	IPP GetServingIPP() const;
	BOOL IsConnected() const;

	// 设置连接保持标志
	//		注：调用SetServeIPP()时，若指定了ISCMC_NO_ASYNC_RECONNECT，
	//			则连接保持标志为false；否则为true
	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	// 对端是否为进程内服务
	BOOL IsLocalPeer() const;

	// 准备断开网络，在有巨量会话对象需要关闭网络时，先批量调用一次PrepareDisconnect()，
	// 调用PrepareDisconnect()后，再调用SetServeIPP(INVALID_IPP)，或析构接口对象
	void PrepareDisconnect();

	// 设置网络超时，INFINITE表示使用默认值（网络对端也会被设置）
	void SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	void GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const;

	// 设置同步调用网络缓冲大小，<0表示不改变此项，==0表示恢复默认值（网络对端也会被设置）
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
	// @maxSendingBytes[in] 最大缓冲大小（字节，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_SEND_BUFFER_SIZE）
	// @maxSendings[in] 最大缓冲调用数量（个，<0表示不改变此项，==0表示恢复默认值，默认ISCM_POSTING_MAX_SENDINGS）
	void SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// 清理客户端对象的posting方法发送队列
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_User_* clients,
				IN INT_PTR clientsCount
				);

	// 方法匹配检查支持
public:
	struct MethodMatchingFlag
	{
		struct Info
		{
			BOOL* pMatchingVar;
			BOOL isPosting;
			Info(BOOL* p, BOOL is) : pMatchingVar(p), isPosting(is) {}
		};
		typedef tcps_QuickStringMap<CPtrStrA, Info, 11> MethodMap;
		MethodMap mmap_;
		BOOL matching_GetPccProperty;
		BOOL matching_ListNodes;
		BOOL matching_GetNodeDynamicContext;
		BOOL matching_ListModules;
		BOOL matching_Execute;
		BOOL matching_QueryJobs;
		BOOL matching_CancelJob;
		BOOL matching_UDPLink_;
		BOOL matching_UDPLinkConfirm_;
		BOOL matching_SetTimeout_;
		BOOL matching_SetSessionBufferSize_;
		void Reset();
		MethodMatchingFlag();
	};
public:
	// 获取本地与对端方法匹配信息
	const MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// 下面流式调用定义仅用于非C++语言的辅助实现
public:
	TCPSError GetStreamedMethodTypeInfo_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo /*= NULL*/,
				OUT INT_PTR& infoLen /*= 0*/
				) const;

	virtual TCPSError GetStreamedCallbackTypeInfo_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo /*= NULL*/,
				OUT INT_PTR& infoLen /*= 0*/
				)
	{	// TODO: 请在派生类中重载此函数
		(void)callbackName; (void)nameLen;
		(void)typeInfo; (void)infoLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

	/// 流式方法调用
	/// @methodName[in] 方法名，必须提供
	/// @nameLen[in] 方法名长度，-1表示方法名是一'\0'结束符字符串
	/// @data[in] 方法参数数据（dataLen==0时可以为NULL）
	/// @dataLen[in] 方法参数数据长度（>=0）
	/// @replyData[out] 返回OUT型参数数据（无OUT参数的方法可以传NULL）
	///			注：若*replyData返回非NULL，则必须使用tcps_Free()释放
	/// @replyLen[out] 返回OUT型参数数据长度（无OUT参数的方法可以传NULL）
	/// @return TCPSError
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	/// 流式回调调用通知（在调用普通的回调函数之前被调用）
	/// @callbackName[in] 回调名，必须提供
	///		注：callbackName==NULL时，用于检测StreamedCallback_()是否被派生，
	///			派生类的StreamedCallback_()中，最前面总这样实现：
	///			{
	///				if(NULL == callbackName)
	///					return TCPS_ERR_INVALID_PARAM; // 必须返回非TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED
	///				...
	///			}
	/// @nameLen[in] 回调名长度，-1表示回调名为'\0'结束符字符串
	/// @data[in] 回调IN型参数数据（dataLen==0时可能为NULL）
	/// @dataLen[in] 回调IN型参数数据长度（>=0）
	/// @replyData[out] 返回OUT型参数数据，传入时已置为NULL，
	///			若返回非NULL，则必须使用tcps_Alloc()申请内存；无OUT参数的回调时可返回NULL
	/// @replyLen[out] 返回OUT型参数数据长度，传入时已置为0
	/// @return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED表示忽略此次流式回调调用，
	///			框架若收到此返回值，则会继续调用普通的回调函数；
	///			其它值，直接返回给服务器端。
	///			<<<注：若遇到IN型参数数据无法被正确解析，应该返回TCPS_ERR_MALFORMED_REQ>>>
	virtual TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT void*& replyData /*= NULL*/,
				OUT INT_PTR& replyLen /*= 0*/
				)
	{	// TODO: 请在派生类中重载此函数
		(void)callbackName; (void)nameLen;
		(void)data; (void)dataLen;
		(void)replyData; (void)replyLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

public:
	TCPSError GetPccProperty(
				OUT PCCProperty& pccProp
				) method;

public:
	TCPSError ListNodes(
				OUT tcps_Array<PCC_NodeDesc>& nodes
				) method;

public:
	TCPSError GetNodeDynamicContext(
				IN const char* nodeName, IN INT32 nodeName_len /*= -1*/,
				OUT PCC_DynamicContext& dynamicContext
				) method;
	TCPSError GetNodeDynamicContext(
				IN const char* nodeName,
				OUT PCC_DynamicContext& dynamicContext
				) method
		{	return this->GetNodeDynamicContext(
							nodeName, -1,
							dynamicContext
							);
		}
	TCPSError GetNodeDynamicContext(
				IN const tcps_String& nodeName,
				OUT PCC_DynamicContext& dynamicContext
				) method
		{	return this->GetNodeDynamicContext(
							nodeName.Get(), nodeName.Length(),
							dynamicContext
							);
		}

public:
	TCPSError ListModules(
				IN const char* regex, IN INT32 regex_len /*= -1*/,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method;
	TCPSError ListModules(
				IN const char* regex,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method
		{	return this->ListModules(
							regex, -1,
							modulesInfo
							);
		}
	TCPSError ListModules(
				IN const tcps_String& regex,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method
		{	return this->ListModules(
							regex.Get(), regex.Length(),
							modulesInfo
							);
		}

public:
	TCPSError Execute(
				IN INT64 moduleKey,
				IN const char* inputUrl, IN INT32 inputUrl_len /*= -1*/,
				IN const char* outputUrl, IN INT32 outputUrl_len /*= -1*/,
				IN const void* moduleParams, IN INT32 moduleParams_len,
				OUT INT64& jobKey
				) method;
	TCPSError Execute(
				IN INT64 moduleKey,
				IN const char* inputUrl,
				IN const char* outputUrl,
				IN const void* moduleParams, IN INT32 moduleParams_len,
				OUT INT64& jobKey
				) method
		{	return this->Execute(
							moduleKey,
							inputUrl, -1,
							outputUrl, -1,
							moduleParams, moduleParams_len,
							jobKey
							);
		}
	TCPSError Execute(
				IN INT64 moduleKey,
				IN const tcps_String& inputUrl,
				IN const tcps_String& outputUrl,
				IN const tcps_Binary& moduleParams,
				OUT INT64& jobKey
				) method
		{	return this->Execute(
							moduleKey,
							inputUrl.Get(), inputUrl.Length(),
							outputUrl.Get(), outputUrl.Length(),
							moduleParams.Get(), moduleParams.Length(),
							jobKey
							);
		}

protected:
	virtual TCPSError OnExecuted(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context
				) posting_callback
	{	// TODO: 请在派生类中重载此函数
		(void)jobKey; (void)errorCode; (void)context;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError OnExecuted1(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context,
				IN const tcps_Array<tcps_Binary>& outArgs
				) posting_callback
	{	// TODO: 请在派生类中重载此函数
		(void)jobKey; (void)errorCode; (void)context; (void)outArgs;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

public:
	TCPSError QueryJobs(
				IN const tcps_Array<INT64>& jobsKey,
				OUT tcps_Array<ExecuteState>& jobsState
				) method;
	TCPSError QueryJobs(
				IN const INT64* jobsKey, IN INT32 jobsKey_count,
				OUT tcps_Array<ExecuteState>& jobsState
				) method
		{	return this->QueryJobs(
							tcps_Array<INT64>(xat_bind, (INT64*)jobsKey, jobsKey_count),
							jobsState
							);
		}

public:
	TCPSError CancelJob(
				IN INT64 jobKey
				) posting_method;

public:
	static TCPSError CancelJob_Batch(
				IN const PPCC_User_* clients,
				IN INT_PTR clientsCount,
				IN INT64 jobKey,
				OUT PPCC_User_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_method;

protected:
	// 返回TCPS_OK允许重定向；返回非TCPS_OK禁止重定向
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{	// TODO: 请在派生类中重载此函数
		(void)redirectIPP; (void)redirectParam;
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 //////
private:
	void* m_base_v_tab_ptr;
	void* m_derived_v_tab_ptr;
	PCC_User_RC* m_faceR;

private:
	struct CallSiteL_
	{
		BOOL needUpdateFlags;
		MethodMatchingFlag matchingFlags;
		PROC fnOnStreamedCall_L_;
		PROC fnGetPccProperty;
		PROC fnListNodes;
		PROC fnGetNodeDynamicContext;
		PROC fnListModules;
		PROC fnExecute;
		PROC fnQueryJobs;
		PROC fnCancelJob;
		CallSiteL_()
			: needUpdateFlags(true)
			, fnOnStreamedCall_L_(NULL)
			, fnGetPccProperty(NULL)
			, fnListNodes(NULL)
			, fnGetNodeDynamicContext(NULL)
			, fnListModules(NULL)
			, fnExecute(NULL)
			, fnQueryJobs(NULL)
			, fnCancelJob(NULL)
			{}
		void Reset()
		{
			needUpdateFlags = true;
			matchingFlags.Reset();
			fnOnStreamedCall_L_ = NULL;
			fnGetPccProperty = NULL;
			fnListNodes = NULL;
			fnGetNodeDynamicContext = NULL;
			fnListModules = NULL;
			fnExecute = NULL;
			fnQueryJobs = NULL;
			fnCancelJob = NULL;
		}
	};
	struct LocalMakingFlag_
	{
		BOOL making;
		BOOL failed;
		LocalMakingFlag_() : making(false), failed(false) {}
	};
	LocalMakingFlag_ m_localMakingFlag;	// 用于本地服务递归调用处理
	IPCC_User_LocalMethod* m_faceL;
	CallSiteL_* m_callSiteL;	// m_faceL!=NULL时有效
	IPP m_localServeIPP;		// m_faceL!=NULL时有效

private:
	OSThreadID m_closingTID;	// 正在关闭会话的用户线程（即正析构Client对象或调用SetServeIPP(NEW_IPP/INVALID_IPP)的线程）

public:
	// 不要使用此函数，仅供框架使用
	OSThreadID GetClosingTID_() const
		{	return m_closingTID;	}

private:
	DWORD m_connectTimeout;
	DWORD m_recvTimeout;
	DWORD m_sendTimeout;
	tcps_SockRecvSendBufParam m_sockRecvSendBufParam;
	iscm_PostingPendingParam m_postingPendingParam;
	iscm_PostingSendParam m_postingSendParam;

private:
	CLocker m_lock;
	BOOL m_streamedCallbackMap_IsInited;
	typedef tcps_QuickStringMap<
				CPtrStrA/*callback_name*/,
				BOOL /*callback_is_matched*/,
				2> StreamedCallbackMap;
	StreamedCallbackMap m_streamedCallbackMap;

public:
	/// 判断流式回调方的回调版本是否匹配（本函数内部会调用this->GetStreamedCallbackTypeInfo_()）
	BOOL IsStreamedCallbackMatched_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/
				);

private:
	TCPSError SetServeIPP_(
				IN BOOL byLocalPeer,
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	void DestroyRequester_(
				IN BOOL byLocalPeer
				);

	void OnNetworkMalformed_();
	virtual void CloseSession_();

	virtual PROC FindCallback_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				);

	static TCPSError OnStreamedCallback_L_(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	static TCPSError Local_OnExecuted(
				IN void* sessionObj_wrap,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context
				) posting_callback;

	static TCPSError Local_OnExecuted1(
				IN void* sessionObj_wrap,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context,
				IN const tcps_Array<tcps_Binary>& outArgs
				) posting_callback;
};
#endif // #ifndef PCC_User_defined

//[[end_iscm]]

#endif	// #ifndef _PCC_CenterClient_h_
