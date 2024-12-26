#include<iostream>
using namespace std;
#include"OAsystemUI.h"
#include"OAUtils.h"

int main(int argc, char const* argv[]) {
	int exit = 0, Pageflag = MainPage;
	AdminData* ptr_admin = nullptr;
	UserData* ptr_user = nullptr;
	OADataCenter::init_OADataCenter();
	while (!exit) {
		system("cls");
		switch (Pageflag) {
		case Exit:
			exit = 1;
			break;
		case MainPage:			//主界面
			Pageflag = OAsystemUI::displayMainPage();
			break;
		case LoginPageAdmin:	//管理员登录界面
			Pageflag = OAsystemUI::displayLoginPage(&ptr_admin);
			break;
		case LoginPageUser:		//用户登录界面
			Pageflag = OAsystemUI::displayLoginPage(&ptr_user);
			break;
		case AdminPage:			//管理员界面
			Pageflag = OAsystemUI::displayAdminPage(ptr_admin);
			break;
		case UserPage:			//用户界面
			Pageflag = OAsystemUI::displayUserPage(ptr_user);
			break;
		case AddUserPage:		//添加用户界面——管理员
			Pageflag = OAsystemUI::displayAddUserPage(ptr_admin);
			break;
		case DelUserPage:		//删除用户界面——管理员
			Pageflag = OAsystemUI::displayDelUserPage(ptr_admin);
			break;
		case AddRoomPage:		//添加会议室界面——管理员
			Pageflag = OAsystemUI::displayAddRoomPage(ptr_admin);
			break;
		case DelRoomPage:		//删除会议室界面——管理员
			Pageflag = OAsystemUI::displayDelRoomPage(ptr_admin);
			break;
		case AdminAddAppPage:	//管理员添加预约
			Pageflag = OAsystemUI::displayAddAppPage(ptr_admin);
			break;
		case UserAddAppPage:	//用户添加预约
			Pageflag = OAsystemUI::displayAddAppPage(ptr_user);
			break;
		case AdminDelAppPage:	//管理员删除预约
			Pageflag = OAsystemUI::displayDelAppPage(ptr_admin);
			break;
		case UserDelAppPage:	//用户删除预约
			Pageflag = OAsystemUI::displayDelAppPage(ptr_user);
			break;
		case CleAppPage:		//清空所有预约——管理员
			Pageflag = OAsystemUI::displayCleAppPage(ptr_admin);
			break;
		case showappadvicePageUser://用户显示预约建议
			Pageflag = OAsystemUI::displayshowappadvicePage(ptr_user);
			break;
		case showappadvicePageAdmin://管理员显示预约建议
			Pageflag = OAsystemUI::displayshowappadvicePage(ptr_admin);
			break;
		case signupPage: //用户注册界面——管理员
			Pageflag = OAsystemUI::displaysignupPage(ptr_admin);
			break;
		case showmeetingroomPageAdmin://管理员显示会议室界面
			Pageflag = OAsystemUI::displayshowmeetingroomPageadmin(ptr_admin);
			break;
		case showmeetingroomPageUser://用户显示会议室界面
			Pageflag = OAsystemUI::displayshowmeetingroomPageuser(ptr_user);
			break;
		case showappPageAdmin://管理员显示预约界面
			Pageflag = OAsystemUI::displayshowappPageAdmin(ptr_admin);
			break;
		case showappPageUser://用户显示预约界面
			Pageflag = OAsystemUI::displayshowappPageUser(ptr_user);
			break;
		}
	}
	OADataCenter::save_OADataCenter();
	return 0;
}