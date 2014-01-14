#include "StdAfx.h"
#include "NodeManage.h"

CNodeManage::CNodeManage()
{

}

CNodeManage::~CNodeManage()
{

}
void CNodeManage::GetPccProperty(
								 PCC_Center_T::PCCProperty & pccProp
				)
{

	pccProp.version="1.0";
}

TCPSError CNodeManage::ListNodes(tcps_Array<PCC_Center_T::NodeDesc>& nodes)
{

		CNPAutoLock lock(m_lock_nodes);
		nodes.Resize(m_nodes.size());
		int i=0;
		std::map<INT32,PCC_Center_S*>::const_iterator it;
		for (it = m_nodes.begin();it!=m_nodes.end();++it)
		{
			it->second->GetStaticContext(nodes[i]);
			++i;
		}
		return TCPS_OK;
}