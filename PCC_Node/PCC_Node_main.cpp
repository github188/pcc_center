// PCC_Node.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "pcc_node_imp.hpp"
#include "MainLoopHandler.h"
#include "ipcvt.h"
int _tmain(int argc, _TCHAR* argv[])
{
	IPP ipp;
	ipp.ip_ = inet_addr("127.0.0.1");
	ipp.port_ = 9011;
	PCC_Node node;
	
	
#if defined(WIN32)
	typedef HWND (WINAPI* NFGetConsoleWindow)();
	NFGetConsoleWindow fnGetConsoleWindow = (NFGetConsoleWindow)GetProcAddress(
		GetModuleHandle(_T("kernel32.dll")), "GetConsoleWindow");
	HWND wnd;
	if(fnGetConsoleWindow && NULL!=(wnd=fnGetConsoleWindow()))
	{
		char ch[1024];
		int l = GetWindowTextA(wnd, ch, sizeof(ch)-16);
		char ippStr[32];
		GetIPPortTxt(ipp, ippStr);
		sprintf(ch+l, " - %s", ippStr);
		SetWindowTextA(wnd, ch);
	}
	
#endif
	node.SetServeIPP(ipp);//断开自动重新连接
	RunMainLoop();
	/*
	while (1)
		{
				if(!node.IsConnected())
				{
					node.SetServeIPP(ipp);//必须设置，已断开自动重新连接
				}
				Sleep(1);
		}
		node.SetServeIPP(INVALID_IPP);*/
	
		return 0;
}