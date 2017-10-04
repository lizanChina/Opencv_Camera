// PaintTypeWin.cpp : implementation file
//

#include "stdafx.h"
#include "O_MFC.h"
#include "PaintTypeWin.h"
#include "afxdialogex.h"


// PaintTypeWin dialog
extern bool scrawl_flag;
extern int  scrawl_type;
IMPLEMENT_DYNAMIC(PaintTypeWin, CDialog)

PaintTypeWin::PaintTypeWin(CWnd* pParent /*=NULL*/)
	: CDialog(PaintTypeWin::IDD, pParent)
{

}

PaintTypeWin::~PaintTypeWin()
{
	delete this;
}

void PaintTypeWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PaintTypeWin, CDialog)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &PaintTypeWin::OnPointBtnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &PaintTypeWin::OnCircleBtnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON8, &PaintTypeWin::OnEllipseBtnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &PaintTypeWin::OnLineBtnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON10, &PaintTypeWin::OnCurveBtnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON3, &PaintTypeWin::OnRectangleBtnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &PaintTypeWin::OnCleanBtnClickedButton4)
END_MESSAGE_MAP()


// PaintTypeWin message handlers


BOOL PaintTypeWin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void PaintTypeWin::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	DestroyWindow();
	CDialog::OnCancel();
}


void PaintTypeWin::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	DestroyWindow();
	CDialog::OnOK();
}

void PaintTypeWin::OnDestroy()
{
	
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
}


void PaintTypeWin::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	scrawl_flag=false;
	CDialog::OnClose();
}


void PaintTypeWin::OnPointBtnClickedButton1()                      //��
{
	// TODO: Add your control notification handler code here
	scrawl_type=0;
}


void PaintTypeWin::OnCircleBtnClickedButton2()                     //Բ
{
	// TODO: Add your control notification handler code here
	scrawl_type=1;
}


void PaintTypeWin::OnEllipseBtnClickedButton8()                    //��Բ
{
	// TODO: Add your control notification handler code here
	scrawl_type=2;
}


void PaintTypeWin::OnLineBtnClickedButton6()                       //ֱ��
{
	// TODO: Add your control notification handler code here
	scrawl_type=3;
}


void PaintTypeWin::OnCurveBtnClickedButton10()                      //����
{
	// TODO: Add your control notification handler code here
	scrawl_type=4;
}


void PaintTypeWin::OnRectangleBtnClickedButton3()                   //����
{
	// TODO: Add your control notification handler code here
	scrawl_type=5;
}


void PaintTypeWin::OnCleanBtnClickedButton4()                       //����
{
	// TODO: Add your control notification handler code here
	scrawl_type=6;
}


BOOL PaintTypeWin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)  
    {  
        switch(pMsg->wParam)  
        {  
            case VK_ESCAPE:                        //Esc���������¼�  
				scrawl_type=-1;
                return true;  
            case VK_RETURN:                        //Enter���������¼�
                return true;
			case VK_F1:                            //����������Ϣ
				this->MessageBox(_T("��Ƭ����ƵĬ�ϱ��浽���棡"));
				return true;
            default:  
				;  
        }  
    }  
	return CDialog::PreTranslateMessage(pMsg);
}
