// PCC_CenterTypesDefine.h
//
// 注意: 此文件为工具生成，请不要修改

#ifndef _PCC_CenterTypesDefine_h_
#define _PCC_CenterTypesDefine_h_

#if defined(_MSC_VER) && (_MSC_VER > 1000)
	#pragma once
#endif

#include "iscm_helper_base.h"

class PCC_CenterSessionMaker;

#ifndef PCC_ModulePattern_defined
#define PCC_ModulePattern_defined
enum PCC_ModulePattern
{
	PCC_MODULE_FRONT_END = 1,
	PCC_MODULE_BACKGROUND = 2,
};
#endif	// #ifndef PCC_ModulePattern_defined

#ifndef PCC_Version_defined
#define PCC_Version_defined
#pragma pack(push, 1)
struct PCC_Version
{
	INT32 major;
	INT32 minor;
	INT32 built;

	PCC_Version()
	{
		this->major = 0;
		this->minor = 0;
		this->built = 0;
	}

	int Compare(const PCC_Version& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_Version)
};
#pragma pack(pop) // #pragma pack(push, 1)
#endif	// #ifndef PCC_Version_defined

#ifndef PCC_Tag_defined
#define PCC_Tag_defined
struct PCC_Tag
{
	tcps_String name;
	PCC_Version version;

	int Compare(const PCC_Tag& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_Tag)
};
#endif	// #ifndef PCC_Tag_defined

#ifndef PCC_ModuleIndex_defined
#define PCC_ModuleIndex_defined
struct PCC_ModuleIndex
{
	INT64 moduleKey;
	PCC_Tag moduleTag;

	PCC_ModuleIndex()
	{
		this->moduleKey = 0;
	}

	int Compare(const PCC_ModuleIndex& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_ModuleIndex)
};
#endif	// #ifndef PCC_ModuleIndex_defined

#ifndef PCC_ModuleFile_defined
#define PCC_ModuleFile_defined
struct PCC_ModuleFile
{
	tcps_String name;
	tcps_Binary data;
	BOOL entry;

	PCC_ModuleFile()
	{
		this->entry = false;
	}

	int Compare(const PCC_ModuleFile& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_ModuleFile)
};
#endif	// #ifndef PCC_ModuleFile_defined

#ifndef PCC_ModuleType_defined
#define PCC_ModuleType_defined
enum PCC_ModuleType
{
	PCC_MODULE_IMGPROC = 1,
	PCC_MODULE_VIDPROC = 2,
	PCC_MODULE_VIDSTRUCTURE = 4,
};
#endif	// #ifndef PCC_ModuleType_defined

#ifndef PCC_ModuleFileType_defined
#define PCC_ModuleFileType_defined
enum PCC_ModuleFileType
{
	PCC_MODULE_MACHINE_RAW = 1,
	PCC_MODULE_CONTROL = 2,
	PCC_MODULE_HTML = 4,
};
#endif	// #ifndef PCC_ModuleFileType_defined

#ifndef PCC_ModuleLatency_defined
#define PCC_ModuleLatency_defined
enum PCC_ModuleLatency
{
	PCC_LATENCY_SMALL = 0,
	PCC_LATENCY_NORMAL = 1,
	PCC_LATENCY_LARGE = 2,
};
#endif	// #ifndef PCC_ModuleLatency_defined

#ifndef PCC_ModuleInfo_defined
#define PCC_ModuleInfo_defined
struct PCC_ModuleInfo
{
	INT64 moduleKey;
	PCC_Tag moduleTag;
	INT32 modulePattern;
	INT32 moduleType;
	tcps_String description;
	INT32 moduleFileType;
	INT32 moduleLatency;
	LTMSEL addTime;
	INT64 moduleSize;

	PCC_ModuleInfo()
	{
		this->moduleKey = 0;
		this->modulePattern = 0;
		this->moduleType = 0;
		this->moduleFileType = 0;
		this->moduleLatency = 0;
		this->addTime = INVALID_UTC_MSEL;
		this->moduleSize = 0;
	}

	int Compare(const PCC_ModuleInfo& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_ModuleInfo)
};
#endif	// #ifndef PCC_ModuleInfo_defined

