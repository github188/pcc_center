#pragma once
#include "sqlite3.h"
#include "Ilocker.h"
#include"tcps_serve.h"
#include "pcc_centertypesdefine.h"
#include <map>
#include "ilocker.h"
class CModelManage
{
public:
	struct nwProcessInfo
	{
		int port;
		int pid;
		char filepath[512];
	};

public:
	CModelManage(void);
	~CModelManage(void);
    int init();
TCPSError AddModel(
				 const PCC_ModelProperty& modelProperty,
				 const tcps_Array<PCC_ModelFile>& modelFiles,
				 const tcps_String&ipp_str
				); 


TCPSError ListModels(
				 tcps_Array<PCC_ModelPropWithKey>& modelsInfo
				); 

TCPSError DelModel(
				 const PCC_Tag& tag
				); 

private:
	BOOL FindExe (const char *searchDir,tcps_String& exefile);
	int generatePort()
	{
		static int port =9100;
		CNPAutoLock lock(m_lock_port);
		return ++port;
	}
	TCPSError StartXNode(const PCC_Tag& tag,const char *path,const tcps_String&ipp_str);
				 

private:
	static const std::string m_ModelsSql;
private:
	sqlite3 *m_db;
	CLocker m_lock_db;
	CLocker m_lock_port;

	std::map<PCC_Tag,nwProcessInfo> m_xnode_processes;
	CLocker m_lock_xnode;


};
