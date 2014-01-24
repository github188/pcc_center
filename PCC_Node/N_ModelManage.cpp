#include "StdAfx.h"
#include "N_ModelManage.h"
#include "npfdk.h"
#include "nplog.h"
#include <sstream>
#include "filestorage.h"
#include "smlib.h"
#include "strtmpl.h"
#include "singleton.h"
#include "ipcvt.h"
#include "np_gridutils.h"
//#include "nodemanage.h"
#include "filesearch.h"
const std::string CModelManage::m_ModelsSql("CREATE TABLE IF NOT EXISTS Models \
										   (id_mod INTEGER PRIMARY KEY AUTOINCREMENT, name_mod TEXT NOT NULL unique, ver_mod TEXT NOT NULL,unique(name_mod,ver_mod))"); 
CModelManage::CModelManage(void)
{
}

CModelManage::~CModelManage(void)
{
}

int CModelManage::init()
{
	char buf[512];
	GetModuleFileName(NULL,buf,512);
	_tcsrchr(buf,'\\')[1] = 0;
	strcat(buf,"Models");

	if(!CreatePath(buf))//�Ѵ��ڣ���Ҳ����TRUE
	{
		NPLogError(("����ModelsĿ¼ʧ�ܣ�\n"));
		return -1;
	};
	
	int rc;
	strcat(buf,"/Models.db");
	rc = sqlite3_open(buf, &m_db);
	if( rc )
	{
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		NPLogError(("��Models���ݿ�ʧ��:%s��\n",sqlite3_errmsg(m_db)));
		sqlite3_close(m_db);
		return -1;
	}
	
	
	//��ʼ�����ݿ�
	char *zErrMsg = 0;
	rc = sqlite3_exec(m_db, CModelManage::m_ModelsSql.c_str(), 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("������ʧ��:%s��\n",zErrMsg));
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
	
}
//modelFiles��Ϊѹ���ļ�
TCPSError CModelManage::AddModel(
				 const PCC_ModelProperty& modelProperty,
				 const tcps_Array<PCC_ModelFile>& modelFiles,
				 const tcps_String&ipp_str
				) 
{
	// �ж��Ƿ��Ѿ���ӹ���ģ����

	//
	//start: ����sqlite��¼��Щ��Ϣ�������쳣�ָ���ǰN�ڵ�ĸ�n����Ϣ
//	std::stringstream insert_sql,ver_str;
//	ver_str<<modelProperty.modelTag.version.major<<"."<<modelProperty.modelTag.version.minor;
//	insert_sql<<"insert into Models(name_mod,ver_mod) values('"
//		<<modelProperty.modelTag.name.Get()<<"','"<<ver_str.str()<<"')";
//	//#define INSNW 0
//#ifndef INSNW
//	char *zErrMsg = 0;
//	if( sqlite3_exec(m_db, insert_sql.str().c_str(), 0, 0, &zErrMsg)!=SQLITE_OK )
//	{
//		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
//		NPLogError(("������ʧ��:%s\n:%s��\n",__FUNCTION__,zErrMsg));
//		sqlite3_free(zErrMsg);
//		return TCPS_ERROR;
//	}
//#endif
	//end:

	
	char buf[512];
	GetModuleFileName(NULL,buf,512);
	_tcsrchr(buf,'\\')[1] = 0;
	strcat(buf,"Models\\");
	if(!CreatePath(buf))//�Ѵ��ڣ���Ҳ����TRUE
	{
		NPLogError(("����Ŀ¼ʧ�ܣ�:%s\n",buf));
		return TCPS_ERROR;
	}
	std::stringstream unpackPath;
	unpackPath<<modelProperty.modelTag.name.Get()<<"-"<<modelProperty.modelTag.version.major
		<<"."<< modelProperty.modelTag.version.minor<<"\\";//"temp";
	strcat(buf,unpackPath.str().c_str());
	if(!CreatePath(buf))//�Ѵ��ڣ���Ҳ����TRUE
	{
		NPLogError(("����Ŀ¼ʧ�ܣ�:%s\n",buf));
		return TCPS_ERROR;
	}
	unpackPath.str("");
	unpackPath.clear();
	unpackPath<<buf;
//	unpackPath<<"N\\";
//	if(!CreatePath(unpackPath.str().c_str()))//�Ѵ��ڣ���Ҳ����TRUE
//	{
//		NPLogError(("����Ŀ¼ʧ�ܣ�:%s\n",unpackPath.str().c_str()));
//		return TCPS_ERROR;
//	}
	for (int i=0;i<modelFiles.Length();++i)
	{
		CFileStorage fs;
		strcat(buf,modelFiles[i].name.Get());

		fs.Open(buf,CFileStorage::fs_create_always);
		fs.Write(0,modelFiles[i].data.Get(),modelFiles[i].data.Length());
		fs.Close();
		//_tcsrchr(buf,'\\')[1] = 0;
		break;
	}

	if(NP_GridFUnpack ( buf,  unpackPath.str().c_str(), NULL))
	{
		//�Ƴ��ļ�
		NPRemoveFileOrDir(buf);
		_tcsrchr(buf,'\\')[1] = 0;
		////////////////
		//����Ĵ���Ҫ����
		/////////////////////
		strcat(buf,"N\\");
		//����ģ�ͷ���˳���
		tcps_String exefile;
		if(FindExe(buf,exefile))
		{
			printf("%s\n",exefile.Get());
		}
		else
		{
			NPLogError(("�޷��ҵ�ģ��%s����������\n",modelProperty.modelTag.name.Get()));
			return TCPS_ERROR;
		}
		strcat(buf,exefile.Get());
		StartXNode(modelProperty.modelTag,buf,ipp_str);

		return TCPS_OK;
	}
	else
		return TCPS_ERROR;
}


