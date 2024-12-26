#include "OAsystemUI.h"
#include<iostream>
#include"OAUtils.h"
#include<string>
#include<ctime>
#include"OADataCenter.h"

using namespace std;

//主界面
int OAsystemUI::displayMainPage()
{
	int Pageflag = MainPage;
	int choice = -1;
	cout << "****欢迎使用会议室预约系统****" << endl;
	cout << "******************************" << endl;
	cout << "	1.管理员登录" << endl;
	cout << "	2.普通用户登录" << endl;
	cout << "	3.注册新用户" << endl;
	cout << "	0.退出系统" << endl;
	cout << "******************************" << endl;
	cout << "请输入您的选择：";
	choice = OAUtils::getNum();
	enum MainChoice { exit = 0, adminlogin, userlogin, signup };
	switch (choice) {
	case MainChoice::exit:
		cout << "欢迎下次使用" << endl;
		Pageflag = Exit;
		system("pause");
		break;
	case MainChoice::adminlogin:
		Pageflag = LoginPageAdmin;
		break;
	case MainChoice::userlogin:
		Pageflag = LoginPageUser;
		break;
	case MainChoice::signup:
		Pageflag = signupPage;
		break;
	default:
		cout << "输入错误，请重新输入" << endl;
		system("pause");
		Pageflag = MainPage;
		break;
	}
	return Pageflag;
}
//管理员登录界面
int OAsystemUI::displayLoginPage(AdminData** ptr_admin)
{
	cout << "**********管理员登录**********" << endl;
	string name, password, depart;
	int pageflag = LoginPage(name, password);
	if (pageflag != Page::MainPage) {
		AdminData admin(name, password, "管理员");
		*ptr_admin = admin.Login();
		if (*ptr_admin) {
			pageflag = Page::AdminPage;
		}
		else {
			cout << "登陆失败，请重新登陆" << endl;
			system("pause");
			pageflag = Page::LoginPageAdmin;
		}
	}
	return pageflag;
}
//用户登录界面
int OAsystemUI::displayLoginPage(UserData** ptr_user)
{
	cout << "***********用户登录***********" << endl;
	string name, password, depart;
	int pageflag = LoginPage(name, password);
	if (pageflag != Page::MainPage) {
		UserData user(name, password, depart);
		*ptr_user = user.Login();
		if (*ptr_user) {
			pageflag = Page::UserPage;
		}
		else {
			cout << "登陆失败，请重新登陆" << endl;
			system("pause");
			pageflag = Page::LoginPageUser;
		}
	}
	return pageflag;
}
//登陆界面，用于获取name和passwo，由管理员和用户登录界面调用
int OAsystemUI::LoginPage(string& name, string& password)
{
	int pageflag = Page::MainPage;
	cout << "******************************" << endl;
	cout << "请输入您的账号(输入0返回上级)：";
	name = OAUtils::getStr();
	if (name != "0") {
		cout << "请输入您的密码(输入0返回上级)：";
		password = OAUtils::getStr();
		if (password != "0") {
			pageflag = -1;
		}
	}
	return pageflag;
}
//管理员界面
int OAsystemUI::displayAdminPage(AdminData* ptr_admin)
{
	int  choice = -1, pageflag = Page::AdminPage;
	cout << "************管理员************" << endl;
	cout << "******************************" << endl;
	cout << "	1.添加用户" << endl;
	cout << "	2.删除用户" << endl;
	cout << "	3.添加会议室" << endl;
	cout << "	4.删除会议室" << endl;
	cout << "	5.添加预约" << endl;
	cout << "	6.查看预约" << endl;
	cout << "	7.删除预约" << endl;
	cout << "	8.清空预约" << endl;
	cout << "	9.查看预约建议" << endl;
	cout << "	10.显示所有会议室" << endl;
	cout << "	0.退出登录" << endl;
	cout << "******************************" << endl;
	cout << "请输入您的选择：";
	choice = OAUtils::getNum();
	enum AdminChoice { Exit, Adduser, Deluser, Addroom, Delroom, Addapp, Showapp, Delapp, Cleapp, showappadvice, showmeetingroom };

	switch (choice) {
	case Exit:
		pageflag = Page::MainPage;
		break;
	case Adduser:
		pageflag = Page::AddUserPage;
		break;
	case Deluser:
		pageflag = Page::DelUserPage;
		break;
	case Addroom:
		pageflag = Page::AddRoomPage;
		break;
	case Delroom:
		pageflag = Page::DelRoomPage;
		break;
	case Addapp:
		pageflag = Page::AdminAddAppPage;
		break;
	case Showapp:
		pageflag = Page::showappPageAdmin;
		break;
	case Delapp:
		pageflag = Page::AdminDelAppPage;
		break;
	case Cleapp:
		pageflag = Page::CleAppPage;
		break;
	case showappadvice:
		pageflag = Page::showappadvicePageAdmin;
		break;
	case showmeetingroom:
		pageflag = Page::showmeetingroomPageAdmin;
		break;
	}

	return pageflag;
}
//获取展示页面编号
int OAsystemUI::displayUserPage(UserData* ptr_user)
{
	int  choice = -1, pageflag = Page::UserPage;
	cout << "*************用户*************" << endl;
	cout << "******************************" << endl;
	cout << "	1.添加预约" << endl;
	cout << "	2.删除预约" << endl;
	cout << "	3.查看预约" << endl;
	cout << "	4.查看预约建议" << endl;
	cout << "	5.显示所有会议室" << endl;
	cout << "	0.退出登录" << endl;
	cout << "******************************" << endl;
	cout << "请输入您的选择：";
	choice = OAUtils::getNum();
	enum { Exit, AddApp, DelApp, ShowApp, Showappadvice, showmeetingroom };
	switch (choice) {
	case Exit:
		pageflag = Page::MainPage;
		break;
	case AddApp:
		pageflag = Page::UserAddAppPage;
		break;
	case DelApp:
		pageflag = Page::UserDelAppPage;
		break;
	case ShowApp:
		pageflag = Page::showappPageUser;
		break;
	case Showappadvice:
		pageflag = Page::showappadvicePageUser;
		break;
	case showmeetingroom:
		pageflag = Page::showmeetingroomPageUser;
		break;
	}
	return pageflag;
}
//添加用户界面——管理员
int OAsystemUI::displayAddUserPage(AdminData* ptr_admin)
{
	cout << "******管理员——添加用户******" << endl;
	cout << "******************************" << endl;
	cout << "请输入要添加的用户名（输入0返回上级）：";
	string name = OAUtils::getStr();
	while (name != "0" && ptr_admin->checkName(name)) {
		cout << "该用户名已被占用，请重新输入：";
		name = OAUtils::getStr();
	}
	if (name != "0") {
		cout << "请输入密码（输入0返回上级）：";
		string password = OAUtils::getStr();
		if (password != "0") {
			cout << "请输入部门（输入0返回上级）：";
			string depart = OAUtils::getStr();
			if (depart != "0") {
				ptr_admin->AddUser(UserData(name, password, depart));
				cout << "添加用户成功" << endl;
				system("pause");
			}
		}
	}
	return Page::AdminPage;
}
//删除用户界面——管理员
int OAsystemUI::displayDelUserPage(const AdminData* ptr_admin)
{
	cout << "******管理员——删除用户******" << endl;
	cout << "******************************" << endl;
	if (ptr_admin->showUser()) {
		cout << "请输入要删除的用户名（输入0返回上级）：";
		string name = OAUtils::getStr();
		while (name != "0" && !ptr_admin->checkName(name)) {
			cout << "该用户不存在，请重新输入（输入0返回上级）：";
			name = OAUtils::getStr();
		}
		if (name != "0") {
			cout << "请输入管理员密码确定删除（输入0取消）：";
			string password = OAUtils::getStr();
			while (password != "0" && password != ptr_admin->getPasw()) {
				cout << "管理员密码错误，请重新输入（输入0取消）：";
				password = OAUtils::getStr();
			}
			if (password != "0") {
				ptr_admin->DelUser(name);
				cout << "删除用户成功" << endl;
			}
		}
	}
	system("pause");
	return Page::AdminPage;
}
//添加会议室界面——管理员
int OAsystemUI::displayAddRoomPage(AdminData* ptr_admin)
{
	cout << "*****管理员——添加会议室*****" << endl;
	cout << "******************************" << endl;
	cout << "请输入会议室门牌号：";
	int id = OAUtils::getNum();
	if (ptr_admin->AddMeetingRoom(id)) {
		cout << "会议室添加成功" << endl;
	}
	else {
		cout << "该会议室已存在" << endl;
	}
	system("pause");
	return Page::AdminPage;
}
//删除会议室界面——管理员
int OAsystemUI::displayDelRoomPage(AdminData* ptr_admin)
{
	cout << "*****管理员——删除会议室*****" << endl;
	cout << "******************************" << endl;
	if (ptr_admin->showRoom()) {
		cout << "请输入会议室门牌号：";
		int id = OAUtils::getNum();
		if (ptr_admin->DelMeetingRoom(id)) {
			cout << "会议室删除成功" << endl;
		}
		else {
			cout << "该会议室不存在" << endl;
		}
	}
	system("pause");
	return Page::AdminPage;
}
//管理员添加预约界面
int OAsystemUI::displayAddAppPage(AdminData* ptr_admin)
{
	int choice = -1, pageflag = Page::AdminPage;
	cout << "**********管理员预约**********" << endl;
	cout << "******************************" << endl;
	AddAppPage(ptr_admin);
	return pageflag;
}
//用户添加预约界面
int OAsystemUI::displayAddAppPage(UserData* ptr_user)
{
	int choice = -1, pageflag = Page::UserPage;
	cout << "***********用户预约***********" << endl;
	cout << "******************************" << endl;
	AddAppPage(ptr_user);
	return pageflag;
}


