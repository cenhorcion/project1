#include "OADataCenter.h"
#include<algorithm>
#include<iomanip>
#include<sstream>
#include<fstream>
#include"OAUtils.h"
//�û���Ϣ�๹��
UserData::UserData() {}
UserData::UserData(string name, string password, string depart)
{
	_name = name;
	_password = password;
	_depart = depart;
}
//��ȡ�û��������롢����
string& UserData::getName()
{
	return _name;
}
string& UserData::getPasw()
{
	return _password;
}
string& UserData::getDepart()
{
	return _depart;
}
const string& UserData::getName() const
{
	return _name;
}
const string& UserData::getPasw() const
{
	return _password;
}
const string& UserData::getDepart() const
{
	return _depart;
}
//�û���¼
UserData* UserData::Login()
{
	return OADataCenter::Login(*this);
}
//�û����ԤԼ�����жϻ������Ƿ���ڣ��ж�ʱ���Ƿ��ͻ
int UserData::addApp(tm& t, time_t duration, MeetingRoom roomid)
{
	int res = 1;
	time_t t_time = mktime(&t);
	pair<_It_room, bool> respair = OADataCenter::checkRoom(roomid);
	if (!(respair.second)) {
		res = -1;
	}
	else if (!OADataCenter::checkTime(t_time, duration, roomid)) {
		res = 0;
	}
	else {
		Appointment app(t, duration, roomid, _name, _depart);
		OADataCenter::AddApp(app);
	}
	return res;
}
//ɾ��ԤԼ
bool UserData::delApp(int id)
{
	return OADataCenter::DelApp(*this, id);
}
//�鿴ԤԼ
bool UserData::showApp()
{
	bool res = OADataCenter::showApp(_name);
	return res;
}

bool UserData::showApp1()
{
	bool res = OADataCenter::showApp1(_name);
	return res;
}
//�����û���Ϣ���ļ�
void UserData::save(ofstream& ofs)
{
	OAUtils::save_str(ofs, _name);
	OAUtils::save_str(ofs, _password);
	OAUtils::save_str(ofs, _depart);
}
//���ļ���ȡ�û���Ϣ
void UserData::read(ifstream& ifs)
{
	OAUtils::read_str(ifs, _name);
	OAUtils::read_str(ifs, _password);
	OAUtils::read_str(ifs, _depart);
}

//����Ա���캯��
AdminData::AdminData() {}
AdminData::AdminData(string name, string password, string depart) :UserData(name, password, depart) {}
//����Ա��¼
AdminData* AdminData::Login()
{
	return OADataCenter::Login(*this);
}
//����Ա�鿴�����û�
bool AdminData::showUser()const
{
	return OADataCenter::showUser();
}
//����Ա�鿴���л�����
bool AdminData::showRoom()
{
	return OADataCenter::showRoom();
}

bool UserData::showRoom()
{
	return OADataCenter::showRoom();
}

bool AdminData::showAppAdvice() {
	return OADataCenter::showAppAdvice();
}

bool UserData::showAppAdvice() {
	return OADataCenter::showAppAdvice();
}


//����Ա����û����������������ĵ�����û�����
void AdminData::AddUser(const UserData& userdata)
{
	OADataCenter::AddUser(userdata);
}
//����Աɾ���û����������������ĵ�ɾ���û�����
void AdminData::DelUser(const string& name)const
{
	OADataCenter::DelUser(name);
}
//����Ա��ӻ����ҡ��������������ĵ���ӻ����Һ���
bool AdminData::AddMeetingRoom(int id)
{
	return OADataCenter::AddMeetingRoom(id);
}
//����Աɾ�������ҡ��������������ĵ�ɾ�������Һ���
bool AdminData::DelMeetingRoom(int roomid)
{
	return OADataCenter::DelMeetingRoom(roomid);
}
//����Ա�˶��û������Ƿ����
bool AdminData::checkName(const string& name)const
{
	return OADataCenter::checkName(name).second;
}

void AdminData::CleAppPage()
{
	OADataCenter::CleApp();
}

