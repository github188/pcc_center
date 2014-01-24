/**
 *                                          Netposa Cloud ISCM
 *                                   (c) Copyright 2011-2013, Netposa
 *                                           All Rights Reserved
 *
 * File		: PCC_Types.iscm.h.
 * Author	: Zhou Guangming
 * Time		: 2013-11-5
 */


/////////////////////////////////////// 下面为指定编译选项 ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// 0 - 不含内置基本接口
// 1 - 含有内置基本接口
#compiler bface = 0

// 0 - 不支持结构体比较
// 1 - 支持结构体比较
#compiler compare = 1

// 0 - 不支持会话解绑
// 1 - 支持会话解绑
#compiler drop = 0

// 0 - 不支持服务重定向
// 1 - 支持服务重定向
#compiler redirect = 1

// 0 - 所有接口共用XXXClient.cpp
// 1 - 每个接口单独XXXClient.cpp
#compiler client = 0

// 0 - 源码静态库(Static Libs)
// 1 - 源码动态库(Depended DLLs)
// 2 - 独立动态库(Released DLLs)
#compiler crt = 2

// 0 - 不进行不良命名风格检查
// 1 - 进行不良命名风格检查
#compiler check = 1


/// 下面的C/C++语法形式的代码不是接口描述所必须的，仅用于辅助人工编写接口和提高可读性用
/// 注意：所有的关键字区分大小写

/// 基本数据类型
/// TYPE VAR_NAME
typedef void* INT8;
typedef void* INT16;
typedef void* INT32;
typedef void* INT64;
typedef void* double;	// 8字节
typedef void* LTMSEL;	// 8字节
typedef void* IPP;
typedef void* BOOL;
typedef void* string;
typedef void* binary;
typedef void* error;

/// 数组: array
/// array<TYPE> VAR_NAME
template<typename TYPE> class array{};

/// 全局常量定义关键字
/// const BASE_TYPE const_val_name = const_val;
#define const

/// 枚举类型
/// enum ENUM_NAME { ENUM_BODY };
#define enum

/// 结构体: struct，结构体内部一条定义语句只允许定义一个变量
/// struct STRU_NAME { STRU_BODY };
#define struct

/// 接口: interface，一个服务可以多个接口
/// interface FACE_NAME { FACE_BODY };
#define interface

/// 公共访问指示符: 接口内部使用，接口的默认访问指示为public
/// public:
#define public

/// 私有访问指示符: 接口内部使用
/// private:
#define private

/// 方法: method
/// method METHOD_NAME(PARAMETERS);
#define method

/// 回调: callback
/// callback CALLBACK_NAME(PARAMETERS);
#define callback

/// 可缓存: cacheable
/// cacheable method METHOD_NAME(PARAMETERS);
/// cacheable callback CALLBACK_NAME(PARAMETERS);
#define cacheable

/// 投递式: posting
/// posting method METHOD_NAME(PARAMETERS);
/// posting callback CALLBACK_NAME(PARAMETERS);
#define posting

/// 输入/输出描述: IN、OUT
/// IN VAR_TYPE VAR_NAME
/// OUT VAR_TYPE VAR_NAME
#define IN
#define OUT


/**
 * Description:	Define module type.
 */
enum PCC_ModulePattern
{
	PCC_MODULE_FRONT_END  = 1,				/* Front end module.									*/
	PCC_MODULE_BACKGROUND = 2,				/* Background module.									*/
};


/**
 * Description:	Define module version type.
 *				major:	Module major version.
 *				minor:	Module minor version.
 *				built:	Module built version.
 */
struct PCC_Version
{
	INT32 major;
	INT32 minor;
	INT32 built;
};


/**
 * Description:	Define tag type or PCC.
 *				name:		name in string.
 *				version:	Version.
 */
struct PCC_Tag
{
	string		name;
	PCC_Version version;
};


/**
 * Description:	Define module index type.
 *				moduleKey:	Module uniform ID in PCC.
 *				moduleTab:	Module tag.
 */ 
struct PCC_ModuleIndex
{
	INT64	moduleKey;
	PCC_Tag moduleTag;
};


/**
 * Description:	Define module file.
 *				name:	Module file name include extend name.
 *				data:	Module file data.
 *				entry:	Module entry or not.
 */
struct PCC_ModuleFile
{
	string name;
	binary data;
	BOOL   entry;
};


/**
 * Description:	
 */
enum PCC_ModuleType
{
	PCC_MODULE_IMGPROC		= 1, 
	PCC_MODULE_VIDPROC		= 2,
	PCC_MODULE_VIDSTRUCTURE = 4,
};


