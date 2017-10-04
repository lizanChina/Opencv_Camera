
// O_MFCDlg.h : header file
//
#include "PictureNameWin.h"
#include "PictureEditeWin.h"
#include <cstring>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#pragma once
using namespace std;

// CO_MFCDlg dialog
class CO_MFCDlg : public CDialogEx
{
// Construction
public:
	CO_MFCDlg(CWnd* pParent = NULL);	// standard constructor
	bool attachWindow(string &pic,const char* name,int ID);     //��opencv����ʾ������MFC�Ŀؼ�����������
	bool showImage(string pic,int id,cv::Mat mat);              //Ч����opencv�Ĵ���ǡ�ø����ڿؼ���    
	CString GetModuleDir();
	char* CStringToChar(CString pstr);
// Dialog Data
	enum { IDD = IDD_O_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	       // DDX/DDV support
	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton2();                         //�ر�����ͷ
	afx_msg void OnBnClickedButton1();                         //������ͷ
	afx_msg void OnTimer(UINT_PTR nIDEvent);         
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	
	cv::VideoCapture * video;
	string videowin_pic;
	bool vedio_flag;                                           //����ʼ���
	bool open_flag;
	char curdir[128];                                          //����Ӧ�ó���ǰ���ڵ�·��
	char picpath[128];                                         //����Ĭ��ͼƬ·��
	char vediopath[128];                                       //�������񱣴��·��
	cv::Mat mat;                                               //����ץ�ĵ�ÿһ֡ͼƬ
	cv::Mat t_mat;                                             //�������յ�ͼƬ
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_vedioctl;
	CvVideoWriter* videowrite;
};
