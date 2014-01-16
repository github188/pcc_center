#include "StdAfx.h"
#include "TrunkManage.h"
#include "npfdk.h"
#include "nplog.h"
#include <sstream>
#include "filestorage.h"
#include "smlib.h"
#include "strtmpl.h"
#include "singleton.h"
#include "ipcvt.h"
//#include "modulemanage.h"
const std::string CTrunkManage::m_TrunkSql("CREATE TABLE IF NOT EXISTS PCC_TRUNKS \
										   (id_trunk INTEGER PRIMARY KEY AUTOINCREMENT, trunk_name TEXT NOT NULL unique, trunk_path TEXT NOT NULL)"); 
//�����module_name �����˰汾��,���磺 name_1_0,type :0 ��Ȩģ��  �������� PCC_ModuleType
const std::string CTrunkManage::m_ModuelsSql("CREATE TABLE IF NOT EXISTS PCC_TRUNK_MODULES \
											 (id_module INTEGER PRIMARY KEY AUTOINCREMENT,id_tk INTEGER , module_name TEXT NOT NULL unique,type INTEGER NOT NULL,\
											 module_path TEXT NOT NULL,foreign key(id_tk) references PCC_TRUNKS (id_trunk) on delete cascade)");


CAuthManage::CAuthManage(CTrunkManage& trunk_mng):
	m_trunk_mng(trunk_mng)
{
}
CAuthManage::~CAuthManage()
{
	closeAuths();
}

int CAuthManage::init()
{
	//����ʱ���������е���Ȩ����
	tcps_Array<tcps_String> auth_paths;
	tcps_Array<tcps_String> trunks;
	m_trunk_mng.getAuthPath(auth_paths,trunks);
	for (int i=0;i<auth_paths.Length();++i)
	{
        startAuth(auth_paths[i].Get(),trunks[i].Get());
	}
	return 0;
}
int CAuthManage::getPort(std::string key)//����trunk��Ӧ����Ȩ����
{
	CNPAutoLock lok(m_lock_auth);
	std::map<std::string,nwProcessInfo>::const_iterator it;
	it = m_trunkPort.find(key);
	if(it!=m_trunkPort.end())
		return it->second.port;
	else//����������Ȩ����
	{
		
		//select * from PCC_TRUNK_MODULES as a left join PCC_TRUNKS as b on a.id_tk=b.id_trunk 
		tcps_String path;
		if(m_trunk_mng.getAuthPath(path,key.c_str())==0)
		{
			std::stringstream auth_exe_port;
			OSProcessID pid = INVALID_OSPROCESSID;
			int cnt = 10;
			nwProcessInfo info;
			info.pid= info.port = -1;
			while(INVALID_OSPROCESSID == pid&&(--cnt)){
				auth_exe_port.str("");
				auth_exe_port.clear();
				info.port =  generatePort();
				auth_exe_port<<path.Get()<<" -port"<<info.port;//todoǱ�ڵĶ˿ڳ�ͻ������� ����srand
				info.pid = pid = NPCreateProcess(auth_exe_port.str().c_str());
				if (INVALID_OSPROCESSID == pid)
				{
					NPLogError(("������Ȩ����ʧ��,��������(%d):%s\n",cnt,path.Get()));

				}
			}
			if (INVALID_OSPROCESSID == pid&&(--cnt))
			{
				NPLogError(("������Ȩ����ʧ��:%s\n",path.Get()));
				return -1;
			}
			addAuth(key,info);
			return 0;
		}
	}
	return -1;
}
int CAuthManage::closeAuths()
{
	CNPAutoLock lok(m_lock_auth);
	std::map<std::string,nwProcessInfo>::const_iterator it;
	for (it = m_trunkPort.begin();it!=m_trunkPort.end();++it)
	{
		NPKillProcess(it->second.pid);
	}
	m_trunkPort.clear();
	return 0;
}
void CAuthManage::addAuth(std::string key,nwProcessInfo info)
{
	CNPAutoLock lok(m_lock_auth);
	m_trunkPort.insert(std::make_pair(key,info));
}
void CAuthManage::removeAuth(std::string key)
{
	CNPAutoLock lok(m_lock_auth);
	std::map<std::string,nwProcessInfo>::const_iterator it;
	it = m_trunkPort.find(key);
	if(it!=m_trunkPort.end())
	{
		NPKillProcess(it->second.pid);
		m_trunkPort.erase(it);
	}
	
}

