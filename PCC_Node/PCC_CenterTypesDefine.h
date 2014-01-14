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

// 'class PCC_Center_T'用于定义接口'PCC_Center'的局部类型
#ifndef PCC_Center_T_defined
#define PCC_Center_T_defined
class PCC_Center_T
{
public:
	struct PCC_ModelFile
	{
		tcps_String name;
	};

public:
	#pragma pack(push, 1)
	struct PCC_ModelVersion
	{
		INT32 major;
		INT32 minor;
		INT32 built;

		PCC_ModelVersion()
		{
			this->major = 0;
			this->minor = 0;
			this->built = 0;
		}
	};
	#pragma pack(pop) // #pragma pack(push, 1)

public:
	struct PCC_ModelTag
	{
		tcps_String name;
		PCC_ModelVersion version;
	};

public:
	struct PCC_ModelProperty
	{
		PCC_ModelTag modelTag;
		tcps_String description;
		LTMSEL addTime;

		PCC_ModelProperty()
		{
			this->addTime = INVALID_UTC_MSEL;
		}
	};

public:
	struct PCC_ModelPropWithKey
	{
		INT64 key;
		PCC_ModelProperty prop;

		PCC_ModelPropWithKey()
		{
			this->key = 0;
		}
	};

public:
	struct PCCProperty
	{
		tcps_String version;
	};

public:
	enum CPUType
	{
		PCC_CPU_X86_X64 = 0,
		PCC_CPU_ARM = 1,
		PCC_CPU_MIPS = 2,
	};

public:
	enum OSType
	{
		PCC_OS_WINDOWS = 0,
		PCC_OS_LINUX = 1,
		PCC_OS_UNIX = 2,
		PCC_OS_ANDROID = 3,
		PCC_OS_IOS = 4,
	};

public:
	struct NodeDesc
	{
		tcps_String name;
		CPUType cpuType;
		INT64 cpuFreq;
		INT32 cpuProcessors;
		INT32 cpuThreads;
		INT64 totalMemoryBytes;
		INT64 networkBandwidth;
		OSType osType;
		tcps_String osDetail;
		INT32 executeBits;

		NodeDesc()
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
	};

public:
	#pragma pack(push, 1)
	struct DynamicContext
	{
		INT32 cpuUsage;
		INT32 memoryUsage;
		INT32 networkUsage;

