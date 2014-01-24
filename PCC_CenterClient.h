// PCC_CenterClient.h
//
// ע��: ���ļ�Ϊ�������ɣ��벻Ҫ�޸�

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
	// initNetworkSingletons���Ƿ��ʼ��������ص�������ֻ�������ӽ����ڷ��񣬿ɴ�false��
	explicit PCC_Center(BOOL initNetworkSingletons = true);
	virtual ~PCC_Center();

protected:
	// ����RPC�������
	// ע�⣺���������࣬������ֻ��������������������������ã�
	//		 �Ա�֤���������̳е�֪ͨ�麯���ܱ���ȷ���á�
	void DestroyRequester();

	// ���Ӻ�֪ͨ�麯��
	// ������ʧ�ܣ�����������OnClose()���Ҽ����첽��������
	// TODO: ���账�����Ӷ���������������������OnConnected()
	virtual TCPSError OnConnected()
		{	return TCPS_OK;	}

	// �Զ˶���֪ͨ�麯������OnClose()֮ǰ�����ã�
	// ע: ֻ�жԶ˹رջ�������߲Żᴥ����Client��������������INVALID_IPP���ᴥ��
	// TODO: ���账��˶���������������������OnPeerBroken()
	virtual void OnPeerBroken()
		{	}

	// ���ӹر�֪ͨ�麯������OnPeerBroken()֮�󱻵��ã�
	// ע: ���йر�������ᴥ��
	// TODO: ���账��رն���������������������OnClose()
	virtual void OnClose()
		{	}

	// ���ӳ�ʱ֪ͨ�麯��
	// TODO: ���账�����ӳ�ʱ����������������������OnConnectTimeout()
	virtual void OnConnectTimeout(IN TCPSError cause)
		{	(void)cause;	}