int CAuthManage::startAuth(std::string trunk,std::string filepath)
{
	//CNPAutoLock lok(m_lock_auth);
	std::stringstream auth_exe_port;
	OSProcessID pid = INVALID_OSPROCESSID;
	int cnt = 10;
	nwProcessInfo info;
	info.pid= info.port = -1;
	
	
	while(INVALID_OSPROCESSID == pid&&(--cnt)){
		auth_exe_port.str("");
		auth_exe_port.clear();
		info.port=generatePort();
		auth_exe_port<<filepath<<" -port"<< info.port;//todoǱ�ڵĶ˿ڳ�ͻ������� ����srand
		info.pid = pid = NPCreateProcess(auth_exe_port.str().c_str());
		if (INVALID_OSPROCESSID == pid)
		{
			NPLogError(("������Ȩ����ʧ��,��������(%d):%s,\n%s\n",cnt,filepath.c_str(),auth_exe_port.str().c_str()));
			
		}
	}
	if (INVALID_OSPROCESSID == pid&&(--cnt))
	{
		NPLogError(("������Ȩ����ʧ��:%s\n",filepath.c_str()));
		return -1;
	}
	
	addAuth(trunk,info);
	return 0;
}

///////////////////CTrunkManage/////////////////////////
CTrunkManage::CTrunkManage(void):m_db(NULL),m_auth_mng(*this)
{

	char buf[512];
	GetModuleFileName(NULL,buf,512);
	_tcsrchr(buf,'\\')[1] = 0;
	strcat(buf,"Trunks");

	if(!CreatePath(buf))//�Ѵ��ڣ���Ҳ����TRUE
	{
		NPLogError(("����TrunksĿ¼ʧ�ܣ�\n"));
		exit(-1);
	};
	
	int rc;
	strcat(buf,"/trunks.db");
	rc = sqlite3_open(buf, &m_db);
	if( rc )
	{
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		NPLogError(("��trunks���ݿ�ʧ��:%s��\n",sqlite3_errmsg(m_db)));
		sqlite3_close(m_db);
		exit(-1);
	}
	
	//��ʼ�����ݿ�
	char *zErrMsg = 0;
	rc = sqlite3_exec(m_db, CTrunkManage::m_TrunkSql.c_str(), 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("������ʧ��:%s��\n",zErrMsg));
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	rc = sqlite3_exec(m_db, CTrunkManage::m_ModuelsSql.c_str(), 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("������ʧ��:%s��\n",zErrMsg));
		sqlite3_free(zErrMsg);
		exit(-1);
	}
 
}

