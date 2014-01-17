#include "StdAfx.h"
#include "NodeManage.h"
#include "ipcvt.h"
#include "strtmpl.h"

CFun::CFun()
{
	m_done = true;
	m_ft = unknown;
	m_param = NULL;
}
CFun::~CFun()
{
}
void CFun::setParam(void* param)
{

}
void CFun::setFunction(FUNTYPE ft)
{

}
int CFun::operator()(PCC_Center_S* ptr)
{
	return 0;
}

CNodeManage::CNodeManage()
{

}

CNodeManage::~CNodeManage()
{

}
void CNodeManage::GetPccProperty(
								 PCC_User_T::PCCProperty & pccProp
				)
{

	pccProp.version="1.0";
}

TCPSError CNodeManage::ListNodes(tcps_Array<PCC_NodeDesc>& nodes)
{
		char compute_name[128];
	    
		CNPAutoLock lock(m_lock_nodes);
		nodes.Resize(m_nodes.size());
		int i=0;
		char buf[64];
		std::map<INT32,PCC_Center_S*>::const_iterator it;
		for (it = m_nodes.begin();it!=m_nodes.end();++it)
		{
			it->second->GetStaticContext(nodes[i]);
			GetNameByIP(it->second->GetPeerIPP().ip_,compute_name);//
			strcat(compute_name,"(");
			strcat(compute_name,IPP_TO_STR_A(it->second->GetPeerIPP()));
			strcat(compute_name,")#");
			strcat(compute_name,itoa(it->second->m_skey,buf,10));
			nodes[i].name =compute_name;//itoa(it->second->m_skey,buf,10);/
			++i;
		}
		return TCPS_OK;
}

TCPSError CNodeManage::DeployNodes( const PCC_ModelProperty& modelProperty,
				 const tcps_Array<PCC_ModelFile>& modelClientFiles)
{
		CNPAutoLock lock(m_lock_nodes);
		std::map<INT32,PCC_Center_S*>::const_iterator it;
		for (it = m_nodes.begin();it!=m_nodes.end();++it)
		{
			//最好检验添加（启动）是否成功
			it->second->AddModel(modelProperty,modelClientFiles);
		}
		return TCPS_OK;
}
TCPSError CNodeManage::DoThingsOnNodes(CFun& cf)
{
		CNPAutoLock lock(m_lock_nodes);
		std::map<INT32,PCC_Center_S*>::const_iterator it;
		for (it = m_nodes.begin();it!=m_nodes.end();++it)
		{
			cf(it->second);	
		}
		return TCPS_OK;
}
TCPSError CNodeManage::GetNodeDynamicContext(const tcps_String& nodeName, PCC_DynamicContext& dynamicContext) 
{
	//解析mycompute(192.168.12.45.200) 应做更多的异常情况处理
	CSmartArray<tstring> strs;
	StrSeparater_Sep(nodeName.Get(),"#",strs);//这里改写
	int key =atoi(strs[strs.size()-1].c_str());
	CNPAutoLock lock(m_lock_nodes);
	std::map<INT32,PCC_Center_S*>::const_iterator it = m_nodes.find(key/*atoi(nodeName.Get())*/);
	if(it !=m_nodes.end())
	{
		it->second->GetDynamicContext(dynamicContext);
		return TCPS_OK;
	}
	return TCPS_ERROR;
}