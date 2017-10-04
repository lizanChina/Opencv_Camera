// PictureEditeWin.cpp : implementation file
#include "stdafx.h"
#include "O_MFC.h"
#include "PictureEditeWin.h"
#include "afxdialogex.h"

// PictureEditeWin dialog
bool scrawl_flag=false;                                  //Ϳѻ���濪����Ǳ����δ�
int  scrawl_type=-1;                                     //Ϳѻ���� -1 ���滭��0��.....
IMPLEMENT_DYNAMIC(PictureEditeWin, CDialog)

PictureEditeWin::PictureEditeWin(CWnd* pParent /*=NULL*/)
	: CDialog(PictureEditeWin::IDD, pParent)
{
	memset(this->curdir,0,sizeof(this->curdir));
	CString t_curdirstr=this->GetModuleDir();
	char * t_curdir=this->CStringToChar(t_curdirstr);
	memcpy(this->curdir,t_curdir,strlen(t_curdir));
	delete t_curdir;
	t_curdir=NULL;
	scale=1;
}
// PictureEditeWin message handlers
CString PictureEditeWin::GetModuleDir()   
{   
	HMODULE module = GetModuleHandle(0);   
	TCHAR pFileName[MAX_PATH];   
	GetModuleFileName(module, pFileName, MAX_PATH);   

	CString csFullPath(pFileName);   
	int nPos = csFullPath.ReverseFind( _T('\\') );   
	if( nPos < 0 )   
		return CString("");   
	else   
		return csFullPath.Left( nPos );  	
}  
//CString ת char *
char * PictureEditeWin::CStringToChar(CString pstr)
{
	int strlen=pstr.GetLength();
	int nbyte=WideCharToMultiByte(CP_ACP,0,pstr,strlen,NULL,0,NULL,NULL);
	char * VoicePath=new char[nbyte+1];
	memset(VoicePath,0,sizeof(VoicePath));
	WideCharToMultiByte(CP_OEMCP,0,pstr,strlen,VoicePath,nbyte,NULL,NULL);
	VoicePath[nbyte]=0;
	return VoicePath;
}
BOOL PictureEditeWin::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here 
	attachWindow(pic,"Pictrue",IDC_STATIC);
	showImage(pic,IDC_STATIC,this->mat);
	beta=5;
	alpha=1.03;
	leftbtn_flag=false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
PictureEditeWin::~PictureEditeWin()
{
}
bool PictureEditeWin::attachWindow(string &pic,const char* name,int ID)
{
	pic=string(name);
	cv::namedWindow(pic, 1);
	HWND hWnd = (HWND) cvGetWindowHandle(name);
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(ID)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	return true;
}
bool PictureEditeWin::showImage(string pic,int id,cv::Mat mat)
{
	CRect rect;
	GetDlgItem(id)->GetClientRect(&rect);	
	cv::resize(mat,mat,cv::Size(rect.Width(),rect.Height()),CV_INTER_CUBIC);	
	imshow(pic,mat);
	return true;
}
void PictureEditeWin::setMat(cv::Mat t_mat)
{
	this->mat=t_mat;
	tempImage=this->mat.clone();
}

void PictureEditeWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON8, m_savebtn);
	DDX_Control(pDX, IDC_BUTTON1, m_graybtn);
	DDX_Control(pDX, IDC_BUTTON5, m_restorebtn);
}

BEGIN_MESSAGE_MAP(PictureEditeWin, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &PictureEditeWin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &PictureEditeWin::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &PictureEditeWin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &PictureEditeWin::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &PictureEditeWin::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON3, &PictureEditeWin::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &PictureEditeWin::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &PictureEditeWin::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON7, &PictureEditeWin::OnBnClickedButton7)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void PictureEditeWin::OnBnClickedButton1()                 //�ҶȰ�ť�����¼�
{
	// TODO: Add your control notification handler code here
	cvtColor(tempImage,tempImage,CV_RGB2GRAY);
	showImage(pic,IDC_STATIC,tempImage);

	this->UpdateData(false);
	this->m_graybtn.EnableWindow(false);
}

void PictureEditeWin::OnBnClickedButton5()                  //�ָ���ť�����¼�
{
	// TODO: Add your control notification handler code here
	showImage(pic,IDC_STATIC,this->mat);
	tempImage=this->mat.clone();
	this->UpdateData(false);
	this->m_graybtn.EnableWindow(true);
}

void PictureEditeWin::OnBnClickedButton2()                   //������ť�����¼�
{
	// TODO: Add your control notification handler code here
	for(int y=0;y<tempImage.rows;++y)
	{
		for(int x=0;x<tempImage.cols;++x)
		{
			for(int c=0;c<3;++c)
			{
				tempImage.at<cv::Vec3b>(y,x)[c] =  
                cv::saturate_cast<uchar>( tempImage.at<cv::Vec3b>(y,x)[c]  + beta); 
			}
		}
	}
	showImage(pic,IDC_STATIC,tempImage);
	this->UpdateData(false);
}


