



#include "PCC_Types.iscm.h"
interface PCC_Center
{
  

    
   	posting callback AddModelCenter (IN IPP centerIPP);


	posting callback DelModelCenter (IN IPP centerIPP);


	/// ��ȡ��̬���л���(JobCenter --> JobTerminalManager)
	/// @staticContext[out] ��̬���л�����Ϣ
	cacheable callback GetStaticContext (OUT PCC_NodeDesc staticContext);


	/// ��ȡ��̬���л���(JobCenter --> JobTerminalManager)
	/// @dynamicContext[out] ��̬���л�����Ϣ
	callback GetDynamicContext (OUT PCC_DynamicContext dynamicContext);


	callback AddModel (IN PCC_ModelProperty moduleProperty, IN array<PCC_ModelFile> modelFiles);


	
	///callback DelModel (IN INT64 modelKey);
	callback DelModel (IN PCC_Tag tag);

};