		DynamicContext()
		{
			this->cpuUsage = 0;
			this->memoryUsage = 0;
			this->networkUsage = 0;
		}
	};
	#pragma pack(pop) // #pragma pack(push, 1)
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
				OUT NodeDesc& staticContext
				) cacheable_callback;

	typedef TCPSError (*FN_GetDynamicContext)(
				IN void* sessionObj_wrap,
				OUT DynamicContext& dynamicContext
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

// 'class BaseFacet_T'用于定义接口'BaseFacet'的局部类型
#ifndef BaseFacet_T_defined
#define BaseFacet_T_defined
class BaseFacet_T
{
public:
	#pragma pack(push, 1)
	struct ConnectionStat
	{
		LTMSEL connectedTime;
		INT64 totals;
		INT64 actives;

		ConnectionStat()
		{
			this->connectedTime = INVALID_UTC_MSEL;
			this->totals = 0;
			this->actives = 0;
		}
	};
	#pragma pack(pop) // #pragma pack(push, 1)

public:
	struct FaceStat
	{
		tcps_String interfaceName;
		ConnectionStat connStat;
	};

public:
	struct IPPToFaceStat
	{
		IPP clientID_IPP;
		tcps_Array<FaceStat> faceStatAr;
	};

public:
	enum ResUsageType
	{
		rut_nothing = 0,
		rut_sys = 1,
		rut_connections = 2,
		rut_sys_connections = 3,
	};

public:
	enum CallType
	{
		ct_method = 0,
		ct_cacheable_method = 1,
		ct_posting_method = 2,
		ct_callback = 3,
		ct_cacheable_callback = 4,
		ct_posting_callback = 5,
	};

public:
	struct CallInfo
	{
		CallType type;
		tcps_String name;

		CallInfo()
			: type(ct_method)
		{
		}
	};

public:
	struct FaceCalls
	{
		tcps_String faceName;
		tcps_Array<CallInfo> calls;
	};

public:
	struct FaceContents
	{
		tcps_String filename;
		tcps_String contents;
	};
};

struct IBaseFacet_LocalMethod : public iscm_ILocalMethodBase, public BaseFacet_T
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

	typedef TCPSError (*FN_AliveCheck)(
				IN void* sessionObj_wrap
				) method;

	typedef TCPSError (*FN_GetServeName)(
				IN void* sessionObj_wrap,
				OUT tcps_String& name,
				OUT INT32& pid
				) cacheable_method;

	typedef TCPSError (*FN_GetContextInfos)(
				IN void* sessionObj_wrap,
				OUT INT32& servePID,
				OUT LTMSEL& startMSEL,
				OUT tcps_String& operatingSystem,
				OUT tcps_String& compiler,
				OUT tcps_String& binType,
				OUT INT64& totalMem,
				OUT INT64& cpuFreq,
				OUT INT32& cpuCount
				) cacheable_method;

	typedef TCPSError (*FN_GetResourceUsage)(
				IN void* sessionObj_wrap,
				IN ResUsageType rut,
				OUT double& cpuUsage,
				OUT double& memUsage,
				OUT tcps_Array<IPPToFaceStat>& connectionsStat
				) method;

	typedef TCPSError (*FN_GetAllInterfaceCalls)(
				IN void* sessionObj_wrap,
				OUT tcps_Array<FaceCalls>& faceCalls
				) cacheable_method;

	typedef TCPSError (*FN_GetIDLHeaders)(
				IN void* sessionObj_wrap,
				OUT tcps_Array<FaceContents>& idlHeaders
				) cacheable_method;

	typedef TCPSError (*FN_GetClientHeaders)(
				IN void* sessionObj_wrap,
				IN const tcps_String& language,
				OUT tcps_Array<FaceContents>& userHeaders
				) cacheable_method;

	typedef TCPSError (*FN_GetServeVersion)(
				IN void* sessionObj_wrap,
				OUT INT32& majorVer,
				OUT INT32& minorVer,
				OUT INT32& thirdVer
				) cacheable_method;

	typedef TCPSError (*FN_GetCompileNum)(
				IN void* sessionObj_wrap,
				OUT INT64& compileNum
				) cacheable_method;

	typedef TCPSError (*FN_GetWorkPath)(
				IN void* sessionObj_wrap,
				OUT tcps_String& path
				) cacheable_method;

	typedef TCPSError (*FN_ShutdownSelf)(
				IN void* sessionObj_wrap
				) posting_method;
};

struct IBaseFacet_LocalCallback : public iscm_ILocalCallbackBase, public BaseFacet_T
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

typedef TCPSError (*FNMakeLocalSession_BaseFacet)(
			IN const IPP& clientID_IPP,
			IN PCC_CenterSessionMaker& sessionMaker,
			OUT IBaseFacet_LocalMethod*& methodHandler,
			IN IBaseFacet_LocalCallback* callbackHandler
			);
#endif	// #ifndef BaseFacet_T_defined


/////////////////////////////////////////////////////////////////////
// 结构体的流式支持内联函数

#ifndef PCC_Center_PCC_ModelFile_STREAMED_FUNCTIONS_defined
	#define PCC_Center_PCC_ModelFile_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_Center_T::PCC_ModelFile& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.name);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_Center_T::PCC_ModelFile& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.name, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_Center_T::PCC_ModelFile& val)
	{
		iscm_StreamedStore(buf, val.name);
	}
#endif	// #ifndef PCC_Center_PCC_ModelFile_STREAMED_FUNCTIONS_defined

