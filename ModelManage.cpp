#include "StdAfx.h"
#include "ModelManage.h"


const std::string CModelManage::m_ModelsSql("CREATE TABLE IF NOT EXISTS Models \
										   (id_mod INTEGER  AUTOINCREMENT, name_mod TEXT NOT NULL unique, ver_mod TEXT NOT NULL,PRIMARY KEY(name_mod,ver_mod))"); 
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