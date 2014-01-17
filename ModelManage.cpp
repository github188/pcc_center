#include "StdAfx.h"
#include "ModelManage.h"
#include "npfdk.h"
#include "nplog.h"
#include <sstream>
#include "filestorage.h"
#include "smlib.h"
#include "strtmpl.h"
#include "singleton.h"
#include "ipcvt.h"
#include "np_gridutils.h"
#include "nodemanage.h"
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

	if(!CreatePath(buf))//已存在，则也返回TRUE
	{
		NPLogError(("创建Models目录失败！\n"));
		return -1;
	};
	
	int rc;
	strcat(buf,"/Models.db");
	rc = sqlite3_open(buf, &m_db);
	if( rc )
	{
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		NPLogError(("打开Models数据库失败:%s！\n",sqlite3_errmsg(m_db)));
		sqlite3_close(m_db);
		return -1;
	}
	
	
	//初始化数据库
	char *zErrMsg = 0;
	rc = sqlite3_exec(m_db, CModelManage::m_ModelsSql.c_str(), 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("创建表失败:%s！\n",zErrMsg));
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
	
}
//modelFiles中为压缩文件
TCPSError CModelManage::AddModel(
				 const PCC_ModelProperty& modelProperty,
				 const tcps_Array<PCC_ModelFile>& modelFiles
				) 
{
	//注意异常判断：例如C无法启动
	//原则应根据配置启动多少个节点 默认部署当前全部节点（考虑弹性增加？）
	//NP_GridFUnpack (const char* packedFile, const char* unpackPath, NP_GridFPackProgress progress);
	//std::string sql ="insert into PCC_TRUNKS(trunk_name,trunk_path) values('"+std::string(trunk.Get())+"','"+std::string(trunk.Get())+"')";
	std::stringstream insert_sql,ver_str;
	ver_str<<modelProperty.modelTag.version.major<<"."<<modelProperty.modelTag.version.minor;
	insert_sql<<"insert into Models(name_mod,ver_mod) values('"
		<<modelProperty.modelTag.name.Get()<<"','"<<ver_str.str()<<"')";
#define INSNW 0
#ifndef INSNW
	char *zErrMsg = 0;
	if( sqlite3_exec(m_db, insert_sql.str().c_str(), 0, 0, &zErrMsg)!=SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		NPLogError(("创建表失败:%s\n:%s！\n",__FUNCTION__,zErrMsg));
		sqlite3_free(zErrMsg);
		return TCPS_ERROR;
	}
#endif
	std::stringstream unpackPath;
	char buf[512];
	GetModuleFileName(NULL,buf,512);
	_tcsrchr(buf,'\\')[1] = 0;
	strcat(buf,"Models\\");
	
	unpackPath<<modelProperty.modelTag.name.Get()<<"-"<<ver_str.str()<<"\\";//"temp";
	strcat(buf,unpackPath.str().c_str());
	//temp目录
	//移除旧版的文件，移除前要发送消息，终断服务端程序及客户端的执行，然后移除文件,待完善
	NPRemoveFileOrDir(buf);
	if(!CreatePath(buf))//已存在，则也返回TRUE
	{
		NPLogError(("创建目录失败！:%s\n",buf));
		return TCPS_ERROR;
	};
	unpackPath.str("");
	unpackPath.clear();
	unpackPath<<buf;
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
		//移除文件
		NPRemoveFileOrDir(buf);
		_tcsrchr(buf,'\\')[1] = 0;
		strcat(buf,"C\\");
		//启动模型服务端程序
		tcps_String exefile;
		if(FindExe(buf,exefile))
		{
			printf("%s\n",exefile.Get());
		}
		strcat(buf,exefile.Get());

       // /models/modelname-1.x/Nxxx.pack 
		//部署model客户端部分到各节点上（默认全部） 并启动
		tcps_Array<PCC_ModelFile> modelClientFiles;
		modelClientFiles.Resize(1);
		CFileStorage fs;
		if(fs.Open("",CFileStorage::fs_read_only))//////
		{
			pgrid_util::Singleton<CNodeManage>::instance().DeployNodes(modelProperty,modelClientFiles);
		}
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
				 INT64 modelKey
				)
{
	return TCPS_OK;
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