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
		case MainPage:			//������
			Pageflag = OAsystemUI::displayMainPage();
			break;
		case LoginPageAdmin:	//����Ա��¼����
			Pageflag = OAsystemUI::displayLoginPage(&ptr_admin);
			break;
		case LoginPageUser:		//�û���¼����
			Pageflag = OAsystemUI::displayLoginPage(&ptr_user);
			break;
		case AdminPage:			//����Ա����
			Pageflag = OAsystemUI::displayAdminPage(ptr_admin);
			break;
		case UserPage:			//�û�����
			Pageflag = OAsystemUI::displayUserPage(ptr_user);
			break;
		case AddUserPage:		//����û����桪������Ա
			Pageflag = OAsystemUI::displayAddUserPage(ptr_admin);
			break;
		case DelUserPage:		//ɾ���û����桪������Ա
			Pageflag = OAsystemUI::displayDelUserPage(ptr_admin);
			break;
		case AddRoomPage:		//��ӻ����ҽ��桪������Ա
			Pageflag = OAsystemUI::displayAddRoomPage(ptr_admin);
			break;
		case DelRoomPage:		//ɾ�������ҽ��桪������Ա
			Pageflag = OAsystemUI::displayDelRoomPage(ptr_admin);
			break;
		case AdminAddAppPage:	//����Ա���ԤԼ
			Pageflag = OAsystemUI::displayAddAppPage(ptr_admin);
			break;
		case UserAddAppPage:	//�û����ԤԼ
			Pageflag = OAsystemUI::displayAddAppPage(ptr_user);
			break;
		case AdminDelAppPage:	//����Աɾ��ԤԼ
			Pageflag = OAsystemUI::displayDelAppPage(ptr_admin);
			break;
		case UserDelAppPage:	//�û�ɾ��ԤԼ
			Pageflag = OAsystemUI::displayDelAppPage(ptr_user);
			break;
		case CleAppPage:		//�������ԤԼ��������Ա
			Pageflag = OAsystemUI::displayCleAppPage(ptr_admin);
			break;
		case showappadvicePageUser://�û���ʾԤԼ����
			Pageflag = OAsystemUI::displayshowappadvicePage(ptr_user);
			break;
		case showappadvicePageAdmin://����Ա��ʾԤԼ����
			Pageflag = OAsystemUI::displayshowappadvicePage(ptr_admin);
			break;
		case signupPage: //�û�ע����桪������Ա
			Pageflag = OAsystemUI::displaysignupPage(ptr_admin);
			break;
		case showmeetingroomPageAdmin://����Ա��ʾ�����ҽ���
			Pageflag = OAsystemUI::displayshowmeetingroomPageadmin(ptr_admin);
			break;
		case showmeetingroomPageUser://�û���ʾ�����ҽ���
			Pageflag = OAsystemUI::displayshowmeetingroomPageuser(ptr_user);
			break;
		case showappPageAdmin://����Ա��ʾԤԼ����
			Pageflag = OAsystemUI::displayshowappPageAdmin(ptr_admin);
			break;
		case showappPageUser://�û���ʾԤԼ����
			Pageflag = OAsystemUI::displayshowappPageUser(ptr_user);
			break;
		}
	}
	OADataCenter::save_OADataCenter();
	return 0;
}