#ifndef PCC_ModuleProperty_defined
#define PCC_ModuleProperty_defined
struct PCC_ModuleProperty
{
	PCC_Tag moduleTag;
	INT32 modulePattern;
	INT32 moduleFileType;
	INT32 moduleType;
	PCC_ModuleLatency moduleLatency;
	tcps_String description;
	INT64 modulePlatform;
	LTMSEL addTime;
	INT64 moduleSize;

	PCC_ModuleProperty()
	{
		this->modulePattern = 0;
		this->moduleFileType = 0;
		this->moduleType = 0;
		this->moduleLatency = PCC_LATENCY_SMALL;
		this->modulePlatform = 0;
		this->addTime = INVALID_UTC_MSEL;
		this->moduleSize = 0;
	}

	int Compare(const PCC_ModuleProperty& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_ModuleProperty)
};
#endif	// #ifndef PCC_ModuleProperty_defined

#ifndef PCC_ModulePlatform_defined
#define PCC_ModulePlatform_defined
enum PCC_ModulePlatform
{
	PCC_MODULE_WIN32 = 1,
	PCC_MODULE_WIN64 = 2,
};
#endif	// #ifndef PCC_ModulePlatform_defined

#ifndef PCC_ModulePropWithKey_defined
#define PCC_ModulePropWithKey_defined
struct PCC_ModulePropWithKey
{
	INT64 key;
	PCC_ModuleProperty prop;

	PCC_ModulePropWithKey()
	{
		this->key = 0;
	}

	int Compare(const PCC_ModulePropWithKey& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_ModulePropWithKey)
};
#endif	// #ifndef PCC_ModulePropWithKey_defined

#ifndef ExecuteState_defined
#define ExecuteState_defined
#pragma pack(push, 1)
struct ExecuteState
{
	INT32 state;

	ExecuteState()
	{
		this->state = 0;
	}

	int Compare(const ExecuteState& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(ExecuteState)
};
#pragma pack(pop) // #pragma pack(push, 1)
#endif	// #ifndef ExecuteState_defined

#ifndef PCC_CPUType_defined
#define PCC_CPUType_defined
enum PCC_CPUType
{
	PCC_CPU_X86_X64 = 0,
	PCC_CPU_ARM = 1,
	PCC_CPU_MIPS = 2,
};
#endif	// #ifndef PCC_CPUType_defined

#ifndef PCC_OSType_defined
#define PCC_OSType_defined
enum PCC_OSType
{
	PCC_OS_WINDOWS = 0,
	PCC_OS_LINUX = 1,
	PCC_OS_UNIX = 2,
	PCC_OS_ANDROID = 3,
	PCC_OS_IOS = 4,
};
#endif	// #ifndef PCC_OSType_defined

#ifndef PCC_NodeDesc_defined
#define PCC_NodeDesc_defined
struct PCC_NodeDesc
{
	tcps_String name;
	PCC_CPUType cpuType;
	INT64 cpuFreq;
	INT32 cpuProcessors;
	INT32 cpuThreads;
	INT64 totalMemoryBytes;
	INT64 networkBandwidth;
	PCC_OSType osType;
	tcps_String osDetail;
	INT32 executeBits;

	PCC_NodeDesc()
	{
		this->cpuType = PCC_CPU_X86_X64;
		this->cpuFreq = 0;
		this->cpuProcessors = 0;
		this->cpuThreads = 0;
		this->totalMemoryBytes = 0;
		this->networkBandwidth = 0;
		this->osType = PCC_OS_WINDOWS;
		this->executeBits = 0;
	}

	int Compare(const PCC_NodeDesc& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_NodeDesc)
};
#endif	// #ifndef PCC_NodeDesc_defined

#ifndef PCC_DynamicContext_defined
#define PCC_DynamicContext_defined
#pragma pack(push, 1)
struct PCC_DynamicContext
{
	INT32 cpuUsage;
	INT32 memoryUsage;
	INT32 networkUsage;

	PCC_DynamicContext()
	{
		this->cpuUsage = 0;
		this->memoryUsage = 0;
		this->networkUsage = 0;
	}

