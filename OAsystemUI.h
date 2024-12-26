#pragma once
#include"OADataCenter.h"
#include"OAUtils.h"
//UI����flag
enum Page {
	Exit,				//�˳�
	MainPage,			//������
	LoginPageAdmin,		//����Ա��¼����
	LoginPageUser,		//�û���¼����
	AdminPage,			//����Ա����
	UserPage,			//�û�����
	AddUserPage,		//����û����桪������Ա
	DelUserPage,		//ɾ���û����桪������Ա
	AddRoomPage,		//��ӻ����ҽ��桪������Ա
	DelRoomPage,		//ɾ�������ҽ��桪������Ա
	AdminAddAppPage,	//����Ա���ԤԼ
	UserAddAppPage,		//�û����ԤԼ
	AdminDelAppPage,	//����Աɾ��ԤԼ
	UserDelAppPage,		//�û�ɾ��ԤԼ
	CleAppPage,			//�������ԤԼ��������Ա
	showappadvicePageUser,   //��ʾԤԼ����
	showappadvicePageAdmin,   //��ʾԤԼ����
	showmeetingroomPageAdmin,	//��ʾ�����ҽ��桪������Ա
	showmeetingroomPageUser,	//��ʾ�����ҽ��桪���û�
	signupPage,			//ע�����
	showappPageUser,	//��ʾ�����ҽ��桪���û�
	showappPageAdmin,	//��ʾ�����ҽ��桪������Ա
};
//UIϵͳ
class OAsystemUI {
public:
	static int displayMainPage();											//�����溯��

	static int displayLoginPage(AdminData** ptr_admin);						//����Ա��¼���溯��
	static int displayLoginPage(UserData** ptr_user);						//�û���¼���溯��
	static int LoginPage(string& name, string& password);					//��½���溯������Ҫ���ڻ�ȡname,password

	static int displayAdminPage(AdminData* ptr_admin);						//����Ա���溯��
	static int displayUserPage(UserData* ptr_user);							//�û����溯��

	static int displayAddUserPage(AdminData* ptr_admin);					//����û����溯����������Ա
	static int displayDelUserPage(const AdminData* ptr_admin);				//ɾ���û����溯����������Ա
	static int displayAddRoomPage(AdminData* ptr_admin);					//��ӻ����ҽ��溯����������Ա
	static int displayDelRoomPage(AdminData* ptr_admin);					//ɾ�������ҽ��溯����������Ա

	static int displayAddAppPage(AdminData* ptr_admin);						//����Ա���ԤԼ
	static int displayAddAppPage(UserData* ptr_user);						//�û����ԤԼ
	static int AddAppPage(UserData* ptr_data);								//ԤԼ����
	static int displayDelAppPage(AdminData* ptr_admin);						//����Աɾ��ԤԼ
	static int displayDelAppPage(UserData* ptr_user);						//�û�ɾ��ԤԼ
	static void DelAppPage(UserData* pt_data);								//ɾ��ԤԼ
	static int displayCleAppPage(AdminData* ptr_admin);						//�������ԤԼ���溯����������Ա
	static int displayshowappadvicePage(AdminData* ptr_admin);              //��ʾԤԼ������桪������Ա
	static int displayshowappadvicePage(UserData* ptr_admin);               //��ʾԤԼ������桪���û�
	static int displaysignupPage(AdminData* ptr_admin);						//ע����溯��
	static int displayshowmeetingroomPageuser(UserData* ptr_user);			//ע����溯��
	static int displayshowmeetingroomPageadmin(AdminData* ptr_admin);	    //��ʾ�����ҽ��桪������Ա
	static int displayshowappPageAdmin(AdminData* ptr_admin);                 //��ʾԤԼ���桪������Ա
	static int displayshowappPageUser(UserData* ptr_user);                   //��ʾԤԼ���桪���û�
};