//预约界面
int OAsystemUI::AddAppPage(UserData* ptr_data)
{
	time_t t1 = time(nullptr);

	// 使用 localtime_s 替代 localtime，确保更安全
	tm local_time = {}; // 创建一个 tm 结构来存储本地时间
	if (localtime_s(&local_time, &t1) != 0) {
		cout << "获取本地时间失败" << endl;
		return Page::AdminPage;
	}

	tm t = {};  // 初始化 tm 结构
	t.tm_year = 1900 + local_time.tm_year;
	t.tm_mon = 1 + local_time.tm_mon;
	t.tm_mday = local_time.tm_mday;

	cout << "会议室只可预约当天的时间(07:00-23:00)" << endl; 
	cout << "当前日期为: " << t.tm_year << "-"
		<< t.tm_mon << "-"
		<< t.tm_mday << endl;

	t.tm_year -= 1900;
	t.tm_mon -= 1;

	cout << "所有可预约会议室如下：" << endl;
	ptr_data->showRoom();

	cout << endl << "已经预约的会议室详情如下：" << endl;
	ptr_data->showApp();

	cout << endl <<  "请输入您要预约的开始时间(小时)(输入-1返回上级)：";
	t.tm_hour = OAUtils::getNum();
	if (t.tm_hour != -1) {
		while (t.tm_hour < 7 || t.tm_hour > 23) {
			cout << "输入有误，请重新输入（输入-1返回上级）：";
			t.tm_hour = OAUtils::getNum();
			if (t.tm_hour == -1) break;
		}
		if (t.tm_hour != -1) {
			cout << "请输入您要预约的开始时间(分)(输入-1返回上级)：";
			t.tm_min = OAUtils::getNum();
			if (t.tm_min != -1) {
				while (t.tm_min < 0 || t.tm_min >= 60) {
					cout << "输入有误，请重新输入（输入-1返回上级）：";
					t.tm_min = OAUtils::getNum();
					if (t.tm_min == -1) break;
				}
				if (t.tm_min != -1) {
					cout << "请输入您预约的会议时长（单位：分钟）(输入-1返回上级）：";
					time_t duration = OAUtils::getNum();
					if (duration != -1) {
						while (t.tm_hour * 60 + t.tm_min + duration > 23 * 60) {
							cout << "超出会议室开放时间，请重新输入预约的会议时长（输入-1返回上级）：";
							duration = OAUtils::getNum();
							if (duration == -1) break;
						}
						if (duration != -1) {
							cout << "请输入您要预约的会议室:";
							int roomid = OAUtils::getNum();
							t.tm_sec = 0;
							
							int Addres = ptr_data->addApp(t, duration, roomid);
							if (Addres == 1) {
								OADataCenter::save_OADataCenter();
								cout << "添加预约成功" << endl;
							}
							else if (Addres == -1) {
								cout << "没有此会议室" << endl;
							}
							else if (Addres == 0) {
								cout << "该会议室预约时间冲突" << endl;
							}
							system("pause");
						}
					}
				}
			}
		}
	}
	return Page::AdminPage;
}