	int Compare(const PCC_DynamicContext& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_DynamicContext)
};
#pragma pack(pop) // #pragma pack(push, 1)
#endif	// #ifndef PCC_DynamicContext_defined

#ifndef PCC_ModelFile_defined
#define PCC_ModelFile_defined
struct PCC_ModelFile
{
	tcps_String name;
	tcps_Binary data;

	int Compare(const PCC_ModelFile& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_ModelFile)
};
#endif	// #ifndef PCC_ModelFile_defined

#ifndef PCC_ModelProperty_defined
#define PCC_ModelProperty_defined
struct PCC_ModelProperty
{
	PCC_Tag modelTag;
	tcps_String description;
	LTMSEL addTime;

	PCC_ModelProperty()
	{
		this->addTime = INVALID_UTC_MSEL;
	}

	int Compare(const PCC_ModelProperty& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_ModelProperty)
};
#endif	// #ifndef PCC_ModelProperty_defined

#ifndef PCC_ModelPropWithKey_defined
#define PCC_ModelPropWithKey_defined
struct PCC_ModelPropWithKey
{
	INT64 key;
	PCC_ModelProperty prop;

	PCC_ModelPropWithKey()
	{
		this->key = 0;
	}

	int Compare(const PCC_ModelPropWithKey& r) const;
	ISCM_STRUCT_COMPARE_OPERATORS(PCC_ModelPropWithKey)
};
#endif	// #ifndef PCC_ModelPropWithKey_defined

// 'class PCC_Center_T'用于定义接口'PCC_Center'的局部类型
#ifndef PCC_Center_T_defined
#define PCC_Center_T_defined
class PCC_Center_T
{
};

struct IPCC_Center_LocalMethod : public iscm_ILocalMethodBase, public PCC_Center_T
{
	typedef TCPSError (*FN_OnStreamedCall_L_)(
				IN void* sessionObj,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);
};

struct IPCC_Center_LocalCallback : public iscm_ILocalCallbackBase, public PCC_Center_T
{
	typedef TCPSError (*FN_OnStreamedCallback_L_)(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	typedef TCPSError (*FN_AddModelCenter)(
				IN void* sessionObj_wrap,
				IN const IPP& centerIPP
				) posting_callback;

	typedef TCPSError (*FN_DelModelCenter)(
				IN void* sessionObj_wrap,
				IN const IPP& centerIPP
				) posting_callback;

	typedef TCPSError (*FN_GetStaticContext)(
				IN void* sessionObj_wrap,
				OUT PCC_NodeDesc& staticContext
				) cacheable_callback;

	typedef TCPSError (*FN_GetDynamicContext)(
				IN void* sessionObj_wrap,
				OUT PCC_DynamicContext& dynamicContext
				) callback;

	typedef TCPSError (*FN_AddModel)(
				IN void* sessionObj_wrap,
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback;

	typedef TCPSError (*FN_DelModel)(
				IN void* sessionObj_wrap,
				IN INT64 modelKey
				) callback;
};

typedef TCPSError (*FNMakeLocalSession_PCC_Center)(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_Center_LocalMethod*& methodHandler,
			IN IPCC_Center_LocalCallback* callbackHandler
			);
#endif	// #ifndef PCC_Center_T_defined

// 'class PCC_Deploy_T'用于定义接口'PCC_Deploy'的局部类型
#ifndef PCC_Deploy_T_defined
#define PCC_Deploy_T_defined
class PCC_Deploy_T
{
};

struct IPCC_Deploy_LocalMethod : public iscm_ILocalMethodBase, public PCC_Deploy_T
{
	typedef TCPSError (*FN_OnStreamedCall_L_)(
				IN void* sessionObj,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	typedef TCPSError (*FN_Login)(
				IN void* sessionObj_wrap,
				IN const tcps_String& ticket
				) method;

	typedef TCPSError (*FN_Logout)(
				IN void* sessionObj_wrap
				) method;

	typedef TCPSError (*FN_CreateTrunk)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk
				) method;

	typedef TCPSError (*FN_RemoveTrunk)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk
				) method;

	typedef TCPSError (*FN_ListTrunk)(
				IN void* sessionObj_wrap,
				OUT tcps_Array<tcps_String>& trunks
				) method;

	typedef TCPSError (*FN_AddAuthCenter)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag,
				IN const tcps_Array<PCC_ModuleFile>& files
				) method;

