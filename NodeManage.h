#pragma once

#include "pcc_centersession.h"
#include "nplog.h"
//#include "tcps_err.h"
class CNodeManage//:public boost::enable_shared_from_this<CModuleManage>
{
public:
typedef std::map<INT64,/*PCC_ModuleInfo*/PCC_Center_T::PCC_ModelProperty>::const_iterator MNG_IT;


public:
	CNodeManage(void);
	~CNodeManage(void);


	bool find(INT64 key,PCC_Center_T::PCC_ModelProperty &info)
	{
		CNPAutoLock lok(m_lock_map);//必须加锁，否则it可能失效
		MNG_IT it = m_models.find(key);
		if(it != m_models.end())
		{
             info = it->second;
			 return true;
		}
		return false;
	}

	bool insert(std::pair<INT64,PCC_Center_T::PCC_ModelProperty> const &  val)
	{
		CNPAutoLock lok(m_lock_map);
		std::map<INT64,PCC_Center_T::PCC_ModelProperty>::_Pairib rt = m_models.insert(val);
		return rt.second;

	}
   

	TCPSError ListModels(
		OUT tcps_Array<PCC_Center_T::PCC_ModelPropWithKey>& m_modelsInfo
		) 
	{
		CNPAutoLock lok(m_lock_map);
		m_modelsInfo.Resize(m_models.size());
		int k= 0;
		for(MNG_IT it = m_models.begin();it!= m_models.end();++it)
		{

			m_modelsInfo[k].key = it->first;
			m_modelsInfo[k].prop= it->second;
			//m_modelsInfo[k].prop.moduleTag.name=it->second.moduleTag.name;
			++k;
		}
		return TCPS_OK;
	}

	TCPSError RemoveModel(
		IN INT64 modelKey
		) 
	{
		CNPAutoLock lok(m_lock_map);
		
		if(!m_models.erase(modelKey))
		{
			NPLogError(("找不到#%d#对应的模块",modelKey));
		}
		return TCPS_OK;
	}

	void pushNode(INT32 key,PCC_Center_S* nd)
	{
		CNPAutoLock lock(m_lock_nodes);
		//nd->m_jobkey = -1;//重置
		std::map<INT32,PCC_Center_S*> ::_Pairib rt= m_nodes.insert(std::make_pair(key,nd));
		ASSERT(rt.second);
		{
			NPLogInfo(("pushNode#当前节点数:%d\n",m_nodes.size()));
		}
	}

	
	void diableNode(INT32 key)
	{
        CNPAutoLock lock(m_lock_nodes);
		m_nodes.erase(key);
	}
    int getNodeCounts()
	{
		CNPAutoLock lock(m_lock_nodes);
		return m_nodes.size();
	}
	
	


	
public:
	void GetPccProperty(
		PCC_Center_T::PCCProperty & pccProp
				);
	TCPSError ListNodes(tcps_Array<PCC_Center_T::NodeDesc>& nodes);
//	void init();
//	BOOL RegisterModules (const char *moduleDir);
//	BOOL CopyModules (const char *moduleDir,tcps_Array<PCC_ModuleFile> &moudleFiles);
//	BOOL CNodeManage::GridModules();
private:
//	OSThread m_threadID;

private:
	CLocker m_lock_map;
//	CLocker m_lock2;//scatter队列的锁
	std::map<INT64,/*PCC_ModuleInfo*/PCC_Center_T::PCC_ModelProperty> m_models;
public:    
	//INT64 m_lastkey;
    //INT64 m_jobkey;

private:
	std::map<INT32,PCC_Center_S*> m_nodes;//iscm会保证这个指针的有效性
	CLocker m_lock_nodes;
	//std::map<INT64,PCC_Service_S*> m_job_service;//service提交作业，待处理的会话
	//CLocker m_locker_job_service;
private:
	//std::queue<SCJob> m_jobs;
	CLocker m_lock_job;
	//MY_NP_GridUserClient m_gridConn;//建立到网格的连接
};