CTrunkManage::~CTrunkManage(void)
{
	if(m_db)
		sqlite3_close(m_db);
}
int CTrunkManage::getAuthPath(tcps_Array<tcps_String>&auth_paths,tcps_Array<tcps_String>&trunks)
{
	std::stringstream sql_query;
	sql_query<<"select module_name, trunk_name ,module_path from PCC_TRUNK_MODULES as a left join PCC_TRUNKS as b on a.id_tk=b.id_trunk where type=0" ;
	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.str().c_str(),-1,&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("ʧ�ܣ�:%s\n",__FUNCTION__));
		return -1;
	}
	char buf[512];
	GetModuleFileName(NULL,buf,512);
	
	strcat(buf,"Trunks\\");
	//strcat(buf,trunk.Get());
	while(sqlite3_step(st_query)== SQLITE_ROW)
	{
		strcat(buf,(const char *)sqlite3_column_text(st_query,1));//1
		auth_paths.Resize(auth_paths.Length()+1);
		trunks.Resize(trunks.Length()+1);
		trunks[trunks.Length()-1].Assign((const char *)sqlite3_column_text(st_query,1));
		//auth_paths[auth_paths.Length()-1].Assign((const char *)sqlite3_column_text(st_query,0));

		strcat(buf,"\\");
		strcat(buf,(const char *)sqlite3_column_text(st_query,0));//2
		const unsigned char *result = sqlite3_column_text(st_query,2);
		std::stringstream mod;
		mod << result;
		strcat(buf,"\\");
		strcat(buf,mod.str().c_str());//3
		//strcat(buf,".exe");
		auth_paths[auth_paths.Length()-1].Assign(buf);
		_tcsrchr(buf,'\\')[1] = 0;
		_tcsrchr(buf,'\\')[1] = 0;
		_tcsrchr(buf,'\\')[1] = 0;
	}
	return 0;
}
int CTrunkManage::getAuthPath(tcps_String&auth_path,const tcps_String& trunk)
{
	std::stringstream sql_query;
	sql_query<<"select module_path,module_name from PCC_TRUNK_MODULES as a left join PCC_TRUNKS as b on a.id_tk=b.id_trunk where type=0 and trunk_name='"
		<<trunk.Get()<<"'";
	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.str().c_str(),-1,&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("ʧ�ܣ�:%s\n",__FUNCTION__));
		return -1;
	}
	char buf[512];
	GetModuleFileName(NULL,buf,512);
	
	strcat(buf,"Trunks\\");
	strcat(buf,trunk.Get());
	if(sqlite3_step(st_query)== SQLITE_ROW)
	{
		strcat(buf,(const char *)sqlite3_column_text(st_query,1));
		//auth_paths.Resize(auth_paths.Length()+1);
		//auth_paths[auth_paths.Length()-1].Assign((const char *)sqlite3_column_text(st_query,0));
		const unsigned char *result = sqlite3_column_text(st_query,0);
		std::stringstream mod;
		mod << result;
		//CSmartArray<tstring> modNamVer;
		//StrSeparater_Sep(mod.str().c_str(),"_",modNamVer);
		strcat(buf,"\\");
		strcat(buf,mod.str().c_str());//modNamVer[0].c_str());
		//strcat(buf,".exe");
		auth_path.Assign(buf);
		_tcsrchr(buf,'\\')[1] = 0;
		_tcsrchr(buf,'\\')[1] = 0;
		return 0;
	}
	return -1;
}
int CTrunkManage::CreateTrunk(const tcps_String& trunk) 
{
	CNPAutoLock lok(m_lock_db);

	char buf[512];
	GetModuleFileName(NULL,buf,512);
	_tcsrchr(buf,'\\')[1] = 0;
	strcat(buf,"Trunks\\");
	strcat(buf,trunk.Get());//trunk_dirΪ���·�����������Ա�֤portable
	if(!CreatePath(buf))//�Ѵ��ڣ���Ҳ����TRUE
	{
		NPLogError(("����TrunksĿ¼ʧ�ܣ�:%s\n",__FUNCTION__));
		return -1;
	};

	std::string sql ="insert into PCC_TRUNKS(trunk_name,trunk_path) values('"+std::string(trunk.Get())+"','"+std::string(trunk.Get())+"')";
	char *zErrMsg = 0;
	if( sqlite3_exec(m_db, sql.c_str(), 0, 0, &zErrMsg)!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("������ʧ��:%s\n:%s��\n",__FUNCTION__,zErrMsg));
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
}
int CTrunkManage::RemoveTrunk(const tcps_String& trunk)
{
	CNPAutoLock lok(m_lock_db);
	std::string sql_del = "delete from PCC_TRUNKS where trunk_name='"+std::string(trunk.Get())+"'";
	std::string sql_query = "select trunk_path from PCC_TRUNKS where trunk_name='"+std::string(trunk.Get())+"'";//quey �Ƕ���� Ҫ�Ż�
	char *zErrMsg = 0;
	//Ҫɾ�� PCC_TRUNK_MODULES ���ж�Ӧ���� ���Ƴ���ӦĿ¼�������ļ���
	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.c_str(),sql_query.length(),&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("ʧ�ܣ�:%s\n",__FUNCTION__));
		return -1;
	}
	
	if(sqlite3_step(st_query)== SQLITE_ROW)
	{
		const unsigned char *result = sqlite3_column_text(st_query,0);
		/*if(result == 0)
			return "";*/
		std::stringstream trunk_dir;
		trunk_dir << result;

		char buf[512];
		GetModuleFileName(NULL,buf,512);
		_tcsrchr(buf,'\\')[1] = 0;
		strcat(buf,"Trunks\\");
		strcat(buf,trunk_dir.str().c_str());//trunk_dirΪ���·�����������Ա�֤portable
		if(!NPRemoveFileOrDir(buf))
		{
			NPLogError(("�Ƴ�ʧ��trunk:%s\n",buf));
			return -1;
		}
	}		
	
	//ɾ����Ӧ���ݿ��¼ 
	if( sqlite3_exec(m_db, sql_del.c_str(), 0, 0, &zErrMsg)!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("ʧ��:%s\n:%s��\n",__FUNCTION__,zErrMsg));
		sqlite3_free(zErrMsg);
		return -1;
	}
	
	return 0;
}
int CTrunkManage::ListTrunk(tcps_Array<tcps_String>& trunks )
{
	CNPAutoLock lok(m_lock_db);
	std::string sql_query = "select trunk_name from PCC_TRUNKS ";
	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.c_str(),sql_query.length(),&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("ʧ�ܣ�:%s\n",__FUNCTION__));
		return -1;
	}
	
	while(sqlite3_step(st_query)== SQLITE_ROW)
	{
		trunks.Resize(trunks.Length()+1);
		trunks[trunks.Length()-1].Assign((const char *)sqlite3_column_text(st_query,0));
	}
	sqlite3_finalize(st_query);  
	return 0;
}
int CTrunkManage::AddAuthCenter(const tcps_String& trunk,const PCC_Tag& authTag,const tcps_Array<PCC_ModuleFile>& files)
{ 
	CNPAutoLock lok(m_lock_db);
	//���ж�trunk�Ƿ����
	std::string sql_query = "select id_trunk from PCC_TRUNKS where trunk_name='"+std::string(trunk.Get())+"'";
	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.c_str(),sql_query.length(),&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("ʧ�ܣ�:%s\n",__FUNCTION__));
		return -1;
	}
	
	if(sqlite3_step(st_query) != SQLITE_ROW)
	{
		NPLogError(("%s������trunk:%s��\n",__FUNCTION__,trunk));  
		return -1;
		//trunks.Resize(trunks.Length()+1);
		//trunks[trunks.Length()].Assign((const char *)sqlite3_column_text(st_query,0));
	}
	//verify PCC_TRUNK_MODULES the record  has exised

	//
	std::stringstream mod_name ;
	mod_name<<authTag.name.Get()<<"_"<<authTag.version.major<<"_"<<authTag.version.minor;
	//_s ����Ŀ¼������ģ���ļ�
	char buf[512];
	GetModuleFileName(NULL,buf,512);
	_tcsrchr(buf,'\\')[1] = 0;
	strcat(buf,"Trunks\\");
	strcat(buf,trunk.Get());//
	strcat(buf,"\\");//
	strcat(buf,mod_name.str().c_str());
	strcat(buf,"\\");//xxx\xxx\...\xx\  //
	if(!CreatePath(buf))//�Ѵ��ڣ���Ҳ����TRUE
	{
		NPLogError(("����TrunksĿ¼ʧ��:%s\n",mod_name.str().c_str()));
		return -1;
	}
	//����Ӧ���ж��Ƿ���Ȩ����ģ�飩�Ѿ����ڣ�����˵�ļ��Ƿ�ɸ���
	std::string entry_name;
	for (int i=0;i<files.Length();++i)
	{
		CFileStorage fs;
		if(files[i].entry)
			entry_name = files[i].name.Get();
		strcat(buf,files[i].name.Get());
		fs.Open(buf,CFileStorage::fs_create_always);
		fs.Write(0,files[i].data.Get(),files[i].data.Length());
		fs.Close();
		_tcsrchr(buf,'\\')[1] = 0;
	}
	//������Ȩ���� ��Ҫ����Ľṹ��ӳ��ģ�鼰����Ȩ���� 
    //��ʱ�򵥴���������
	std::stringstream auth_exe;
	//auth_exe<<authTag.name.Get()<<".exe -port"<< m_auth_mng.generatePort();//3000;//todoǱ�ڵĶ˿ڳ�ͻ������� ����srand
	auth_exe<<buf<<entry_name/*authTag.name.Get()<<".exe "*/;//-port"<< m_auth_mng.generatePort();//3000;//todoǱ�ڵĶ˿ڳ�ͻ������� ����srand
	//strcat(buf,auth_exe.str().c_str());
	if(entry_name.empty())
	{
		NPLogError(("%s,�޷��ҵ���Ȩ���������EXE!\n",__FUNCTION__));
		return -1;
	}
	if(m_auth_mng.startAuth(trunk.Get(),auth_exe.str())<0)
	{	
		NPLogError(("%s,������Ȩ����ʧ�ܣ�\n",__FUNCTION__));
		//return -1;
	}
	//_e
	int id = sqlite3_column_int(st_query,0);
	sqlite3_finalize(st_query);  
	
	std::stringstream sql_insert ;
	//type = 0 ��Ȩģ�� oth �㷨ģ��

	//14/1/10 9:24//module_path�����پ���path�����壬path��trunk_name+module_name �Ƶ���
	sql_insert<<"insert into  PCC_TRUNK_MODULES(id_tk,module_name,type,module_path)\
		values("<<id<<",'"<<mod_name.str()<<"',"<<0<<",'"<<entry_name<<"')";
	char *zErrMsg = 0;
	if( sqlite3_exec(m_db, sql_insert.str().c_str(), 0, 0, &zErrMsg)!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("%s,���ݲ���ʧ��:%s��\n",__FUNCTION__,zErrMsg));
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;

}
int CTrunkManage::RemoveAuthCenter(const tcps_String& trunk,const PCC_Tag& authTag)
{
	CNPAutoLock lok(m_lock_db);
	//���ж�trunk�Ƿ����
	std::string sql_query = "select id_trunk from PCC_TRUNKS where trunk_name="+std::string(trunk.Get());
	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.c_str(),sql_query.length(),&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%s,ʧ�ܣ�\n",__FUNCTION__));
		return -1;
	}
	
	if(sqlite3_step(st_query) != SQLITE_ROW)
	{
		NPLogError(("������trunk:%s��\n",trunk));  
		return -1;
		//trunks.Resize(trunks.Length()+1);
		//trunks[trunks.Length()].Assign((const char *)sqlite3_column_text(st_query,0));
	}
	int id = sqlite3_column_int(st_query,0);
	sqlite3_finalize(st_query);  

	std::stringstream sql_del ;
	sql_del<<"delete from PCC_TRUNK_MODULES where type=0 and id_tk="<<id<<" and module_name='"
		<<authTag.name.Get()<<"_"<<authTag.version.major<<"_"<<authTag.version.minor<<"'";
	char *zErrMsg = 0;
	if( sqlite3_exec(m_db, sql_del.str().c_str(), 0, 0, &zErrMsg)!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("%s,ʧ��:%s��\n",__FUNCTION__,zErrMsg));
		sqlite3_free(zErrMsg);
		return -1;
	}

	char buf[512];
	GetModuleFileName(NULL,buf,512);
	_tcsrchr(buf,'\\')[1] = 0;
	strcat(buf,"Trunks\\");
	std::stringstream trunk_dir;
	trunk_dir<<"\\"<<trunk.Get()<<"\\"<<authTag.name.Get()<<"_"<<authTag.version.major<<"_"<<authTag.version.minor;
	strcat(buf,trunk_dir.str().c_str());//trunk_dirΪ���·�����������Ա�֤portable
	if(!NPRemoveFileOrDir(buf))
	{
		NPLogError(("�Ƴ�ʧ��trunk:%s\n",buf));
		return -1;
	}
	//NPRemoveFileOrDir();
	return 0;

}
//�˺����� FindAuthCenter�Ĳ�� ?Ӧ������ const tcps_String& trunk 
int CTrunkManage::ListAuthCenter(const tcps_String& trunk,tcps_Array<PCC_Tag>& authTags)
{
	CNPAutoLock lok(m_lock_db);
	std::stringstream sql_query;
	sql_query<<"select module_name  from PCC_TRUNK_MODULES as a left join PCC_TRUNKS as b on a.id_tk=b.id_trunk where type=0 ";
		//<<trunk.Get()<<"'";

	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.str().c_str(),-1,&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%s,ʧ�ܣ�\n",__FUNCTION__));
		return -1;
	}
	while(sqlite3_step(st_query) == SQLITE_ROW)
	{
		const unsigned char *result = sqlite3_column_text(st_query,0);
		std::stringstream mod;
		mod << result;
		CSmartArray<tstring> modNamVer;
		StrSeparater_Sep(mod.str().c_str(),"_",modNamVer);
		ASSERT(modNamVer.size()==3);
		authTags.Resize(authTags.Length()+1);

		authTags[authTags.Length()-1].name = modNamVer[0].c_str();
		authTags[authTags.Length()-1].version .major = atoi(modNamVer[1].c_str());
		authTags[authTags.Length()-1].version .minor = atoi(modNamVer[2].c_str());
	}
	sqlite3_finalize(st_query);  
	
	return 0;

}
//������������
int CTrunkManage::FindAuthCenter(const tcps_String& trunk,const PCC_Tag& authTag)
{
	CNPAutoLock lok(m_lock_db);
	std::stringstream sql_query;
	sql_query<<"select module_name  from PCC_TRUNK_MODULES as a left join PCC_TRUNKS as b on a.id_tk=b.id_trunk where type=0 and trunk_name = '"
		<<trunk.Get()<<"'";

	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.str().c_str(),-1,&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%s,ʧ�ܣ�\n",__FUNCTION__));
		return -1;
	}
	
	if(sqlite3_step(st_query) != SQLITE_ROW)
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%s,�����ڣ�\n",__FUNCTION__));  
		return -1;
	}
	const unsigned char *result = sqlite3_column_text(st_query,0);
	std::stringstream mod;
	mod << result;
	CSmartArray<tstring> modNamVer;
	StrSeparater_Sep(mod.str().c_str(),"_",modNamVer);
	ASSERT(modNamVer.size()==3);

	//authTag.name = modNamVer[0].c_str();
	//authTag.version .major = atoi(modNamVer[1].c_str());
	//authTag.version .minor = atoi(modNamVer[2].c_str());

	sqlite3_finalize(st_query);  
	return 0;
}
//ֻ����pccģ������
int CTrunkManage::AddModule(const tcps_String& trunk,const PCC_ModuleProperty& moduleProperty
			  ,const tcps_Array<PCC_ModuleFile>& moudleFiles,INT64& moduleKey)
{
	//ASSERT(moduleProperty.moduleType);
	int ty =moduleProperty.moduleType;

	CNPAutoLock lok(m_lock_db);//��δ�����Էֶμ������Ż�����ʱ�򻯴���
	//���ж�trunk�Ƿ����
	std::string sql_query = "select id_trunk from PCC_TRUNKS where trunk_name='"+std::string(trunk.Get())+"'";
	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.c_str(),sql_query.length(),&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%s,ʧ�ܣ�\n",__FUNCTION__));
		return -1;
	}
	
	if(sqlite3_step(st_query) != SQLITE_ROW)
	{
		NPLogError(("%s,������trunk:%s��\n",__FUNCTION__,trunk));  
		return -1;
		//trunks.Resize(trunks.Length()+1);
		//trunks[trunks.Length()].Assign((const char *)sqlite3_column_text(st_query,0));
	}
	//verify PCC_TRUNK_MODULES the record  has exised

	//
	std::stringstream mod_name ;
	mod_name<<moduleProperty.moduleTag.name.Get()<<"_"<<moduleProperty.moduleTag.version.major<<"_"<<moduleProperty.moduleTag.version.minor;
	if(moduleProperty.moduleType != PCC_MODULE_VIDSTRUCTURE)//������㷨��
	{
		
		//_s ����Ŀ¼������ģ���ļ�
		char buf[512];
		GetModuleFileName(NULL,buf,512);
		_tcsrchr(buf,'\\')[1] = 0;
		strcat(buf,"Trunks\\");
		strcat(buf,trunk.Get());//
		strcat(buf,"\\");//
		strcat(buf,mod_name.str().c_str());
		strcat(buf,"\\");//xxx\xxx\...\xx\  //
		if(!CreatePath(buf))//�Ѵ��ڣ���Ҳ����TRUE
		{
			NPLogError(("����TrunksĿ¼ʧ��:%s\n",mod_name.str().c_str()));
			return -1;
		}
		for (int i=0;i<moudleFiles.Length();++i)
		{
			CFileStorage fs;
			strcat(buf,moudleFiles[i].name.Get());
			fs.Open(buf,CFileStorage::fs_create_always);
			fs.Write(0,moudleFiles[i].data.Get(),moudleFiles[i].data.Length());
			fs.Close();
			_tcsrchr(buf,'\\')[1] = 0;
		}
		//_e
	}
	int id = sqlite3_column_int(st_query,0);
	sqlite3_finalize(st_query);  
	
	std::stringstream sql_insert ;
	//type = 1 ��Ȩģ�� 0 �㷨ģ��
    sql_query ="select max(seq) from sqlite_sequence where name = 'PCC_TRUNK_MODULES'";
	//sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.c_str(),sql_query.length(),&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%s,ʧ�ܣ�\n",__FUNCTION__));
		return -1;
	}
	
	if(sqlite3_step(st_query) != SQLITE_ROW)
	{
		NPLogError(("%s,����ģ��keyʧ�ܣ�\n",__FUNCTION__));  
		return -1;
		//trunks.Resize(trunks.Length()+1);
		//trunks[trunks.Length()].Assign((const char *)sqlite3_column_text(st_query,0));
	}

	moduleKey = sqlite3_column_int(st_query,0)+1;
	sqlite3_finalize(st_query);  
	

	sql_insert<<"insert into  PCC_TRUNK_MODULES(id_tk,module_name,type,module_path)\
		values("<<id<<",'"<<mod_name.str()<<"',"<<ty<<",'"<<mod_name.str()<<"')";
	char *zErrMsg = 0;
	if( sqlite3_exec(m_db, sql_insert.str().c_str(), 0, 0, &zErrMsg)!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("%s,ʧ��:%s��\n",__FUNCTION__,zErrMsg));
		sqlite3_free(zErrMsg);
		return -1;
	}

	return 0;
}
int CTrunkManage::AddModuleFile(const tcps_String& trunk,INT64 moduleKey
				  ,PCC_ModuleFileType fileType,const tcps_Array<PCC_ModuleFile>& moduleFiles)
{
	CNPAutoLock lok(m_lock_db);

	return 0;
}
int CTrunkManage::RemoveModule(const tcps_String& trunk,INT64 moduleKey/*,MY_NP_GridUserClient &m_gridConn*/)
{
	CNPAutoLock lok(m_lock_db);
	//���ж�trunk�Ƿ����
	std::string sql_query = "select id_trunk from PCC_TRUNKS where trunk_name='"+std::string(trunk.Get())+"'";
	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.c_str(),sql_query.length(),&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%s,ʧ�ܣ�\n",__FUNCTION__));
		return -1;
	}
	
	if(sqlite3_step(st_query) != SQLITE_ROW)
	{
		NPLogError(("%s,������trunk:%s��\n",__FUNCTION__,trunk));  
		return -1;
		//trunks.Resize(trunks.Length()+1);
		//trunks[trunks.Length()].Assign((const char *)sqlite3_column_text(st_query,0));
	}
	int trunk_id = sqlite3_column_int(st_query,0);
	sqlite3_finalize(st_query);  

	std::stringstream sql_if;
	sql_if<<" select module_name ,type from PCC_TRUNK_MODULES as a left join PCC_TRUNKS as b on a.id_tk=b.id_trunk where id_module="
		<<moduleKey;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_if.str().c_str(),sql_if.str().length(),&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%sʧ�ܣ�\n",__FUNCTION__));
		return -1;
	}
	
	if(sqlite3_step(st_query) != SQLITE_ROW)
	{
		NPLogError(("%s,��ȡģ����Ϣʧ�ܣ�\n",__FUNCTION__));  
		return -1;
		//trunks.Resize(trunks.Length()+1);
		//trunks[trunks.Length()].Assign((const char *)sqlite3_column_text(st_query,0));
	}

    const unsigned char *result = sqlite3_column_text(st_query,0);//module_name
	std::stringstream mod;
	mod << result;
	int ty = sqlite3_column_int(st_query,1);	
	sqlite3_finalize(st_query);  

	std::stringstream sql_del ;
	sql_del<<"delete from PCC_TRUNK_MODULES where id_tk="<<trunk_id<<" and id_module="
		<<moduleKey;
	char *zErrMsg = 0;
	if( sqlite3_exec(m_db, sql_del.str().c_str(), 0, 0, &zErrMsg)!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("%s,ʧ��:%s��\n",__FUNCTION__,zErrMsg));
		sqlite3_free(zErrMsg);
		return -1;
	}
	if((ty&4)==0)//pcc��ģ��
	{
		char buf[512];
		GetModuleFileName(NULL,buf,512);
		_tcsrchr(buf,'\\')[1] = 0;
		strcat(buf,"Trunks\\");
		std::stringstream trunk_dir;
		trunk_dir<<"\\"<<trunk.Get()<<"\\"<<mod.str();//authTag.name.Get()<<"_"<<authTag.version.major<<"_"<<authTag.version.minor;
		strcat(buf,trunk_dir.str().c_str());//trunk_dirΪ���·�����������Ա�֤portable
		if(!NPRemoveFileOrDir(buf))
		{
			NPLogError(("�Ƴ�ʧ��trunk:%s\n",buf));
			return -1;
		}
	}
	else
	{/*
		
			moduleKey = -1;//��ʼ��
			tcps_Array<GRID_User_T::JobProgram> progInfos;
			if( TCPS_OK == m_gridConn.ListJobPrograms(progInfos))
			{
				CSmartArray<tstring> modNamVer;
				StrSeparater_Sep(mod.str().c_str(),"_",modNamVer);
				ASSERT(modNamVer.size()==3);
				for(int i=0;i< progInfos.Length();++i)
				{
					if(progInfos[i].programInfo.programID.name == modNamVer[0].c_str() &&
						progInfos[i].programInfo.programID.ver.majorVer == atoi(modNamVer[1].c_str()) &&
						progInfos[i].programInfo.programID.ver.minorVer == atoi(modNamVer[2].c_str()) )
					{
						moduleKey = progInfos[i].programKey;
						assert(moduleKey < BASE_ID);
						break;
					}
				}
				assert(moduleKey > -1);
				tcps_Array<INT64> delProId;
				delProId.Resize(1);
				delProId[0] = moduleKey;
				return (int)m_gridConn.DelJobProgram(delProId);
			}*/
			return -1;
		
	}
	return 0;
}
int CTrunkManage::RemoveModuleFiles(const tcps_String& trunk,INT64 moduleKey,INT32 fileType)
{
	CNPAutoLock lok(m_lock_db);

	return 0;
}
int CTrunkManage::ListModules(const tcps_String& trunk,tcps_Array<PCC_ModulePropWithKey>& modulesInfo)
{
	CNPAutoLock lok(m_lock_db);
	std::stringstream sql_query;
	sql_query<<"select id_module,module_name,type from PCC_TRUNK_MODULES as a left join PCC_TRUNKS as b on a.id_tk=b.id_trunk and a.type!=0 where  trunk_name='"
		<<trunk.Get()<<"'";

	sqlite3_stmt* st_query;
	if (SQLITE_OK !=sqlite3_prepare_v2(m_db,sql_query.str().c_str(),-1,&st_query,NULL))
	{
		sqlite3_finalize(st_query);  
		NPLogError(("%s,ʧ�ܣ�\n",__FUNCTION__));
		return -1;
	}
	while(sqlite3_step(st_query) == SQLITE_ROW)
	{
		int key = sqlite3_column_int(st_query,0);
		const unsigned char *result = sqlite3_column_text(st_query,1);
		int ty = sqlite3_column_int(st_query,2);
		std::stringstream mod;
		mod << result;

		CSmartArray<tstring> modNamVer;
		StrSeparater_Sep(mod.str().c_str(),"_",modNamVer);
		ASSERT(modNamVer.size()==3);
		modulesInfo.Resize(modulesInfo.Length()+1);
		modulesInfo[modulesInfo.Length()-1].key =key;
		modulesInfo[modulesInfo.Length()-1].prop.moduleTag.name = modNamVer[0].c_str();
		modulesInfo[modulesInfo.Length()-1].prop.moduleTag.version .major = atoi(modNamVer[1].c_str());
		modulesInfo[modulesInfo.Length()-1].prop.moduleTag.version .minor = atoi(modNamVer[2].c_str());
		modulesInfo[modulesInfo.Length()-1].prop.moduleType = ty;
	}
	sqlite3_finalize(st_query);  
	return 0;
}

