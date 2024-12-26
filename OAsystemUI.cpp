#include "OAsystemUI.h"
#include<iostream>
#include"OAUtils.h"
#include<string>
#include<ctime>
#include"OADataCenter.h"

using namespace std;

//������
int OAsystemUI::displayMainPage()
{
	int Pageflag = MainPage;
	int choice = -1;
	cout << "****��ӭʹ�û�����ԤԼϵͳ****" << endl;
	cout << "******************************" << endl;
	cout << "	1.����Ա��¼" << endl;
	cout << "	2.��ͨ�û���¼" << endl;
	cout << "	3.ע�����û�" << endl;
	cout << "	0.�˳�ϵͳ" << endl;
	cout << "******************************" << endl;
	cout << "����������ѡ��";
	choice = OAUtils::getNum();
	enum MainChoice { exit = 0, adminlogin, userlogin, signup };
	switch (choice) {
	case MainChoice::exit:
		cout << "��ӭ�´�ʹ��" << endl;
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
		cout << "�����������������" << endl;
		system("pause");
		Pageflag = MainPage;
		break;
	}
	return Pageflag;
}
//����Ա��¼����
int OAsystemUI::displayLoginPage(AdminData** ptr_admin)
{
	cout << "**********����Ա��¼**********" << endl;
	string name, password, depart;
	int pageflag = LoginPage(name, password);
	if (pageflag != Page::MainPage) {
		AdminData admin(name, password, "����Ա");
		*ptr_admin = admin.Login();
		if (*ptr_admin) {
			pageflag = Page::AdminPage;
		}
		else {
			cout << "��½ʧ�ܣ������µ�½" << endl;
			system("pause");
			pageflag = Page::LoginPageAdmin;
		}
	}
	return pageflag;
}
//�û���¼����
int OAsystemUI::displayLoginPage(UserData** ptr_user)
{
	cout << "***********�û���¼***********" << endl;
	string name, password, depart;
	int pageflag = LoginPage(name, password);
	if (pageflag != Page::MainPage) {
		UserData user(name, password, depart);
		*ptr_user = user.Login();
		if (*ptr_user) {
			pageflag = Page::UserPage;
		}
		else {
			cout << "��½ʧ�ܣ������µ�½" << endl;
			system("pause");
			pageflag = Page::LoginPageUser;
		}
	}
	return pageflag;
}
//��½���棬���ڻ�ȡname��passwo���ɹ���Ա���û���¼�������
int OAsystemUI::LoginPage(string& name, string& password)
{
	int pageflag = Page::MainPage;
	cout << "******************************" << endl;
	cout << "�����������˺�(����0�����ϼ�)��";
	name = OAUtils::getStr();
	if (name != "0") {
		cout << "��������������(����0�����ϼ�)��";
		password = OAUtils::getStr();
		if (password != "0") {
			pageflag = -1;
		}
	}
	return pageflag;
}
//����Ա����
int OAsystemUI::displayAdminPage(AdminData* ptr_admin)
{
	int  choice = -1, pageflag = Page::AdminPage;
	cout << "************����Ա************" << endl;
	cout << "******************************" << endl;
	cout << "	1.����û�" << endl;
	cout << "	2.ɾ���û�" << endl;
	cout << "	3.��ӻ�����" << endl;
	cout << "	4.ɾ��������" << endl;
	cout << "	5.���ԤԼ" << endl;
	cout << "	6.�鿴ԤԼ" << endl;
	cout << "	7.ɾ��ԤԼ" << endl;
	cout << "	8.���ԤԼ" << endl;
	cout << "	9.�鿴ԤԼ����" << endl;
	cout << "	10.��ʾ���л�����" << endl;
	cout << "	0.�˳���¼" << endl;
	cout << "******************************" << endl;
	cout << "����������ѡ��";
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
//��ȡչʾҳ����
int OAsystemUI::displayUserPage(UserData* ptr_user)
{
	int  choice = -1, pageflag = Page::UserPage;
	cout << "*************�û�*************" << endl;
	cout << "******************************" << endl;
	cout << "	1.���ԤԼ" << endl;
	cout << "	2.ɾ��ԤԼ" << endl;
	cout << "	3.�鿴ԤԼ" << endl;
	cout << "	4.�鿴ԤԼ����" << endl;
	cout << "	5.��ʾ���л�����" << endl;
	cout << "	0.�˳���¼" << endl;
	cout << "******************************" << endl;
	cout << "����������ѡ��";
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
//����û����桪������Ա
int OAsystemUI::displayAddUserPage(AdminData* ptr_admin)
{
	cout << "******����Ա��������û�******" << endl;
	cout << "******************************" << endl;
	cout << "������Ҫ��ӵ��û���������0�����ϼ�����";
	string name = OAUtils::getStr();
	while (name != "0" && ptr_admin->checkName(name)) {
		cout << "���û����ѱ�ռ�ã����������룺";
		name = OAUtils::getStr();
	}
	if (name != "0") {
		cout << "���������루����0�����ϼ�����";
		string password = OAUtils::getStr();
		if (password != "0") {
			cout << "�����벿�ţ�����0�����ϼ�����";
			string depart = OAUtils::getStr();
			if (depart != "0") {
				ptr_admin->AddUser(UserData(name, password, depart));
				cout << "����û��ɹ�" << endl;
				system("pause");
			}
		}
	}
	return Page::AdminPage;
}
//ɾ���û����桪������Ա
int OAsystemUI::displayDelUserPage(const AdminData* ptr_admin)
{
	cout << "******����Ա����ɾ���û�******" << endl;
	cout << "******************************" << endl;
	if (ptr_admin->showUser()) {
		cout << "������Ҫɾ�����û���������0�����ϼ�����";
		string name = OAUtils::getStr();
		while (name != "0" && !ptr_admin->checkName(name)) {
			cout << "���û������ڣ����������루����0�����ϼ�����";
			name = OAUtils::getStr();
		}
		if (name != "0") {
			cout << "���������Ա����ȷ��ɾ��������0ȡ������";
			string password = OAUtils::getStr();
			while (password != "0" && password != ptr_admin->getPasw()) {
				cout << "����Ա����������������루����0ȡ������";
				password = OAUtils::getStr();
			}
			if (password != "0") {
				ptr_admin->DelUser(name);
				cout << "ɾ���û��ɹ�" << endl;
			}
		}
	}
	system("pause");
	return Page::AdminPage;
}
//��ӻ����ҽ��桪������Ա
int OAsystemUI::displayAddRoomPage(AdminData* ptr_admin)
{
	cout << "*****����Ա������ӻ�����*****" << endl;
	cout << "******************************" << endl;
	cout << "��������������ƺţ�";
	int id = OAUtils::getNum();
	if (ptr_admin->AddMeetingRoom(id)) {
		cout << "��������ӳɹ�" << endl;
	}
	else {
		cout << "�û������Ѵ���" << endl;
	}
	system("pause");
	return Page::AdminPage;
}
//ɾ�������ҽ��桪������Ա
int OAsystemUI::displayDelRoomPage(AdminData* ptr_admin)
{
	cout << "*****����Ա����ɾ��������*****" << endl;
	cout << "******************************" << endl;
	if (ptr_admin->showRoom()) {
		cout << "��������������ƺţ�";
		int id = OAUtils::getNum();
		if (ptr_admin->DelMeetingRoom(id)) {
			cout << "������ɾ���ɹ�" << endl;
		}
		else {
			cout << "�û����Ҳ�����" << endl;
		}
	}
	system("pause");
	return Page::AdminPage;
}
//����Ա���ԤԼ����
int OAsystemUI::displayAddAppPage(AdminData* ptr_admin)
{
	int choice = -1, pageflag = Page::AdminPage;
	cout << "**********����ԱԤԼ**********" << endl;
	cout << "******************************" << endl;
	AddAppPage(ptr_admin);
	return pageflag;
}
//�û����ԤԼ����
int OAsystemUI::displayAddAppPage(UserData* ptr_user)
{
	int choice = -1, pageflag = Page::UserPage;
	cout << "***********�û�ԤԼ***********" << endl;
	cout << "******************************" << endl;
	AddAppPage(ptr_user);
	return pageflag;
}


//ԤԼ����
int OAsystemUI::AddAppPage(UserData* ptr_data)
{
	time_t t1 = time(nullptr);

	// ʹ�� localtime_s ��� localtime��ȷ������ȫ
	tm local_time = {}; // ����һ�� tm �ṹ���洢����ʱ��
	if (localtime_s(&local_time, &t1) != 0) {
		cout << "��ȡ����ʱ��ʧ��" << endl;
		return Page::AdminPage;
	}

	tm t = {};  // ��ʼ�� tm �ṹ
	t.tm_year = 1900 + local_time.tm_year;
	t.tm_mon = 1 + local_time.tm_mon;
	t.tm_mday = local_time.tm_mday;

	cout << "������ֻ��ԤԼ�����ʱ��(07:00-23:00)" << endl; 
	cout << "��ǰ����Ϊ: " << t.tm_year << "-"
		<< t.tm_mon << "-"
		<< t.tm_mday << endl;

	t.tm_year -= 1900;
	t.tm_mon -= 1;

	cout << "���п�ԤԼ���������£�" << endl;
	ptr_data->showRoom();

	cout << endl << "�Ѿ�ԤԼ�Ļ������������£�" << endl;
	ptr_data->showApp();

	cout << endl <<  "��������ҪԤԼ�Ŀ�ʼʱ��(Сʱ)(����-1�����ϼ�)��";
	t.tm_hour = OAUtils::getNum();
	if (t.tm_hour != -1) {
		while (t.tm_hour < 7 || t.tm_hour > 23) {
			cout << "�����������������루����-1�����ϼ�����";
			t.tm_hour = OAUtils::getNum();
			if (t.tm_hour == -1) break;
		}
		if (t.tm_hour != -1) {
			cout << "��������ҪԤԼ�Ŀ�ʼʱ��(��)(����-1�����ϼ�)��";
			t.tm_min = OAUtils::getNum();
			if (t.tm_min != -1) {
				while (t.tm_min < 0 || t.tm_min >= 60) {
					cout << "�����������������루����-1�����ϼ�����";
					t.tm_min = OAUtils::getNum();
					if (t.tm_min == -1) break;
				}
				if (t.tm_min != -1) {
					cout << "��������ԤԼ�Ļ���ʱ������λ�����ӣ�(����-1�����ϼ�����";
					time_t duration = OAUtils::getNum();
					if (duration != -1) {
						while (t.tm_hour * 60 + t.tm_min + duration > 23 * 60) {
							cout << "���������ҿ���ʱ�䣬����������ԤԼ�Ļ���ʱ��������-1�����ϼ�����";
							duration = OAUtils::getNum();
							if (duration == -1) break;
						}
						if (duration != -1) {
							cout << "��������ҪԤԼ�Ļ�����:";
							int roomid = OAUtils::getNum();
							t.tm_sec = 0;
							
							int Addres = ptr_data->addApp(t, duration, roomid);
							if (Addres == 1) {
								OADataCenter::save_OADataCenter();
								cout << "���ԤԼ�ɹ�" << endl;
							}
							else if (Addres == -1) {
								cout << "û�д˻�����" << endl;
							}
							else if (Addres == 0) {
								cout << "�û�����ԤԼʱ���ͻ" << endl;
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

//����Աɾ��ԤԼ����
int OAsystemUI::displayDelAppPage(AdminData* ptr_admin)
{
	int pageflag = Page::AdminPage;
	cout << "********����Աɾ��ԤԼ********" << endl;
	cout << "******************************" << endl;
	if (ptr_admin->showApp()) {
		DelAppPage(ptr_admin);
	}
	return pageflag;
}
//�û�ɾ��ԤԼ����
int OAsystemUI::displayDelAppPage(UserData* ptr_user)
{
	int pageflag = Page::UserPage;
	cout << "*********�û�ɾ��ԤԼ*********" << endl;
	cout << "******************************" << endl;
	if (ptr_user->showApp1()) {
		DelAppPage(ptr_user);
	}
	return pageflag;
}
//ɾ��ԤԼ����
void OAsystemUI::DelAppPage(UserData* pt_data)
{
	bool res = true;
	cout << "������Ҫɾ��ԤԼ����ţ�";
	int id = OAUtils::getNum();
	id -= 1;
	if (!pt_data->delApp(id)) {
		cout << "ɾ��ʧ��" << endl;
		res = false;
	}
	else {
		cout << "ɾ���ɹ�" << endl;
	}
	system("pause");
}
//���ԤԼ����
int OAsystemUI::displayCleAppPage(AdminData* ptr_admin)
{
	cout << "********����Ա���ԤԼ********" << endl;
	cout << "******************************" << endl;
	cout << "�Ƿ�ȷ���������ԤԼ��" << endl;
	cout << "1.��\t2.��" << endl;
	int choice = OAUtils::getNum();
	if (choice == 1) {
		ptr_admin->CleAppPage();
		cout << "�����" << endl;
	}
	system("pause");
	return Page::AdminPage;
}

int OAsystemUI::displayshowappadvicePage(AdminData* ptr_admin)
{
	cout << "******����Ա������ʾԤԼ����******" << endl;
	cout << "**********************************" << endl;
	ptr_admin->showAppAdvice();
	system("pause");
	return Page::AdminPage;
}

int OAsystemUI::displayshowappadvicePage(UserData* pt_data)
{
	cout << "******�û�������ʾԤԼ����******" << endl;
	cout << "********************************" << endl;
	pt_data->showAppAdvice();
	system("pause");
	return Page::UserPage;
}

int OAsystemUI::displaysignupPage(AdminData* ptr_admin)
{
	cout << "**********�û�ע��ҳ��**********" << endl;
	cout << "********************************" << endl;
	cout << "������Ҫ��ӵ��û���������0�����ϼ�����";
	string name = OAUtils::getStr();
	while (name != "0" && ptr_admin->checkName(name)) {
		cout << "���û����ѱ�ռ�ã����������룺";
		name = OAUtils::getStr();
	}
	if (name != "0") {
		cout << "���������루����0�����ϼ�����";
		string password = OAUtils::getStr();
		if (password != "0") {
			cout << "�����벿�ţ�����0�����ϼ�����";
			string depart = OAUtils::getStr();
			if (depart != "0") {
				ptr_admin->AddUser(UserData(name, password, depart));
				cout << "����û��ɹ�" << endl;
				system("pause");
			}
		}
	}
	return Page::MainPage;
}

int OAsystemUI::displayshowmeetingroomPageuser(UserData* ptr_user) {
	cout << "********�û�--��ʾ������********" << endl;
	cout << "********************************" << endl;
	ptr_user->showRoom();
	system("pause");
	return Page::UserPage;
}
int OAsystemUI::displayshowmeetingroomPageadmin(AdminData* ptr_admin) {
	cout << "********����Ա--��ʾ������********" << endl;
	cout << "**********************************" << endl;
	ptr_admin->showRoom();
	system("pause");
	return Page::AdminPage;
}

int OAsystemUI::displayshowappPageUser(UserData* ptr_user) {
	cout << "********�û�--��ʾԤԼ����********" << endl;
	cout << "**********************************" << endl;
	ptr_user->showApp1();
	return Page::UserPage;
}

int OAsystemUI::displayshowappPageAdmin(AdminData* ptr_admin) {
	cout << "*******����Ա--��ʾԤԼ����*******" << endl;
	cout << "**********************************" << endl;
	ptr_admin->showApp();
	return Page::AdminPage;
}