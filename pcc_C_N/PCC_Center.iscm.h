



#include "PCC_Types.iscm.h"
interface PCC_Center
{
  

    
   	posting callback AddModelCenter (IN IPP centerIPP);


	posting callback DelModelCenter (IN IPP centerIPP);


	/// 获取静态运行环境(JobCenter --> JobTerminalManager)
	/// @staticContext[out] 静态运行环境信息
	cacheable callback GetStaticContext (OUT PCC_NodeDesc staticContext);


	/// 获取动态运行环境(JobCenter --> JobTerminalManager)
	/// @dynamicContext[out] 动态运行环境信息
	callback GetDynamicContext (OUT PCC_DynamicContext dynamicContext);


	callback AddModel (IN PCC_ModelProperty moduleProperty, IN array<PCC_ModelFile> modelFiles);


	
	///callback DelModel (IN INT64 modelKey);
	callback DelModel (IN PCC_Tag tag);

};
