// PCC_CenterSession.cpp
//
// ע��: ���ļ�Ϊ�������ɣ���С���޸�

#include "StdAfx.h"
#include "PCC_CenterSession.h"
#include "ipcvt.h"
#include "nplog.h"
#include "nodemanage.h"
#include "singleton.h"
#include "modelmanage.h"
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
// interface PCC_Deploy

PCC_Deploy_S::PCC_Deploy_S(PCC_CenterSessionMaker& sessionMaker, PCC_CenterSession* sessionR, IPCC_Deploy_LocalCallback* sessionL)
	: m_sessionMaker(sessionMaker), m_sessionR(sessionR), m_sessionL(sessionL)
{
	NPR_ASSERT((NULL==sessionR) != (NULL==sessionL)); // ����ֻ��Ϊһ��ģʽ
	// TODO: �����PCC_Deploy�Ĺ��촦��
}

PCC_Deploy_S::~PCC_Deploy_S()
{
	// TODO: �����PCC_Deploy����������
}

TCPSError PCC_Deploy_S::OnConnected(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN INT32 sessionCount
				)
{
	// TODO: ����ӽӿ�PCC_Deploy�����Ӻ���

	NPLogInfo(("PCC_Deploy_S::OnConnected(%d, %s, %d)", sessionKey, IPP_TO_STR_A(peerID_IPP), sessionCount));
	return m_deploy.OnConnected(sessionKey,peerID_IPP,sessionCount);
	
}

void PCC_Deploy_S::OnCallbackReady()
{
	// TODO: ����ӽӿ�PCC_Deploy�Ļص���������

	NPLogInfo(("PCC_Deploy_S::OnCallbackReady()"));
}

void PCC_Deploy_S::OnPostingCallReady()
{
	// TODO: ����ӽӿ�PCC_Deploy��posting�ص���������

	NPLogInfo(("PCC_Deploy_S::OnPostingCallReady()"));
}

void PCC_Deploy_S::OnPeerBroken(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_Deploy_S::OnPeerBroken(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: ����ӽӿ�PCC_Deploy�ĶԶ˶��ߴ���
}

void PCC_Deploy_S::OnClose(
				IN INT32 sessionKey,
				IN const IPP& peerID_IPP,
				IN TCPSError cause
				)
{
	NPLogInfo(("PCC_Deploy_S::OnClose(%d, %s, %s(%d))", sessionKey, IPP_TO_STR_A(peerID_IPP), tcps_GetErrTxt(cause), cause));
	// TODO: ����ӽӿ�PCC_Deploy�����ӹرմ���
	m_deploy.OnClose(sessionKey,peerID_IPP,cause);
}

TCPSError PCC_Deploy_S::Login(
				IN const tcps_String& ticket
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.Login(ticket);	
}

TCPSError PCC_Deploy_S::Logout(
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.Logout();
}

TCPSError PCC_Deploy_S::CreateTrunk(
				IN const tcps_String& trunk
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.CreateTrunk(trunk);
}

TCPSError PCC_Deploy_S::RemoveTrunk(
				IN const tcps_String& trunk
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.RemoveTrunk(trunk);
}

TCPSError PCC_Deploy_S::ListTrunk(
				OUT tcps_Array<tcps_String>& trunks
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.ListTrunk(trunks);
}

TCPSError PCC_Deploy_S::AddAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag,
				IN const tcps_Array<PCC_ModuleFile>& files
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.AddAuthCenter(trunk,authTag,files);
}

TCPSError PCC_Deploy_S::RemoveAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.RemoveAuthCenter(trunk,authTag);
}

TCPSError PCC_Deploy_S::ListAuthCenter(
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_Tag>& authTags
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.ListAuthCenter(trunk,authTags);
}

TCPSError PCC_Deploy_S::FindAuthCenter(
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.FindAuthCenter(trunk,authTag);
}

TCPSError PCC_Deploy_S::AddModule(
				IN const tcps_String& trunk,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles,
				OUT INT64& moduleKey
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.AddModule(trunk,moduleProperty,moudleFiles,moduleKey);
}

TCPSError PCC_Deploy_S::AddModuleFile(
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.AddModuleFile(trunk,moduleKey,fileType,moduleFiles);
}

TCPSError PCC_Deploy_S::RemoveModule(
				IN const tcps_String& trunk,
				IN INT64 moduleKey
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.RemoveModule(trunk,moduleKey);
}

TCPSError PCC_Deploy_S::RemoveModuleFiles(
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN INT32 fileType
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.RemoveModuleFiles(trunk,moduleKey,fileType);
}

TCPSError PCC_Deploy_S::ListModules(
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo
				) method
{
	// TODO: ��ʵ�ִ˺���
	return m_deploy.ListModules(trunk,modulesInfo);
}

