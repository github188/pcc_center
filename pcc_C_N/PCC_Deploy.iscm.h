

#include "PCC_Types.iscm.h"


/**
 * Description:	Define interface for PCC deploy.
 */
interface PCC_Deploy
{
	/**
	 * Description:	Define login interfaces.
	 */
public:
	/**
	 * Function:	Login().	
	 * Input:		userName:	User name.
	 *				password:	Password.
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Login PCC.
	 */
	method Login (IN string ticket);


	/**
	 * Function:	Logout().	
	 * Input:		None.
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Logout PCC.
	 */
	method Logout ();

	/**
	 * Description:	Define directory interfaces.
	 */
public:
	/**
	 * Function:	CreateTrunk().
	 * Input:		trunk:	Trunk name.
	 * Output:		None.
	 * Return:		error code.
	 * Description:	Create trunk.
	 */
	method CreateTrunk (IN string trunk);


	/**
	 * Function:	RemoveTrunk().
	 * Input:		trunk:	Trunk name.
	 * Output:		None.
	 * Return:		error code.
	 * Description:	Remove trunk.
	 */
	method RemoveTrunk (IN string trunk);


	/**
	 * Function:	ListTrunk().
	 * Input:		None.
	 * Output:		All Trunk.
	 * Return:		error code.
	 * Description:	List all trunk.
	 */
	method ListTrunk (OUT array<string> trunks);


	/**
	 * Description:	Authorize center interfaces.
	 */
public:
	/**
	 * Function:	AddAuthCenter().	
	 * Input:		trunk:		Trunk name.
	 *				authTag:	Authorize center tag.
	 *				files:		Authorize center execute files.
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Add Authorize center into PCC.
	 */
	method AddAuthCenter (IN string trunk, IN PCC_Tag authTag, IN array<PCC_ModuleFile> files);


	/**
	 * Function:	RemoveAuthCenter().	
	 * Input:		trunk:		Trunk name.
	 *				authTag:	Authorize center tag.
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Remove Authorize center from PCC.
	 */
	method RemoveAuthCenter (IN string trunk, IN PCC_Tag authTag);


	/**
	 * Function:	ListAuthCenter().	
	 * Input:		trunk:		Trunk name.
	 * Output:		authTags:	ALL authorize center tags.
	 * Return:		Error code.
	 * Description:	List all authorize centers in trunk.
	 */
	method ListAuthCenter (IN string trunk, OUT array<PCC_Tag> authTags);


	/**
	 * Function:	FindAuthCenter().	
	 * Input:		trunk:		Trunk name.
	 * Output:		authTag:	Authorize center tag.
	 * Return:		Error code.
	 * Description:	Find specific authorize centers in trunk.
	 */
	method FindAuthCenter (IN string trunk, IN PCC_Tag authTag);


public:
	/**
	 * Function:	AddModule().
	 * Input:		moduleTag:		Module tag.
	 *				modulePattern:	Module pattern.
	 *				moduleFiles:	Module native machine raw files.
	 * Output:		moduleKey:		Module uniform ID in PCC.
	 * Return:		Error code.
	 * Description:	Add module into PCC.
	 */
	method AddModule (IN string trunk,IN INT64 modelKey, IN PCC_ModuleProperty moduleProperty, IN array<PCC_ModuleFile> moudleFiles, OUT INT64 moduleKey);


	/**
	 * Function:	AddModuleFile().
	 * Input:		moduleKey:		Module uniform ID in PCC created by AddMoudle() or get from ListModules().
	 *				fileType:		File type.
	 *				moduleFiles:	Module files.
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Add module files.
	 */
	method AddModuleFile (IN string trunk, IN INT64 moduleKey, IN PCC_ModuleFileType fileType, IN array<PCC_ModuleFile> moduleFiles);


	/**
	 * Function:	RemoveModule().
	 * Input:		moduleKey:	Module uniform ID in PCC created by AddMoudle() or get from ListModules().
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Remove module from PCC by module uniform key.
	 */
	method RemoveModule (IN string trunk, IN INT64 moduleKey);


	/**
	 * Function:	RemoveModuleFiles().
	 * Input:		moduleKey:	Module uniform ID in PCC created by AddMoudle() or get from ListModules().
	 *				fileType:	Module file type in PCC_ModuleFileType.
	 * Output:		None.
	 * Return:		Error code.
	 * Description:	Remove module files
	 */
	method RemoveModuleFiles (IN string trunk, IN INT64 moduleKey, IN INT32 fileType);


	/**
	 * Function:	ListModules().
	 * Input:		None.
	 * Output:		modulesInfo:	Output modules info.
	 * Return:		Error code.
	 * Description:	List all modules in PCC.
	 */
	method ListModules (IN string trunk, OUT array<PCC_ModulePropWithKey> modulesInfo);

    method AddModel (IN PCC_ModelProperty modelProperty, IN array<PCC_ModelFile> modelFiles);

	method ListModels (OUT array<PCC_ModelPropWithKey> modelsInfo);
	
    method DelModel (IN INT64 modelKey);

};