#ifndef PCC_Center_PCC_ModelTag_STREAMED_FUNCTIONS_defined
	#define PCC_Center_PCC_ModelTag_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_Center_T::PCC_ModelTag& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.name);
		size += (int)sizeof(val.version);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_Center_T::PCC_ModelTag& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.name, data);
		iscm_StreamedLoad(val.version, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_Center_T::PCC_ModelTag& val)
	{
		iscm_StreamedStore(buf, val.name);
		iscm_StreamedStore(buf, val.version);
	}
#endif	// #ifndef PCC_Center_PCC_ModelTag_STREAMED_FUNCTIONS_defined

#ifndef PCC_Center_PCC_ModelProperty_STREAMED_FUNCTIONS_defined
	#define PCC_Center_PCC_ModelProperty_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_Center_T::PCC_ModelProperty& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.modelTag);
		size += iscm_GetStreamedSize(val.description);
		size += (int)sizeof(val.addTime);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_Center_T::PCC_ModelProperty& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.modelTag, data);
		iscm_StreamedLoad(val.description, data);
		iscm_StreamedLoad(val.addTime, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_Center_T::PCC_ModelProperty& val)
	{
		iscm_StreamedStore(buf, val.modelTag);
		iscm_StreamedStore(buf, val.description);
		iscm_StreamedStore(buf, val.addTime);
	}
#endif	// #ifndef PCC_Center_PCC_ModelProperty_STREAMED_FUNCTIONS_defined

#ifndef PCC_Center_PCC_ModelPropWithKey_STREAMED_FUNCTIONS_defined
	#define PCC_Center_PCC_ModelPropWithKey_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_Center_T::PCC_ModelPropWithKey& val)
	{
		int size = 0;
		size += (int)sizeof(val.key);
		size += iscm_GetStreamedSize(val.prop);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_Center_T::PCC_ModelPropWithKey& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.key, data);
		iscm_StreamedLoad(val.prop, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_Center_T::PCC_ModelPropWithKey& val)
	{
		iscm_StreamedStore(buf, val.key);
		iscm_StreamedStore(buf, val.prop);
	}
#endif	// #ifndef PCC_Center_PCC_ModelPropWithKey_STREAMED_FUNCTIONS_defined

#ifndef PCC_Center_PCCProperty_STREAMED_FUNCTIONS_defined
	#define PCC_Center_PCCProperty_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_Center_T::PCCProperty& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.version);
		return size;
	}
	inline void iscm_StreamedLoad(PCC_Center_T::PCCProperty& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.version, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_Center_T::PCCProperty& val)
	{
		iscm_StreamedStore(buf, val.version);
	}
#endif	// #ifndef PCC_Center_PCCProperty_STREAMED_FUNCTIONS_defined

#ifndef PCC_Center_NodeDesc_STREAMED_FUNCTIONS_defined
	#define PCC_Center_NodeDesc_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const PCC_Center_T::NodeDesc& val)
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
	inline void iscm_StreamedLoad(PCC_Center_T::NodeDesc& val, const BYTE*& data)
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
	inline void iscm_StreamedStore(BYTE*& buf, const PCC_Center_T::NodeDesc& val)
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
#endif	// #ifndef PCC_Center_NodeDesc_STREAMED_FUNCTIONS_defined

#ifndef BaseFacet_FaceStat_STREAMED_FUNCTIONS_defined
	#define BaseFacet_FaceStat_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const BaseFacet_T::FaceStat& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.interfaceName);
		size += (int)sizeof(val.connStat);
		return size;
	}
	inline void iscm_StreamedLoad(BaseFacet_T::FaceStat& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.interfaceName, data);
		iscm_StreamedLoad(val.connStat, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const BaseFacet_T::FaceStat& val)
	{
		iscm_StreamedStore(buf, val.interfaceName);
		iscm_StreamedStore(buf, val.connStat);
	}
#endif	// #ifndef BaseFacet_FaceStat_STREAMED_FUNCTIONS_defined

