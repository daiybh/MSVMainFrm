// MSVInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSVMainFrm.h"
#include "MSVInfoDlg.h"


// CMSVInfoDlg 对话框

IMPLEMENT_DYNAMIC(CMSVInfoDlg, CDialog)

CMSVInfoDlg::CMSVInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMSVInfoDlg::IDD, pParent)
{
     m_bIsShow = FALSE;
}

CMSVInfoDlg::~CMSVInfoDlg()
{
}

void CMSVInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DATAINFO, m_treeDataInfo);
}


BEGIN_MESSAGE_MAP(CMSVInfoDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CMSVInfoDlg 消息处理程序

BOOL CMSVInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetClientRect(rect);

	m_treeDataInfo.MoveWindow(rect,TRUE);
  

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
CString CMSVInfoDlg::GetstrFileType(DWORD nID)
{
	switch (nID)
	{
	case 2:
		return _T("MatroxAvi");
	case 1:
		return _T("RiffxAvi");
	case 4:
		return _T("GVG");
	case 5:
		return _T("MXF");
	case 3:
		return _T("MAV70");
	case 7:
		return _T("WMV");
	case 8:
		return _T("AVI2.0");
	case 191:
		return _T("ISMV");
	case 70:
		return _T("MP4");
	case 189:
		return _T("TS");

		//--------------Audio filetype------------------
	case 21:
		return _T("WAV");
	case 22:
		return _T("MP2");
	case 23:
		return _T("MP3");
	case 27:
		return _T("DBE");
	case 25:
		return _T("AAC");
	case 28:
		return _T("HEAAC");
	case 24:
		return _T("MXF");
	default:
		//return _T("unknown filetype");
		break;
	}	
   

	return _T("unknown filetype");
}

CString CMSVInfoDlg::GetstrCodeType(DWORD nID)
{
	switch (nID)
	{
	case 1:
		return _T("MPEG2");
	case 3:
		return _T("MJPEG");
	case 2:
		return _T("MPEG4");
	case 4:
		return _T("DV");
	case 21:
		return _T("WMV");
	case 57:
		return _T("H.264");
	case 55:
		return _T("DNxHD");
	default:
		//return _T("unknown codetype");
		break;
	}

 
	return _T("unknown codetype");
}


CString CMSVInfoDlg::GetstrSubCodeType(DWORD EncID,DWORD SubnID)
{
	switch (EncID)
	{
	case 1:  //MPEG2
		switch(SubnID)
		{
		case 2:
			return _T("MPEG2IFrame");
		case 3:
			return _T("MPEG2IBPFrame");
		case 1:
			return _T("MPEG2IMX");
		default:
			return _T("unknown sub encodetype");
		}
	case 3://MJEPG
		return _T("unknown sub encodetype");
	case 2://MPEG4
		switch(SubnID)
		{
		case 842297453:
			return _T("MSV2");
		case 1983148141:
			return _T("MSV3");
		default:
			return _T("unknown sub encodetype");
		}
	case 4: // DV
		switch(SubnID)
		{
		case 1:
			return _T("DV25");
		case 2:
			return _T("DV50");
		case 0:
			return _T("DVCAM");
		default:
			return _T("unknown sub encodetype");
		}
	case 21://WMV
		switch(SubnID)
		{
		case 1:
			return _T("WMV8");
		case 0:
			return _T("WMV9");
		default:
			return _T("unknown sub encodetype");
		}
	case 57://H.264
		switch(SubnID)
		{
		case 3:
			return _T("MPEG2IBPFrame");
		default:
			return _T("unknown sub encodetype");
		};
	case 55: //DNxHD
		switch(SubnID)
		{
		case 2:
			return _T("MPEG2IFrame");
		default:
			return _T("unknown sub encodetype");
		};
	default:
		//return _T("unknown sub encodetype");
		break;
	}
 
	return _T("unknown sub encodetype");

}

CString CMSVInfoDlg::GetstrChromaFmt(DWORD nID)
{
	switch (nID)
	{
	case 1:
		return _T("4:2:0");
	case 2:
		return _T("4:2:2");
	case 3:
		return _T("4:4:4");
	default:
		return _T("unknown chroma format");
	}
}

//-----------------------------------------------------------
// 函数名称：
//     
// 参数：
//    - 
// 返回：
//     
// 说明：
//     
//-----------------------------------------------------------


BOOL CMSVInfoDlg::SetDataInfo(int nCureSel,BYTE *lpData)
{
	 if(nCureSel < 0)
		 return FALSE;
	 m_treeDataInfo.DeleteAllItems();

	 HTREEITEM hRoot,hTwoLevel,hThreeLevel;
	DATA_INFO *lpDataInfo = (DATA_INFO*)lpData;
    hRoot = m_treeDataInfo.InsertItem(_T("DATA_INFO"),TVI_ROOT);
	CString temp,temp2;

	temp.Format(_T("DWORD file_type:            %d(%s)"),lpDataInfo->file_type,GetstrFileType(lpDataInfo->file_type));
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);

	temp.Format(_T("DWORD codec_type:           %d(%s)"),lpDataInfo->codec_type,GetstrCodeType(lpDataInfo->codec_type));
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);

	CString strShowText = (nCureSel%2)?_T("srcAudioEncType"):_T("sub_codec_type");
	temp.Format(_T("DWORD %s:       %d(%s)"),strShowText,lpDataInfo->sub_codec_type,GetstrSubCodeType(lpDataInfo->codec_type,lpDataInfo->sub_codec_type));
    hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	temp.Format(_T("DWORD video_width:          %u"),lpDataInfo->video_width);
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	temp.Format(_T("DWORD video_height:         %u"),lpDataInfo->video_height);
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	temp.Format(_T("DWORD video_chroma_fmt:     %u(%s)"),lpDataInfo->video_chroma_fmt,GetstrChromaFmt(lpDataInfo->video_chroma_fmt));
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	temp.Format(_T("DWORD video_seq:            %u"),lpDataInfo->video_seq);
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	temp.Format(_T("DWORD audio_alone:          %u"),lpDataInfo->audio_alone);
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	temp.Format(_T("DWORD bit_rate:             %u"),lpDataInfo->bit_rate);
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	temp.Format(_T("DWORD create_obj:           %u"),lpDataInfo->create_obj);
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	temp.Format(_T("DWORD dwAudMask:            %u"),lpDataInfo->dwAudMask);
	hTwoLevel = m_treeDataInfo.InsertItem(temp,hRoot);


	//---------------------------------------------------------------------------------------
	hTwoLevel = m_treeDataInfo.InsertItem(_T("WAVEFORMATEX audio_format_in"),hRoot);

	temp.Format(_T("WORD wFormatTag:            %u"),lpDataInfo->audio_format_in.wFormatTag);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("WORD nChannels:             %u"),lpDataInfo->audio_format_in.nChannels);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("DWORD nSamplesPerSec:       %u"),lpDataInfo->audio_format_in.nSamplesPerSec);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("DWORD nAvgBytesPerSec:      %u"),lpDataInfo->audio_format_in.nAvgBytesPerSec);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("WORD nBlockAlign:           %u"),lpDataInfo->audio_format_in.nBlockAlign);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("WORD wBitsPerSample:        %u"),lpDataInfo->audio_format_in.wBitsPerSample);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("WORD cbSize:                %u"),lpDataInfo->audio_format_in.cbSize);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	//--------------------------------------------------------------------------------------------
	hTwoLevel = m_treeDataInfo.InsertItem(_T("WAVEFORMATEX audio_format_out"),hRoot);

	temp.Format(_T("WORD wFormatTag:            %u"),lpDataInfo->audio_format_out.wFormatTag);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("WORD nChannels:             %u"),lpDataInfo->audio_format_out.nChannels);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("DWORD nSamplesPerSec:       %u"),lpDataInfo->audio_format_out.nSamplesPerSec);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("DWORD nAvgBytesPerSec:      %u"),lpDataInfo->audio_format_out.nAvgBytesPerSec);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("WORD nBlockAlign:           %u"),lpDataInfo->audio_format_out.nBlockAlign);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("WORD wBitsPerSample:        %u"),lpDataInfo->audio_format_out.wBitsPerSample);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	temp.Format(_T("WORD cbSize:                %u"),lpDataInfo->audio_format_out.cbSize);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);


	//--------------------------------------------------------------------------------------
	temp2 = lpDataInfo->object_name;	//将char* 转为Cstring
	temp.Format(_T("char object_name[256]:      %s"),temp2);
	hThreeLevel = m_treeDataInfo.InsertItem(temp,hTwoLevel);

    m_treeDataInfo.Expand(hRoot,TVE_EXPAND);

	m_bIsShow = TRUE;

	return TRUE;

}
void CMSVInfoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
     AnimateWindow(500,AW_BLEND|AW_HIDE);
	 m_bIsShow = FALSE;
   // ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CMSVInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(m_bIsShow)
	{
		AnimateWindow(1000,AW_BLEND);
	}
	// TODO: 在此处添加消息处理程序代码
}
