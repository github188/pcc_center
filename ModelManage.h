#pragma once
#include "sqlite3.h"
#include "Ilocker.h"
#include"tcps_serve.h"

class CModelManage
{
public:
	CModelManage(void);
	~CModelManage(void);
    int init();


private:
	static const std::string m_ModelsSql;
private:
	sqlite3 *m_db;
	CLocker m_lock_db;
};
