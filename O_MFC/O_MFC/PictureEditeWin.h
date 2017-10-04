#pragma once
#include <string>
#include "PaintTypeWin.h"
#include "PictureNameWin.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;

// PictureEditeWin dialog
class PictureEditeWin : public CDialog
{
	DECLARE_DYNAMIC(PictureEditeWin)

public:
	PictureEditeWin(CWnd* pParent = NULL);              // standard constructor
	virtual ~PictureEditeWin();
	bool attachWindow(string &pic,const char* name,int ID);     //��opencv����ʾ������MFC�Ŀؼ�����������
	bool showImage(string pic,int id,cv::Mat mat);              //Ч����opencv�Ĵ���ǡ�ø����ڿؼ���    
// Dialog Data
	enum { IDD = IDD_DIALOG2 };
	void setMat(cv::Mat t_mat);
	CString GetModuleDir();
	char* CStringToChar(CString pstr);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_savebtn;
	cv::Mat mat;
	cv::Mat tempImage;
	string  pic;
	bool    leftbtn_flag;                                //�������ͷű�� 
	double  scale;                                       //�Ŵ�ϵ��
	int     beta;                                        //����
	double  alpha;                                       //�Աȶ�
	char    curdir[128];
	cv::Point start_point;
	cv::Point tmp_point;
	cv::Point end_point;
	virtual BOOL OnInitDialog();
	CButton m_graybtn;
	CButton m_restorebtn;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton7();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