//ԤԼ�๹�캯��
Appointment::Appointment()
{
	this->_t = { 0 };
	this->_roomnum = 0;
	this->_duration = 0;
}
Appointment::Appointment(const tm& t, time_t duration, int roomid, string name, string depart)
{
	_t = t;
	_duration = duration;
	_roomnum = roomid;
	_username = name;
	_userdepart = depart;
}
//��ȡԤԼ��time_t��ʽʱ��
const time_t Appointment::getAppTime()const
{
	return mktime(const_cast<tm*>(&_t));  // ȥ�� const ���η�
}
//��ȡԤԼ��ʱ������
const time_t Appointment::getAppDuration()const
{
	return _duration;
}
//��ȡԤԼ�Ļ�����
const int Appointment::getRoomID() const
{
	return _roomnum;
}
//��ȡԤԼ�û�
const string& Appointment::getAppName()const
{
	return _username;
}
//��ȡԤԼ����
const string& Appointment::getAppdepart()const
{
	return _userdepart;
}
//����Լ��Ϣ���ļ�
void Appointment::save(ofstream& ofs)
{
	// ��ʱ���ʽ��Ϊ�ַ��������� "2024-12-23 14:30:00"��
	ofs << _t.tm_year + 1900 << "-"  // ��ݣ���1900�꿪ʼ��
		<< setfill('0') << setw(2) << _t.tm_mon + 1 << "-"  // �·ݣ���0��ʼ��
		<< setw(2) << _t.tm_mday << " "
		<< setw(2) << _t.tm_hour << ":"
		<< setw(2) << _t.tm_min << ":"
		<< setw(2) << _t.tm_sec << endl;

	// ��ʱ���ͷ����ֱ�ӱ���Ϊ�ı�
	ofs << _duration << endl;
	ofs << _roomnum << endl;

	// �����û����Ͳ�����Ϣ
	OAUtils::save_str(ofs, _username);
	OAUtils::save_str(ofs, _userdepart);
}
//���ļ���ȡԤԼ��Ϣ
void Appointment::read(ifstream& ifs)
{
	// ��ȡʱ�䣺���� "YYYY-MM-DD HH:MM:SS" ��ʽ����
	int year, month, day, hour, minute, second;
	ifs >> year;
	ifs.ignore(1, '-');  // ���Էָ��� '-'
	ifs >> month;
	ifs.ignore(1, '-');
	ifs >> day;
	ifs.ignore(1, ' ');  // ���Էָ��� ' '
	ifs >> hour;
	ifs.ignore(1, ':');
	ifs >> minute;
	ifs.ignore(1, ':');
	ifs >> second;
	ifs.ignore();  // �������з�

	_t.tm_year = year - 1900;
	_t.tm_mon = month - 1;
	_t.tm_mday = day;
	_t.tm_hour = hour;
	_t.tm_min = minute;
	_t.tm_sec = second;

	// ��ȡʱ���ͷ����
	ifs >> _duration;
	ifs.ignore();  // �������з�
	ifs >> _roomnum;
	ifs.ignore();  // �������з�

	// ��ȡ�û����Ͳ�����Ϣ
	OAUtils::read_str(ifs, _username);
	OAUtils::read_str(ifs, _userdepart);
}
//�û��͹���Ա��¼��������
UserData* OADataCenter::Login(const UserData& userdata)
{
	UserData* res = nullptr;
	pair<_It_user, bool> checkpair = checkName(userdata.getName());
	if (checkpair.second) {
		if (checkPasw(checkpair.first, userdata.getPasw())) {
			res = &(*checkpair.first);
		}
	}
	return res;
}

AdminData* OADataCenter::Login(const AdminData& admindata)
{
	AdminData* admin_ptr = nullptr;
	if (admin.getName() == admindata.getName() && admin.getPasw() == admindata.getPasw()) {
		admin_ptr = &admin;
	}
	return admin_ptr;
}

