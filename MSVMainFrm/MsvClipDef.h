#if !defined AFX_MSVClipDef_H
#define AFX_MSVClipDef_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmsystem.h"

#define MAX_DATA_NUM 10
#define MAX_BLOCK_SIZE 10
#define CLOSECAPTION_SIZE 258
#define  _FRAME_HEAD_SIZE 44      //28 +4 + 4 +4, add VITC + LTC + CC + AFD
#define  _PACKET_HEAD_SIZE 28

#define   SEND_BUF_SIZE	(3584*1024)
#define   RECV_BUF_SIZE	(8192*1024)

#pragma pack(push,4)

typedef struct tagIDX_STATUS
{		
	DWORD		dwTotalFrms;
	DWORD		dwProtect;
	DWORD		dwRecStatus;
	DWORD		dwPlayStatus;
	DWORD		dwPauseStatus;
	DWORD		dwFirstFrm;
	DWORD		dwLastFrm;
	DWORD		dwClipType;	
}IDX_STATUS,*pIDX_STATUS; 

typedef struct tagIDX_HEADER
{
	IDX_STATUS	status;

	BYTE		byMagic[16];
	float		fVersion;
	DWORD		dwHeadSize;
	DWORD		dwDataInfoSize;
	DWORD		dwSecSize;
	float		frame_rate;
	DWORD		dwDataNum;
	char		clip_nameA[260];
	char		clip_nameB[260];
	char        ch_closecaption[260];
	DWORD       dwReServe1;
	DWORD       dwReServe2;
	DWORD		dwGOPBCount;
	DWORD		dwGOPPCount;
}IDX_HEADER,*pIDX_HEADER; 

typedef struct tagDATA_INFO
{
	DWORD		file_type;
	DWORD		codec_type;
	DWORD		sub_codec_type;
	DWORD		video_width;
	DWORD		video_height;
	DWORD		video_chroma_fmt;
	DWORD		video_seq;
	DWORD		audio_alone;
	DWORD		bit_rate;
	DWORD		create_obj;
	DWORD		dwAudMask;
	WAVEFORMATEX	audio_format_in;
	WAVEFORMATEX	audio_format_out;
	char		object_name[260];
}DATA_INFO,*pDATA_INFO;


typedef struct tagFrmDataInfo
{
	ULONGLONG	data_offset;
	DWORD		data_bufsize;
	DWORD		frm_type;
}FrmDataInfo,*pFrmDataInfo;

typedef struct tagFrmHeadInfo
{
	int			keyframe;
	int			manualframe;
	int			manualframetype;
	DWORD		file_end_flag;
	DWORD		gop_flag;
	DWORD		pre_seq;
	DWORD		pre_i;
	DWORD		post_i;
	DWORD		pre_ref;
	DWORD		post_ref;
	ULONGLONG	pts;
	ULONGLONG	dts;
	int         cc_size;        //CC实际长度
	BYTE        cc_data[CLOSECAPTION_SIZE];
}FrmHeadInfo,*pFrmHeadInfo;

typedef struct tagFRAME_DETAIL
{
	BYTE		framehead[16];
	DWORD		secnum;
	FrmHeadInfo frm_head_info;
	FrmDataInfo data_info[10];
}FRAME_DETAIL,*pFRAME_DETAIL;

typedef struct _tag_Packet_Data
{
	DWORD dwTcpHead;
	DWORD dwSize;		//Size of Packet
	int iPacketFlag;	//0:Normal Packet,1:Start Packet,2:End Packet, 4:First Frame Pic,5:XML Packet
	int iFrameNum;		//The Frame Count in Packet
	int iPacketNo;		//每帧数据的序号
	DWORD dwTotalFrame; //总帧数
	DWORD dwClipID;
}_Packet_Data;

typedef struct _tag_Packet_Multi_Frames
{
	_Packet_Data stData;
	BYTE pPacketBuf[RECV_BUF_SIZE];	//Para. Data or Frame Data
}_Packet_Multi_Frames;

typedef struct _tag_FRAME_DATA
{
	DWORD dwSize;		//Frame Size
	DWORD dwTypeV0;
	DWORD dwTypeV1;
	DWORD dwSizeV0;
	DWORD dwSizeA0;
	DWORD dwSizeV1;	
	DWORD dwSizeA1;
	DWORD dwVITC;          //Time Code
	DWORD dwLTC; 
	DWORD dwAFD;
	DWORD dwCC;            //CC 保证在最后一位
}_Frame_Data;

typedef struct _tag_Progress
{	
	DWORD dwTcpHead;
	DWORD dwSize;		//Frame Size
	int   iFlag;		//dwFlag = 1:开始 0:进度数据 2:迁移完成 -1:写出错 -2:丢包
	DWORD dwWriteFrame;	//
	DWORD dwClipID;
	TCHAR szDestPicPath[MAX_PATH];
	_tag_Progress()
	{
		dwTcpHead = 0x00aa0155;
		dwClipID = 0;
		dwSize = 20;
		iFlag = 0;
		dwWriteFrame = 0;
		memset(szDestPicPath,0,MAX_PATH);
	}
}_Frame_Progress;

typedef struct _CARRAYERR_CLIP
{
	DWORD	dwTime;
	int     iErrCount;
	BOOL    bIDXBadClipFlag;//坏的IDX文件标志
	CString strErrIdxName;
}CarrayErr_Clip;


#pragma pack(pop)

#endif 
