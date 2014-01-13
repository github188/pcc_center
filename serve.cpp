// serve.cpp

#include "StdAfx.h"
#include "ipcvt.h"
#include "SingletonsRegister.h"
#include "CmdArgParser.h"
#include "MainLoopHandler.h"
#include "nplog.h"
#include "rpc_serve.h"
#include "PCC_CenterSession.h"

int g_majorVer = 1;
int g_minorVer = 0;
int g_thirdVer = 0;
char g_compileNumInfo[32] =
{
	"ISCMComp"	// 8����ʼ��ʶ�ַ�
	"-1\0\0\0\0\0\0\0\0\0\0\0\0\0\0" // ��16���ַ����ڴ�ű���ţ�svn�ţ����ⲿ����д�룩
	"ISCMNum"	// 8��������ʶ�ַ�����������'\0'��
};
BOOL g_exitFlag = false;

IPP g_serveIPP = IPP(INADDR_ANY, 2011);

static void LogPrint__(void* /*param*/, const char* txt)
	{	NPLogInfo(("%s", txt));	}

int main(int argc, const char* argv[])
{
	// ����������ѡ��
	CmdArgParser cmdParser("", TCtoC_str(CStrFormat(_T("����汾: %d.%d.%d"), g_majorVer, g_minorVer, g_thirdVer)));

	CStringA sip;
	VERIFY(cmdParser.AddStr(
			sip, "-ip", "", "IP",
			"�����TCP����IP��Ĭ�ϼ�����������IP"
			));

	int tcpPort = g_serveIPP.port_;
	VERIFY(cmdParser.AddInt(
			tcpPort, "-p",
			1, GET_INT_MAX_VALUE(WORD),
			tcpPort, "port",
			"�����TCP�����˿�"
			));

	if(!cmdParser.RunParse(argc, argv))
		return -1;

	if(!sip.IsEmpty())
	{
		if(!IsValidIP((const char*)sip, &g_serveIPP.ip_))
		{
			NPLogError((_T("�Ƿ�ip����: %s"), (LPCTSTR)CtoTC_str((const char*)sip)));
			return -1;
		}
	}
	g_serveIPP.port_ = tcpPort;

	// ���û���ϵͳ����
#if defined(WIN32)
	SetCurrentDirectory(GetExeDir());
#endif
	tcps_SetLogPrint(LogPrint__, NULL);

	// ����rpc�������
	// ���ڹ���PCC_CenterSessionMakerʱ����һ void* �������Ự����
	// �磺PCC_CenterSessionMaker sessionMaker(param);
	// �ڻỰ�����п�ʹ��this->m_sessionMaker.m_userParameter���
	PCC_CenterSessionMaker sessionMaker;
	iscm_IRPCServeMan* rpcMan = NULL;
	TCPSError err = iscm_MakeRPCServeMan(rpcMan, g_serveIPP.port_, g_serveIPP.ip_, &sessionMaker, TCPS_MAX_TOTAL_SESSIONS/2);
	if(TCPS_OK == err)
	{
		// ������ѭ��
		NPLogInfo(("Running serve..."));
		struct TCheck
		{
			static BOOL RunCheck(void* /*param*/)
				{	return !g_exitFlag;	}
		};
#if defined(WIN32)
		typedef HWND (WINAPI* FNGetConsoleWindow)();
		FNGetConsoleWindow fnGetConsoleWindow
			= (FNGetConsoleWindow)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "GetConsoleWindow");
		HWND wnd;
		if(fnGetConsoleWindow && NULL!=(wnd=fnGetConsoleWindow()))
		{
			char ch[1024];
			int l = GetWindowTextA(wnd, ch, sizeof(ch)-16);
			char ippStr[32];
			GetIPPortTxt(g_serveIPP, ippStr);
			sprintf(ch+l, " - %s", ippStr);
			SetWindowTextA(wnd, ch);
		}
#endif
		RunMainLoop(TCheck::RunCheck, NULL);
		g_exitFlag = true;
		NPLogInfo(("Exiting serve..."));
	}
	else
	{
		NPLogError(("iscm_MakeRPCServeMan(%d) failed, %s(%d)", tcpPort, tcps_GetErrTxt(err), err));
	}

	// ����rpc�������
	if(rpcMan)
		rpcMan->DeleteThis();

//#if defined(_NP_IS_X86) || defined(_NP_IS_X64)
//	NPCRT_API_SetPerformancePolicy(false, true);
//#endif

	// ����tcps/iscm�������е�ȫ�ֶ���ӵ���̵߳ģ�
	tcps_DestroyAllGlobalObjects();

	return 0;
}