void OADataCenter::AddUser(const UserData& userdata)
{
	user.push_back(userdata);
	OADataCenter::save_OADataCenter();
}
//��������ɾ���û�
void OADataCenter::DelUser(const string& name)
{
	user.erase(OADataCenter::get_It_User(name));
	save_OADataCenter();
}
//����������ӻ����ҡ������ǰ�жϻ������Ƿ����
bool OADataCenter::AddMeetingRoom(int id)
{
	bool res = false;
	if (!checkRoom(id).second) {
		cout << "��������������ƣ� ";
		string name;
		name = OAUtils::getStr();

		cout << "����������������� ";
		int num;
		num = OAUtils::getNum();

		roomname.push_back(name);
		room.push_back(id);
		roomcapacity.push_back(num);

		res = true;
		OADataCenter::save_OADataCenter();
	}
	return res;
}
//��������ɾ�������ҡ���ɾ��ǰ�жϻ������Ƿ����
bool OADataCenter::DelMeetingRoom(MeetingRoom roomid)
{
	bool res = false;
	_It_room it = get_It_Room(roomid);

	if (it != room.end()) {
		size_t index = std::distance(room.begin(), it);

		// �����±�ɾ����Ӧ��Ԫ��
		room.erase(room.begin() + index);
		roomname.erase(roomname.begin() + index);
		roomcapacity.erase(roomcapacity.begin() + index);
		res = true;
		OADataCenter::save_OADataCenter();
	}
	return res;
}
//�����������ԤԼ
void OADataCenter::AddApp(const Appointment& app)
{
	App.push_back(app);
	save_OADataCenter();
}
//��������ɾ��ԤԼ
bool OADataCenter::DelApp(const UserData& data, int id)
{
	bool res = false;
	sort(App.begin(), App.end(), CompareName());
	pair<_It_app, _It_app> respair;
	if (&data != &admin) {
		respair = equal_range(App.begin(), App.end(), Appointment(tm(), 0, 0, data.getName(), ""), CompareName());
	}
	else {
		respair.first = App.begin();
		respair.second = App.end();
	}
	if (id < respair.second - respair.first && id >= 0) {
		App.erase(respair.first + id);
		res = true;
		save_OADataCenter();
	}
	return res;
}
//�����������ԤԼ
void OADataCenter::CleApp()
{
	App.clear();
	vector<Appointment>().swap(App);
}
//�����������ݵ��ļ�
void OADataCenter::init_OADataCenter()
{
	ifstream ifs("src/DataCenter.txt");

	if (ifs.is_open()) {
		size_t usersize = 0;
		ifs >> usersize;  // ��ȡ user �Ĵ�С
		user.resize(usersize);
		for (auto it = user.begin(); it != user.end(); it++) {
			it->read(ifs);  // ���� read �������ı����ݽ����ɶ�Ӧ�Ķ���
		}

		size_t roomsize = 0;
		ifs >> roomsize;  // ��ȡ room �Ĵ�С
		room.resize(roomsize);
		for (auto it = room.begin(); it != room.end(); it++) {
			ifs >> *it;  // ���� room Ԫ��֧�ִ��ı���ȡ
		}

		size_t roomnamesize = 0;
		ifs >> roomnamesize;  // ��ȡ roomname �Ĵ�С
		roomname.resize(roomnamesize);
		for (auto it = roomname.begin(); it != roomname.end(); it++) {
			ifs >> *it;  // ���� roomname Ԫ��֧�ִ��ı���ȡ
		}

		size_t roomcapacitysize = 0;
		ifs >> roomcapacitysize;  // ��ȡ roomcapacity �Ĵ�С
		roomcapacity.resize(roomcapacitysize);
		for (auto it = roomcapacity.begin(); it != roomcapacity.end(); it++) {
			ifs >> *it;  // ���� roomcapacity Ԫ��֧�ִ��ı���ȡ
		}

		size_t appsize = 0;
		ifs >> appsize;  // ��ȡ App �Ĵ�С
		App.resize(appsize);
		for (auto it = App.begin(); it != App.end(); it++) {
			it->read(ifs);  // ���� read �������ı����ݽ����ɶ�Ӧ�Ķ���
		}

		ifs.close();
	}
}

