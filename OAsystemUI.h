#pragma once
#include"OADataCenter.h"
#include"OAUtils.h"
//UI界面flag
enum Page {
	Exit,				//退出
	MainPage,			//主界面
	LoginPageAdmin,		//管理员登录界面
	LoginPageUser,		//用户登录界面
	AdminPage,			//管理员界面
	UserPage,			//用户界面
	AddUserPage,		//添加用户界面——管理员
	DelUserPage,		//删除用户界面——管理员
	AddRoomPage,		//添加会议室界面——管理员
	DelRoomPage,		//删除会议室界面——管理员
	AdminAddAppPage,	//管理员添加预约
	UserAddAppPage,		//用户添加预约
	AdminDelAppPage,	//管理员删除预约
	UserDelAppPage,		//用户删除预约
	CleAppPage,			//清空所有预约——管理员
	showappadvicePageUser,   //显示预约建议
	showappadvicePageAdmin,   //显示预约建议
	showmeetingroomPageAdmin,	//显示会议室界面——管理员
	showmeetingroomPageUser,	//显示会议室界面——用户
	signupPage,			//注册界面
	showappPageUser,	//显示会议室界面——用户
	showappPageAdmin,	//显示会议室界面——管理员
};
//UI系统
class OAsystemUI {
public:
	static int displayMainPage();											//主界面函数

	static int displayLoginPage(AdminData** ptr_admin);						//管理员登录界面函数
	static int displayLoginPage(UserData** ptr_user);						//用户登录界面函数
	static int LoginPage(string& name, string& password);					//登陆界面函数，主要用于获取name,password

	static int displayAdminPage(AdminData* ptr_admin);						//管理员界面函数
	static int displayUserPage(UserData* ptr_user);							//用户界面函数

	static int displayAddUserPage(AdminData* ptr_admin);					//添加用户界面函数——管理员
	static int displayDelUserPage(const AdminData* ptr_admin);				//删除用户界面函数——管理员
	static int displayAddRoomPage(AdminData* ptr_admin);					//添加会议室界面函数——管理员
	static int displayDelRoomPage(AdminData* ptr_admin);					//删除会议室界面函数——管理员

	static int displayAddAppPage(AdminData* ptr_admin);						//管理员添加预约
	static int displayAddAppPage(UserData* ptr_user);						//用户添加预约
	static int AddAppPage(UserData* ptr_data);								//预约界面
	static int displayDelAppPage(AdminData* ptr_admin);						//管理员删除预约
	static int displayDelAppPage(UserData* ptr_user);						//用户删除预约
	static void DelAppPage(UserData* pt_data);								//删除预约
	static int displayCleAppPage(AdminData* ptr_admin);						//清空所有预约界面函数——管理员
	static int displayshowappadvicePage(AdminData* ptr_admin);              //显示预约建议界面——管理员
	static int displayshowappadvicePage(UserData* ptr_admin);               //显示预约建议界面——用户
	static int displaysignupPage(AdminData* ptr_admin);						//注册界面函数
	static int displayshowmeetingroomPageuser(UserData* ptr_user);			//注册界面函数
	static int displayshowmeetingroomPageadmin(AdminData* ptr_admin);	    //显示会议室界面——管理员
	static int displayshowappPageAdmin(AdminData* ptr_admin);                 //显示预约界面——管理员
	static int displayshowappPageUser(UserData* ptr_user);                   //显示预约界面——用户
};