/**
 * Description:	Define module file type.
 */
enum PCC_ModuleFileType
{
	PCC_MODULE_MACHINE_RAW = 1,					/* Native executable file(Assembly, C/C++)			*/
	PCC_MODULE_CONTROL	   = 2,					/* Control file.									*/
	PCC_MODULE_HTML		   = 4,					/* HTML file.										*/
};


/**
 * Description:	Define module latency.
 */
enum PCC_ModuleLatency
{
	PCC_LATENCY_SMALL  = 0,						/* Small latency,  less than 2 seconds.				*/
	PCC_LATENCY_NORMAL = 1,						/* Normal latency, more than 2 seconds.				*/
	PCC_LATENCY_LARGE  = 2,						/* Large latency, more than 1 minutes.				*/
};


/**
 * Description:	Define module info get from PCC.
 * Member:		moduleKey:		Module uniform ID in PCC.
 *				modulePattern:	Module pattern in PCC_ModulePattern.
 *				moduleTag:		Module tag.
 *				description:	Module description in string.
 *				moduleLatency:	Module latency.
 */
struct PCC_ModuleInfo
{
	INT64	moduleKey;
	PCC_Tag	moduleTag;
	INT32	modulePattern;
	INT32	moduleType;
	string	description;
	INT32	moduleFileType;
	INT32	moduleLatency;
	LTMSEL	addTime;
	INT64	moduleSize;
};


/**
 * Description:	
 */
struct PCC_ModuleProperty
{
	PCC_Tag			  moduleTag;
	INT32			  modulePattern;
	INT32			  moduleFileType;
	INT32			  moduleType;
	PCC_ModuleLatency moduleLatency;
	string			  description;
	INT64			  modulePlatform;
	LTMSEL			  addTime;
	INT64			  moduleSize;
};


enum PCC_ModulePlatform
{
	PCC_MODULE_WIN32 = 1, 
	PCC_MODULE_WIN64 = 2, 
};


/**
 * Description:	
 */
struct PCC_ModulePropWithKey
{
	INT64			   key;
	INT64			   model;
	PCC_ModuleProperty prop;
};


//2014/1/14
//temp added by wt
struct ExecuteState
{
    INT32 state;
};

/**
 * Description:	Define CPU type for PCC.
 */
enum PCC_CPUType
{
    PCC_CPU_X86_X64 = 0,					/* X86/X64.											*/
    PCC_CPU_ARM,							/* ARM.												*/
    PCC_CPU_MIPS,							/* MIPS.											*/
};

/**
 * Description:	Define operation type for PCC.
 */
enum PCC_OSType
{
    PCC_OS_WINDOWS = 0,						/* Windows.											*/
    PCC_OS_LINUX,							/* Linux.											*/
    PCC_OS_UNIX,							/* Unix.											*/
    PCC_OS_ANDROID,							/* Android.											*/
    PCC_OS_IOS,								/* IOS.												*/
};

/**
 * Description:	Define node description for PCC.
 * Parameters:	name:				Node name.
 *				cpuType:			Node CPU type.	
 *				cpuFreq:			CPU frequency in HZ.
 *				cpuProcessors:		CPU processor count.
 *				cpuThread:			CPU thread count.
 *				totalMemoryBytes:	Total memory size in bytes.
 *				networkBandwidth:	Network band with in Mb/s.
 *				osType:				Operation system type.
 *				osDetail:			Operation system detail info.
 *				executeBits:		Execute bits count.
 */
struct PCC_NodeDesc 
{
    string		name;
    PCC_CPUType	cpuType;
    INT64		cpuFreq;
    INT32		cpuProcessors;
    INT32		cpuThreads;
    INT64		totalMemoryBytes;
    INT64		networkBandwidth;
    PCC_OSType	osType;
    string		osDetail;
    INT32		executeBits;
};

/**
 * Description:	Define dynamic context.
 * Parameters:	cpuUsage:		CPU usage in percent.
 *				memoryUsage:	Memory usage in percent.
 *				networkUsage:	Network usage in percent.
 */
struct PCC_DynamicContext
{
    INT32 cpuUsage;
    INT32 memoryUsage;
    INT32 networkUsage;
};

//////////////////////////////////////////////////////////////
struct PCC_ModelFile
{
    string name;
	binary data;
};

struct PCC_ModelProperty
{
    PCC_Tag	modelTag;
    string	description;
    LTMSEL	addTime;
};

/**
 * Description:	
 */
struct PCC_ModelPropWithKey
{
    INT64			  key;
    PCC_ModelProperty prop;
};
