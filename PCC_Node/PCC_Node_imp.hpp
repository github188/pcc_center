

#include "pcc_centerclient.h"
#include "osfunc.h"
#include "CpuMem.h"
#include "Register.h"
class PCC_Node : public PCC_Center
{
private:
	PCC_Node(const PCC_Node&);
	PCC_Node& operator= (const PCC_Node&);

public:
	PCC_Node()
		{}
	virtual ~PCC_Node()
		{	DestroyRequester();	}

/// 基本网络事件
protected:
	virtual TCPSError OnConnected()
	{
		// TODO: 请添加连接后处理
		return TCPS_OK;
	}
	virtual void OnPeerBroken()
	{
		// TODO: 请添加对端断线处理
	}
	virtual void OnClose()
	{
		// TODO: 请添加连接关闭处理
	}
	virtual void OnConnectTimeout(IN TCPSError cause)
	{
		// TODO: 请添加连接超时处理
		(void)cause;
	}

/// 回调
protected:
	virtual TCPSError AddModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{
		// TODO: 请实现此函数
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError DelModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{
		// TODO: 请实现此函数
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError GetStaticContext(
				OUT NodeDesc& staticContext
				) cacheable_callback
	{
		// TODO: 请实现此函数
		
		staticContext.cpuType = PCC_CPU_X86_X64;
		staticContext.cpuFreq = 0;
		staticContext.cpuProcessors = 0;
		staticContext.cpuThreads = 0;
		staticContext.totalMemoryBytes = 0;
		staticContext.networkBandwidth = 0;
		staticContext.osType = PCC_OS_WINDOWS;
		staticContext.executeBits = 0;
		
		/**
		* Description:	Only binary support now.
		*/
		//staticContext.binaryType = bt_machineRaw;

		/**
		* Description:	Get system info.
		*/
		tcps_String str(OSGetSystemVersionInfo().c_str());
		staticContext.osDetail = str;

		/**
		* Description:	Set default CPU type.
		*/
		staticContext.cpuType = PCC_CPU_X86_X64;

#ifdef WIN32
		int			   cpuInfo[4];
		SYSTEM_INFO	   info;
		MEMORYSTATUSEX memStatus;


		/**
		* Description:	Get system info.
		*/
		GetSystemInfo(&info);

		/**
		* Description:	Output CPU thread number and processor number.
		*/
		staticContext.cpuThreads	= info.dwNumberOfProcessors;
		staticContext.cpuProcessors = info.dwNumberOfProcessors;

		/**
		* Description:	Check HTT flag.
		*/
		__cpuid(cpuInfo, 1);

		if (cpuInfo[3] & (1 << 28))
		{
			/**
			* Description:	HTT, thread number is processor number 2 times. 
			*/
			staticContext.cpuProcessors = staticContext.cpuThreads / 2;
		}

		/**
		* Description:	Get IsWow64Process function address.
		*/
		typedef BOOL (WINAPI *LPFN_ISWOW) (HANDLE, PBOOL); 
		staticContext.executeBits = 32;
		LPFN_ISWOW fnIsWow		  = (LPFN_ISWOW)GetProcAddress( GetModuleHandle("kernel32"),"IsWow64Process"); 

		/**
		* Description:	Has IsWow64Process function?
		*/
		if (NULL != fnIsWow) 
		{ 
			BOOL isWow = FALSE; 

			/**
			* Description:	Check process(32) running on 64 bit system?
			*/
			if (fnIsWow(GetCurrentProcess(), &isWow) && isWow)
			{
				staticContext.executeBits = 32;
			}

			/**
			* Description:	64 bit system if 64 bit application is running.
			*/
			else if (sizeof(long) == 8)
			{
				staticContext.executeBits = 64;
			}
		}

		/**
		* Description:	Get CPU frequency from register table.
		*/
		DWORD cpuFreq;
		BOOL  ok = GetRegKeyValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 
			"~MHz", (TCHAR *)&cpuFreq, REG_DWORD);

		/**
		* Description:	Get CPU frequency OK?
		*/
		if (ok)
		{
			staticContext.cpuFreq = (INT64)cpuFreq * 100000;
		}
		else
		{
			staticContext.cpuFreq = -1;
		}

		/**
		* Description:	Get physical memory size.
		*/
		memStatus.dwLength = sizeof(memStatus);

		if (GlobalMemoryStatusEx(&memStatus))
		{
			staticContext.totalMemoryBytes = (INT64)memStatus.ullTotalPhys;
		}
		else
		{
			staticContext.totalMemoryBytes = -1;
		}

		/**
		* Description:	Get operation system info.
		*/
		OSVERSIONINFO osVerInfo;

		staticContext.osType		  = PCC_OS_WINDOWS;
		osVerInfo.dwOSVersionInfoSize = sizeof(osVerInfo);
		GetVersionEx(&osVerInfo);

		switch (osVerInfo.dwMajorVersion)
		{
		case 4:
			{
				if (0 == osVerInfo.dwMinorVersion)
				{
					staticContext.osType = PCC_OS_WINDOWS;
				}
				else if (10 == osVerInfo.dwMinorVersion)
				{
					staticContext.osType = PCC_OS_WINDOWS;
				}
				break;
			}

		case 5:
			{
				if (0 == osVerInfo.dwMinorVersion)
				{
					staticContext.osType = PCC_OS_WINDOWS;
				}
				else if (1 == osVerInfo.dwMinorVersion)
				{
					staticContext.osType = PCC_OS_WINDOWS;
				}
				break;
			}

		case 6:
			{
				if (0 == osVerInfo.dwMinorVersion)
				{
					staticContext.osType = PCC_OS_WINDOWS;
				}
				else if (1 == osVerInfo.dwMinorVersion)
				{
					staticContext.osType = PCC_OS_WINDOWS;
				}
				else if (2 == osVerInfo.dwMinorVersion)
				{
					staticContext.osType = PCC_OS_WINDOWS;
				}
				break;
			}
		}
#endif
	/**
	 * Description:	Get network band width.
	 */
	staticContext.networkBandwidth = 100;
		return TCPS_OK;
	}

	virtual TCPSError GetDynamicContext(
				OUT DynamicContext& dynamicContext
				) callback
	{
		// TODO: 请实现此函数

		dynamicContext.memoryUsage = GetMemUsageEx();
		dynamicContext.cpuUsage	   = GetCpuUsageEx();
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError AddModel(
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback
	{
		// TODO: 请实现此函数
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

	virtual TCPSError DelModel(
				IN INT64 modelKey
				) callback
	{
		// TODO: 请实现此函数
		return TCPS_ERR_NOT_IMPLEMENTED;
	}

protected:
	// 返回TCPS_OK允许重定向；返回非TCPS_OK禁止重定向
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		// TODO: 请实现此函数
		return TCPS_OK;
	}
};

class NodeBaseFacet : public BaseFacet
{
private:
	NodeBaseFacet(const NodeBaseFacet&);
	NodeBaseFacet& operator= (const NodeBaseFacet&);

public:
	NodeBaseFacet()
		{}
	virtual ~NodeBaseFacet()
		{	DestroyRequester();	}

/// 基本网络事件
protected:
	virtual TCPSError OnConnected()
	{
		// TODO: 请添加连接后处理
		return TCPS_OK;
	}
	virtual void OnPeerBroken()
	{
		// TODO: 请添加对端断线处理
	}
	virtual void OnClose()
	{
		// TODO: 请添加连接关闭处理
	}
	virtual void OnConnectTimeout(IN TCPSError cause)
	{
		// TODO: 请添加连接超时处理
		(void)cause;
	}
};