void PictureEditeWin::OnBnClickedButton6()                   //�䰵��ť�����¼� 
{
	// TODO: Add your control notification handler code here
	for(int y=0;y<tempImage.rows;++y)
	{
		for(int x=0;x<tempImage.cols;++x)
		{
			for(int c=0;c<3;++c)
			{
				tempImage.at<cv::Vec3b>(y,x)[c] =  
                cv::saturate_cast<uchar>( tempImage.at<cv::Vec3b>(y,x)[c]  - beta); 
			}
		}
	}
	showImage(pic,IDC_STATIC,tempImage);
	this->UpdateData(false);
}

void PictureEditeWin::OnBnClickedButton8()                   //���水ť�����¼�
{
	// TODO: Add your control notification handler code here
	PictureNameWin picwin;
	picwin.setWtype(1);
	picwin.DoModal();
	if(!picwin.filename)
	{
		return ;
	}
	char t_filepath[128]={0};
	memset(t_filepath,0,sizeof(t_filepath));
	sprintf(t_filepath,"C:\\Users\\Administrator\\Desktop\\%s",picwin.filename);

	bool res=cv::imwrite(t_filepath,tempImage);
	if(res)
	{
		this->MessageBox(_T("ͼƬ�ɹ����������!"));
	}
	if(picwin.filename)
	{
		delete picwin.filename;
		picwin.filename=NULL;
	}
}


void PictureEditeWin::OnBnClickedButton3()                                     //�Աȶ�+
{
	// TODO: Add your control notification handler code here
	for(int y=0;y<tempImage.rows;++y)
	{
		for(int x=0;x<tempImage.cols;++x)
		{
			for(int c=0;c<3;++c)
			{
				tempImage.at<cv::Vec3b>(y,x)[c] =  
                cv::saturate_cast<uchar>( alpha*tempImage.at<cv::Vec3b>(y,x)[c]); 
			}
		}
	}
	showImage(pic,IDC_STATIC,tempImage);
	this->UpdateData(false);
}


void PictureEditeWin::OnBnClickedButton4()                                     //�Աȶ�-
{
	// TODO: Add your control notification handler code here
	for(int y=0;y<tempImage.rows;++y)
	{
		for(int x=0;x<tempImage.cols;++x)
		{
			for(int c=0;c<3;++c)
			{
				tempImage.at<cv::Vec3b>(y,x)[c] =  
                cv::saturate_cast<uchar>( tempImage.at<cv::Vec3b>(y,x)[c]/alpha); 
			}
		}
	}
	showImage(pic,IDC_STATIC,tempImage);
	this->UpdateData(false);
}


void PictureEditeWin::OnBnClickedButton9()                                     //���ֱ༭
{
	// TODO: Add your control notification handler code here



}

void PictureEditeWin::OnBnClickedButton7()                                     //�滭Ϳѻ
{
	// TODO: Add your control notification handler code here
	if(!scrawl_flag)
	{
		PaintTypeWin *ptwin=new PaintTypeWin;
		ptwin->Create(IDD_DIALOG3,NULL);
		ptwin->ShowWindow(SW_SHOW);
		scrawl_flag=true;
	}
}


BOOL PictureEditeWin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_ESCAPE:                                                       //Esc���������¼�  
			scrawl_type=-1;
			return true;  
		case VK_RETURN:                                                       //Enter���������¼�
			return true;
		case VK_F1:                                                           //����������Ϣ
			this->MessageBox(_T("��Ƭ����ƵĬ�ϱ��浽���棡"));
			return true;
		default:  
			;  
		}  
	}  
	return CDialog::PreTranslateMessage(pMsg);
}

void PictureEditeWin::OnLButtonDown(UINT nFlags, CPoint point)                //����������
{
	// TODO: Add your message handler code here and/or call default
	leftbtn_flag=true;
	this->start_point.x=point.x;
	this->start_point.y=point.y;
	if(scrawl_type==0)
	{
		cv::circle(this->tempImage,this->start_point,1,cv::Scalar(0,0,255),5,8);
		showImage(pic,IDC_STATIC,tempImage);
		this->UpdateData(false);
		
	}
	CDialog::OnLButtonDown(nFlags, point);
}



void PictureEditeWin::OnLButtonUp(UINT nFlags, CPoint point)                  //�������ͷ�
{
	// TODO: Add your message handler code here and/or call default
	leftbtn_flag=false;
	this->end_point.x=point.x;
	this->end_point.y=point.y;
	switch(scrawl_type)
	{
	case 0:
		{

			break;
		}
	case 1:
		{

			break;
		}
	
	}



	CDialog::OnLButtonUp(nFlags, point);
}


void PictureEditeWin::OnMouseMove(UINT nFlags, CPoint point)                  //����ƶ������¼�
{
	// TODO: Add your message handler code here and/or call default
	if(leftbtn_flag)
	{
		this->tmp_point.x=point.x;
		this->tmp_point.y=point.y;



	}
	CDialog::OnMouseMove(nFlags, point);
}