	typedef TCPSError (*FN_RemoveAuthCenter)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method;

	typedef TCPSError (*FN_ListAuthCenter)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_Tag>& authTags
				) method;

	typedef TCPSError (*FN_FindAuthCenter)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN const PCC_Tag& authTag
				) method;

	typedef TCPSError (*FN_AddModule)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles,
				OUT INT64& moduleKey
				) method;

	typedef TCPSError (*FN_AddModuleFile)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles
				) method;

	typedef TCPSError (*FN_RemoveModule)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN INT64 moduleKey
				) method;

	typedef TCPSError (*FN_RemoveModuleFiles)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				IN INT64 moduleKey,
				IN INT32 fileType
				) method;

	typedef TCPSError (*FN_ListModules)(
				IN void* sessionObj_wrap,
				IN const tcps_String& trunk,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo
				) method;

	typedef TCPSError (*FN_AddModel)(
				IN void* sessionObj_wrap,
				IN const PCC_ModelProperty& modelProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) method;

	typedef TCPSError (*FN_ListModels)(
				IN void* sessionObj_wrap,
				OUT tcps_Array<PCC_ModelPropWithKey>& modelsInfo
				) method;

	typedef TCPSError (*FN_DelModel)(
				IN void* sessionObj_wrap,
				IN INT64 modelKey
				) method;
};

struct IPCC_Deploy_LocalCallback : public iscm_ILocalCallbackBase, public PCC_Deploy_T
{
	typedef TCPSError (*FN_OnStreamedCallback_L_)(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);
};

typedef TCPSError (*FNMakeLocalSession_PCC_Deploy)(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_Deploy_LocalMethod*& methodHandler,
			IN IPCC_Deploy_LocalCallback* callbackHandler
			);
#endif	// #ifndef PCC_Deploy_T_defined

// 'class PCC_User_T'用于定义接口'PCC_User'的局部类型
#ifndef PCC_User_T_defined
#define PCC_User_T_defined
class PCC_User_T
{
public:
	struct PCCProperty
	{
		tcps_String version;

		int Compare(const PCCProperty& r) const;
		ISCM_STRUCT_COMPARE_OPERATORS(PCCProperty)
	};
};

struct IPCC_User_LocalMethod : public iscm_ILocalMethodBase, public PCC_User_T
{
	typedef TCPSError (*FN_OnStreamedCall_L_)(
				IN void* sessionObj,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	typedef TCPSError (*FN_GetPccProperty)(
				IN void* sessionObj_wrap,
				OUT PCCProperty& pccProp
				) method;

	typedef TCPSError (*FN_ListNodes)(
				IN void* sessionObj_wrap,
				OUT tcps_Array<PCC_NodeDesc>& nodes
				) method;

	typedef TCPSError (*FN_GetNodeDynamicContext)(
				IN void* sessionObj_wrap,
				IN const tcps_String& nodeName,
				OUT PCC_DynamicContext& dynamicContext
				) method;

	typedef TCPSError (*FN_ListModules)(
				IN void* sessionObj_wrap,
				IN const tcps_String& regex,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method;

	typedef TCPSError (*FN_Execute)(
				IN void* sessionObj_wrap,
				IN INT64 moduleKey,
				IN const tcps_String& inputUrl,
				IN const tcps_String& outputUrl,
				IN const tcps_Binary& moduleParams,
				OUT INT64& jobKey
				) method;

	typedef TCPSError (*FN_QueryJobs)(
				IN void* sessionObj_wrap,
				IN const tcps_Array<INT64>& jobsKey,
				OUT tcps_Array<ExecuteState>& jobsState
				) method;

	typedef TCPSError (*FN_CancelJob)(
				IN void* sessionObj_wrap,
				IN INT64 jobKey
				) posting_method;
};

struct IPCC_User_LocalCallback : public iscm_ILocalCallbackBase, public PCC_User_T
{
	typedef TCPSError (*FN_OnStreamedCallback_L_)(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

	typedef TCPSError (*FN_OnExecuted)(
				IN void* sessionObj_wrap,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context
				) posting_callback;

	typedef TCPSError (*FN_OnExecuted1)(
				IN void* sessionObj_wrap,
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context,
				IN const tcps_Array<tcps_Binary>& outArgs
				) posting_callback;
};

typedef TCPSError (*FNMakeLocalSession_PCC_User)(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IPCC_User_LocalMethod*& methodHandler,
			IN IPCC_User_LocalCallback* callbackHandler
			);
#endif	// #ifndef PCC_User_T_defined


/////////////////////////////////////////////////////////////////////
// 结构体的Compare()函数内联实现

#ifndef PCC_Version_Compare_defined
	#define PCC_Version_Compare_defined
	inline int PCC_Version::Compare(const PCC_Version& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->major, r.major);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->minor, r.minor);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->built, r.built);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_Version_Compare_defined

#ifndef PCC_Tag_Compare_defined
	#define PCC_Tag_Compare_defined
	inline int PCC_Tag::Compare(const PCC_Tag& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->name, r.name);
		if(0 != cmp)
			return cmp;
		cmp = this->version.Compare(r.version);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_Tag_Compare_defined

#ifndef PCC_ModuleIndex_Compare_defined
	#define PCC_ModuleIndex_Compare_defined
	inline int PCC_ModuleIndex::Compare(const PCC_ModuleIndex& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->moduleKey, r.moduleKey);
		if(0 != cmp)
			return cmp;
		cmp = this->moduleTag.Compare(r.moduleTag);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_ModuleIndex_Compare_defined

#ifndef PCC_ModuleFile_Compare_defined
	#define PCC_ModuleFile_Compare_defined
	inline int PCC_ModuleFile::Compare(const PCC_ModuleFile& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->name, r.name);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->data, r.data);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->entry, r.entry);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_ModuleFile_Compare_defined

