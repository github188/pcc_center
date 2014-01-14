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
	// TODO: ���账���˶���������������������OnPeerBroken()
	virtual void OnPeerBroken()
		{	}

	// ���ӹر�֪ͨ�麯������OnPeerBroken()֮�󱻵��ã�
	// ע: ���йر�������ᴥ��
	// TODO: ���账���رն���������������������OnClose()
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

	// �����ͻ��˶����posting�������Ͷ���
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
				OUT NodeDesc& staticContext
				) cacheable_callback
	{	// TODO: ���������������ش˺���
		(void)staticContext;
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError GetDynamicContext(
				OUT DynamicContext& dynamicContext
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
				IN INT64 modelKey
				) callback
	{	// TODO: ���������������ش˺���
		(void)modelKey;
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
				OUT NodeDesc& staticContext
				) cacheable_callback;

	static TCPSError Local_GetDynamicContext(
				IN void* sessionObj_wrap,
				OUT DynamicContext& dynamicContext
				) callback;

	static TCPSError Local_AddModel(
				IN void* sessionObj_wrap,
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback;

	static TCPSError Local_DelModel(
				IN void* sessionObj_wrap,
				IN INT64 modelKey
				) callback;
};
#endif // #ifndef PCC_Center_defined

#ifndef BaseFacet_defined
#define BaseFacet_defined
class BaseFacet_S;
class BaseFacet_RC;
class BaseFacet : public IBaseFacet_LocalCallback
{
	friend class BaseFacet_S;
	friend class BaseFacet_RC;
private:
	BaseFacet(const BaseFacet&);
	BaseFacet& operator= (const BaseFacet&);

	typedef BaseFacet* PBaseFacet_;

public:
	// initNetworkSingletons���Ƿ��ʼ��������ص�������ֻ�������ӽ����ڷ��񣬿ɴ�false��
	explicit BaseFacet(BOOL initNetworkSingletons = true);
	virtual ~BaseFacet();

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
	// TODO: ���账���˶���������������������OnPeerBroken()
	virtual void OnPeerBroken()
		{	}

	// ���ӹر�֪ͨ�麯������OnPeerBroken()֮�󱻵��ã�
	// ע: ���йر�������ᴥ��
	// TODO: ���账���رն���������������������OnClose()
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

	// �����ͻ��˶����posting�������Ͷ���
	TCPSError CleanPostingSendingQueue();
	static TCPSError CleanPostingSendingQueue(
				IN const PBaseFacet_* clients,
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
		typedef tcps_QuickStringMap<CPtrStrA, Info, 13> MethodMap;
		MethodMap mmap_;
		BOOL matching_AliveCheck;
		BOOL matching_GetServeName;
		BOOL matching_GetContextInfos;
		BOOL matching_GetResourceUsage;
		BOOL matching_GetAllInterfaceCalls;
		BOOL matching_GetIDLHeaders;
		BOOL matching_GetClientHeaders;
		BOOL matching_GetServeVersion;
		BOOL matching_GetCompileNum;
		BOOL matching_GetWorkPath;
		BOOL matching_ShutdownSelf;
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
	TCPSError AliveCheck(
				) method;

public:
	TCPSError GetServeName(
				OUT tcps_String& name,
				OUT INT32& pid
				) cacheable_method;

public:
	TCPSError GetContextInfos(
				OUT INT32& servePID,
				OUT LTMSEL& startMSEL,
				OUT tcps_String& operatingSystem,
				OUT tcps_String& compiler,
				OUT tcps_String& binType,
				OUT INT64& totalMem,
				OUT INT64& cpuFreq,
				OUT INT32& cpuCount
				) cacheable_method;

public:
	TCPSError GetResourceUsage(
				IN ResUsageType rut,
				OUT double& cpuUsage,
				OUT double& memUsage,
				OUT tcps_Array<IPPToFaceStat>& connectionsStat
				) method;

public:
	TCPSError GetAllInterfaceCalls(
				OUT tcps_Array<FaceCalls>& faceCalls
				) cacheable_method;

public:
	TCPSError GetIDLHeaders(
				OUT tcps_Array<FaceContents>& idlHeaders
				) cacheable_method;

public:
	TCPSError GetClientHeaders(
				IN const char* language, IN INT32 language_len /*= -1*/,
				OUT tcps_Array<FaceContents>& userHeaders
				) cacheable_method;
	TCPSError GetClientHeaders(
				IN const char* language,
				OUT tcps_Array<FaceContents>& userHeaders
				) cacheable_method
		{	return this->GetClientHeaders(
							language, -1,
							userHeaders
							);
		}
	TCPSError GetClientHeaders(
				IN const tcps_String& language,
				OUT tcps_Array<FaceContents>& userHeaders
				) cacheable_method
		{	return this->GetClientHeaders(
							language.Get(), language.Length(),
							userHeaders
							);
		}

public:
	TCPSError GetServeVersion(
				OUT INT32& majorVer,
				OUT INT32& minorVer,
				OUT INT32& thirdVer
				) cacheable_method;

public:
	TCPSError GetCompileNum(
				OUT INT64& compileNum
				) cacheable_method;

public:
	TCPSError GetWorkPath(
				OUT tcps_String& path
				) cacheable_method;

public:
	TCPSError ShutdownSelf(
				) posting_method;

public:
	static TCPSError ShutdownSelf_Batch(
				IN const PBaseFacet_* clients,
				IN INT_PTR clientsCount,
				OUT PBaseFacet_* sendFaileds = NULL,
				OUT INT_PTR* failedCount = NULL
				) posting_method;

	//////////////////////////////////////////////////////////////
	////// �ڴ�֮��Ĵ���ʹ����������ģ�ΪISCM���ʵ�ִ��� //////
private:
	void* m_base_v_tab_ptr;
	void* m_derived_v_tab_ptr;
	BaseFacet_RC* m_faceR;

private:
	struct CallSiteL_
	{
		BOOL needUpdateFlags;
		MethodMatchingFlag matchingFlags;
		PROC fnOnStreamedCall_L_;
		PROC fnAliveCheck;
		PROC fnGetServeName;
		PROC fnGetContextInfos;
		PROC fnGetResourceUsage;
		PROC fnGetAllInterfaceCalls;
		PROC fnGetIDLHeaders;
		PROC fnGetClientHeaders;
		PROC fnGetServeVersion;
		PROC fnGetCompileNum;
		PROC fnGetWorkPath;
		PROC fnShutdownSelf;
		CallSiteL_()
			: needUpdateFlags(true)
			, fnOnStreamedCall_L_(NULL)
			, fnAliveCheck(NULL)
			, fnGetServeName(NULL)
			, fnGetContextInfos(NULL)
			, fnGetResourceUsage(NULL)
			, fnGetAllInterfaceCalls(NULL)
			, fnGetIDLHeaders(NULL)
			, fnGetClientHeaders(NULL)
			, fnGetServeVersion(NULL)
			, fnGetCompileNum(NULL)
			, fnGetWorkPath(NULL)
			, fnShutdownSelf(NULL)
			{}
		void Reset()
		{
			needUpdateFlags = true;
			matchingFlags.Reset();
			fnOnStreamedCall_L_ = NULL;
			fnAliveCheck = NULL;
			fnGetServeName = NULL;
			fnGetContextInfos = NULL;
			fnGetResourceUsage = NULL;
			fnGetAllInterfaceCalls = NULL;
			fnGetIDLHeaders = NULL;
			fnGetClientHeaders = NULL;
			fnGetServeVersion = NULL;
			fnGetCompileNum = NULL;
			fnGetWorkPath = NULL;
			fnShutdownSelf = NULL;
		}
	};
	struct LocalMakingFlag_
	{
		BOOL making;
		BOOL failed;
		LocalMakingFlag_() : making(false), failed(false) {}
	};
	LocalMakingFlag_ m_localMakingFlag;	// ���ڱ��ط���ݹ���ô���
	IBaseFacet_LocalMethod* m_faceL;
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
#endif // #ifndef BaseFacet_defined

//[[end_iscm]]

#endif	// #ifndef _PCC_CenterClient_h_