/**
 *                                          Netposa Algorithm SDK
 *                                   (c) Copyright 2011-2013, Netposa
 *                                           All Rights Reserved
 *
 * File		: PCC_User.iscm.h
 * Author	: Zhou Guangming
 * Time		: 2014-1-13
 */


#include "PCC_Types.iscm.h"


/**
 * Description:	Define interface between user and PCC.
 */
interface PCC_User
{
public:
	/**
	 * Description:	Define PCC property type.
	 * Parameters:	version:	PCC version.
	 */
	struct PCCProperty
	{
		string version;		  
	};

public:
	/**
	 * Function:	GetPccProperty().
	 * Input:		None.
	 * Output:		pccProp:	PCC property.
	 * Return:		Error code.
	 * Description:	Get PCC property.
	 */
	method GetPccProperty (OUT PCCProperty pccProp);
	

	/**
	 * Function:	ListNodes
	 * Input:		None.
	 * Output:		nodes:	Nodes description.
	 * Return:		Error code.
	 * Description:	List all nodes in PCC.
	 */
	method ListNodes (OUT array<PCC_NodeDesc> nodes);


	/**
	 * Function:	GetNodeDynamicContext().
	 * Input:		nodeName:		Node name get by ListNodes().
	 * Output:		dynamicContext:	Output node dynamic context.
	 * Return:		Error code.
	 * Description:	Get specific node dynamic context.
	 */
	method GetNodeDynamicContext (IN string nodeName, OUT PCC_DynamicContext dynamicContext);


	/**
	 * Function:	ListModules().
	 * Input:		None.
	 * Output:		modulesInfo:	Output modules info.
	 * Return:		Error code.
	 * Description:	List all modules in PCC.
	 */
	method ListModules (IN string regex, OUT array<PCC_ModuleInfo> modulesInfo);


	/**
	 * Function:	Execute().	
	 * Input:		moduleKey:	Module uniform ID in PCC get by ListModules().
	 *				inputUrl:	Input uniform resource locator.	
	 *				outputUrl:	Output uniform resource locator.
	 *				params:		Module processing parameters.
	 * Output:		jobKey:		Output processing job uniform ID in PCC.
	 * Return:		Error code.
	 * Description:	Execute module to process input data specific by "inputUrl" in specific module, 
	 *				and output result to "outputUrl".
	 */
	method Execute (IN INT64 moduleKey, IN string inputUrl, IN string outputUrl, IN binary moduleParams, OUT INT64 jobKey);


	/**
	 * Function:	OnExecuted().
	 * Input:		jobKey:		Processing job uniform ID in PCC created by Execute().
	 *				errorCode:	Processing result.
	 *				context:	Processing context.
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Job finishes execution callback function.
	 */
	posting callback OnExecuted (IN INT64 jobKey, IN error errorCode, IN binary context);


	/**
	 * Function:	OnExecuted1().
	 * Input:		jobKey:		Processing job uniform ID in PCC created by Execute().
	 *				errorCode:	Processing result.
	 *				context:	Processing context.
	 *				outArgs:	Output arguments.
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Job finishes execution callback function.
	 */
	posting callback OnExecuted1 (IN INT64 jobKey, IN error errorCode, IN binary context, IN array<binary> outArgs);


	/**
	 * Function:	QueryJob().	
	 * Input:		jobKey:		Processing job uniform ID in PCC created by Execute().
	 * Output:		errorCode:	Processed error code.
	 *				progress:	Processed progress, 0~100.
	 * Return:		Error code.
	 * Description:	Query job processing state.
	 */
	method QueryJobs (IN array<INT64> jobsKey, OUT array<ExecuteState> jobsState);


	/**
	 * Function:	CancelJob().
	 * Input:		jobKey:	Processing job uniform ID in PCC created by Execute().
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Cancel the executing job.
	 */
	posting method CancelJob (IN INT64 jobKey);
};