///////////////////////////////CNPDeploy////////////////////////////////////////////////
CNPDeploy::CNPDeploy()
{
}
CNPDeploy::~CNPDeploy()
{

}
TCPSError CNPDeploy::OnConnected(
					  IN INT32 sessionKey,
					  IN const IPP& peerID_IPP,
					  IN INT32 sessionCount
					  )
{
	m_client_ipp = peerID_IPP;
	return TCPS_OK;
}
void CNPDeploy::OnClose(
						IN INT32 sessionKey,
						IN const IPP& peerID_IPP,
						IN TCPSError cause
						)
{
	//m_gridConn.SetServeIPP(INVALID_IPP);
}

TCPSError CNPDeploy::Login(
				IN const tcps_String& ticket
				) 
{
//m_gridConn.m_user = "netposa";
//m_gridConn.m_pass = "netposa";
//
//IPP serverIPP;
//
//serverIPP.ip_ = GetLocalIP();//inet_addr("127.0.0.1");//���ӱ���
//serverIPP.port_ = 9012;
//m_gridConn.m_service = NULL;
//return m_gridConn.SetServeIPP(serverIPP,0,m_client_ipp);//
	return TCPS_OK;
}

TCPSError CNPDeploy::Logout(
				 )
{
	//return m_gridConn.Logout();
	return TCPS_OK;
}

