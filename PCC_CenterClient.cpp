// PCC_CenterClient.cpp
//
// 注意: 此文件为工具生成，请不要修改

#include "StdAfx.h"
#include "PCC_CenterClient.h"
#include "ipcvt.h"
#include "Binary.h"
#include "PtrStr.h"
#include "ScopeGuard.h"
#include "AutoInterface.h"
#include "ILocker.h"
#include "TaskMan.h"
#include "smlib.h"
#include "iscm_requester.h"
#include "iscm_callback_serve.h"
#include "iscm_posting_caller.h"
#include "iscm_udp_serve.h"
#include "tcps_connect_man.h"
#include "iscm_helper.h"
#include "iscm_smart_container.h"

#if defined(_MSC_VER)
	#pragma warning(disable: 4702) // unreachable code
#endif

static const char* s_PCC_Center_AddModelCenter_TypeInfo_ = NULL;
static int s_PCC_Center_AddModelCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Center_DelModelCenter_TypeInfo_ = NULL;
static int s_PCC_Center_DelModelCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Center_GetStaticContext_TypeInfo_ = NULL;
static int s_PCC_Center_GetStaticContext_TypeInfo_len_ = 0;

static const char* s_PCC_Center_GetDynamicContext_TypeInfo_ = NULL;
static int s_PCC_Center_GetDynamicContext_TypeInfo_len_ = 0;

static const char* s_PCC_Center_AddModel_TypeInfo_ = NULL;
static int s_PCC_Center_AddModel_TypeInfo_len_ = 0;

static const char* s_PCC_Center_DelModel_TypeInfo_ = NULL;
static int s_PCC_Center_DelModel_TypeInfo_len_ = 0;

static const char* s_PCC_Center_UDPLink__TypeInfo_ = NULL;
static int s_PCC_Center_UDPLink__TypeInfo_len_ = 0;

static const char* s_PCC_Center_UDPLinkConfirm__TypeInfo_ = NULL;
static int s_PCC_Center_UDPLinkConfirm__TypeInfo_len_ = 0;

static const char* s_PCC_Center_SetRedirect__TypeInfo_ = NULL;
static int s_PCC_Center_SetRedirect__TypeInfo_len_ = 0;

static const char* s_PCC_Center_SetTimeout__TypeInfo_ = NULL;
static int s_PCC_Center_SetTimeout__TypeInfo_len_ = 0;

static const char* s_PCC_Center_SetSessionBufferSize__TypeInfo_ = NULL;
static int s_PCC_Center_SetSessionBufferSize__TypeInfo_len_ = 0;

static const char* s_PCC_Center_MethodCheck__TypeInfo_ = NULL;
static int s_PCC_Center_MethodCheck__TypeInfo_len_ = 0;

static const char* s_PCC_Center_CallbackCheck__TypeInfo_ = NULL;
static int s_PCC_Center_CallbackCheck__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_Login_TypeInfo_ = NULL;
static int s_PCC_Deploy_Login_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_Logout_TypeInfo_ = NULL;
static int s_PCC_Deploy_Logout_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_CreateTrunk_TypeInfo_ = NULL;
static int s_PCC_Deploy_CreateTrunk_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_RemoveTrunk_TypeInfo_ = NULL;
static int s_PCC_Deploy_RemoveTrunk_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_ListTrunk_TypeInfo_ = NULL;
static int s_PCC_Deploy_ListTrunk_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_AddAuthCenter_TypeInfo_ = NULL;
static int s_PCC_Deploy_AddAuthCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_RemoveAuthCenter_TypeInfo_ = NULL;
static int s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_ListAuthCenter_TypeInfo_ = NULL;
static int s_PCC_Deploy_ListAuthCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_FindAuthCenter_TypeInfo_ = NULL;
static int s_PCC_Deploy_FindAuthCenter_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_AddModule_TypeInfo_ = NULL;
static int s_PCC_Deploy_AddModule_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_AddModuleFile_TypeInfo_ = NULL;
static int s_PCC_Deploy_AddModuleFile_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_RemoveModule_TypeInfo_ = NULL;
static int s_PCC_Deploy_RemoveModule_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_RemoveModuleFiles_TypeInfo_ = NULL;
static int s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_ListModules_TypeInfo_ = NULL;
static int s_PCC_Deploy_ListModules_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_AddModel_TypeInfo_ = NULL;
static int s_PCC_Deploy_AddModel_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_DelModel_TypeInfo_ = NULL;
static int s_PCC_Deploy_DelModel_TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_SetRedirect__TypeInfo_ = NULL;
static int s_PCC_Deploy_SetRedirect__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_SetTimeout__TypeInfo_ = NULL;
static int s_PCC_Deploy_SetTimeout__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_SetSessionBufferSize__TypeInfo_ = NULL;
static int s_PCC_Deploy_SetSessionBufferSize__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_MethodCheck__TypeInfo_ = NULL;
static int s_PCC_Deploy_MethodCheck__TypeInfo_len_ = 0;

static const char* s_PCC_Deploy_CallbackCheck__TypeInfo_ = NULL;
static int s_PCC_Deploy_CallbackCheck__TypeInfo_len_ = 0;

static const char* s_PCC_User_GetPccProperty_TypeInfo_ = NULL;
static int s_PCC_User_GetPccProperty_TypeInfo_len_ = 0;

static const char* s_PCC_User_ListNodes_TypeInfo_ = NULL;
static int s_PCC_User_ListNodes_TypeInfo_len_ = 0;

static const char* s_PCC_User_GetNodeDynamicContext_TypeInfo_ = NULL;
static int s_PCC_User_GetNodeDynamicContext_TypeInfo_len_ = 0;

static const char* s_PCC_User_ListModules_TypeInfo_ = NULL;
static int s_PCC_User_ListModules_TypeInfo_len_ = 0;

static const char* s_PCC_User_Execute_TypeInfo_ = NULL;
static int s_PCC_User_Execute_TypeInfo_len_ = 0;

static const char* s_PCC_User_OnExecuted_TypeInfo_ = NULL;
static int s_PCC_User_OnExecuted_TypeInfo_len_ = 0;

static const char* s_PCC_User_OnExecuted1_TypeInfo_ = NULL;
static int s_PCC_User_OnExecuted1_TypeInfo_len_ = 0;

static const char* s_PCC_User_QueryJobs_TypeInfo_ = NULL;
static int s_PCC_User_QueryJobs_TypeInfo_len_ = 0;

static const char* s_PCC_User_CancelJob_TypeInfo_ = NULL;
static int s_PCC_User_CancelJob_TypeInfo_len_ = 0;

static const char* s_PCC_User_UDPLink__TypeInfo_ = NULL;
static int s_PCC_User_UDPLink__TypeInfo_len_ = 0;

static const char* s_PCC_User_UDPLinkConfirm__TypeInfo_ = NULL;
static int s_PCC_User_UDPLinkConfirm__TypeInfo_len_ = 0;

static const char* s_PCC_User_SetRedirect__TypeInfo_ = NULL;
static int s_PCC_User_SetRedirect__TypeInfo_len_ = 0;

static const char* s_PCC_User_SetTimeout__TypeInfo_ = NULL;
static int s_PCC_User_SetTimeout__TypeInfo_len_ = 0;

static const char* s_PCC_User_SetSessionBufferSize__TypeInfo_ = NULL;
static int s_PCC_User_SetSessionBufferSize__TypeInfo_len_ = 0;

static const char* s_PCC_User_MethodCheck__TypeInfo_ = NULL;
static int s_PCC_User_MethodCheck__TypeInfo_len_ = 0;

static const char* s_PCC_User_CallbackCheck__TypeInfo_ = NULL;
static int s_PCC_User_CallbackCheck__TypeInfo_len_ = 0;

static INT_PTR InitializeAllCallsTypeInfo_()
{
	// BOOL和枚举类型长度必须为4字节（网络协议已规定为固定4字节）
	STATIC_ASSERT(4 == sizeof(BOOL));
	STATIC_ASSERT(4 == sizeof(DummyEnumType));

	BEGIN_LOCAL_SAFE_STATIC_OBJ(INT_PTR, dummyVar);

	{
		BYTE const chZipped[] =
		{
			0x19,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x61,0x00,
			0x00,0x83,0xBD,0x09,0x35,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_AddModelCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_AddModelCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x19,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x61,0x00,
			0x00,0x83,0xBD,0x09,0x35,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_DelModelCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_DelModelCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x0A,0x01,0x00,0x80,0x78,0x01,0x4D,0x4F,0xCB,0x0A,0xC2,0x30,0x10,0xF4,0x5F,0xF4,
			0x98,0x83,0x68,0x29,0x82,0xF4,0x50,0x9A,0xCB,0x82,0x4D,0x42,0x93,0xD0,0xDE,0x42,
			0x1A,0x83,0x8A,0x45,0xC5,0x7A,0x11,0xFA,0xF1,0xE6,0xD1,0x87,0x97,0x61,0xE7,0xB1,
			0xCB,0x2C,0x2B,0x0A,0x55,0x30,0x29,0xBE,0x2F,0xBB,0x66,0x71,0x56,0xCD,0x21,0x55,
			0x4D,0x9A,0x64,0x5B,0x34,0x29,0x79,0x55,0x66,0x33,0x29,0x81,0xF1,0x0C,0x1D,0xBD,
			0x47,0x9E,0x67,0x8B,0x6D,0x6F,0x36,0xFD,0xE7,0x7D,0x7B,0x5C,0xA6,0x88,0xBF,0x86,
			0x80,0x88,0x34,0xF1,0xB8,0xDF,0x2D,0x18,0x15,0x87,0x7E,0x9B,0xF2,0x10,0x1C,0x77,
			0x63,0x32,0x9C,0x8D,0x46,0xE8,0x43,0xB9,0xAA,0x81,0x60,0x5A,0xF3,0xB1,0x8E,0x13,
			0x4E,0x40,0x64,0x13,0xFB,0x38,0x26,0x09,0x2C,0x24,0x27,0xB8,0xA2,0x80,0x67,0x13,
			0xA8,0xAF,0x6A,0xB4,0xB9,0x5A,0xDD,0x76,0x56,0x19,0xDD,0x75,0xAD,0x36,0xF7,0x81,
			0x4A,0x31,0xFC,0x7F,0x80,0x56,0x3F,0x0C,0xE3,0x52,0x1A,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_GetStaticContext_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_GetStaticContext_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x47,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x77,0xA9,0xCC,0x4B,0xCC,0xCD,
			0x4C,0x76,0xCE,0xCF,0x2B,0x49,0xAD,0x28,0x51,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0x41,
			0x26,0xAD,0x93,0x13,0x73,0x72,0x92,0x12,0x93,0xB3,0x6B,0xFC,0x43,0x43,0x6A,0x02,
			0x30,0xB4,0xE8,0x30,0x00,0x00,0x51,0x7B,0x17,0xDB,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_GetDynamicContext_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_GetDynamicContext_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xB1,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x49,0xCD,0x71,
			0xCB,0xCC,0x49,0x55,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0xB1,0x0E,0x80,0x89,0x06,
			0x14,0xE5,0x17,0xA4,0x16,0x95,0x54,0xAA,0x80,0x44,0x42,0x12,0xD3,0x75,0xA0,0x2A,
			0x7C,0x42,0x7C,0x83,0x5D,0x7D,0x20,0x0A,0x81,0xC2,0x30,0x8D,0x20,0x55,0x61,0xA9,
			0x45,0xC5,0x99,0xF9,0x79,0x10,0x39,0x28,0x47,0xC5,0xD3,0x2F,0xC4,0xD8,0x48,0x07,
			0x99,0xB4,0x4E,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xC1,0xB0,
			0x0F,0xA8,0xB4,0x26,0xB1,0xA8,0x28,0xB1,0xD2,0x06,0x2E,0x05,0x72,0xA0,0x9D,0x0E,
			0x03,0x00,0x2E,0xC4,0x3C,0x89,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_AddModel_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_AddModel_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x13,0x00,0x00,0x80,0x78,0x01,0x4B,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,
			0xF4,0x03,0xA2,0x10,0x33,0x13,0x1D,0x06,0x00,0x47,0x50,0x06,0x3E,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_DelModel_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_DelModel_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x1C,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0x0F,0x0D,
			0xA9,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0x41,0xB0,0x18,0x00,0x91,0x83,0x08,0xDE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_UDPLink__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_UDPLink__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x08,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0x61,0x00,0x00,
			0x0E,0xD3,0x02,0xFE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_UDPLinkConfirm__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_UDPLinkConfirm__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x23,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x01,0x52,
			0x49,0x99,0x79,0x89,0x45,0x95,0x3A,0x0C,0x00,0xF8,0x4D,0x0C,0xF9,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_SetRedirect__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_SetRedirect__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_SetTimeout__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_SetTimeout__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_SetSessionBufferSize__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_SetSessionBufferSize__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3A,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,0xC1,0x10,
			0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,0x9A,0x78,
			0x15,0x41,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_MethodCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_MethodCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3C,0x00,0x00,0x80,0x78,0x01,0x4B,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,
			0xF4,0xAB,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,
			0xC1,0x10,0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,
			0xC2,0xD8,0x15,0xED,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Center_CallbackCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Center_CallbackCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x12,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x61,0x00,0x00,0x46,0x0C,0x06,0xD4,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_Login_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_Login_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x08,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0x61,0x00,0x00,
			0x0E,0xD3,0x02,0xFE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_Logout_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_Logout_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x12,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x61,0x00,0x00,0x46,0x0C,0x06,0xD4,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_CreateTrunk_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_CreateTrunk_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x12,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x61,0x00,0x00,0x46,0x0C,0x06,0xD4,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_RemoveTrunk_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_RemoveTrunk_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x1A,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0x0F,0x0D,
			0xA9,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,0x61,
			0x00,0x00,0x8D,0xB9,0x09,0xCE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_ListTrunk_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_ListTrunk_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x94,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x29,0xCD,0x49,
			0x75,0xCB,0xCC,0x49,0x55,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x49,0xCA,0xCC,0x4B,
			0x2C,0xAA,0xD4,0x71,0xF2,0xF7,0xF7,0xD1,0xB1,0x0E,0x00,0x2A,0x09,0x49,0x4C,0x87,
			0xC9,0x81,0xB8,0x61,0xA9,0x45,0xC5,0x99,0xF9,0x79,0x10,0x39,0x28,0x47,0xC5,0xD3,
			0x2F,0xC4,0xD8,0x48,0x07,0x99,0xB4,0xCE,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,
			0xAB,0x81,0x1A,0x0C,0x64,0x41,0x8D,0x03,0x2A,0xAC,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,
			0x01,0x09,0x20,0x9C,0x60,0xA7,0xC3,0x00,0x00,0xC2,0x86,0x32,0x45,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_AddAuthCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_AddAuthCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x58,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x49,0x4C,0x57,0x29,0x2E,
			0x29,0xCA,0xCC,0x4B,0xD7,0x09,0x00,0x72,0xC3,0x52,0x8B,0x8A,0x33,0xF3,0xF3,0x74,
			0xAC,0x91,0x38,0x2A,0x9E,0x7E,0x21,0xC6,0x46,0x3A,0xC8,0xA4,0x75,0x6E,0x6A,0x49,
			0x46,0x7E,0x4A,0x8D,0xA7,0x5F,0x0D,0x54,0x33,0x90,0x05,0xD2,0x02,0x34,0x4E,0x87,
			0x01,0x00,0x1D,0x3E,0x1D,0x0C,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_RemoveAuthCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x60,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x49,0x4C,0x57,0x29,0x2E,
			0x29,0xCA,0xCC,0x4B,0xD7,0x09,0x00,0x72,0xC3,0x52,0x8B,0x8A,0x33,0xF3,0xF3,0x74,
			0xAC,0x91,0x38,0x2A,0x9E,0x7E,0x21,0xC6,0x46,0x3A,0xC8,0xA4,0x75,0x6E,0x6A,0x49,
			0x46,0x7E,0x4A,0x8D,0xA7,0x5F,0x0D,0x54,0xB3,0x7F,0x68,0x48,0x4D,0x62,0x51,0x51,
			0x62,0xA5,0x0D,0x48,0x27,0xD0,0x54,0x3B,0x1D,0x06,0x00,0x1B,0x60,0x20,0x06,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_ListAuthCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_ListAuthCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x58,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x49,0x4C,0x57,0x29,0x2E,
			0x29,0xCA,0xCC,0x4B,0xD7,0x09,0x00,0x72,0xC3,0x52,0x8B,0x8A,0x33,0xF3,0xF3,0x74,
			0xAC,0x91,0x38,0x2A,0x9E,0x7E,0x21,0xC6,0x46,0x3A,0xC8,0xA4,0x75,0x6E,0x6A,0x49,
			0x46,0x7E,0x4A,0x8D,0xA7,0x5F,0x0D,0x54,0x33,0x90,0x05,0xD2,0x02,0x34,0x4E,0x87,
			0x01,0x00,0x1D,0x3E,0x1D,0x0C,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_FindAuthCenter_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_FindAuthCenter_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x53,0x01,0x00,0x80,0x78,0x01,0x65,0x50,0x4B,0x0B,0x82,0x40,0x10,0xEE,0xBF,0xE4,
			0x71,0x0F,0x65,0xD1,0xC5,0x0C,0x4C,0x2C,0x84,0xF5,0x81,0x6E,0x41,0x27,0xD9,0x72,
			0xB1,0x05,0x73,0x63,0xDD,0x0E,0x0B,0xFE,0xF8,0x76,0xCB,0x27,0x5E,0x06,0xE6,0x9B,
			0xF9,0x1E,0x33,0xB1,0xEB,0x66,0x01,0xCB,0x3F,0x25,0x39,0xD1,0x92,0x18,0xB5,0xE0,
			0xB4,0x2A,0xC0,0x9D,0x56,0x98,0x4B,0x70,0x8C,0x22,0x08,0xAC,0xB8,0x5F,0x81,0x58,
			0x90,0xEA,0x21,0x97,0x1A,0x81,0x0E,0xF2,0x42,0xF7,0x96,0xA5,0x81,0x03,0xA1,0xBD,
			0x02,0x63,0x2C,0x8C,0x12,0x85,0xDA,0xEB,0x09,0x08,0x9D,0xE4,0xEC,0xD9,0xE6,0x58,
			0x2F,0xE6,0xEC,0x4D,0xB8,0x90,0x86,0x26,0x23,0x5C,0x00,0x3F,0x44,0x1B,0x73,0x52,
			0x67,0xE6,0xA0,0x8D,0xA8,0x56,0x77,0x5B,0x00,0x51,0x90,0x7A,0x50,0x33,0x54,0xF3,
			0x4B,0xAA,0x64,0xBA,0x2B,0x34,0xF7,0x4A,0x78,0x4D,0x59,0xF5,0x9F,0xB5,0x8D,0x31,
			0xB7,0xB1,0x5E,0x44,0x3C,0x59,0xDE,0xF8,0x61,0xD3,0xEB,0x37,0x83,0x77,0x17,0x54,
			0x19,0x35,0x98,0x73,0x2C,0xF7,0xC3,0x4C,0xFF,0xED,0x00,0xA2,0x0B,0x52,0x64,0x9D,
			0x62,0xF1,0x05,0x00,0x71,0x6E,0xC2,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_AddModule_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_AddModule_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xC1,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x29,0xCD,0x49,
			0x75,0xCB,0xCC,0x49,0x55,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x49,0xCA,0xCC,0x4B,
			0x2C,0xAA,0xD4,0x71,0xF2,0xF7,0xF7,0xD1,0xB1,0x0E,0x40,0x51,0x12,0x52,0x59,0x90,
			0xAA,0x0C,0x16,0xF2,0x77,0x09,0xF5,0x71,0x8D,0xF7,0x75,0x74,0xF6,0xF0,0xF4,0x73,
			0x8D,0x0F,0x72,0x0C,0xB7,0x35,0xD4,0x41,0x92,0x70,0xF6,0xF7,0x0B,0x09,0xF2,0xF7,
			0xB1,0x35,0x42,0x16,0xF4,0x08,0xF1,0xF5,0xB1,0x35,0xD1,0xB1,0xCE,0x4D,0x2D,0xC9,
			0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,0x81,0xDA,0x08,0x64,0x79,0xFA,0x85,0x98,0x99,0xE8,
			0x00,0x19,0x98,0x16,0x82,0x44,0x13,0x8B,0x8A,0x12,0x2B,0x6D,0x50,0xE5,0xEC,0x74,
			0x18,0x00,0x48,0x5C,0x40,0x2C,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_AddModuleFile_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_AddModuleFile_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x1B,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x01,0xB2,0x3C,0xFD,0x42,0xCC,0x4C,0x74,0x18,
			0x00,0x94,0x3B,0x09,0x68,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_RemoveModule_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_RemoveModule_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x24,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0x01,0xB2,0x3C,0xFD,0x42,0xCC,0x4C,0xA0,0x0C,
			0x63,0x23,0x1D,0x06,0x00,0xF9,0x8C,0x0B,0xF7,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_RemoveModuleFiles_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x48,0x01,0x00,0x80,0x78,0x01,0x5D,0x8F,0x5F,0x0B,0x82,0x30,0x14,0xC5,0xFB,0x2E,
			0xF9,0xB8,0x87,0xB2,0xE8,0xC5,0x0C,0x64,0x48,0x48,0x73,0x8A,0xAE,0xA2,0x27,0x19,
			0x39,0x52,0x28,0x17,0x73,0x3D,0x0C,0xFC,0xF0,0x6D,0x3A,0xF0,0xCF,0xCB,0xE0,0x9E,
			0x7B,0xCE,0xEF,0x9E,0xA5,0x10,0x16,0x31,0x2F,0x7F,0x6F,0x86,0xA8,0x64,0xCD,0x53,
			0xAD,0x53,0xAD,0xA0,0x80,0x84,0x18,0x3E,0x8A,0x3C,0x0E,0x10,0xF2,0x37,0x60,0xAA,
			0xE1,0x24,0xD3,0xAA,0xBF,0x9D,0x89,0x28,0xC8,0xCE,0xA1,0xEF,0x02,0xCF,0x38,0x07,
			0x5E,0x2A,0xF8,0xF7,0x5E,0xCB,0xEA,0xC2,0x94,0x13,0x61,0x72,0xD8,0xF7,0x81,0x71,
			0xC7,0x84,0x54,0x4B,0xBF,0xD1,0x1C,0x83,0x20,0xF4,0x05,0x74,0x68,0xE7,0xCE,0xDE,
			0x11,0x6E,0xCB,0x82,0x56,0x8A,0xBA,0xE9,0xAD,0x9A,0x8F,0x48,0x9C,0x87,0xC8,0x24,
			0xF4,0xD0,0x37,0xD1,0x18,0xC7,0x5A,0x4C,0xF6,0xC6,0x44,0x5B,0xF3,0x66,0xD8,0xD9,
			0xC1,0x74,0x5B,0x9C,0xF1,0x3E,0x4C,0x56,0xBC,0xEC,0x22,0xDC,0xD9,0x70,0x72,0x25,
			0x1D,0x15,0x82,0xAA,0xE3,0x58,0x61,0xF2,0xBF,0x13,0x58,0xFD,0x01,0x17,0xCC,0x6B,
			0x9C,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_ListModules_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_ListModules_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xAF,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x49,0xCD,0x71,
			0xCB,0xCC,0x49,0x55,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xD7,0xB1,0x0E,0x80,0x89,0x06,
			0x14,0xE5,0x17,0xA4,0x16,0x95,0x54,0xAA,0x80,0x44,0x42,0x12,0xD3,0x75,0xA0,0x2A,
			0x7C,0x42,0x7C,0x83,0x5D,0x7D,0x20,0x0A,0x81,0xC2,0x30,0x8D,0x20,0x55,0x61,0xA9,
			0x45,0xC5,0x99,0xF9,0x79,0x10,0x39,0x28,0x47,0xC5,0xD3,0x2F,0xC4,0xD8,0x48,0x07,
			0x99,0xB4,0xCE,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,0xC1,0xB0,0x0D,0xA8,
			0xB0,0x26,0xB1,0xA8,0x28,0xB1,0xD2,0x06,0x2E,0x05,0x72,0x9E,0x9D,0x0E,0x03,0x00,
			0xB8,0x83,0x3B,0xDD,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_AddModel_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_AddModel_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x11,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,
			0xA2,0x10,0x33,0x13,0x1D,0x06,0x00,0x3A,0x7C,0x05,0x92,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_DelModel_TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_DelModel_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x23,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x01,0x52,
			0x49,0x99,0x79,0x89,0x45,0x95,0x3A,0x0C,0x00,0xF8,0x4D,0x0C,0xF9,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_SetRedirect__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_SetRedirect__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_SetTimeout__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_SetTimeout__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_SetSessionBufferSize__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_SetSessionBufferSize__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3A,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,0xC1,0x10,
			0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,0x9A,0x78,
			0x15,0x41,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_MethodCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_MethodCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3C,0x00,0x00,0x80,0x78,0x01,0x4B,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,
			0xF4,0xAB,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,
			0xC1,0x10,0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,
			0xC2,0xD8,0x15,0xED,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_Deploy_CallbackCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_Deploy_CallbackCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x36,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x0F,0x2D,0x4E,0x2D,0xB2,0xB2,
			0x0A,0x70,0x76,0x0E,0x28,0xCA,0x2F,0x48,0x2D,0x2A,0xA9,0x54,0x29,0x2E,0x29,0xCA,
			0xCC,0x4B,0xD7,0xB1,0xCE,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0x0F,0x0D,0xA9,0x41,
			0x92,0xD6,0x61,0x00,0x00,0x15,0xA5,0x13,0x7E,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_GetPccProperty_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_GetPccProperty_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x05,0x01,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x77,0x0E,0x08,0x0D,0xA9,0x2C,
			0x48,0x55,0x0E,0x80,0xB0,0xE3,0x23,0x2C,0xCC,0xE2,0x23,0xCC,0x4C,0x6C,0x0D,0x74,
			0x60,0x22,0x8E,0x41,0xBE,0xB6,0x70,0x8E,0xAF,0x67,0x40,0xB0,0xAD,0x8E,0x35,0x48,
			0xCE,0x2F,0x3F,0x25,0xD5,0x25,0xB5,0x38,0x59,0xA5,0xB8,0xA4,0x28,0x33,0x2F,0x1D,
			0xA6,0x04,0x64,0x9A,0x8E,0xA7,0x5F,0x88,0x99,0x09,0x88,0x34,0x36,0x42,0x90,0x10,
			0x11,0x20,0x09,0xD2,0xED,0x1F,0x0C,0x56,0x08,0xD5,0x0B,0x51,0x09,0x36,0x16,0x22,
			0x01,0x76,0x8F,0x7F,0x70,0x7C,0xB8,0xA7,0x9F,0x8B,0x7F,0x78,0x30,0xD4,0x39,0x40,
			0x01,0x1F,0x4F,0xBF,0xD0,0x08,0x88,0x7B,0x80,0xBC,0x50,0x3F,0x4F,0x04,0xC7,0xD1,
			0xCF,0x25,0xC8,0xDF,0xD3,0x05,0x2E,0xE9,0xE9,0x0F,0x72,0x6A,0x6E,0x6A,0x49,0x46,
			0x7E,0x4A,0x8D,0x7F,0x68,0x48,0x4D,0x62,0x51,0x51,0x62,0xA5,0x0D,0xB2,0xDB,0xED,
			0x74,0x18,0x00,0x74,0x50,0x50,0x20,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_ListNodes_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_ListNodes_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x4F,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0x77,0xA9,0xCC,0x4B,0xCC,0xCD,
			0x4C,0x76,0xCE,0xCF,0x2B,0x49,0xAD,0x28,0x51,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0x41,
			0x26,0xAD,0x73,0x53,0x4B,0x32,0xF2,0x53,0x6A,0x3C,0xFD,0x6A,0x8A,0x4B,0x8A,0x32,
			0xF3,0xD2,0x75,0xFC,0x43,0x43,0x6A,0x02,0x30,0xB4,0xEA,0x30,0x00,0x00,0x28,0x51,
			0x1B,0x05,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_GetNodeDynamicContext_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_GetNodeDynamicContext_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0xB1,0x00,0x00,0x80,0x78,0x01,0x0B,0x70,0x76,0x8E,0xF7,0xCD,0x4F,0x29,0xCD,0x49,
			0xF5,0xCC,0x4B,0xCB,0x57,0xF1,0xF4,0x0B,0x31,0x33,0xD1,0x09,0x00,0x0A,0x86,0x24,
			0xA6,0xEB,0x00,0x79,0xC6,0x46,0x50,0xB2,0xB8,0xA4,0x28,0x33,0x0F,0x55,0xC8,0x27,
			0xC4,0x37,0xD8,0xD5,0x07,0x24,0x0F,0xD4,0x63,0x0D,0xD5,0xA4,0x02,0x55,0x08,0xE2,
			0x86,0xA5,0x16,0x15,0x67,0xE6,0xE7,0x41,0xE4,0xA0,0x1C,0x90,0x15,0x70,0x43,0x21,
			0x6C,0xEB,0xDC,0xD4,0x92,0x8C,0xFC,0x94,0x1A,0x4F,0xBF,0x1A,0xA8,0x66,0xFF,0xD0,
			0x90,0x9A,0xC4,0xA2,0xA2,0xC4,0x4A,0x1B,0x90,0x31,0x08,0xF7,0xD9,0xE9,0x30,0x00,
			0x00,0x21,0xEA,0x38,0x91,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_ListModules_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_ListModules_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x39,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,
			0xA2,0x10,0x33,0x13,0x1D,0x20,0xA3,0xB8,0xA4,0x28,0x33,0x2F,0x1D,0x95,0x95,0x94,
			0x99,0x97,0x58,0x54,0xA9,0xE3,0x1F,0x1A,0x02,0x55,0xC7,0x00,0x00,0x5E,0xC4,0x13,
			0xF7,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_Execute_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_Execute_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x2E,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0x03,0xA2,0x10,0x33,0x13,0x1D,0x20,
			0x23,0xB5,0xA8,0x28,0xBF,0x08,0xC4,0x48,0xCA,0xCC,0x4B,0x2C,0xAA,0xD4,0x61,0x00,
			0x00,0x9D,0x70,0x10,0xCE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_OnExecuted_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_OnExecuted_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3F,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0x03,0xA2,0x10,0x33,0x13,0x1D,0x20,
			0x23,0xB5,0xA8,0x28,0xBF,0x08,0xC4,0x48,0xCA,0xCC,0x4B,0x2C,0xAA,0x04,0xB1,0x12,
			0x8B,0x8A,0x12,0x2B,0x6D,0x20,0x7C,0x3B,0x1D,0x06,0x00,0xFC,0x3B,0x17,0x2B,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_OnExecuted1_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_OnExecuted1_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x44,0x00,0x00,0x80,0x78,0x01,0x73,0xAD,0x48,0x4D,0x2E,0x2D,0x49,0x0D,0x2E,0x49,
			0x2C,0x49,0x55,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0xB1,0xCE,0x4D,0x2D,0xC9,0xC8,0x4F,
			0xA9,0xF1,0xF4,0xAB,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x01,0x0A,0x9B,0x99,0xD8,0xE9,
			0xF8,0x87,0x86,0x40,0x05,0x5C,0x91,0x34,0xD9,0xE9,0x30,0x00,0x00,0x43,0xDB,0x17,
			0xE7,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_QueryJobs_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_QueryJobs_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x19,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x33,0x13,0x1D,0x06,0x00,0x83,
			0xB1,0x08,0xF5,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_CancelJob_TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_CancelJob_TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x1C,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0x0F,0x0D,
			0xA9,0xF1,0xF4,0x0B,0x31,0x36,0xD2,0x41,0xB0,0x18,0x00,0x91,0x83,0x08,0xDE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_UDPLink__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_UDPLink__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x08,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0x61,0x00,0x00,
			0x0E,0xD3,0x02,0xFE,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_UDPLinkConfirm__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_UDPLinkConfirm__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x23,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0x4F,0x4E,
			0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,0xF4,0xAB,0xF1,0x0C,0x08,0xD0,0x01,0x52,
			0x49,0x99,0x79,0x89,0x45,0x95,0x3A,0x0C,0x00,0xF8,0x4D,0x0C,0xF9,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_SetRedirect__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_SetRedirect__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_SetTimeout__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_SetTimeout__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x22,0x00,0x00,0x80,0x78,0x01,0x2B,0xC8,0x2F,0x2E,0xC9,0xCC,0x4B,0x8F,0xCF,0x4D,
			0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0x03,0xA2,0x10,0x63,0x23,0x1D,0x38,0x83,0x01,
			0x00,0xE4,0xB8,0x0B,0x7F,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_SetSessionBufferSize__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_SetSessionBufferSize__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3A,0x00,0x00,0x80,0x78,0x01,0xCB,0x4D,0x2D,0xC9,0xC8,0x4F,0xA9,0xF1,0xF4,0xAB,
			0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,0xC1,0x10,
			0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,0x9A,0x78,
			0x15,0x41,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_MethodCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_MethodCheck__TypeInfo_len_ = bin.Length()-1;
	}

	{
		BYTE const chZipped[] =
		{
			0x3C,0x00,0x00,0x80,0x78,0x01,0x4B,0x4E,0xCC,0xC9,0x49,0x4A,0x4C,0xCE,0xAE,0xF1,
			0xF4,0xAB,0x49,0x2C,0x2A,0x4A,0xAC,0xB4,0x29,0x2E,0x29,0xCA,0xCC,0x4B,0xB7,0xD3,
			0xC1,0x10,0xF0,0x0F,0x0D,0x81,0x2A,0x71,0xF2,0xF7,0xF7,0xB1,0xD3,0x61,0x00,0x00,
			0xC2,0xD8,0x15,0xED,
		};
		static CBinary idTxt;
		CBinary& bin = idTxt;
		VERIFY(QuickUnzip(chZipped, sizeof(chZipped), bin));
		s_PCC_User_CallbackCheck__TypeInfo_ = (const char*)bin.Get();
		s_PCC_User_CallbackCheck__TypeInfo_len_ = bin.Length()-1;
	}

	END_LOCAL_SAFE_STATIC_OBJ(dummyVar);
}

class PCC_Center_RC : public PCC_Center_T
{
	friend class PCC_Center;
	friend class PCC_Center_S;
private:
	PCC_Center_RC(const PCC_Center_RC&);
	PCC_Center_RC& operator= (const PCC_Center_RC&);

public:
	explicit PCC_Center_RC(PCC_Center* owner = NULL);
	virtual ~PCC_Center_RC();

protected:
	void DestroyRequester();

	virtual TCPSError OnConnected()
	{
		if(m_owner)
			return m_owner->OnConnected();
		return TCPS_OK;
	}

	virtual void OnPeerBroken()
	{
		if(m_owner)
			m_owner->OnPeerBroken();
	}
	virtual void OnClose()
	{
		if(m_owner)
			m_owner->OnClose();
	}

	virtual void OnConnectTimeout(IN TCPSError cause)
	{
		if(m_owner)
			m_owner->OnConnectTimeout(cause);
	}

public:
	TCPSError SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	IPP GetServeIPP() const;
	IPP GetServingIPP() const;
	BOOL IsConnected() const;

	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	void PrepareDisconnect();

	void SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	void GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const;

	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

public:
	const PCC_Center::MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

public:
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

protected:
	virtual TCPSError AddModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{
		if(m_owner)
		{
			return m_owner->AddModelCenter(
					centerIPP
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError DelModelCenter(
				IN const IPP& centerIPP
				) posting_callback
	{
		if(m_owner)
		{
			return m_owner->DelModelCenter(
					centerIPP
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError GetStaticContext(
				OUT PCC_NodeDesc& staticContext
				) cacheable_callback
	{
		if(m_owner)
		{
			return m_owner->GetStaticContext(
					staticContext
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError GetDynamicContext(
				OUT PCC_DynamicContext& dynamicContext
				) callback
	{
		if(m_owner)
		{
			return m_owner->GetDynamicContext(
					dynamicContext
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError AddModel(
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) callback
	{
		if(m_owner)
		{
			return m_owner->AddModel(
					moduleProperty,
					modelFiles
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError DelModel(
				IN INT64 modelKey
				) callback
	{
		if(m_owner)
		{
			return m_owner->DelModel(
					modelKey
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	// 返回TCPS_OK允许重定向；返回非TCPS_OK禁止重定向
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		if(m_owner)
		{
			return m_owner->OnPrepareRedirect_(
					redirectIPP,
					redirectParam
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 //////
private:
	PCC_Center* const m_owner;
	iscm_ClientThreadIDs m_callingOutTIDs;
	DWORD m_sessionFlags;
	DWORD m_reconnectIntervalMSELs;
	DataOutfiter m_dataOutfiter;
	iscm_IRequester* m_rpcRequester;
	BOOL m_needBrokenNotify;
	BOOL m_prepareDisconnect;

	struct TAsyncTaskStat_
	{
		INT_PTR postingCallingBytes;// 正在等待执行的posting callback的总调用数据大小
		INT32 postingCallings;		// 正在等待执行的posting callback的调用数量
		long totalAsyncTasks;		// 总的正在执行的异步任务数量，等于postingCallings + 其它异步任务数
		TAsyncTaskStat_() : postingCallingBytes(0), postingCallings(0), totalAsyncTasks(0) {}
	};
	TAsyncTaskStat_ m_asyncTaskStat;

private:
	struct ReconnectTask_ : public NPBaseTask
	{
		PCC_Center_RC& face_;
		explicit ReconnectTask_(PCC_Center_RC& face) : face_(face) {}
		virtual ~ReconnectTask_() {}
		virtual void OnPoolTask()
		{
			// ReconnectTask_重连动作不同于OnConnectedFailedTask_，不做多服务IPP智能切换
			if(!face_.m_prepareDisconnect && face_.IsConnected())
				face_.m_rpcRequester->Reconnect();
			else
				ASSERT(true);
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
			tcps_Delete(this);
		}
	};
	friend struct ReconnectTask_;

private:
	void OnNetworkMalformed_()
	{
		if(m_prepareDisconnect || !m_rpcRequester->IsConnected())
			return;
		ReconnectTask_* task = tcps_NewEx(ReconnectTask_, (*this));
		VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
		FetchTaskPool()->Push(task);
	}

private:
	iscm_MatchingUpdateFlag m_methodMatchingUpdatedFlag;
	PCC_Center::MethodMatchingFlag m_methodMatchingFlag;
	TCPSError UpdateMethodMatchingFlag_();

private:
	iscm_PostingPendingParam m_postingPendingParam;

private:
	static TCPSError Wrap_AddModelCenter(PCC_Center_RC*, PCC_Center*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_callback;
	static TCPSError Wrap_DelModelCenter(PCC_Center_RC*, PCC_Center*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_callback;
	static TCPSError Wrap_GetStaticContext(PCC_Center_RC*, PCC_Center*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) cacheable_callback;
	static TCPSError Wrap_GetDynamicContext(PCC_Center_RC*, PCC_Center*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) callback;
	static TCPSError Wrap_AddModel(PCC_Center_RC*, PCC_Center*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) callback;
	static TCPSError Wrap_DelModel(PCC_Center_RC*, PCC_Center*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) callback;
	static TCPSError Wrap_SetRedirect_(PCC_Center_RC*, PCC_Center*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_callback;
	static TCPSError Wrap_CallbackCheck_(PCC_Center_RC*, PCC_Center*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) callback;

private:
	TCPSError UDPLink_(
				OUT INT32& servePort,
				OUT INT32& linkKey
				) method;

private:
	TCPSError UDPLinkConfirm_(
				) method;

private:
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		IPP ipp = m_rpcRequester->GetServingIPP();
		if(redirectIPP != ipp)
		{
			TCPSError err = this->OnPrepareRedirect_(redirectIPP, redirectParam);
			if(TCPS_OK != err)
				return err;

			struct SwitchTask : public NPBaseTask
			{
				long* totalAsyncTasks_;
				iscm_IRequester* requester_;
				IPP newIPP_;
				virtual void OnPoolTask()
				{
					requester_->TempSwitchTo(newIPP_);
					VERIFY(InterlockedDecrement(totalAsyncTasks_) >= 0);
					this->~SwitchTask();
					tcps_Free(this);
				}
			};
			SwitchTask* task = ::new(tcps_Alloc(sizeof(SwitchTask))) SwitchTask();
			task->totalAsyncTasks_ = &m_asyncTaskStat.totalAsyncTasks;
			task->requester_ = m_rpcRequester;
			task->newIPP_ = redirectIPP;
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
			FetchTaskPool()->Push(task);
		}
		return TCPS_OK;
	}

private:
	TCPSError SetTimeout_(
				IN INT32 recvTimeout,
				IN INT32 sendTimeout
				) posting_method;

private:
	TCPSError SetSessionBufferSize_(
				IN INT32 recvBufBytes,
				IN INT32 sendBufBytes
				) posting_method;

private:
	TCPSError MethodCheck_(
				IN const tcps_Array<tcps_String>& methods,
				IN const tcps_Array<tcps_String>& methodTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) method;

private:
	TCPSError CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback;

private:
	void OnPrepareRPCCallback_(
				IN const void* inParamsData,
				IN INT_PTR inParamsDataLen,
				OUT BOOL& notifyByTaskPool /*= true*/
				);
	TCPSError OnRPCCallback_(
				OUT BOOL& requireReplyData /*= true*/,
				IN const void* inParamsData,
				OUT BOOL& dataTransferred /*= false*/,
				IN INT_PTR inParamsDataLen,
				OUT iscm_IRPCOutfiter* outfiter
				);
	struct CallbackProxy_ : public iscm_ICallbackServeMan::IRPCClient
	{
		PCC_Center_RC& face_;
		INT32 sessionKey_;
		long callbackRefCount_;

		explicit CallbackProxy_(PCC_Center_RC& face)
			: face_(face), sessionKey_(0), callbackRefCount_(0)
			{}
		virtual INT32& GetSessionKey()
			{	return sessionKey_;	}
		virtual void IncreaseCallbackRef()
			{	ASSERT(callbackRefCount_ >= 0); InterlockedIncrement(&callbackRefCount_);	}
		virtual void DecreaseCallbackRef()
			{	ASSERT(callbackRefCount_ >= 1); InterlockedDecrement(&callbackRefCount_);	}
		virtual void OnCallbackInit()
			{}
		virtual void OnCallbackClose(
					TCPSError cause
					)
			{
				if(face_.m_prepareDisconnect || TCPS_OK==cause || !face_.m_rpcRequester->IsConnected())
					return;
				ReconnectTask_* task = tcps_NewEx(ReconnectTask_, (face_));
				VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);
				FetchTaskPool()->Push(task);
			}
		virtual void OnPrepareRPCCallback(
					IN const void* inParamsData,
					IN INT_PTR inParamsDataLen,
					OUT BOOL& notifyByTaskPool /*= true*/
					)
			{	face_.OnPrepareRPCCallback_(inParamsData, inParamsDataLen, notifyByTaskPool);	}
		virtual TCPSError OnRPCCallback(
					OUT BOOL& requireReplyData /*= true*/,
					IN const void* inParamsData,
					OUT BOOL& dataTransferred /*= false*/,
					IN INT_PTR inParamsDataLen,
					OUT iscm_IRPCOutfiter* outfiter
					)
		{
			TCPSError err;
			while(true)
			{
				err = face_.OnRPCCallback_(requireReplyData, inParamsData, dataTransferred, inParamsDataLen, outfiter);
				if(TCPS_ERR_POSTING_PENDING_FULL == err)
				{
					ASSERT(!dataTransferred);
					Sleep(1);
					continue;
				}
				else
					break;
			}
			return err;
		}
	};
	friend struct CallbackProxy_;
	CallbackProxy_ m_callbackProxy;

private:
	typedef TCPSError (*FCallbackHandler_)(
						IN PCC_Center_RC* thisObj /*= NULL*/,
						IN PCC_Center* faceObj /*= NULL*/,
						IN iscm_PeerCallFlags peerCallFlags,
						IN OUT const BYTE*& ptrInParams,
						IN OUT INT_PTR& ptrInParamsLen,
						OUT iscm_IRPCOutfiter* outfiter
						);
	struct CallbackSite_
	{
		FCallbackHandler_ handler;
		BOOL isPosting; // 是否为 posting 修饰的方法/回调
		explicit CallbackSite_(FCallbackHandler_ hd = NULL, BOOL pst = false)
			: handler(hd), isPosting(pst)
			{}
	};
	typedef CQuickStringMap<CPtrStrA, CallbackSite_, QSS_Traits<8> > CallbackMap_;
	static const CallbackMap_* sm_callbackMap;
	static CallbackMap_& GetCallbackMap_();
	static void InitCallbackMap_();

private:
	mutable CLocker m_callbackCallLock;
	struct PostingTask_ : public NPBaseTask
	{
		PCC_Center_RC& face_;
		iscm_PeerCallFlags peerCallFlags_;
		void* baseInParamsData_;
		CPtrStrA call_id_;
		const BYTE* inParamsData_;
		INT_PTR inParamsDataLen_;
		FCallbackHandler_ handler_;

		explicit PostingTask_(PCC_Center_RC& face) : face_(face) {}
		virtual ~PostingTask_() {}
		virtual void OnPoolTask()
		{
			ASSERT(baseInParamsData_ && inParamsData_ && inParamsDataLen_>=0);
			ASSERT((INT_PTR)(inParamsData_ - (const BYTE*)baseInParamsData_) > 0);
			INT_PTR const inParamsDataLen_t = inParamsDataLen_;
			if(!face_.m_prepareDisconnect && face_.IsConnected())
			{
				CNPAutoLock locker(face_.m_callbackCallLock);
				TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
				if(face_.m_owner)
				{
					void* replyData = NULL;
					INT_PTR replyLen = 0;
					err = face_.m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
					if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
					{
						if(face_.m_owner->IsStreamedCallbackMatched_(call_id_.p, call_id_.len))
						{
							err = face_.m_owner->StreamedCallback_(call_id_.p, call_id_.len, inParamsData_, inParamsDataLen_, replyData, replyLen);
							ASSERT(NULL==replyData && 0==replyLen);
							if(TCPS_OK == err)
							{
								inParamsData_ += inParamsDataLen_;
								inParamsDataLen_ = 0;
							}
							else if(TCPS_ERR_MALFORMED_REQ == err)
								face_.OnNetworkMalformed_();
						}
					}
				}
				if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
				{
					err = handler_(
								&face_, NULL,
								peerCallFlags_,
								inParamsData_,
								inParamsDataLen_,
								NULL/*outfiter*/
								);
				}
				ASSERT(TCPS_OK!=err || 0==inParamsDataLen_);
			}
			else
				ASSERT(true);

			tcps_Free(baseInParamsData_);
			PCC_Center_RC& face = face_;
			tcps_Delete(this);

			CNPAutoLock locker(face.m_postingCallbacks.lock);
			face.m_asyncTaskStat.postingCallingBytes -= inParamsDataLen_t;
			ASSERT(face.m_asyncTaskStat.postingCallingBytes >= 0);
			--(face.m_asyncTaskStat.postingCallings);
			ASSERT(face.m_asyncTaskStat.postingCallings >= 0);
			VERIFY(InterlockedDecrement(&face.m_asyncTaskStat.totalAsyncTasks) >= 0);

			ASSERT(face.m_postingCallbacks.calling);
			if(NULL == face.m_postingCallbacks.head)
			{
				face.m_postingCallbacks.calling = false;
				return; // 队列处理完毕
			}

			NPBaseTask* task = face.m_postingCallbacks.head;
			if(face.m_postingCallbacks.head == face.m_postingCallbacks.tail)
				face.m_postingCallbacks.head = face.m_postingCallbacks.tail = NULL;
			else
				face.m_postingCallbacks.head = task->m_nextPoolTask;
			// 此处无须对m_asyncTaskStat.postingCallings等变量进行增加（在OnRPCCallback_()已经加过）
			FetchTaskPool()->Push(task);
		}
	};
	friend struct PostingTask_;
	struct PostingTaskSite_
	{
		mutable CLocker lock;
		BOOL calling;
		NPBaseTask* head;
		NPBaseTask* tail;
		PostingTaskSite_() : calling(false), head(NULL), tail(NULL) {}
	};
	PostingTaskSite_ m_postingCallbacks;

private:
	struct PostingProxy_ : public iscm_IPostingCallerMan::INotifier
	{
		PCC_Center_RC& face_;
		INT32 callerKey_; // 为iscm_IPostingCallerMan中的会话标识

		explicit PostingProxy_(PCC_Center_RC& face)
			: face_(face), callerKey_(0)
			{}

		virtual void OnSessionClose(
					IN INT32 callerKey,
					IN TCPSError cause
					)
		{
			(void)callerKey; (void)cause;
			ASSERT(callerKey_ == callerKey);
			callerKey_ = 0;
		}

		virtual void OnSessionPost(
					IN INT32 callerKey,
					IN const void* data,
					IN INT_PTR dataLen,
					OUT BOOL& dataTransferred /*= false*/
					)
		{
			(void)callerKey;
			ASSERT(callerKey_ == callerKey);
			while(true)
			{
				BOOL requireReplyData = true;
				TCPSError err = face_.OnRPCCallback_(requireReplyData, data, dataTransferred, dataLen, NULL);
				ASSERT(TCPS_OK!=err || !requireReplyData);
				if(TCPS_ERR_POSTING_PENDING_FULL == err)
				{
					ASSERT(!dataTransferred);
					Sleep(1);
					continue;
				}
				else
					break;
			}
		}
	};
	friend struct PostingProxy_;
	PostingProxy_ m_postingProxy;

private:
	struct NetworkHandler_ : public iscm_IRequester::IEventHandler
	{
		PCC_Center_RC& face_;
		explicit NetworkHandler_(PCC_Center_RC& face) : face_(face) {}
		virtual BOOL Notify(
					IN iscm_IRequester::EventType ev,
					IN TCPSError cause,
					OUT TCPSError* actionErr /*= NULL*/
					);
	};
	friend struct NetworkHandler_;
	NetworkHandler_ m_networkHandler;

private:
	struct OnConnectedFailedTask_ : public NPBaseTask
	{
		PCC_Center_RC& face_;
		explicit OnConnectedFailedTask_(PCC_Center_RC& face) : face_(face) {}
		virtual ~OnConnectedFailedTask_() {}
		virtual void OnPoolTask()
		{
			// 停止以前连接
			IPP clientID_IPP, secondaryServeIPP, tertiaryServeIPP;
			IPP serveIPP = face_.m_rpcRequester->GetServeIPP(NULL, &clientID_IPP, &secondaryServeIPP, &tertiaryServeIPP);
			face_.SetServeIPP(INVALID_IPP, face_.m_sessionFlags, INVALID_IPP, INVALID_IPP, INVALID_IPP, face_.m_reconnectIntervalMSELs);

			// 切换IPP后再次异步延迟建立连接
			if(serveIPP.IsValid())
			{
				BOOL const ippSwitched = iscm_ThreeIPPSwitch(serveIPP, secondaryServeIPP, tertiaryServeIPP);
				DWORD delayTicks = face_.m_reconnectIntervalMSELs;
				if(ippSwitched)
					delayTicks = min((DWORD)500, delayTicks);
				face_.m_rpcRequester->SetServeIPP(serveIPP, "PCC_Center", iscm_IRequester::cflag_async_connect, clientID_IPP, delayTicks, secondaryServeIPP, tertiaryServeIPP);
				face_.m_prepareDisconnect = false;
			}
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
			tcps_Delete(this);
		}
	};
	friend struct OnConnectedFailedTask_;

private:
	struct UDPCallbackProxy_ : public iscm_IUDPSession
	{
		PCC_Center_RC& face_;
		BOOL isUsing_;
		explicit UDPCallbackProxy_(PCC_Center_RC& face)
			: face_(face), isUsing_(false)
			{}
		virtual void OnUDPCall(
					IN tcps_Binary& frame
					);
	};
	friend struct UDPCallbackProxy_;
	UDPCallbackProxy_ m_UDPCallbackProxy;

private:
	struct StreamedCall_Task_;
	friend struct StreamedCall_Task_;

// posting method方法的异步投递任务类声明，
// 在回调里面调用自身的方法时，使用异步任务（防止死锁）。
private:
	struct SetTimeout__Task_;
	friend struct SetTimeout__Task_;
	struct SetSessionBufferSize__Task_;
	friend struct SetSessionBufferSize__Task_;
};

TCPSError PCC_Center_RC::CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback
{
	if(0==callbacks.Length() || callbacks.Length()!=callbackTypeInfos.Length())
		return TCPS_ERR_INVALID_PARAM;

	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<7> > CallbackMap_;
	static CallbackMap_* s_cbMap = NULL;
	if(NULL == s_cbMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_cbMap)
		{
			static CallbackMap_ s_cbMapObj;
			CallbackMap_& cbMap = s_cbMapObj;
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModelCenter"), CPtrStrA(s_PCC_Center_AddModelCenter_TypeInfo_, s_PCC_Center_AddModelCenter_TypeInfo_len_))).second);
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("DelModelCenter"), CPtrStrA(s_PCC_Center_DelModelCenter_TypeInfo_, s_PCC_Center_DelModelCenter_TypeInfo_len_))).second);
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetStaticContext"), CPtrStrA(s_PCC_Center_GetStaticContext_TypeInfo_, s_PCC_Center_GetStaticContext_TypeInfo_len_))).second);
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetDynamicContext"), CPtrStrA(s_PCC_Center_GetDynamicContext_TypeInfo_, s_PCC_Center_GetDynamicContext_TypeInfo_len_))).second);
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModel"), CPtrStrA(s_PCC_Center_AddModel_TypeInfo_, s_PCC_Center_AddModel_TypeInfo_len_))).second);
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("DelModel"), CPtrStrA(s_PCC_Center_DelModel_TypeInfo_, s_PCC_Center_DelModel_TypeInfo_len_))).second);
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetRedirect_"), CPtrStrA(s_PCC_Center_SetRedirect__TypeInfo_, s_PCC_Center_SetRedirect__TypeInfo_len_))).second);
			s_cbMap = &cbMap;
		}
	}

	matchingFlags.Resize(callbacks.Length());
	for(int index=0; index<callbacks.Length(); ++index)
	{
		BOOL& flag = matchingFlags[index];
		const tcps_String& name = callbacks[index];
		const tcps_String& typeInfos = callbackTypeInfos[index];
		CallbackMap_::const_iterator cit = s_cbMap->find(name.Get(), name.Length());
		if(cit!=s_cbMap->end() && 0==typeInfos.Compare(cit->second.p, cit->second.len))
			flag = true;
		else
			flag = false;
	}
	return TCPS_OK;
}

PCC_Center::MethodMatchingFlag::MethodMatchingFlag()
{
	Reset();
	mmap_.insert(std::make_pair(CPtrStrA("UDPLink_", 8), Info(&matching_UDPLink_, false)));
	mmap_.insert(std::make_pair(CPtrStrA("UDPLinkConfirm_", 15), Info(&matching_UDPLinkConfirm_, false)));
	mmap_.insert(std::make_pair(CPtrStrA("SetTimeout_", 11), Info(&matching_SetTimeout_, true)));
	mmap_.insert(std::make_pair(CPtrStrA("SetSessionBufferSize_", 21), Info(&matching_SetSessionBufferSize_, true)));
}

void PCC_Center::MethodMatchingFlag::Reset()
{
	matching_UDPLink_ = false;
	matching_UDPLinkConfirm_ = false;
	matching_SetTimeout_ = false;
	matching_SetSessionBufferSize_ = false;
}

TCPSError PCC_Center_RC::UpdateMethodMatchingFlag_()
{
	if(!m_methodMatchingUpdatedFlag.needUpdate)
		return TCPS_OK;
	InitializeAllCallsTypeInfo_();
	tcps_String methods_ar[4];
	IN tcps_Array<tcps_String> methods;
	methods.Attach(xat_bind, methods_ar, 4);
	tcps_String methodTypeInfos_ar[4];
	IN tcps_Array<tcps_String> methodTypeInfos;
	methodTypeInfos.Attach(xat_bind, methodTypeInfos_ar, 4);
	methods_ar[0].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("UDPLink_"));
	methodTypeInfos_ar[0].Attach(xat_bind, (char*)s_PCC_Center_UDPLink__TypeInfo_, s_PCC_Center_UDPLink__TypeInfo_len_);
	methods_ar[1].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("UDPLinkConfirm_"));
	methodTypeInfos_ar[1].Attach(xat_bind, (char*)s_PCC_Center_UDPLinkConfirm__TypeInfo_, s_PCC_Center_UDPLinkConfirm__TypeInfo_len_);
	methods_ar[2].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetTimeout_"));
	methodTypeInfos_ar[2].Attach(xat_bind, (char*)s_PCC_Center_SetTimeout__TypeInfo_, s_PCC_Center_SetTimeout__TypeInfo_len_);
	methods_ar[3].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetSessionBufferSize_"));
	methodTypeInfos_ar[3].Attach(xat_bind, (char*)s_PCC_Center_SetSessionBufferSize__TypeInfo_, s_PCC_Center_SetSessionBufferSize__TypeInfo_len_);
	OUT tcps_Array<BOOL> matchingFlags;
	TCPSError err = this->MethodCheck_(methods, methodTypeInfos, matchingFlags);
	if(TCPS_OK == err)
	{
		if(matchingFlags.Length() == methods.Length())
		{
			m_methodMatchingUpdatedFlag.needUpdate = false;
			const BOOL* const matchingFlags_p = matchingFlags.Get();
			m_methodMatchingFlag.matching_UDPLink_ = matchingFlags_p[0];
			m_methodMatchingFlag.matching_UDPLinkConfirm_ = matchingFlags_p[1];
			m_methodMatchingFlag.matching_SetTimeout_ = matchingFlags_p[2];
			m_methodMatchingFlag.matching_SetSessionBufferSize_ = matchingFlags_p[3];
		}
		else
		{
			ASSERT(false);
			err = TCPS_ERR_MALFORMED_REPLY;
		}
	}
	if(m_methodMatchingUpdatedFlag.needUpdate)
		m_methodMatchingFlag.Reset();
	return err;
}

const PCC_Center::MethodMatchingFlag& PCC_Center_RC::GetMethodMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	TCPSError ret = UpdateMethodMatchingFlag_();
	if(err)
		*err = ret;
	return m_methodMatchingFlag;
}

BOOL PCC_Center_RC::NetworkHandler_::Notify(
				IN iscm_IRequester::EventType ev,
				IN TCPSError cause,
				OUT TCPSError* actionErr /*= NULL*/
				)
{
	if(actionErr)
		*actionErr = TCPS_OK;
	if(iscm_IRequester::et_connected==ev || iscm_IRequester::et_attached==ev)
	{
		if(face_.m_prepareDisconnect)
			return true;
	}

	if(iscm_IRequester::et_connected == ev)
	{
#if 1
		// 建立回调通道
		if(0 == (face_.m_sessionFlags&ISCMC_NO_CALLBACK))
		{
			// 连接回调通道，使用直接连接方式
			IPP const serveIPP = face_.m_rpcRequester->GetServingIPP();
			INT32 peerSessionKey;
			INT64 const bindID = face_.m_rpcRequester->GetPeerSessionKey(peerSessionKey);
			ASSERT(serveIPP.IsValid() && 0!=bindID && 0!=peerSessionKey);

			AutoDeleteInterface<iscm_IRequester> autoRequester;
			autoRequester.face_ = iscm_MakeRequester(false);
			if(NULL == autoRequester.face_)
			{
				// 容错处理
				ASSERT(false);
				if(actionErr)
					*actionErr = TCPS_ERR_OUT_OF_MEMORY;
				return false;
			}

			DWORD connectTimeout = INFINITE;
			DWORD recvTimeout = INFINITE;
			DWORD sendTimeout = INFINITE;
			face_.m_rpcRequester->GetTimeout(&connectTimeout, &recvTimeout, &sendTimeout);
			DWORD const timeoutMSELs = (INFINITE==connectTimeout ? iscm_GetDefaultConnectTimeout() : connectTimeout);
			BOOL const is_AF_LOCAL = tcps_Use_AF_LOCAL(serveIPP.ip_);
			SOCKET cbSock = TCPNewClientByTime(serveIPP.ip_, serveIPP.port_, timeoutMSELs, is_AF_LOCAL);
			if(!SockValid(cbSock))
			{
				if(actionErr)
					*actionErr = TCPS_ERR_CONNECT_FAILED;
				return false;
			}

			iscm_IRequester* callbackRequester = autoRequester.face_;
			VERIFY(TCPS_OK == callbackRequester->AttachSocket(cbSock, true));

			// 若应用程序没有调用过SetTimeout()，则此处使用有限时间超时（ISCM对同步RPC调用默认使用超长时间超时，见'iscm_requester.cpp'）
			recvTimeout = (INFINITE==recvTimeout ? 2000 : recvTimeout);
			sendTimeout = (INFINITE==sendTimeout ? 1000 : sendTimeout);
			callbackRequester->SetTimeout(INFINITE, recvTimeout, sendTimeout);

			SockWriteBuf swb[2];
			swb[0].data = &bindID;
			swb[0].len = sizeof(bindID);
			swb[1].data = &peerSessionKey;
			swb[1].len = sizeof(peerSessionKey);
			tcps_Binary reply;
			TCPSError err = callbackRequester->Call(RPCCT_TO_CALLBACK, swb, ARRAY_LEN(swb), reply);
			if(TCPS_OK != err)
			{
				if(actionErr)
					*actionErr = err;
				return false;
			}
			ASSERT(reply.IsEmpty());

			VERIFY(cbSock == callbackRequester->DropSocket());
			face_.m_callbackProxy.IncreaseCallbackRef();
			iscm_FetchCallbackServeMan().AddCallbackClient(&face_.m_callbackProxy, cbSock);
		}
#endif

#if 1
		// 建立posting通道
		if(0 == (face_.m_sessionFlags&ISCMC_NO_POSTING_CHANNEL)
			&& 0 == (face_.m_sessionFlags&ISCMC_UDP_POSTING)
			)
		{
			// 连接posting通道，使用直接连接方式
			SOCKET postingSock = INVALID_SOCKET;

			AutoDeleteInterface<iscm_IRequester> autoRequester;
			autoRequester.face_ = iscm_MakeRequester(false);
			if(NULL == autoRequester.face_)
			{
				// 容错处理
				ASSERT(false);
				if(actionErr)
					*actionErr = TCPS_ERR_OUT_OF_MEMORY;
				return false;
			}

			DWORD connectTimeout = INFINITE;
			DWORD recvTimeout = INFINITE;
			DWORD sendTimeout = INFINITE;
			face_.m_rpcRequester->GetTimeout(&connectTimeout, &recvTimeout, &sendTimeout);
			DWORD const timeoutMSELs = (INFINITE==connectTimeout ? iscm_GetDefaultConnectTimeout() : connectTimeout);
			INT32 peerSessionKey;
			INT64 const bindID = face_.m_rpcRequester->GetPeerSessionKey(peerSessionKey);
			ASSERT(0!=bindID && 0!=peerSessionKey);

			IPP const serveIPP = face_.m_rpcRequester->GetServingIPP();
			ASSERT(serveIPP.IsValid());
			BOOL is_AF_LOCAL = tcps_Use_AF_LOCAL(serveIPP.ip_);
			postingSock = TCPNewClientByTime(serveIPP.ip_, serveIPP.port_, timeoutMSELs, is_AF_LOCAL);
			if(!SockValid(postingSock))
			{
				if(actionErr)
					*actionErr = TCPS_ERR_CONNECT_FAILED;
				return false;
			}

			iscm_IRequester* postingRequester = autoRequester.face_;
			VERIFY(TCPS_OK == postingRequester->AttachSocket(postingSock, true));

			// 若应用程序没有调用过SetTimeout()，则此处使用有限时间超时（ISCM对同步RPC调用默认使用超长时间超时，见'iscm_requester.cpp'）
			recvTimeout = (INFINITE==recvTimeout ? 2000 : recvTimeout);
			sendTimeout = (INFINITE==sendTimeout ? 1000 : sendTimeout);
			postingRequester->SetTimeout(INFINITE, recvTimeout, sendTimeout);

			SockWriteBuf swb[2];
			swb[0].data = &bindID;
			swb[0].len = sizeof(bindID);
			swb[1].data = &peerSessionKey;
			swb[1].len = sizeof(peerSessionKey);
			tcps_Binary reply;
			TCPSError err = postingRequester->Call(RPCCT_TO_POSTING_CHANNEL, swb, ARRAY_LEN(swb), reply);
			/*if(TCPS_OK != err)
			{
				if(TCPS_ERR_NOT_SUPPORTED != err)
				{
					if(actionErr)
						*actionErr = err;
					return false;
				}
			}*/
			ASSERT(reply.IsEmpty());

			if(TCPS_OK == err)
			{
				VERIFY(postingSock == postingRequester->DropSocket());
				iscm_FetchPostingCallerMan().AddSession(face_.m_postingProxy.callerKey_, postingSock, true, &face_.m_postingProxy);
			}
		}
#endif
	}
	else if(iscm_IRequester::et_broken==ev || iscm_IRequester::et_dropped==ev)
	{
		// 总尝试删除一次
#if 1
		iscm_FetchCallbackServeMan().DelCallbackClient(&face_.m_callbackProxy);
#endif
#if 1
		if(0 != face_.m_postingProxy.callerKey_)
			iscm_FetchPostingCallerMan().CloseSession(face_.m_postingProxy.callerKey_);
#endif
	}

	if(iscm_IRequester::et_connected==ev || iscm_IRequester::et_attached==ev)
	{
		ASSERT(!face_.m_UDPCallbackProxy.isUsing_);
		while(ISCMC_UDP_POSTING&face_.m_sessionFlags)
		{
			AutoSock udpSock;
			udpSock.sock_ = UDPNew();
			if(!SockValid(udpSock.sock_))
				break;
			IPP localIPP = SockGetLocal(face_.m_rpcRequester->GetSocket());
			if(!localIPP.IsValid())
				break;
			if(TCPS_OK != tcps_AutoBindUDPPort(udpSock.sock_, localIPP.ip_, &localIPP.port_))
				break;

			INT32 serveUDPPort = -1;
			INT32 udpLinkKey = 0;
			TCPSError err = face_.UDPLink_(serveUDPPort, udpLinkKey);
			if(TCPS_OK == err)
			{
				ASSERT(0 != udpLinkKey);
				IPP peerIPP = face_.GetServingIPP();
				if(0 != UDPConnect(udpSock.sock_, peerIPP.ip_, serveUDPPort))
					break;
				iscm_UDPFrag linkFrag;
				linkFrag.fragType = ISCM_UDP_FRAG_LINK;
				linkFrag.dummyI32 = 0;
				linkFrag.sendKey = udpLinkKey;
				linkFrag.fragNum = 0;
				int r = SockWrite(udpSock.sock_, &linkFrag, sizeof(linkFrag));
				if((int)sizeof(linkFrag) != r)
					break;
				err = face_.UDPLinkConfirm_();
				if(TCPS_OK != err)
					break;
				INT32 sessionID;
				face_.m_rpcRequester->GetPeerSessionKey(sessionID);
				iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
				udpServer.AddSession(sessionID, udpSock.Drop(), &face_.m_UDPCallbackProxy);
				face_.m_UDPCallbackProxy.isUsing_ = true;
			}
			break;
		}
		// 忽略UDP连接错误，若UDP连接失败，则只使用TCP

		DWORD recvTimeout = INFINITE;
		DWORD sendTimeout = INFINITE;
		face_.GetTimeout(NULL, &recvTimeout, &sendTimeout);
		if(INFINITE!=recvTimeout || INFINITE!=sendTimeout)
			face_.SetTimeout_(recvTimeout, sendTimeout);

		INT32 recvBufBytes = -1;
		INT32 sendBufBytes = -1;
		face_.GetSessionBufferSize(&recvBufBytes, &sendBufBytes);
		if(recvBufBytes>=0 || sendBufBytes>=0)
			face_.SetSessionBufferSize_(recvBufBytes, sendBufBytes);
		if((0 == (face_.m_sessionFlags&ISCMC_NO_CALLBACK)) && (recvBufBytes>=0 || sendBufBytes>=0))
		{
			iscm_ICallbackServeMan& man = iscm_FetchCallbackServeMan();
			man.SetSessionBufferSize(&face_.m_callbackProxy, recvBufBytes, sendBufBytes);
		}

		ASSERT(!face_.m_needBrokenNotify);
		face_.m_needBrokenNotify = true;
		TCPSError err = TCPS_ERROR;

		// 此处对m_asyncTaskStat.totalAsyncTasks提前加一，以防止如下情况发生：
		// 当用户程序在OnConnected()中异步投递了删除本Client对象的任务，且返回非TCPS_OK；
		// 此时可能OnConnectedFailedTask_::OnPoolTask()被执行时，本Client对象已经被析构，
		// 导致非法内存错误。
		VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);

		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnConnected);
			try
			{
				err = face_.OnConnected();
			}
			catch(TCPSError ret)
			{
				ASSERT(TCPS_OK != ret);
				err = ret;
			}
			catch(int ret)
			{
				ASSERT(TCPS_OK != ret);
				err = (TCPSError)ret;
			}
			catch(std::bad_alloc)
			{
				err = TCPS_ERR_OUT_OF_MEMORY;
			}
			ISCM_BEGIN_CATCH_ALL_()
				err = TCPS_ERR_UNKNOWN_EXCEPTION;
			ISCM_END_CATCH_ALL_()
		}

		if(TCPS_OK!=err && 0==(ISCMC_NO_ASYNC_RECONNECT&face_.m_sessionFlags))
		{
			// 在OnConnected()之前引用计数已经加一，此处不能再加
		//	VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);
			OnConnectedFailedTask_* task = tcps_NewEx(OnConnectedFailedTask_, (face_));
			FetchTaskPool()->Push(task);
		}
		else
		{
			// OnConnected()返回成功，对在OnConnected()之前的引用计数加一做对称处理
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		}
		if(actionErr)
			*actionErr = err;
	}
	else if(iscm_IRequester::et_connect_timeout == ev)
	{
		iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnConnectTimeout);
		ISCM_BEGIN_TRY_()
			face_.OnConnectTimeout(cause);
		ISCM_END_TRY_()
		ISCM_BEGIN_CATCH_ALL_()
		ISCM_END_CATCH_ALL_()
	}
	else
	{
		ASSERT(iscm_IRequester::et_broken==ev || iscm_IRequester::et_dropped==ev);
		if(0 != face_.m_postingProxy.callerKey_)
			iscm_FetchPostingCallerMan().CloseSession(face_.m_postingProxy.callerKey_);
		ASSERT(face_.m_callbackProxy.callbackRefCount_ >= 0);
		while(face_.m_callbackProxy.callbackRefCount_ > 0)
			Sleep(1);
		while(0 != face_.m_postingProxy.callerKey_)
			Sleep(1);
		while(face_.m_asyncTaskStat.postingCallings > 0)
			Sleep(1);
		ASSERT(0==face_.m_asyncTaskStat.postingCallingBytes && 0==face_.m_asyncTaskStat.postingCallings);
		if(face_.m_needBrokenNotify)
		{
			face_.m_needBrokenNotify = false;
			{
				iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnClose);
				ISCM_BEGIN_TRY_()
					if(face_.m_owner && (INVALID_OSTHREADID==face_.m_owner->GetClosingTID_() || OSThreadSelf()!=face_.m_owner->GetClosingTID_()))
						face_.OnPeerBroken();
					face_.OnClose();
				ISCM_END_TRY_()
				ISCM_BEGIN_CATCH_ALL_()
				ISCM_END_CATCH_ALL_()
			}

			if(face_.m_UDPCallbackProxy.isUsing_)
			{
				face_.m_UDPCallbackProxy.isUsing_ = false;
				INT32 sessionID;
				face_.m_rpcRequester->GetPeerSessionKey(sessionID);
				iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
				udpServer.CloseSession(sessionID);
			}
		}
	}
	face_.m_methodMatchingUpdatedFlag.needUpdate = true;

	return true;
}

const PCC_Center_RC::CallbackMap_* PCC_Center_RC::sm_callbackMap = NULL;
PCC_Center_RC::CallbackMap_& PCC_Center_RC::GetCallbackMap_()
	{	LOCAL_SAFE_STATIC_OBJ(CallbackMap_);	}

void PCC_Center_RC::InitCallbackMap_()
{
	if(sm_callbackMap)
		return;
	IscmRPCGlobalLocker locker;
	if(sm_callbackMap)
		return;
	CallbackMap_& cbMap = GetCallbackMap_();
	ASSERT(0 == cbMap.size());
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::AddModelCenter"), CallbackSite_(&PCC_Center_RC::Wrap_AddModelCenter, true))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::DelModelCenter"), CallbackSite_(&PCC_Center_RC::Wrap_DelModelCenter, true))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::GetStaticContext"), CallbackSite_(&PCC_Center_RC::Wrap_GetStaticContext, false))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::GetDynamicContext"), CallbackSite_(&PCC_Center_RC::Wrap_GetDynamicContext, false))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::AddModel"), CallbackSite_(&PCC_Center_RC::Wrap_AddModel, false))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::DelModel"), CallbackSite_(&PCC_Center_RC::Wrap_DelModel, false))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::SetRedirect_"), CallbackSite_(&PCC_Center_RC::Wrap_SetRedirect_, true))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Center::CallbackCheck_"), CallbackSite_(&PCC_Center_RC::Wrap_CallbackCheck_, false))).second);
	sm_callbackMap = &cbMap;
}

PCC_Center_RC::PCC_Center_RC(PCC_Center* owner /*= NULL*/)
	: m_owner(owner)
	, m_sessionFlags(0)
	, m_reconnectIntervalMSELs(2000)
	, m_rpcRequester(iscm_MakeRequester(false))
	, m_needBrokenNotify(false)
	, m_prepareDisconnect(false)
	, m_callbackProxy(*this)
	, m_postingProxy(*this)
	, m_networkHandler(*this)
	, m_UDPCallbackProxy(*this)
{
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_String*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_Binary*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_Array<int>*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((CPtrStrA*)64)->len));

	m_rpcRequester->SetEventHandler(&m_networkHandler);
	iscm_InitClientSingletons(true, true);
	InitCallbackMap_();
}

PCC_Center_RC::~PCC_Center_RC()
{
	DestroyRequester();
}

void PCC_Center_RC::DestroyRequester()
{
	if(NULL == m_rpcRequester)
		return;
	NPR_ASSERT_EX(!m_callingOutTIDs.HasFlag(OSThreadSelf(), NULL), "禁止在对象自己的调用里删除自身");
	PrepareDisconnect();
	while(0 != m_postingProxy.callerKey_)
		Sleep(1);
	ASSERT(m_callbackProxy.callbackRefCount_ >= 0);
	while(m_callbackProxy.callbackRefCount_ > 0)
		Sleep(1);
	ASSERT(m_asyncTaskStat.postingCallingBytes>=0 && m_asyncTaskStat.postingCallings>=0 && m_asyncTaskStat.totalAsyncTasks>=0);
	while(m_asyncTaskStat.totalAsyncTasks > 0)
		Sleep(1);
	ASSERT(0==m_asyncTaskStat.postingCallingBytes && 0==m_asyncTaskStat.postingCallings);
	m_rpcRequester->DeleteThis();
	m_rpcRequester = NULL;
}

TCPSError PCC_Center_RC::SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	NPR_ASSERT_EX(!m_callingOutTIDs.HasFlag(OSThreadSelf(), NULL), "禁止在对象自己的调用里调用此函数");
	m_sessionFlags = sessionFlags;
	m_sessionFlags &= ~ISCMC_NO_CALLBACK; // 本接口支持重定向，总启动回调（忽略ISCMC_NO_CALLBACK标志）
	m_reconnectIntervalMSELs = max((DWORD)10, reconnectIntervalMSELs);
	DWORD t1, t2, t3;
	m_rpcRequester->GetTimeout(&t1, &t2, &t3, NULL);
	m_rpcRequester->SetTimeout(t1, t2, t2, m_reconnectIntervalMSELs);
	iscm_IRequester::ConnectFlag cflag;
	if(ISCMC_ASYNC_CONNECT&sessionFlags)
		cflag = iscm_IRequester::cflag_async_connect;
	else if(ISCMC_NO_ASYNC_RECONNECT&sessionFlags)
		cflag = iscm_IRequester::cflag_wait_no_reconnect;
	else
		cflag = iscm_IRequester::cflag_wait_async_reconnect;
	TCPSError err = m_rpcRequester->SetServeIPP(serveIPP, "PCC_Center", cflag, clientID_IPP, 0, secondaryServeIPP, tertiaryServeIPP);
	if(serveIPP.IsValid())
		m_prepareDisconnect = false;
	return err;
}

IPP PCC_Center_RC::GetServeIPP() const
	{	return m_rpcRequester->GetServeIPP();	}

IPP PCC_Center_RC::GetServingIPP() const
	{	return m_rpcRequester->GetServingIPP();	}

BOOL PCC_Center_RC::IsConnected() const
	{	return m_rpcRequester->IsConnected();	}

void PCC_Center_RC::SetKeeping(
			IN BOOL keeping
			)
	{	m_rpcRequester->SetKeeping(keeping);	}

BOOL PCC_Center_RC::IsKeeping() const
	{	return m_rpcRequester->IsKeeping();	}

void PCC_Center_RC::PrepareDisconnect()
{
	m_prepareDisconnect = true;
	m_rpcRequester->PrepareDisconnect();
	if(0 != m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().CloseSession(m_postingProxy.callerKey_);
	iscm_FetchCallbackServeMan().DelCallbackClient(&m_callbackProxy);
	if(m_UDPCallbackProxy.isUsing_)
	{
		m_UDPCallbackProxy.isUsing_ = false;
		INT32 sessionID;
		m_rpcRequester->GetPeerSessionKey(sessionID);
		iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
		udpServer.CloseSession(sessionID, true);
	}
}

void PCC_Center_RC::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	m_rpcRequester->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	if(IsConnected())
		SetTimeout_(recvTimeout, sendTimeout);
}

void PCC_Center_RC::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const
	{	m_rpcRequester->GetTimeout(connectTimeout, recvTimeout, sendTimeout);	}

void PCC_Center_RC::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	if(recvBufBytes<0 && sendBufBytes<0)
		return;
	m_rpcRequester->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	if(0 == (m_sessionFlags&ISCMC_NO_CALLBACK))
	{
		iscm_ICallbackServeMan& man = iscm_FetchCallbackServeMan();
		man.SetSessionBufferSize(&m_callbackProxy, recvBufBytes, sendBufBytes);
	}
	if(IsConnected())
		SetSessionBufferSize_(recvBufBytes, sendBufBytes);
}

void PCC_Center_RC::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
	{	m_rpcRequester->GetSessionBufferSize(recvBufBytes, sendBufBytes);	}

void PCC_Center_RC::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
	{	m_postingPendingParam.Set(maxPendingBytes, maxPendings);	}

void PCC_Center_RC::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
	{	m_postingPendingParam.Get(maxPendingBytes, maxPendings);	}

void PCC_Center_RC::OnPrepareRPCCallback_(
				IN const void* inParamsData,
				IN INT_PTR inParamsDataLen,
				OUT BOOL& notifyByTaskPool /*= true*/
				)
{
#if 1
	// 所有调用都用taskPool异步方式，以保证不同会话的并行调用
	ASSERT(inParamsData && inParamsDataLen>0 && notifyByTaskPool);
	(void)inParamsData; (void)inParamsDataLen; (void)notifyByTaskPool;
#else
	ASSERT(inParamsData && inParamsDataLen>0 && notifyByTaskPool);
	const BYTE* ptrInParams = (const BYTE*)inParamsData;
	INT_PTR ptrInParamsLen = inParamsDataLen;

	if(ptrInParamsLen < (int)sizeof(iscm_PeerCallFlags))
		return;
	iscm_PeerCallFlags peerCallFlags = *(iscm_PeerCallFlags*)ptrInParams;
	if((int)sizeof(BOOL) != peerCallFlags.sizeofBOOL_req)
		return;
	if((int)sizeof(DummyEnumType) != peerCallFlags.sizeofEnum_req)
		return;
	ptrInParams += sizeof(iscm_PeerCallFlags);
	ptrInParamsLen -= sizeof(iscm_PeerCallFlags);

	if(ptrInParamsLen < (int)sizeof(INT32))
		return;
	INT32 call_id_len = *(INT32*)ptrInParams;
	ptrInParams += sizeof(INT32);
	ptrInParamsLen -= sizeof(INT32);
	if(ptrInParamsLen < call_id_len+1)
		return;
	const char* call_id = (const char*)ptrInParams;
	ptrInParams += call_id_len+1;
	ptrInParamsLen -= call_id_len+1;

	ASSERT(sm_callbackMap);
	CallbackMap_::const_iterator cit = sm_callbackMap->find(call_id, call_id_len);
	if(sm_callbackMap->end() == cit)
		return;

	if(cit->second.isPosting)
		notifyByTaskPool = false;
#endif
}

TCPSError PCC_Center_RC::OnRPCCallback_(
				OUT BOOL& requireReplyData /*= true*/,
				IN const void* inParamsData,
				OUT BOOL& dataTransferred /*= false*/,
				IN INT_PTR inParamsDataLen,
				OUT iscm_IRPCOutfiter* outfiter
				)
{
	(void)inParamsDataLen; // avoid warning.
	ASSERT(requireReplyData && inParamsData && inParamsDataLen>0/* && outfiter*/);
	const BYTE* ptrInParams = (const BYTE*)inParamsData;
	INT_PTR ptrInParamsLen = inParamsDataLen;

	if(ptrInParamsLen < (int)sizeof(iscm_PeerCallFlags))
		return TCPS_ERR_MALFORMED_REQ;
	iscm_PeerCallFlags peerCallFlags = *(iscm_PeerCallFlags*)ptrInParams;
	if((int)sizeof(BOOL) != peerCallFlags.sizeofBOOL_req)
		return TCPS_ERR_MALFORMED_REQ;
	if((int)sizeof(DummyEnumType) != peerCallFlags.sizeofEnum_req)
		return TCPS_ERR_MALFORMED_REQ;
	ptrInParams += sizeof(iscm_PeerCallFlags);
	ptrInParamsLen -= sizeof(iscm_PeerCallFlags);

	if(ptrInParamsLen < (int)sizeof(INT32))
		return TCPS_ERR_MALFORMED_REQ;
	INT32 call_id_len = *(INT32*)ptrInParams;
	ptrInParams += sizeof(INT32);
	ptrInParamsLen -= sizeof(INT32);
	if(ptrInParamsLen < call_id_len+1)
		return TCPS_ERR_MALFORMED_REQ;
	const char* call_id = (const char*)ptrInParams;
	ptrInParams += call_id_len+1;
	ptrInParamsLen -= call_id_len+1;

	ASSERT(sm_callbackMap);
	CallbackMap_::const_iterator cit = sm_callbackMap->find(call_id, call_id_len);
	if(sm_callbackMap->end() == cit)
		return TCPS_ERR_TRY_CALL_OTHER_METHODS; // 本接口不支持，尝试其它接口

	CPtrStrA const streamedCallID(call_id+CONST_STR_LEN("PCC_Center::"), call_id_len-CONST_STR_LEN("PCC_Center::"));

	// posting回调
	if(cit->second.isPosting)
	{
		if(m_prepareDisconnect)
			return TCPS_ERR_EXITING;

		// 当缓存的未决调用小于1个时，直接调用
		if(m_postingPendingParam.maxPendings_ <= 1)
		{
			CNPAutoLock locker(m_callbackCallLock);
			TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
			if(m_owner)
			{
				void* replyData = NULL;
				INT_PTR replyLen = 0;
				err = m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
				if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
				{
					if(!m_owner->IsStreamedCallbackMatched_(streamedCallID.p, streamedCallID.len))
						return TCPS_ERR_CALLBACK_NOT_MATCH;

					{
						iscm_ClientCallType cct = (cit->second.isPosting ? iscm_cct_posting_callback : iscm_cct_callback);
						iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(m_callingOutTIDs, cct);
						err = m_owner->StreamedCallback_(streamedCallID.p, streamedCallID.len, ptrInParams, ptrInParamsLen, replyData, replyLen);
					}
					ASSERT(NULL==replyData && 0==replyLen);
					if(TCPS_OK == err)
					{
						ptrInParams += ptrInParamsLen;
						ptrInParamsLen = 0;
					}
					else if(TCPS_ERR_MALFORMED_REQ == err)
					{
						this->OnNetworkMalformed_();
						return TCPS_ERR_MALFORMED_REQ;
					}
				}
			}
			if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
				err = cit->second.handler(this, NULL, peerCallFlags, ptrInParams, ptrInParamsLen, NULL/*outfiter*/);
#ifdef _DEBUG
			if(TCPS_OK == err)
			{
				ASSERT(ptrInParams-(const BYTE*)inParamsData == inParamsDataLen);
				ASSERT(0 == ptrInParamsLen);
			}
#else
			(void)err;
#endif
			ASSERT(!peerCallFlags.requireReply);
			requireReplyData = false;
			ASSERT(!dataTransferred);
			return TCPS_OK;
		}

		// 投递一个task，异步执行
		if(m_asyncTaskStat.postingCallingBytes >= m_postingPendingParam.maxPendingBytes_
			|| m_asyncTaskStat.postingCallings >= m_postingPendingParam.maxPendings_
			)
		{
			// 对内置的SetRedirect_()回调，不做限制
			if("PCC_Center::SetRedirect_" != cit->first)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}

		// 投递一个异步回调任务，或加入待执行队列
		PostingTask_* task = tcps_NewEx(PostingTask_, (*this));
		task->peerCallFlags_ = peerCallFlags;
		task->baseInParamsData_ = (void*)inParamsData;
		task->call_id_ = streamedCallID;
		task->inParamsData_ = ptrInParams;
		task->inParamsDataLen_ = ptrInParamsLen;
		task->handler_ = cit->second.handler;
		VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
		{
			CNPAutoLock locker(m_postingCallbacks.lock);
			m_asyncTaskStat.postingCallingBytes += ptrInParamsLen;
			++(m_asyncTaskStat.postingCallings);
			if(m_postingCallbacks.calling)
			{
				task->m_nextPoolTask = NULL;
				if(m_postingCallbacks.tail)
				{
					m_postingCallbacks.tail->m_nextPoolTask = task;
					m_postingCallbacks.tail = task;
				}
				else
					m_postingCallbacks.head = m_postingCallbacks.tail = task;
			}
			else
			{
				ASSERT(NULL==m_postingCallbacks.head && NULL==m_postingCallbacks.tail);
				ASSERT(ptrInParamsLen==m_asyncTaskStat.postingCallingBytes && 1==m_asyncTaskStat.postingCallings);
				m_postingCallbacks.calling = true;
				FetchTaskPool()->Push(task);
			}
		}

		if(peerCallFlags.requireReply)
		{
			// 给outfiter填充内置返回参数
			struct PostOutParamWrapSite
			{
				iscm_RPCReplyPrefix replyPrefix;
				PostOutParamWrapSite() { replyPrefix.Init(); }
				static void FreeAction(void* p)
				{
					PostOutParamWrapSite* ptr = (PostOutParamWrapSite*)((BYTE*)p - offset_of(PostOutParamWrapSite, replyPrefix));
					ptr->~PostOutParamWrapSite();
					tcps_Free(ptr);
				}
			};
			PostOutParamWrapSite* opWrapper = tcps_New(PostOutParamWrapSite);
			Set_BaseType_(outfiter, opWrapper->replyPrefix, PostOutParamWrapSite::FreeAction);
		}
		else
		{
			// 指示不需要发送回应数据了
			requireReplyData = false;
		}

		dataTransferred = true; // 指示输入参数数据指针inParamsData被转移
		return TCPS_OK; // 立即返回成功
	}

	// 非posting方法/回调
	TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	{
		CNPAutoLock locker(m_callbackCallLock);
		if(m_owner)
		{
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			err = m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
			if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			{
				if("CallbackCheck_" == streamedCallID)
				{
					// CallbackCheck_()在流式调用端不提供，必须调用C++的映射版本
					err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
				}
				else
				{
					if(!m_owner->IsStreamedCallbackMatched_(streamedCallID.p, streamedCallID.len))
						return TCPS_ERR_CALLBACK_NOT_MATCH;

					{
						iscm_ClientCallType cct = (cit->second.isPosting ? iscm_cct_posting_callback : iscm_cct_callback);
						iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(m_callingOutTIDs, cct);
						err = m_owner->StreamedCallback_(streamedCallID.p, streamedCallID.len, ptrInParams, ptrInParamsLen, replyData, replyLen);
					}
					if(TCPS_OK == err)
					{
						ptrInParams += ptrInParamsLen;
						ptrInParamsLen = 0;
						iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
						replyPrefix->Init();
						outfiter->Push(replyPrefix, sizeof(iscm_RPCReplyPrefix), true, NULL);
						if(replyLen > 0)
						{
							ASSERT(replyData && outfiter);
							outfiter->Push(replyData, replyLen, true, NULL);
						}
						else
							ASSERT(NULL == replyData);
					}
					else
					{
						ASSERT(NULL==replyData && 0==replyLen);
						if(TCPS_ERR_MALFORMED_REQ == err)
						{
							this->OnNetworkMalformed_();
							return TCPS_ERR_MALFORMED_REQ;
						}
					}
				}
			}
		}
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
			err = cit->second.handler(this, NULL, peerCallFlags, ptrInParams, ptrInParamsLen, outfiter);
	}
#ifdef _DEBUG
	if(TCPS_OK == err)
	{
		ASSERT(ptrInParams-(const BYTE*)inParamsData == inParamsDataLen);
		ASSERT(0 == ptrInParamsLen);
	}
#endif
	return err;
}

struct PCC_Center_RC::StreamedCall_Task_ : public NPBaseTask
{
	PCC_Center_RC& face_;
	tcps_String methodName_;
	tcps_Binary data_;
	explicit StreamedCall_Task_(
				PCC_Center_RC& face,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/
				)
		: face_(face)
	{
		methodName_.Assign(methodName, nameLen);
		data_.Assign(data, dataLen);
	}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			SockWriteBuf buf;
			buf.data = data_.Get();
			buf.len = data_.Length();
			face_.StreamedCall_(
						methodName_.Get(), methodName_.Length(),
						&buf, 1,
						NULL, NULL
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_Center_RC::StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;
	if(NULL==methodName || 0==nameLen)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if(nameLen < 0)
		nameLen = strlen(methodName);

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	const PCC_Center::MethodMatchingFlag& methodMatchingFlag = GetMethodMatchingFlag();
	PCC_Center::MethodMatchingFlag::MethodMap::const_iterator itMethod = methodMatchingFlag.mmap_.find(methodName, nameLen);
	if(methodMatchingFlag.mmap_.end() == itMethod)
		return TCPS_ERR_METHOD_NOT_MATCH;
	ASSERT(itMethod->second.pMatchingVar);
	if(!*(itMethod->second.pMatchingVar))
		return TCPS_ERR_METHOD_NOT_MATCH;

	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			if(itMethod->second.isPosting)
			{
				StreamedCall_Task_* task = tcps_NewEx(StreamedCall_Task_, (
								*this,
								methodName, nameLen,
								data, dataLen
								));
				VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
				FetchTaskPool()->Push(task);
			}
			else
				NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = !(itMethod->second.isPosting);
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = (INT32)(12+nameLen);
	CSmartBuf<char, 256> call_id_buf(call_id_len+1);
	strncpy(call_id_buf.Get(), "PCC_Center::", 12);
	StrAssign(call_id_buf.Get()+12, methodName, nameLen);
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push(call_id_buf.Get(), call_id_len+1);

	// 填充IN参数到outfiter
	if(dataLen > 0)
		m_dataOutfiter.Push(data, dataLen);

	// 调用RPCCall()
	if(peerCallFlags.requireReply) // method
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_RPCReplyPrefix replyPrefix;
		err = m_rpcRequester->RecvD(&replyPrefix, sizeof(replyPrefix));
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}

		INT_PTR leftReplyLen = replyBytes - sizeof(replyPrefix);
		ASSERT(leftReplyLen >= 0);
		if(leftReplyLen > 0)
		{
			ASSERT(replyData && replyLen);
			tcps_Binary replied_data;
			if(!replied_data.Resize(leftReplyLen))
			{
				this->OnNetworkMalformed_();
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			err = m_rpcRequester->RecvD(replied_data.Get(), (int)leftReplyLen);
			if(TCPS_OK != err)
			{
				// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
				return err;
			}
			if(NULL==replyData || NULL==replyLen)
			{
				ASSERT(false);
				return TCPS_ERR_INVALID_PARAM;
			}
			INT32 bytes = 0;
			*replyData = replied_data.Drop(&bytes);
			*replyLen = bytes;
		}
	}
	else // posting method
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_UDPCallbackProxy.isUsing_)
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID;
			m_rpcRequester->GetPeerSessionKey(sessionID);
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

void PCC_Center_RC::UDPCallbackProxy_::OnUDPCall(
				IN tcps_Binary& frame
				)
{
	ASSERT(frame.Length() > 0);
	while(true)
	{
		BOOL requireReplyData = true;
		const void* inParamsData = frame.Get();
		BOOL dataTransferred = false;
		INT_PTR inParamsDataLen = frame.Length();
		TCPSError err = face_.OnRPCCallback_(requireReplyData, inParamsData, dataTransferred, inParamsDataLen, NULL/*outfiter*/);
		ASSERT(TCPS_OK!=err || !requireReplyData);
		if(TCPS_ERR_POSTING_PENDING_FULL == err)
		{
			ASSERT(!dataTransferred);
			Sleep(1);
			continue;
		}
		else
		{
			if(dataTransferred)
				frame.Drop();
			break;
		}
	}
}

TCPSError PCC_Center_RC::Wrap_AddModelCenter(
				IN PCC_Center_RC* thisObj /*= NULL*/,
				IN PCC_Center* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN IPP centerIPP
	IN IPP centerIPP_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, centerIPP_wrap);

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Center::AddModelCenter() posting_callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_posting_callback);
			errTcps = thisObj->AddModelCenter(
				centerIPP_wrap
				);
		}
		else
		{
			ASSERT(faceObj);
			errTcps = faceObj->AddModelCenter(
				centerIPP_wrap
				);
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_Center_RC::Wrap_DelModelCenter(
				IN PCC_Center_RC* thisObj /*= NULL*/,
				IN PCC_Center* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN IPP centerIPP
	IN IPP centerIPP_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, centerIPP_wrap);

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Center::DelModelCenter() posting_callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_posting_callback);
			errTcps = thisObj->DelModelCenter(
				centerIPP_wrap
				);
		}
		else
		{
			ASSERT(faceObj);
			errTcps = faceObj->DelModelCenter(
				centerIPP_wrap
				);
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_Center_RC::Wrap_GetStaticContext(
				IN PCC_Center_RC* thisObj /*= NULL*/,
				IN PCC_Center* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) cacheable_callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Center::GetStaticContext() cacheable_callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT PCC_NodeDesc staticContext;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_callback);
			errTcps = thisObj->GetStaticContext(
				opWrapper->staticContext
				);
		}
		else
		{
			ASSERT(faceObj);
			errTcps = faceObj->GetStaticContext(
				opWrapper->staticContext
				);
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT PCC_NodeDesc staticContext
	OUT const PCC_NodeDesc& staticContext_wrap = opWrapper->staticContext;
		Set_String_(outfiter, staticContext_wrap.name);
		Set_BaseType_(outfiter, staticContext_wrap.cpuType);
		Set_BaseType_(outfiter, staticContext_wrap.cpuFreq);
		Set_BaseType_(outfiter, staticContext_wrap.cpuProcessors);
		Set_BaseType_(outfiter, staticContext_wrap.cpuThreads);
		Set_BaseType_(outfiter, staticContext_wrap.totalMemoryBytes);
		Set_BaseType_(outfiter, staticContext_wrap.networkBandwidth);
		Set_BaseType_(outfiter, staticContext_wrap.osType);
		Set_String_(outfiter, staticContext_wrap.osDetail);
		Set_BaseType_(outfiter, staticContext_wrap.executeBits);

	return TCPS_OK;
}

TCPSError PCC_Center_RC::Wrap_GetDynamicContext(
				IN PCC_Center_RC* thisObj /*= NULL*/,
				IN PCC_Center* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Center::GetDynamicContext() callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT PCC_DynamicContext dynamicContext;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_callback);
			errTcps = thisObj->GetDynamicContext(
				opWrapper->dynamicContext
				);
		}
		else
		{
			ASSERT(faceObj);
			errTcps = faceObj->GetDynamicContext(
				opWrapper->dynamicContext
				);
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT PCC_DynamicContext dynamicContext
	OUT const PCC_DynamicContext& dynamicContext_wrap = opWrapper->dynamicContext;
	Set_BaseType_(outfiter, dynamicContext_wrap);

	return TCPS_OK;
}

TCPSError PCC_Center_RC::Wrap_AddModel(
				IN PCC_Center_RC* thisObj /*= NULL*/,
				IN PCC_Center* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN PCC_ModelProperty moduleProperty
	IN PCC_ModelProperty moduleProperty_wrap;
			GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.modelTag.name);
			GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.modelTag.version);
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.description);
		GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, moduleProperty_wrap.addTime);

	// IN tcps_Array<PCC_ModelFile> modelFiles
	IN tcps_Array<PCC_ModelFile> modelFiles_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	modelFiles_wrap.Resize(array_len);
	for(int idx1=0; idx1<modelFiles_wrap.Length(); ++idx1)
	{
		PCC_ModelFile& ref1 = modelFiles_wrap[idx1];
			GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1.name);
	}

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Center::AddModel() callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_callback);
			errTcps = thisObj->AddModel(
				moduleProperty_wrap,
				modelFiles_wrap
				);
		}
		else
		{
			ASSERT(faceObj);
			errTcps = faceObj->AddModel(
				moduleProperty_wrap,
				modelFiles_wrap
				);
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_Center_RC::Wrap_DelModel(
				IN PCC_Center_RC* thisObj /*= NULL*/,
				IN PCC_Center* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT64 modelKey
	IN INT64 modelKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, modelKey_wrap);

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Center::DelModel() callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_callback);
			errTcps = thisObj->DelModel(
				modelKey_wrap
				);
		}
		else
		{
			ASSERT(faceObj);
			errTcps = faceObj->DelModel(
				modelKey_wrap
				);
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_Center_RC::UDPLink_(
				OUT INT32& servePort_wrap,
				OUT INT32& linkKey_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_UDPLink_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 20;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::UDPLink_", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT INT32 servePort
		PICK_BASETYPE_Q(iscm_replied_picker, servePort_wrap);

		// OUT INT32 linkKey
		PICK_BASETYPE_Q(iscm_replied_picker, linkKey_wrap);
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Center::UDPLink_() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_RC::UDPLinkConfirm_(
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_UDPLinkConfirm_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 27;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::UDPLinkConfirm_", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Center::UDPLinkConfirm_() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_RC::Wrap_SetRedirect_(
				IN PCC_Center_RC* thisObj /*= NULL*/,
				IN PCC_Center* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN IPP redirectIPP
	IN IPP redirectIPP_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, redirectIPP_wrap);

	// IN tcps_Binary redirectParam
	IN tcps_Binary redirectParam_wrap;
	GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, redirectParam_wrap);

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Center::SetRedirect_() posting_callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_posting_callback);
			errTcps = thisObj->SetRedirect_(
				redirectIPP_wrap,
				redirectParam_wrap
				);
		}
		else
		{
			(void)faceObj;
			ASSERT(false);
			errTcps = TCPS_ERR_INTERNAL_BUG;
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

struct PCC_Center_RC::SetTimeout__Task_ : public NPBaseTask
{
	PCC_Center_RC& face_;
	IN INT32 recvTimeout_wrap_;
	IN INT32 sendTimeout_wrap_;
	explicit SetTimeout__Task_(
				PCC_Center_RC& face,
				IN INT32 recvTimeout_wrap,
				IN INT32 sendTimeout_wrap
				)
		: face_(face)
		, recvTimeout_wrap_(recvTimeout_wrap)
		, sendTimeout_wrap_(sendTimeout_wrap)
		{}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			face_.SetTimeout_(
						recvTimeout_wrap_,
						sendTimeout_wrap_
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_Center_RC::SetTimeout_(
				IN INT32 recvTimeout_wrap,
				IN INT32 sendTimeout_wrap
				) posting_method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			SetTimeout__Task_* task = tcps_NewEx(SetTimeout__Task_, (
							*this,
							recvTimeout_wrap,
							sendTimeout_wrap
							));
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
			FetchTaskPool()->Push(task);
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_SetTimeout_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 23;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::SetTimeout_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT32 recvTimeout
	Put_BaseType_(&m_dataOutfiter, recvTimeout_wrap);

	// IN INT32 sendTimeout
	Put_BaseType_(&m_dataOutfiter, sendTimeout_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_UDPCallbackProxy.isUsing_)
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID;
			m_rpcRequester->GetPeerSessionKey(sessionID);
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

struct PCC_Center_RC::SetSessionBufferSize__Task_ : public NPBaseTask
{
	PCC_Center_RC& face_;
	IN INT32 recvBufBytes_wrap_;
	IN INT32 sendBufBytes_wrap_;
	explicit SetSessionBufferSize__Task_(
				PCC_Center_RC& face,
				IN INT32 recvBufBytes_wrap,
				IN INT32 sendBufBytes_wrap
				)
		: face_(face)
		, recvBufBytes_wrap_(recvBufBytes_wrap)
		, sendBufBytes_wrap_(sendBufBytes_wrap)
		{}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			face_.SetSessionBufferSize_(
						recvBufBytes_wrap_,
						sendBufBytes_wrap_
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_Center_RC::SetSessionBufferSize_(
				IN INT32 recvBufBytes_wrap,
				IN INT32 sendBufBytes_wrap
				) posting_method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			SetSessionBufferSize__Task_* task = tcps_NewEx(SetSessionBufferSize__Task_, (
							*this,
							recvBufBytes_wrap,
							sendBufBytes_wrap
							));
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
			FetchTaskPool()->Push(task);
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_SetSessionBufferSize_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 33;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::SetSessionBufferSize_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT32 recvBufBytes
	Put_BaseType_(&m_dataOutfiter, recvBufBytes_wrap);

	// IN INT32 sendBufBytes
	Put_BaseType_(&m_dataOutfiter, sendBufBytes_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_UDPCallbackProxy.isUsing_)
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID;
			m_rpcRequester->GetPeerSessionKey(sessionID);
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Center_RC::MethodCheck_(
				IN const tcps_Array<tcps_String>& methods_wrap,
				IN const tcps_Array<tcps_String>& methodTypeInfos_wrap,
				OUT tcps_Array<BOOL>& matchingFlags_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 24;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Center::MethodCheck_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_Array<tcps_String> methods
	Put_BaseType_(&m_dataOutfiter, methods_wrap.LenRef());
	for(int idx1=0; idx1<methods_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = methods_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// IN tcps_Array<tcps_String> methodTypeInfos
	Put_BaseType_(&m_dataOutfiter, methodTypeInfos_wrap.LenRef());
	for(int idx1=0; idx1<methodTypeInfos_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = methodTypeInfos_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_IRequester* iscm_replied_picker = m_rpcRequester;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<BOOL> matchingFlags
		PICK_PODARRAY_(iscm_replied_picker, matchingFlags_wrap);
	}
	return TCPS_OK;
}

TCPSError PCC_Center_RC::Wrap_CallbackCheck_(
				IN PCC_Center_RC* thisObj /*= NULL*/,
				IN PCC_Center* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_Array<tcps_String> callbacks
	IN tcps_Array<tcps_String> callbacks_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	callbacks_wrap.Resize(array_len);
	for(int idx1=0; idx1<callbacks_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = callbacks_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	// IN tcps_Array<tcps_String> callbackTypeInfos
	IN tcps_Array<tcps_String> callbackTypeInfos_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	callbackTypeInfos_wrap.Resize(array_len);
	for(int idx1=0; idx1<callbackTypeInfos_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = callbackTypeInfos_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Center::CallbackCheck_() callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<BOOL> matchingFlags;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_callback);
			errTcps = thisObj->CallbackCheck_(
				callbacks_wrap,
				callbackTypeInfos_wrap,
				opWrapper->matchingFlags
				);
		}
		else
		{
			(void)faceObj;
			ASSERT(false);
			errTcps = TCPS_ERR_INTERNAL_BUG;
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<BOOL> matchingFlags
	OUT const tcps_Array<BOOL>& matchingFlags_wrap = opWrapper->matchingFlags;
	Set_PODArray_(outfiter, matchingFlags_wrap);

	return TCPS_OK;
}

PCC_Center::PCC_Center(BOOL initNetworkSingletons /*= true*/)
	: m_faceR(NULL), m_faceL(NULL), m_callSiteL(NULL)
	, m_closingTID(INVALID_OSTHREADID)
	, m_connectTimeout(INFINITE), m_recvTimeout(INFINITE), m_sendTimeout(INFINITE)
	, m_streamedCallbackMap_IsInited(false)
{
	m_base_v_tab_ptr = m_derived_v_tab_ptr = *(LPVOID*)this;
	if(initNetworkSingletons)
		iscm_InitClientSingletons(true, true);
	else
		iscm_InitClientSingletons(false, false);
	PCC_Center_RC::GetCallbackMap_();
}

PCC_Center::~PCC_Center()
{
	BOOL isNotDerived = (m_base_v_tab_ptr == m_derived_v_tab_ptr);
	NPR_ASSERT_EX(isNotDerived || (NULL==m_faceR && NULL==m_faceL), "请在最终派生类的析构函数的最后调用一次DestroyRequester()");
	DestroyRequester();
	if(m_callSiteL)
		tcps_Delete(m_callSiteL);
}

void PCC_Center::DestroyRequester_(
				IN BOOL byLocalPeer
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);

	CAutoObj<AutoFlag<OSThreadID> > autoClosingTID;
	if(!byLocalPeer)
		ConstructAutoObj(AutoFlag<OSThreadID>, autoClosingTID, (m_closingTID, OSThreadSelf()));

	if(m_faceR)
	{
		tcps_Delete(m_faceR);
		m_faceR = NULL;
	}
	else if(m_faceL)
	{
		if(INVALID_OSTHREADID==m_closingTID || OSThreadSelf()!=m_closingTID)
			this->OnPeerBroken();
		this->OnClose();
		m_faceL->DeleteThis();
		m_faceL = NULL;
		if(m_callSiteL)
			m_callSiteL->Reset();
		m_localServeIPP = INVALID_IPP;
	}
}

void PCC_Center::DestroyRequester()
{
	DestroyRequester_(false);
}

TCPSError PCC_Center::SetServeIPP_(
				IN BOOL byLocalPeer,
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	CNPAutoLock locker(m_lock);
	m_derived_v_tab_ptr = *(LPVOID*)this;
	ASSERT(NULL==m_faceR || NULL==m_faceL);

	if(m_localMakingFlag.making)
	{
		if(serveIPP.IsValid())
		{
			ASSERT(false);
			return TCPS_ERR_EXTERNAL_BUG;
		}
		m_localMakingFlag.failed = true;
		return TCPS_OK;
	}

	if(m_faceL && m_localServeIPP==serveIPP)
		return TCPS_OK;

	if(serveIPP.IsValid() && iscm_IsRegisteredServe(serveIPP))
	{
		DestroyRequester_(byLocalPeer);

		ASSERT(!m_localMakingFlag.making && !m_localMakingFlag.failed);
		AutoFlag<BOOL> autoFlag(m_localMakingFlag.making, true);
		FinalAssign<BOOL> finalAssign(m_localMakingFlag.failed, false);

		union
		{
		PCC_CenterSessionMaker* sessionMaker;
		void* dummyUnionPtr;
		};
		sessionMaker = NULL;
		FNMakeLocalSession_PCC_Center fnMake =
					(FNMakeLocalSession_PCC_Center)iscm_GetRegisteredFunction(
						serveIPP,
						"MakeLocalSession_PCC_Center",
						&dummyUnionPtr
						);
		if(NULL == fnMake)
			return TCPS_ERR_INVALID_INTERFACE;

		ASSERT(sessionMaker);
		TCPSError err = fnMake(clientID_IPP, *sessionMaker, m_faceL, this);
		if(TCPS_OK==err && m_localMakingFlag.failed)
		{
			ASSERT(m_faceL);
			m_faceL->DeleteThis();
			m_faceL = NULL;
			err = TCPS_ERR_CONNECT_FAILED;
		}
		if(TCPS_OK != err)
		{
			ASSERT(NULL == m_faceL);
			return err;
		}
		if(m_callSiteL)
			m_callSiteL->needUpdateFlags = true;

		ASSERT(m_faceL);
		err = this->OnConnected();
		if(TCPS_OK==err && m_localMakingFlag.failed)
			err = TCPS_ERR_CONNECT_FAILED;
		if(TCPS_OK != err)
		{
			if(INVALID_OSTHREADID==m_closingTID || OSThreadSelf()!=m_closingTID)
				this->OnPeerBroken();
			this->OnClose();
			m_faceL->DeleteThis();
			m_faceL = NULL;
			return err;
		}
		m_localServeIPP = serveIPP;
		return TCPS_OK;
	}

	if(m_faceL)
		DestroyRequester_(byLocalPeer);
	if(NULL == m_faceR)
	{
		if(!serveIPP.IsValid())
			return TCPS_OK;
		m_faceR = tcps_NewEx(PCC_Center_RC, (this));
	}

	if(INFINITE!=m_connectTimeout || INFINITE!=m_recvTimeout || INFINITE!=m_sendTimeout)
		m_faceR->SetTimeout(m_connectTimeout, m_recvTimeout, m_sendTimeout);
	if(!m_sockRecvSendBufParam.IsDefault())
		m_faceR->SetSessionBufferSize(m_sockRecvSendBufParam.recvBufBytes_, m_sockRecvSendBufParam.sendBufBytes_);
	if(!m_postingPendingParam.IsDefault())
		m_faceR->SetPostingPendingParameters(m_postingPendingParam.maxPendingBytes_, m_postingPendingParam.maxPendings_);
	return m_faceR->SetServeIPP(
						serveIPP,
						sessionFlags,
						clientID_IPP,
						secondaryServeIPP,
						tertiaryServeIPP,
						reconnectIntervalMSELs
						);
}

TCPSError PCC_Center::SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	CNPAutoLock locker(m_lock);
	AutoFlag<OSThreadID> autoClosingTID(m_closingTID, OSThreadSelf());
	return SetServeIPP_(false, serveIPP, sessionFlags, clientID_IPP, secondaryServeIPP, tertiaryServeIPP, reconnectIntervalMSELs);
}

IPP PCC_Center::GetServeIPP() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->GetServeIPP();
	else if(m_faceL)
		return m_localServeIPP;
	return INVALID_IPP;
}

IPP PCC_Center::GetServingIPP() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->GetServingIPP();
	else if(m_faceL)
		return m_localServeIPP;
	return INVALID_IPP;
}

BOOL PCC_Center::IsConnected() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->IsConnected();
	else if(m_faceL)
		return true;
	return false;
}

void PCC_Center::SetKeeping(
				IN BOOL keeping
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetKeeping(keeping);
}

BOOL PCC_Center::IsKeeping() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->IsKeeping();
	return false;
}

BOOL PCC_Center::IsLocalPeer() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	return (NULL != m_faceL);
}

void PCC_Center::PrepareDisconnect()
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->PrepareDisconnect();
}

void PCC_Center::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	m_connectTimeout = connectTimeout;
	m_recvTimeout = recvTimeout;
	m_sendTimeout = sendTimeout;
}

void PCC_Center::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		m_faceR->GetTimeout(connectTimeout, recvTimeout, sendTimeout);
		return;
	}
	if(connectTimeout)
		*connectTimeout = m_connectTimeout;
	if(recvTimeout)
		*recvTimeout = m_recvTimeout;
	if(sendTimeout)
		*sendTimeout = m_sendTimeout;
}

void PCC_Center::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	m_sockRecvSendBufParam.Set(recvBufBytes, sendBufBytes);
}

void PCC_Center::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_sockRecvSendBufParam.Get(recvBufBytes, sendBufBytes);
}

void PCC_Center::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetPostingPendingParameters(maxPendingBytes, maxPendings);
	m_postingPendingParam.Set(maxPendingBytes, maxPendings);
}

void PCC_Center::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_postingPendingParam.Get(maxPendingBytes, maxPendings);
}

void PCC_Center::SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR && 0!=m_faceR->m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().SetBufferingParam(m_faceR->m_postingProxy.callerKey_, maxSendingBytes, maxSendings);
	m_postingSendParam.Set(maxSendingBytes, maxSendings);
}

void PCC_Center::GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_postingSendParam.Get(maxSendingBytes, maxSendings);
}

TCPSError PCC_Center::CleanPostingSendingQueue()
{
	if(NULL==m_faceR || 0==m_faceR->m_postingProxy.callerKey_)
		return TCPS_ERR_CALL_WAS_IGNORED;
	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(&m_faceR->m_postingProxy.callerKey_, 1);
}

TCPSError PCC_Center::CleanPostingSendingQueue(
				IN const PPCC_Center_* clients,
				IN INT_PTR clientsCount
				)
{
	tcps_SmartArray<PPCC_Center_, 256> clients_ar_;
	for(INT_PTR i=0; i<clientsCount; ++i)
	{
		if(NULL == clients[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(NULL==clients[i]->m_faceR || 0==clients[i]->m_faceR->m_postingProxy.callerKey_)
			continue;
		clients_ar_.push_back(clients[i]);
	}
	if(0 == clients_ar_.size())
		return TCPS_OK;

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> callerKey_ar_;
	callerKey_ar_.resize(clients_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)clients_ar_.size(); ++i)
		callerKey_ar_[i] = clients_ar_[i]->m_faceR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(callerKey_ar_.Get(), callerKey_ar_.size());
}

const PCC_Center::MethodMatchingFlag& PCC_Center::GetMethodMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->GetMethodMatchingFlag(err);
	}
	else if(m_faceL)
	{
		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		if(m_callSiteL->needUpdateFlags)
		{
			InitializeAllCallsTypeInfo_();
			m_callSiteL->needUpdateFlags = false;
		}
		if(err)
			*err = TCPS_OK;
		return m_callSiteL->matchingFlags;
	}

	static MethodMatchingFlag const defaultFlags;
	if(err)
		*err = TCPS_ERR_NEED_SERVE_IPP;
	return defaultFlags;
}

TCPSError PCC_Center::GetStreamedMethodTypeInfo_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo,
				OUT INT_PTR& infoLen
				) const
{
	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<0> > MethodMap_;
	static MethodMap_* s_mMap = NULL;
	if(NULL == s_mMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_mMap)
		{
			static MethodMap_ s_mMapObj;
			MethodMap_& mMap = s_mMapObj;
			s_mMap = &mMap;
		}
	}
	MethodMap_::iterator it = s_mMap->find(methodName, nameLen);
	if(it == s_mMap->end())
		return TCPS_ERR_METHOD_NOT_MATCH;
	infoLen = it->second.GetLength();
	typeInfo = (char*)tcps_Alloc(infoLen+1);
	StrAssign(typeInfo, it->second);
	return TCPS_OK;
}

TCPSError PCC_Center::StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	if(m_faceR)
	{
		return m_faceR->StreamedCall_(
					methodName, nameLen,
					data, dataLen,
					replyData, replyLen
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			return m_streamedCallSite.func(
						m_streamedCallSite.serverObj, m_streamedCallSite.sessionObj,
						"PCC_Center", methodName,
						data, dataLen,
						replyData, replyLen
						);
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnOnStreamedCall_L_;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("OnStreamedCall_L_", -1, NULL, 0);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Center_LocalMethod::FN_OnStreamedCall_L_)methodFuncL)(
					m_faceL,
					methodName, nameLen,
					data, dataLen,
					replyData, replyLen
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

BOOL PCC_Center::IsStreamedCallbackMatched_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/
				)
{
	if(m_streamedCallbackMap_IsInited)
	{
		StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
		if(it == m_streamedCallbackMap.end())
			return false;
		return it->second;
	}

	CNPAutoLock locker(m_lock);

	if(m_streamedCallbackMap_IsInited)
	{
		StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
		if(it == m_streamedCallbackMap.end())
			return false;
		return it->second;
	}

	ASSERT(0 == m_streamedCallbackMap.size());

	InitializeAllCallsTypeInfo_();
	BOOL matched;
	TCPSError err;
	char* typeInfo;
	INT_PTR infoLen;
	(void)matched; (void)err; (void)typeInfo; (void)infoLen;

	typeInfo = NULL;
	infoLen = 0;
	err = this->GetStreamedCallbackTypeInfo_("AddModelCenter", 14, typeInfo, infoLen);
	matched = (TCPS_OK==err && s_PCC_Center_AddModelCenter_TypeInfo_len_==infoLen && 0==strncmp(s_PCC_Center_AddModelCenter_TypeInfo_, typeInfo, infoLen));
	VERIFY(m_streamedCallbackMap.insert(std::make_pair(CPtrStrA("AddModelCenter", 14), matched)).second);
	if(typeInfo)
		tcps_Free(typeInfo);

	typeInfo = NULL;
	infoLen = 0;
	err = this->GetStreamedCallbackTypeInfo_("DelModelCenter", 14, typeInfo, infoLen);
	matched = (TCPS_OK==err && s_PCC_Center_DelModelCenter_TypeInfo_len_==infoLen && 0==strncmp(s_PCC_Center_DelModelCenter_TypeInfo_, typeInfo, infoLen));
	VERIFY(m_streamedCallbackMap.insert(std::make_pair(CPtrStrA("DelModelCenter", 14), matched)).second);
	if(typeInfo)
		tcps_Free(typeInfo);

	typeInfo = NULL;
	infoLen = 0;
	err = this->GetStreamedCallbackTypeInfo_("GetStaticContext", 16, typeInfo, infoLen);
	matched = (TCPS_OK==err && s_PCC_Center_GetStaticContext_TypeInfo_len_==infoLen && 0==strncmp(s_PCC_Center_GetStaticContext_TypeInfo_, typeInfo, infoLen));
	VERIFY(m_streamedCallbackMap.insert(std::make_pair(CPtrStrA("GetStaticContext", 16), matched)).second);
	if(typeInfo)
		tcps_Free(typeInfo);

	typeInfo = NULL;
	infoLen = 0;
	err = this->GetStreamedCallbackTypeInfo_("GetDynamicContext", 17, typeInfo, infoLen);
	matched = (TCPS_OK==err && s_PCC_Center_GetDynamicContext_TypeInfo_len_==infoLen && 0==strncmp(s_PCC_Center_GetDynamicContext_TypeInfo_, typeInfo, infoLen));
	VERIFY(m_streamedCallbackMap.insert(std::make_pair(CPtrStrA("GetDynamicContext", 17), matched)).second);
	if(typeInfo)
		tcps_Free(typeInfo);

	typeInfo = NULL;
	infoLen = 0;
	err = this->GetStreamedCallbackTypeInfo_("AddModel", 8, typeInfo, infoLen);
	matched = (TCPS_OK==err && s_PCC_Center_AddModel_TypeInfo_len_==infoLen && 0==strncmp(s_PCC_Center_AddModel_TypeInfo_, typeInfo, infoLen));
	VERIFY(m_streamedCallbackMap.insert(std::make_pair(CPtrStrA("AddModel", 8), matched)).second);
	if(typeInfo)
		tcps_Free(typeInfo);

	typeInfo = NULL;
	infoLen = 0;
	err = this->GetStreamedCallbackTypeInfo_("DelModel", 8, typeInfo, infoLen);
	matched = (TCPS_OK==err && s_PCC_Center_DelModel_TypeInfo_len_==infoLen && 0==strncmp(s_PCC_Center_DelModel_TypeInfo_, typeInfo, infoLen));
	VERIFY(m_streamedCallbackMap.insert(std::make_pair(CPtrStrA("DelModel", 8), matched)).second);
	if(typeInfo)
		tcps_Free(typeInfo);

	m_streamedCallbackMap_IsInited = true;
	StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
	if(it == m_streamedCallbackMap.end())
		return false;
	return it->second;
}

void PCC_Center::OnNetworkMalformed_()
{
	if(m_faceR)
		m_faceR->OnNetworkMalformed_();
}

void PCC_Center::CloseSession_()
{
	this->SetServeIPP_(true, INVALID_IPP);
}

PROC PCC_Center::FindCallback_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				)
{
	if(NULL == name)
	{
		ASSERT(false);
		return NULL;
	}

	// 对OnStreamedCallback_L_()特殊处理
	if(nameLen<0 && 0==strcmp("OnStreamedCallback_L_", name))
		return (PROC)&OnStreamedCallback_L_;

	InitializeAllCallsTypeInfo_();
	typedef TwoItems<CPtrStrA, PROC> FuncPair;
	typedef CQuickStringMap<CPtrStrA, FuncPair, QSS_Traits<6> > CallbackMap_;
	static CallbackMap_* s_cbMap = NULL;
	if(NULL == s_cbMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_cbMap)
		{
			static CallbackMap_ s_cbMapObj;
			CallbackMap_& cbMap = s_cbMapObj;
			cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModelCenter"), FuncPair(CPtrStrA(s_PCC_Center_AddModelCenter_TypeInfo_, s_PCC_Center_AddModelCenter_TypeInfo_len_), (PROC)&Local_AddModelCenter)));
			cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("DelModelCenter"), FuncPair(CPtrStrA(s_PCC_Center_DelModelCenter_TypeInfo_, s_PCC_Center_DelModelCenter_TypeInfo_len_), (PROC)&Local_DelModelCenter)));
			cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetStaticContext"), FuncPair(CPtrStrA(s_PCC_Center_GetStaticContext_TypeInfo_, s_PCC_Center_GetStaticContext_TypeInfo_len_), (PROC)&Local_GetStaticContext)));
			cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetDynamicContext"), FuncPair(CPtrStrA(s_PCC_Center_GetDynamicContext_TypeInfo_, s_PCC_Center_GetDynamicContext_TypeInfo_len_), (PROC)&Local_GetDynamicContext)));
			cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModel"), FuncPair(CPtrStrA(s_PCC_Center_AddModel_TypeInfo_, s_PCC_Center_AddModel_TypeInfo_len_), (PROC)&Local_AddModel)));
			cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("DelModel"), FuncPair(CPtrStrA(s_PCC_Center_DelModel_TypeInfo_, s_PCC_Center_DelModel_TypeInfo_len_), (PROC)&Local_DelModel)));
			s_cbMap = &cbMap;
		}
	}

	CallbackMap_::iterator it = s_cbMap->find(name, nameLen);
	if(s_cbMap->end() == it)
		return NULL;
	const CPtrStrA& ps = it->second.first;
	if(0 != ps.Compare(type, typeLen))
		return NULL;
	return it->second.second;
}

TCPSError PCC_Center::OnStreamedCallback_L_(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	PCC_Center* const pCC_CenterObj = (PCC_Center*)sessionObj;
	ASSERT(pCC_CenterObj->m_faceL);
	if(nameLen < 0)
		nameLen = strlen(callbackName);

	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_CenterObj->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_CenterObj->IsStreamedCallbackMatched_(callbackName, nameLen))
			return TCPS_ERR_CALLBACK_NOT_MATCH;
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_CenterObj->StreamedCallback_(callbackName, nameLen, data, dataLen, iscm_replyData, iscm_replyLen);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
		{
			if(replyData)
				*replyData = iscm_replyData;
			if(replyLen)
				*replyLen = iscm_replyLen;
			return err;
		}
	}

	INT_PTR call_id_len = 12+nameLen;
	CSmartBuf<char, 256> call_id_buf(call_id_len+1);
	char* const call_id = call_id_buf.Get();
	strncpy(call_id, "PCC_Center::", 12);
	StrAssign(call_id+12, callbackName, nameLen);

	PCC_Center_RC::InitCallbackMap_();
	ASSERT(PCC_Center_RC::sm_callbackMap);
	PCC_Center_RC::CallbackMap_::const_iterator cit = PCC_Center_RC::sm_callbackMap->find(call_id, call_id_len);
	if(PCC_Center_RC::sm_callbackMap->end() == cit)
		return TCPS_ERR_TRY_CALL_OTHER_METHODS; // 本接口不支持，尝试其它接口

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = !(cit->second.isPosting);
	peerCallFlags.dummy_15 = 0;
	const BYTE* ptrInParams = (const BYTE*)data;
	INT_PTR ptrInParamsLen = dataLen;
	if(peerCallFlags.requireReply)
	{
		iscm_RPCDataOutfiter outfiter;
		err = cit->second.handler(NULL, pCC_CenterObj, peerCallFlags, ptrInParams, ptrInParamsLen, &outfiter);
		if(TCPS_OK != err)
			return err;
		// outfiter.swbBufs_[0]总指向iscm_RPCDataOutfiter::reply_
		// outfiter.swbBufs_[1]为iscm_RPCReplyPrefix replyPrefix
		ASSERT(outfiter.swbBufs_.size()==1 || outfiter.swbBufs_.size()>=2);
		if(outfiter.swbBufs_.size() >= 2)
		{
			ASSERT(replyData && replyLen);
			*replyLen = SockTotalizeWriteBufVec(outfiter.swbBufs_.Get()+2, outfiter.swbBufs_.size()-2);
			*replyData = tcps_Alloc(*replyLen);
			BYTE* q = (BYTE*)*replyData;
			for(INT_PTR i=2; i<(INT_PTR)outfiter.swbBufs_.size(); ++i)
			{
				const SockWriteBuf& swb = outfiter.swbBufs_[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT(q-(BYTE*)*replyData == *replyLen);
		}
	}
	else
	{
		err = cit->second.handler(NULL, pCC_CenterObj, peerCallFlags, ptrInParams, ptrInParamsLen, NULL/*outfiter*/);
	}

	return err;
}

TCPSError PCC_Center::Local_AddModelCenter(
				IN void* sessionObj,
				IN const IPP& centerIPP_wrap
				) posting_callback
{
	PCC_Center* const pCC_CenterObj_wrap = (PCC_Center*)sessionObj;
	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_CenterObj_wrap->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_CenterObj_wrap->IsStreamedCallbackMatched_("AddModelCenter", 14))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter dataOutfiter;

		// IN IPP centerIPP
		Put_BaseType_(&dataOutfiter, centerIPP_wrap);

		ISCM_GAIN_TEMPORARY_CONTINUOUS_CALL_DATA(dataOutfiter.bufs_.Get(), dataOutfiter.bufs_.size(), iscm_data, iscm_dataLen);
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_CenterObj_wrap->StreamedCallback_(
						"AddModelCenter", 14,
						iscm_data, iscm_dataLen,
						iscm_replyData, iscm_replyLen
						);
		ASSERT(NULL==iscm_replyData && 0==iscm_replyLen);
		if(iscm_replyData)
			tcps_Free(iscm_replyData);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			return err;
		// 忽略返回TCPS_ERR_MALFORMED_REQ情况？？
	}

	return pCC_CenterObj_wrap->AddModelCenter(
					centerIPP_wrap
					);
}

TCPSError PCC_Center::Local_DelModelCenter(
				IN void* sessionObj,
				IN const IPP& centerIPP_wrap
				) posting_callback
{
	PCC_Center* const pCC_CenterObj_wrap = (PCC_Center*)sessionObj;
	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_CenterObj_wrap->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_CenterObj_wrap->IsStreamedCallbackMatched_("DelModelCenter", 14))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter dataOutfiter;

		// IN IPP centerIPP
		Put_BaseType_(&dataOutfiter, centerIPP_wrap);

		ISCM_GAIN_TEMPORARY_CONTINUOUS_CALL_DATA(dataOutfiter.bufs_.Get(), dataOutfiter.bufs_.size(), iscm_data, iscm_dataLen);
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_CenterObj_wrap->StreamedCallback_(
						"DelModelCenter", 14,
						iscm_data, iscm_dataLen,
						iscm_replyData, iscm_replyLen
						);
		ASSERT(NULL==iscm_replyData && 0==iscm_replyLen);
		if(iscm_replyData)
			tcps_Free(iscm_replyData);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			return err;
		// 忽略返回TCPS_ERR_MALFORMED_REQ情况？？
	}

	return pCC_CenterObj_wrap->DelModelCenter(
					centerIPP_wrap
					);
}

TCPSError PCC_Center::Local_GetStaticContext(
				IN void* sessionObj,
				OUT PCC_NodeDesc& staticContext_wrap
				) cacheable_callback
{
	PCC_Center* const pCC_CenterObj_wrap = (PCC_Center*)sessionObj;
	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_CenterObj_wrap->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_CenterObj_wrap->IsStreamedCallbackMatched_("GetStaticContext", 16))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		const BYTE* iscm_data = NULL;
		INT_PTR iscm_dataLen = 0;
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_CenterObj_wrap->StreamedCallback_(
						"GetStaticContext", 16,
						iscm_data, iscm_dataLen,
						iscm_replyData, iscm_replyLen
						);
		if(TCPS_OK == err)
		{
			ASSERT(iscm_replyData && iscm_replyLen>0);
			const BYTE* iscm_replied_picker = (const BYTE*)iscm_replyData;
			const BYTE* const iscm_replied_end = iscm_replied_picker + iscm_replyLen;
			(void)iscm_replied_end;
			iscm_RPCReplyPrefix replyPrefix;
			replyPrefix.Init();
			INT32 array_len;
			(void)array_len;

			// OUT PCC_NodeDesc staticContext
				PICK_STRING_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.name);
				PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.cpuType);
				PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.cpuFreq);
				PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.cpuProcessors);
				PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.cpuThreads);
				PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.totalMemoryBytes);
				PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.networkBandwidth);
				PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.osType);
				PICK_STRING_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.osDetail);
				PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, staticContext_wrap.executeBits);
			ASSERT(iscm_replied_picker == iscm_replied_end);
		}
		if(iscm_replyData)
			tcps_Free(iscm_replyData);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			return err;
		// 忽略返回TCPS_ERR_MALFORMED_REQ情况？？
	}

	return pCC_CenterObj_wrap->GetStaticContext(
					staticContext_wrap
					);
}

TCPSError PCC_Center::Local_GetDynamicContext(
				IN void* sessionObj,
				OUT PCC_DynamicContext& dynamicContext_wrap
				) callback
{
	PCC_Center* const pCC_CenterObj_wrap = (PCC_Center*)sessionObj;
	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_CenterObj_wrap->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_CenterObj_wrap->IsStreamedCallbackMatched_("GetDynamicContext", 17))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		const BYTE* iscm_data = NULL;
		INT_PTR iscm_dataLen = 0;
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_CenterObj_wrap->StreamedCallback_(
						"GetDynamicContext", 17,
						iscm_data, iscm_dataLen,
						iscm_replyData, iscm_replyLen
						);
		if(TCPS_OK == err)
		{
			ASSERT(iscm_replyData && iscm_replyLen>0);
			const BYTE* iscm_replied_picker = (const BYTE*)iscm_replyData;
			const BYTE* const iscm_replied_end = iscm_replied_picker + iscm_replyLen;
			(void)iscm_replied_end;
			iscm_RPCReplyPrefix replyPrefix;
			replyPrefix.Init();
			INT32 array_len;
			(void)array_len;

			// OUT PCC_DynamicContext dynamicContext
			PICK_BASETYPE_Q_EX(pCC_CenterObj_wrap, iscm_replied_picker, dynamicContext_wrap);
			ASSERT(iscm_replied_picker == iscm_replied_end);
		}
		if(iscm_replyData)
			tcps_Free(iscm_replyData);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			return err;
		// 忽略返回TCPS_ERR_MALFORMED_REQ情况？？
	}

	return pCC_CenterObj_wrap->GetDynamicContext(
					dynamicContext_wrap
					);
}

TCPSError PCC_Center::Local_AddModel(
				IN void* sessionObj,
				IN const PCC_ModelProperty& moduleProperty_wrap,
				IN const tcps_Array<PCC_ModelFile>& modelFiles_wrap
				) callback
{
	PCC_Center* const pCC_CenterObj_wrap = (PCC_Center*)sessionObj;
	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_CenterObj_wrap->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_CenterObj_wrap->IsStreamedCallbackMatched_("AddModel", 8))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter dataOutfiter;

		// IN PCC_ModelProperty moduleProperty
				Put_String_(&dataOutfiter, moduleProperty_wrap.modelTag.name.Get(), moduleProperty_wrap.modelTag.name.LenRef());
				Put_BaseType_(&dataOutfiter, moduleProperty_wrap.modelTag.version);
			Put_String_(&dataOutfiter, moduleProperty_wrap.description.Get(), moduleProperty_wrap.description.LenRef());
			Put_BaseType_(&dataOutfiter, moduleProperty_wrap.addTime);

		// IN tcps_Array<PCC_ModelFile> modelFiles
		Put_BaseType_(&dataOutfiter, modelFiles_wrap.LenRef());
		for(int idx2=0; idx2<modelFiles_wrap.Length(); ++idx2)
		{
			const PCC_ModelFile& ref2 = modelFiles_wrap[idx2];
				Put_String_(&dataOutfiter, ref2.name.Get(), ref2.name.LenRef());
		}

		ISCM_GAIN_TEMPORARY_CONTINUOUS_CALL_DATA(dataOutfiter.bufs_.Get(), dataOutfiter.bufs_.size(), iscm_data, iscm_dataLen);
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_CenterObj_wrap->StreamedCallback_(
						"AddModel", 8,
						iscm_data, iscm_dataLen,
						iscm_replyData, iscm_replyLen
						);
		ASSERT(NULL==iscm_replyData && 0==iscm_replyLen);
		if(iscm_replyData)
			tcps_Free(iscm_replyData);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			return err;
		// 忽略返回TCPS_ERR_MALFORMED_REQ情况？？
	}

	return pCC_CenterObj_wrap->AddModel(
					moduleProperty_wrap,
					modelFiles_wrap
					);
}

TCPSError PCC_Center::Local_DelModel(
				IN void* sessionObj,
				IN INT64 modelKey_wrap
				) callback
{
	PCC_Center* const pCC_CenterObj_wrap = (PCC_Center*)sessionObj;
	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_CenterObj_wrap->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_CenterObj_wrap->IsStreamedCallbackMatched_("DelModel", 8))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter dataOutfiter;

		// IN INT64 modelKey
		Put_BaseType_(&dataOutfiter, modelKey_wrap);

		ISCM_GAIN_TEMPORARY_CONTINUOUS_CALL_DATA(dataOutfiter.bufs_.Get(), dataOutfiter.bufs_.size(), iscm_data, iscm_dataLen);
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_CenterObj_wrap->StreamedCallback_(
						"DelModel", 8,
						iscm_data, iscm_dataLen,
						iscm_replyData, iscm_replyLen
						);
		ASSERT(NULL==iscm_replyData && 0==iscm_replyLen);
		if(iscm_replyData)
			tcps_Free(iscm_replyData);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			return err;
		// 忽略返回TCPS_ERR_MALFORMED_REQ情况？？
	}

	return pCC_CenterObj_wrap->DelModel(
					modelKey_wrap
					);
}

class PCC_Deploy_RC : public PCC_Deploy_T
{
	friend class PCC_Deploy;
	friend class PCC_Deploy_S;
private:
	PCC_Deploy_RC(const PCC_Deploy_RC&);
	PCC_Deploy_RC& operator= (const PCC_Deploy_RC&);

public:
	explicit PCC_Deploy_RC(PCC_Deploy* owner = NULL);
	virtual ~PCC_Deploy_RC();

protected:
	void DestroyRequester();

	virtual TCPSError OnConnected()
	{
		if(m_owner)
			return m_owner->OnConnected();
		return TCPS_OK;
	}

	virtual void OnPeerBroken()
	{
		if(m_owner)
			m_owner->OnPeerBroken();
	}
	virtual void OnClose()
	{
		if(m_owner)
			m_owner->OnClose();
	}

	virtual void OnConnectTimeout(IN TCPSError cause)
	{
		if(m_owner)
			m_owner->OnConnectTimeout(cause);
	}

public:
	TCPSError SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	IPP GetServeIPP() const;
	IPP GetServingIPP() const;
	BOOL IsConnected() const;

	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	void PrepareDisconnect();

	void SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	void GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const;

	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

public:
	const PCC_Deploy::MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

public:
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

public:
	TCPSError Login(
				IN const char* ticket, IN INT32 ticket_len /*= -1*/
				) method;

public:
	TCPSError Logout(
				) method;

public:
	TCPSError CreateTrunk(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/
				) method;

public:
	TCPSError RemoveTrunk(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/
				) method;

public:
	TCPSError ListTrunk(
				OUT tcps_Array<tcps_String>& trunks
				) method;

public:
	TCPSError AddAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN const PCC_Tag& authTag,
				IN const tcps_Array<PCC_ModuleFile>& files
				) method;

public:
	TCPSError RemoveAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN const PCC_Tag& authTag
				) method;

public:
	TCPSError ListAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				OUT tcps_Array<PCC_Tag>& authTags
				) method;

public:
	TCPSError FindAuthCenter(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN const PCC_Tag& authTag
				) method;

public:
	TCPSError AddModule(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN const PCC_ModuleProperty& moduleProperty,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles,
				OUT INT64& moduleKey
				) method;

public:
	TCPSError AddModuleFile(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 moduleKey,
				IN PCC_ModuleFileType fileType,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles
				) method;

public:
	TCPSError RemoveModule(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 moduleKey
				) method;

public:
	TCPSError RemoveModuleFiles(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				IN INT64 moduleKey,
				IN INT32 fileType
				) method;

public:
	TCPSError ListModules(
				IN const char* trunk, IN INT32 trunk_len /*= -1*/,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo
				) method;

public:
	TCPSError AddModel(
				IN const PCC_ModelProperty& moduleProperty,
				IN const tcps_Array<PCC_ModelFile>& modelFiles
				) method;

public:
	TCPSError DelModel(
				IN INT64 modelKey
				) method;

protected:
	// 返回TCPS_OK允许重定向；返回非TCPS_OK禁止重定向
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		if(m_owner)
		{
			return m_owner->OnPrepareRedirect_(
					redirectIPP,
					redirectParam
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 //////
private:
	PCC_Deploy* const m_owner;
	iscm_ClientThreadIDs m_callingOutTIDs;
	DWORD m_sessionFlags;
	DWORD m_reconnectIntervalMSELs;
	DataOutfiter m_dataOutfiter;
	iscm_IRequester* m_rpcRequester;
	BOOL m_needBrokenNotify;
	BOOL m_prepareDisconnect;

	struct TAsyncTaskStat_
	{
		INT_PTR postingCallingBytes;// 正在等待执行的posting callback的总调用数据大小
		INT32 postingCallings;		// 正在等待执行的posting callback的调用数量
		long totalAsyncTasks;		// 总的正在执行的异步任务数量，等于postingCallings + 其它异步任务数
		TAsyncTaskStat_() : postingCallingBytes(0), postingCallings(0), totalAsyncTasks(0) {}
	};
	TAsyncTaskStat_ m_asyncTaskStat;

private:
	struct ReconnectTask_ : public NPBaseTask
	{
		PCC_Deploy_RC& face_;
		explicit ReconnectTask_(PCC_Deploy_RC& face) : face_(face) {}
		virtual ~ReconnectTask_() {}
		virtual void OnPoolTask()
		{
			// ReconnectTask_重连动作不同于OnConnectedFailedTask_，不做多服务IPP智能切换
			if(!face_.m_prepareDisconnect && face_.IsConnected())
				face_.m_rpcRequester->Reconnect();
			else
				ASSERT(true);
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
			tcps_Delete(this);
		}
	};
	friend struct ReconnectTask_;

private:
	void OnNetworkMalformed_()
	{
		if(m_prepareDisconnect || !m_rpcRequester->IsConnected())
			return;
		ReconnectTask_* task = tcps_NewEx(ReconnectTask_, (*this));
		VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
		FetchTaskPool()->Push(task);
	}

private:
	iscm_MatchingUpdateFlag m_methodMatchingUpdatedFlag;
	PCC_Deploy::MethodMatchingFlag m_methodMatchingFlag;
	TCPSError UpdateMethodMatchingFlag_();

private:
	iscm_PostingPendingParam m_postingPendingParam;

private:
	static TCPSError Wrap_SetRedirect_(PCC_Deploy_RC*, PCC_Deploy*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_callback;
	static TCPSError Wrap_CallbackCheck_(PCC_Deploy_RC*, PCC_Deploy*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) callback;

private:
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		IPP ipp = m_rpcRequester->GetServingIPP();
		if(redirectIPP != ipp)
		{
			TCPSError err = this->OnPrepareRedirect_(redirectIPP, redirectParam);
			if(TCPS_OK != err)
				return err;

			struct SwitchTask : public NPBaseTask
			{
				long* totalAsyncTasks_;
				iscm_IRequester* requester_;
				IPP newIPP_;
				virtual void OnPoolTask()
				{
					requester_->TempSwitchTo(newIPP_);
					VERIFY(InterlockedDecrement(totalAsyncTasks_) >= 0);
					this->~SwitchTask();
					tcps_Free(this);
				}
			};
			SwitchTask* task = ::new(tcps_Alloc(sizeof(SwitchTask))) SwitchTask();
			task->totalAsyncTasks_ = &m_asyncTaskStat.totalAsyncTasks;
			task->requester_ = m_rpcRequester;
			task->newIPP_ = redirectIPP;
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
			FetchTaskPool()->Push(task);
		}
		return TCPS_OK;
	}

private:
	TCPSError SetTimeout_(
				IN INT32 recvTimeout,
				IN INT32 sendTimeout
				) posting_method;

private:
	TCPSError SetSessionBufferSize_(
				IN INT32 recvBufBytes,
				IN INT32 sendBufBytes
				) posting_method;

private:
	TCPSError MethodCheck_(
				IN const tcps_Array<tcps_String>& methods,
				IN const tcps_Array<tcps_String>& methodTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) method;

private:
	TCPSError CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback;

private:
	void OnPrepareRPCCallback_(
				IN const void* inParamsData,
				IN INT_PTR inParamsDataLen,
				OUT BOOL& notifyByTaskPool /*= true*/
				);
	TCPSError OnRPCCallback_(
				OUT BOOL& requireReplyData /*= true*/,
				IN const void* inParamsData,
				OUT BOOL& dataTransferred /*= false*/,
				IN INT_PTR inParamsDataLen,
				OUT iscm_IRPCOutfiter* outfiter
				);
	struct CallbackProxy_ : public iscm_ICallbackServeMan::IRPCClient
	{
		PCC_Deploy_RC& face_;
		INT32 sessionKey_;
		long callbackRefCount_;

		explicit CallbackProxy_(PCC_Deploy_RC& face)
			: face_(face), sessionKey_(0), callbackRefCount_(0)
			{}
		virtual INT32& GetSessionKey()
			{	return sessionKey_;	}
		virtual void IncreaseCallbackRef()
			{	ASSERT(callbackRefCount_ >= 0); InterlockedIncrement(&callbackRefCount_);	}
		virtual void DecreaseCallbackRef()
			{	ASSERT(callbackRefCount_ >= 1); InterlockedDecrement(&callbackRefCount_);	}
		virtual void OnCallbackInit()
			{}
		virtual void OnCallbackClose(
					TCPSError cause
					)
			{
				if(face_.m_prepareDisconnect || TCPS_OK==cause || !face_.m_rpcRequester->IsConnected())
					return;
				ReconnectTask_* task = tcps_NewEx(ReconnectTask_, (face_));
				VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);
				FetchTaskPool()->Push(task);
			}
		virtual void OnPrepareRPCCallback(
					IN const void* inParamsData,
					IN INT_PTR inParamsDataLen,
					OUT BOOL& notifyByTaskPool /*= true*/
					)
			{	face_.OnPrepareRPCCallback_(inParamsData, inParamsDataLen, notifyByTaskPool);	}
		virtual TCPSError OnRPCCallback(
					OUT BOOL& requireReplyData /*= true*/,
					IN const void* inParamsData,
					OUT BOOL& dataTransferred /*= false*/,
					IN INT_PTR inParamsDataLen,
					OUT iscm_IRPCOutfiter* outfiter
					)
		{
			TCPSError err;
			while(true)
			{
				err = face_.OnRPCCallback_(requireReplyData, inParamsData, dataTransferred, inParamsDataLen, outfiter);
				if(TCPS_ERR_POSTING_PENDING_FULL == err)
				{
					ASSERT(!dataTransferred);
					Sleep(1);
					continue;
				}
				else
					break;
			}
			return err;
		}
	};
	friend struct CallbackProxy_;
	CallbackProxy_ m_callbackProxy;

private:
	typedef TCPSError (*FCallbackHandler_)(
						IN PCC_Deploy_RC* thisObj /*= NULL*/,
						IN PCC_Deploy* faceObj /*= NULL*/,
						IN iscm_PeerCallFlags peerCallFlags,
						IN OUT const BYTE*& ptrInParams,
						IN OUT INT_PTR& ptrInParamsLen,
						OUT iscm_IRPCOutfiter* outfiter
						);
	struct CallbackSite_
	{
		FCallbackHandler_ handler;
		BOOL isPosting; // 是否为 posting 修饰的方法/回调
		explicit CallbackSite_(FCallbackHandler_ hd = NULL, BOOL pst = false)
			: handler(hd), isPosting(pst)
			{}
	};
	typedef CQuickStringMap<CPtrStrA, CallbackSite_, QSS_Traits<2> > CallbackMap_;
	static const CallbackMap_* sm_callbackMap;
	static CallbackMap_& GetCallbackMap_();
	static void InitCallbackMap_();

private:
	mutable CLocker m_callbackCallLock;
	struct PostingTask_ : public NPBaseTask
	{
		PCC_Deploy_RC& face_;
		iscm_PeerCallFlags peerCallFlags_;
		void* baseInParamsData_;
		CPtrStrA call_id_;
		const BYTE* inParamsData_;
		INT_PTR inParamsDataLen_;
		FCallbackHandler_ handler_;

		explicit PostingTask_(PCC_Deploy_RC& face) : face_(face) {}
		virtual ~PostingTask_() {}
		virtual void OnPoolTask()
		{
			ASSERT(baseInParamsData_ && inParamsData_ && inParamsDataLen_>=0);
			ASSERT((INT_PTR)(inParamsData_ - (const BYTE*)baseInParamsData_) > 0);
			INT_PTR const inParamsDataLen_t = inParamsDataLen_;
			if(!face_.m_prepareDisconnect && face_.IsConnected())
			{
				CNPAutoLock locker(face_.m_callbackCallLock);
				TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
				if(face_.m_owner)
				{
					void* replyData = NULL;
					INT_PTR replyLen = 0;
					err = face_.m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
					if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
					{
						if(face_.m_owner->IsStreamedCallbackMatched_(call_id_.p, call_id_.len))
						{
							err = face_.m_owner->StreamedCallback_(call_id_.p, call_id_.len, inParamsData_, inParamsDataLen_, replyData, replyLen);
							ASSERT(NULL==replyData && 0==replyLen);
							if(TCPS_OK == err)
							{
								inParamsData_ += inParamsDataLen_;
								inParamsDataLen_ = 0;
							}
							else if(TCPS_ERR_MALFORMED_REQ == err)
								face_.OnNetworkMalformed_();
						}
					}
				}
				if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
				{
					err = handler_(
								&face_, NULL,
								peerCallFlags_,
								inParamsData_,
								inParamsDataLen_,
								NULL/*outfiter*/
								);
				}
				ASSERT(TCPS_OK!=err || 0==inParamsDataLen_);
			}
			else
				ASSERT(true);

			tcps_Free(baseInParamsData_);
			PCC_Deploy_RC& face = face_;
			tcps_Delete(this);

			CNPAutoLock locker(face.m_postingCallbacks.lock);
			face.m_asyncTaskStat.postingCallingBytes -= inParamsDataLen_t;
			ASSERT(face.m_asyncTaskStat.postingCallingBytes >= 0);
			--(face.m_asyncTaskStat.postingCallings);
			ASSERT(face.m_asyncTaskStat.postingCallings >= 0);
			VERIFY(InterlockedDecrement(&face.m_asyncTaskStat.totalAsyncTasks) >= 0);

			ASSERT(face.m_postingCallbacks.calling);
			if(NULL == face.m_postingCallbacks.head)
			{
				face.m_postingCallbacks.calling = false;
				return; // 队列处理完毕
			}

			NPBaseTask* task = face.m_postingCallbacks.head;
			if(face.m_postingCallbacks.head == face.m_postingCallbacks.tail)
				face.m_postingCallbacks.head = face.m_postingCallbacks.tail = NULL;
			else
				face.m_postingCallbacks.head = task->m_nextPoolTask;
			// 此处无须对m_asyncTaskStat.postingCallings等变量进行增加（在OnRPCCallback_()已经加过）
			FetchTaskPool()->Push(task);
		}
	};
	friend struct PostingTask_;
	struct PostingTaskSite_
	{
		mutable CLocker lock;
		BOOL calling;
		NPBaseTask* head;
		NPBaseTask* tail;
		PostingTaskSite_() : calling(false), head(NULL), tail(NULL) {}
	};
	PostingTaskSite_ m_postingCallbacks;

private:
	struct PostingProxy_ : public iscm_IPostingCallerMan::INotifier
	{
		PCC_Deploy_RC& face_;
		INT32 callerKey_; // 为iscm_IPostingCallerMan中的会话标识

		explicit PostingProxy_(PCC_Deploy_RC& face)
			: face_(face), callerKey_(0)
			{}

		virtual void OnSessionClose(
					IN INT32 callerKey,
					IN TCPSError cause
					)
		{
			(void)callerKey; (void)cause;
			ASSERT(callerKey_ == callerKey);
			callerKey_ = 0;
		}

		virtual void OnSessionPost(
					IN INT32 callerKey,
					IN const void* data,
					IN INT_PTR dataLen,
					OUT BOOL& dataTransferred /*= false*/
					)
		{
			(void)callerKey;
			ASSERT(callerKey_ == callerKey);
			while(true)
			{
				BOOL requireReplyData = true;
				TCPSError err = face_.OnRPCCallback_(requireReplyData, data, dataTransferred, dataLen, NULL);
				ASSERT(TCPS_OK!=err || !requireReplyData);
				if(TCPS_ERR_POSTING_PENDING_FULL == err)
				{
					ASSERT(!dataTransferred);
					Sleep(1);
					continue;
				}
				else
					break;
			}
		}
	};
	friend struct PostingProxy_;
	PostingProxy_ m_postingProxy;

private:
	struct NetworkHandler_ : public iscm_IRequester::IEventHandler
	{
		PCC_Deploy_RC& face_;
		explicit NetworkHandler_(PCC_Deploy_RC& face) : face_(face) {}
		virtual BOOL Notify(
					IN iscm_IRequester::EventType ev,
					IN TCPSError cause,
					OUT TCPSError* actionErr /*= NULL*/
					);
	};
	friend struct NetworkHandler_;
	NetworkHandler_ m_networkHandler;

private:
	struct OnConnectedFailedTask_ : public NPBaseTask
	{
		PCC_Deploy_RC& face_;
		explicit OnConnectedFailedTask_(PCC_Deploy_RC& face) : face_(face) {}
		virtual ~OnConnectedFailedTask_() {}
		virtual void OnPoolTask()
		{
			// 停止以前连接
			IPP clientID_IPP, secondaryServeIPP, tertiaryServeIPP;
			IPP serveIPP = face_.m_rpcRequester->GetServeIPP(NULL, &clientID_IPP, &secondaryServeIPP, &tertiaryServeIPP);
			face_.SetServeIPP(INVALID_IPP, face_.m_sessionFlags, INVALID_IPP, INVALID_IPP, INVALID_IPP, face_.m_reconnectIntervalMSELs);

			// 切换IPP后再次异步延迟建立连接
			if(serveIPP.IsValid())
			{
				BOOL const ippSwitched = iscm_ThreeIPPSwitch(serveIPP, secondaryServeIPP, tertiaryServeIPP);
				DWORD delayTicks = face_.m_reconnectIntervalMSELs;
				if(ippSwitched)
					delayTicks = min((DWORD)500, delayTicks);
				face_.m_rpcRequester->SetServeIPP(serveIPP, "PCC_Deploy", iscm_IRequester::cflag_async_connect, clientID_IPP, delayTicks, secondaryServeIPP, tertiaryServeIPP);
				face_.m_prepareDisconnect = false;
			}
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
			tcps_Delete(this);
		}
	};
	friend struct OnConnectedFailedTask_;

private:
	struct StreamedCall_Task_;
	friend struct StreamedCall_Task_;

// posting method方法的异步投递任务类声明，
// 在回调里面调用自身的方法时，使用异步任务（防止死锁）。
private:
	struct SetTimeout__Task_;
	friend struct SetTimeout__Task_;
	struct SetSessionBufferSize__Task_;
	friend struct SetSessionBufferSize__Task_;
};

TCPSError PCC_Deploy_RC::CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback
{
	if(0==callbacks.Length() || callbacks.Length()!=callbackTypeInfos.Length())
		return TCPS_ERR_INVALID_PARAM;

	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<1> > CallbackMap_;
	static CallbackMap_* s_cbMap = NULL;
	if(NULL == s_cbMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_cbMap)
		{
			static CallbackMap_ s_cbMapObj;
			CallbackMap_& cbMap = s_cbMapObj;
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetRedirect_"), CPtrStrA(s_PCC_Deploy_SetRedirect__TypeInfo_, s_PCC_Deploy_SetRedirect__TypeInfo_len_))).second);
			s_cbMap = &cbMap;
		}
	}

	matchingFlags.Resize(callbacks.Length());
	for(int index=0; index<callbacks.Length(); ++index)
	{
		BOOL& flag = matchingFlags[index];
		const tcps_String& name = callbacks[index];
		const tcps_String& typeInfos = callbackTypeInfos[index];
		CallbackMap_::const_iterator cit = s_cbMap->find(name.Get(), name.Length());
		if(cit!=s_cbMap->end() && 0==typeInfos.Compare(cit->second.p, cit->second.len))
			flag = true;
		else
			flag = false;
	}
	return TCPS_OK;
}

PCC_Deploy::MethodMatchingFlag::MethodMatchingFlag()
{
	Reset();
	mmap_.insert(std::make_pair(CPtrStrA("Login", 5), Info(&matching_Login, false)));
	mmap_.insert(std::make_pair(CPtrStrA("Logout", 6), Info(&matching_Logout, false)));
	mmap_.insert(std::make_pair(CPtrStrA("CreateTrunk", 11), Info(&matching_CreateTrunk, false)));
	mmap_.insert(std::make_pair(CPtrStrA("RemoveTrunk", 11), Info(&matching_RemoveTrunk, false)));
	mmap_.insert(std::make_pair(CPtrStrA("ListTrunk", 9), Info(&matching_ListTrunk, false)));
	mmap_.insert(std::make_pair(CPtrStrA("AddAuthCenter", 13), Info(&matching_AddAuthCenter, false)));
	mmap_.insert(std::make_pair(CPtrStrA("RemoveAuthCenter", 16), Info(&matching_RemoveAuthCenter, false)));
	mmap_.insert(std::make_pair(CPtrStrA("ListAuthCenter", 14), Info(&matching_ListAuthCenter, false)));
	mmap_.insert(std::make_pair(CPtrStrA("FindAuthCenter", 14), Info(&matching_FindAuthCenter, false)));
	mmap_.insert(std::make_pair(CPtrStrA("AddModule", 9), Info(&matching_AddModule, false)));
	mmap_.insert(std::make_pair(CPtrStrA("AddModuleFile", 13), Info(&matching_AddModuleFile, false)));
	mmap_.insert(std::make_pair(CPtrStrA("RemoveModule", 12), Info(&matching_RemoveModule, false)));
	mmap_.insert(std::make_pair(CPtrStrA("RemoveModuleFiles", 17), Info(&matching_RemoveModuleFiles, false)));
	mmap_.insert(std::make_pair(CPtrStrA("ListModules", 11), Info(&matching_ListModules, false)));
	mmap_.insert(std::make_pair(CPtrStrA("AddModel", 8), Info(&matching_AddModel, false)));
	mmap_.insert(std::make_pair(CPtrStrA("DelModel", 8), Info(&matching_DelModel, false)));
	mmap_.insert(std::make_pair(CPtrStrA("SetTimeout_", 11), Info(&matching_SetTimeout_, true)));
	mmap_.insert(std::make_pair(CPtrStrA("SetSessionBufferSize_", 21), Info(&matching_SetSessionBufferSize_, true)));
}

void PCC_Deploy::MethodMatchingFlag::Reset()
{
	matching_Login = false;
	matching_Logout = false;
	matching_CreateTrunk = false;
	matching_RemoveTrunk = false;
	matching_ListTrunk = false;
	matching_AddAuthCenter = false;
	matching_RemoveAuthCenter = false;
	matching_ListAuthCenter = false;
	matching_FindAuthCenter = false;
	matching_AddModule = false;
	matching_AddModuleFile = false;
	matching_RemoveModule = false;
	matching_RemoveModuleFiles = false;
	matching_ListModules = false;
	matching_AddModel = false;
	matching_DelModel = false;
	matching_SetTimeout_ = false;
	matching_SetSessionBufferSize_ = false;
}

TCPSError PCC_Deploy_RC::UpdateMethodMatchingFlag_()
{
	if(!m_methodMatchingUpdatedFlag.needUpdate)
		return TCPS_OK;
	InitializeAllCallsTypeInfo_();
	tcps_String methods_ar[18];
	IN tcps_Array<tcps_String> methods;
	methods.Attach(xat_bind, methods_ar, 18);
	tcps_String methodTypeInfos_ar[18];
	IN tcps_Array<tcps_String> methodTypeInfos;
	methodTypeInfos.Attach(xat_bind, methodTypeInfos_ar, 18);
	methods_ar[0].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("Login"));
	methodTypeInfos_ar[0].Attach(xat_bind, (char*)s_PCC_Deploy_Login_TypeInfo_, s_PCC_Deploy_Login_TypeInfo_len_);
	methods_ar[1].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("Logout"));
	methodTypeInfos_ar[1].Attach(xat_bind, (char*)s_PCC_Deploy_Logout_TypeInfo_, s_PCC_Deploy_Logout_TypeInfo_len_);
	methods_ar[2].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("CreateTrunk"));
	methodTypeInfos_ar[2].Attach(xat_bind, (char*)s_PCC_Deploy_CreateTrunk_TypeInfo_, s_PCC_Deploy_CreateTrunk_TypeInfo_len_);
	methods_ar[3].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("RemoveTrunk"));
	methodTypeInfos_ar[3].Attach(xat_bind, (char*)s_PCC_Deploy_RemoveTrunk_TypeInfo_, s_PCC_Deploy_RemoveTrunk_TypeInfo_len_);
	methods_ar[4].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("ListTrunk"));
	methodTypeInfos_ar[4].Attach(xat_bind, (char*)s_PCC_Deploy_ListTrunk_TypeInfo_, s_PCC_Deploy_ListTrunk_TypeInfo_len_);
	methods_ar[5].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("AddAuthCenter"));
	methodTypeInfos_ar[5].Attach(xat_bind, (char*)s_PCC_Deploy_AddAuthCenter_TypeInfo_, s_PCC_Deploy_AddAuthCenter_TypeInfo_len_);
	methods_ar[6].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("RemoveAuthCenter"));
	methodTypeInfos_ar[6].Attach(xat_bind, (char*)s_PCC_Deploy_RemoveAuthCenter_TypeInfo_, s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_);
	methods_ar[7].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("ListAuthCenter"));
	methodTypeInfos_ar[7].Attach(xat_bind, (char*)s_PCC_Deploy_ListAuthCenter_TypeInfo_, s_PCC_Deploy_ListAuthCenter_TypeInfo_len_);
	methods_ar[8].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("FindAuthCenter"));
	methodTypeInfos_ar[8].Attach(xat_bind, (char*)s_PCC_Deploy_FindAuthCenter_TypeInfo_, s_PCC_Deploy_FindAuthCenter_TypeInfo_len_);
	methods_ar[9].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("AddModule"));
	methodTypeInfos_ar[9].Attach(xat_bind, (char*)s_PCC_Deploy_AddModule_TypeInfo_, s_PCC_Deploy_AddModule_TypeInfo_len_);
	methods_ar[10].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("AddModuleFile"));
	methodTypeInfos_ar[10].Attach(xat_bind, (char*)s_PCC_Deploy_AddModuleFile_TypeInfo_, s_PCC_Deploy_AddModuleFile_TypeInfo_len_);
	methods_ar[11].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("RemoveModule"));
	methodTypeInfos_ar[11].Attach(xat_bind, (char*)s_PCC_Deploy_RemoveModule_TypeInfo_, s_PCC_Deploy_RemoveModule_TypeInfo_len_);
	methods_ar[12].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("RemoveModuleFiles"));
	methodTypeInfos_ar[12].Attach(xat_bind, (char*)s_PCC_Deploy_RemoveModuleFiles_TypeInfo_, s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_);
	methods_ar[13].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("ListModules"));
	methodTypeInfos_ar[13].Attach(xat_bind, (char*)s_PCC_Deploy_ListModules_TypeInfo_, s_PCC_Deploy_ListModules_TypeInfo_len_);
	methods_ar[14].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("AddModel"));
	methodTypeInfos_ar[14].Attach(xat_bind, (char*)s_PCC_Deploy_AddModel_TypeInfo_, s_PCC_Deploy_AddModel_TypeInfo_len_);
	methods_ar[15].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("DelModel"));
	methodTypeInfos_ar[15].Attach(xat_bind, (char*)s_PCC_Deploy_DelModel_TypeInfo_, s_PCC_Deploy_DelModel_TypeInfo_len_);
	methods_ar[16].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetTimeout_"));
	methodTypeInfos_ar[16].Attach(xat_bind, (char*)s_PCC_Deploy_SetTimeout__TypeInfo_, s_PCC_Deploy_SetTimeout__TypeInfo_len_);
	methods_ar[17].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetSessionBufferSize_"));
	methodTypeInfos_ar[17].Attach(xat_bind, (char*)s_PCC_Deploy_SetSessionBufferSize__TypeInfo_, s_PCC_Deploy_SetSessionBufferSize__TypeInfo_len_);
	OUT tcps_Array<BOOL> matchingFlags;
	TCPSError err = this->MethodCheck_(methods, methodTypeInfos, matchingFlags);
	if(TCPS_OK == err)
	{
		if(matchingFlags.Length() == methods.Length())
		{
			m_methodMatchingUpdatedFlag.needUpdate = false;
			const BOOL* const matchingFlags_p = matchingFlags.Get();
			m_methodMatchingFlag.matching_Login = matchingFlags_p[0];
			m_methodMatchingFlag.matching_Logout = matchingFlags_p[1];
			m_methodMatchingFlag.matching_CreateTrunk = matchingFlags_p[2];
			m_methodMatchingFlag.matching_RemoveTrunk = matchingFlags_p[3];
			m_methodMatchingFlag.matching_ListTrunk = matchingFlags_p[4];
			m_methodMatchingFlag.matching_AddAuthCenter = matchingFlags_p[5];
			m_methodMatchingFlag.matching_RemoveAuthCenter = matchingFlags_p[6];
			m_methodMatchingFlag.matching_ListAuthCenter = matchingFlags_p[7];
			m_methodMatchingFlag.matching_FindAuthCenter = matchingFlags_p[8];
			m_methodMatchingFlag.matching_AddModule = matchingFlags_p[9];
			m_methodMatchingFlag.matching_AddModuleFile = matchingFlags_p[10];
			m_methodMatchingFlag.matching_RemoveModule = matchingFlags_p[11];
			m_methodMatchingFlag.matching_RemoveModuleFiles = matchingFlags_p[12];
			m_methodMatchingFlag.matching_ListModules = matchingFlags_p[13];
			m_methodMatchingFlag.matching_AddModel = matchingFlags_p[14];
			m_methodMatchingFlag.matching_DelModel = matchingFlags_p[15];
			m_methodMatchingFlag.matching_SetTimeout_ = matchingFlags_p[16];
			m_methodMatchingFlag.matching_SetSessionBufferSize_ = matchingFlags_p[17];
		}
		else
		{
			ASSERT(false);
			err = TCPS_ERR_MALFORMED_REPLY;
		}
	}
	if(m_methodMatchingUpdatedFlag.needUpdate)
		m_methodMatchingFlag.Reset();
	return err;
}

const PCC_Deploy::MethodMatchingFlag& PCC_Deploy_RC::GetMethodMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	TCPSError ret = UpdateMethodMatchingFlag_();
	if(err)
		*err = ret;
	return m_methodMatchingFlag;
}

BOOL PCC_Deploy_RC::NetworkHandler_::Notify(
				IN iscm_IRequester::EventType ev,
				IN TCPSError cause,
				OUT TCPSError* actionErr /*= NULL*/
				)
{
	if(actionErr)
		*actionErr = TCPS_OK;
	if(iscm_IRequester::et_connected==ev || iscm_IRequester::et_attached==ev)
	{
		if(face_.m_prepareDisconnect)
			return true;
	}

	if(iscm_IRequester::et_connected == ev)
	{
#if 1
		// 建立回调通道
		if(0 == (face_.m_sessionFlags&ISCMC_NO_CALLBACK))
		{
			// 连接回调通道，使用直接连接方式
			IPP const serveIPP = face_.m_rpcRequester->GetServingIPP();
			INT32 peerSessionKey;
			INT64 const bindID = face_.m_rpcRequester->GetPeerSessionKey(peerSessionKey);
			ASSERT(serveIPP.IsValid() && 0!=bindID && 0!=peerSessionKey);

			AutoDeleteInterface<iscm_IRequester> autoRequester;
			autoRequester.face_ = iscm_MakeRequester(false);
			if(NULL == autoRequester.face_)
			{
				// 容错处理
				ASSERT(false);
				if(actionErr)
					*actionErr = TCPS_ERR_OUT_OF_MEMORY;
				return false;
			}

			DWORD connectTimeout = INFINITE;
			DWORD recvTimeout = INFINITE;
			DWORD sendTimeout = INFINITE;
			face_.m_rpcRequester->GetTimeout(&connectTimeout, &recvTimeout, &sendTimeout);
			DWORD const timeoutMSELs = (INFINITE==connectTimeout ? iscm_GetDefaultConnectTimeout() : connectTimeout);
			BOOL const is_AF_LOCAL = tcps_Use_AF_LOCAL(serveIPP.ip_);
			SOCKET cbSock = TCPNewClientByTime(serveIPP.ip_, serveIPP.port_, timeoutMSELs, is_AF_LOCAL);
			if(!SockValid(cbSock))
			{
				if(actionErr)
					*actionErr = TCPS_ERR_CONNECT_FAILED;
				return false;
			}

			iscm_IRequester* callbackRequester = autoRequester.face_;
			VERIFY(TCPS_OK == callbackRequester->AttachSocket(cbSock, true));

			// 若应用程序没有调用过SetTimeout()，则此处使用有限时间超时（ISCM对同步RPC调用默认使用超长时间超时，见'iscm_requester.cpp'）
			recvTimeout = (INFINITE==recvTimeout ? 2000 : recvTimeout);
			sendTimeout = (INFINITE==sendTimeout ? 1000 : sendTimeout);
			callbackRequester->SetTimeout(INFINITE, recvTimeout, sendTimeout);

			SockWriteBuf swb[2];
			swb[0].data = &bindID;
			swb[0].len = sizeof(bindID);
			swb[1].data = &peerSessionKey;
			swb[1].len = sizeof(peerSessionKey);
			tcps_Binary reply;
			TCPSError err = callbackRequester->Call(RPCCT_TO_CALLBACK, swb, ARRAY_LEN(swb), reply);
			if(TCPS_OK != err)
			{
				if(actionErr)
					*actionErr = err;
				return false;
			}
			ASSERT(reply.IsEmpty());

			VERIFY(cbSock == callbackRequester->DropSocket());
			face_.m_callbackProxy.IncreaseCallbackRef();
			iscm_FetchCallbackServeMan().AddCallbackClient(&face_.m_callbackProxy, cbSock);
		}
#endif

#if 1
		// 建立posting通道
		if(0 == (face_.m_sessionFlags&ISCMC_NO_POSTING_CHANNEL)
			&& 0 == (face_.m_sessionFlags&ISCMC_UDP_POSTING)
			)
		{
			// 连接posting通道，使用直接连接方式
			SOCKET postingSock = INVALID_SOCKET;

			AutoDeleteInterface<iscm_IRequester> autoRequester;
			autoRequester.face_ = iscm_MakeRequester(false);
			if(NULL == autoRequester.face_)
			{
				// 容错处理
				ASSERT(false);
				if(actionErr)
					*actionErr = TCPS_ERR_OUT_OF_MEMORY;
				return false;
			}

			DWORD connectTimeout = INFINITE;
			DWORD recvTimeout = INFINITE;
			DWORD sendTimeout = INFINITE;
			face_.m_rpcRequester->GetTimeout(&connectTimeout, &recvTimeout, &sendTimeout);
			DWORD const timeoutMSELs = (INFINITE==connectTimeout ? iscm_GetDefaultConnectTimeout() : connectTimeout);
			INT32 peerSessionKey;
			INT64 const bindID = face_.m_rpcRequester->GetPeerSessionKey(peerSessionKey);
			ASSERT(0!=bindID && 0!=peerSessionKey);

			IPP const serveIPP = face_.m_rpcRequester->GetServingIPP();
			ASSERT(serveIPP.IsValid());
			BOOL is_AF_LOCAL = tcps_Use_AF_LOCAL(serveIPP.ip_);
			postingSock = TCPNewClientByTime(serveIPP.ip_, serveIPP.port_, timeoutMSELs, is_AF_LOCAL);
			if(!SockValid(postingSock))
			{
				if(actionErr)
					*actionErr = TCPS_ERR_CONNECT_FAILED;
				return false;
			}

			iscm_IRequester* postingRequester = autoRequester.face_;
			VERIFY(TCPS_OK == postingRequester->AttachSocket(postingSock, true));

			// 若应用程序没有调用过SetTimeout()，则此处使用有限时间超时（ISCM对同步RPC调用默认使用超长时间超时，见'iscm_requester.cpp'）
			recvTimeout = (INFINITE==recvTimeout ? 2000 : recvTimeout);
			sendTimeout = (INFINITE==sendTimeout ? 1000 : sendTimeout);
			postingRequester->SetTimeout(INFINITE, recvTimeout, sendTimeout);

			SockWriteBuf swb[2];
			swb[0].data = &bindID;
			swb[0].len = sizeof(bindID);
			swb[1].data = &peerSessionKey;
			swb[1].len = sizeof(peerSessionKey);
			tcps_Binary reply;
			TCPSError err = postingRequester->Call(RPCCT_TO_POSTING_CHANNEL, swb, ARRAY_LEN(swb), reply);
			/*if(TCPS_OK != err)
			{
				if(TCPS_ERR_NOT_SUPPORTED != err)
				{
					if(actionErr)
						*actionErr = err;
					return false;
				}
			}*/
			ASSERT(reply.IsEmpty());

			if(TCPS_OK == err)
			{
				VERIFY(postingSock == postingRequester->DropSocket());
				iscm_FetchPostingCallerMan().AddSession(face_.m_postingProxy.callerKey_, postingSock, true, &face_.m_postingProxy);
			}
		}
#endif
	}
	else if(iscm_IRequester::et_broken==ev || iscm_IRequester::et_dropped==ev)
	{
		// 总尝试删除一次
#if 1
		iscm_FetchCallbackServeMan().DelCallbackClient(&face_.m_callbackProxy);
#endif
#if 1
		if(0 != face_.m_postingProxy.callerKey_)
			iscm_FetchPostingCallerMan().CloseSession(face_.m_postingProxy.callerKey_);
#endif
	}

	if(iscm_IRequester::et_connected==ev || iscm_IRequester::et_attached==ev)
	{
		DWORD recvTimeout = INFINITE;
		DWORD sendTimeout = INFINITE;
		face_.GetTimeout(NULL, &recvTimeout, &sendTimeout);
		if(INFINITE!=recvTimeout || INFINITE!=sendTimeout)
			face_.SetTimeout_(recvTimeout, sendTimeout);

		INT32 recvBufBytes = -1;
		INT32 sendBufBytes = -1;
		face_.GetSessionBufferSize(&recvBufBytes, &sendBufBytes);
		if(recvBufBytes>=0 || sendBufBytes>=0)
			face_.SetSessionBufferSize_(recvBufBytes, sendBufBytes);
		if((0 == (face_.m_sessionFlags&ISCMC_NO_CALLBACK)) && (recvBufBytes>=0 || sendBufBytes>=0))
		{
			iscm_ICallbackServeMan& man = iscm_FetchCallbackServeMan();
			man.SetSessionBufferSize(&face_.m_callbackProxy, recvBufBytes, sendBufBytes);
		}

		ASSERT(!face_.m_needBrokenNotify);
		face_.m_needBrokenNotify = true;
		TCPSError err = TCPS_ERROR;

		// 此处对m_asyncTaskStat.totalAsyncTasks提前加一，以防止如下情况发生：
		// 当用户程序在OnConnected()中异步投递了删除本Client对象的任务，且返回非TCPS_OK；
		// 此时可能OnConnectedFailedTask_::OnPoolTask()被执行时，本Client对象已经被析构，
		// 导致非法内存错误。
		VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);

		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnConnected);
			try
			{
				err = face_.OnConnected();
			}
			catch(TCPSError ret)
			{
				ASSERT(TCPS_OK != ret);
				err = ret;
			}
			catch(int ret)
			{
				ASSERT(TCPS_OK != ret);
				err = (TCPSError)ret;
			}
			catch(std::bad_alloc)
			{
				err = TCPS_ERR_OUT_OF_MEMORY;
			}
			ISCM_BEGIN_CATCH_ALL_()
				err = TCPS_ERR_UNKNOWN_EXCEPTION;
			ISCM_END_CATCH_ALL_()
		}

		if(TCPS_OK!=err && 0==(ISCMC_NO_ASYNC_RECONNECT&face_.m_sessionFlags))
		{
			// 在OnConnected()之前引用计数已经加一，此处不能再加
		//	VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);
			OnConnectedFailedTask_* task = tcps_NewEx(OnConnectedFailedTask_, (face_));
			FetchTaskPool()->Push(task);
		}
		else
		{
			// OnConnected()返回成功，对在OnConnected()之前的引用计数加一做对称处理
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		}
		if(actionErr)
			*actionErr = err;
	}
	else if(iscm_IRequester::et_connect_timeout == ev)
	{
		iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnConnectTimeout);
		ISCM_BEGIN_TRY_()
			face_.OnConnectTimeout(cause);
		ISCM_END_TRY_()
		ISCM_BEGIN_CATCH_ALL_()
		ISCM_END_CATCH_ALL_()
	}
	else
	{
		ASSERT(iscm_IRequester::et_broken==ev || iscm_IRequester::et_dropped==ev);
		if(0 != face_.m_postingProxy.callerKey_)
			iscm_FetchPostingCallerMan().CloseSession(face_.m_postingProxy.callerKey_);
		ASSERT(face_.m_callbackProxy.callbackRefCount_ >= 0);
		while(face_.m_callbackProxy.callbackRefCount_ > 0)
			Sleep(1);
		while(0 != face_.m_postingProxy.callerKey_)
			Sleep(1);
		while(face_.m_asyncTaskStat.postingCallings > 0)
			Sleep(1);
		ASSERT(0==face_.m_asyncTaskStat.postingCallingBytes && 0==face_.m_asyncTaskStat.postingCallings);
		if(face_.m_needBrokenNotify)
		{
			face_.m_needBrokenNotify = false;
			{
				iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnClose);
				ISCM_BEGIN_TRY_()
					if(face_.m_owner && (INVALID_OSTHREADID==face_.m_owner->GetClosingTID_() || OSThreadSelf()!=face_.m_owner->GetClosingTID_()))
						face_.OnPeerBroken();
					face_.OnClose();
				ISCM_END_TRY_()
				ISCM_BEGIN_CATCH_ALL_()
				ISCM_END_CATCH_ALL_()
			}
		}
	}
	face_.m_methodMatchingUpdatedFlag.needUpdate = true;

	return true;
}

const PCC_Deploy_RC::CallbackMap_* PCC_Deploy_RC::sm_callbackMap = NULL;
PCC_Deploy_RC::CallbackMap_& PCC_Deploy_RC::GetCallbackMap_()
	{	LOCAL_SAFE_STATIC_OBJ(CallbackMap_);	}

void PCC_Deploy_RC::InitCallbackMap_()
{
	if(sm_callbackMap)
		return;
	IscmRPCGlobalLocker locker;
	if(sm_callbackMap)
		return;
	CallbackMap_& cbMap = GetCallbackMap_();
	ASSERT(0 == cbMap.size());
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::SetRedirect_"), CallbackSite_(&PCC_Deploy_RC::Wrap_SetRedirect_, true))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_Deploy::CallbackCheck_"), CallbackSite_(&PCC_Deploy_RC::Wrap_CallbackCheck_, false))).second);
	sm_callbackMap = &cbMap;
}

PCC_Deploy_RC::PCC_Deploy_RC(PCC_Deploy* owner /*= NULL*/)
	: m_owner(owner)
	, m_sessionFlags(0)
	, m_reconnectIntervalMSELs(2000)
	, m_rpcRequester(iscm_MakeRequester(false))
	, m_needBrokenNotify(false)
	, m_prepareDisconnect(false)
	, m_callbackProxy(*this)
	, m_postingProxy(*this)
	, m_networkHandler(*this)
{
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_String*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_Binary*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_Array<int>*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((CPtrStrA*)64)->len));

	m_rpcRequester->SetEventHandler(&m_networkHandler);
	iscm_InitClientSingletons(true, true);
	InitCallbackMap_();
}

PCC_Deploy_RC::~PCC_Deploy_RC()
{
	DestroyRequester();
}

void PCC_Deploy_RC::DestroyRequester()
{
	if(NULL == m_rpcRequester)
		return;
	NPR_ASSERT_EX(!m_callingOutTIDs.HasFlag(OSThreadSelf(), NULL), "禁止在对象自己的调用里删除自身");
	PrepareDisconnect();
	while(0 != m_postingProxy.callerKey_)
		Sleep(1);
	ASSERT(m_callbackProxy.callbackRefCount_ >= 0);
	while(m_callbackProxy.callbackRefCount_ > 0)
		Sleep(1);
	ASSERT(m_asyncTaskStat.postingCallingBytes>=0 && m_asyncTaskStat.postingCallings>=0 && m_asyncTaskStat.totalAsyncTasks>=0);
	while(m_asyncTaskStat.totalAsyncTasks > 0)
		Sleep(1);
	ASSERT(0==m_asyncTaskStat.postingCallingBytes && 0==m_asyncTaskStat.postingCallings);
	m_rpcRequester->DeleteThis();
	m_rpcRequester = NULL;
}

TCPSError PCC_Deploy_RC::SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	NPR_ASSERT_EX(!m_callingOutTIDs.HasFlag(OSThreadSelf(), NULL), "禁止在对象自己的调用里调用此函数");
	m_sessionFlags = sessionFlags;
	m_sessionFlags &= ~ISCMC_NO_CALLBACK; // 本接口支持重定向，总启动回调（忽略ISCMC_NO_CALLBACK标志）
	m_reconnectIntervalMSELs = max((DWORD)10, reconnectIntervalMSELs);
	DWORD t1, t2, t3;
	m_rpcRequester->GetTimeout(&t1, &t2, &t3, NULL);
	m_rpcRequester->SetTimeout(t1, t2, t2, m_reconnectIntervalMSELs);
	iscm_IRequester::ConnectFlag cflag;
	if(ISCMC_ASYNC_CONNECT&sessionFlags)
		cflag = iscm_IRequester::cflag_async_connect;
	else if(ISCMC_NO_ASYNC_RECONNECT&sessionFlags)
		cflag = iscm_IRequester::cflag_wait_no_reconnect;
	else
		cflag = iscm_IRequester::cflag_wait_async_reconnect;
	TCPSError err = m_rpcRequester->SetServeIPP(serveIPP, "PCC_Deploy", cflag, clientID_IPP, 0, secondaryServeIPP, tertiaryServeIPP);
	if(serveIPP.IsValid())
		m_prepareDisconnect = false;
	return err;
}

IPP PCC_Deploy_RC::GetServeIPP() const
	{	return m_rpcRequester->GetServeIPP();	}

IPP PCC_Deploy_RC::GetServingIPP() const
	{	return m_rpcRequester->GetServingIPP();	}

BOOL PCC_Deploy_RC::IsConnected() const
	{	return m_rpcRequester->IsConnected();	}

void PCC_Deploy_RC::SetKeeping(
			IN BOOL keeping
			)
	{	m_rpcRequester->SetKeeping(keeping);	}

BOOL PCC_Deploy_RC::IsKeeping() const
	{	return m_rpcRequester->IsKeeping();	}

void PCC_Deploy_RC::PrepareDisconnect()
{
	m_prepareDisconnect = true;
	m_rpcRequester->PrepareDisconnect();
	if(0 != m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().CloseSession(m_postingProxy.callerKey_);
	iscm_FetchCallbackServeMan().DelCallbackClient(&m_callbackProxy);
}

void PCC_Deploy_RC::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	m_rpcRequester->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	if(IsConnected())
		SetTimeout_(recvTimeout, sendTimeout);
}

void PCC_Deploy_RC::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const
	{	m_rpcRequester->GetTimeout(connectTimeout, recvTimeout, sendTimeout);	}

void PCC_Deploy_RC::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	if(recvBufBytes<0 && sendBufBytes<0)
		return;
	m_rpcRequester->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	if(0 == (m_sessionFlags&ISCMC_NO_CALLBACK))
	{
		iscm_ICallbackServeMan& man = iscm_FetchCallbackServeMan();
		man.SetSessionBufferSize(&m_callbackProxy, recvBufBytes, sendBufBytes);
	}
	if(IsConnected())
		SetSessionBufferSize_(recvBufBytes, sendBufBytes);
}

void PCC_Deploy_RC::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
	{	m_rpcRequester->GetSessionBufferSize(recvBufBytes, sendBufBytes);	}

void PCC_Deploy_RC::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
	{	m_postingPendingParam.Set(maxPendingBytes, maxPendings);	}

void PCC_Deploy_RC::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
	{	m_postingPendingParam.Get(maxPendingBytes, maxPendings);	}

void PCC_Deploy_RC::OnPrepareRPCCallback_(
				IN const void* inParamsData,
				IN INT_PTR inParamsDataLen,
				OUT BOOL& notifyByTaskPool /*= true*/
				)
{
#if 1
	// 所有调用都用taskPool异步方式，以保证不同会话的并行调用
	ASSERT(inParamsData && inParamsDataLen>0 && notifyByTaskPool);
	(void)inParamsData; (void)inParamsDataLen; (void)notifyByTaskPool;
#else
	ASSERT(inParamsData && inParamsDataLen>0 && notifyByTaskPool);
	const BYTE* ptrInParams = (const BYTE*)inParamsData;
	INT_PTR ptrInParamsLen = inParamsDataLen;

	if(ptrInParamsLen < (int)sizeof(iscm_PeerCallFlags))
		return;
	iscm_PeerCallFlags peerCallFlags = *(iscm_PeerCallFlags*)ptrInParams;
	if((int)sizeof(BOOL) != peerCallFlags.sizeofBOOL_req)
		return;
	if((int)sizeof(DummyEnumType) != peerCallFlags.sizeofEnum_req)
		return;
	ptrInParams += sizeof(iscm_PeerCallFlags);
	ptrInParamsLen -= sizeof(iscm_PeerCallFlags);

	if(ptrInParamsLen < (int)sizeof(INT32))
		return;
	INT32 call_id_len = *(INT32*)ptrInParams;
	ptrInParams += sizeof(INT32);
	ptrInParamsLen -= sizeof(INT32);
	if(ptrInParamsLen < call_id_len+1)
		return;
	const char* call_id = (const char*)ptrInParams;
	ptrInParams += call_id_len+1;
	ptrInParamsLen -= call_id_len+1;

	ASSERT(sm_callbackMap);
	CallbackMap_::const_iterator cit = sm_callbackMap->find(call_id, call_id_len);
	if(sm_callbackMap->end() == cit)
		return;

	if(cit->second.isPosting)
		notifyByTaskPool = false;
#endif
}

TCPSError PCC_Deploy_RC::OnRPCCallback_(
				OUT BOOL& requireReplyData /*= true*/,
				IN const void* inParamsData,
				OUT BOOL& dataTransferred /*= false*/,
				IN INT_PTR inParamsDataLen,
				OUT iscm_IRPCOutfiter* outfiter
				)
{
	(void)inParamsDataLen; // avoid warning.
	ASSERT(requireReplyData && inParamsData && inParamsDataLen>0/* && outfiter*/);
	const BYTE* ptrInParams = (const BYTE*)inParamsData;
	INT_PTR ptrInParamsLen = inParamsDataLen;

	if(ptrInParamsLen < (int)sizeof(iscm_PeerCallFlags))
		return TCPS_ERR_MALFORMED_REQ;
	iscm_PeerCallFlags peerCallFlags = *(iscm_PeerCallFlags*)ptrInParams;
	if((int)sizeof(BOOL) != peerCallFlags.sizeofBOOL_req)
		return TCPS_ERR_MALFORMED_REQ;
	if((int)sizeof(DummyEnumType) != peerCallFlags.sizeofEnum_req)
		return TCPS_ERR_MALFORMED_REQ;
	ptrInParams += sizeof(iscm_PeerCallFlags);
	ptrInParamsLen -= sizeof(iscm_PeerCallFlags);

	if(ptrInParamsLen < (int)sizeof(INT32))
		return TCPS_ERR_MALFORMED_REQ;
	INT32 call_id_len = *(INT32*)ptrInParams;
	ptrInParams += sizeof(INT32);
	ptrInParamsLen -= sizeof(INT32);
	if(ptrInParamsLen < call_id_len+1)
		return TCPS_ERR_MALFORMED_REQ;
	const char* call_id = (const char*)ptrInParams;
	ptrInParams += call_id_len+1;
	ptrInParamsLen -= call_id_len+1;

	ASSERT(sm_callbackMap);
	CallbackMap_::const_iterator cit = sm_callbackMap->find(call_id, call_id_len);
	if(sm_callbackMap->end() == cit)
		return TCPS_ERR_TRY_CALL_OTHER_METHODS; // 本接口不支持，尝试其它接口

	CPtrStrA const streamedCallID(call_id+CONST_STR_LEN("PCC_Deploy::"), call_id_len-CONST_STR_LEN("PCC_Deploy::"));

	// posting回调
	if(cit->second.isPosting)
	{
		if(m_prepareDisconnect)
			return TCPS_ERR_EXITING;

		// 当缓存的未决调用小于1个时，直接调用
		if(m_postingPendingParam.maxPendings_ <= 1)
		{
			CNPAutoLock locker(m_callbackCallLock);
			TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
			if(m_owner)
			{
				void* replyData = NULL;
				INT_PTR replyLen = 0;
				err = m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
				if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
				{
					if(!m_owner->IsStreamedCallbackMatched_(streamedCallID.p, streamedCallID.len))
						return TCPS_ERR_CALLBACK_NOT_MATCH;

					{
						iscm_ClientCallType cct = (cit->second.isPosting ? iscm_cct_posting_callback : iscm_cct_callback);
						iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(m_callingOutTIDs, cct);
						err = m_owner->StreamedCallback_(streamedCallID.p, streamedCallID.len, ptrInParams, ptrInParamsLen, replyData, replyLen);
					}
					ASSERT(NULL==replyData && 0==replyLen);
					if(TCPS_OK == err)
					{
						ptrInParams += ptrInParamsLen;
						ptrInParamsLen = 0;
					}
					else if(TCPS_ERR_MALFORMED_REQ == err)
					{
						this->OnNetworkMalformed_();
						return TCPS_ERR_MALFORMED_REQ;
					}
				}
			}
			if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
				err = cit->second.handler(this, NULL, peerCallFlags, ptrInParams, ptrInParamsLen, NULL/*outfiter*/);
#ifdef _DEBUG
			if(TCPS_OK == err)
			{
				ASSERT(ptrInParams-(const BYTE*)inParamsData == inParamsDataLen);
				ASSERT(0 == ptrInParamsLen);
			}
#else
			(void)err;
#endif
			ASSERT(!peerCallFlags.requireReply);
			requireReplyData = false;
			ASSERT(!dataTransferred);
			return TCPS_OK;
		}

		// 投递一个task，异步执行
		if(m_asyncTaskStat.postingCallingBytes >= m_postingPendingParam.maxPendingBytes_
			|| m_asyncTaskStat.postingCallings >= m_postingPendingParam.maxPendings_
			)
		{
			// 对内置的SetRedirect_()回调，不做限制
			if("PCC_Deploy::SetRedirect_" != cit->first)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}

		// 投递一个异步回调任务，或加入待执行队列
		PostingTask_* task = tcps_NewEx(PostingTask_, (*this));
		task->peerCallFlags_ = peerCallFlags;
		task->baseInParamsData_ = (void*)inParamsData;
		task->call_id_ = streamedCallID;
		task->inParamsData_ = ptrInParams;
		task->inParamsDataLen_ = ptrInParamsLen;
		task->handler_ = cit->second.handler;
		VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
		{
			CNPAutoLock locker(m_postingCallbacks.lock);
			m_asyncTaskStat.postingCallingBytes += ptrInParamsLen;
			++(m_asyncTaskStat.postingCallings);
			if(m_postingCallbacks.calling)
			{
				task->m_nextPoolTask = NULL;
				if(m_postingCallbacks.tail)
				{
					m_postingCallbacks.tail->m_nextPoolTask = task;
					m_postingCallbacks.tail = task;
				}
				else
					m_postingCallbacks.head = m_postingCallbacks.tail = task;
			}
			else
			{
				ASSERT(NULL==m_postingCallbacks.head && NULL==m_postingCallbacks.tail);
				ASSERT(ptrInParamsLen==m_asyncTaskStat.postingCallingBytes && 1==m_asyncTaskStat.postingCallings);
				m_postingCallbacks.calling = true;
				FetchTaskPool()->Push(task);
			}
		}

		if(peerCallFlags.requireReply)
		{
			// 给outfiter填充内置返回参数
			struct PostOutParamWrapSite
			{
				iscm_RPCReplyPrefix replyPrefix;
				PostOutParamWrapSite() { replyPrefix.Init(); }
				static void FreeAction(void* p)
				{
					PostOutParamWrapSite* ptr = (PostOutParamWrapSite*)((BYTE*)p - offset_of(PostOutParamWrapSite, replyPrefix));
					ptr->~PostOutParamWrapSite();
					tcps_Free(ptr);
				}
			};
			PostOutParamWrapSite* opWrapper = tcps_New(PostOutParamWrapSite);
			Set_BaseType_(outfiter, opWrapper->replyPrefix, PostOutParamWrapSite::FreeAction);
		}
		else
		{
			// 指示不需要发送回应数据了
			requireReplyData = false;
		}

		dataTransferred = true; // 指示输入参数数据指针inParamsData被转移
		return TCPS_OK; // 立即返回成功
	}

	// 非posting方法/回调
	TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	{
		CNPAutoLock locker(m_callbackCallLock);
		if(m_owner)
		{
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			err = m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
			if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			{
				if("CallbackCheck_" == streamedCallID)
				{
					// CallbackCheck_()在流式调用端不提供，必须调用C++的映射版本
					err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
				}
				else
				{
					if(!m_owner->IsStreamedCallbackMatched_(streamedCallID.p, streamedCallID.len))
						return TCPS_ERR_CALLBACK_NOT_MATCH;

					{
						iscm_ClientCallType cct = (cit->second.isPosting ? iscm_cct_posting_callback : iscm_cct_callback);
						iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(m_callingOutTIDs, cct);
						err = m_owner->StreamedCallback_(streamedCallID.p, streamedCallID.len, ptrInParams, ptrInParamsLen, replyData, replyLen);
					}
					if(TCPS_OK == err)
					{
						ptrInParams += ptrInParamsLen;
						ptrInParamsLen = 0;
						iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
						replyPrefix->Init();
						outfiter->Push(replyPrefix, sizeof(iscm_RPCReplyPrefix), true, NULL);
						if(replyLen > 0)
						{
							ASSERT(replyData && outfiter);
							outfiter->Push(replyData, replyLen, true, NULL);
						}
						else
							ASSERT(NULL == replyData);
					}
					else
					{
						ASSERT(NULL==replyData && 0==replyLen);
						if(TCPS_ERR_MALFORMED_REQ == err)
						{
							this->OnNetworkMalformed_();
							return TCPS_ERR_MALFORMED_REQ;
						}
					}
				}
			}
		}
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
			err = cit->second.handler(this, NULL, peerCallFlags, ptrInParams, ptrInParamsLen, outfiter);
	}
#ifdef _DEBUG
	if(TCPS_OK == err)
	{
		ASSERT(ptrInParams-(const BYTE*)inParamsData == inParamsDataLen);
		ASSERT(0 == ptrInParamsLen);
	}
#endif
	return err;
}

struct PCC_Deploy_RC::StreamedCall_Task_ : public NPBaseTask
{
	PCC_Deploy_RC& face_;
	tcps_String methodName_;
	tcps_Binary data_;
	explicit StreamedCall_Task_(
				PCC_Deploy_RC& face,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/
				)
		: face_(face)
	{
		methodName_.Assign(methodName, nameLen);
		data_.Assign(data, dataLen);
	}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			SockWriteBuf buf;
			buf.data = data_.Get();
			buf.len = data_.Length();
			face_.StreamedCall_(
						methodName_.Get(), methodName_.Length(),
						&buf, 1,
						NULL, NULL
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_Deploy_RC::StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;
	if(NULL==methodName || 0==nameLen)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if(nameLen < 0)
		nameLen = strlen(methodName);

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	const PCC_Deploy::MethodMatchingFlag& methodMatchingFlag = GetMethodMatchingFlag();
	PCC_Deploy::MethodMatchingFlag::MethodMap::const_iterator itMethod = methodMatchingFlag.mmap_.find(methodName, nameLen);
	if(methodMatchingFlag.mmap_.end() == itMethod)
		return TCPS_ERR_METHOD_NOT_MATCH;
	ASSERT(itMethod->second.pMatchingVar);
	if(!*(itMethod->second.pMatchingVar))
		return TCPS_ERR_METHOD_NOT_MATCH;

	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			if(itMethod->second.isPosting)
			{
				StreamedCall_Task_* task = tcps_NewEx(StreamedCall_Task_, (
								*this,
								methodName, nameLen,
								data, dataLen
								));
				VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
				FetchTaskPool()->Push(task);
			}
			else
				NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = !(itMethod->second.isPosting);
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = (INT32)(12+nameLen);
	CSmartBuf<char, 256> call_id_buf(call_id_len+1);
	strncpy(call_id_buf.Get(), "PCC_Deploy::", 12);
	StrAssign(call_id_buf.Get()+12, methodName, nameLen);
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push(call_id_buf.Get(), call_id_len+1);

	// 填充IN参数到outfiter
	if(dataLen > 0)
		m_dataOutfiter.Push(data, dataLen);

	// 调用RPCCall()
	if(peerCallFlags.requireReply) // method
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_RPCReplyPrefix replyPrefix;
		err = m_rpcRequester->RecvD(&replyPrefix, sizeof(replyPrefix));
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}

		INT_PTR leftReplyLen = replyBytes - sizeof(replyPrefix);
		ASSERT(leftReplyLen >= 0);
		if(leftReplyLen > 0)
		{
			ASSERT(replyData && replyLen);
			tcps_Binary replied_data;
			if(!replied_data.Resize(leftReplyLen))
			{
				this->OnNetworkMalformed_();
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			err = m_rpcRequester->RecvD(replied_data.Get(), (int)leftReplyLen);
			if(TCPS_OK != err)
			{
				// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
				return err;
			}
			if(NULL==replyData || NULL==replyLen)
			{
				ASSERT(false);
				return TCPS_ERR_INVALID_PARAM;
			}
			INT32 bytes = 0;
			*replyData = replied_data.Drop(&bytes);
			*replyLen = bytes;
		}
	}
	else // posting method
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(0 != m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::Login(
				IN const char* ticket_wrap, IN INT32 ticket_wrap_len /*= -1*/
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_Login)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 17;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::Login", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String ticket
	if(NULL == ticket_wrap)
	{
		if(ticket_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		ticket_wrap = "";
		ticket_wrap_len = 0;
	}
	if(ticket_wrap_len < 0)
	{
		ticket_wrap_len = (INT32)strlen(ticket_wrap);
		Put_BaseType_(&m_dataOutfiter, ticket_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)ticket_wrap, ticket_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, ticket_wrap, ticket_wrap_len);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::Login() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::Logout(
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_Logout)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 18;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::Logout", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::Logout() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::CreateTrunk(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_CreateTrunk)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 23;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::CreateTrunk", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::CreateTrunk() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::RemoveTrunk(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_RemoveTrunk)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 23;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::RemoveTrunk", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::RemoveTrunk() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::ListTrunk(
				OUT tcps_Array<tcps_String>& trunks_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_ListTrunk)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 21;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::ListTrunk", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<tcps_String> trunks
		PICK_BASETYPE_Q(iscm_replied_picker, array_len);
		trunks_wrap.Resize(array_len);
		for(int idx2=0; idx2<trunks_wrap.Length(); ++idx2)
		{
			tcps_String& ref2 = trunks_wrap[idx2];
			PICK_STRING_Q(iscm_replied_picker, ref2);
		}
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::ListTrunk() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::AddAuthCenter(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN const PCC_Tag& authTag_wrap,
				IN const tcps_Array<PCC_ModuleFile>& files_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_AddAuthCenter)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 25;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::AddAuthCenter", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// IN PCC_Tag authTag
		Put_String_(&m_dataOutfiter, authTag_wrap.name.Get(), authTag_wrap.name.LenRef());
		Put_BaseType_(&m_dataOutfiter, authTag_wrap.version);

	// IN tcps_Array<PCC_ModuleFile> files
	Put_BaseType_(&m_dataOutfiter, files_wrap.LenRef());
	for(int idx1=0; idx1<files_wrap.Length(); ++idx1)
	{
		const PCC_ModuleFile& ref1 = files_wrap[idx1];
			Put_String_(&m_dataOutfiter, ref1.name.Get(), ref1.name.LenRef());
			Put_Binary_(&m_dataOutfiter, ref1.data.Get(), ref1.data.LenRef());
			Put_BaseType_(&m_dataOutfiter, ref1.entry);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::AddAuthCenter() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::RemoveAuthCenter(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN const PCC_Tag& authTag_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_RemoveAuthCenter)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 28;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::RemoveAuthCenter", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// IN PCC_Tag authTag
		Put_String_(&m_dataOutfiter, authTag_wrap.name.Get(), authTag_wrap.name.LenRef());
		Put_BaseType_(&m_dataOutfiter, authTag_wrap.version);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::RemoveAuthCenter() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::ListAuthCenter(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				OUT tcps_Array<PCC_Tag>& authTags_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_ListAuthCenter)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 26;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::ListAuthCenter", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<PCC_Tag> authTags
		PICK_BASETYPE_Q(iscm_replied_picker, array_len);
		authTags_wrap.Resize(array_len);
		for(int idx2=0; idx2<authTags_wrap.Length(); ++idx2)
		{
			PCC_Tag& ref2 = authTags_wrap[idx2];
				PICK_STRING_Q(iscm_replied_picker, ref2.name);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.version);
		}
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::ListAuthCenter() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::FindAuthCenter(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN const PCC_Tag& authTag_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_FindAuthCenter)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 26;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::FindAuthCenter", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// IN PCC_Tag authTag
		Put_String_(&m_dataOutfiter, authTag_wrap.name.Get(), authTag_wrap.name.LenRef());
		Put_BaseType_(&m_dataOutfiter, authTag_wrap.version);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::FindAuthCenter() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::AddModule(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN const PCC_ModuleProperty& moduleProperty_wrap,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles_wrap,
				OUT INT64& moduleKey_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_AddModule)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 21;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::AddModule", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// IN PCC_ModuleProperty moduleProperty
			Put_String_(&m_dataOutfiter, moduleProperty_wrap.moduleTag.name.Get(), moduleProperty_wrap.moduleTag.name.LenRef());
			Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.moduleTag.version);
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.modulePattern);
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.moduleFileType);
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.moduleType);
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.moduleLatency);
		Put_String_(&m_dataOutfiter, moduleProperty_wrap.description.Get(), moduleProperty_wrap.description.LenRef());
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.modulePlatform);
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.addTime);
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.moduleSize);

	// IN tcps_Array<PCC_ModuleFile> moudleFiles
	Put_BaseType_(&m_dataOutfiter, moudleFiles_wrap.LenRef());
	for(int idx1=0; idx1<moudleFiles_wrap.Length(); ++idx1)
	{
		const PCC_ModuleFile& ref1 = moudleFiles_wrap[idx1];
			Put_String_(&m_dataOutfiter, ref1.name.Get(), ref1.name.LenRef());
			Put_Binary_(&m_dataOutfiter, ref1.data.Get(), ref1.data.LenRef());
			Put_BaseType_(&m_dataOutfiter, ref1.entry);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT INT64 moduleKey
		PICK_BASETYPE_Q(iscm_replied_picker, moduleKey_wrap);
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::AddModule() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::AddModuleFile(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN INT64 moduleKey_wrap,
				IN PCC_ModuleFileType fileType_wrap,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_AddModuleFile)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 25;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::AddModuleFile", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// IN INT64 moduleKey
	Put_BaseType_(&m_dataOutfiter, moduleKey_wrap);

	// IN PCC_ModuleFileType fileType
	Put_BaseType_(&m_dataOutfiter, fileType_wrap);

	// IN tcps_Array<PCC_ModuleFile> moduleFiles
	Put_BaseType_(&m_dataOutfiter, moduleFiles_wrap.LenRef());
	for(int idx1=0; idx1<moduleFiles_wrap.Length(); ++idx1)
	{
		const PCC_ModuleFile& ref1 = moduleFiles_wrap[idx1];
			Put_String_(&m_dataOutfiter, ref1.name.Get(), ref1.name.LenRef());
			Put_Binary_(&m_dataOutfiter, ref1.data.Get(), ref1.data.LenRef());
			Put_BaseType_(&m_dataOutfiter, ref1.entry);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::AddModuleFile() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::RemoveModule(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN INT64 moduleKey_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_RemoveModule)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 24;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::RemoveModule", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// IN INT64 moduleKey
	Put_BaseType_(&m_dataOutfiter, moduleKey_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::RemoveModule() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::RemoveModuleFiles(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN INT64 moduleKey_wrap,
				IN INT32 fileType_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_RemoveModuleFiles)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 29;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::RemoveModuleFiles", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// IN INT64 moduleKey
	Put_BaseType_(&m_dataOutfiter, moduleKey_wrap);

	// IN INT32 fileType
	Put_BaseType_(&m_dataOutfiter, fileType_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::RemoveModuleFiles() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::ListModules(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_ListModules)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 23;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::ListModules", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String trunk
	if(NULL == trunk_wrap)
	{
		if(trunk_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		trunk_wrap = "";
		trunk_wrap_len = 0;
	}
	if(trunk_wrap_len < 0)
	{
		trunk_wrap_len = (INT32)strlen(trunk_wrap);
		Put_BaseType_(&m_dataOutfiter, trunk_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)trunk_wrap, trunk_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, trunk_wrap, trunk_wrap_len);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<PCC_ModulePropWithKey> modulesInfo
		PICK_BASETYPE_Q(iscm_replied_picker, array_len);
		modulesInfo_wrap.Resize(array_len);
		for(int idx2=0; idx2<modulesInfo_wrap.Length(); ++idx2)
		{
			PCC_ModulePropWithKey& ref2 = modulesInfo_wrap[idx2];
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.key);
						PICK_STRING_Q(iscm_replied_picker, ref2.prop.moduleTag.name);
						PICK_BASETYPE_Q(iscm_replied_picker, ref2.prop.moduleTag.version);
					PICK_BASETYPE_Q(iscm_replied_picker, ref2.prop.modulePattern);
					PICK_BASETYPE_Q(iscm_replied_picker, ref2.prop.moduleFileType);
					PICK_BASETYPE_Q(iscm_replied_picker, ref2.prop.moduleType);
					PICK_BASETYPE_Q(iscm_replied_picker, ref2.prop.moduleLatency);
					PICK_STRING_Q(iscm_replied_picker, ref2.prop.description);
					PICK_BASETYPE_Q(iscm_replied_picker, ref2.prop.modulePlatform);
					PICK_BASETYPE_Q(iscm_replied_picker, ref2.prop.addTime);
					PICK_BASETYPE_Q(iscm_replied_picker, ref2.prop.moduleSize);
		}
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::ListModules() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::AddModel(
				IN const PCC_ModelProperty& moduleProperty_wrap,
				IN const tcps_Array<PCC_ModelFile>& modelFiles_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_AddModel)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 20;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::AddModel", call_id_len+1);

	// 填充IN参数到outfiter

	// IN PCC_ModelProperty moduleProperty
			Put_String_(&m_dataOutfiter, moduleProperty_wrap.modelTag.name.Get(), moduleProperty_wrap.modelTag.name.LenRef());
			Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.modelTag.version);
		Put_String_(&m_dataOutfiter, moduleProperty_wrap.description.Get(), moduleProperty_wrap.description.LenRef());
		Put_BaseType_(&m_dataOutfiter, moduleProperty_wrap.addTime);

	// IN tcps_Array<PCC_ModelFile> modelFiles
	Put_BaseType_(&m_dataOutfiter, modelFiles_wrap.LenRef());
	for(int idx1=0; idx1<modelFiles_wrap.Length(); ++idx1)
	{
		const PCC_ModelFile& ref1 = modelFiles_wrap[idx1];
			Put_String_(&m_dataOutfiter, ref1.name.Get(), ref1.name.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::AddModel() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::DelModel(
				IN INT64 modelKey_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_DelModel)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 20;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::DelModel", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT64 modelKey
	Put_BaseType_(&m_dataOutfiter, modelKey_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_Deploy::DelModel() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::Wrap_SetRedirect_(
				IN PCC_Deploy_RC* thisObj /*= NULL*/,
				IN PCC_Deploy* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN IPP redirectIPP
	IN IPP redirectIPP_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, redirectIPP_wrap);

	// IN tcps_Binary redirectParam
	IN tcps_Binary redirectParam_wrap;
	GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, redirectParam_wrap);

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Deploy::SetRedirect_() posting_callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_posting_callback);
			errTcps = thisObj->SetRedirect_(
				redirectIPP_wrap,
				redirectParam_wrap
				);
		}
		else
		{
			(void)faceObj;
			ASSERT(false);
			errTcps = TCPS_ERR_INTERNAL_BUG;
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

struct PCC_Deploy_RC::SetTimeout__Task_ : public NPBaseTask
{
	PCC_Deploy_RC& face_;
	IN INT32 recvTimeout_wrap_;
	IN INT32 sendTimeout_wrap_;
	explicit SetTimeout__Task_(
				PCC_Deploy_RC& face,
				IN INT32 recvTimeout_wrap,
				IN INT32 sendTimeout_wrap
				)
		: face_(face)
		, recvTimeout_wrap_(recvTimeout_wrap)
		, sendTimeout_wrap_(sendTimeout_wrap)
		{}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			face_.SetTimeout_(
						recvTimeout_wrap_,
						sendTimeout_wrap_
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_Deploy_RC::SetTimeout_(
				IN INT32 recvTimeout_wrap,
				IN INT32 sendTimeout_wrap
				) posting_method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			SetTimeout__Task_* task = tcps_NewEx(SetTimeout__Task_, (
							*this,
							recvTimeout_wrap,
							sendTimeout_wrap
							));
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
			FetchTaskPool()->Push(task);
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_SetTimeout_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 23;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::SetTimeout_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT32 recvTimeout
	Put_BaseType_(&m_dataOutfiter, recvTimeout_wrap);

	// IN INT32 sendTimeout
	Put_BaseType_(&m_dataOutfiter, sendTimeout_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
		if(TCPS_OK != err)
			return err;
	}
	return TCPS_OK;
}

struct PCC_Deploy_RC::SetSessionBufferSize__Task_ : public NPBaseTask
{
	PCC_Deploy_RC& face_;
	IN INT32 recvBufBytes_wrap_;
	IN INT32 sendBufBytes_wrap_;
	explicit SetSessionBufferSize__Task_(
				PCC_Deploy_RC& face,
				IN INT32 recvBufBytes_wrap,
				IN INT32 sendBufBytes_wrap
				)
		: face_(face)
		, recvBufBytes_wrap_(recvBufBytes_wrap)
		, sendBufBytes_wrap_(sendBufBytes_wrap)
		{}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			face_.SetSessionBufferSize_(
						recvBufBytes_wrap_,
						sendBufBytes_wrap_
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_Deploy_RC::SetSessionBufferSize_(
				IN INT32 recvBufBytes_wrap,
				IN INT32 sendBufBytes_wrap
				) posting_method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			SetSessionBufferSize__Task_* task = tcps_NewEx(SetSessionBufferSize__Task_, (
							*this,
							recvBufBytes_wrap,
							sendBufBytes_wrap
							));
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
			FetchTaskPool()->Push(task);
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_SetSessionBufferSize_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 33;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::SetSessionBufferSize_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT32 recvBufBytes
	Put_BaseType_(&m_dataOutfiter, recvBufBytes_wrap);

	// IN INT32 sendBufBytes
	Put_BaseType_(&m_dataOutfiter, sendBufBytes_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
		if(TCPS_OK != err)
			return err;
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::MethodCheck_(
				IN const tcps_Array<tcps_String>& methods_wrap,
				IN const tcps_Array<tcps_String>& methodTypeInfos_wrap,
				OUT tcps_Array<BOOL>& matchingFlags_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 24;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_Deploy::MethodCheck_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_Array<tcps_String> methods
	Put_BaseType_(&m_dataOutfiter, methods_wrap.LenRef());
	for(int idx1=0; idx1<methods_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = methods_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// IN tcps_Array<tcps_String> methodTypeInfos
	Put_BaseType_(&m_dataOutfiter, methodTypeInfos_wrap.LenRef());
	for(int idx1=0; idx1<methodTypeInfos_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = methodTypeInfos_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_IRequester* iscm_replied_picker = m_rpcRequester;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<BOOL> matchingFlags
		PICK_PODARRAY_(iscm_replied_picker, matchingFlags_wrap);
	}
	return TCPS_OK;
}

TCPSError PCC_Deploy_RC::Wrap_CallbackCheck_(
				IN PCC_Deploy_RC* thisObj /*= NULL*/,
				IN PCC_Deploy* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_Array<tcps_String> callbacks
	IN tcps_Array<tcps_String> callbacks_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	callbacks_wrap.Resize(array_len);
	for(int idx1=0; idx1<callbacks_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = callbacks_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	// IN tcps_Array<tcps_String> callbackTypeInfos
	IN tcps_Array<tcps_String> callbackTypeInfos_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	callbackTypeInfos_wrap.Resize(array_len);
	for(int idx1=0; idx1<callbackTypeInfos_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = callbackTypeInfos_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_Deploy::CallbackCheck_() callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<BOOL> matchingFlags;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_callback);
			errTcps = thisObj->CallbackCheck_(
				callbacks_wrap,
				callbackTypeInfos_wrap,
				opWrapper->matchingFlags
				);
		}
		else
		{
			(void)faceObj;
			ASSERT(false);
			errTcps = TCPS_ERR_INTERNAL_BUG;
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<BOOL> matchingFlags
	OUT const tcps_Array<BOOL>& matchingFlags_wrap = opWrapper->matchingFlags;
	Set_PODArray_(outfiter, matchingFlags_wrap);

	return TCPS_OK;
}

PCC_Deploy::PCC_Deploy(BOOL initNetworkSingletons /*= true*/)
	: m_faceR(NULL), m_faceL(NULL), m_callSiteL(NULL)
	, m_closingTID(INVALID_OSTHREADID)
	, m_connectTimeout(INFINITE), m_recvTimeout(INFINITE), m_sendTimeout(INFINITE)
	, m_streamedCallbackMap_IsInited(false)
{
	m_base_v_tab_ptr = m_derived_v_tab_ptr = *(LPVOID*)this;
	if(initNetworkSingletons)
		iscm_InitClientSingletons(true, true);
	else
		iscm_InitClientSingletons(false, false);
	PCC_Deploy_RC::GetCallbackMap_();
}

PCC_Deploy::~PCC_Deploy()
{
	BOOL isNotDerived = (m_base_v_tab_ptr == m_derived_v_tab_ptr);
	NPR_ASSERT_EX(isNotDerived || (NULL==m_faceR && NULL==m_faceL), "请在最终派生类的析构函数的最后调用一次DestroyRequester()");
	DestroyRequester();
	if(m_callSiteL)
		tcps_Delete(m_callSiteL);
}

void PCC_Deploy::DestroyRequester_(
				IN BOOL byLocalPeer
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);

	CAutoObj<AutoFlag<OSThreadID> > autoClosingTID;
	if(!byLocalPeer)
		ConstructAutoObj(AutoFlag<OSThreadID>, autoClosingTID, (m_closingTID, OSThreadSelf()));

	if(m_faceR)
	{
		tcps_Delete(m_faceR);
		m_faceR = NULL;
	}
	else if(m_faceL)
	{
		if(INVALID_OSTHREADID==m_closingTID || OSThreadSelf()!=m_closingTID)
			this->OnPeerBroken();
		this->OnClose();
		m_faceL->DeleteThis();
		m_faceL = NULL;
		if(m_callSiteL)
			m_callSiteL->Reset();
		m_localServeIPP = INVALID_IPP;
	}
}

void PCC_Deploy::DestroyRequester()
{
	DestroyRequester_(false);
}

TCPSError PCC_Deploy::SetServeIPP_(
				IN BOOL byLocalPeer,
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	CNPAutoLock locker(m_lock);
	m_derived_v_tab_ptr = *(LPVOID*)this;
	ASSERT(NULL==m_faceR || NULL==m_faceL);

	if(m_localMakingFlag.making)
	{
		if(serveIPP.IsValid())
		{
			ASSERT(false);
			return TCPS_ERR_EXTERNAL_BUG;
		}
		m_localMakingFlag.failed = true;
		return TCPS_OK;
	}

	if(m_faceL && m_localServeIPP==serveIPP)
		return TCPS_OK;

	if(serveIPP.IsValid() && iscm_IsRegisteredServe(serveIPP))
	{
		DestroyRequester_(byLocalPeer);

		ASSERT(!m_localMakingFlag.making && !m_localMakingFlag.failed);
		AutoFlag<BOOL> autoFlag(m_localMakingFlag.making, true);
		FinalAssign<BOOL> finalAssign(m_localMakingFlag.failed, false);

		union
		{
		PCC_CenterSessionMaker* sessionMaker;
		void* dummyUnionPtr;
		};
		sessionMaker = NULL;
		FNMakeLocalSession_PCC_Deploy fnMake =
					(FNMakeLocalSession_PCC_Deploy)iscm_GetRegisteredFunction(
						serveIPP,
						"MakeLocalSession_PCC_Deploy",
						&dummyUnionPtr
						);
		if(NULL == fnMake)
			return TCPS_ERR_INVALID_INTERFACE;

		ASSERT(sessionMaker);
		TCPSError err = fnMake(clientID_IPP, *sessionMaker, m_faceL, this);
		if(TCPS_OK==err && m_localMakingFlag.failed)
		{
			ASSERT(m_faceL);
			m_faceL->DeleteThis();
			m_faceL = NULL;
			err = TCPS_ERR_CONNECT_FAILED;
		}
		if(TCPS_OK != err)
		{
			ASSERT(NULL == m_faceL);
			return err;
		}
		if(m_callSiteL)
			m_callSiteL->needUpdateFlags = true;

		ASSERT(m_faceL);
		err = this->OnConnected();
		if(TCPS_OK==err && m_localMakingFlag.failed)
			err = TCPS_ERR_CONNECT_FAILED;
		if(TCPS_OK != err)
		{
			if(INVALID_OSTHREADID==m_closingTID || OSThreadSelf()!=m_closingTID)
				this->OnPeerBroken();
			this->OnClose();
			m_faceL->DeleteThis();
			m_faceL = NULL;
			return err;
		}
		m_localServeIPP = serveIPP;
		return TCPS_OK;
	}

	if(m_faceL)
		DestroyRequester_(byLocalPeer);
	if(NULL == m_faceR)
	{
		if(!serveIPP.IsValid())
			return TCPS_OK;
		m_faceR = tcps_NewEx(PCC_Deploy_RC, (this));
	}

	if(INFINITE!=m_connectTimeout || INFINITE!=m_recvTimeout || INFINITE!=m_sendTimeout)
		m_faceR->SetTimeout(m_connectTimeout, m_recvTimeout, m_sendTimeout);
	if(!m_sockRecvSendBufParam.IsDefault())
		m_faceR->SetSessionBufferSize(m_sockRecvSendBufParam.recvBufBytes_, m_sockRecvSendBufParam.sendBufBytes_);
	if(!m_postingPendingParam.IsDefault())
		m_faceR->SetPostingPendingParameters(m_postingPendingParam.maxPendingBytes_, m_postingPendingParam.maxPendings_);
	return m_faceR->SetServeIPP(
						serveIPP,
						sessionFlags,
						clientID_IPP,
						secondaryServeIPP,
						tertiaryServeIPP,
						reconnectIntervalMSELs
						);
}

TCPSError PCC_Deploy::SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	CNPAutoLock locker(m_lock);
	AutoFlag<OSThreadID> autoClosingTID(m_closingTID, OSThreadSelf());
	return SetServeIPP_(false, serveIPP, sessionFlags, clientID_IPP, secondaryServeIPP, tertiaryServeIPP, reconnectIntervalMSELs);
}

IPP PCC_Deploy::GetServeIPP() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->GetServeIPP();
	else if(m_faceL)
		return m_localServeIPP;
	return INVALID_IPP;
}

IPP PCC_Deploy::GetServingIPP() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->GetServingIPP();
	else if(m_faceL)
		return m_localServeIPP;
	return INVALID_IPP;
}

BOOL PCC_Deploy::IsConnected() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->IsConnected();
	else if(m_faceL)
		return true;
	return false;
}

void PCC_Deploy::SetKeeping(
				IN BOOL keeping
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetKeeping(keeping);
}

BOOL PCC_Deploy::IsKeeping() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->IsKeeping();
	return false;
}

BOOL PCC_Deploy::IsLocalPeer() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	return (NULL != m_faceL);
}

void PCC_Deploy::PrepareDisconnect()
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->PrepareDisconnect();
}

void PCC_Deploy::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	m_connectTimeout = connectTimeout;
	m_recvTimeout = recvTimeout;
	m_sendTimeout = sendTimeout;
}

void PCC_Deploy::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		m_faceR->GetTimeout(connectTimeout, recvTimeout, sendTimeout);
		return;
	}
	if(connectTimeout)
		*connectTimeout = m_connectTimeout;
	if(recvTimeout)
		*recvTimeout = m_recvTimeout;
	if(sendTimeout)
		*sendTimeout = m_sendTimeout;
}

void PCC_Deploy::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	m_sockRecvSendBufParam.Set(recvBufBytes, sendBufBytes);
}

void PCC_Deploy::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_sockRecvSendBufParam.Get(recvBufBytes, sendBufBytes);
}

void PCC_Deploy::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetPostingPendingParameters(maxPendingBytes, maxPendings);
	m_postingPendingParam.Set(maxPendingBytes, maxPendings);
}

void PCC_Deploy::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_postingPendingParam.Get(maxPendingBytes, maxPendings);
}

void PCC_Deploy::SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR && 0!=m_faceR->m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().SetBufferingParam(m_faceR->m_postingProxy.callerKey_, maxSendingBytes, maxSendings);
	m_postingSendParam.Set(maxSendingBytes, maxSendings);
}

void PCC_Deploy::GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_postingSendParam.Get(maxSendingBytes, maxSendings);
}

TCPSError PCC_Deploy::CleanPostingSendingQueue()
{
	if(NULL==m_faceR || 0==m_faceR->m_postingProxy.callerKey_)
		return TCPS_ERR_CALL_WAS_IGNORED;
	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(&m_faceR->m_postingProxy.callerKey_, 1);
}

TCPSError PCC_Deploy::CleanPostingSendingQueue(
				IN const PPCC_Deploy_* clients,
				IN INT_PTR clientsCount
				)
{
	tcps_SmartArray<PPCC_Deploy_, 256> clients_ar_;
	for(INT_PTR i=0; i<clientsCount; ++i)
	{
		if(NULL == clients[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(NULL==clients[i]->m_faceR || 0==clients[i]->m_faceR->m_postingProxy.callerKey_)
			continue;
		clients_ar_.push_back(clients[i]);
	}
	if(0 == clients_ar_.size())
		return TCPS_OK;

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> callerKey_ar_;
	callerKey_ar_.resize(clients_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)clients_ar_.size(); ++i)
		callerKey_ar_[i] = clients_ar_[i]->m_faceR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(callerKey_ar_.Get(), callerKey_ar_.size());
}

const PCC_Deploy::MethodMatchingFlag& PCC_Deploy::GetMethodMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->GetMethodMatchingFlag(err);
	}
	else if(m_faceL)
	{
		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		if(m_callSiteL->needUpdateFlags)
		{
			InitializeAllCallsTypeInfo_();
			m_callSiteL->matchingFlags.matching_Login = (NULL != m_faceL->FindMethod_("Login", 5, s_PCC_Deploy_Login_TypeInfo_, s_PCC_Deploy_Login_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_Logout = (NULL != m_faceL->FindMethod_("Logout", 6, s_PCC_Deploy_Logout_TypeInfo_, s_PCC_Deploy_Logout_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_CreateTrunk = (NULL != m_faceL->FindMethod_("CreateTrunk", 11, s_PCC_Deploy_CreateTrunk_TypeInfo_, s_PCC_Deploy_CreateTrunk_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_RemoveTrunk = (NULL != m_faceL->FindMethod_("RemoveTrunk", 11, s_PCC_Deploy_RemoveTrunk_TypeInfo_, s_PCC_Deploy_RemoveTrunk_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_ListTrunk = (NULL != m_faceL->FindMethod_("ListTrunk", 9, s_PCC_Deploy_ListTrunk_TypeInfo_, s_PCC_Deploy_ListTrunk_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_AddAuthCenter = (NULL != m_faceL->FindMethod_("AddAuthCenter", 13, s_PCC_Deploy_AddAuthCenter_TypeInfo_, s_PCC_Deploy_AddAuthCenter_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_RemoveAuthCenter = (NULL != m_faceL->FindMethod_("RemoveAuthCenter", 16, s_PCC_Deploy_RemoveAuthCenter_TypeInfo_, s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_ListAuthCenter = (NULL != m_faceL->FindMethod_("ListAuthCenter", 14, s_PCC_Deploy_ListAuthCenter_TypeInfo_, s_PCC_Deploy_ListAuthCenter_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_FindAuthCenter = (NULL != m_faceL->FindMethod_("FindAuthCenter", 14, s_PCC_Deploy_FindAuthCenter_TypeInfo_, s_PCC_Deploy_FindAuthCenter_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_AddModule = (NULL != m_faceL->FindMethod_("AddModule", 9, s_PCC_Deploy_AddModule_TypeInfo_, s_PCC_Deploy_AddModule_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_AddModuleFile = (NULL != m_faceL->FindMethod_("AddModuleFile", 13, s_PCC_Deploy_AddModuleFile_TypeInfo_, s_PCC_Deploy_AddModuleFile_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_RemoveModule = (NULL != m_faceL->FindMethod_("RemoveModule", 12, s_PCC_Deploy_RemoveModule_TypeInfo_, s_PCC_Deploy_RemoveModule_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_RemoveModuleFiles = (NULL != m_faceL->FindMethod_("RemoveModuleFiles", 17, s_PCC_Deploy_RemoveModuleFiles_TypeInfo_, s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_ListModules = (NULL != m_faceL->FindMethod_("ListModules", 11, s_PCC_Deploy_ListModules_TypeInfo_, s_PCC_Deploy_ListModules_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_AddModel = (NULL != m_faceL->FindMethod_("AddModel", 8, s_PCC_Deploy_AddModel_TypeInfo_, s_PCC_Deploy_AddModel_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_DelModel = (NULL != m_faceL->FindMethod_("DelModel", 8, s_PCC_Deploy_DelModel_TypeInfo_, s_PCC_Deploy_DelModel_TypeInfo_len_));
			m_callSiteL->needUpdateFlags = false;
		}
		if(err)
			*err = TCPS_OK;
		return m_callSiteL->matchingFlags;
	}

	static MethodMatchingFlag const defaultFlags;
	if(err)
		*err = TCPS_ERR_NEED_SERVE_IPP;
	return defaultFlags;
}

TCPSError PCC_Deploy::GetStreamedMethodTypeInfo_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo,
				OUT INT_PTR& infoLen
				) const
{
	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<16> > MethodMap_;
	static MethodMap_* s_mMap = NULL;
	if(NULL == s_mMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_mMap)
		{
			static MethodMap_ s_mMapObj;
			MethodMap_& mMap = s_mMapObj;
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Login"), CPtrStrA(s_PCC_Deploy_Login_TypeInfo_, s_PCC_Deploy_Login_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Logout"), CPtrStrA(s_PCC_Deploy_Logout_TypeInfo_, s_PCC_Deploy_Logout_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("CreateTrunk"), CPtrStrA(s_PCC_Deploy_CreateTrunk_TypeInfo_, s_PCC_Deploy_CreateTrunk_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveTrunk"), CPtrStrA(s_PCC_Deploy_RemoveTrunk_TypeInfo_, s_PCC_Deploy_RemoveTrunk_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListTrunk"), CPtrStrA(s_PCC_Deploy_ListTrunk_TypeInfo_, s_PCC_Deploy_ListTrunk_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddAuthCenter"), CPtrStrA(s_PCC_Deploy_AddAuthCenter_TypeInfo_, s_PCC_Deploy_AddAuthCenter_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveAuthCenter"), CPtrStrA(s_PCC_Deploy_RemoveAuthCenter_TypeInfo_, s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListAuthCenter"), CPtrStrA(s_PCC_Deploy_ListAuthCenter_TypeInfo_, s_PCC_Deploy_ListAuthCenter_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("FindAuthCenter"), CPtrStrA(s_PCC_Deploy_FindAuthCenter_TypeInfo_, s_PCC_Deploy_FindAuthCenter_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModule"), CPtrStrA(s_PCC_Deploy_AddModule_TypeInfo_, s_PCC_Deploy_AddModule_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModuleFile"), CPtrStrA(s_PCC_Deploy_AddModuleFile_TypeInfo_, s_PCC_Deploy_AddModuleFile_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveModule"), CPtrStrA(s_PCC_Deploy_RemoveModule_TypeInfo_, s_PCC_Deploy_RemoveModule_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("RemoveModuleFiles"), CPtrStrA(s_PCC_Deploy_RemoveModuleFiles_TypeInfo_, s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListModules"), CPtrStrA(s_PCC_Deploy_ListModules_TypeInfo_, s_PCC_Deploy_ListModules_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("AddModel"), CPtrStrA(s_PCC_Deploy_AddModel_TypeInfo_, s_PCC_Deploy_AddModel_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("DelModel"), CPtrStrA(s_PCC_Deploy_DelModel_TypeInfo_, s_PCC_Deploy_DelModel_TypeInfo_len_))).second);
			s_mMap = &mMap;
		}
	}
	MethodMap_::iterator it = s_mMap->find(methodName, nameLen);
	if(it == s_mMap->end())
		return TCPS_ERR_METHOD_NOT_MATCH;
	infoLen = it->second.GetLength();
	typeInfo = (char*)tcps_Alloc(infoLen+1);
	StrAssign(typeInfo, it->second);
	return TCPS_OK;
}

TCPSError PCC_Deploy::StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	if(m_faceR)
	{
		return m_faceR->StreamedCall_(
					methodName, nameLen,
					data, dataLen,
					replyData, replyLen
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			return m_streamedCallSite.func(
						m_streamedCallSite.serverObj, m_streamedCallSite.sessionObj,
						"PCC_Deploy", methodName,
						data, dataLen,
						replyData, replyLen
						);
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnOnStreamedCall_L_;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("OnStreamedCall_L_", -1, NULL, 0);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_OnStreamedCall_L_)methodFuncL)(
					m_faceL,
					methodName, nameLen,
					data, dataLen,
					replyData, replyLen
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

BOOL PCC_Deploy::IsStreamedCallbackMatched_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/
				)
{
	if(m_streamedCallbackMap_IsInited)
	{
		StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
		if(it == m_streamedCallbackMap.end())
			return false;
		return it->second;
	}

	CNPAutoLock locker(m_lock);

	if(m_streamedCallbackMap_IsInited)
	{
		StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
		if(it == m_streamedCallbackMap.end())
			return false;
		return it->second;
	}

	ASSERT(0 == m_streamedCallbackMap.size());

	InitializeAllCallsTypeInfo_();
	BOOL matched;
	TCPSError err;
	char* typeInfo;
	INT_PTR infoLen;
	(void)matched; (void)err; (void)typeInfo; (void)infoLen;

	m_streamedCallbackMap_IsInited = true;
	StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
	if(it == m_streamedCallbackMap.end())
		return false;
	return it->second;
}

TCPSError PCC_Deploy::Login(
				IN const char* ticket_wrap, IN INT32 ticket_wrap_len /*= -1*/
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->Login(
					ticket_wrap, ticket_wrap_len
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String ticket_tmp_wrap;
			ticket_tmp_wrap.Attach(xat_bind, (char*)ticket_wrap, ticket_wrap_len);
			inParamsLen += iscm_GetStreamedSize(ticket_tmp_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, ticket_tmp_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"Login",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnLogin;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("Login", 5, s_PCC_Deploy_Login_TypeInfo_, s_PCC_Deploy_Login_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_Login)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)ticket_wrap, ticket_wrap_len)
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::Logout(
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->Logout(
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"Logout",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnLogout;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("Logout", 6, s_PCC_Deploy_Logout_TypeInfo_, s_PCC_Deploy_Logout_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_Logout)methodFuncL)(
					m_faceL
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::CreateTrunk(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->CreateTrunk(
					trunk_wrap, trunk_wrap_len
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"CreateTrunk",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnCreateTrunk;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("CreateTrunk", 11, s_PCC_Deploy_CreateTrunk_TypeInfo_, s_PCC_Deploy_CreateTrunk_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_CreateTrunk)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len)
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::RemoveTrunk(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->RemoveTrunk(
					trunk_wrap, trunk_wrap_len
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"RemoveTrunk",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnRemoveTrunk;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("RemoveTrunk", 11, s_PCC_Deploy_RemoveTrunk_TypeInfo_, s_PCC_Deploy_RemoveTrunk_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_RemoveTrunk)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len)
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::ListTrunk(
				OUT tcps_Array<tcps_String>& trunks_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->ListTrunk(
					trunks_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"ListTrunk",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(trunks_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnListTrunk;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("ListTrunk", 9, s_PCC_Deploy_ListTrunk_TypeInfo_, s_PCC_Deploy_ListTrunk_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_ListTrunk)methodFuncL)(
					m_faceL,
					trunks_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::AddAuthCenter(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN const PCC_Tag& authTag_wrap,
				IN const tcps_Array<PCC_ModuleFile>& files_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->AddAuthCenter(
					trunk_wrap, trunk_wrap_len,
					authTag_wrap,
					files_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);
			inParamsLen += iscm_GetStreamedSize(authTag_wrap);
			inParamsLen += iscm_GetStreamedSize(files_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, authTag_wrap);
			iscm_StreamedStore(pInParamsBuf, files_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"AddAuthCenter",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnAddAuthCenter;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("AddAuthCenter", 13, s_PCC_Deploy_AddAuthCenter_TypeInfo_, s_PCC_Deploy_AddAuthCenter_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_AddAuthCenter)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					authTag_wrap,
					files_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::RemoveAuthCenter(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN const PCC_Tag& authTag_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->RemoveAuthCenter(
					trunk_wrap, trunk_wrap_len,
					authTag_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);
			inParamsLen += iscm_GetStreamedSize(authTag_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, authTag_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"RemoveAuthCenter",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnRemoveAuthCenter;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("RemoveAuthCenter", 16, s_PCC_Deploy_RemoveAuthCenter_TypeInfo_, s_PCC_Deploy_RemoveAuthCenter_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_RemoveAuthCenter)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					authTag_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::ListAuthCenter(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				OUT tcps_Array<PCC_Tag>& authTags_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->ListAuthCenter(
					trunk_wrap, trunk_wrap_len,
					authTags_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"ListAuthCenter",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(authTags_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnListAuthCenter;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("ListAuthCenter", 14, s_PCC_Deploy_ListAuthCenter_TypeInfo_, s_PCC_Deploy_ListAuthCenter_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_ListAuthCenter)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					authTags_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::FindAuthCenter(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN const PCC_Tag& authTag_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->FindAuthCenter(
					trunk_wrap, trunk_wrap_len,
					authTag_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);
			inParamsLen += iscm_GetStreamedSize(authTag_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, authTag_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"FindAuthCenter",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnFindAuthCenter;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("FindAuthCenter", 14, s_PCC_Deploy_FindAuthCenter_TypeInfo_, s_PCC_Deploy_FindAuthCenter_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_FindAuthCenter)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					authTag_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::AddModule(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN const PCC_ModuleProperty& moduleProperty_wrap,
				IN const tcps_Array<PCC_ModuleFile>& moudleFiles_wrap,
				OUT INT64& moduleKey_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->AddModule(
					trunk_wrap, trunk_wrap_len,
					moduleProperty_wrap,
					moudleFiles_wrap,
					moduleKey_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);
			inParamsLen += iscm_GetStreamedSize(moduleProperty_wrap);
			inParamsLen += iscm_GetStreamedSize(moudleFiles_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, moduleProperty_wrap);
			iscm_StreamedStore(pInParamsBuf, moudleFiles_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"AddModule",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(moduleKey_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnAddModule;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("AddModule", 9, s_PCC_Deploy_AddModule_TypeInfo_, s_PCC_Deploy_AddModule_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_AddModule)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					moduleProperty_wrap,
					moudleFiles_wrap,
					moduleKey_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::AddModuleFile(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN INT64 moduleKey_wrap,
				IN PCC_ModuleFileType fileType_wrap,
				IN const tcps_Array<PCC_ModuleFile>& moduleFiles_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->AddModuleFile(
					trunk_wrap, trunk_wrap_len,
					moduleKey_wrap,
					fileType_wrap,
					moduleFiles_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);
			inParamsLen += sizeof(moduleKey_wrap);
			inParamsLen += sizeof(fileType_wrap);
			inParamsLen += iscm_GetStreamedSize(moduleFiles_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, moduleKey_wrap);
			iscm_StreamedStore(pInParamsBuf, fileType_wrap);
			iscm_StreamedStore(pInParamsBuf, moduleFiles_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"AddModuleFile",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnAddModuleFile;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("AddModuleFile", 13, s_PCC_Deploy_AddModuleFile_TypeInfo_, s_PCC_Deploy_AddModuleFile_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_AddModuleFile)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					moduleKey_wrap,
					fileType_wrap,
					moduleFiles_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::RemoveModule(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN INT64 moduleKey_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->RemoveModule(
					trunk_wrap, trunk_wrap_len,
					moduleKey_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);
			inParamsLen += sizeof(moduleKey_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, moduleKey_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"RemoveModule",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnRemoveModule;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("RemoveModule", 12, s_PCC_Deploy_RemoveModule_TypeInfo_, s_PCC_Deploy_RemoveModule_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_RemoveModule)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					moduleKey_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::RemoveModuleFiles(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				IN INT64 moduleKey_wrap,
				IN INT32 fileType_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->RemoveModuleFiles(
					trunk_wrap, trunk_wrap_len,
					moduleKey_wrap,
					fileType_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);
			inParamsLen += sizeof(moduleKey_wrap);
			inParamsLen += sizeof(fileType_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, moduleKey_wrap);
			iscm_StreamedStore(pInParamsBuf, fileType_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"RemoveModuleFiles",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnRemoveModuleFiles;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("RemoveModuleFiles", 17, s_PCC_Deploy_RemoveModuleFiles_TypeInfo_, s_PCC_Deploy_RemoveModuleFiles_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_RemoveModuleFiles)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					moduleKey_wrap,
					fileType_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::ListModules(
				IN const char* trunk_wrap, IN INT32 trunk_wrap_len /*= -1*/,
				OUT tcps_Array<PCC_ModulePropWithKey>& modulesInfo_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->ListModules(
					trunk_wrap, trunk_wrap_len,
					modulesInfo_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String trunk_tmp_wrap;
			trunk_tmp_wrap.Attach(xat_bind, (char*)trunk_wrap, trunk_wrap_len);
			inParamsLen += iscm_GetStreamedSize(trunk_tmp_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, trunk_tmp_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"ListModules",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(modulesInfo_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnListModules;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("ListModules", 11, s_PCC_Deploy_ListModules_TypeInfo_, s_PCC_Deploy_ListModules_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_ListModules)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)trunk_wrap, trunk_wrap_len),
					modulesInfo_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::AddModel(
				IN const PCC_ModelProperty& moduleProperty_wrap,
				IN const tcps_Array<PCC_ModelFile>& modelFiles_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->AddModel(
					moduleProperty_wrap,
					modelFiles_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			inParamsLen += iscm_GetStreamedSize(moduleProperty_wrap);
			inParamsLen += iscm_GetStreamedSize(modelFiles_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, moduleProperty_wrap);
			iscm_StreamedStore(pInParamsBuf, modelFiles_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"AddModel",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnAddModel;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("AddModel", 8, s_PCC_Deploy_AddModel_TypeInfo_, s_PCC_Deploy_AddModel_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_AddModel)methodFuncL)(
					m_faceL,
					moduleProperty_wrap,
					modelFiles_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_Deploy::DelModel(
				IN INT64 modelKey_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->DelModel(
					modelKey_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			inParamsLen += sizeof(modelKey_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, modelKey_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_Deploy",
						"DelModel",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnDelModel;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("DelModel", 8, s_PCC_Deploy_DelModel_TypeInfo_, s_PCC_Deploy_DelModel_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_Deploy_LocalMethod::FN_DelModel)methodFuncL)(
					m_faceL,
					modelKey_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

void PCC_Deploy::OnNetworkMalformed_()
{
	if(m_faceR)
		m_faceR->OnNetworkMalformed_();
}

void PCC_Deploy::CloseSession_()
{
	this->SetServeIPP_(true, INVALID_IPP);
}

PROC PCC_Deploy::FindCallback_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				)
{
	if(NULL == name)
	{
		ASSERT(false);
		return NULL;
	}

	// 对OnStreamedCallback_L_()特殊处理
	if(nameLen<0 && 0==strcmp("OnStreamedCallback_L_", name))
		return (PROC)&OnStreamedCallback_L_;

	InitializeAllCallsTypeInfo_();
	typedef TwoItems<CPtrStrA, PROC> FuncPair;
	typedef CQuickStringMap<CPtrStrA, FuncPair, QSS_Traits<0> > CallbackMap_;
	static CallbackMap_* s_cbMap = NULL;
	if(NULL == s_cbMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_cbMap)
		{
			static CallbackMap_ s_cbMapObj;
			CallbackMap_& cbMap = s_cbMapObj;
			s_cbMap = &cbMap;
		}
	}

	CallbackMap_::iterator it = s_cbMap->find(name, nameLen);
	if(s_cbMap->end() == it)
		return NULL;
	const CPtrStrA& ps = it->second.first;
	if(0 != ps.Compare(type, typeLen))
		return NULL;
	return it->second.second;
}

TCPSError PCC_Deploy::OnStreamedCallback_L_(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	PCC_Deploy* const pCC_DeployObj = (PCC_Deploy*)sessionObj;
	ASSERT(pCC_DeployObj->m_faceL);
	if(nameLen < 0)
		nameLen = strlen(callbackName);

	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_DeployObj->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_DeployObj->IsStreamedCallbackMatched_(callbackName, nameLen))
			return TCPS_ERR_CALLBACK_NOT_MATCH;
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_DeployObj->StreamedCallback_(callbackName, nameLen, data, dataLen, iscm_replyData, iscm_replyLen);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
		{
			if(replyData)
				*replyData = iscm_replyData;
			if(replyLen)
				*replyLen = iscm_replyLen;
			return err;
		}
	}

	INT_PTR call_id_len = 12+nameLen;
	CSmartBuf<char, 256> call_id_buf(call_id_len+1);
	char* const call_id = call_id_buf.Get();
	strncpy(call_id, "PCC_Deploy::", 12);
	StrAssign(call_id+12, callbackName, nameLen);

	PCC_Deploy_RC::InitCallbackMap_();
	ASSERT(PCC_Deploy_RC::sm_callbackMap);
	PCC_Deploy_RC::CallbackMap_::const_iterator cit = PCC_Deploy_RC::sm_callbackMap->find(call_id, call_id_len);
	if(PCC_Deploy_RC::sm_callbackMap->end() == cit)
		return TCPS_ERR_TRY_CALL_OTHER_METHODS; // 本接口不支持，尝试其它接口

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = !(cit->second.isPosting);
	peerCallFlags.dummy_15 = 0;
	const BYTE* ptrInParams = (const BYTE*)data;
	INT_PTR ptrInParamsLen = dataLen;
	if(peerCallFlags.requireReply)
	{
		iscm_RPCDataOutfiter outfiter;
		err = cit->second.handler(NULL, pCC_DeployObj, peerCallFlags, ptrInParams, ptrInParamsLen, &outfiter);
		if(TCPS_OK != err)
			return err;
		// outfiter.swbBufs_[0]总指向iscm_RPCDataOutfiter::reply_
		// outfiter.swbBufs_[1]为iscm_RPCReplyPrefix replyPrefix
		ASSERT(outfiter.swbBufs_.size()==1 || outfiter.swbBufs_.size()>=2);
		if(outfiter.swbBufs_.size() >= 2)
		{
			ASSERT(replyData && replyLen);
			*replyLen = SockTotalizeWriteBufVec(outfiter.swbBufs_.Get()+2, outfiter.swbBufs_.size()-2);
			*replyData = tcps_Alloc(*replyLen);
			BYTE* q = (BYTE*)*replyData;
			for(INT_PTR i=2; i<(INT_PTR)outfiter.swbBufs_.size(); ++i)
			{
				const SockWriteBuf& swb = outfiter.swbBufs_[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT(q-(BYTE*)*replyData == *replyLen);
		}
	}
	else
	{
		err = cit->second.handler(NULL, pCC_DeployObj, peerCallFlags, ptrInParams, ptrInParamsLen, NULL/*outfiter*/);
	}

	return err;
}

class PCC_User_RC : public PCC_User_T
{
	friend class PCC_User;
	friend class PCC_User_S;
private:
	PCC_User_RC(const PCC_User_RC&);
	PCC_User_RC& operator= (const PCC_User_RC&);

public:
	explicit PCC_User_RC(PCC_User* owner = NULL);
	virtual ~PCC_User_RC();

protected:
	void DestroyRequester();

	virtual TCPSError OnConnected()
	{
		if(m_owner)
			return m_owner->OnConnected();
		return TCPS_OK;
	}

	virtual void OnPeerBroken()
	{
		if(m_owner)
			m_owner->OnPeerBroken();
	}
	virtual void OnClose()
	{
		if(m_owner)
			m_owner->OnClose();
	}

	virtual void OnConnectTimeout(IN TCPSError cause)
	{
		if(m_owner)
			m_owner->OnConnectTimeout(cause);
	}

public:
	TCPSError SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags = 0,
				IN const IPP& clientID_IPP = INVALID_IPP,
				IN const IPP& secondaryServeIPP = INVALID_IPP,
				IN const IPP& tertiaryServeIPP = INVALID_IPP,
				IN DWORD reconnectIntervalMSELs = 2000
				);
	IPP GetServeIPP() const;
	IPP GetServingIPP() const;
	BOOL IsConnected() const;

	void SetKeeping(
				IN BOOL keeping
				);
	BOOL IsKeeping() const;

	void PrepareDisconnect();

	void SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				);
	void GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const;

	void SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				);
	void GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const;

	void SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				);
	void GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const;

public:
	const PCC_User::MethodMatchingFlag& GetMethodMatchingFlag(
				OUT TCPSError* err = NULL
				);

public:
	TCPSError StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				);

public:
	TCPSError GetPccProperty(
				OUT PCCProperty& pccProp
				) method;

public:
	TCPSError ListNodes(
				OUT tcps_Array<PCC_NodeDesc>& nodes
				) method;

public:
	TCPSError GetNodeDynamicContext(
				IN const char* nodeName, IN INT32 nodeName_len /*= -1*/,
				OUT PCC_DynamicContext& dynamicContext
				) method;

public:
	TCPSError ListModules(
				IN const char* regex, IN INT32 regex_len /*= -1*/,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo
				) method;

public:
	TCPSError Execute(
				IN INT64 moduleKey,
				IN const char* inputUrl, IN INT32 inputUrl_len /*= -1*/,
				IN const char* outputUrl, IN INT32 outputUrl_len /*= -1*/,
				IN const void* moduleParams, IN INT32 moduleParams_len,
				OUT INT64& jobKey
				) method;

protected:
	virtual TCPSError OnExecuted(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context
				) posting_callback
	{
		if(m_owner)
		{
			return m_owner->OnExecuted(
					jobKey,
					errorCode,
					context
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

protected:
	virtual TCPSError OnExecuted1(
				IN INT64 jobKey,
				IN TCPSError errorCode,
				IN const tcps_Binary& context,
				IN const tcps_Array<tcps_Binary>& outArgs
				) posting_callback
	{
		if(m_owner)
		{
			return m_owner->OnExecuted1(
					jobKey,
					errorCode,
					context,
					outArgs
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_ERR_CALLBACK_NOT_IMPLEMENTED;
	}

public:
	TCPSError QueryJobs(
				IN const tcps_Array<INT64>& jobsKey,
				OUT tcps_Array<ExecuteState>& jobsState
				) method;

public:
	TCPSError CancelJob(
				IN INT64 jobKey
				) posting_method;

protected:
	// 返回TCPS_OK允许重定向；返回非TCPS_OK禁止重定向
	virtual TCPSError OnPrepareRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		if(m_owner)
		{
			return m_owner->OnPrepareRedirect_(
					redirectIPP,
					redirectParam
					);
		}
		// TODO: 请在派生类中重载此函数
		return TCPS_OK;
	}

	//////////////////////////////////////////////////////////////
	////// 在此之后的代码使用者无需关心，为ISCM框架实现代码 //////
private:
	PCC_User* const m_owner;
	iscm_ClientThreadIDs m_callingOutTIDs;
	DWORD m_sessionFlags;
	DWORD m_reconnectIntervalMSELs;
	DataOutfiter m_dataOutfiter;
	iscm_IRequester* m_rpcRequester;
	BOOL m_needBrokenNotify;
	BOOL m_prepareDisconnect;

	struct TAsyncTaskStat_
	{
		INT_PTR postingCallingBytes;// 正在等待执行的posting callback的总调用数据大小
		INT32 postingCallings;		// 正在等待执行的posting callback的调用数量
		long totalAsyncTasks;		// 总的正在执行的异步任务数量，等于postingCallings + 其它异步任务数
		TAsyncTaskStat_() : postingCallingBytes(0), postingCallings(0), totalAsyncTasks(0) {}
	};
	TAsyncTaskStat_ m_asyncTaskStat;

private:
	struct ReconnectTask_ : public NPBaseTask
	{
		PCC_User_RC& face_;
		explicit ReconnectTask_(PCC_User_RC& face) : face_(face) {}
		virtual ~ReconnectTask_() {}
		virtual void OnPoolTask()
		{
			// ReconnectTask_重连动作不同于OnConnectedFailedTask_，不做多服务IPP智能切换
			if(!face_.m_prepareDisconnect && face_.IsConnected())
				face_.m_rpcRequester->Reconnect();
			else
				ASSERT(true);
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
			tcps_Delete(this);
		}
	};
	friend struct ReconnectTask_;

private:
	void OnNetworkMalformed_()
	{
		if(m_prepareDisconnect || !m_rpcRequester->IsConnected())
			return;
		ReconnectTask_* task = tcps_NewEx(ReconnectTask_, (*this));
		VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
		FetchTaskPool()->Push(task);
	}

private:
	iscm_MatchingUpdateFlag m_methodMatchingUpdatedFlag;
	PCC_User::MethodMatchingFlag m_methodMatchingFlag;
	TCPSError UpdateMethodMatchingFlag_();

private:
	iscm_PostingPendingParam m_postingPendingParam;

private:
	static TCPSError Wrap_OnExecuted(PCC_User_RC*, PCC_User*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_callback;
	static TCPSError Wrap_OnExecuted1(PCC_User_RC*, PCC_User*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_callback;
	static TCPSError Wrap_SetRedirect_(PCC_User_RC*, PCC_User*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) posting_callback;
	static TCPSError Wrap_CallbackCheck_(PCC_User_RC*, PCC_User*, iscm_PeerCallFlags, const BYTE*&, INT_PTR&, iscm_IRPCOutfiter*) callback;

private:
	TCPSError UDPLink_(
				OUT INT32& servePort,
				OUT INT32& linkKey
				) method;

private:
	TCPSError UDPLinkConfirm_(
				) method;

private:
	TCPSError SetRedirect_(
				IN const IPP& redirectIPP,
				IN const tcps_Binary& redirectParam
				) posting_callback
	{
		IPP ipp = m_rpcRequester->GetServingIPP();
		if(redirectIPP != ipp)
		{
			TCPSError err = this->OnPrepareRedirect_(redirectIPP, redirectParam);
			if(TCPS_OK != err)
				return err;

			struct SwitchTask : public NPBaseTask
			{
				long* totalAsyncTasks_;
				iscm_IRequester* requester_;
				IPP newIPP_;
				virtual void OnPoolTask()
				{
					requester_->TempSwitchTo(newIPP_);
					VERIFY(InterlockedDecrement(totalAsyncTasks_) >= 0);
					this->~SwitchTask();
					tcps_Free(this);
				}
			};
			SwitchTask* task = ::new(tcps_Alloc(sizeof(SwitchTask))) SwitchTask();
			task->totalAsyncTasks_ = &m_asyncTaskStat.totalAsyncTasks;
			task->requester_ = m_rpcRequester;
			task->newIPP_ = redirectIPP;
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
			FetchTaskPool()->Push(task);
		}
		return TCPS_OK;
	}

private:
	TCPSError SetTimeout_(
				IN INT32 recvTimeout,
				IN INT32 sendTimeout
				) posting_method;

private:
	TCPSError SetSessionBufferSize_(
				IN INT32 recvBufBytes,
				IN INT32 sendBufBytes
				) posting_method;

private:
	TCPSError MethodCheck_(
				IN const tcps_Array<tcps_String>& methods,
				IN const tcps_Array<tcps_String>& methodTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) method;

private:
	TCPSError CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback;

private:
	void OnPrepareRPCCallback_(
				IN const void* inParamsData,
				IN INT_PTR inParamsDataLen,
				OUT BOOL& notifyByTaskPool /*= true*/
				);
	TCPSError OnRPCCallback_(
				OUT BOOL& requireReplyData /*= true*/,
				IN const void* inParamsData,
				OUT BOOL& dataTransferred /*= false*/,
				IN INT_PTR inParamsDataLen,
				OUT iscm_IRPCOutfiter* outfiter
				);
	struct CallbackProxy_ : public iscm_ICallbackServeMan::IRPCClient
	{
		PCC_User_RC& face_;
		INT32 sessionKey_;
		long callbackRefCount_;

		explicit CallbackProxy_(PCC_User_RC& face)
			: face_(face), sessionKey_(0), callbackRefCount_(0)
			{}
		virtual INT32& GetSessionKey()
			{	return sessionKey_;	}
		virtual void IncreaseCallbackRef()
			{	ASSERT(callbackRefCount_ >= 0); InterlockedIncrement(&callbackRefCount_);	}
		virtual void DecreaseCallbackRef()
			{	ASSERT(callbackRefCount_ >= 1); InterlockedDecrement(&callbackRefCount_);	}
		virtual void OnCallbackInit()
			{}
		virtual void OnCallbackClose(
					TCPSError cause
					)
			{
				if(face_.m_prepareDisconnect || TCPS_OK==cause || !face_.m_rpcRequester->IsConnected())
					return;
				ReconnectTask_* task = tcps_NewEx(ReconnectTask_, (face_));
				VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);
				FetchTaskPool()->Push(task);
			}
		virtual void OnPrepareRPCCallback(
					IN const void* inParamsData,
					IN INT_PTR inParamsDataLen,
					OUT BOOL& notifyByTaskPool /*= true*/
					)
			{	face_.OnPrepareRPCCallback_(inParamsData, inParamsDataLen, notifyByTaskPool);	}
		virtual TCPSError OnRPCCallback(
					OUT BOOL& requireReplyData /*= true*/,
					IN const void* inParamsData,
					OUT BOOL& dataTransferred /*= false*/,
					IN INT_PTR inParamsDataLen,
					OUT iscm_IRPCOutfiter* outfiter
					)
		{
			TCPSError err;
			while(true)
			{
				err = face_.OnRPCCallback_(requireReplyData, inParamsData, dataTransferred, inParamsDataLen, outfiter);
				if(TCPS_ERR_POSTING_PENDING_FULL == err)
				{
					ASSERT(!dataTransferred);
					Sleep(1);
					continue;
				}
				else
					break;
			}
			return err;
		}
	};
	friend struct CallbackProxy_;
	CallbackProxy_ m_callbackProxy;

private:
	typedef TCPSError (*FCallbackHandler_)(
						IN PCC_User_RC* thisObj /*= NULL*/,
						IN PCC_User* faceObj /*= NULL*/,
						IN iscm_PeerCallFlags peerCallFlags,
						IN OUT const BYTE*& ptrInParams,
						IN OUT INT_PTR& ptrInParamsLen,
						OUT iscm_IRPCOutfiter* outfiter
						);
	struct CallbackSite_
	{
		FCallbackHandler_ handler;
		BOOL isPosting; // 是否为 posting 修饰的方法/回调
		explicit CallbackSite_(FCallbackHandler_ hd = NULL, BOOL pst = false)
			: handler(hd), isPosting(pst)
			{}
	};
	typedef CQuickStringMap<CPtrStrA, CallbackSite_, QSS_Traits<4> > CallbackMap_;
	static const CallbackMap_* sm_callbackMap;
	static CallbackMap_& GetCallbackMap_();
	static void InitCallbackMap_();

private:
	mutable CLocker m_callbackCallLock;
	struct PostingTask_ : public NPBaseTask
	{
		PCC_User_RC& face_;
		iscm_PeerCallFlags peerCallFlags_;
		void* baseInParamsData_;
		CPtrStrA call_id_;
		const BYTE* inParamsData_;
		INT_PTR inParamsDataLen_;
		FCallbackHandler_ handler_;

		explicit PostingTask_(PCC_User_RC& face) : face_(face) {}
		virtual ~PostingTask_() {}
		virtual void OnPoolTask()
		{
			ASSERT(baseInParamsData_ && inParamsData_ && inParamsDataLen_>=0);
			ASSERT((INT_PTR)(inParamsData_ - (const BYTE*)baseInParamsData_) > 0);
			INT_PTR const inParamsDataLen_t = inParamsDataLen_;
			if(!face_.m_prepareDisconnect && face_.IsConnected())
			{
				CNPAutoLock locker(face_.m_callbackCallLock);
				TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
				if(face_.m_owner)
				{
					void* replyData = NULL;
					INT_PTR replyLen = 0;
					err = face_.m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
					if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
					{
						if(face_.m_owner->IsStreamedCallbackMatched_(call_id_.p, call_id_.len))
						{
							err = face_.m_owner->StreamedCallback_(call_id_.p, call_id_.len, inParamsData_, inParamsDataLen_, replyData, replyLen);
							ASSERT(NULL==replyData && 0==replyLen);
							if(TCPS_OK == err)
							{
								inParamsData_ += inParamsDataLen_;
								inParamsDataLen_ = 0;
							}
							else if(TCPS_ERR_MALFORMED_REQ == err)
								face_.OnNetworkMalformed_();
						}
					}
				}
				if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
				{
					err = handler_(
								&face_, NULL,
								peerCallFlags_,
								inParamsData_,
								inParamsDataLen_,
								NULL/*outfiter*/
								);
				}
				ASSERT(TCPS_OK!=err || 0==inParamsDataLen_);
			}
			else
				ASSERT(true);

			tcps_Free(baseInParamsData_);
			PCC_User_RC& face = face_;
			tcps_Delete(this);

			CNPAutoLock locker(face.m_postingCallbacks.lock);
			face.m_asyncTaskStat.postingCallingBytes -= inParamsDataLen_t;
			ASSERT(face.m_asyncTaskStat.postingCallingBytes >= 0);
			--(face.m_asyncTaskStat.postingCallings);
			ASSERT(face.m_asyncTaskStat.postingCallings >= 0);
			VERIFY(InterlockedDecrement(&face.m_asyncTaskStat.totalAsyncTasks) >= 0);

			ASSERT(face.m_postingCallbacks.calling);
			if(NULL == face.m_postingCallbacks.head)
			{
				face.m_postingCallbacks.calling = false;
				return; // 队列处理完毕
			}

			NPBaseTask* task = face.m_postingCallbacks.head;
			if(face.m_postingCallbacks.head == face.m_postingCallbacks.tail)
				face.m_postingCallbacks.head = face.m_postingCallbacks.tail = NULL;
			else
				face.m_postingCallbacks.head = task->m_nextPoolTask;
			// 此处无须对m_asyncTaskStat.postingCallings等变量进行增加（在OnRPCCallback_()已经加过）
			FetchTaskPool()->Push(task);
		}
	};
	friend struct PostingTask_;
	struct PostingTaskSite_
	{
		mutable CLocker lock;
		BOOL calling;
		NPBaseTask* head;
		NPBaseTask* tail;
		PostingTaskSite_() : calling(false), head(NULL), tail(NULL) {}
	};
	PostingTaskSite_ m_postingCallbacks;

private:
	struct PostingProxy_ : public iscm_IPostingCallerMan::INotifier
	{
		PCC_User_RC& face_;
		INT32 callerKey_; // 为iscm_IPostingCallerMan中的会话标识

		explicit PostingProxy_(PCC_User_RC& face)
			: face_(face), callerKey_(0)
			{}

		virtual void OnSessionClose(
					IN INT32 callerKey,
					IN TCPSError cause
					)
		{
			(void)callerKey; (void)cause;
			ASSERT(callerKey_ == callerKey);
			callerKey_ = 0;
		}

		virtual void OnSessionPost(
					IN INT32 callerKey,
					IN const void* data,
					IN INT_PTR dataLen,
					OUT BOOL& dataTransferred /*= false*/
					)
		{
			(void)callerKey;
			ASSERT(callerKey_ == callerKey);
			while(true)
			{
				BOOL requireReplyData = true;
				TCPSError err = face_.OnRPCCallback_(requireReplyData, data, dataTransferred, dataLen, NULL);
				ASSERT(TCPS_OK!=err || !requireReplyData);
				if(TCPS_ERR_POSTING_PENDING_FULL == err)
				{
					ASSERT(!dataTransferred);
					Sleep(1);
					continue;
				}
				else
					break;
			}
		}
	};
	friend struct PostingProxy_;
	PostingProxy_ m_postingProxy;

private:
	struct NetworkHandler_ : public iscm_IRequester::IEventHandler
	{
		PCC_User_RC& face_;
		explicit NetworkHandler_(PCC_User_RC& face) : face_(face) {}
		virtual BOOL Notify(
					IN iscm_IRequester::EventType ev,
					IN TCPSError cause,
					OUT TCPSError* actionErr /*= NULL*/
					);
	};
	friend struct NetworkHandler_;
	NetworkHandler_ m_networkHandler;

private:
	struct OnConnectedFailedTask_ : public NPBaseTask
	{
		PCC_User_RC& face_;
		explicit OnConnectedFailedTask_(PCC_User_RC& face) : face_(face) {}
		virtual ~OnConnectedFailedTask_() {}
		virtual void OnPoolTask()
		{
			// 停止以前连接
			IPP clientID_IPP, secondaryServeIPP, tertiaryServeIPP;
			IPP serveIPP = face_.m_rpcRequester->GetServeIPP(NULL, &clientID_IPP, &secondaryServeIPP, &tertiaryServeIPP);
			face_.SetServeIPP(INVALID_IPP, face_.m_sessionFlags, INVALID_IPP, INVALID_IPP, INVALID_IPP, face_.m_reconnectIntervalMSELs);

			// 切换IPP后再次异步延迟建立连接
			if(serveIPP.IsValid())
			{
				BOOL const ippSwitched = iscm_ThreeIPPSwitch(serveIPP, secondaryServeIPP, tertiaryServeIPP);
				DWORD delayTicks = face_.m_reconnectIntervalMSELs;
				if(ippSwitched)
					delayTicks = min((DWORD)500, delayTicks);
				face_.m_rpcRequester->SetServeIPP(serveIPP, "PCC_User", iscm_IRequester::cflag_async_connect, clientID_IPP, delayTicks, secondaryServeIPP, tertiaryServeIPP);
				face_.m_prepareDisconnect = false;
			}
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
			tcps_Delete(this);
		}
	};
	friend struct OnConnectedFailedTask_;

private:
	struct UDPCallbackProxy_ : public iscm_IUDPSession
	{
		PCC_User_RC& face_;
		BOOL isUsing_;
		explicit UDPCallbackProxy_(PCC_User_RC& face)
			: face_(face), isUsing_(false)
			{}
		virtual void OnUDPCall(
					IN tcps_Binary& frame
					);
	};
	friend struct UDPCallbackProxy_;
	UDPCallbackProxy_ m_UDPCallbackProxy;

private:
	struct StreamedCall_Task_;
	friend struct StreamedCall_Task_;

// posting method方法的异步投递任务类声明，
// 在回调里面调用自身的方法时，使用异步任务（防止死锁）。
private:
	struct CancelJob_Task_;
	friend struct CancelJob_Task_;
	struct SetTimeout__Task_;
	friend struct SetTimeout__Task_;
	struct SetSessionBufferSize__Task_;
	friend struct SetSessionBufferSize__Task_;
};

TCPSError PCC_User_RC::CallbackCheck_(
				IN const tcps_Array<tcps_String>& callbacks,
				IN const tcps_Array<tcps_String>& callbackTypeInfos,
				OUT tcps_Array<BOOL>& matchingFlags
				) callback
{
	if(0==callbacks.Length() || callbacks.Length()!=callbackTypeInfos.Length())
		return TCPS_ERR_INVALID_PARAM;

	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<3> > CallbackMap_;
	static CallbackMap_* s_cbMap = NULL;
	if(NULL == s_cbMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_cbMap)
		{
			static CallbackMap_ s_cbMapObj;
			CallbackMap_& cbMap = s_cbMapObj;
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("OnExecuted"), CPtrStrA(s_PCC_User_OnExecuted_TypeInfo_, s_PCC_User_OnExecuted_TypeInfo_len_))).second);
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("OnExecuted1"), CPtrStrA(s_PCC_User_OnExecuted1_TypeInfo_, s_PCC_User_OnExecuted1_TypeInfo_len_))).second);
			VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("SetRedirect_"), CPtrStrA(s_PCC_User_SetRedirect__TypeInfo_, s_PCC_User_SetRedirect__TypeInfo_len_))).second);
			s_cbMap = &cbMap;
		}
	}

	matchingFlags.Resize(callbacks.Length());
	for(int index=0; index<callbacks.Length(); ++index)
	{
		BOOL& flag = matchingFlags[index];
		const tcps_String& name = callbacks[index];
		const tcps_String& typeInfos = callbackTypeInfos[index];
		CallbackMap_::const_iterator cit = s_cbMap->find(name.Get(), name.Length());
		if(cit!=s_cbMap->end() && 0==typeInfos.Compare(cit->second.p, cit->second.len))
			flag = true;
		else
			flag = false;
	}
	return TCPS_OK;
}

PCC_User::MethodMatchingFlag::MethodMatchingFlag()
{
	Reset();
	mmap_.insert(std::make_pair(CPtrStrA("GetPccProperty", 14), Info(&matching_GetPccProperty, false)));
	mmap_.insert(std::make_pair(CPtrStrA("ListNodes", 9), Info(&matching_ListNodes, false)));
	mmap_.insert(std::make_pair(CPtrStrA("GetNodeDynamicContext", 21), Info(&matching_GetNodeDynamicContext, false)));
	mmap_.insert(std::make_pair(CPtrStrA("ListModules", 11), Info(&matching_ListModules, false)));
	mmap_.insert(std::make_pair(CPtrStrA("Execute", 7), Info(&matching_Execute, false)));
	mmap_.insert(std::make_pair(CPtrStrA("QueryJobs", 9), Info(&matching_QueryJobs, false)));
	mmap_.insert(std::make_pair(CPtrStrA("CancelJob", 9), Info(&matching_CancelJob, true)));
	mmap_.insert(std::make_pair(CPtrStrA("UDPLink_", 8), Info(&matching_UDPLink_, false)));
	mmap_.insert(std::make_pair(CPtrStrA("UDPLinkConfirm_", 15), Info(&matching_UDPLinkConfirm_, false)));
	mmap_.insert(std::make_pair(CPtrStrA("SetTimeout_", 11), Info(&matching_SetTimeout_, true)));
	mmap_.insert(std::make_pair(CPtrStrA("SetSessionBufferSize_", 21), Info(&matching_SetSessionBufferSize_, true)));
}

void PCC_User::MethodMatchingFlag::Reset()
{
	matching_GetPccProperty = false;
	matching_ListNodes = false;
	matching_GetNodeDynamicContext = false;
	matching_ListModules = false;
	matching_Execute = false;
	matching_QueryJobs = false;
	matching_CancelJob = false;
	matching_UDPLink_ = false;
	matching_UDPLinkConfirm_ = false;
	matching_SetTimeout_ = false;
	matching_SetSessionBufferSize_ = false;
}

TCPSError PCC_User_RC::UpdateMethodMatchingFlag_()
{
	if(!m_methodMatchingUpdatedFlag.needUpdate)
		return TCPS_OK;
	InitializeAllCallsTypeInfo_();
	tcps_String methods_ar[11];
	IN tcps_Array<tcps_String> methods;
	methods.Attach(xat_bind, methods_ar, 11);
	tcps_String methodTypeInfos_ar[11];
	IN tcps_Array<tcps_String> methodTypeInfos;
	methodTypeInfos.Attach(xat_bind, methodTypeInfos_ar, 11);
	methods_ar[0].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("GetPccProperty"));
	methodTypeInfos_ar[0].Attach(xat_bind, (char*)s_PCC_User_GetPccProperty_TypeInfo_, s_PCC_User_GetPccProperty_TypeInfo_len_);
	methods_ar[1].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("ListNodes"));
	methodTypeInfos_ar[1].Attach(xat_bind, (char*)s_PCC_User_ListNodes_TypeInfo_, s_PCC_User_ListNodes_TypeInfo_len_);
	methods_ar[2].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("GetNodeDynamicContext"));
	methodTypeInfos_ar[2].Attach(xat_bind, (char*)s_PCC_User_GetNodeDynamicContext_TypeInfo_, s_PCC_User_GetNodeDynamicContext_TypeInfo_len_);
	methods_ar[3].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("ListModules"));
	methodTypeInfos_ar[3].Attach(xat_bind, (char*)s_PCC_User_ListModules_TypeInfo_, s_PCC_User_ListModules_TypeInfo_len_);
	methods_ar[4].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("Execute"));
	methodTypeInfos_ar[4].Attach(xat_bind, (char*)s_PCC_User_Execute_TypeInfo_, s_PCC_User_Execute_TypeInfo_len_);
	methods_ar[5].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("QueryJobs"));
	methodTypeInfos_ar[5].Attach(xat_bind, (char*)s_PCC_User_QueryJobs_TypeInfo_, s_PCC_User_QueryJobs_TypeInfo_len_);
	methods_ar[6].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("CancelJob"));
	methodTypeInfos_ar[6].Attach(xat_bind, (char*)s_PCC_User_CancelJob_TypeInfo_, s_PCC_User_CancelJob_TypeInfo_len_);
	methods_ar[7].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("UDPLink_"));
	methodTypeInfos_ar[7].Attach(xat_bind, (char*)s_PCC_User_UDPLink__TypeInfo_, s_PCC_User_UDPLink__TypeInfo_len_);
	methods_ar[8].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("UDPLinkConfirm_"));
	methodTypeInfos_ar[8].Attach(xat_bind, (char*)s_PCC_User_UDPLinkConfirm__TypeInfo_, s_PCC_User_UDPLinkConfirm__TypeInfo_len_);
	methods_ar[9].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetTimeout_"));
	methodTypeInfos_ar[9].Attach(xat_bind, (char*)s_PCC_User_SetTimeout__TypeInfo_, s_PCC_User_SetTimeout__TypeInfo_len_);
	methods_ar[10].Attach(xat_bind, (char*)CONST_STR_TO_PTR_LEN("SetSessionBufferSize_"));
	methodTypeInfos_ar[10].Attach(xat_bind, (char*)s_PCC_User_SetSessionBufferSize__TypeInfo_, s_PCC_User_SetSessionBufferSize__TypeInfo_len_);
	OUT tcps_Array<BOOL> matchingFlags;
	TCPSError err = this->MethodCheck_(methods, methodTypeInfos, matchingFlags);
	if(TCPS_OK == err)
	{
		if(matchingFlags.Length() == methods.Length())
		{
			m_methodMatchingUpdatedFlag.needUpdate = false;
			const BOOL* const matchingFlags_p = matchingFlags.Get();
			m_methodMatchingFlag.matching_GetPccProperty = matchingFlags_p[0];
			m_methodMatchingFlag.matching_ListNodes = matchingFlags_p[1];
			m_methodMatchingFlag.matching_GetNodeDynamicContext = matchingFlags_p[2];
			m_methodMatchingFlag.matching_ListModules = matchingFlags_p[3];
			m_methodMatchingFlag.matching_Execute = matchingFlags_p[4];
			m_methodMatchingFlag.matching_QueryJobs = matchingFlags_p[5];
			m_methodMatchingFlag.matching_CancelJob = matchingFlags_p[6];
			m_methodMatchingFlag.matching_UDPLink_ = matchingFlags_p[7];
			m_methodMatchingFlag.matching_UDPLinkConfirm_ = matchingFlags_p[8];
			m_methodMatchingFlag.matching_SetTimeout_ = matchingFlags_p[9];
			m_methodMatchingFlag.matching_SetSessionBufferSize_ = matchingFlags_p[10];
		}
		else
		{
			ASSERT(false);
			err = TCPS_ERR_MALFORMED_REPLY;
		}
	}
	if(m_methodMatchingUpdatedFlag.needUpdate)
		m_methodMatchingFlag.Reset();
	return err;
}

const PCC_User::MethodMatchingFlag& PCC_User_RC::GetMethodMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	TCPSError ret = UpdateMethodMatchingFlag_();
	if(err)
		*err = ret;
	return m_methodMatchingFlag;
}

BOOL PCC_User_RC::NetworkHandler_::Notify(
				IN iscm_IRequester::EventType ev,
				IN TCPSError cause,
				OUT TCPSError* actionErr /*= NULL*/
				)
{
	if(actionErr)
		*actionErr = TCPS_OK;
	if(iscm_IRequester::et_connected==ev || iscm_IRequester::et_attached==ev)
	{
		if(face_.m_prepareDisconnect)
			return true;
	}

	if(iscm_IRequester::et_connected == ev)
	{
#if 1
		// 建立回调通道
		if(0 == (face_.m_sessionFlags&ISCMC_NO_CALLBACK))
		{
			// 连接回调通道，使用直接连接方式
			IPP const serveIPP = face_.m_rpcRequester->GetServingIPP();
			INT32 peerSessionKey;
			INT64 const bindID = face_.m_rpcRequester->GetPeerSessionKey(peerSessionKey);
			ASSERT(serveIPP.IsValid() && 0!=bindID && 0!=peerSessionKey);

			AutoDeleteInterface<iscm_IRequester> autoRequester;
			autoRequester.face_ = iscm_MakeRequester(false);
			if(NULL == autoRequester.face_)
			{
				// 容错处理
				ASSERT(false);
				if(actionErr)
					*actionErr = TCPS_ERR_OUT_OF_MEMORY;
				return false;
			}

			DWORD connectTimeout = INFINITE;
			DWORD recvTimeout = INFINITE;
			DWORD sendTimeout = INFINITE;
			face_.m_rpcRequester->GetTimeout(&connectTimeout, &recvTimeout, &sendTimeout);
			DWORD const timeoutMSELs = (INFINITE==connectTimeout ? iscm_GetDefaultConnectTimeout() : connectTimeout);
			BOOL const is_AF_LOCAL = tcps_Use_AF_LOCAL(serveIPP.ip_);
			SOCKET cbSock = TCPNewClientByTime(serveIPP.ip_, serveIPP.port_, timeoutMSELs, is_AF_LOCAL);
			if(!SockValid(cbSock))
			{
				if(actionErr)
					*actionErr = TCPS_ERR_CONNECT_FAILED;
				return false;
			}

			iscm_IRequester* callbackRequester = autoRequester.face_;
			VERIFY(TCPS_OK == callbackRequester->AttachSocket(cbSock, true));

			// 若应用程序没有调用过SetTimeout()，则此处使用有限时间超时（ISCM对同步RPC调用默认使用超长时间超时，见'iscm_requester.cpp'）
			recvTimeout = (INFINITE==recvTimeout ? 2000 : recvTimeout);
			sendTimeout = (INFINITE==sendTimeout ? 1000 : sendTimeout);
			callbackRequester->SetTimeout(INFINITE, recvTimeout, sendTimeout);

			SockWriteBuf swb[2];
			swb[0].data = &bindID;
			swb[0].len = sizeof(bindID);
			swb[1].data = &peerSessionKey;
			swb[1].len = sizeof(peerSessionKey);
			tcps_Binary reply;
			TCPSError err = callbackRequester->Call(RPCCT_TO_CALLBACK, swb, ARRAY_LEN(swb), reply);
			if(TCPS_OK != err)
			{
				if(actionErr)
					*actionErr = err;
				return false;
			}
			ASSERT(reply.IsEmpty());

			VERIFY(cbSock == callbackRequester->DropSocket());
			face_.m_callbackProxy.IncreaseCallbackRef();
			iscm_FetchCallbackServeMan().AddCallbackClient(&face_.m_callbackProxy, cbSock);
		}
#endif

#if 1
		// 建立posting通道
		if(0 == (face_.m_sessionFlags&ISCMC_NO_POSTING_CHANNEL)
			&& 0 == (face_.m_sessionFlags&ISCMC_UDP_POSTING)
			)
		{
			// 连接posting通道，使用直接连接方式
			SOCKET postingSock = INVALID_SOCKET;

			AutoDeleteInterface<iscm_IRequester> autoRequester;
			autoRequester.face_ = iscm_MakeRequester(false);
			if(NULL == autoRequester.face_)
			{
				// 容错处理
				ASSERT(false);
				if(actionErr)
					*actionErr = TCPS_ERR_OUT_OF_MEMORY;
				return false;
			}

			DWORD connectTimeout = INFINITE;
			DWORD recvTimeout = INFINITE;
			DWORD sendTimeout = INFINITE;
			face_.m_rpcRequester->GetTimeout(&connectTimeout, &recvTimeout, &sendTimeout);
			DWORD const timeoutMSELs = (INFINITE==connectTimeout ? iscm_GetDefaultConnectTimeout() : connectTimeout);
			INT32 peerSessionKey;
			INT64 const bindID = face_.m_rpcRequester->GetPeerSessionKey(peerSessionKey);
			ASSERT(0!=bindID && 0!=peerSessionKey);

			IPP const serveIPP = face_.m_rpcRequester->GetServingIPP();
			ASSERT(serveIPP.IsValid());
			BOOL is_AF_LOCAL = tcps_Use_AF_LOCAL(serveIPP.ip_);
			postingSock = TCPNewClientByTime(serveIPP.ip_, serveIPP.port_, timeoutMSELs, is_AF_LOCAL);
			if(!SockValid(postingSock))
			{
				if(actionErr)
					*actionErr = TCPS_ERR_CONNECT_FAILED;
				return false;
			}

			iscm_IRequester* postingRequester = autoRequester.face_;
			VERIFY(TCPS_OK == postingRequester->AttachSocket(postingSock, true));

			// 若应用程序没有调用过SetTimeout()，则此处使用有限时间超时（ISCM对同步RPC调用默认使用超长时间超时，见'iscm_requester.cpp'）
			recvTimeout = (INFINITE==recvTimeout ? 2000 : recvTimeout);
			sendTimeout = (INFINITE==sendTimeout ? 1000 : sendTimeout);
			postingRequester->SetTimeout(INFINITE, recvTimeout, sendTimeout);

			SockWriteBuf swb[2];
			swb[0].data = &bindID;
			swb[0].len = sizeof(bindID);
			swb[1].data = &peerSessionKey;
			swb[1].len = sizeof(peerSessionKey);
			tcps_Binary reply;
			TCPSError err = postingRequester->Call(RPCCT_TO_POSTING_CHANNEL, swb, ARRAY_LEN(swb), reply);
			/*if(TCPS_OK != err)
			{
				if(TCPS_ERR_NOT_SUPPORTED != err)
				{
					if(actionErr)
						*actionErr = err;
					return false;
				}
			}*/
			ASSERT(reply.IsEmpty());

			if(TCPS_OK == err)
			{
				VERIFY(postingSock == postingRequester->DropSocket());
				iscm_FetchPostingCallerMan().AddSession(face_.m_postingProxy.callerKey_, postingSock, true, &face_.m_postingProxy);
			}
		}
#endif
	}
	else if(iscm_IRequester::et_broken==ev || iscm_IRequester::et_dropped==ev)
	{
		// 总尝试删除一次
#if 1
		iscm_FetchCallbackServeMan().DelCallbackClient(&face_.m_callbackProxy);
#endif
#if 1
		if(0 != face_.m_postingProxy.callerKey_)
			iscm_FetchPostingCallerMan().CloseSession(face_.m_postingProxy.callerKey_);
#endif
	}

	if(iscm_IRequester::et_connected==ev || iscm_IRequester::et_attached==ev)
	{
		ASSERT(!face_.m_UDPCallbackProxy.isUsing_);
		while(ISCMC_UDP_POSTING&face_.m_sessionFlags)
		{
			AutoSock udpSock;
			udpSock.sock_ = UDPNew();
			if(!SockValid(udpSock.sock_))
				break;
			IPP localIPP = SockGetLocal(face_.m_rpcRequester->GetSocket());
			if(!localIPP.IsValid())
				break;
			if(TCPS_OK != tcps_AutoBindUDPPort(udpSock.sock_, localIPP.ip_, &localIPP.port_))
				break;

			INT32 serveUDPPort = -1;
			INT32 udpLinkKey = 0;
			TCPSError err = face_.UDPLink_(serveUDPPort, udpLinkKey);
			if(TCPS_OK == err)
			{
				ASSERT(0 != udpLinkKey);
				IPP peerIPP = face_.GetServingIPP();
				if(0 != UDPConnect(udpSock.sock_, peerIPP.ip_, serveUDPPort))
					break;
				iscm_UDPFrag linkFrag;
				linkFrag.fragType = ISCM_UDP_FRAG_LINK;
				linkFrag.dummyI32 = 0;
				linkFrag.sendKey = udpLinkKey;
				linkFrag.fragNum = 0;
				int r = SockWrite(udpSock.sock_, &linkFrag, sizeof(linkFrag));
				if((int)sizeof(linkFrag) != r)
					break;
				err = face_.UDPLinkConfirm_();
				if(TCPS_OK != err)
					break;
				INT32 sessionID;
				face_.m_rpcRequester->GetPeerSessionKey(sessionID);
				iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
				udpServer.AddSession(sessionID, udpSock.Drop(), &face_.m_UDPCallbackProxy);
				face_.m_UDPCallbackProxy.isUsing_ = true;
			}
			break;
		}
		// 忽略UDP连接错误，若UDP连接失败，则只使用TCP

		DWORD recvTimeout = INFINITE;
		DWORD sendTimeout = INFINITE;
		face_.GetTimeout(NULL, &recvTimeout, &sendTimeout);
		if(INFINITE!=recvTimeout || INFINITE!=sendTimeout)
			face_.SetTimeout_(recvTimeout, sendTimeout);

		INT32 recvBufBytes = -1;
		INT32 sendBufBytes = -1;
		face_.GetSessionBufferSize(&recvBufBytes, &sendBufBytes);
		if(recvBufBytes>=0 || sendBufBytes>=0)
			face_.SetSessionBufferSize_(recvBufBytes, sendBufBytes);
		if((0 == (face_.m_sessionFlags&ISCMC_NO_CALLBACK)) && (recvBufBytes>=0 || sendBufBytes>=0))
		{
			iscm_ICallbackServeMan& man = iscm_FetchCallbackServeMan();
			man.SetSessionBufferSize(&face_.m_callbackProxy, recvBufBytes, sendBufBytes);
		}

		ASSERT(!face_.m_needBrokenNotify);
		face_.m_needBrokenNotify = true;
		TCPSError err = TCPS_ERROR;

		// 此处对m_asyncTaskStat.totalAsyncTasks提前加一，以防止如下情况发生：
		// 当用户程序在OnConnected()中异步投递了删除本Client对象的任务，且返回非TCPS_OK；
		// 此时可能OnConnectedFailedTask_::OnPoolTask()被执行时，本Client对象已经被析构，
		// 导致非法内存错误。
		VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);

		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnConnected);
			try
			{
				err = face_.OnConnected();
			}
			catch(TCPSError ret)
			{
				ASSERT(TCPS_OK != ret);
				err = ret;
			}
			catch(int ret)
			{
				ASSERT(TCPS_OK != ret);
				err = (TCPSError)ret;
			}
			catch(std::bad_alloc)
			{
				err = TCPS_ERR_OUT_OF_MEMORY;
			}
			ISCM_BEGIN_CATCH_ALL_()
				err = TCPS_ERR_UNKNOWN_EXCEPTION;
			ISCM_END_CATCH_ALL_()
		}

		if(TCPS_OK!=err && 0==(ISCMC_NO_ASYNC_RECONNECT&face_.m_sessionFlags))
		{
			// 在OnConnected()之前引用计数已经加一，此处不能再加
		//	VERIFY(InterlockedIncrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 1);
			OnConnectedFailedTask_* task = tcps_NewEx(OnConnectedFailedTask_, (face_));
			FetchTaskPool()->Push(task);
		}
		else
		{
			// OnConnected()返回成功，对在OnConnected()之前的引用计数加一做对称处理
			VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		}
		if(actionErr)
			*actionErr = err;
	}
	else if(iscm_IRequester::et_connect_timeout == ev)
	{
		iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnConnectTimeout);
		ISCM_BEGIN_TRY_()
			face_.OnConnectTimeout(cause);
		ISCM_END_TRY_()
		ISCM_BEGIN_CATCH_ALL_()
		ISCM_END_CATCH_ALL_()
	}
	else
	{
		ASSERT(iscm_IRequester::et_broken==ev || iscm_IRequester::et_dropped==ev);
		if(0 != face_.m_postingProxy.callerKey_)
			iscm_FetchPostingCallerMan().CloseSession(face_.m_postingProxy.callerKey_);
		ASSERT(face_.m_callbackProxy.callbackRefCount_ >= 0);
		while(face_.m_callbackProxy.callbackRefCount_ > 0)
			Sleep(1);
		while(0 != face_.m_postingProxy.callerKey_)
			Sleep(1);
		while(face_.m_asyncTaskStat.postingCallings > 0)
			Sleep(1);
		ASSERT(0==face_.m_asyncTaskStat.postingCallingBytes && 0==face_.m_asyncTaskStat.postingCallings);
		if(face_.m_needBrokenNotify)
		{
			face_.m_needBrokenNotify = false;
			{
				iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(face_.m_callingOutTIDs, iscm_cct_OnClose);
				ISCM_BEGIN_TRY_()
					if(face_.m_owner && (INVALID_OSTHREADID==face_.m_owner->GetClosingTID_() || OSThreadSelf()!=face_.m_owner->GetClosingTID_()))
						face_.OnPeerBroken();
					face_.OnClose();
				ISCM_END_TRY_()
				ISCM_BEGIN_CATCH_ALL_()
				ISCM_END_CATCH_ALL_()
			}

			if(face_.m_UDPCallbackProxy.isUsing_)
			{
				face_.m_UDPCallbackProxy.isUsing_ = false;
				INT32 sessionID;
				face_.m_rpcRequester->GetPeerSessionKey(sessionID);
				iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
				udpServer.CloseSession(sessionID);
			}
		}
	}
	face_.m_methodMatchingUpdatedFlag.needUpdate = true;

	return true;
}

const PCC_User_RC::CallbackMap_* PCC_User_RC::sm_callbackMap = NULL;
PCC_User_RC::CallbackMap_& PCC_User_RC::GetCallbackMap_()
	{	LOCAL_SAFE_STATIC_OBJ(CallbackMap_);	}

void PCC_User_RC::InitCallbackMap_()
{
	if(sm_callbackMap)
		return;
	IscmRPCGlobalLocker locker;
	if(sm_callbackMap)
		return;
	CallbackMap_& cbMap = GetCallbackMap_();
	ASSERT(0 == cbMap.size());
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::OnExecuted"), CallbackSite_(&PCC_User_RC::Wrap_OnExecuted, true))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::OnExecuted1"), CallbackSite_(&PCC_User_RC::Wrap_OnExecuted1, true))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::SetRedirect_"), CallbackSite_(&PCC_User_RC::Wrap_SetRedirect_, true))).second);
	VERIFY(cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("PCC_User::CallbackCheck_"), CallbackSite_(&PCC_User_RC::Wrap_CallbackCheck_, false))).second);
	sm_callbackMap = &cbMap;
}

PCC_User_RC::PCC_User_RC(PCC_User* owner /*= NULL*/)
	: m_owner(owner)
	, m_sessionFlags(0)
	, m_reconnectIntervalMSELs(2000)
	, m_rpcRequester(iscm_MakeRequester(false))
	, m_needBrokenNotify(false)
	, m_prepareDisconnect(false)
	, m_callbackProxy(*this)
	, m_postingProxy(*this)
	, m_networkHandler(*this)
	, m_UDPCallbackProxy(*this)
{
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_String*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_Binary*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((tcps_Array<int>*)64)->LenRef()));
	STATIC_ASSERT(sizeof(INT32) == sizeof(((CPtrStrA*)64)->len));

	m_rpcRequester->SetEventHandler(&m_networkHandler);
	iscm_InitClientSingletons(true, true);
	InitCallbackMap_();
}

PCC_User_RC::~PCC_User_RC()
{
	DestroyRequester();
}

void PCC_User_RC::DestroyRequester()
{
	if(NULL == m_rpcRequester)
		return;
	NPR_ASSERT_EX(!m_callingOutTIDs.HasFlag(OSThreadSelf(), NULL), "禁止在对象自己的调用里删除自身");
	PrepareDisconnect();
	while(0 != m_postingProxy.callerKey_)
		Sleep(1);
	ASSERT(m_callbackProxy.callbackRefCount_ >= 0);
	while(m_callbackProxy.callbackRefCount_ > 0)
		Sleep(1);
	ASSERT(m_asyncTaskStat.postingCallingBytes>=0 && m_asyncTaskStat.postingCallings>=0 && m_asyncTaskStat.totalAsyncTasks>=0);
	while(m_asyncTaskStat.totalAsyncTasks > 0)
		Sleep(1);
	ASSERT(0==m_asyncTaskStat.postingCallingBytes && 0==m_asyncTaskStat.postingCallings);
	m_rpcRequester->DeleteThis();
	m_rpcRequester = NULL;
}

TCPSError PCC_User_RC::SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	NPR_ASSERT_EX(!m_callingOutTIDs.HasFlag(OSThreadSelf(), NULL), "禁止在对象自己的调用里调用此函数");
	m_sessionFlags = sessionFlags;
	m_sessionFlags &= ~ISCMC_NO_CALLBACK; // 本接口支持重定向，总启动回调（忽略ISCMC_NO_CALLBACK标志）
	m_reconnectIntervalMSELs = max((DWORD)10, reconnectIntervalMSELs);
	DWORD t1, t2, t3;
	m_rpcRequester->GetTimeout(&t1, &t2, &t3, NULL);
	m_rpcRequester->SetTimeout(t1, t2, t2, m_reconnectIntervalMSELs);
	iscm_IRequester::ConnectFlag cflag;
	if(ISCMC_ASYNC_CONNECT&sessionFlags)
		cflag = iscm_IRequester::cflag_async_connect;
	else if(ISCMC_NO_ASYNC_RECONNECT&sessionFlags)
		cflag = iscm_IRequester::cflag_wait_no_reconnect;
	else
		cflag = iscm_IRequester::cflag_wait_async_reconnect;
	TCPSError err = m_rpcRequester->SetServeIPP(serveIPP, "PCC_User", cflag, clientID_IPP, 0, secondaryServeIPP, tertiaryServeIPP);
	if(serveIPP.IsValid())
		m_prepareDisconnect = false;
	return err;
}

IPP PCC_User_RC::GetServeIPP() const
	{	return m_rpcRequester->GetServeIPP();	}

IPP PCC_User_RC::GetServingIPP() const
	{	return m_rpcRequester->GetServingIPP();	}

BOOL PCC_User_RC::IsConnected() const
	{	return m_rpcRequester->IsConnected();	}

void PCC_User_RC::SetKeeping(
			IN BOOL keeping
			)
	{	m_rpcRequester->SetKeeping(keeping);	}

BOOL PCC_User_RC::IsKeeping() const
	{	return m_rpcRequester->IsKeeping();	}

void PCC_User_RC::PrepareDisconnect()
{
	m_prepareDisconnect = true;
	m_rpcRequester->PrepareDisconnect();
	if(0 != m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().CloseSession(m_postingProxy.callerKey_);
	iscm_FetchCallbackServeMan().DelCallbackClient(&m_callbackProxy);
	if(m_UDPCallbackProxy.isUsing_)
	{
		m_UDPCallbackProxy.isUsing_ = false;
		INT32 sessionID;
		m_rpcRequester->GetPeerSessionKey(sessionID);
		iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
		udpServer.CloseSession(sessionID, true);
	}
}

void PCC_User_RC::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	m_rpcRequester->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	if(IsConnected())
		SetTimeout_(recvTimeout, sendTimeout);
}

void PCC_User_RC::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const
	{	m_rpcRequester->GetTimeout(connectTimeout, recvTimeout, sendTimeout);	}

void PCC_User_RC::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	if(recvBufBytes<0 && sendBufBytes<0)
		return;
	m_rpcRequester->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	if(0 == (m_sessionFlags&ISCMC_NO_CALLBACK))
	{
		iscm_ICallbackServeMan& man = iscm_FetchCallbackServeMan();
		man.SetSessionBufferSize(&m_callbackProxy, recvBufBytes, sendBufBytes);
	}
	if(IsConnected())
		SetSessionBufferSize_(recvBufBytes, sendBufBytes);
}

void PCC_User_RC::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
	{	m_rpcRequester->GetSessionBufferSize(recvBufBytes, sendBufBytes);	}

void PCC_User_RC::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
	{	m_postingPendingParam.Set(maxPendingBytes, maxPendings);	}

void PCC_User_RC::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
	{	m_postingPendingParam.Get(maxPendingBytes, maxPendings);	}

void PCC_User_RC::OnPrepareRPCCallback_(
				IN const void* inParamsData,
				IN INT_PTR inParamsDataLen,
				OUT BOOL& notifyByTaskPool /*= true*/
				)
{
#if 1
	// 所有调用都用taskPool异步方式，以保证不同会话的并行调用
	ASSERT(inParamsData && inParamsDataLen>0 && notifyByTaskPool);
	(void)inParamsData; (void)inParamsDataLen; (void)notifyByTaskPool;
#else
	ASSERT(inParamsData && inParamsDataLen>0 && notifyByTaskPool);
	const BYTE* ptrInParams = (const BYTE*)inParamsData;
	INT_PTR ptrInParamsLen = inParamsDataLen;

	if(ptrInParamsLen < (int)sizeof(iscm_PeerCallFlags))
		return;
	iscm_PeerCallFlags peerCallFlags = *(iscm_PeerCallFlags*)ptrInParams;
	if((int)sizeof(BOOL) != peerCallFlags.sizeofBOOL_req)
		return;
	if((int)sizeof(DummyEnumType) != peerCallFlags.sizeofEnum_req)
		return;
	ptrInParams += sizeof(iscm_PeerCallFlags);
	ptrInParamsLen -= sizeof(iscm_PeerCallFlags);

	if(ptrInParamsLen < (int)sizeof(INT32))
		return;
	INT32 call_id_len = *(INT32*)ptrInParams;
	ptrInParams += sizeof(INT32);
	ptrInParamsLen -= sizeof(INT32);
	if(ptrInParamsLen < call_id_len+1)
		return;
	const char* call_id = (const char*)ptrInParams;
	ptrInParams += call_id_len+1;
	ptrInParamsLen -= call_id_len+1;

	ASSERT(sm_callbackMap);
	CallbackMap_::const_iterator cit = sm_callbackMap->find(call_id, call_id_len);
	if(sm_callbackMap->end() == cit)
		return;

	if(cit->second.isPosting)
		notifyByTaskPool = false;
#endif
}

TCPSError PCC_User_RC::OnRPCCallback_(
				OUT BOOL& requireReplyData /*= true*/,
				IN const void* inParamsData,
				OUT BOOL& dataTransferred /*= false*/,
				IN INT_PTR inParamsDataLen,
				OUT iscm_IRPCOutfiter* outfiter
				)
{
	(void)inParamsDataLen; // avoid warning.
	ASSERT(requireReplyData && inParamsData && inParamsDataLen>0/* && outfiter*/);
	const BYTE* ptrInParams = (const BYTE*)inParamsData;
	INT_PTR ptrInParamsLen = inParamsDataLen;

	if(ptrInParamsLen < (int)sizeof(iscm_PeerCallFlags))
		return TCPS_ERR_MALFORMED_REQ;
	iscm_PeerCallFlags peerCallFlags = *(iscm_PeerCallFlags*)ptrInParams;
	if((int)sizeof(BOOL) != peerCallFlags.sizeofBOOL_req)
		return TCPS_ERR_MALFORMED_REQ;
	if((int)sizeof(DummyEnumType) != peerCallFlags.sizeofEnum_req)
		return TCPS_ERR_MALFORMED_REQ;
	ptrInParams += sizeof(iscm_PeerCallFlags);
	ptrInParamsLen -= sizeof(iscm_PeerCallFlags);

	if(ptrInParamsLen < (int)sizeof(INT32))
		return TCPS_ERR_MALFORMED_REQ;
	INT32 call_id_len = *(INT32*)ptrInParams;
	ptrInParams += sizeof(INT32);
	ptrInParamsLen -= sizeof(INT32);
	if(ptrInParamsLen < call_id_len+1)
		return TCPS_ERR_MALFORMED_REQ;
	const char* call_id = (const char*)ptrInParams;
	ptrInParams += call_id_len+1;
	ptrInParamsLen -= call_id_len+1;

	ASSERT(sm_callbackMap);
	CallbackMap_::const_iterator cit = sm_callbackMap->find(call_id, call_id_len);
	if(sm_callbackMap->end() == cit)
		return TCPS_ERR_TRY_CALL_OTHER_METHODS; // 本接口不支持，尝试其它接口

	CPtrStrA const streamedCallID(call_id+CONST_STR_LEN("PCC_User::"), call_id_len-CONST_STR_LEN("PCC_User::"));

	// posting回调
	if(cit->second.isPosting)
	{
		if(m_prepareDisconnect)
			return TCPS_ERR_EXITING;

		// 当缓存的未决调用小于1个时，直接调用
		if(m_postingPendingParam.maxPendings_ <= 1)
		{
			CNPAutoLock locker(m_callbackCallLock);
			TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
			if(m_owner)
			{
				void* replyData = NULL;
				INT_PTR replyLen = 0;
				err = m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
				if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
				{
					if(!m_owner->IsStreamedCallbackMatched_(streamedCallID.p, streamedCallID.len))
						return TCPS_ERR_CALLBACK_NOT_MATCH;

					{
						iscm_ClientCallType cct = (cit->second.isPosting ? iscm_cct_posting_callback : iscm_cct_callback);
						iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(m_callingOutTIDs, cct);
						err = m_owner->StreamedCallback_(streamedCallID.p, streamedCallID.len, ptrInParams, ptrInParamsLen, replyData, replyLen);
					}
					ASSERT(NULL==replyData && 0==replyLen);
					if(TCPS_OK == err)
					{
						ptrInParams += ptrInParamsLen;
						ptrInParamsLen = 0;
					}
					else if(TCPS_ERR_MALFORMED_REQ == err)
					{
						this->OnNetworkMalformed_();
						return TCPS_ERR_MALFORMED_REQ;
					}
				}
			}
			if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
				err = cit->second.handler(this, NULL, peerCallFlags, ptrInParams, ptrInParamsLen, NULL/*outfiter*/);
#ifdef _DEBUG
			if(TCPS_OK == err)
			{
				ASSERT(ptrInParams-(const BYTE*)inParamsData == inParamsDataLen);
				ASSERT(0 == ptrInParamsLen);
			}
#else
			(void)err;
#endif
			ASSERT(!peerCallFlags.requireReply);
			requireReplyData = false;
			ASSERT(!dataTransferred);
			return TCPS_OK;
		}

		// 投递一个task，异步执行
		if(m_asyncTaskStat.postingCallingBytes >= m_postingPendingParam.maxPendingBytes_
			|| m_asyncTaskStat.postingCallings >= m_postingPendingParam.maxPendings_
			)
		{
			// 对内置的SetRedirect_()回调，不做限制
			if("PCC_User::SetRedirect_" != cit->first)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}

		// 投递一个异步回调任务，或加入待执行队列
		PostingTask_* task = tcps_NewEx(PostingTask_, (*this));
		task->peerCallFlags_ = peerCallFlags;
		task->baseInParamsData_ = (void*)inParamsData;
		task->call_id_ = streamedCallID;
		task->inParamsData_ = ptrInParams;
		task->inParamsDataLen_ = ptrInParamsLen;
		task->handler_ = cit->second.handler;
		VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) >= 1);
		{
			CNPAutoLock locker(m_postingCallbacks.lock);
			m_asyncTaskStat.postingCallingBytes += ptrInParamsLen;
			++(m_asyncTaskStat.postingCallings);
			if(m_postingCallbacks.calling)
			{
				task->m_nextPoolTask = NULL;
				if(m_postingCallbacks.tail)
				{
					m_postingCallbacks.tail->m_nextPoolTask = task;
					m_postingCallbacks.tail = task;
				}
				else
					m_postingCallbacks.head = m_postingCallbacks.tail = task;
			}
			else
			{
				ASSERT(NULL==m_postingCallbacks.head && NULL==m_postingCallbacks.tail);
				ASSERT(ptrInParamsLen==m_asyncTaskStat.postingCallingBytes && 1==m_asyncTaskStat.postingCallings);
				m_postingCallbacks.calling = true;
				FetchTaskPool()->Push(task);
			}
		}

		if(peerCallFlags.requireReply)
		{
			// 给outfiter填充内置返回参数
			struct PostOutParamWrapSite
			{
				iscm_RPCReplyPrefix replyPrefix;
				PostOutParamWrapSite() { replyPrefix.Init(); }
				static void FreeAction(void* p)
				{
					PostOutParamWrapSite* ptr = (PostOutParamWrapSite*)((BYTE*)p - offset_of(PostOutParamWrapSite, replyPrefix));
					ptr->~PostOutParamWrapSite();
					tcps_Free(ptr);
				}
			};
			PostOutParamWrapSite* opWrapper = tcps_New(PostOutParamWrapSite);
			Set_BaseType_(outfiter, opWrapper->replyPrefix, PostOutParamWrapSite::FreeAction);
		}
		else
		{
			// 指示不需要发送回应数据了
			requireReplyData = false;
		}

		dataTransferred = true; // 指示输入参数数据指针inParamsData被转移
		return TCPS_OK; // 立即返回成功
	}

	// 非posting方法/回调
	TCPSError err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
	{
		CNPAutoLock locker(m_callbackCallLock);
		if(m_owner)
		{
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			err = m_owner->StreamedCallback_(NULL, 0, NULL, 0, replyData, replyLen);
			if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			{
				if("CallbackCheck_" == streamedCallID)
				{
					// CallbackCheck_()在流式调用端不提供，必须调用C++的映射版本
					err = TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED;
				}
				else
				{
					if(!m_owner->IsStreamedCallbackMatched_(streamedCallID.p, streamedCallID.len))
						return TCPS_ERR_CALLBACK_NOT_MATCH;

					{
						iscm_ClientCallType cct = (cit->second.isPosting ? iscm_cct_posting_callback : iscm_cct_callback);
						iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(m_callingOutTIDs, cct);
						err = m_owner->StreamedCallback_(streamedCallID.p, streamedCallID.len, ptrInParams, ptrInParamsLen, replyData, replyLen);
					}
					if(TCPS_OK == err)
					{
						ptrInParams += ptrInParamsLen;
						ptrInParamsLen = 0;
						iscm_RPCReplyPrefix* replyPrefix = (iscm_RPCReplyPrefix*)tcps_Alloc(sizeof(iscm_RPCReplyPrefix));
						replyPrefix->Init();
						outfiter->Push(replyPrefix, sizeof(iscm_RPCReplyPrefix), true, NULL);
						if(replyLen > 0)
						{
							ASSERT(replyData && outfiter);
							outfiter->Push(replyData, replyLen, true, NULL);
						}
						else
							ASSERT(NULL == replyData);
					}
					else
					{
						ASSERT(NULL==replyData && 0==replyLen);
						if(TCPS_ERR_MALFORMED_REQ == err)
						{
							this->OnNetworkMalformed_();
							return TCPS_ERR_MALFORMED_REQ;
						}
					}
				}
			}
		}
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED == err)
			err = cit->second.handler(this, NULL, peerCallFlags, ptrInParams, ptrInParamsLen, outfiter);
	}
#ifdef _DEBUG
	if(TCPS_OK == err)
	{
		ASSERT(ptrInParams-(const BYTE*)inParamsData == inParamsDataLen);
		ASSERT(0 == ptrInParamsLen);
	}
#endif
	return err;
}

struct PCC_User_RC::StreamedCall_Task_ : public NPBaseTask
{
	PCC_User_RC& face_;
	tcps_String methodName_;
	tcps_Binary data_;
	explicit StreamedCall_Task_(
				PCC_User_RC& face,
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/
				)
		: face_(face)
	{
		methodName_.Assign(methodName, nameLen);
		data_.Assign(data, dataLen);
	}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			SockWriteBuf buf;
			buf.data = data_.Get();
			buf.len = data_.Length();
			face_.StreamedCall_(
						methodName_.Get(), methodName_.Length(),
						&buf, 1,
						NULL, NULL
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_User_RC::StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;
	if(NULL==methodName || 0==nameLen)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if(nameLen < 0)
		nameLen = strlen(methodName);

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	const PCC_User::MethodMatchingFlag& methodMatchingFlag = GetMethodMatchingFlag();
	PCC_User::MethodMatchingFlag::MethodMap::const_iterator itMethod = methodMatchingFlag.mmap_.find(methodName, nameLen);
	if(methodMatchingFlag.mmap_.end() == itMethod)
		return TCPS_ERR_METHOD_NOT_MATCH;
	ASSERT(itMethod->second.pMatchingVar);
	if(!*(itMethod->second.pMatchingVar))
		return TCPS_ERR_METHOD_NOT_MATCH;

	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			if(itMethod->second.isPosting)
			{
				StreamedCall_Task_* task = tcps_NewEx(StreamedCall_Task_, (
								*this,
								methodName, nameLen,
								data, dataLen
								));
				VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
				FetchTaskPool()->Push(task);
			}
			else
				NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = !(itMethod->second.isPosting);
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = (INT32)(10+nameLen);
	CSmartBuf<char, 256> call_id_buf(call_id_len+1);
	strncpy(call_id_buf.Get(), "PCC_User::", 10);
	StrAssign(call_id_buf.Get()+10, methodName, nameLen);
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push(call_id_buf.Get(), call_id_len+1);

	// 填充IN参数到outfiter
	if(dataLen > 0)
		m_dataOutfiter.Push(data, dataLen);

	// 调用RPCCall()
	if(peerCallFlags.requireReply) // method
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_RPCReplyPrefix replyPrefix;
		err = m_rpcRequester->RecvD(&replyPrefix, sizeof(replyPrefix));
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}

		INT_PTR leftReplyLen = replyBytes - sizeof(replyPrefix);
		ASSERT(leftReplyLen >= 0);
		if(leftReplyLen > 0)
		{
			ASSERT(replyData && replyLen);
			tcps_Binary replied_data;
			if(!replied_data.Resize(leftReplyLen))
			{
				this->OnNetworkMalformed_();
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			err = m_rpcRequester->RecvD(replied_data.Get(), (int)leftReplyLen);
			if(TCPS_OK != err)
			{
				// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
				return err;
			}
			if(NULL==replyData || NULL==replyLen)
			{
				ASSERT(false);
				return TCPS_ERR_INVALID_PARAM;
			}
			INT32 bytes = 0;
			*replyData = replied_data.Drop(&bytes);
			*replyLen = bytes;
		}
	}
	else // posting method
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_UDPCallbackProxy.isUsing_)
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID;
			m_rpcRequester->GetPeerSessionKey(sessionID);
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

void PCC_User_RC::UDPCallbackProxy_::OnUDPCall(
				IN tcps_Binary& frame
				)
{
	ASSERT(frame.Length() > 0);
	while(true)
	{
		BOOL requireReplyData = true;
		const void* inParamsData = frame.Get();
		BOOL dataTransferred = false;
		INT_PTR inParamsDataLen = frame.Length();
		TCPSError err = face_.OnRPCCallback_(requireReplyData, inParamsData, dataTransferred, inParamsDataLen, NULL/*outfiter*/);
		ASSERT(TCPS_OK!=err || !requireReplyData);
		if(TCPS_ERR_POSTING_PENDING_FULL == err)
		{
			ASSERT(!dataTransferred);
			Sleep(1);
			continue;
		}
		else
		{
			if(dataTransferred)
				frame.Drop();
			break;
		}
	}
}

TCPSError PCC_User_RC::GetPccProperty(
				OUT PCCProperty& pccProp_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_GetPccProperty)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 24;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::GetPccProperty", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT PCCProperty pccProp
			PICK_STRING_Q(iscm_replied_picker, pccProp_wrap.version);
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_User::GetPccProperty() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::ListNodes(
				OUT tcps_Array<PCC_NodeDesc>& nodes_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_ListNodes)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 19;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::ListNodes", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<PCC_NodeDesc> nodes
		PICK_BASETYPE_Q(iscm_replied_picker, array_len);
		nodes_wrap.Resize(array_len);
		for(int idx2=0; idx2<nodes_wrap.Length(); ++idx2)
		{
			PCC_NodeDesc& ref2 = nodes_wrap[idx2];
				PICK_STRING_Q(iscm_replied_picker, ref2.name);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.cpuType);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.cpuFreq);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.cpuProcessors);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.cpuThreads);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.totalMemoryBytes);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.networkBandwidth);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.osType);
				PICK_STRING_Q(iscm_replied_picker, ref2.osDetail);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.executeBits);
		}
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_User::ListNodes() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::GetNodeDynamicContext(
				IN const char* nodeName_wrap, IN INT32 nodeName_wrap_len /*= -1*/,
				OUT PCC_DynamicContext& dynamicContext_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_GetNodeDynamicContext)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 31;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::GetNodeDynamicContext", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String nodeName
	if(NULL == nodeName_wrap)
	{
		if(nodeName_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		nodeName_wrap = "";
		nodeName_wrap_len = 0;
	}
	if(nodeName_wrap_len < 0)
	{
		nodeName_wrap_len = (INT32)strlen(nodeName_wrap);
		Put_BaseType_(&m_dataOutfiter, nodeName_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)nodeName_wrap, nodeName_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, nodeName_wrap, nodeName_wrap_len);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT PCC_DynamicContext dynamicContext
		PICK_BASETYPE_Q(iscm_replied_picker, dynamicContext_wrap);
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_User::GetNodeDynamicContext() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::ListModules(
				IN const char* regex_wrap, IN INT32 regex_wrap_len /*= -1*/,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_ListModules)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 21;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::ListModules", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_String regex
	if(NULL == regex_wrap)
	{
		if(regex_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		regex_wrap = "";
		regex_wrap_len = 0;
	}
	if(regex_wrap_len < 0)
	{
		regex_wrap_len = (INT32)strlen(regex_wrap);
		Put_BaseType_(&m_dataOutfiter, regex_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)regex_wrap, regex_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, regex_wrap, regex_wrap_len);
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<PCC_ModuleInfo> modulesInfo
		PICK_BASETYPE_Q(iscm_replied_picker, array_len);
		modulesInfo_wrap.Resize(array_len);
		for(int idx2=0; idx2<modulesInfo_wrap.Length(); ++idx2)
		{
			PCC_ModuleInfo& ref2 = modulesInfo_wrap[idx2];
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.moduleKey);
					PICK_STRING_Q(iscm_replied_picker, ref2.moduleTag.name);
					PICK_BASETYPE_Q(iscm_replied_picker, ref2.moduleTag.version);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.modulePattern);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.moduleType);
				PICK_STRING_Q(iscm_replied_picker, ref2.description);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.moduleFileType);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.moduleLatency);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.addTime);
				PICK_BASETYPE_Q(iscm_replied_picker, ref2.moduleSize);
		}
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_User::ListModules() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::Execute(
				IN INT64 moduleKey_wrap,
				IN const char* inputUrl_wrap, IN INT32 inputUrl_wrap_len /*= -1*/,
				IN const char* outputUrl_wrap, IN INT32 outputUrl_wrap_len /*= -1*/,
				IN const void* moduleParams_wrap, IN INT32 moduleParams_wrap_len,
				OUT INT64& jobKey_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_Execute)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 17;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::Execute", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT64 moduleKey
	Put_BaseType_(&m_dataOutfiter, moduleKey_wrap);

	// IN tcps_String inputUrl
	if(NULL == inputUrl_wrap)
	{
		if(inputUrl_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		inputUrl_wrap = "";
		inputUrl_wrap_len = 0;
	}
	if(inputUrl_wrap_len < 0)
	{
		inputUrl_wrap_len = (INT32)strlen(inputUrl_wrap);
		Put_BaseType_(&m_dataOutfiter, inputUrl_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)inputUrl_wrap, inputUrl_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, inputUrl_wrap, inputUrl_wrap_len);
	}

	// IN tcps_String outputUrl
	if(NULL == outputUrl_wrap)
	{
		if(outputUrl_wrap_len > 0)
		{
			ASSERT(false);
			return TCPS_ERR_INVALID_PARAM;
		}
		outputUrl_wrap = "";
		outputUrl_wrap_len = 0;
	}
	if(outputUrl_wrap_len < 0)
	{
		outputUrl_wrap_len = (INT32)strlen(outputUrl_wrap);
		Put_BaseType_(&m_dataOutfiter, outputUrl_wrap_len);
		Put_Bytes_(&m_dataOutfiter, (const BYTE*)outputUrl_wrap, outputUrl_wrap_len+1);
	}
	else
	{
		Put_String_(&m_dataOutfiter, outputUrl_wrap, outputUrl_wrap_len);
	}

	// IN tcps_Binary moduleParams
	if(moduleParams_wrap_len<0 || (moduleParams_wrap_len>0 && NULL==moduleParams_wrap))
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	Put_Binary_(&m_dataOutfiter, moduleParams_wrap, moduleParams_wrap_len);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT INT64 jobKey
		PICK_BASETYPE_Q(iscm_replied_picker, jobKey_wrap);
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_User::Execute() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::Wrap_OnExecuted(
				IN PCC_User_RC* thisObj /*= NULL*/,
				IN PCC_User* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT64 jobKey
	IN INT64 jobKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, jobKey_wrap);

	// IN TCPSError errorCode
	IN TCPSError errorCode_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, errorCode_wrap);

	// IN tcps_Binary context
	IN tcps_Binary context_wrap;
	GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, context_wrap);

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_User::OnExecuted() posting_callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_posting_callback);
			errTcps = thisObj->OnExecuted(
				jobKey_wrap,
				errorCode_wrap,
				context_wrap
				);
		}
		else
		{
			ASSERT(faceObj);
			errTcps = faceObj->OnExecuted(
				jobKey_wrap,
				errorCode_wrap,
				context_wrap
				);
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_User_RC::Wrap_OnExecuted1(
				IN PCC_User_RC* thisObj /*= NULL*/,
				IN PCC_User* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN INT64 jobKey
	IN INT64 jobKey_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, jobKey_wrap);

	// IN TCPSError errorCode
	IN TCPSError errorCode_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, errorCode_wrap);

	// IN tcps_Binary context
	IN tcps_Binary context_wrap;
	GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, context_wrap);

	// IN tcps_Array<tcps_Binary> outArgs
	IN tcps_Array<tcps_Binary> outArgs_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	outArgs_wrap.Resize(array_len);
	for(int idx1=0; idx1<outArgs_wrap.Length(); ++idx1)
	{
		tcps_Binary& ref1 = outArgs_wrap[idx1];
		GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_User::OnExecuted1() posting_callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_posting_callback);
			errTcps = thisObj->OnExecuted1(
				jobKey_wrap,
				errorCode_wrap,
				context_wrap,
				outArgs_wrap
				);
		}
		else
		{
			ASSERT(faceObj);
			errTcps = faceObj->OnExecuted1(
				jobKey_wrap,
				errorCode_wrap,
				context_wrap,
				outArgs_wrap
				);
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

TCPSError PCC_User_RC::QueryJobs(
				IN const tcps_Array<INT64>& jobsKey_wrap,
				OUT tcps_Array<ExecuteState>& jobsState_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_QueryJobs)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 19;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::QueryJobs", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_Array<INT64> jobsKey
	Put_PODArray_<DataOutfiter, INT64>(&m_dataOutfiter, jobsKey_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_IRequester* iscm_replied_picker = m_rpcRequester;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<ExecuteState> jobsState
		PICK_PODARRAY_(iscm_replied_picker, jobsState_wrap);
	}
	return TCPS_OK;
}

struct PCC_User_RC::CancelJob_Task_ : public NPBaseTask
{
	PCC_User_RC& face_;
	IN INT64 jobKey_wrap_;
	explicit CancelJob_Task_(
				PCC_User_RC& face,
				IN INT64 jobKey_wrap
				)
		: face_(face)
		, jobKey_wrap_(jobKey_wrap)
		{}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			face_.CancelJob(
						jobKey_wrap_
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_User_RC::CancelJob(
				IN INT64 jobKey_wrap
				) posting_method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			CancelJob_Task_* task = tcps_NewEx(CancelJob_Task_, (
							*this,
							jobKey_wrap
							));
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
			FetchTaskPool()->Push(task);
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_CancelJob)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 19;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::CancelJob", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT64 jobKey
	Put_BaseType_(&m_dataOutfiter, jobKey_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_UDPCallbackProxy.isUsing_)
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID;
			m_rpcRequester->GetPeerSessionKey(sessionID);
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::UDPLink_(
				OUT INT32& servePort_wrap,
				OUT INT32& linkKey_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_UDPLink_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 18;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::UDPLink_", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT INT32 servePort
		PICK_BASETYPE_Q(iscm_replied_picker, servePort_wrap);

		// OUT INT32 linkKey
		PICK_BASETYPE_Q(iscm_replied_picker, linkKey_wrap);
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_User::UDPLink_() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::UDPLinkConfirm_(
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_UDPLinkConfirm_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 25;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::UDPLinkConfirm_", call_id_len+1);

	// 填充IN参数到outfiter

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		tcps_Binary replied_data;
		if(!replied_data.Resize(replyBytes))
		{
			this->OnNetworkMalformed_();
			return TCPS_ERR_OUT_OF_MEMORY;
		}
		err = m_rpcRequester->RecvD(replied_data.Get(), replyBytes);
		if(TCPS_OK != err)
		{
			// 无须调用this->OnNetworkMalformed_(), m_rpcRequester->RecvD()已做处理
			return err;
		}
		const BYTE* iscm_replied_picker = replied_data.Get();
		const BYTE* const iscm_replied_end = iscm_replied_picker + replyBytes;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_Q(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.
		if(iscm_replied_picker != iscm_replied_end)
		{
			// NPLogError(("PCC_User::UDPLinkConfirm_() method, Malformed replied"));
			this->OnNetworkMalformed_();
			return TCPS_ERR_MALFORMED_REPLY;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::Wrap_SetRedirect_(
				IN PCC_User_RC* thisObj /*= NULL*/,
				IN PCC_User* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) posting_callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN IPP redirectIPP
	IN IPP redirectIPP_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, redirectIPP_wrap);

	// IN tcps_Binary redirectParam
	IN tcps_Binary redirectParam_wrap;
	GET_BINARY_EX_(thisObj, ptrInParams, ptrInParamsLen, redirectParam_wrap);

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_User::SetRedirect_() posting_callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_posting_callback);
			errTcps = thisObj->SetRedirect_(
				redirectIPP_wrap,
				redirectParam_wrap
				);
		}
		else
		{
			(void)faceObj;
			ASSERT(false);
			errTcps = TCPS_ERR_INTERNAL_BUG;
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	return TCPS_OK;
}

struct PCC_User_RC::SetTimeout__Task_ : public NPBaseTask
{
	PCC_User_RC& face_;
	IN INT32 recvTimeout_wrap_;
	IN INT32 sendTimeout_wrap_;
	explicit SetTimeout__Task_(
				PCC_User_RC& face,
				IN INT32 recvTimeout_wrap,
				IN INT32 sendTimeout_wrap
				)
		: face_(face)
		, recvTimeout_wrap_(recvTimeout_wrap)
		, sendTimeout_wrap_(sendTimeout_wrap)
		{}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			face_.SetTimeout_(
						recvTimeout_wrap_,
						sendTimeout_wrap_
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_User_RC::SetTimeout_(
				IN INT32 recvTimeout_wrap,
				IN INT32 sendTimeout_wrap
				) posting_method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			SetTimeout__Task_* task = tcps_NewEx(SetTimeout__Task_, (
							*this,
							recvTimeout_wrap,
							sendTimeout_wrap
							));
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
			FetchTaskPool()->Push(task);
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_SetTimeout_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 21;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::SetTimeout_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT32 recvTimeout
	Put_BaseType_(&m_dataOutfiter, recvTimeout_wrap);

	// IN INT32 sendTimeout
	Put_BaseType_(&m_dataOutfiter, sendTimeout_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_UDPCallbackProxy.isUsing_)
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID;
			m_rpcRequester->GetPeerSessionKey(sessionID);
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

struct PCC_User_RC::SetSessionBufferSize__Task_ : public NPBaseTask
{
	PCC_User_RC& face_;
	IN INT32 recvBufBytes_wrap_;
	IN INT32 sendBufBytes_wrap_;
	explicit SetSessionBufferSize__Task_(
				PCC_User_RC& face,
				IN INT32 recvBufBytes_wrap,
				IN INT32 sendBufBytes_wrap
				)
		: face_(face)
		, recvBufBytes_wrap_(recvBufBytes_wrap)
		, sendBufBytes_wrap_(sendBufBytes_wrap)
		{}
	virtual void OnPoolTask()
	{
		if(!face_.m_prepareDisconnect)
		{
			face_.SetSessionBufferSize_(
						recvBufBytes_wrap_,
						sendBufBytes_wrap_
						);
		}
		VERIFY(InterlockedDecrement(&face_.m_asyncTaskStat.totalAsyncTasks) >= 0);
		tcps_Delete(this);
	}
};
TCPSError PCC_User_RC::SetSessionBufferSize_(
				IN INT32 recvBufBytes_wrap,
				IN INT32 sendBufBytes_wrap
				) posting_method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			SetSessionBufferSize__Task_* task = tcps_NewEx(SetSessionBufferSize__Task_, (
							*this,
							recvBufBytes_wrap,
							sendBufBytes_wrap
							));
			VERIFY(InterlockedIncrement(&m_asyncTaskStat.totalAsyncTasks) > 0);
			FetchTaskPool()->Push(task);
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	TCPSError errUpdate = UpdateMethodMatchingFlag_();
	if(TCPS_OK != errUpdate)
		return errUpdate;
	if(!m_methodMatchingFlag.matching_SetSessionBufferSize_)
		return TCPS_ERR_METHOD_NOT_MATCH;

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 31;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::SetSessionBufferSize_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN INT32 recvBufBytes
	Put_BaseType_(&m_dataOutfiter, recvBufBytes_wrap);

	// IN INT32 sendBufBytes
	Put_BaseType_(&m_dataOutfiter, sendBufBytes_wrap);

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		if(m_UDPCallbackProxy.isUsing_)
		{
			int total = SockTotalizeWriteBufVec(reqBufVec, reqBufVecCount);
			BYTE* p = (BYTE*)tcps_Alloc(total);
			if(NULL == p)
			{
				ASSERT(false);
				return TCPS_ERR_OUT_OF_MEMORY;
			}
			BYTE* q = p;
			for(int i=0; i<reqBufVecCount; ++i)
			{
				const SockWriteBuf& swb = reqBufVec[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT((int)(q-p) == total);
			SockWriteBuf swb_udp;
			swb_udp.data = p;
			swb_udp.len = total;
			INT32 sessionID;
			m_rpcRequester->GetPeerSessionKey(sessionID);
			iscm_IUDPServeMan& udpServer = iscm_FetchUDPServeMan();
			udpServer.SendSessionData(sessionID, &swb_udp, 1);
		}
		else if(0 != m_postingProxy.callerKey_)
		{
			INT_PTR queueFullIndexes = -1;
			INT_PTR queueFullCount = 0;
			TCPSError err = iscm_FetchPostingCallerMan().BatchPosting(&m_postingProxy.callerKey_, 1, reqBufVec, reqBufVecCount, &queueFullIndexes, &queueFullCount);
			if(TCPS_OK != err)
				return err;
			ASSERT(0==queueFullCount || 1==queueFullCount);
			if(1 == queueFullCount)
				return TCPS_ERR_POSTING_PENDING_FULL;
		}
		else
		{
			TCPSError err = m_rpcRequester->Post(RPCCT_RPC, reqBufVec, reqBufVecCount);
			if(TCPS_OK != err)
				return err;
		}
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::MethodCheck_(
				IN const tcps_Array<tcps_String>& methods_wrap,
				IN const tcps_Array<tcps_String>& methodTypeInfos_wrap,
				OUT tcps_Array<BOOL>& matchingFlags_wrap
				) method
{
	iscm_ClientCallType iscm_cct_ = iscm_cct_invalid;
	if(m_callingOutTIDs.HasFlag(OSThreadSelf(), &iscm_cct_))
	{
		if(iscm_cct_OnClose == iscm_cct_)
			return TCPS_ERR_EXITING;
		if(iscm_cct_callback==iscm_cct_ || iscm_cct_posting_callback==iscm_cct_)
		{
			NPR_ASSERT_EX(false, _T("在回调函数里调用会话自身的同步方法，可能导致死锁！"));
			return TCPS_OK;
		}
	}

	iscm_IRequester::AutoBeginCallEx locker(m_rpcRequester);
	ASSERT(0 == m_dataOutfiter.bufs_.size());

	DataOutfiter::AutoClear outfiter_AutoClear(m_dataOutfiter);

	// 填充基本类型数据到outfiter
	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 1;
	peerCallFlags.dummy_15 = 0;
	m_dataOutfiter.Push(&peerCallFlags, sizeof(peerCallFlags));

	INT32 call_id_len = 22;
	m_dataOutfiter.Push(&call_id_len, sizeof(INT32));
	m_dataOutfiter.Push("PCC_User::MethodCheck_", call_id_len+1);

	// 填充IN参数到outfiter

	// IN tcps_Array<tcps_String> methods
	Put_BaseType_(&m_dataOutfiter, methods_wrap.LenRef());
	for(int idx1=0; idx1<methods_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = methods_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// IN tcps_Array<tcps_String> methodTypeInfos
	Put_BaseType_(&m_dataOutfiter, methodTypeInfos_wrap.LenRef());
	for(int idx1=0; idx1<methodTypeInfos_wrap.Length(); ++idx1)
	{
		const tcps_String& ref1 = methodTypeInfos_wrap[idx1];
		Put_String_(&m_dataOutfiter, ref1.Get(), ref1.LenRef());
	}

	// 调用RPCCall()
	{
		const SockWriteBuf* reqBufVec = m_dataOutfiter.bufs_.Get();
		int reqBufVecCount = (int)m_dataOutfiter.bufs_.size();
		int replyBytes = 0;
		TCPSError err = m_rpcRequester->CallEx(RPCCT_RPC, reqBufVec, reqBufVecCount, replyBytes);
		if(TCPS_OK != err)
			return err;

		iscm_IRequester* iscm_replied_picker = m_rpcRequester;

		iscm_RPCReplyPrefix replyPrefix;
		PICK_BASETYPE_(iscm_replied_picker, replyPrefix);
		INT32 array_len;
		(void)array_len; // avoid warning.

		// OUT tcps_Array<BOOL> matchingFlags
		PICK_PODARRAY_(iscm_replied_picker, matchingFlags_wrap);
	}
	return TCPS_OK;
}

TCPSError PCC_User_RC::Wrap_CallbackCheck_(
				IN PCC_User_RC* thisObj /*= NULL*/,
				IN PCC_User* faceObj /*= NULL*/,
				IN iscm_PeerCallFlags peerCallFlags,
				IN OUT const BYTE*& ptrInParams,
				IN OUT INT_PTR& ptrInParamsLen,
				OUT iscm_IRPCOutfiter* outfiter
				) callback
{
	ASSERT((NULL==thisObj) != (NULL==faceObj));
	(void)ptrInParams; (void)ptrInParamsLen; (void)outfiter; // avoid warning.
	TCPSError errTcps = TCPS_ERROR;

	// 从ptrInParams中分析出输入参数
	INT32 array_len;
	(void)array_len; // avoid warning.
	(void)peerCallFlags;

	// IN tcps_Array<tcps_String> callbacks
	IN tcps_Array<tcps_String> callbacks_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	callbacks_wrap.Resize(array_len);
	for(int idx1=0; idx1<callbacks_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = callbacks_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	// IN tcps_Array<tcps_String> callbackTypeInfos
	IN tcps_Array<tcps_String> callbackTypeInfos_wrap;
	GET_BASETYPE_EX_(thisObj, ptrInParams, ptrInParamsLen, array_len);
	callbackTypeInfos_wrap.Resize(array_len);
	for(int idx1=0; idx1<callbackTypeInfos_wrap.Length(); ++idx1)
	{
		tcps_String& ref1 = callbackTypeInfos_wrap[idx1];
		GET_STRING_EX_(thisObj, ptrInParams, ptrInParamsLen, ref1);
	}

	if(0 != ptrInParamsLen)
	{
		// NPLogError(("PCC_User::CallbackCheck_() callback, Malformed request"));
		if(thisObj)
			thisObj->OnNetworkMalformed_();
		return TCPS_ERR_MALFORMED_REQ;
	}

	// 定义输出参数
	struct OutParamWrapSite
	{
		iscm_RPCReplyPrefix replyPrefix_iscm;
		OUT tcps_Array<BOOL> matchingFlags;
		OutParamWrapSite() { replyPrefix_iscm.Init(); }
		~OutParamWrapSite() { }
		static void FreeAction(void* p)
		{
			OutParamWrapSite* ptr = (OutParamWrapSite*)((BYTE*)p - offset_of(OutParamWrapSite, replyPrefix_iscm));
			ptr->~OutParamWrapSite();
			tcps_Free(ptr);
		}
	};
	OutParamWrapSite* opWrapper = NULL;
	if(outfiter) // 非posting call
		opWrapper = tcps_New(OutParamWrapSite);
	else
		ASSERT(true); // posting call

	// 调用用户实现的回调函数
	try
	{
		if(thisObj)
		{
			iscm_ClientThreadIDs::AutoThisTID autoCallingFlag(thisObj->m_callingOutTIDs, iscm_cct_callback);
			errTcps = thisObj->CallbackCheck_(
				callbacks_wrap,
				callbackTypeInfos_wrap,
				opWrapper->matchingFlags
				);
		}
		else
		{
			(void)faceObj;
			ASSERT(false);
			errTcps = TCPS_ERR_INTERNAL_BUG;
		}
	}
	catch(TCPSError ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = ret;
	}
	catch(int ret)
	{
		ASSERT(TCPS_OK != ret);
		errTcps = (TCPSError)ret;
	}
	catch(std::bad_alloc)
	{
		errTcps = TCPS_ERR_OUT_OF_MEMORY;
	}
	ISCM_BEGIN_CATCH_ALL_()
		errTcps = TCPS_ERR_UNKNOWN_EXCEPTION;
	ISCM_END_CATCH_ALL_()

	if(TCPS_OK != errTcps)
	{
		if(opWrapper)
			OutParamWrapSite::FreeAction(opWrapper);
		return errTcps;
	}

	// 填充OUT数据到outfiter
	if(opWrapper)
	{
		// FreeAction()负责对所有out数据在网络发送完成后进行析构清理工作
		Set_BaseType_(outfiter, opWrapper->replyPrefix_iscm, OutParamWrapSite::FreeAction);
	}

	// OUT tcps_Array<BOOL> matchingFlags
	OUT const tcps_Array<BOOL>& matchingFlags_wrap = opWrapper->matchingFlags;
	Set_PODArray_(outfiter, matchingFlags_wrap);

	return TCPS_OK;
}

PCC_User::PCC_User(BOOL initNetworkSingletons /*= true*/)
	: m_faceR(NULL), m_faceL(NULL), m_callSiteL(NULL)
	, m_closingTID(INVALID_OSTHREADID)
	, m_connectTimeout(INFINITE), m_recvTimeout(INFINITE), m_sendTimeout(INFINITE)
	, m_streamedCallbackMap_IsInited(false)
{
	m_base_v_tab_ptr = m_derived_v_tab_ptr = *(LPVOID*)this;
	if(initNetworkSingletons)
		iscm_InitClientSingletons(true, true);
	else
		iscm_InitClientSingletons(false, false);
	PCC_User_RC::GetCallbackMap_();
}

PCC_User::~PCC_User()
{
	BOOL isNotDerived = (m_base_v_tab_ptr == m_derived_v_tab_ptr);
	NPR_ASSERT_EX(isNotDerived || (NULL==m_faceR && NULL==m_faceL), "请在最终派生类的析构函数的最后调用一次DestroyRequester()");
	DestroyRequester();
	if(m_callSiteL)
		tcps_Delete(m_callSiteL);
}

void PCC_User::DestroyRequester_(
				IN BOOL byLocalPeer
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);

	CAutoObj<AutoFlag<OSThreadID> > autoClosingTID;
	if(!byLocalPeer)
		ConstructAutoObj(AutoFlag<OSThreadID>, autoClosingTID, (m_closingTID, OSThreadSelf()));

	if(m_faceR)
	{
		tcps_Delete(m_faceR);
		m_faceR = NULL;
	}
	else if(m_faceL)
	{
		if(INVALID_OSTHREADID==m_closingTID || OSThreadSelf()!=m_closingTID)
			this->OnPeerBroken();
		this->OnClose();
		m_faceL->DeleteThis();
		m_faceL = NULL;
		if(m_callSiteL)
			m_callSiteL->Reset();
		m_localServeIPP = INVALID_IPP;
	}
}

void PCC_User::DestroyRequester()
{
	DestroyRequester_(false);
}

TCPSError PCC_User::SetServeIPP_(
				IN BOOL byLocalPeer,
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	CNPAutoLock locker(m_lock);
	m_derived_v_tab_ptr = *(LPVOID*)this;
	ASSERT(NULL==m_faceR || NULL==m_faceL);

	if(m_localMakingFlag.making)
	{
		if(serveIPP.IsValid())
		{
			ASSERT(false);
			return TCPS_ERR_EXTERNAL_BUG;
		}
		m_localMakingFlag.failed = true;
		return TCPS_OK;
	}

	if(m_faceL && m_localServeIPP==serveIPP)
		return TCPS_OK;

	if(serveIPP.IsValid() && iscm_IsRegisteredServe(serveIPP))
	{
		DestroyRequester_(byLocalPeer);

		ASSERT(!m_localMakingFlag.making && !m_localMakingFlag.failed);
		AutoFlag<BOOL> autoFlag(m_localMakingFlag.making, true);
		FinalAssign<BOOL> finalAssign(m_localMakingFlag.failed, false);

		union
		{
		PCC_CenterSessionMaker* sessionMaker;
		void* dummyUnionPtr;
		};
		sessionMaker = NULL;
		FNMakeLocalSession_PCC_User fnMake =
					(FNMakeLocalSession_PCC_User)iscm_GetRegisteredFunction(
						serveIPP,
						"MakeLocalSession_PCC_User",
						&dummyUnionPtr
						);
		if(NULL == fnMake)
			return TCPS_ERR_INVALID_INTERFACE;

		ASSERT(sessionMaker);
		TCPSError err = fnMake(clientID_IPP, *sessionMaker, m_faceL, this);
		if(TCPS_OK==err && m_localMakingFlag.failed)
		{
			ASSERT(m_faceL);
			m_faceL->DeleteThis();
			m_faceL = NULL;
			err = TCPS_ERR_CONNECT_FAILED;
		}
		if(TCPS_OK != err)
		{
			ASSERT(NULL == m_faceL);
			return err;
		}
		if(m_callSiteL)
			m_callSiteL->needUpdateFlags = true;

		ASSERT(m_faceL);
		err = this->OnConnected();
		if(TCPS_OK==err && m_localMakingFlag.failed)
			err = TCPS_ERR_CONNECT_FAILED;
		if(TCPS_OK != err)
		{
			if(INVALID_OSTHREADID==m_closingTID || OSThreadSelf()!=m_closingTID)
				this->OnPeerBroken();
			this->OnClose();
			m_faceL->DeleteThis();
			m_faceL = NULL;
			return err;
		}
		m_localServeIPP = serveIPP;
		return TCPS_OK;
	}

	if(m_faceL)
		DestroyRequester_(byLocalPeer);
	if(NULL == m_faceR)
	{
		if(!serveIPP.IsValid())
			return TCPS_OK;
		m_faceR = tcps_NewEx(PCC_User_RC, (this));
	}

	if(INFINITE!=m_connectTimeout || INFINITE!=m_recvTimeout || INFINITE!=m_sendTimeout)
		m_faceR->SetTimeout(m_connectTimeout, m_recvTimeout, m_sendTimeout);
	if(!m_sockRecvSendBufParam.IsDefault())
		m_faceR->SetSessionBufferSize(m_sockRecvSendBufParam.recvBufBytes_, m_sockRecvSendBufParam.sendBufBytes_);
	if(!m_postingPendingParam.IsDefault())
		m_faceR->SetPostingPendingParameters(m_postingPendingParam.maxPendingBytes_, m_postingPendingParam.maxPendings_);
	return m_faceR->SetServeIPP(
						serveIPP,
						sessionFlags,
						clientID_IPP,
						secondaryServeIPP,
						tertiaryServeIPP,
						reconnectIntervalMSELs
						);
}

TCPSError PCC_User::SetServeIPP(
				IN const IPP& serveIPP,
				IN DWORD sessionFlags /*= 0*/,
				IN const IPP& clientID_IPP /*= INVALID_IPP*/,
				IN const IPP& secondaryServeIPP /*= INVALID_IPP*/,
				IN const IPP& tertiaryServeIPP /*= INVALID_IPP*/,
				IN DWORD reconnectIntervalMSELs /*= 2000*/
				)
{
	CNPAutoLock locker(m_lock);
	AutoFlag<OSThreadID> autoClosingTID(m_closingTID, OSThreadSelf());
	return SetServeIPP_(false, serveIPP, sessionFlags, clientID_IPP, secondaryServeIPP, tertiaryServeIPP, reconnectIntervalMSELs);
}

IPP PCC_User::GetServeIPP() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->GetServeIPP();
	else if(m_faceL)
		return m_localServeIPP;
	return INVALID_IPP;
}

IPP PCC_User::GetServingIPP() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->GetServingIPP();
	else if(m_faceL)
		return m_localServeIPP;
	return INVALID_IPP;
}

BOOL PCC_User::IsConnected() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->IsConnected();
	else if(m_faceL)
		return true;
	return false;
}

void PCC_User::SetKeeping(
				IN BOOL keeping
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetKeeping(keeping);
}

BOOL PCC_User::IsKeeping() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		return m_faceR->IsKeeping();
	return false;
}

BOOL PCC_User::IsLocalPeer() const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	return (NULL != m_faceL);
}

void PCC_User::PrepareDisconnect()
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->PrepareDisconnect();
}

void PCC_User::SetTimeout(
				IN DWORD connectTimeout /*= INFINITE*/,
				IN DWORD recvTimeout /*= INFINITE*/,
				IN DWORD sendTimeout /*= INFINITE*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetTimeout(connectTimeout, recvTimeout, sendTimeout);
	m_connectTimeout = connectTimeout;
	m_recvTimeout = recvTimeout;
	m_sendTimeout = sendTimeout;
}

void PCC_User::GetTimeout(
				OUT DWORD* connectTimeout /*= NULL*/,
				OUT DWORD* recvTimeout /*= NULL*/,
				OUT DWORD* sendTimeout /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		m_faceR->GetTimeout(connectTimeout, recvTimeout, sendTimeout);
		return;
	}
	if(connectTimeout)
		*connectTimeout = m_connectTimeout;
	if(recvTimeout)
		*recvTimeout = m_recvTimeout;
	if(sendTimeout)
		*sendTimeout = m_sendTimeout;
}

void PCC_User::SetSessionBufferSize(
				IN INT32 recvBufBytes /*= -1*/,
				IN INT32 sendBufBytes /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetSessionBufferSize(recvBufBytes, sendBufBytes);
	m_sockRecvSendBufParam.Set(recvBufBytes, sendBufBytes);
}

void PCC_User::GetSessionBufferSize(
				OUT INT32* recvBufBytes /*= NULL*/,
				OUT INT32* sendBufBytes /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_sockRecvSendBufParam.Get(recvBufBytes, sendBufBytes);
}

void PCC_User::SetPostingPendingParameters(
				IN INT32 maxPendingBytes /*= -1*/,
				IN INT32 maxPendings /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
		m_faceR->SetPostingPendingParameters(maxPendingBytes, maxPendings);
	m_postingPendingParam.Set(maxPendingBytes, maxPendings);
}

void PCC_User::GetPostingPendingParameters(
				OUT INT32* maxPendingBytes /*= NULL*/,
				OUT INT32* maxPendings /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_postingPendingParam.Get(maxPendingBytes, maxPendings);
}

void PCC_User::SetPostingSendParameters(
				IN INT32 maxSendingBytes /*= -1*/,
				IN INT32 maxSendings /*= -1*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR && 0!=m_faceR->m_postingProxy.callerKey_)
		iscm_FetchPostingCallerMan().SetBufferingParam(m_faceR->m_postingProxy.callerKey_, maxSendingBytes, maxSendings);
	m_postingSendParam.Set(maxSendingBytes, maxSendings);
}

void PCC_User::GetPostingSendParameters(
				OUT INT32* maxSendingBytes /*= NULL*/,
				OUT INT32* maxSendings /*= NULL*/
				) const
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	m_postingSendParam.Get(maxSendingBytes, maxSendings);
}

TCPSError PCC_User::CleanPostingSendingQueue()
{
	if(NULL==m_faceR || 0==m_faceR->m_postingProxy.callerKey_)
		return TCPS_ERR_CALL_WAS_IGNORED;
	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(&m_faceR->m_postingProxy.callerKey_, 1);
}

TCPSError PCC_User::CleanPostingSendingQueue(
				IN const PPCC_User_* clients,
				IN INT_PTR clientsCount
				)
{
	tcps_SmartArray<PPCC_User_, 256> clients_ar_;
	for(INT_PTR i=0; i<clientsCount; ++i)
	{
		if(NULL == clients[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(NULL==clients[i]->m_faceR || 0==clients[i]->m_faceR->m_postingProxy.callerKey_)
			continue;
		clients_ar_.push_back(clients[i]);
	}
	if(0 == clients_ar_.size())
		return TCPS_OK;

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> callerKey_ar_;
	callerKey_ar_.resize(clients_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)clients_ar_.size(); ++i)
		callerKey_ar_[i] = clients_ar_[i]->m_faceR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	return callerMan.BatchCleanQueue(callerKey_ar_.Get(), callerKey_ar_.size());
}

const PCC_User::MethodMatchingFlag& PCC_User::GetMethodMatchingFlag(
				OUT TCPSError* err /*= NULL*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->GetMethodMatchingFlag(err);
	}
	else if(m_faceL)
	{
		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		if(m_callSiteL->needUpdateFlags)
		{
			InitializeAllCallsTypeInfo_();
			m_callSiteL->matchingFlags.matching_GetPccProperty = (NULL != m_faceL->FindMethod_("GetPccProperty", 14, s_PCC_User_GetPccProperty_TypeInfo_, s_PCC_User_GetPccProperty_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_ListNodes = (NULL != m_faceL->FindMethod_("ListNodes", 9, s_PCC_User_ListNodes_TypeInfo_, s_PCC_User_ListNodes_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_GetNodeDynamicContext = (NULL != m_faceL->FindMethod_("GetNodeDynamicContext", 21, s_PCC_User_GetNodeDynamicContext_TypeInfo_, s_PCC_User_GetNodeDynamicContext_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_ListModules = (NULL != m_faceL->FindMethod_("ListModules", 11, s_PCC_User_ListModules_TypeInfo_, s_PCC_User_ListModules_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_Execute = (NULL != m_faceL->FindMethod_("Execute", 7, s_PCC_User_Execute_TypeInfo_, s_PCC_User_Execute_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_QueryJobs = (NULL != m_faceL->FindMethod_("QueryJobs", 9, s_PCC_User_QueryJobs_TypeInfo_, s_PCC_User_QueryJobs_TypeInfo_len_));
			m_callSiteL->matchingFlags.matching_CancelJob = (NULL != m_faceL->FindMethod_("CancelJob", 9, s_PCC_User_CancelJob_TypeInfo_, s_PCC_User_CancelJob_TypeInfo_len_));
			m_callSiteL->needUpdateFlags = false;
		}
		if(err)
			*err = TCPS_OK;
		return m_callSiteL->matchingFlags;
	}

	static MethodMatchingFlag const defaultFlags;
	if(err)
		*err = TCPS_ERR_NEED_SERVE_IPP;
	return defaultFlags;
}

TCPSError PCC_User::GetStreamedMethodTypeInfo_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				OUT char*& typeInfo,
				OUT INT_PTR& infoLen
				) const
{
	InitializeAllCallsTypeInfo_();
	typedef CQuickStringMap<CPtrStrA, CPtrStrA, QSS_Traits<7> > MethodMap_;
	static MethodMap_* s_mMap = NULL;
	if(NULL == s_mMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_mMap)
		{
			static MethodMap_ s_mMapObj;
			MethodMap_& mMap = s_mMapObj;
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetPccProperty"), CPtrStrA(s_PCC_User_GetPccProperty_TypeInfo_, s_PCC_User_GetPccProperty_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListNodes"), CPtrStrA(s_PCC_User_ListNodes_TypeInfo_, s_PCC_User_ListNodes_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("GetNodeDynamicContext"), CPtrStrA(s_PCC_User_GetNodeDynamicContext_TypeInfo_, s_PCC_User_GetNodeDynamicContext_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("ListModules"), CPtrStrA(s_PCC_User_ListModules_TypeInfo_, s_PCC_User_ListModules_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("Execute"), CPtrStrA(s_PCC_User_Execute_TypeInfo_, s_PCC_User_Execute_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("QueryJobs"), CPtrStrA(s_PCC_User_QueryJobs_TypeInfo_, s_PCC_User_QueryJobs_TypeInfo_len_))).second);
			VERIFY(mMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("CancelJob"), CPtrStrA(s_PCC_User_CancelJob_TypeInfo_, s_PCC_User_CancelJob_TypeInfo_len_))).second);
			s_mMap = &mMap;
		}
	}
	MethodMap_::iterator it = s_mMap->find(methodName, nameLen);
	if(it == s_mMap->end())
		return TCPS_ERR_METHOD_NOT_MATCH;
	infoLen = it->second.GetLength();
	typeInfo = (char*)tcps_Alloc(infoLen+1);
	StrAssign(typeInfo, it->second);
	return TCPS_OK;
}

TCPSError PCC_User::StreamedCall_(
				IN const char* methodName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	if(m_faceR)
	{
		return m_faceR->StreamedCall_(
					methodName, nameLen,
					data, dataLen,
					replyData, replyLen
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			return m_streamedCallSite.func(
						m_streamedCallSite.serverObj, m_streamedCallSite.sessionObj,
						"PCC_User", methodName,
						data, dataLen,
						replyData, replyLen
						);
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnOnStreamedCall_L_;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("OnStreamedCall_L_", -1, NULL, 0);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_User_LocalMethod::FN_OnStreamedCall_L_)methodFuncL)(
					m_faceL,
					methodName, nameLen,
					data, dataLen,
					replyData, replyLen
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

BOOL PCC_User::IsStreamedCallbackMatched_(
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/
				)
{
	if(m_streamedCallbackMap_IsInited)
	{
		StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
		if(it == m_streamedCallbackMap.end())
			return false;
		return it->second;
	}

	CNPAutoLock locker(m_lock);

	if(m_streamedCallbackMap_IsInited)
	{
		StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
		if(it == m_streamedCallbackMap.end())
			return false;
		return it->second;
	}

	ASSERT(0 == m_streamedCallbackMap.size());

	InitializeAllCallsTypeInfo_();
	BOOL matched;
	TCPSError err;
	char* typeInfo;
	INT_PTR infoLen;
	(void)matched; (void)err; (void)typeInfo; (void)infoLen;

	typeInfo = NULL;
	infoLen = 0;
	err = this->GetStreamedCallbackTypeInfo_("OnExecuted", 10, typeInfo, infoLen);
	matched = (TCPS_OK==err && s_PCC_User_OnExecuted_TypeInfo_len_==infoLen && 0==strncmp(s_PCC_User_OnExecuted_TypeInfo_, typeInfo, infoLen));
	VERIFY(m_streamedCallbackMap.insert(std::make_pair(CPtrStrA("OnExecuted", 10), matched)).second);
	if(typeInfo)
		tcps_Free(typeInfo);

	typeInfo = NULL;
	infoLen = 0;
	err = this->GetStreamedCallbackTypeInfo_("OnExecuted1", 11, typeInfo, infoLen);
	matched = (TCPS_OK==err && s_PCC_User_OnExecuted1_TypeInfo_len_==infoLen && 0==strncmp(s_PCC_User_OnExecuted1_TypeInfo_, typeInfo, infoLen));
	VERIFY(m_streamedCallbackMap.insert(std::make_pair(CPtrStrA("OnExecuted1", 11), matched)).second);
	if(typeInfo)
		tcps_Free(typeInfo);

	m_streamedCallbackMap_IsInited = true;
	StreamedCallbackMap::iterator it = m_streamedCallbackMap.find(callbackName, nameLen);
	if(it == m_streamedCallbackMap.end())
		return false;
	return it->second;
}

TCPSError PCC_User::GetPccProperty(
				OUT PCCProperty& pccProp_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->GetPccProperty(
					pccProp_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_User",
						"GetPccProperty",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(pccProp_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnGetPccProperty;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("GetPccProperty", 14, s_PCC_User_GetPccProperty_TypeInfo_, s_PCC_User_GetPccProperty_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_User_LocalMethod::FN_GetPccProperty)methodFuncL)(
					m_faceL,
					pccProp_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_User::ListNodes(
				OUT tcps_Array<PCC_NodeDesc>& nodes_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->ListNodes(
					nodes_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_User",
						"ListNodes",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(nodes_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnListNodes;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("ListNodes", 9, s_PCC_User_ListNodes_TypeInfo_, s_PCC_User_ListNodes_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_User_LocalMethod::FN_ListNodes)methodFuncL)(
					m_faceL,
					nodes_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_User::GetNodeDynamicContext(
				IN const char* nodeName_wrap, IN INT32 nodeName_wrap_len /*= -1*/,
				OUT PCC_DynamicContext& dynamicContext_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->GetNodeDynamicContext(
					nodeName_wrap, nodeName_wrap_len,
					dynamicContext_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String nodeName_tmp_wrap;
			nodeName_tmp_wrap.Attach(xat_bind, (char*)nodeName_wrap, nodeName_wrap_len);
			inParamsLen += iscm_GetStreamedSize(nodeName_tmp_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, nodeName_tmp_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_User",
						"GetNodeDynamicContext",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(dynamicContext_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnGetNodeDynamicContext;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("GetNodeDynamicContext", 21, s_PCC_User_GetNodeDynamicContext_TypeInfo_, s_PCC_User_GetNodeDynamicContext_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_User_LocalMethod::FN_GetNodeDynamicContext)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)nodeName_wrap, nodeName_wrap_len),
					dynamicContext_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_User::ListModules(
				IN const char* regex_wrap, IN INT32 regex_wrap_len /*= -1*/,
				OUT tcps_Array<PCC_ModuleInfo>& modulesInfo_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->ListModules(
					regex_wrap, regex_wrap_len,
					modulesInfo_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			tcps_String regex_tmp_wrap;
			regex_tmp_wrap.Attach(xat_bind, (char*)regex_wrap, regex_wrap_len);
			inParamsLen += iscm_GetStreamedSize(regex_tmp_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, regex_tmp_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_User",
						"ListModules",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(modulesInfo_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnListModules;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("ListModules", 11, s_PCC_User_ListModules_TypeInfo_, s_PCC_User_ListModules_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_User_LocalMethod::FN_ListModules)methodFuncL)(
					m_faceL,
					tcps_String(xat_bind, (char*)regex_wrap, regex_wrap_len),
					modulesInfo_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_User::Execute(
				IN INT64 moduleKey_wrap,
				IN const char* inputUrl_wrap, IN INT32 inputUrl_wrap_len /*= -1*/,
				IN const char* outputUrl_wrap, IN INT32 outputUrl_wrap_len /*= -1*/,
				IN const void* moduleParams_wrap, IN INT32 moduleParams_wrap_len,
				OUT INT64& jobKey_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->Execute(
					moduleKey_wrap,
					inputUrl_wrap, inputUrl_wrap_len,
					outputUrl_wrap, outputUrl_wrap_len,
					moduleParams_wrap, moduleParams_wrap_len,
					jobKey_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			inParamsLen += sizeof(moduleKey_wrap);
			tcps_String inputUrl_tmp_wrap;
			inputUrl_tmp_wrap.Attach(xat_bind, (char*)inputUrl_wrap, inputUrl_wrap_len);
			inParamsLen += iscm_GetStreamedSize(inputUrl_tmp_wrap);
			tcps_String outputUrl_tmp_wrap;
			outputUrl_tmp_wrap.Attach(xat_bind, (char*)outputUrl_wrap, outputUrl_wrap_len);
			inParamsLen += iscm_GetStreamedSize(outputUrl_tmp_wrap);
			tcps_Binary moduleParams_tmp_wrap;
			moduleParams_tmp_wrap.Attach(xat_bind, (void*)moduleParams_wrap, moduleParams_wrap_len);
			inParamsLen += iscm_GetStreamedSize(moduleParams_tmp_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, moduleKey_wrap);
			iscm_StreamedStore(pInParamsBuf, inputUrl_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, outputUrl_tmp_wrap);
			iscm_StreamedStore(pInParamsBuf, moduleParams_tmp_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_User",
						"Execute",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(jobKey_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnExecute;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("Execute", 7, s_PCC_User_Execute_TypeInfo_, s_PCC_User_Execute_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_User_LocalMethod::FN_Execute)methodFuncL)(
					m_faceL,
					moduleKey_wrap,
					tcps_String(xat_bind, (char*)inputUrl_wrap, inputUrl_wrap_len),
					tcps_String(xat_bind, (char*)outputUrl_wrap, outputUrl_wrap_len),
					tcps_Binary(xat_bind, (BYTE*)moduleParams_wrap, moduleParams_wrap_len),
					jobKey_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_User::QueryJobs(
				IN const tcps_Array<INT64>& jobsKey_wrap,
				OUT tcps_Array<ExecuteState>& jobsState_wrap
				) method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->QueryJobs(
					jobsKey_wrap,
					jobsState_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			inParamsLen += iscm_GetStreamedSize(jobsKey_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, jobsKey_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_User",
						"QueryJobs",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			iscm_StreamedLoad(jobsState_wrap, pReplyData);
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnQueryJobs;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("QueryJobs", 9, s_PCC_User_QueryJobs_TypeInfo_, s_PCC_User_QueryJobs_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_User_LocalMethod::FN_QueryJobs)methodFuncL)(
					m_faceL,
					jobsKey_wrap,
					jobsState_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_User::CancelJob(
				IN INT64 jobKey_wrap
				) posting_method
{
	ASSERT(NULL==m_faceR || NULL==m_faceL);
	if(m_faceR)
	{
		return m_faceR->CancelJob(
					jobKey_wrap
					);
	}
	else if(m_faceL)
	{
		if(m_streamedCallSite.func)
		{
			// 计算输入参数长度
			INT_PTR inParamsLen = 0;
			(void)inParamsLen;
			inParamsLen += sizeof(jobKey_wrap);

			// 拷贝输入参数到inParamsBuf
			tcps_Binary inParamsBuf;
			if(!inParamsBuf.Resize(inParamsLen))
				return TCPS_ERR_OUT_OF_MEMORY;
			BYTE* pInParamsBuf = inParamsBuf.Get();
			(void)pInParamsBuf;
			iscm_StreamedStore(pInParamsBuf, jobKey_wrap);
			ASSERT(pInParamsBuf-inParamsBuf.Get() == inParamsLen);

			// 调用外部流式方法处理函数
			void* replyData = NULL;
			INT_PTR replyLen = 0;
			TCPSError err = m_streamedCallSite.func(
						m_streamedCallSite.serverObj,
						m_streamedCallSite.sessionObj,
						"PCC_User",
						"CancelJob",
						inParamsBuf.Get(),
						inParamsLen,
						&replyData,
						&replyLen
						);
			tcps_Binary autoFreeReplyData;
			if(replyData)
				autoFreeReplyData.Attach(xat_hold, replyData, replyLen);
			if(TCPS_OK != err)
				return err;

			// 解析返回参数
			const BYTE* pReplyData = (const BYTE*)replyData;
			(void)pReplyData;
			ASSERT(pReplyData-(const BYTE*)replyData == replyLen);
			return TCPS_OK;
		}

		if(NULL == m_callSiteL)
		{
			CNPAutoLock locker(m_lock);
			if(NULL == m_callSiteL)
				m_callSiteL = tcps_New(CallSiteL_);
		}
		PROC& methodFuncL = m_callSiteL->fnCancelJob;
		if(NULL == methodFuncL)
		{
			InitializeAllCallsTypeInfo_();
			methodFuncL = m_faceL->FindMethod_("CancelJob", 9, s_PCC_User_CancelJob_TypeInfo_, s_PCC_User_CancelJob_TypeInfo_len_);
			if(NULL == methodFuncL)
				return TCPS_ERR_METHOD_NOT_MATCH;
		}
		return ((IPCC_User_LocalMethod::FN_CancelJob)methodFuncL)(
					m_faceL,
					jobKey_wrap
					);
	}
	else
		return TCPS_ERR_NEED_SERVE_IPP;
}

TCPSError PCC_User::CancelJob_Batch(
				IN const PPCC_User_* wrap_clients,
				IN INT_PTR wrap_clientsCount,
				IN INT64 jobKey_wrap,
				OUT PPCC_User_* wrap_sendFaileds /*= NULL*/,
				OUT INT_PTR* wrap_failedCount /*= NULL*/
				) posting_method
{
	if(wrap_failedCount)
		*wrap_failedCount= 0;

	if(NULL==wrap_clients || wrap_clientsCount<=0)
	{
		ASSERT(false);
		return TCPS_ERR_INVALID_PARAM;
	}
	if((!!wrap_sendFaileds) != (!!wrap_failedCount))
	{
		ASSERT(false); // wrap_sendFaileds、wrap_failedCount要么都为NULL，要么都不为NULL
		return TCPS_ERR_INVALID_PARAM;
	}

	INT_PTR notReadies = 0;
	tcps_SmartArray<PPCC_User_, 256> iscm_clients_ar_;
	for(INT_PTR i=0; i<wrap_clientsCount; ++i)
	{
		if(NULL == wrap_clients[i])
		{
			ASSERT_EX(false, tcps_GetErrTxt(TCPS_ERR_INVALID_PARAM));
			continue;
		}
		if(wrap_clients[i]->m_faceL)
		{
			wrap_clients[i]->CancelJob(
					jobKey_wrap
					);
			continue;
		}
		if(TCPS_OK != wrap_clients[i]->m_faceR->UpdateMethodMatchingFlag_())
			continue;
		if(!wrap_clients[i]->m_faceR->m_methodMatchingFlag.matching_CancelJob)
		{
		//	IPP peerIPP = wrap_clients[i]->m_faceR->GetServingIPP();
		//	NPLogWarning(("The 'PCC_User::CancelJob()' of '%s' is not matched!", IPP_TO_STR_A(peerIPP)));
			continue;
		}
		if(0 == wrap_clients[i]->m_faceR->m_postingProxy.callerKey_)
		{
			if(wrap_sendFaileds)
			{
				wrap_sendFaileds[notReadies] = wrap_clients[i];
				++notReadies;
			}
			continue;
		}
		iscm_clients_ar_.push_back(wrap_clients[i]);
	}
	if(0 == iscm_clients_ar_.size())
		return TCPS_OK;

	// 准备调用数据
	tcps_SmartArray<SockWriteBuf, 256> iscm_swb_ar_;
	SockWriteBuf iscm_swb_;

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = 0;
	peerCallFlags.dummy_15 = 0;
	iscm_swb_.data = &peerCallFlags;
	iscm_swb_.len = sizeof(peerCallFlags);
	iscm_swb_ar_.push_back(iscm_swb_);

	INT32 call_id_len = 19;
	iscm_swb_.data = &call_id_len;
	iscm_swb_.len = sizeof(call_id_len);
	iscm_swb_ar_.push_back(iscm_swb_);
	iscm_swb_.data = "PCC_User::CancelJob";
	iscm_swb_.len = call_id_len+1;
	iscm_swb_ar_.push_back(iscm_swb_);

	// IN INT64 jobKey
	iscm_swb_.data = &jobKey_wrap;
	iscm_swb_.len = sizeof(jobKey_wrap);
	iscm_swb_ar_.push_back(iscm_swb_);

	// 准备callerKeys
	tcps_SmartArray<INT32, 256> iscm_callerKey_ar_;
	iscm_callerKey_ar_.resize(iscm_clients_ar_.size());
	for(INT_PTR i=0; i<(INT_PTR)iscm_clients_ar_.size(); ++i)
		iscm_callerKey_ar_[i] = iscm_clients_ar_[i]->m_faceR->m_postingProxy.callerKey_;

	iscm_IPostingCallerMan& callerMan = iscm_FetchPostingCallerMan();
	if(NULL == wrap_sendFaileds)
	{
		return callerMan.BatchPosting(
							iscm_callerKey_ar_.Get(),
							iscm_callerKey_ar_.size(),
							iscm_swb_ar_.Get(),
							iscm_swb_ar_.size(),
							NULL,
							NULL
							);
	}

	ASSERT(wrap_failedCount);
	tcps_SmartArray<INT_PTR, 256> iscm_queueFullIndexesAr;
	iscm_queueFullIndexesAr.resize(iscm_callerKey_ar_.size());
	TCPSError err = callerMan.BatchPosting(
						iscm_callerKey_ar_.Get(),
						iscm_callerKey_ar_.size(),
						iscm_swb_ar_.Get(),
						iscm_swb_ar_.size(),
						iscm_queueFullIndexesAr.Get(),
						wrap_failedCount
						);
	ASSERT(0<=*wrap_failedCount && *wrap_failedCount<=(INT_PTR)iscm_queueFullIndexesAr.size());
	for(INT_PTR i=0; i<*wrap_failedCount; ++i)
		(wrap_sendFaileds+notReadies)[i] = iscm_clients_ar_[iscm_queueFullIndexesAr[i]];
	*wrap_failedCount += notReadies;
	return err;
}

void PCC_User::OnNetworkMalformed_()
{
	if(m_faceR)
		m_faceR->OnNetworkMalformed_();
}

void PCC_User::CloseSession_()
{
	this->SetServeIPP_(true, INVALID_IPP);
}

PROC PCC_User::FindCallback_(
				IN const char* name,
				IN INT_PTR nameLen /*= -1*/,
				IN const char* type,
				IN INT_PTR typeLen /*= -1*/
				)
{
	if(NULL == name)
	{
		ASSERT(false);
		return NULL;
	}

	// 对OnStreamedCallback_L_()特殊处理
	if(nameLen<0 && 0==strcmp("OnStreamedCallback_L_", name))
		return (PROC)&OnStreamedCallback_L_;

	InitializeAllCallsTypeInfo_();
	typedef TwoItems<CPtrStrA, PROC> FuncPair;
	typedef CQuickStringMap<CPtrStrA, FuncPair, QSS_Traits<2> > CallbackMap_;
	static CallbackMap_* s_cbMap = NULL;
	if(NULL == s_cbMap)
	{
		IscmRPCGlobalLocker locker;
		if(NULL == s_cbMap)
		{
			static CallbackMap_ s_cbMapObj;
			CallbackMap_& cbMap = s_cbMapObj;
			cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("OnExecuted"), FuncPair(CPtrStrA(s_PCC_User_OnExecuted_TypeInfo_, s_PCC_User_OnExecuted_TypeInfo_len_), (PROC)&Local_OnExecuted)));
			cbMap.insert(std::make_pair(CONST_STR_TO_PTRSTR_A("OnExecuted1"), FuncPair(CPtrStrA(s_PCC_User_OnExecuted1_TypeInfo_, s_PCC_User_OnExecuted1_TypeInfo_len_), (PROC)&Local_OnExecuted1)));
			s_cbMap = &cbMap;
		}
	}

	CallbackMap_::iterator it = s_cbMap->find(name, nameLen);
	if(s_cbMap->end() == it)
		return NULL;
	const CPtrStrA& ps = it->second.first;
	if(0 != ps.Compare(type, typeLen))
		return NULL;
	return it->second.second;
}

TCPSError PCC_User::OnStreamedCallback_L_(
				IN void* sessionObj,
				IN const char* callbackName,
				IN INT_PTR nameLen /*= -1*/,
				IN const void* data /*= NULL*/,
				IN INT_PTR dataLen /*>= 0*/,
				OUT LPVOID* replyData /*= NULL*/,
				OUT INT_PTR* replyLen /*= NULL*/
				)
{
	if(replyData)
		*replyData = NULL;
	if(replyLen)
		*replyLen = 0;

	PCC_User* const pCC_UserObj = (PCC_User*)sessionObj;
	ASSERT(pCC_UserObj->m_faceL);
	if(nameLen < 0)
		nameLen = strlen(callbackName);

	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_UserObj->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_UserObj->IsStreamedCallbackMatched_(callbackName, nameLen))
			return TCPS_ERR_CALLBACK_NOT_MATCH;
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_UserObj->StreamedCallback_(callbackName, nameLen, data, dataLen, iscm_replyData, iscm_replyLen);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
		{
			if(replyData)
				*replyData = iscm_replyData;
			if(replyLen)
				*replyLen = iscm_replyLen;
			return err;
		}
	}

	INT_PTR call_id_len = 10+nameLen;
	CSmartBuf<char, 256> call_id_buf(call_id_len+1);
	char* const call_id = call_id_buf.Get();
	strncpy(call_id, "PCC_User::", 10);
	StrAssign(call_id+10, callbackName, nameLen);

	PCC_User_RC::InitCallbackMap_();
	ASSERT(PCC_User_RC::sm_callbackMap);
	PCC_User_RC::CallbackMap_::const_iterator cit = PCC_User_RC::sm_callbackMap->find(call_id, call_id_len);
	if(PCC_User_RC::sm_callbackMap->end() == cit)
		return TCPS_ERR_TRY_CALL_OTHER_METHODS; // 本接口不支持，尝试其它接口

	iscm_PeerCallFlags peerCallFlags;
	peerCallFlags.sizeofBOOL_req = (INT8)sizeof(BOOL);
	peerCallFlags.sizeofEnum_req = (INT8)sizeof(DummyEnumType);
	peerCallFlags.requireReply = !(cit->second.isPosting);
	peerCallFlags.dummy_15 = 0;
	const BYTE* ptrInParams = (const BYTE*)data;
	INT_PTR ptrInParamsLen = dataLen;
	if(peerCallFlags.requireReply)
	{
		iscm_RPCDataOutfiter outfiter;
		err = cit->second.handler(NULL, pCC_UserObj, peerCallFlags, ptrInParams, ptrInParamsLen, &outfiter);
		if(TCPS_OK != err)
			return err;
		// outfiter.swbBufs_[0]总指向iscm_RPCDataOutfiter::reply_
		// outfiter.swbBufs_[1]为iscm_RPCReplyPrefix replyPrefix
		ASSERT(outfiter.swbBufs_.size()==1 || outfiter.swbBufs_.size()>=2);
		if(outfiter.swbBufs_.size() >= 2)
		{
			ASSERT(replyData && replyLen);
			*replyLen = SockTotalizeWriteBufVec(outfiter.swbBufs_.Get()+2, outfiter.swbBufs_.size()-2);
			*replyData = tcps_Alloc(*replyLen);
			BYTE* q = (BYTE*)*replyData;
			for(INT_PTR i=2; i<(INT_PTR)outfiter.swbBufs_.size(); ++i)
			{
				const SockWriteBuf& swb = outfiter.swbBufs_[i];
				memcpy(q, swb.data, swb.len);
				q += swb.len;
			}
			ASSERT(q-(BYTE*)*replyData == *replyLen);
		}
	}
	else
	{
		err = cit->second.handler(NULL, pCC_UserObj, peerCallFlags, ptrInParams, ptrInParamsLen, NULL/*outfiter*/);
	}

	return err;
}

TCPSError PCC_User::Local_OnExecuted(
				IN void* sessionObj,
				IN INT64 jobKey_wrap,
				IN TCPSError errorCode_wrap,
				IN const tcps_Binary& context_wrap
				) posting_callback
{
	PCC_User* const pCC_UserObj_wrap = (PCC_User*)sessionObj;
	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_UserObj_wrap->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_UserObj_wrap->IsStreamedCallbackMatched_("OnExecuted", 10))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter dataOutfiter;

		// IN INT64 jobKey
		Put_BaseType_(&dataOutfiter, jobKey_wrap);

		// IN TCPSError errorCode
		Put_BaseType_(&dataOutfiter, errorCode_wrap);

		// IN tcps_Binary context
		Put_Binary_(&dataOutfiter, context_wrap.Get(), context_wrap.LenRef());

		ISCM_GAIN_TEMPORARY_CONTINUOUS_CALL_DATA(dataOutfiter.bufs_.Get(), dataOutfiter.bufs_.size(), iscm_data, iscm_dataLen);
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_UserObj_wrap->StreamedCallback_(
						"OnExecuted", 10,
						iscm_data, iscm_dataLen,
						iscm_replyData, iscm_replyLen
						);
		ASSERT(NULL==iscm_replyData && 0==iscm_replyLen);
		if(iscm_replyData)
			tcps_Free(iscm_replyData);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			return err;
		// 忽略返回TCPS_ERR_MALFORMED_REQ情况？？
	}

	return pCC_UserObj_wrap->OnExecuted(
					jobKey_wrap,
					errorCode_wrap,
					context_wrap
					);
}

TCPSError PCC_User::Local_OnExecuted1(
				IN void* sessionObj,
				IN INT64 jobKey_wrap,
				IN TCPSError errorCode_wrap,
				IN const tcps_Binary& context_wrap,
				IN const tcps_Array<tcps_Binary>& outArgs_wrap
				) posting_callback
{
	PCC_User* const pCC_UserObj_wrap = (PCC_User*)sessionObj;
	void* iscm_replyData = NULL;
	INT_PTR iscm_replyLen = 0;
	TCPSError err = pCC_UserObj_wrap->StreamedCallback_(NULL, 0, NULL, 0, iscm_replyData, iscm_replyLen);
	if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
	{
		if(!pCC_UserObj_wrap->IsStreamedCallbackMatched_("OnExecuted1", 11))
			return TCPS_ERR_CALLBACK_NOT_MATCH;

		DataOutfiter dataOutfiter;

		// IN INT64 jobKey
		Put_BaseType_(&dataOutfiter, jobKey_wrap);

		// IN TCPSError errorCode
		Put_BaseType_(&dataOutfiter, errorCode_wrap);

		// IN tcps_Binary context
		Put_Binary_(&dataOutfiter, context_wrap.Get(), context_wrap.LenRef());

		// IN tcps_Array<tcps_Binary> outArgs
		Put_BaseType_(&dataOutfiter, outArgs_wrap.LenRef());
		for(int idx2=0; idx2<outArgs_wrap.Length(); ++idx2)
		{
			const tcps_Binary& ref2 = outArgs_wrap[idx2];
			Put_Binary_(&dataOutfiter, ref2.Get(), ref2.LenRef());
		}

		ISCM_GAIN_TEMPORARY_CONTINUOUS_CALL_DATA(dataOutfiter.bufs_.Get(), dataOutfiter.bufs_.size(), iscm_data, iscm_dataLen);
		iscm_replyData = NULL;
		iscm_replyLen = 0;
		err = pCC_UserObj_wrap->StreamedCallback_(
						"OnExecuted1", 11,
						iscm_data, iscm_dataLen,
						iscm_replyData, iscm_replyLen
						);
		ASSERT(NULL==iscm_replyData && 0==iscm_replyLen);
		if(iscm_replyData)
			tcps_Free(iscm_replyData);
		if(TCPS_ERR_STREAMED_CALLBACK_NOT_IMPLEMENTED != err)
			return err;
		// 忽略返回TCPS_ERR_MALFORMED_REQ情况？？
	}

	return pCC_UserObj_wrap->OnExecuted1(
					jobKey_wrap,
					errorCode_wrap,
					context_wrap,
					outArgs_wrap
					);
}
