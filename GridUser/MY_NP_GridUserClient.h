#pragma once

#include "NP_GridUserClient.h"

class PCC_Service_S;
class MY_NP_GridUserClient : public GRID_User
{
private:
	MY_NP_GridUserClient(const MY_NP_GridUserClient&);
	MY_NP_GridUserClient& operator= (const MY_NP_GridUserClient&);

public:
	tcps_String m_user;
	tcps_String m_pass;
	PCC_Service_S * m_service;

public:
	MY_NP_GridUserClient()
	{}
	virtual ~MY_NP_GridUserClient()
	{	DestroyRequester();	}

	/// ���������¼�
protected:
	virtual TCPSError OnConnected()
	{
		return this->Login(m_user, m_pass);
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
	virtual TCPSError ReplyCommitJob(
		IN INT64 jobKey,
		IN TCPSError replyCode,
		IN const tcps_Binary& context
		) posting_callback;
	/*
	{
			return m_service->OnExecuted(jobKey,replyCode,context.Get(),context.Length());
		}*/
	

protected:
	// ����TCPS_OK�����ض��򣻷��ط�TCPS_OK��ֹ�ض���
	virtual TCPSError OnPrepareRedirect_(
		IN const IPP& redirectIPP,
		IN const tcps_Binary& redirectParam
		) posting_callback
	{
		// TODO: ��ʵ�ִ˺���
		redirectIPP;redirectParam;
		return TCPS_OK;
	}
};