//管理员删除预约界面
int OAsystemUI::displayDelAppPage(AdminData* ptr_admin)
{
	int pageflag = Page::AdminPage;
	cout << "********管理员删除预约********" << endl;
	cout << "******************************" << endl;
	if (ptr_admin->showApp()) {
		DelAppPage(ptr_admin);
	}
	return pageflag;
}
//用户删除预约界面
int OAsystemUI::displayDelAppPage(UserData* ptr_user)
{
	int pageflag = Page::UserPage;
	cout << "*********用户删除预约*********" << endl;
	cout << "******************************" << endl;
	if (ptr_user->showApp1()) {
		DelAppPage(ptr_user);
	}
	return pageflag;
}
//删除预约界面
void OAsystemUI::DelAppPage(UserData* pt_data)
{
	bool res = true;
	cout << "请输入要删除预约的序号：";
	int id = OAUtils::getNum();
	id -= 1;
	if (!pt_data->delApp(id)) {
		cout << "删除失败" << endl;
		res = false;
	}
	else {
		cout << "删除成功" << endl;
	}
	system("pause");
}
//清空预约界面
int OAsystemUI::displayCleAppPage(AdminData* ptr_admin)
{
	cout << "********管理员清空预约********" << endl;
	cout << "******************************" << endl;
	cout << "是否确定清空所有预约？" << endl;
	cout << "1.是\t2.否" << endl;
	int choice = OAUtils::getNum();
	if (choice == 1) {
		ptr_admin->CleAppPage();
		cout << "已清空" << endl;
	}
	system("pause");
	return Page::AdminPage;
}