//���ļ�д������
void OADataCenter::save_OADataCenter()
{
	ofstream ofs("src/DataCenter.txt");

	if (ofs.is_open()) {
		// д�� user ����
		ofs << user.size() << endl;  // ��д�� user ������
		for (auto it = user.begin(); it != user.end(); it++) {
			it->save(ofs);  // ���� save ������ user ���������ı���ʽд��
		}

		// д�� room ����
		ofs << room.size() << endl;
		for (auto it = room.begin(); it != room.end(); it++) {
			ofs << *it << endl;  // ������� room �е�Ԫ�ؿ���ֱ�����Ϊ�ı�
		}

		// д�� roomname ����
		ofs << roomname.size() << endl;
		for (auto it = roomname.begin(); it != roomname.end(); it++) {
			ofs << *it << endl;  // ͬ������ roomname �е�Ԫ�ؿ���ֱ�����Ϊ�ı�
		}

		// д�� roomcapacity ����
		ofs << roomcapacity.size() << endl;
		for (auto it = roomcapacity.begin(); it != roomcapacity.end(); it++) {
			ofs << *it << endl;  // ͬ������ roomcapacity �е�Ԫ�ؿ���ֱ�����Ϊ�ı�
		}

		// д�� App ����
		ofs << App.size() << endl;
		for (auto it = App.begin(); it != App.end(); it++) {
			it->save(ofs);  // ���� save ������ App ���������ı���ʽд��
		}

		ofs.close();
	}
}

//�������ĺ˶�ʱ���Ƿ��ͻ
bool OADataCenter::checkTime(time_t t_time, time_t duration, MeetingRoom roomid)
{
	bool res = true;
	duration *= 60;
	sort(App.begin(), App.end(), CompareRoomID());
	auto roomidAppit = equal_range(App.begin(), App.end(), Appointment(tm(), 0, roomid, "", ""), CompareRoomID());

	for (_It_app it = roomidAppit.first; roomidAppit.first != App.end() && it != roomidAppit.second; it++) {
		if (it->getAppTime() == t_time ||
			(it->getAppTime() < t_time && it->getAppTime() + it->getAppDuration() * 60 > t_time) ||
			(it->getAppTime() > t_time && it->getAppTime() < t_time + duration)) {
			res = false;
			break;
		}
	}
	return res;
}
//ͨ��������ȡ�û��ĵ��������������򷵻�end()
_It_user OADataCenter::get_It_User(const string& name)
{
	for (_It_user it = user.begin(); it != user.end(); it++) {
		if (it->getName() == name) {
			return it;
		}
	}
	return user.end();
}
//ͨ������Ż�ȡ�����ҵ������������ڷ���end
_It_room OADataCenter::get_It_Room(const MeetingRoom& id)
{
	return find(room.begin(), room.end(), id);
}

//�������ĺ�ʵ�Ƿ��������Ϊname���û�
pair<_It_user, bool> OADataCenter::checkName(const string& name)
{
	pair<_It_user, bool> res;
	res.first = get_It_User(name);
	res.second = res.first != user.end();
	return res;
}
//�������ĺ˶����롪����½ʱ����
bool OADataCenter::checkPasw(const _It_user& it, const string& password)
{
	if (it != user.end()) {
		return it->getPasw() == password;
	}
	else {
		return false;
	}
}
//���������ж��Ƿ����id������
pair<_It_room, bool> OADataCenter::checkRoom(const MeetingRoom& id)
{
	pair<_It_room, bool> res;
	res.first = get_It_Room(id);
	res.second = res.first != room.end();
	return res;
}