#ifndef PCC_ModuleInfo_Compare_defined
	#define PCC_ModuleInfo_Compare_defined
	inline int PCC_ModuleInfo::Compare(const PCC_ModuleInfo& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->moduleKey, r.moduleKey);
		if(0 != cmp)
			return cmp;
		cmp = this->moduleTag.Compare(r.moduleTag);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->modulePattern, r.modulePattern);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->moduleType, r.moduleType);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->description, r.description);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->moduleFileType, r.moduleFileType);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->moduleLatency, r.moduleLatency);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->addTime, r.addTime);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->moduleSize, r.moduleSize);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_ModuleInfo_Compare_defined

#ifndef PCC_ModuleProperty_Compare_defined
	#define PCC_ModuleProperty_Compare_defined
	inline int PCC_ModuleProperty::Compare(const PCC_ModuleProperty& r) const
	{
		int cmp = 0;
		cmp = this->moduleTag.Compare(r.moduleTag);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->modulePattern, r.modulePattern);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->moduleFileType, r.moduleFileType);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->moduleType, r.moduleType);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->moduleLatency, r.moduleLatency);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->description, r.description);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->modulePlatform, r.modulePlatform);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->addTime, r.addTime);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->moduleSize, r.moduleSize);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_ModuleProperty_Compare_defined

#ifndef PCC_ModulePropWithKey_Compare_defined
	#define PCC_ModulePropWithKey_Compare_defined
	inline int PCC_ModulePropWithKey::Compare(const PCC_ModulePropWithKey& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->key, r.key);
		if(0 != cmp)
			return cmp;
		cmp = this->prop.Compare(r.prop);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_ModulePropWithKey_Compare_defined

#ifndef ExecuteState_Compare_defined
	#define ExecuteState_Compare_defined
	inline int ExecuteState::Compare(const ExecuteState& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->state, r.state);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef ExecuteState_Compare_defined

#ifndef PCC_NodeDesc_Compare_defined
	#define PCC_NodeDesc_Compare_defined
	inline int PCC_NodeDesc::Compare(const PCC_NodeDesc& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->name, r.name);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->cpuType, r.cpuType);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->cpuFreq, r.cpuFreq);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->cpuProcessors, r.cpuProcessors);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->cpuThreads, r.cpuThreads);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->totalMemoryBytes, r.totalMemoryBytes);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->networkBandwidth, r.networkBandwidth);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->osType, r.osType);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->osDetail, r.osDetail);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->executeBits, r.executeBits);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_NodeDesc_Compare_defined

