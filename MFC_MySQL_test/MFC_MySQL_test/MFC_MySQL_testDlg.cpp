
// MFC_MySQL_testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_MySQL_test.h"
#include "MFC_MySQL_testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_MySQL_testDlg �Ի���




CMFC_MySQL_testDlg::CMFC_MySQL_testDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_MySQL_testDlg::IDD, pParent)
	, m_input_id(_T(""))
	, m_input_name(_T(""))
	, m_input_salary(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_MySQL_testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_input_id);
	DDX_Text(pDX, IDC_EDIT2, m_input_name);
	DDX_Text(pDX, IDC_EDIT1, m_input_salary);
}

BEGIN_MESSAGE_MAP(CMFC_MySQL_testDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC_MySQL_testDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFC_MySQL_testDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_MySQL_testDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFC_MySQL_testDlg ��Ϣ�������

BOOL CMFC_MySQL_testDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFC_MySQL_testDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_MySQL_testDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFC_MySQL_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_MySQL_testDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString local_id=m_input_id.GetBuffer();
	CString local_name = m_input_name.GetBuffer();
	CString local_salary = m_input_salary.GetBuffer();
	MYSQL local_mysql;
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","test",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
	}
	else
	{
		AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
	}
	// ���� SQL ����ַ���
	CString sql_insert;
	sql_insert.Format(_T("insert into emp_test(id, name, salary) values (%s, %s, %s);"), local_id, local_name, local_salary);
	//CString תchar *
	string sql_Insert=transformPlus.toString(sql_insert);
	const char  * sql=sql_Insert.c_str();
	// ִ�� sql ��䡣
	// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣
	if(mysql_query(&local_mysql,sql)==0)
	{   
		AfxMessageBox(_T("insert succeed!"));   
	}else{
		AfxMessageBox(_T("insert failed!"));
	}
	// �ر� local_mysql �����������ݿ����ӣ� һ������²���д��
	mysql_close(&local_mysql);
	UpdateData(FALSE);

}


void CMFC_MySQL_testDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	OnCancel();
}

void CMFC_MySQL_testDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// ���û��ڱ༭��������������� ������ֻʵ����ͨ�� id ���ҡ�
	CString local_id = m_input_id.GetBuffer();
	//CString local_name = m_input_name.GetBuffer();
	//CString local_salary = m_input_salary.GetBuffer();
	// ���� MYSQL ����
	MYSQL local_mysql;
	// ��ʼ�� MYSQL ����
	mysql_init(&local_mysql);
	// �������ݿ⡣
	if(!mysql_real_connect(&local_mysql,"localhost","root","","test",3306,NULL,0))
	{
		AfxMessageBox(_T("connect to database failed!"));
	}
	else
	{
		AfxMessageBox(_T("connect to database success!"));
		// �����ַ����� ʹ����֧�����ġ�
		mysql_query(&local_mysql, "set names 'gb2312'");
	}

	//CString select_sql_all;
	CString select_sql_by_id;
	//CString select_sql_by_name;
	// ��Ų�ѯ����ı���
	MYSQL_RES* result;
	MYSQL_ROW row;
	//select_sql_all.Format("select * from emp_test");
	select_sql_by_id.Format(_T("select id, name, salary from emp_test where id = %s"), local_id.GetBuffer());
	string str=transformPlus.toString(select_sql_by_id);
	const char * query=str.c_str();
	// select_sql_by_name.Format("select id, name, salary from emp_test where name = \'%s\'", local_name.GetBuffer());
	int res = mysql_query(&local_mysql, query);
	// mysql_query �������� 0  ��ʾ ��ѯ�ɹ���
	if(res==0){
		// ��ȡ��ѯ������������� result ���档
		result = mysql_store_result(&local_mysql);
		// ��ȡ��ѯ����������� �����ò���������ע���ˡ�
		// int row_count = mysql_num_rows(result);
		// ѭ���شӲ�ѯ������ó�һ�У� ����ֵ�� row ������
		while(row = mysql_fetch_row(result)){
			CString local_id;
			CString local_name;
			CString local_salary;
			CString local_message;
			// �������ݿ��л�ȡ������ �������ַ����У� row[0], row[1], row[2], �ֱ��ʾһ����ѯ����еĵ�1�� 2�� 3 ���ֶΣ� �ҽ����� emp_test
			// ����ֻ�� 3 ���ֶΡ�
			local_id.Format(_T("%s"),row[0]);//row ��ֵ��local_id
			local_name.Format(_T("%s"),row[1]);
			local_salary.Format(_T("%s"),row[2]);
			// ���ַ�����������������Ϣ����ʾ��
			local_message.Format(_T("results: "));
			local_message += local_id + _T(",") +local_name + _T(",") + local_salary;
			AfxMessageBox(local_message.GetBuffer());
		}
		mysql_free_result(result);
		AfxMessageBox(_T("select succeed!"));
	}else{
		AfxMessageBox(_T("no results!"));
	}

	mysql_close(&local_mysql);
	UpdateData(FALSE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