#ifndef BaseFacet_IPPToFaceStat_STREAMED_FUNCTIONS_defined
	#define BaseFacet_IPPToFaceStat_STREAMED_FUNCTIONS_defined
	#ifndef BaseFacet_FaceStat_GetStreamedSize_Array1_defined
		#define BaseFacet_FaceStat_GetStreamedSize_Array1_defined
		ISCM_DEFINE_ARRAY_STREAMED_FUNCTIONS_(BaseFacet_T::FaceStat)
	#endif
	inline int iscm_GetStreamedSize(const BaseFacet_T::IPPToFaceStat& val)
	{
		int size = 0;
		size += (int)sizeof(val.clientID_IPP);
		size += iscm_GetStreamedSize(val.faceStatAr);
		return size;
	}
	inline void iscm_StreamedLoad(BaseFacet_T::IPPToFaceStat& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.clientID_IPP, data);
		iscm_StreamedLoad(val.faceStatAr, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const BaseFacet_T::IPPToFaceStat& val)
	{
		iscm_StreamedStore(buf, val.clientID_IPP);
		iscm_StreamedStore(buf, val.faceStatAr);
	}
#endif	// #ifndef BaseFacet_IPPToFaceStat_STREAMED_FUNCTIONS_defined

#ifndef BaseFacet_CallInfo_STREAMED_FUNCTIONS_defined
	#define BaseFacet_CallInfo_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const BaseFacet_T::CallInfo& val)
	{
		int size = 0;
		size += (int)sizeof(val.type);
		size += iscm_GetStreamedSize(val.name);
		return size;
	}
	inline void iscm_StreamedLoad(BaseFacet_T::CallInfo& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.type, data);
		iscm_StreamedLoad(val.name, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const BaseFacet_T::CallInfo& val)
	{
		iscm_StreamedStore(buf, val.type);
		iscm_StreamedStore(buf, val.name);
	}
#endif	// #ifndef BaseFacet_CallInfo_STREAMED_FUNCTIONS_defined

#ifndef BaseFacet_FaceCalls_STREAMED_FUNCTIONS_defined
	#define BaseFacet_FaceCalls_STREAMED_FUNCTIONS_defined
	#ifndef BaseFacet_CallInfo_GetStreamedSize_Array1_defined
		#define BaseFacet_CallInfo_GetStreamedSize_Array1_defined
		ISCM_DEFINE_ARRAY_STREAMED_FUNCTIONS_(BaseFacet_T::CallInfo)
	#endif
	inline int iscm_GetStreamedSize(const BaseFacet_T::FaceCalls& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.faceName);
		size += iscm_GetStreamedSize(val.calls);
		return size;
	}
	inline void iscm_StreamedLoad(BaseFacet_T::FaceCalls& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.faceName, data);
		iscm_StreamedLoad(val.calls, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const BaseFacet_T::FaceCalls& val)
	{
		iscm_StreamedStore(buf, val.faceName);
		iscm_StreamedStore(buf, val.calls);
	}
#endif	// #ifndef BaseFacet_FaceCalls_STREAMED_FUNCTIONS_defined

#ifndef BaseFacet_FaceContents_STREAMED_FUNCTIONS_defined
	#define BaseFacet_FaceContents_STREAMED_FUNCTIONS_defined
	inline int iscm_GetStreamedSize(const BaseFacet_T::FaceContents& val)
	{
		int size = 0;
		size += iscm_GetStreamedSize(val.filename);
		size += iscm_GetStreamedSize(val.contents);
		return size;
	}
	inline void iscm_StreamedLoad(BaseFacet_T::FaceContents& val, const BYTE*& data)
	{
		iscm_StreamedLoad(val.filename, data);
		iscm_StreamedLoad(val.contents, data);
	}
	inline void iscm_StreamedStore(BYTE*& buf, const BaseFacet_T::FaceContents& val)
	{
		iscm_StreamedStore(buf, val.filename);
		iscm_StreamedStore(buf, val.contents);
	}
#endif	// #ifndef BaseFacet_FaceContents_STREAMED_FUNCTIONS_defined

#endif	// #ifndef _PCC_CenterTypesDefine_h_