#ifndef PCC_DynamicContext_Compare_defined
	#define PCC_DynamicContext_Compare_defined
	inline int PCC_DynamicContext::Compare(const PCC_DynamicContext& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->cpuUsage, r.cpuUsage);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->memoryUsage, r.memoryUsage);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->networkUsage, r.networkUsage);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_DynamicContext_Compare_defined

#ifndef PCC_ModelFile_Compare_defined
	#define PCC_ModelFile_Compare_defined
	inline int PCC_ModelFile::Compare(const PCC_ModelFile& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->name, r.name);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->data, r.data);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_ModelFile_Compare_defined

#ifndef PCC_ModelProperty_Compare_defined
	#define PCC_ModelProperty_Compare_defined
	inline int PCC_ModelProperty::Compare(const PCC_ModelProperty& r) const
	{
		int cmp = 0;
		cmp = this->modelTag.Compare(r.modelTag);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->description, r.description);
		if(0 != cmp)
			return cmp;
		cmp = SimpleTypeCompare_(this->addTime, r.addTime);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_ModelProperty_Compare_defined

#ifndef PCC_ModelPropWithKey_Compare_defined
	#define PCC_ModelPropWithKey_Compare_defined
	inline int PCC_ModelPropWithKey::Compare(const PCC_ModelPropWithKey& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->key, r.key);
		if(0 != cmp)
			return cmp;
		cmp = this->prop.Compare(r.prop);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_ModelPropWithKey_Compare_defined

#ifndef PCC_User_PCCProperty_Compare_defined
	#define PCC_User_PCCProperty_Compare_defined
	inline int PCC_User_T::PCCProperty::Compare(const PCCProperty& r) const
	{
		int cmp = 0;
		cmp = SimpleTypeCompare_(this->version, r.version);
		if(0 != cmp)
			return cmp;
		return 0;
	}
#endif	// #ifndef PCC_User_PCCProperty_Compare_defined


/////////////////////////////////////////////////////////////////////
// 结构体的流式支持内联函数

#ifndef PCC_Tag_STREAMED_FUNCTIONS_defined
	#define PCC_Tag_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_Tag& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.name);
		size += (int)sizeof(val.version);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_Tag& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.name, data);
		iscm_StreamedLoad(val.version, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_Tag& val)
	{
		iscm_StreamedStore(buf, val.name);
		iscm_StreamedStore(buf, val.version);
	}
#endif	// #ifndef PCC_Tag_STREAMED_FUNCTIONS_defined

#ifndef PCC_ModuleIndex_STREAMED_FUNCTIONS_defined
	#define PCC_ModuleIndex_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_ModuleIndex& val)
	{
		int size = 0;
		size += (int)sizeof(val.moduleKey);
		size += iscm_GetStreamedSize(val.moduleTag);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_ModuleIndex& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.moduleKey, data);
		iscm_StreamedLoad(val.moduleTag, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_ModuleIndex& val)
	{
		iscm_StreamedStore(buf, val.moduleKey);
		iscm_StreamedStore(buf, val.moduleTag);
	}
#endif	// #ifndef PCC_ModuleIndex_STREAMED_FUNCTIONS_defined

#ifndef PCC_ModuleFile_STREAMED_FUNCTIONS_defined
	#define PCC_ModuleFile_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_ModuleFile& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.name);
		size += iscm_GetStreamedSize(val.data);
		size += (int)sizeof(val.entry);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_ModuleFile& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.name, data);
		iscm_StreamedLoad(val.data, data);
		iscm_StreamedLoad(val.entry, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_ModuleFile& val)
	{
		iscm_StreamedStore(buf, val.name);
		iscm_StreamedStore(buf, val.data);
		iscm_StreamedStore(buf, val.entry);
	}
#endif	// #ifndef PCC_ModuleFile_STREAMED_FUNCTIONS_defined