TCPSError CNPDeploy::CreateTrunk(const tcps_String& trunk) 
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().CreateTrunk(trunk);
}
TCPSError CNPDeploy::RemoveTrunk(const tcps_String& trunk) 
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().RemoveTrunk(trunk);
}
TCPSError CNPDeploy::ListTrunk(tcps_Array<tcps_String>& trunks )
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().ListTrunk(trunks);
}
TCPSError CNPDeploy::AddAuthCenter(const tcps_String& trunk,const PCC_Tag& authTag,const tcps_Array<PCC_ModuleFile>& files)
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().AddAuthCenter(trunk,authTag,files);
}
TCPSError CNPDeploy::RemoveAuthCenter(const tcps_String& trunk,const PCC_Tag& authTag)
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().RemoveAuthCenter(trunk,authTag);
}
TCPSError CNPDeploy::ListAuthCenter(const tcps_String& trunk,tcps_Array<PCC_Tag>& authTags) 
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().ListAuthCenter(trunk,authTags);
}
TCPSError CNPDeploy::FindAuthCenter(const tcps_String& trunk,const PCC_Tag& authTag)
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().FindAuthCenter(trunk,authTag);
}
TCPSError CNPDeploy::AddModule(const tcps_String& trunk,const PCC_ModuleProperty& moduleProperty,const tcps_Array<PCC_ModuleFile>& moudleFiles,INT64& moduleKey)
{
	if(pgrid_util::Singleton<CTrunkManage>::instance().AddModule(trunk,moduleProperty,moudleFiles,moduleKey)==-1)
		return TCPS_ERROR;
    if (moduleProperty.moduleType == PCC_MODULE_VIDSTRUCTURE)//
	{/*

		GRID_ProgramInfo progInfo;
		progInfo.programID.name = moduleProperty.moduleTag.name;
		progInfo.programID.ver.majorVer = moduleProperty.moduleTag.version.major;
		progInfo.programID.ver.minorVer = moduleProperty.moduleTag.version.minor;


		progInfo.programID.cpuType = (GRID_CPUType )0;// cpu_x86_x64;
		progInfo.programID.osType = ost_Windows_7;//ost_Unknown;
		progInfo.programID.executeBits = (GRID_ExecuteBits )32;//eb_32bits;
		progInfo.programID.binaryType =(GRID_BinaryType )0;//bt_machineRaw; 



		tcps_Array<GRID_ProgramFile> files;
		files.Resize(moudleFiles.Length());
		for(int i=0;i<moudleFiles.Length();++i)
		{
			files[i].name = moudleFiles[i].name;
			files[i].isExecutable = FALSE;
			files[i].data = moudleFiles[i].data;//�������ƿ���
		}
		if( TCPS_OK == m_gridConn.AddJobProgram(progInfo, files))//�����ڲ�������һ��id��
		{
			moduleKey = -1;//��ʼ��
			tcps_Array<GRID_User_T::JobProgram> progInfos;
			if( TCPS_OK == m_gridConn.ListJobPrograms(progInfos))
			{
				for(int i=0;i< progInfos.Length();++i)
				{
					if(progInfos[i].programInfo.programID.name == progInfo.programID.name &&
						progInfos[i].programInfo.programID.ver.majorVer == progInfo.programID.ver.majorVer &&
						progInfos[i].programInfo.programID.ver.minorVer == progInfo.programID.ver.minorVer )
					{
						moduleKey = progInfos[i].programKey;
						assert(moduleKey < BASE_ID);
						break;
					}
				}
				assert(moduleKey > -1);
				return TCPS_OK ;
			}
			return TCPS_ERROR;
		}*/
	}

	return  TCPS_OK ;
}
TCPSError CNPDeploy::AddModuleFile(const tcps_String& trunk,INT64 moduleKey,PCC_ModuleFileType fileType,const tcps_Array<PCC_ModuleFile>& moduleFiles)
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().AddModuleFile(trunk,moduleKey,fileType,moduleFiles);
}
TCPSError CNPDeploy::RemoveModule(const tcps_String& trunk,INT64 moduleKey)
{
	return (TCPSError) pgrid_util::Singleton<CTrunkManage>::instance().RemoveModule(trunk,moduleKey/*,m_gridConn*/);
}
TCPSError CNPDeploy::RemoveModuleFiles(const tcps_String& trunk,INT64 moduleKey,INT32 fileType)
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().RemoveModuleFiles(trunk,moduleKey,fileType);
}
TCPSError CNPDeploy::ListModules(const tcps_String& trunk,tcps_Array<PCC_ModulePropWithKey>& modulesInfo)
{
	return (TCPSError)pgrid_util::Singleton<CTrunkManage>::instance().ListModules(trunk,modulesInfo);
}