#include "StdAfx.h"
#include "PCC_Startup.h"
#include "Singleton.h"
#include "smlib.h"
//#include "my_np_griduserclient.h"
#include "nplog.h"
//#include "modulemanage.h"
#include "npfdk.h"
#include "TrunkManage.h"
#include "modelmanage.h"
class PCC_Scatter_S;
CPCC_Startup::CPCC_Startup(void)
{
}

CPCC_Startup::~CPCC_Startup(void)
{
}

int CPCC_Startup::Startup()
{

	//test

	//boost::shared_ptr<CModuleManage> pmm ;
	//pmm.reset(new CModuleManage );
	//pmm->RemoveModule(0);
	//test
//	tcps_Array<PCC_ModuleFile> moudleFiles;
//	pgrid_util::Singleton<CScatteredManage>::instance().CopyModules("D:/niwho-work/new_pgrid/job_center/Debug.2008/ScatterProgams/1000001#PCC_ImgProc_Phimix-1.0",moudleFiles);	
//	pgrid_util::Singleton<CScatteredManage>::instance().mytest();
//	pgrid_util::Singleton<CScatteredManage>::instance().init();
//_s debug
//	int rt;
//	pgrid_util::Singleton<CTrunkManage>::instance();//.init();//
//	tcps_String trunk;
	//trunk.Assign("wtttt2");
  //  rt = pgrid_util::Singleton<CTrunkManage>::instance().CreateTrunk( trunk); 
	//rt = pgrid_util::Singleton<CTrunkManage>::instance().RemoveTrunk(trunk);
	//rt = pgrid_util::Singleton<CTrunkManage>::instance().CreateTrunk( trunk); 
//	tcps_Array<tcps_String> trunks; 
//	rt = pgrid_util::Singleton<CTrunkManage>::instance().ListTrunk(trunks);

//	PCC_ModuleProperty prop;
//	prop.moduleType = 0;//PCC_MODULE_IMGPROC;
///	prop.moduleTag.name = "compppp";
//	prop.moduleTag.version.major = 2;
//	prop.moduleTag.version.minor = 1;
//	FILE *fp;
//	fp = fopen(
//		"D:/niwho-work/NP_PCC_test/Release/auth_test.exe"//face_togpl(1)test.json
//		,"rb"); 
//	fseek(fp,0,SEEK_END);//48��6254
//
//	long file_len = ftell(fp);
//	fseek(fp,0,SEEK_SET);
	
//	tcps_Array<PCC_ModuleFile> moudleFiles;
//	moudleFiles.Resize(1);
//	moudleFiles[0].data.Resize(file_len);
//	fread(moudleFiles[0].data.Get(),file_len,1,fp);
//	moudleFiles[0].name = "auth_test.exe";
//	moudleFiles[0].entry = TRUE;
//	fclose(fp);
//	PCC_ModuleTag tag;
//	tag.name = "authcenter1";
//	tag.version.major = 1;
//	tag.version.minor = 2;
//	rt = pgrid_util::Singleton<CTrunkManage>::instance().AddAuthCenter(trunk,tag,moudleFiles);
//	INT64 moduleKey =1;
//	rt = pgrid_util::Singleton<CTrunkManage>::instance().AddModule(trunk,prop,moudleFiles,moduleKey);
	//const tcps_String& trunk,INT64 moduleKey,MY_NP_GridUserClient &m_gridConn
//	MY_NP_GridUserClient m_gridConn;
//	rt = pgrid_util::Singleton<CTrunkManage>::instance().RemoveModule(trunk,moduleKey,m_gridConn);
	//const tcps_String& trunk,tcps_Array<PCC_ModulePropWithKey>& modulesInfo
//	rt = pgrid_util::Singleton<CTrunkManage>::instance().AddModule(trunk,prop,moudleFiles,moduleKey);
//	tcps_Array<PCC_ModulePropWithKey> modulesInfo;
//	rt = pgrid_util::Singleton<CTrunkManage>::instance().ListModules(trunk,modulesInfo);
//	return 0;
//_e debug
	//����jc����
//	char jobcenterdir[MAX_PATH];
//	GetModuleFileName(NULL,jobcenterdir,MAX_PATH);
//	_tcsrchr(jobcenterdir,'\\')[1] = 0;
//	strcat(jobcenterdir,"/JobCenter.exe -port 9012");
//	OSProcessID id = NPCreateProcess(jobcenterdir);
//	if (INVALID_OSPROCESSID == id)
//	{
//		NPLogError(("�����������ʧ��"));
//		return -1;
//	}

//	HANDLE hd = OpenProcess(PROCESS_ALL_ACCESS, false, id);
//	Sleep(500);//�ȴ�grid�������
	//��ȡjcģ��
	//ʹ�õ���ģʽ����ȫ�ֱ���
	/*
	MY_NP_GridUserClient& m_gridUser = pgrid_util::Singleton<MY_NP_GridUserClient>::instance();
		m_gridUser.m_user = "netposa";
		m_gridUser.m_pass = "netposa";
		
		IPP serverIPP;
		serverIPP.ip_ = inet_addr("127.0.0.1");//���ӱ���
		serverIPP.port_ = 9011;
		
		TCPSError ret = m_gridUser.SetServeIPP(serverIPP);//
		int counter =0;
		while (TCPS_OK != ret && counter++ < 10)
		{
			ret = m_gridUser.SetServeIPP(serverIPP);//
			Sleep(100);
		}
		if (TCPS_OK != ret)
		{
			NPLogError(("�����������ʧ��"));
			return -1;
		}
		else
		{
			m_gridUser.SetKeeping(TRUE);//\
	       
			//��ȡ�������ĳ���ģ��
			//���ﲻ��Ҫ�������
			/ *
			tcps_Array<GRID_User_T::JobProgram> progInfos;
					TCPSError ret = m_gridUser.ListJobPrograms(progInfos);
			
					std::map<>;
					if (TCPS_OK == ret)
					{
			
					}
					else
					{
						NPLogError(("��ȡ����ģ��ʧ��"));
						return -1;
					}* /
			
		}*/
	
	

	//ȫ�ֱ������� ʹ�õ���ģʽ���� ��������Ǳ�־����
	//pgrid_util::Singleton<std::deque< > >::instance();//�û��ύ����ҵ�������FIFO��just for scattered
    //pgrid_util::Singleton<std::map<Node_Id,PCC_Scatter_S*> >::instance();//scattered �ڵ�����
//	pgrid_util::Singleton<CScatteredManage>::instance().init();//
	//scatterd ģ��Ŀ¼

	pgrid_util::Singleton<CTrunkManage>::instance();//.init();//
	pgrid_util::Singleton<CModelManage>::instance().init();
	PCC_ModelProperty modelProperty;
	modelProperty.modelTag.name = "mmodel0";
	modelProperty.modelTag.version.major = 1;
	modelProperty.modelTag.version.minor = 2;	
	FILE *fp;
	fp = fopen(
		"C:/Users/niwho/Documents/My RTX Files/niwho/Grid.cnp"//face_togpl(1)test.json
		,"rb"); 
	fseek(fp,0,SEEK_END);//48��6254

	long file_len = ftell(fp);
	fseek(fp,0,SEEK_SET);
	
	tcps_Array<PCC_ModelFile> modelFiles;
	modelFiles.Resize(1);
	modelFiles[0].data.Resize(file_len);
	fread(modelFiles[0].data.Get(),file_len,1,fp);
	modelFiles[0].name = "Grid.cnp";
	//moudleFiles[0].entry = TRUE;
	fclose(fp);
	pgrid_util::Singleton<CModelManage>::instance().AddModel(modelProperty,modelFiles);
//	tcps_String trunk;
//	trunk.Assign("wtttt2");
//	int rt;
//	FILE *fp;
//	fp = fopen(
//		"D:/niwho-work/NP_PCC_test/Release/auth_test.exe"//face_togpl(1)test.json
//		,"rb"); 
//	fseek(fp,0,SEEK_END);//48��6254
//
//	long file_len = ftell(fp);
//	fseek(fp,0,SEEK_SET);
//	
//	tcps_Array<PCC_ModuleFile> moudleFiles;
//	moudleFiles.Resize(1);
//	moudleFiles[0].data.Resize(file_len);
//	fread(moudleFiles[0].data.Get(),file_len,1,fp);
//	moudleFiles[0].name = "auth_test.exe";
//	moudleFiles[0].entry = TRUE;
//	fclose(fp);
//	PCC_ModuleTag tag;
//	tag.name = "authcenter2";
//	tag.version.major = 1;
//	tag.version.minor = 2;
//	rt = pgrid_util::Singleton<CTrunkManage>::instance().AddAuthCenter(trunk,tag,moudleFiles);
	return 0;
}