#ifndef PCC_ModuleInfo_STREAMED_FUNCTIONS_defined
	#define PCC_ModuleInfo_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_ModuleInfo& val)
	{
		int size = 0;
		size += (int)sizeof(val.moduleKey);
		size += iscm_GetStreamedSize(val.moduleTag);
		size += (int)sizeof(val.modulePattern);
		size += (int)sizeof(val.moduleType);
		size += iscm_GetStreamedSize(val.description);
		size += (int)sizeof(val.moduleFileType);
		size += (int)sizeof(val.moduleLatency);
		size += (int)sizeof(val.addTime);
		size += (int)sizeof(val.moduleSize);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_ModuleInfo& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.moduleKey, data);
		iscm_StreamedLoad(val.moduleTag, data);
		iscm_StreamedLoad(val.modulePattern, data);
		iscm_StreamedLoad(val.moduleType, data);
		iscm_StreamedLoad(val.description, data);
		iscm_StreamedLoad(val.moduleFileType, data);
		iscm_StreamedLoad(val.moduleLatency, data);
		iscm_StreamedLoad(val.addTime, data);
		iscm_StreamedLoad(val.moduleSize, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_ModuleInfo& val)
	{
		iscm_StreamedStore(buf, val.moduleKey);
		iscm_StreamedStore(buf, val.moduleTag);
		iscm_StreamedStore(buf, val.modulePattern);
		iscm_StreamedStore(buf, val.moduleType);
		iscm_StreamedStore(buf, val.description);
		iscm_StreamedStore(buf, val.moduleFileType);
		iscm_StreamedStore(buf, val.moduleLatency);
		iscm_StreamedStore(buf, val.addTime);
		iscm_StreamedStore(buf, val.moduleSize);
	}
#endif	// #ifndef PCC_ModuleInfo_STREAMED_FUNCTIONS_defined

#ifndef PCC_ModuleProperty_STREAMED_FUNCTIONS_defined
	#define PCC_ModuleProperty_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_ModuleProperty& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.moduleTag);
		size += (int)sizeof(val.modulePattern);
		size += (int)sizeof(val.moduleFileType);
		size += (int)sizeof(val.moduleType);
		size += (int)sizeof(val.moduleLatency);
		size += iscm_GetStreamedSize(val.description);
		size += (int)sizeof(val.modulePlatform);
		size += (int)sizeof(val.addTime);
		size += (int)sizeof(val.moduleSize);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_ModuleProperty& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.moduleTag, data);
		iscm_StreamedLoad(val.modulePattern, data);
		iscm_StreamedLoad(val.moduleFileType, data);
		iscm_StreamedLoad(val.moduleType, data);
		iscm_StreamedLoad(val.moduleLatency, data);
		iscm_StreamedLoad(val.description, data);
		iscm_StreamedLoad(val.modulePlatform, data);
		iscm_StreamedLoad(val.addTime, data);
		iscm_StreamedLoad(val.moduleSize, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_ModuleProperty& val)
	{
		iscm_StreamedStore(buf, val.moduleTag);
		iscm_StreamedStore(buf, val.modulePattern);
		iscm_StreamedStore(buf, val.moduleFileType);
		iscm_StreamedStore(buf, val.moduleType);
		iscm_StreamedStore(buf, val.moduleLatency);
		iscm_StreamedStore(buf, val.description);
		iscm_StreamedStore(buf, val.modulePlatform);
		iscm_StreamedStore(buf, val.addTime);
		iscm_StreamedStore(buf, val.moduleSize);
	}
#endif	// #ifndef PCC_ModuleProperty_STREAMED_FUNCTIONS_defined

#ifndef PCC_ModulePropWithKey_STREAMED_FUNCTIONS_defined
	#define PCC_ModulePropWithKey_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_ModulePropWithKey& val)
	{
		int size = 0;
		size += (int)sizeof(val.key);
		size += iscm_GetStreamedSize(val.prop);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_ModulePropWithKey& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.key, data);
		iscm_StreamedLoad(val.prop, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_ModulePropWithKey& val)
	{
		iscm_StreamedStore(buf, val.key);
		iscm_StreamedStore(buf, val.prop);
	}
#endif	// #ifndef PCC_ModulePropWithKey_STREAMED_FUNCTIONS_defined