public:
	// ��������������
	// @serveIPP[in] ��һ��ѡ������IPP��INVALID_IPP��ʾȡ������
	// @sessionFlags[in] �Ự��־��Ϊ����ֵ��λ���
	//		ISCMC_NO_CALLBACK��ISCMC_ASYNC_CONNECT��ISCMC_UDP_POSTING��ISCMC_NO_ASYNC_RECONNECT��ISCMC_NO_POSTING_CHANNEL
	// @clientID_IPP[in] �ͻ��˱�ʶIPP��INVALID_IPPʹ���Զ�ֵ����ʶ�˿�ʹ��0��
	// @secondaryServeIPP[in] �ڶ���ѡ����IPP��ȡ������ʱ�����������ԣ�
	// @tertiaryServeIPP[in] ������ѡ����IPP��ȡ������ʱ�����������ԣ�
	// @reconnectIntervalMSELs[in] �����ؽ����ʱ��
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

	// �������ӱ��ֱ�־
	//		ע������SetServeIPP()ʱ����ָ����ISCMC_NO_ASYNC_RECONNECT��
	//			�����ӱ��ֱ�־Ϊfalse������Ϊtrue
	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	// �Զ��Ƿ�Ϊ�����ڷ���
	BOOL IsLocalPeer() const;

	// ׼���Ͽ����磬���о����Ự������Ҫ�ر�����ʱ������������һ��PrepareDisconnect()��
	// ����PrepareDisconnect()���ٵ���SetServeIPP(INVALID_IPP)���������ӿڶ���
	void PrepareDisconnect();

	// �������糬ʱ��INFINITE��ʾʹ��Ĭ��ֵ������Զ�Ҳ�ᱻ���ã�
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

	// ����ͬ���������绺���С��<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ������Զ�Ҳ�ᱻ���ã�
	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	// ����postingִ�ж˲���
	// @maxPendingBytes[in] ��󻺳��С���ֽڣ�<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_PENDING_BUFFER_SIZE��
	// @maxPendings[in] ��󻺳��������������<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_MAX_PENDINGS��
	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

	// ����posting���ö˲���
	// @maxSendingBytes[in] ��󻺳��С���ֽڣ�<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_SEND_BUFFER_SIZE��
	// @maxSendings[in] ��󻺳��������������<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_MAX_SENDINGS��
	void SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// ����ͻ��˶����posting�������Ͷ���
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_Center_* clients,
				IN INT_PTR clientsCount
				);

	// ����ƥ����֧��
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
	// ��ȡ������Զ˷���ƥ����Ϣ
	const MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// ������ʽ���ö�������ڷ�C++���Եĸ���ʵ��
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
	{	// TODO: ���������������ش˺���
		(void)callbackName; (void)nameLen;
		(void)typeInfo; (void)infoLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

	/// ��ʽ��������
	/// @methodName[in] �������������ṩ
	/// @nameLen[in] ���������ȣ�-1��ʾ��������һ'\0'�������ַ���
	/// @data[in] �����������ݣ�dataLen==0ʱ����ΪNULL��
	/// @dataLen[in] �����������ݳ��ȣ�>=0��
	/// @replyData[out] ����OUT�Ͳ������ݣ���OUT�����ķ������Դ�NULL��
	///			ע����*replyData���ط�NULL�������ʹ��tcps_Free()�ͷ�
	/// @replyLen[out] ����OUT�Ͳ������ݳ��ȣ���OUT�����ķ������Դ�NULL��
	/// @return TCPSError
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	/// ��ʽ�ص�����֪ͨ���ڵ�����ͨ�Ļص�����֮ǰ�����ã�
	/// @callbackName[in] �ص����������ṩ
	///		ע��callbackName==NULLʱ�����ڼ��StreamedCallback_()�Ƿ�������
	///			�������StreamedCallback_()�У���ǰ��������ʵ�֣�
	///			{
	///				if(NULL == callbackName)
	///					return TCPS_ERR_INVALID_PARAM; // ���뷵�ط�TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED
	///				...
	///			}
	/// @nameLen[in] �ص������ȣ�-1��ʾ�ص���Ϊ'\0'�������ַ���
	/// @data[in] �ص�IN�Ͳ������ݣ�dataLen==0ʱ����ΪNULL��
	/// @dataLen[in] �ص�IN�Ͳ������ݳ��ȣ�>=0��
	/// @replyData[out] ����OUT�Ͳ������ݣ�����ʱ����ΪNULL��
	///			�����ط�NULL�������ʹ��tcps_Alloc()�����ڴ棻��OUT�����Ļص�ʱ�ɷ���NULL
	/// @replyLen[out] ����OUT�Ͳ������ݳ��ȣ�����ʱ����Ϊ0
	/// @return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED��ʾ���Դ˴���ʽ�ص����ã�
	///			������յ��˷���ֵ��������������ͨ�Ļص�������
	///			����ֵ��ֱ�ӷ��ظ��������ˡ�
	///			<<<ע��������IN�Ͳ��������޷�����ȷ������Ӧ�÷���TCPS_ERR_MALFORMED_REQ>>>
	virtual TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT void*& replyData /*= NULL*/,
				OUT INT_PTR& replyLen /*= 0*/
				)
	{	// TODO: ���������������ش˺���
		(void)callbackName; (void)nameLen;
		(void)data; (void)dataLen;
		(void)replyData; (void)replyLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError AddModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{	// TODO: ���������������ش˺���
		(void)centerIPP;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError DelModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{	// TODO: ���������������ش˺���
		(void)centerIPP;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError GetStaticContext(
				OUT PCC_NodeDesc& staticContext
				) cacheable_callback
	{	// TODO: ���������������ش˺���
		(void)staticContext;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError GetDynamicContext(
				OUT PCC_DynamicContext& dynamicContext
				) callback
	{	// TODO: ���������������ش˺���
		(void)dynamicContext;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError AddModel(
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback
	{	// TODO: ���������������ش˺���
		(void)moduleProperty; (void)modelFiles;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError DelModel(
				IN const PCC_Tag& tag
				) callback
	{	// TODO: ���������������ش˺���
		(void)tag;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	// ����TCPS_OK�����ض��򣻷��ط�TCPS_OK��ֹ�ض���
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{	// TODO: ���������������ش˺���
		(void)redirectIPP; (void)redirectParam;
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// �ڴ�֮��Ĵ���ʹ����������ģ�ΪISCM���ʵ�ִ��� //////
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
	LocalMakingFlag_ m_localMakingFlag;	// ���ڱ��ط���ݹ���ô���
	IPCC_Center_LocalMethod* m_faceL;
	CallSiteL_* m_callSiteL;	// m_faceL!=NULLʱ��Ч
	IPP m_localServeIPP;		// m_faceL!=NULLʱ��Ч

private:
	OSThreadID m_closingTID;	// ���ڹرջỰ���û��̣߳���������Client��������SetServeIPP(NEW_IPP/INVALID_IPP)���̣߳�

public:
	// ��Ҫʹ�ô˺������������ʹ��
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
	/// �ж���ʽ�ص����Ļص��汾�Ƿ�ƥ�䣨�������ڲ������this->GetStreamedCallbackTypeInfo_()��
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
	// initNetworkSingletons���Ƿ��ʼ��������ص�������ֻ�������ӽ����ڷ��񣬿ɴ�false��
	explicit PCC_Deploy(BOOL initNetworkSingletons = true);
	virtual ~PCC_Deploy();

protected:
	// ����RPC�������
	// ע�⣺���������࣬������ֻ��������������������������ã�
	//		 �Ա�֤���������̳е�֪ͨ�麯���ܱ���ȷ���á�
	void DestroyRequester();

	// ���Ӻ�֪ͨ�麯��
	// ������ʧ�ܣ�����������OnClose()���Ҽ����첽��������
	// TODO: ���账�����Ӷ���������������������OnConnected()
	virtual TCPSError OnConnected()
		{	return TCPS_OK;	}

	// �Զ˶���֪ͨ�麯������OnClose()֮ǰ�����ã�
	// ע: ֻ�жԶ˹رջ�������߲Żᴥ����Client��������������INVALID_IPP���ᴥ��
	// TODO: ���账��˶���������������������OnPeerBroken()
	virtual void OnPeerBroken()
		{	}

	// ���ӹر�֪ͨ�麯������OnPeerBroken()֮�󱻵��ã�
	// ע: ���йر�������ᴥ��
	// TODO: ���账��رն���������������������OnClose()
	virtual void OnClose()
		{	}

	// ���ӳ�ʱ֪ͨ�麯��
	// TODO: ���账�����ӳ�ʱ����������������������OnConnectTimeout()
	virtual void OnConnectTimeout(IN TCPSError cause)
		{	(void)cause;	}

public:
	// ��������������
	// @serveIPP[in] ��һ��ѡ������IPP��INVALID_IPP��ʾȡ������
	// @sessionFlags[in] �Ự��־��Ϊ����ֵ��λ���
	//		ISCMC_NO_CALLBACK��ISCMC_ASYNC_CONNECT��ISCMC_UDP_POSTING��ISCMC_NO_ASYNC_RECONNECT��ISCMC_NO_POSTING_CHANNEL
	// @clientID_IPP[in] �ͻ��˱�ʶIPP��INVALID_IPPʹ���Զ�ֵ����ʶ�˿�ʹ��0��
	// @secondaryServeIPP[in] �ڶ���ѡ����IPP��ȡ������ʱ�����������ԣ�
	// @tertiaryServeIPP[in] ������ѡ����IPP��ȡ������ʱ�����������ԣ�
	// @reconnectIntervalMSELs[in] �����ؽ����ʱ��
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

	// �������ӱ��ֱ�־
	//		ע������SetServeIPP()ʱ����ָ����ISCMC_NO_ASYNC_RECONNECT��
	//			�����ӱ��ֱ�־Ϊfalse������Ϊtrue
	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	// �Զ��Ƿ�Ϊ�����ڷ���
	BOOL IsLocalPeer() const;

	// ׼���Ͽ����磬���о����Ự������Ҫ�ر�����ʱ������������һ��PrepareDisconnect()��
	// ����PrepareDisconnect()���ٵ���SetServeIPP(INVALID_IPP)���������ӿڶ���
	void PrepareDisconnect();

	// �������糬ʱ��INFINITE��ʾʹ��Ĭ��ֵ������Զ�Ҳ�ᱻ���ã�
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

	// ����ͬ���������绺���С��<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ������Զ�Ҳ�ᱻ���ã�
	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	// ����postingִ�ж˲���
	// @maxPendingBytes[in] ��󻺳��С���ֽڣ�<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_PENDING_BUFFER_SIZE��
	// @maxPendings[in] ��󻺳��������������<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_MAX_PENDINGS��
	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

	// ����posting���ö˲���
	// @maxSendingBytes[in] ��󻺳��С���ֽڣ�<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_SEND_BUFFER_SIZE��
	// @maxSendings[in] ��󻺳��������������<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_MAX_SENDINGS��
	void SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// ����ͻ��˶����posting�������Ͷ���
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_Deploy_* clients,
				IN INT_PTR clientsCount
				);

	// ����ƥ����֧��
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
	// ��ȡ������Զ˷���ƥ����Ϣ
	const MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// ������ʽ���ö�������ڷ�C++���Եĸ���ʵ��
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
	{	// TODO: ���������������ش˺���
		(void)callbackName; (void)nameLen;
		(void)typeInfo; (void)infoLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

	/// ��ʽ��������
	/// @methodName[in] �������������ṩ
	/// @nameLen[in] ���������ȣ�-1��ʾ��������һ'\0'�������ַ���
	/// @data[in] �����������ݣ�dataLen==0ʱ����ΪNULL��
	/// @dataLen[in] �����������ݳ��ȣ�>=0��
	/// @replyData[out] ����OUT�Ͳ������ݣ���OUT�����ķ������Դ�NULL��
	///			ע����*replyData���ط�NULL�������ʹ��tcps_Free()�ͷ�
	/// @replyLen[out] ����OUT�Ͳ������ݳ��ȣ���OUT�����ķ������Դ�NULL��
	/// @return TCPSError
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	/// ��ʽ�ص�����֪ͨ���ڵ�����ͨ�Ļص�����֮ǰ�����ã�
	/// @callbackName[in] �ص����������ṩ
	///		ע��callbackName==NULLʱ�����ڼ��StreamedCallback_()�Ƿ�������
	///			�������StreamedCallback_()�У���ǰ��������ʵ�֣�
	///			{
	///				if(NULL == callbackName)
	///					return TCPS_ERR_INVALID_PARAM; // ���뷵�ط�TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED
	///				...
	///			}
	/// @nameLen[in] �ص������ȣ�-1��ʾ�ص���Ϊ'\0'�������ַ���
	/// @data[in] �ص�IN�Ͳ������ݣ�dataLen==0ʱ����ΪNULL��
	/// @dataLen[in] �ص�IN�Ͳ������ݳ��ȣ�>=0��
	/// @replyData[out] ����OUT�Ͳ������ݣ�����ʱ����ΪNULL��
	///			�����ط�NULL�������ʹ��tcps_Alloc()�����ڴ棻��OUT�����Ļص�ʱ�ɷ���NULL
	/// @replyLen[out] ����OUT�Ͳ������ݳ��ȣ�����ʱ����Ϊ0
	/// @return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED��ʾ���Դ˴���ʽ�ص����ã�
	///			������յ��˷���ֵ��������������ͨ�Ļص�������
	///			����ֵ��ֱ�ӷ��ظ��������ˡ�
	///			<<<ע��������IN�Ͳ��������޷�����ȷ������Ӧ�÷���TCPS_ERR_MALFORMED_REQ>>>
	virtual TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT void*& replyData /*= NULL*/,
				OUT INT_PTR& replyLen /*= 0*/
				)
	{	// TODO: ���������������ش˺���
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
	// ����TCPS_OK�����ض��򣻷��ط�TCPS_OK��ֹ�ض���
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{	// TODO: ���������������ش˺���
		(void)redirectIPP; (void)redirectParam;
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// �ڴ�֮��Ĵ���ʹ����������ģ�ΪISCM���ʵ�ִ��� //////
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
	LocalMakingFlag_ m_localMakingFlag;	// ���ڱ��ط���ݹ���ô���
	IPCC_Deploy_LocalMethod* m_faceL;
	CallSiteL_* m_callSiteL;	// m_faceL!=NULLʱ��Ч
	IPP m_localServeIPP;		// m_faceL!=NULLʱ��Ч

private:
	OSThreadID m_closingTID;	// ���ڹرջỰ���û��̣߳���������Client��������SetServeIPP(NEW_IPP/INVALID_IPP)���̣߳�

public:
	// ��Ҫʹ�ô˺������������ʹ��
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
	/// �ж���ʽ�ص����Ļص��汾�Ƿ�ƥ�䣨�������ڲ������this->GetStreamedCallbackTypeInfo_()��
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
	// initNetworkSingletons���Ƿ��ʼ��������ص�������ֻ�������ӽ����ڷ��񣬿ɴ�false��
	explicit PCC_User(BOOL initNetworkSingletons = true);
	virtual ~PCC_User();

protected:
	// ����RPC�������
	// ע�⣺���������࣬������ֻ��������������������������ã�
	//		 �Ա�֤���������̳е�֪ͨ�麯���ܱ���ȷ���á�
	void DestroyRequester();

	// ���Ӻ�֪ͨ�麯��
	// ������ʧ�ܣ�����������OnClose()���Ҽ����첽��������
	// TODO: ���账�����Ӷ���������������������OnConnected()
	virtual TCPSError OnConnected()
		{	return TCPS_OK;	}

	// �Զ˶���֪ͨ�麯������OnClose()֮ǰ�����ã�
	// ע: ֻ�жԶ˹رջ�������߲Żᴥ����Client��������������INVALID_IPP���ᴥ��
	// TODO: ���账��˶���������������������OnPeerBroken()
	virtual void OnPeerBroken()
		{	}

	// ���ӹر�֪ͨ�麯������OnPeerBroken()֮�󱻵��ã�
	// ע: ���йر�������ᴥ��
	// TODO: ���账��رն���������������������OnClose()
	virtual void OnClose()
		{	}

	// ���ӳ�ʱ֪ͨ�麯��
	// TODO: ���账�����ӳ�ʱ����������������������OnConnectTimeout()
	virtual void OnConnectTimeout(IN TCPSError cause)
		{	(void)cause;	}

public:
	// ��������������
	// @serveIPP[in] ��һ��ѡ������IPP��INVALID_IPP��ʾȡ������
	// @sessionFlags[in] �Ự��־��Ϊ����ֵ��λ���
	//		ISCMC_NO_CALLBACK��ISCMC_ASYNC_CONNECT��ISCMC_UDP_POSTING��ISCMC_NO_ASYNC_RECONNECT��ISCMC_NO_POSTING_CHANNEL
	// @clientID_IPP[in] �ͻ��˱�ʶIPP��INVALID_IPPʹ���Զ�ֵ����ʶ�˿�ʹ��0��
	// @secondaryServeIPP[in] �ڶ���ѡ����IPP��ȡ������ʱ�����������ԣ�
	// @tertiaryServeIPP[in] ������ѡ����IPP��ȡ������ʱ�����������ԣ�
	// @reconnectIntervalMSELs[in] �����ؽ����ʱ��
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

	// �������ӱ��ֱ�־
	//		ע������SetServeIPP()ʱ����ָ����ISCMC_NO_ASYNC_RECONNECT��
	//			�����ӱ��ֱ�־Ϊfalse������Ϊtrue
	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	// �Զ��Ƿ�Ϊ�����ڷ���
	BOOL IsLocalPeer() const;

	// ׼���Ͽ����磬���о����Ự������Ҫ�ر�����ʱ������������һ��PrepareDisconnect()��
	// ����PrepareDisconnect()���ٵ���SetServeIPP(INVALID_IPP)���������ӿڶ���
	void PrepareDisconnect();

	// �������糬ʱ��INFINITE��ʾʹ��Ĭ��ֵ������Զ�Ҳ�ᱻ���ã�
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

	// ����ͬ���������绺���С��<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ������Զ�Ҳ�ᱻ���ã�
	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	// ����postingִ�ж˲���
	// @maxPendingBytes[in] ��󻺳��С���ֽڣ�<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_PENDING_BUFFER_SIZE��
	// @maxPendings[in] ��󻺳��������������<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_MAX_PENDINGS��
	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

	// ����posting���ö˲���
	// @maxSendingBytes[in] ��󻺳��С���ֽڣ�<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_SEND_BUFFER_SIZE��
	// @maxSendings[in] ��󻺳��������������<0��ʾ���ı���==0��ʾ�ָ�Ĭ��ֵ��Ĭ��ISCM_POSTING_MAX_SENDINGS��
	void SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				);
	void GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const;

	// ����ͻ��˶����posting�������Ͷ���
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PPCC_User_* clients,
				IN INT_PTR clientsCount
				);

	// ����ƥ����֧��
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
	// ��ȡ������Զ˷���ƥ����Ϣ
	const MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

	// ������ʽ���ö�������ڷ�C++���Եĸ���ʵ��
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
	{	// TODO: ���������������ش˺���
		(void)callbackName; (void)nameLen;
		(void)typeInfo; (void)infoLen;
		return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	}

	/// ��ʽ��������
	/// @methodName[in] �������������ṩ
	/// @nameLen[in] ���������ȣ�-1��ʾ��������һ'\0'�������ַ���
	/// @data[in] �����������ݣ�dataLen==0ʱ����ΪNULL��
	/// @dataLen[in] �����������ݳ��ȣ�>=0��
	/// @replyData[out] ����OUT�Ͳ������ݣ���OUT�����ķ������Դ�NULL��
	///			ע����*replyData���ط�NULL�������ʹ��tcps_Free()�ͷ�
	/// @replyLen[out] ����OUT�Ͳ������ݳ��ȣ���OUT�����ķ������Դ�NULL��
	/// @return TCPSError
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	/// ��ʽ�ص�����֪ͨ���ڵ�����ͨ�Ļص�����֮ǰ�����ã�
	/// @callbackName[in] �ص����������ṩ
	///		ע��callbackName==NULLʱ�����ڼ��StreamedCallback_()�Ƿ�������
	///			�������StreamedCallback_()�У���ǰ��������ʵ�֣�
	///			{
	///				if(NULL == callbackName)
	///					return TCPS_ERR_INVALID_PARAM; // ���뷵�ط�TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED
	///				...
	///			}
	/// @nameLen[in] �ص������ȣ�-1��ʾ�ص���Ϊ'\0'�������ַ���
	/// @data[in] �ص�IN�Ͳ������ݣ�dataLen==0ʱ����ΪNULL��
	/// @dataLen[in] �ص�IN�Ͳ������ݳ��ȣ�>=0��
	/// @replyData[out] ����OUT�Ͳ������ݣ�����ʱ����ΪNULL��
	///			�����ط�NULL�������ʹ��tcps_Alloc()�����ڴ棻��OUT�����Ļص�ʱ�ɷ���NULL
	/// @replyLen[out] ����OUT�Ͳ������ݳ��ȣ�����ʱ����Ϊ0
	/// @return TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED��ʾ���Դ˴���ʽ�ص����ã�
	///			������յ��˷���ֵ��������������ͨ�Ļص�������
	///			����ֵ��ֱ�ӷ��ظ��������ˡ�
	///			<<<ע��������IN�Ͳ��������޷�����ȷ������Ӧ�÷���TCPS_ERR_MALFORMED_REQ>>>
	virtual TCPSError StreamedCallback_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT void*& replyData /*= NULL*/,
				OUT INT_PTR& replyLen /*= 0*/
				)
	{	// TODO: ���������������ش˺���
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
	{	// TODO: ���������������ش˺���
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
	{	// TODO: ���������������ش˺���
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
	// ����TCPS_OK�����ض��򣻷��ط�TCPS_OK��ֹ�ض���
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{	// TODO: ���������������ش˺���
		(void)redirectIPP; (void)redirectParam;
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// �ڴ�֮��Ĵ���ʹ����������ģ�ΪISCM���ʵ�ִ��� //////
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
	LocalMakingFlag_ m_localMakingFlag;	// ���ڱ��ط���ݹ���ô���
	IPCC_User_LocalMethod* m_faceL;
	CallSiteL_* m_callSiteL;	// m_faceL!=NULLʱ��Ч
	IPP m_localServeIPP;		// m_faceL!=NULLʱ��Ч

private:
	OSThreadID m_closingTID;	// ���ڹرջỰ���û��̣߳���������Client��������SetServeIPP(NEW_IPP/INVALID_IPP)���̣߳�

public:
	// ��Ҫʹ�ô˺������������ʹ��
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
	/// �ж���ʽ�ص����Ļص��汾�Ƿ�ƥ�䣨�������ڲ������this->GetStreamedCallbackTypeInfo_()��
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