int OAsystemUI::displayshowappadvicePage(AdminData* ptr_admin)
{
	cout << "******管理员——显示预约建议******" << endl;
	cout << "**********************************" << endl;
	ptr_admin->showAppAdvice();
	system("pause");
	return Page::AdminPage;
}

int OAsystemUI::displayshowappadvicePage(UserData* pt_data)
{
	cout << "******用户——显示预约建议******" << endl;
	cout << "********************************" << endl;
	pt_data->showAppAdvice();
	system("pause");
	return Page::UserPage;
}

int OAsystemUI::displaysignupPage(AdminData* ptr_admin)
{
	cout << "**********用户注册页面**********" << endl;
	cout << "********************************" << endl;
	cout << "请输入要添加的用户名（输入0返回上级）：";
	string name = OAUtils::getStr();
	while (name != "0" && ptr_admin->checkName(name)) {
		cout << "该用户名已被占用，请重新输入：";
		name = OAUtils::getStr();
	}
	if (name != "0") {
		cout << "请输入密码（输入0返回上级）：";
		string password = OAUtils::getStr();
		if (password != "0") {
			cout << "请输入部门（输入0返回上级）：";
			string depart = OAUtils::getStr();
			if (depart != "0") {
				ptr_admin->AddUser(UserData(name, password, depart));
				cout << "添加用户成功" << endl;
				system("pause");
			}
		}
	}
	return Page::MainPage;
}

int OAsystemUI::displayshowmeetingroomPageuser(UserData* ptr_user) {
	cout << "********用户--显示会议室********" << endl;
	cout << "********************************" << endl;
	ptr_user->showRoom();
	system("pause");
	return Page::UserPage;
}
int OAsystemUI::displayshowmeetingroomPageadmin(AdminData* ptr_admin) {
	cout << "********管理员--显示会议室********" << endl;
	cout << "**********************************" << endl;
	ptr_admin->showRoom();
	system("pause");
	return Page::AdminPage;
}

int OAsystemUI::displayshowappPageUser(UserData* ptr_user) {
	cout << "********用户--显示预约界面********" << endl;
	cout << "**********************************" << endl;
	ptr_user->showApp1();
	return Page::UserPage;
}

int OAsystemUI::displayshowappPageAdmin(AdminData* ptr_admin) {
	cout << "*******管理员--显示预约界面*******" << endl;
	cout << "**********************************" << endl;
	ptr_admin->showApp();
	return Page::AdminPage;
}