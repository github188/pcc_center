// PCC_Node.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "pcc_node_imp.hpp"
#include "MainLoopHandler.h"
#include "ipcvt.h"
#include "Singleton.h"
#include "n_modelmanage.h"
int _tmain(int argc, _TCHAR* argv[])
{
	IPP ipp;
	ipp.ip_ = inet_addr("127.0.0.1");
	ipp.port_ = 2011;
	PCC_Node node;
	
	//debug_start
	pgrid_util::Singleton<CModelManage>::instance().init();
	PCC_ModelProperty modelProperty;
	modelProperty.modelTag.name = "mmodel0";
	modelProperty.modelTag.version.major = 1;
	modelProperty.modelTag.version.minor = 2;	
	FILE *fp;
	fp = fopen(
		"E:/PCC_Center/Debug.2008/Models/mmodel0-1.2/N.npk"//face_togpl(1)test.json
		,"rb"); 
	fseek(fp,0,SEEK_END);//48：6254

	long file_len = ftell(fp);
	fseek(fp,0,SEEK_SET);
	
	tcps_Array<PCC_ModelFile> modelFiles;
	modelFiles.Resize(1);
	modelFiles[0].data.Resize(file_len);
	fread(modelFiles[0].data.Get(),file_len,1,fp);
	modelFiles[0].name = "N.npk";
	//moudleFiles[0].entry = TRUE;
	fclose(fp);
	pgrid_util::Singleton<CModelManage>::instance().AddModel(modelProperty,modelFiles);
	//debug_end
	
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