//�û��鿴�Լ���ԤԼ��Ϣ
bool OADataCenter::showApp1(const string& name)
{
	bool res = false;
	pair<_It_app, _It_app> myApp;
	if (name != admin.getName()) {
		sort(App.begin(), App.end(), CompareName());
		myApp = equal_range(App.begin(), App.end(), Appointment(tm(), 0, 0, name, ""), CompareName());
	}
	else {
		myApp.first = App.begin();
		myApp.second = App.end();
	}
	if (myApp.first == App.end()) {
		cout << "��û��ԤԼ" << endl;
		system("pause");
	}
	else {
		res = true;
		cout << setw(10) << setiosflags(ios::left) << "���"
			<< setw(10) << setiosflags(ios::left) << "����"
			<< setw(30) << setiosflags(ios::left) << "��ʼʱ��"
			<< setw(30) << setiosflags(ios::left) << "����ʱ��"
			<< setw(10) << setiosflags(ios::left) << "ԤԼ��"
			<< setw(10) << setiosflags(ios::left) << "ԤԼ����" << endl;
		int i = 1;
		for (_It_app it = myApp.first; it != myApp.second; it++, i++) {
			time_t t = it->getAppTime();
			tm tm_t;
			localtime_s(&tm_t, &t);
			cout << setw(10) << setiosflags(ios::left) << i;			
			//���ԤԼ��Ϣ
			ostringstream oss , oss1 ;
			oss << tm_t.tm_year + 1900 << "��" << tm_t.tm_mon + 1 << "��" << tm_t.tm_mday << "��" << tm_t.tm_hour << "ʱ" << tm_t.tm_min << "��";
			int timebegin = tm_t.tm_hour * 60 + tm_t.tm_min;
			int timeend = timebegin + it->getAppDuration();
			int endhour = timeend / 60;
			int endmin = timeend % 60;
			oss1 << tm_t.tm_year + 1900 << "��" << tm_t.tm_mon + 1 << "��" << tm_t.tm_mday << "��" << endhour << "ʱ" << endmin << "��";
			cout << setw(10) << it->getRoomID() << setw(30) << oss.str() << setw(30) << oss1.str() << setw(10)
				<< it -> getAppName() << setw(10) << it -> getAppdepart() << endl;
		}
		system("pause");
	}
	return res;
}
//����Ա�鿴�����˵�ԤԼ��Ϣ���û�ԤԼ������ʱ��ʾ�Լ���ԤԼ�Ļ�����
bool OADataCenter::showApp(const string& name)
{
	bool res = false;
	pair<_It_app, _It_app> myApp;
	myApp.first = App.begin();
	myApp.second = App.end();
	if (myApp.first == App.end()) {
		cout << "��û��ԤԼ" << endl;
		system("pause");
	}
	else {
		res = true;
		cout << setw(10) << setiosflags(ios::left) << "���"
			<< setw(10) << setiosflags(ios::left) << "����"
			<< setw(30) << setiosflags(ios::left) << "��ʼʱ��"
			<< setw(30) << setiosflags(ios::left) << "����ʱ��"
			<< setw(10) << setiosflags(ios::left) << "ԤԼ��"
			<< setw(10) << setiosflags(ios::left) << "ԤԼ����" << endl;
		int i = 1;
		for (_It_app it = myApp.first; it != myApp.second; it++, i++) {
			time_t t = it->getAppTime();
			tm tm_t;
			localtime_s(&tm_t, &t);
			cout << setw(10) << setiosflags(ios::left) << i;
			//���ԤԼ��Ϣ
			ostringstream oss, oss1;
			oss << tm_t.tm_year + 1900 << "��" << tm_t.tm_mon + 1 << "��" << tm_t.tm_mday << "��" << tm_t.tm_hour << "ʱ" << tm_t.tm_min << "��";
			int timebegin = tm_t.tm_hour * 60 + tm_t.tm_min;
			int timeend = timebegin + it->getAppDuration();
			int endhour = timeend / 60;
			int endmin = timeend % 60;
			oss1 << tm_t.tm_year + 1900 << "��" << tm_t.tm_mon + 1 << "��" << tm_t.tm_mday << "��" << endhour << "ʱ" << endmin << "��";
			cout << setw(10) << it->getRoomID() << setw(30) << oss.str() << setw(30) << oss1.str() << setw(10)
				<< it->getAppName() << setw(10) << it->getAppdepart() << endl;
		}
		system("pause");
	}
	return res;
}
//�������Ĳ鿴�����û������ɹ���Աɾ���û�ʱ����
bool OADataCenter::showUser()
{
	bool res = false;
	if (user.size() == 0) {
		cout << "��ǰû���û�" << endl;
	}
	else {
		res = true;
		cout << setw(10) << setiosflags(ios::left) << "���"
			<< setw(10) << setiosflags(ios::left) << "�û���"
			<< setw(10) << setiosflags(ios::left) << "����" << endl;
		int i = 1;
		for (_It_user it = OADataCenter::user.begin(); it != OADataCenter::user.end(); it++, i++) {
			cout << setw(10) << setiosflags(ios::left) << i
				<< setw(10) << setiosflags(ios::left) << it->getName()
				<< setw(10) << setiosflags(ios::left) << it->getDepart() << endl;
		}
	}
	return res;
}
//�������Ĳ鿴���л����ҡ����ɹ���Աɾ��������ʱ����
bool OADataCenter::showRoom()
{
	bool res = false;
	if (OADataCenter::room.size() == 0) {
		cout << "��ǰû�л�����" << endl;
	}
	else {
		res = true;
		cout << setw(10) << setiosflags(ios::left) << "���"
			<< setw(10) << setiosflags(ios::left) << "���ƺ�"
			<< setw(15) << setiosflags(ios::left) << "����������"
			<< setw(10) << setiosflags(ios::left) << "��������" << endl;
		int i = 1;
		_It_roomname it1 = OADataCenter::roomname.begin();
		_It_roomcapacity it2 = OADataCenter::roomcapacity.begin();
		_It_room it = OADataCenter::room.begin();
		for (; it != OADataCenter::room.end(); it++, i++, it1++, it2++) {
			cout << setw(10) << setiosflags(ios::left) << i
				<< setw(10) << setiosflags(ios::left) << *it
				<< setw(15) << setiosflags(ios::left) << *it1
				<< setw(10) << setiosflags(ios::left) << *it2 << endl;
		}
	}
	return res;
}

