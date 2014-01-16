
class XXXPCC_Center : public PCC_Center
{
private:
	XXXPCC_Center(const XXXPCC_Center&);
	XXXPCC_Center& operator= (const XXXPCC_Center&);

public:
	XXXPCC_Center()
		{}
	virtual ~XXXPCC_Center()
		{	DestroyRequester();	}

/// ���������¼�
protected:
	virtual TCPSError OnConnected()
	{
		// TODO: ��������Ӻ���
		return TCPS_OK;
	}
	virtual void OnPeerBroken()
	{
		// TODO: ����ӶԶ˶��ߴ���
	}
	virtual void OnClose()
	{
		// TODO: ��������ӹرմ���
	}
	virtual void OnConnectTimeout(IN TCPSError cause)
	{
		// TODO: ��������ӳ�ʱ����
		(void)cause;
	}

/// �ص�
protected:
	virtual TCPSError AddModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError DelModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError GetStaticContext(
				OUT PCC_NodeDesc& staticContext
				) cacheable_callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError GetDynamicContext(
				OUT PCC_DynamicContext& dynamicContext
				) callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError AddModel(
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError DelModel(
				IN INT64 modelKey
				) callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

protected:
	// ����TCPS_OK�����ض��򣻷��ط�TCPS_OK��ֹ�ض���
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_OK;
	}
};

class XXXPCC_Deploy : public PCC_Deploy
{
private:
	XXXPCC_Deploy(const XXXPCC_Deploy&);
	XXXPCC_Deploy& operator= (const XXXPCC_Deploy&);

public:
	XXXPCC_Deploy()
		{}
	virtual ~XXXPCC_Deploy()
		{	DestroyRequester();	}

/// ���������¼�
protected:
	virtual TCPSError OnConnected()
	{
		// TODO: ��������Ӻ���
		return TCPS_OK;
	}
	virtual void OnPeerBroken()
	{
		// TODO: ����ӶԶ˶��ߴ���
	}
	virtual void OnClose()
	{
		// TODO: ��������ӹرմ���
	}
	virtual void OnConnectTimeout(IN TCPSError cause)
	{
		// TODO: ��������ӳ�ʱ����
		(void)cause;
	}

protected:
	// ����TCPS_OK�����ض��򣻷��ط�TCPS_OK��ֹ�ض���
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_OK;
	}
};

class XXXPCC_User : public PCC_User
{
private:
	XXXPCC_User(const XXXPCC_User&);
	XXXPCC_User& operator= (const XXXPCC_User&);

public:
	XXXPCC_User()
		{}
	virtual ~XXXPCC_User()
		{	DestroyRequester();	}

/// ���������¼�
protected:
	virtual TCPSError OnConnected()
	{
		// TODO: ��������Ӻ���
		return TCPS_OK;
	}
	virtual void OnPeerBroken()
	{
		// TODO: ����ӶԶ˶��ߴ���
	}
	virtual void OnClose()
	{
		// TODO: ��������ӹرմ���
	}
	virtual void OnConnectTimeout(IN TCPSError cause)
	{
		// TODO: ��������ӳ�ʱ����
		(void)cause;
	}

/// �ص�
protected:
	virtual TCPSError OnExecuted(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context
				) posting_callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError OnExecuted1(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context,
				IN const tcps_Array<tcps_Binary>& outArgs
				) posting_callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

protected:
	// ����TCPS_OK�����ض��򣻷��ط�TCPS_OK��ֹ�ض���
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		// TODO: ��ʵ�ִ˺���
		return TCPS_OK;
	}
};