TCPSError PCC_Deploy_S::AddModel(
				IN const PCC_ModelProperty& modelProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) method
{
	// TODO: ��ʵ�ִ˺���
	return pgrid_util::Singleton<CModelManage>::instance().AddModel(modelProperty,modelFiles);
}

TCPSError PCC_Deploy_S::ListModels(
				OUT tcps_Array<PCC_ModelPropWithKey>& modelsInfo
				) method
{
	// TODO: ��ʵ�ִ˺���
	return pgrid_util::Singleton<CModelManage>::instance().ListModels(modelsInfo);
}

TCPSError PCC_Deploy_S::DelModel(
				IN INT64 modelKey
				) method
{
	// TODO: ��ʵ�ִ˺���
	return pgrid_util::Singleton<CModelManage>::instance().DelModel( modelKey ); 
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
	m_client_ipp = peerID_IPP;
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
	m_gridConn.m_user = "netposa";
	m_gridConn.m_pass = "netposa";

	IPP serverIPP;
	
	serverIPP.ip_ = GetLocalIP();//inet_addr("127.0.0.1");//���ӱ���
	serverIPP.port_ = 9012;
	//m_gridConn.m_service = m_psenssion;
	m_gridConn.SetServeIPP(serverIPP,0,m_client_ipp);//
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
	pgrid_util::Singleton<CNodeManage>::instance().GetPccProperty(pccProp);
	return TCPS_OK;
}

TCPSError PCC_User_S::ListNodes(
				OUT tcps_Array<PCC_NodeDesc>& nodes
				) method
{
	// TODO: ��ʵ�ִ˺���
	return pgrid_util::Singleton<CNodeManage>::instance().ListNodes(nodes);
}

TCPSError PCC_User_S::GetNodeDynamicContext(
				IN const tcps_String& nodeName,
				OUT PCC_DynamicContext& dynamicContext
				) method
{
	// TODO: ��ʵ�ִ˺���
	//IPP ipp;
	//this->GetPeerIPP(&ipp);

	return pgrid_util::Singleton<CNodeManage>::instance().GetNodeDynamicContext(nodeName,dynamicContext);
}

TCPSError PCC_User_S::ListModules(
				IN const tcps_String& regex,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method
{
	// TODO: ��ʵ�ִ˺���
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().ListModules(regex,modulesInfo);
	//return TCPS_ERR_NOT_IMPLEMENTED;
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
	//��moduleKey�����ƶϳ�execute�����õ�ģ�ͣ�����汾����moduleKey��ȫ��Ψһ��
	//
	//��ʱ����������ҵ
	{
		GRID_JobInfo  jobinfo;
		jobinfo.dataInputUrl = inputUrl;
		jobinfo.dataOutputUrl = outputUrl;
		jobinfo.programParam = moduleParams;//Ӧ��֧�����ݿ��� ������������

		//jobinfo.splitter.name = "RecordsSplit";	//
		jobinfo.splitter.ver.majorVer = 1;
		jobinfo.splitter.ver.minorVer = 0;
		PCC_Tag tag;
		if(pgrid_util::Singleton<CTrunkManage>::instance().getModuleTag(moduleKey,tag)<0)
			return TCPS_ERROR;
		jobinfo.programID.ver.majorVer = tag.version.major;
		jobinfo.programID.ver.minorVer = tag.version.minor;
		jobinfo.programID.name = tag.name;

		jobinfo.programID.cpuType = cpu_x86_x64;
		jobinfo.programID.osType = ost_Windows_7;
		jobinfo.programID.executeBits = eb_32bits;
		jobinfo.programID.binaryType =bt_machineRaw; 

		jobinfo.priority = GRID_JOBPRIO_NORMAL;
		jobinfo.jobTaskMaxAttempts = 3;
		jobinfo.skipFailedJobTaskPercent = 0;
		GRID_ProgramID prog;
		BOOL isFound =FALSE;
		prog.name = tag.name;
		prog.ver.majorVer=tag.version.major;
		prog.ver.minorVer=tag.version.minor;
		m_gridConn.FindJobProgram(prog,isFound);
		if(!isFound)
		{
			//��ȡģ��from trunk
			tcps_Array<PCC_ModuleFile> moudleFiles;
			pgrid_util::Singleton<CTrunkManage>::instance().GetModuleByID( moduleKey, moudleFiles);
			//���ģ��
			GRID_ProgramInfo programInfo;
			tcps_Array<GRID_ProgramFile> files;
			files.Resize(moudleFiles.Length());
			for (int i=0;i<moudleFiles.Length();++i)
			{
				files[i].name = moudleFiles[i].name;
				files[i].data = moudleFiles[i].data;
			}
			programInfo.programID = jobinfo.programID;
			m_gridConn.AddJobProgram( programInfo, files );
		}
		return m_gridConn.CommitJob(jobKey, jobinfo);
	}
	//return TCPS_ERR_NOT_IMPLEMENTED;
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