#ifndef PCC_NodeDesc_STREAMED_FUNCTIONS_defined
	#define PCC_NodeDesc_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_NodeDesc& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.name);
		size += (int)sizeof(val.cpuType);
		size += (int)sizeof(val.cpuFreq);
		size += (int)sizeof(val.cpuProcessors);
		size += (int)sizeof(val.cpuThreads);
		size += (int)sizeof(val.totalMemoryBytes);
		size += (int)sizeof(val.networkBandwidth);
		size += (int)sizeof(val.osType);
		size += iscm_GetStreamedSize(val.osDetail);
		size += (int)sizeof(val.executeBits);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_NodeDesc& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.name, data);
		iscm_StreamedLoad(val.cpuType, data);
		iscm_StreamedLoad(val.cpuFreq, data);
		iscm_StreamedLoad(val.cpuProcessors, data);
		iscm_StreamedLoad(val.cpuThreads, data);
		iscm_StreamedLoad(val.totalMemoryBytes, data);
		iscm_StreamedLoad(val.networkBandwidth, data);
		iscm_StreamedLoad(val.osType, data);
		iscm_StreamedLoad(val.osDetail, data);
		iscm_StreamedLoad(val.executeBits, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_NodeDesc& val)
	{
		iscm_StreamedStore(buf, val.name);
		iscm_StreamedStore(buf, val.cpuType);
		iscm_StreamedStore(buf, val.cpuFreq);
		iscm_StreamedStore(buf, val.cpuProcessors);
		iscm_StreamedStore(buf, val.cpuThreads);
		iscm_StreamedStore(buf, val.totalMemoryBytes);
		iscm_StreamedStore(buf, val.networkBandwidth);
		iscm_StreamedStore(buf, val.osType);
		iscm_StreamedStore(buf, val.osDetail);
		iscm_StreamedStore(buf, val.executeBits);
	}
#endif	// #ifndef PCC_NodeDesc_STREAMED_FUNCTIONS_defined

#ifndef PCC_ModelFile_STREAMED_FUNCTIONS_defined
	#define PCC_ModelFile_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_ModelFile& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.name);
		size += iscm_GetStreamedSize(val.data);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_ModelFile& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.name, data);
		iscm_StreamedLoad(val.data, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_ModelFile& val)
	{
		iscm_StreamedStore(buf, val.name);
		iscm_StreamedStore(buf, val.data);
	}
#endif	// #ifndef PCC_ModelFile_STREAMED_FUNCTIONS_defined

#ifndef PCC_ModelProperty_STREAMED_FUNCTIONS_defined
	#define PCC_ModelProperty_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_ModelProperty& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.modelTag);
		size += iscm_GetStreamedSize(val.description);
		size += (int)sizeof(val.addTime);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_ModelProperty& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.modelTag, data);
		iscm_StreamedLoad(val.description, data);
		iscm_StreamedLoad(val.addTime, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_ModelProperty& val)
	{
		iscm_StreamedStore(buf, val.modelTag);
		iscm_StreamedStore(buf, val.description);
		iscm_StreamedStore(buf, val.addTime);
	}
#endif	// #ifndef PCC_ModelProperty_STREAMED_FUNCTIONS_defined

#ifndef PCC_ModelPropWithKey_STREAMED_FUNCTIONS_defined
	#define PCC_ModelPropWithKey_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_ModelPropWithKey& val)
	{
		int size = 0;
		size += (int)sizeof(val.key);
		size += iscm_GetStreamedSize(val.prop);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_ModelPropWithKey& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.key, data);
		iscm_StreamedLoad(val.prop, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_ModelPropWithKey& val)
	{
		iscm_StreamedStore(buf, val.key);
		iscm_StreamedStore(buf, val.prop);
	}
#endif	// #ifndef PCC_ModelPropWithKey_STREAMED_FUNCTIONS_defined

#ifndef PCC_User_PCCProperty_STREAMED_FUNCTIONS_defined
	#define PCC_User_PCCProperty_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_User_T::PCCProperty& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.version);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_User_T::PCCProperty& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.version, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_User_T::PCCProperty& val)
	{
		iscm_StreamedStore(buf, val.version);
	}
#endif	// #ifndef PCC_User_PCCProperty_STREAMED_FUNCTIONS_defined

#endif	// #ifndef _PCC_CenterTypesDefine_h_
