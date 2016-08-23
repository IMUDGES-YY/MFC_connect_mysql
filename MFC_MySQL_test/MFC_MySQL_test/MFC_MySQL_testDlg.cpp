
// MFC_MySQL_testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_MySQL_test.h"
#include "MFC_MySQL_testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFC_MySQL_testDlg 对话框




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


// CMFC_MySQL_testDlg 消息处理程序

BOOL CMFC_MySQL_testDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_MySQL_testDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC_MySQL_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_MySQL_testDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// 创建 SQL 语句字符串
	CString sql_insert;
	sql_insert.Format(_T("insert into emp_test(id, name, salary) values (%s, %s, %s);"), local_id, local_name, local_salary);
	//CString 转char *
	string sql_Insert=transformPlus.toString(sql_insert);
	const char  * sql=sql_Insert.c_str();
	// 执行 sql 语句。
	// mysql_query() 的返回值份很多情形， 进行判断使要注意。
	if(mysql_query(&local_mysql,sql)==0)
	{   
		AfxMessageBox(_T("insert succeed!"));   
	}else{
		AfxMessageBox(_T("insert failed!"));
	}
	// 关闭 local_mysql 所关联的数据库连接， 一般情况下不用写。
	mysql_close(&local_mysql);
	UpdateData(FALSE);

}


void CMFC_MySQL_testDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	
	OnCancel();
}

void CMFC_MySQL_testDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// 将用户在编辑框的输入放入变量， 这里我只实现了通过 id 查找。
	CString local_id = m_input_id.GetBuffer();
	//CString local_name = m_input_name.GetBuffer();
	//CString local_salary = m_input_salary.GetBuffer();
	// 创建 MYSQL 对象。
	MYSQL local_mysql;
	// 初始化 MYSQL 对象。
	mysql_init(&local_mysql);
	// 连接数据库。
	if(!mysql_real_connect(&local_mysql,"localhost","root","","test",3306,NULL,0))
	{
		AfxMessageBox(_T("connect to database failed!"));
	}
	else
	{
		AfxMessageBox(_T("connect to database success!"));
		// 设置字符集， 使程序支持中文。
		mysql_query(&local_mysql, "set names 'gb2312'");
	}

	//CString select_sql_all;
	CString select_sql_by_id;
	//CString select_sql_by_name;
	// 存放查询结果的变量
	MYSQL_RES* result;
	MYSQL_ROW row;
	//select_sql_all.Format("select * from emp_test");
	select_sql_by_id.Format(_T("select id, name, salary from emp_test where id = %s"), local_id.GetBuffer());
	string str=transformPlus.toString(select_sql_by_id);
	const char * query=str.c_str();
	// select_sql_by_name.Format("select id, name, salary from emp_test where name = \'%s\'", local_name.GetBuffer());
	int res = mysql_query(&local_mysql, query);
	// mysql_query 函数返回 0  表示 查询成功。
	if(res==0){
		// 获取查询结果，并保存在 result 里面。
		result = mysql_store_result(&local_mysql);
		// 获取查询结果的行数， 这里用不到，所以注释了。
		// int row_count = mysql_num_rows(result);
		// 循环地从查询结果中拿出一行， 并赋值给 row 变量。
		while(row = mysql_fetch_row(result)){
			CString local_id;
			CString local_name;
			CString local_salary;
			CString local_message;
			// 将从数据库中获取的数据 保存在字符串中， row[0], row[1], row[2], 分别表示一条查询结果中的第1， 2， 3 个字段， 我建立的 emp_test
			// 表中只有 3 个字段。
			local_id.Format(_T("%s"),row[0]);//row 赋值到local_id
			local_name.Format(_T("%s"),row[1]);
			local_salary.Format(_T("%s"),row[2]);
			// 将字符串连接起来，供消息框显示。
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
	// TODO: 在此添加控件通知处理程序代码
}