bool OADataCenter::showAppAdvice()
{
	bool res = false;
	if (OADataCenter::room.size() == 0) {
		cout << "��ǰû�л�����" << endl;
	}
	else {
		bool flag = 0;
		res = true;
		int num;
		cout << "������ԤԼ����������" << endl;
		num = OAUtils::getNum();
		for (auto it = OADataCenter::roomcapacity.begin(); it != OADataCenter::roomcapacity.end(); it++) {
			if (*it >= num) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			cout << "������ԤԼ�Ļ��������£�" << endl;
			cout << setw(10) << setiosflags(ios::left) << "���"
				<< setw(10) << setiosflags(ios::left) << "���ƺ�"
				<< setw(15) << setiosflags(ios::left) << "����������"
				<< setw(10) << setiosflags(ios::left) << "��������" << endl;
			int i = 1;
			_It_roomname it1 = OADataCenter::roomname.begin();
			_It_room it2 = OADataCenter::room.begin();
			for (auto it = OADataCenter::roomcapacity.begin(); it != OADataCenter::roomcapacity.end(); it++, it1++, it2++) {
				if (*it >= num) {
					cout << setw(10) << setiosflags(ios::left) << i
						<< setw(10) << setiosflags(ios::left) << *it2
						<< setw(15) << setiosflags(ios::left) << *it1
						<< setw(10) << setiosflags(ios::left) << *it << endl;
					i++;
				}
			}
		}
		if (flag == 0) {
			cout << "��ǰû���㹻�Ļ���������" << endl;
		}
	}
	return res;
}

using MeetingRoom = int;
using MeetingRoomname = string;
using MeetingRoomcapacity = int;
AdminData OADataCenter::admin("admin", "admin", "����Ա");
vector<UserData> OADataCenter::user;
vector<MeetingRoom> OADataCenter::room;
vector<MeetingRoomname> OADataCenter::roomname;
vector<Appointment> OADataCenter::App;
vector<MeetingRoomcapacity> OADataCenter::roomcapacity;


//����ν��
bool CompareName::operator()(const Appointment& a1, const Appointment& a2)
{
	return a1.getAppName() < a2.getAppName();
}

bool CompareRoomID::operator()(const Appointment& a1, const Appointment& a2)
{
	return a1.getRoomID() < a2.getRoomID();
}
//���ԤԼ�º���
void PrintApp::operator()(Appointment& a)
{
	time_t t = a.getAppTime();
	tm tm_t;
	localtime_s(&tm_t, &t);
	ostringstream oss;
	oss << tm_t.tm_year + 1900 << "��" << tm_t.tm_mon + 1 << "��" << tm_t.tm_mday << "��" << tm_t.tm_hour << "ʱ" << tm_t.tm_min << "��";
	cout << setw(10) << a.getRoomID() << setw(30) << oss.str() << setw(10) << a.getAppDuration() << setw(10)
		<< a.getAppName() << setw(10) << a.getAppdepart() << endl;
}