TCPSError CModelManage::ListModels(
				 tcps_Array<PCC_ModelPropWithKey>& modelsInfo
				)
{
	return TCPS_OK;
}

TCPSError CModelManage::DelModel(
				 const PCC_Tag& tag
				)
{
	CNPAutoLock lock(m_lock_xnode);
	std::map<PCC_Tag,nwProcessInfo>::const_iterator it;
	it = m_xnode_processes.find(tag);
	if(it!=m_xnode_processes.end())
	{
		
		NPKillProcess(it->second.pid);
		//�Ƴ��ļ�
		char buf[512];
		char tmp[16];
		GetModuleFileName(NULL,buf,512);
		_tcsrchr(buf,'\\')[1] = 0;
		std::stringstream path;
		path<<buf<<"Models\\"<<tag.name.Get()<<"-"<<tag.version.major<<"."<<tag.version.minor;
		NPRemoveFileOrDir(path.str().c_str());
		return TCPS_OK;
	}	

	return TCPS_ERROR;
}

BOOL CModelManage::FindExe (const char *searchDir,tcps_String& exefile)
{
	struct TFSCB
	{
		
		static BOOL fn(LPVOID cbParam, BOOL isDir, LPCTSTR filePathname)
		{

			if (!isDir)
			{
				std::string str1 =GetFileName(filePathname);
				int npos =-1;
				npos =str1.find_last_of(".");
				if(npos>-1)
				{
					std::string str_suffix = str1.substr(npos,-1);
					if(str_suffix == ".exe")
					{
						((tcps_String*)cbParam)->Resize(str1.length()+1);
						((tcps_String*)cbParam)->Assign(str1.c_str());
						return true;
					}
				}
				
			}

			return true;
		}

		static BOOL Find (const char *srcDir,void* param)
		{

			return FileSearchEx(srcDir, "*", 0, fn, param , 0, "", "");
		}
	};

	
	return (TFSCB::Find(searchDir,&exefile));
}


TCPSError CModelManage::StartXNode(const PCC_Tag& tag,const char *filepath,const tcps_String&ipp_str)
{
	std::stringstream auth_exe_port;
	OSProcessID pid = INVALID_OSPROCESSID;
	int cnt = 10;
	nwProcessInfo info;
	strcpy(info.filepath,filepath);
	info.pid= info.port = -1;
	//temp
	info.port =9012;
	
	
	while(INVALID_OSPROCESSID == pid&&(--cnt)){
		auth_exe_port.str("");
		auth_exe_port.clear();
		info.port=generatePort();
		auth_exe_port<<filepath<<" -ippcenter"<<ipp_str.Get() <<"."<<9012;//info.port;//todoǱ�ڵĶ˿ڳ�ͻ������� ����srand
		info.pid = pid = NPCreateProcess(auth_exe_port.str().c_str());
		if (INVALID_OSPROCESSID == pid)
		{
			NPLogError(("�����ڵ�ʧ��,��������(%d):%s,\n%s\n",cnt,filepath,auth_exe_port.str().c_str()));
			
		}
	}
	if (INVALID_OSPROCESSID == pid&&(--cnt))
	{
		NPLogError(("�����ڵ�ʧ��:%s\n",filepath));
		return TCPS_ERROR;
	}
	
	//addAuth(trunk,info);
	//��¼
	CNPAutoLock lock(m_lock_xnode);
	m_xnode_processes.insert(std::make_pair(tag,info));
	return TCPS_OK;
}