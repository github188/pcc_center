/**
 *                                          Netposa Algorithm SDK
 *                                   (c) Copyright 2011-2013, Netposa
 *                                           All Rights Reserved
 *
 * File		: NP_GridUtils.h.
 * Author	: Zhou Guangming
 * Time		: 2013-7-30
 */


#ifndef __NP_GRIDUTILS_H__
#define __NP_GRIDUTILS_H__

#ifdef WIN32
    #define PGRID_CALL __stdcall
#else
    #define PGRID_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef void (PGRID_CALL *NP_GridFPackProgress)(int progress);


/**
 * Function:	NP_GridFPack().
 * Input:		unpackPath:	Source directory.
 *				packedPath:	Packed file directory.
 *				packedFile:	Packed file name.
 *				progress:	Pack progress callback function, NULL no callback.
 * Output:		None.
 * Return:		Packed directory OK or not.
 * Description:	Pack all files in specific directory to specific name in specific directory.
 */
extern BOOL PGRID_CALL  
NP_GridFPack (const char *unpackPath, const char *packedPath, const char *packedFile, 
			  NP_GridFPackProgress progress, const char *extName = "pack", BOOL packRoot = TRUE);



/**
 * Function:	NP_GridFUnpack().
 * Input:		packedFile:	Packed file absolute path.
 *				unpackPath:	Unpack directory path.
 *				progress:	Unpack progress callback function, NULL no callback.
 * Output:		None.
 * Return:		Unpack file OK or not. 
 * Description:	Unpack file.
 */
extern BOOL PGRID_CALL 
NP_GridFUnpack (const char* packedFile, const char* unpackPath, NP_GridFPackProgress progress);


/**
 * Function:	NP_GridYuv420pToJpg().
 * Input:		yuv:	The pointer point to YUV image data.
 *				width:	Image width in pixel.
 *				height:	Image height in pixel.
 *				step[3]:Image step in byte.
 *				bufSize:Buffer size of jpgBuf in bytes.
 * Output:		jpgBuf:	JPEG data.
 * Return:		JPEG data size in byte.
 * Description:	Encode YUV420P to JPEG.
 */
extern int PGRID_CALL 
NP_GridYuv420pToJpg (const void *yuv[3], int width, int height, const int step[3], void *jpgBuf, int bufSize);


/**
 * Function:	NP_GridGetProgMainDll().
 * Input:		dllPath:	Grid program dynamic link library path.
 *				dllNum:		Grid program dynamic link library number.
 * Output:		errText:	Error text.
 *				mainFun:	Output main function prefix.
 * Return:		-1 if get main dynamic link library failed, > 0 if OK.
 * Description:	Find main dynamic link library of grid program.
 */
extern int PGRID_CALL 
NP_GridGetProgMainDll (const char *dllPath[], int dllNum, const char **errText, char mainFun[MAX_PATH]);


/**
 * Function:	NP_GridFindProgramEntry().
 * Input:		path:	Grid program path.
 * Output:		entry:	Grid program entry path.
 * Return:		Find grid program entry OK or not.
 * Description:	Find grid program entry.
 */
extern BOOL __stdcall 
NP_GridFindProgramEntry (const char *path, char entryDll[MAX_PATH], char entryFun[MAX_PATH] = NULL);


/**
 * Function:	NP_GridGetModuleVersion().
 * Input:		modulePath:	Module file path.
 * Output:		majorVer:	Major version.
 *				minorVer:	Minor version.
 *				thirdVer:	Third version.
 *				fourthVer:	Fourth version.
 * Return:		Get module version successful or failure.
 * Description:	Get module version.
 */
extern BOOL PGRID_CALL 
NP_GridGetModuleVersion (const char *modulePath, int &majorVer, int &minorVer, int &thirdVer, int &fourthVer);


/**
 * Function:	NP_Base64CalcEncodeSize().
 * Input:		dataBuf:	Pointer point to input buffer.
 *				dataSize:	Input buffer size in bytes.
 * Output:		None.
 * Return:		Data size encoded in bytes.
 * Description:	Calculate encoded data buffer size in base64.
 */
extern int PGRID_CALL 
NP_Base64CalcEncodeSize (const void *dataBuf, int dataSize);


/**
 * Function:	NP_Base64Encode().
 * Input:		dataBuf:	Pointer point to input buffer.
 *				dataLen:	Input data size in bytes.
 * Output:		outputBuf:	Output encode data.
 * Return:		Encode data OK or not.
 * Description:	Encode binary data in base64.
 */
extern BOOL PGRID_CALL 
NP_Base64Encode (const void* dataBuf, int dataLen, void *outputBuf);


/**
 * Function:	NP_Base64CalcDecodeSize().
 * Input:		dataBuf:	Pointer point to data buffer.
 *				dataLen:	Data buffer size in bytes.
 * Output:		None.
 * Return:		Decode data size in bytes.
 * Description:	Decode data in base64.
 */
extern int PGRID_CALL 
NP_Base64CalcDecodeSize (const void *dataBuf, int dataLen);


/**
 * Function:	NP_Base64Decode().	
 * Input:		dataBuf:
 *				dataLen:	
 * Output:		outputBuf:
 * Return:		Decode OK or not.
 * Description:	Decode data in base64.
 */
extern BOOL PGRID_CALL 
NP_Base64Decode (const void *dataBuf, int dataLen, void *outputBuf);


#ifdef __cplusplus
}
#endif


#endif	/* __NP_GRIDUTILS_H__ */
