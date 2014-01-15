#include "StdAfx.h"
#include "NodeManage.h"

CNodeManage::CNodeManage()
{

}

CNodeManage::~CNodeManage()
{

}
void CNodeManage::GetPccProperty(
								 PCCProperty & pccProp
				)
{

	pccProp.version="1.0";
}

TCPSError CNodeManage::ListNodes(tcps_Array<NodeDesc>& nodes)
{

		CNPAutoLock lock(m_lock_nodes);
		nodes.Resize(m_nodes.size());
		int i=0;
		char buf[64];
		std::map<INT32,PCC_Center_S*>::const_iterator it;
		for (it = m_nodes.begin();it!=m_nodes.end();++it)
		{
			it->second->GetStaticContext(nodes[i]);
			nodes[i].name = itoa(it->second->m_skey,buf,10);
			++i;
		}
		return TCPS_OK;
}

TCPSError CNodeManage::GetNodeDynamicContext(const tcps_String& nodeName, DynamicContext& dynamicContext) 
{
	CNPAutoLock lock(m_lock_nodes);
	std::map<INT32,PCC_Center_S*>::const_iterator it = m_nodes.find(atoi(nodeName.Get()));
	if(it !=m_nodes.end())
	{
		it->second->GetDynamicContext(dynamicContext);
		return TCPS_OK;
	}
	return TCPS_ERROR;
}