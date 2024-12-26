#include "OADataCenter.h"
#include<algorithm>
#include<iomanip>
#include<sstream>
#include<fstream>
#include"OAUtils.h"
//用户信息类构造
UserData::UserData() {}
UserData::UserData(string name, string password, string depart)
{
	_name = name;
	_password = password;
	_depart = depart;
}
//获取用户名、密码、部门
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
//用户登录
UserData* UserData::Login()
{
	return OADataCenter::Login(*this);
}
//用户添加预约——判断会议室是否存在，判断时间是否冲突
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
//删除预约
bool UserData::delApp(int id)
{
	return OADataCenter::DelApp(*this, id);
}
//查看预约
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
//保存用户信息到文件
void UserData::save(ofstream& ofs)
{
	OAUtils::save_str(ofs, _name);
	OAUtils::save_str(ofs, _password);
	OAUtils::save_str(ofs, _depart);
}
//从文件读取用户信息
void UserData::read(ifstream& ifs)
{
	OAUtils::read_str(ifs, _name);
	OAUtils::read_str(ifs, _password);
	OAUtils::read_str(ifs, _depart);
}

//管理员构造函数
AdminData::AdminData() {}
AdminData::AdminData(string name, string password, string depart) :UserData(name, password, depart) {}
//管理员登录
AdminData* AdminData::Login()
{
	return OADataCenter::Login(*this);
}
//管理员查看所有用户
bool AdminData::showUser()const
{
	return OADataCenter::showUser();
}
//管理员查看所有会议室
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


//管理员添加用户——调用数据中心的添加用户函数
void AdminData::AddUser(const UserData& userdata)
{
	OADataCenter::AddUser(userdata);
}
//管理员删除用户——调用数据中心的删除用户函数
void AdminData::DelUser(const string& name)const
{
	OADataCenter::DelUser(name);
}
//管理员添加会议室——调用数据中心的添加会议室函数
bool AdminData::AddMeetingRoom(int id)
{
	return OADataCenter::AddMeetingRoom(id);
}
//管理员删除会议室——调用数据中心的删除会议室函数
bool AdminData::DelMeetingRoom(int roomid)
{
	return OADataCenter::DelMeetingRoom(roomid);
}
//管理员核对用户姓名是否存在
bool AdminData::checkName(const string& name)const
{
	return OADataCenter::checkName(name).second;
}

void AdminData::CleAppPage()
{
	OADataCenter::CleApp();
}

//预约类构造函数
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
//获取预约的time_t格式时间
const time_t Appointment::getAppTime()const
{
	return mktime(const_cast<tm*>(&_t));  // 去掉 const 修饰符
}
//获取预约的时长分钟
const time_t Appointment::getAppDuration()const
{
	return _duration;
}
//获取预约的会议室
const int Appointment::getRoomID() const
{
	return _roomnum;
}
//获取预约用户
const string& Appointment::getAppName()const
{
	return _username;
}
//获取预约部门
const string& Appointment::getAppdepart()const
{
	return _userdepart;
}
//保存约信息到文件
void Appointment::save(ofstream& ofs)
{
	// 将时间格式化为字符串（例如 "2024-12-23 14:30:00"）
	ofs << _t.tm_year + 1900 << "-"  // 年份（从1900年开始）
		<< setfill('0') << setw(2) << _t.tm_mon + 1 << "-"  // 月份（从0开始）
		<< setw(2) << _t.tm_mday << " "
		<< setw(2) << _t.tm_hour << ":"
		<< setw(2) << _t.tm_min << ":"
		<< setw(2) << _t.tm_sec << endl;

	// 将时长和房间号直接保存为文本
	ofs << _duration << endl;
	ofs << _roomnum << endl;

	// 保存用户名和部门信息
	OAUtils::save_str(ofs, _username);
	OAUtils::save_str(ofs, _userdepart);
}
//从文件读取预约信息
void Appointment::read(ifstream& ifs)
{
	// 读取时间：按照 "YYYY-MM-DD HH:MM:SS" 格式解析
	int year, month, day, hour, minute, second;
	ifs >> year;
	ifs.ignore(1, '-');  // 忽略分隔符 '-'
	ifs >> month;
	ifs.ignore(1, '-');
	ifs >> day;
	ifs.ignore(1, ' ');  // 忽略分隔符 ' '
	ifs >> hour;
	ifs.ignore(1, ':');
	ifs >> minute;
	ifs.ignore(1, ':');
	ifs >> second;
	ifs.ignore();  // 跳过换行符

	_t.tm_year = year - 1900;
	_t.tm_mon = month - 1;
	_t.tm_mday = day;
	_t.tm_hour = hour;
	_t.tm_min = minute;
	_t.tm_sec = second;

	// 读取时长和房间号
	ifs >> _duration;
	ifs.ignore();  // 跳过换行符
	ifs >> _roomnum;
	ifs.ignore();  // 跳过换行符

	// 读取用户名和部门信息
	OAUtils::read_str(ifs, _username);
	OAUtils::read_str(ifs, _userdepart);
}
//用户和管理员登录函数重载
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
//数据中心删除用户
void OADataCenter::DelUser(const string& name)
{
	user.erase(OADataCenter::get_It_User(name));
	save_OADataCenter();
}
//数据中心添加会议室——添加前判断会议室是否存在
bool OADataCenter::AddMeetingRoom(int id)
{
	bool res = false;
	if (!checkRoom(id).second) {
		cout << "请输入会议室名称： ";
		string name;
		name = OAUtils::getStr();

		cout << "请输入会议室容量： ";
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
//数据中心删除会议室——删除前判断会议室是否存在
bool OADataCenter::DelMeetingRoom(MeetingRoom roomid)
{
	bool res = false;
	_It_room it = get_It_Room(roomid);

	if (it != room.end()) {
		size_t index = std::distance(room.begin(), it);

		// 根据下标删除对应的元素
		room.erase(room.begin() + index);
		roomname.erase(roomname.begin() + index);
		roomcapacity.erase(roomcapacity.begin() + index);
		res = true;
		OADataCenter::save_OADataCenter();
	}
	return res;
}
//数据中心添加预约
void OADataCenter::AddApp(const Appointment& app)
{
	App.push_back(app);
	save_OADataCenter();
}
//数据中心删除预约
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
//数据中心清空预约
void OADataCenter::CleApp()
{
	App.clear();
	vector<Appointment>().swap(App);
}
//保存所有数据到文件
void OADataCenter::init_OADataCenter()
{
	ifstream ifs("src/DataCenter.txt");

	if (ifs.is_open()) {
		size_t usersize = 0;
		ifs >> usersize;  // 读取 user 的大小
		user.resize(usersize);
		for (auto it = user.begin(); it != user.end(); it++) {
			it->read(ifs);  // 假设 read 方法将文本数据解析成对应的对象
		}

		size_t roomsize = 0;
		ifs >> roomsize;  // 读取 room 的大小
		room.resize(roomsize);
		for (auto it = room.begin(); it != room.end(); it++) {
			ifs >> *it;  // 假设 room 元素支持从文本读取
		}

		size_t roomnamesize = 0;
		ifs >> roomnamesize;  // 读取 roomname 的大小
		roomname.resize(roomnamesize);
		for (auto it = roomname.begin(); it != roomname.end(); it++) {
			ifs >> *it;  // 假设 roomname 元素支持从文本读取
		}

		size_t roomcapacitysize = 0;
		ifs >> roomcapacitysize;  // 读取 roomcapacity 的大小
		roomcapacity.resize(roomcapacitysize);
		for (auto it = roomcapacity.begin(); it != roomcapacity.end(); it++) {
			ifs >> *it;  // 假设 roomcapacity 元素支持从文本读取
		}

		size_t appsize = 0;
		ifs >> appsize;  // 读取 App 的大小
		App.resize(appsize);
		for (auto it = App.begin(); it != App.end(); it++) {
			it->read(ifs);  // 假设 read 方法将文本数据解析成对应的对象
		}

		ifs.close();
	}
}

//从文件写入数据
void OADataCenter::save_OADataCenter()
{
	ofstream ofs("src/DataCenter.txt");

	if (ofs.is_open()) {
		// 写入 user 容器
		ofs << user.size() << endl;  // 先写入 user 的数量
		for (auto it = user.begin(); it != user.end(); it++) {
			it->save(ofs);  // 假设 save 方法将 user 的数据以文本格式写入
		}

		// 写入 room 容器
		ofs << room.size() << endl;
		for (auto it = room.begin(); it != room.end(); it++) {
			ofs << *it << endl;  // 这里假设 room 中的元素可以直接输出为文本
		}

		// 写入 roomname 容器
		ofs << roomname.size() << endl;
		for (auto it = roomname.begin(); it != roomname.end(); it++) {
			ofs << *it << endl;  // 同样假设 roomname 中的元素可以直接输出为文本
		}

		// 写入 roomcapacity 容器
		ofs << roomcapacity.size() << endl;
		for (auto it = roomcapacity.begin(); it != roomcapacity.end(); it++) {
			ofs << *it << endl;  // 同样假设 roomcapacity 中的元素可以直接输出为文本
		}

		// 写入 App 容器
		ofs << App.size() << endl;
		for (auto it = App.begin(); it != App.end(); it++) {
			it->save(ofs);  // 假设 save 方法将 App 的数据以文本格式写入
		}

		ofs.close();
	}
}

//数据中心核对时间是否冲突
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
//通过姓名获取用户的迭代器，不存在则返回end()
_It_user OADataCenter::get_It_User(const string& name)
{
	for (_It_user it = user.begin(); it != user.end(); it++) {
		if (it->getName() == name) {
			return it;
		}
	}
	return user.end();
}
//通过房间号获取会议室迭代器，不存在返回end
_It_room OADataCenter::get_It_Room(const MeetingRoom& id)
{
	return find(room.begin(), room.end(), id);
}

//数据中心核实是否存在姓名为name的用户
pair<_It_user, bool> OADataCenter::checkName(const string& name)
{
	pair<_It_user, bool> res;
	res.first = get_It_User(name);
	res.second = res.first != user.end();
	return res;
}
//数据中心核对密码——登陆时调用
bool OADataCenter::checkPasw(const _It_user& it, const string& password)
{
	if (it != user.end()) {
		return it->getPasw() == password;
	}
	else {
		return false;
	}
}
//数据中心判断是否存在id会议室
pair<_It_room, bool> OADataCenter::checkRoom(const MeetingRoom& id)
{
	pair<_It_room, bool> res;
	res.first = get_It_Room(id);
	res.second = res.first != room.end();
	return res;
}

//用户查看自己的预约信息
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
		cout << "您没有预约" << endl;
		system("pause");
	}
	else {
		res = true;
		cout << setw(10) << setiosflags(ios::left) << "序号"
			<< setw(10) << setiosflags(ios::left) << "房间"
			<< setw(30) << setiosflags(ios::left) << "开始时间"
			<< setw(30) << setiosflags(ios::left) << "结束时间"
			<< setw(10) << setiosflags(ios::left) << "预约人"
			<< setw(10) << setiosflags(ios::left) << "预约部门" << endl;
		int i = 1;
		for (_It_app it = myApp.first; it != myApp.second; it++, i++) {
			time_t t = it->getAppTime();
			tm tm_t;
			localtime_s(&tm_t, &t);
			cout << setw(10) << setiosflags(ios::left) << i;			
			//输出预约信息
			ostringstream oss , oss1 ;
			oss << tm_t.tm_year + 1900 << "年" << tm_t.tm_mon + 1 << "月" << tm_t.tm_mday << "日" << tm_t.tm_hour << "时" << tm_t.tm_min << "分";
			int timebegin = tm_t.tm_hour * 60 + tm_t.tm_min;
			int timeend = timebegin + it->getAppDuration();
			int endhour = timeend / 60;
			int endmin = timeend % 60;
			oss1 << tm_t.tm_year + 1900 << "年" << tm_t.tm_mon + 1 << "月" << tm_t.tm_mday << "日" << endhour << "时" << endmin << "分";
			cout << setw(10) << it->getRoomID() << setw(30) << oss.str() << setw(30) << oss1.str() << setw(10)
				<< it -> getAppName() << setw(10) << it -> getAppdepart() << endl;
		}
		system("pause");
	}
	return res;
}
//管理员查看所有人的预约信息或用户预约会议室时显示以及被预约的会议室
bool OADataCenter::showApp(const string& name)
{
	bool res = false;
	pair<_It_app, _It_app> myApp;
	myApp.first = App.begin();
	myApp.second = App.end();
	if (myApp.first == App.end()) {
		cout << "您没有预约" << endl;
		system("pause");
	}
	else {
		res = true;
		cout << setw(10) << setiosflags(ios::left) << "序号"
			<< setw(10) << setiosflags(ios::left) << "房间"
			<< setw(30) << setiosflags(ios::left) << "开始时间"
			<< setw(30) << setiosflags(ios::left) << "结束时间"
			<< setw(10) << setiosflags(ios::left) << "预约人"
			<< setw(10) << setiosflags(ios::left) << "预约部门" << endl;
		int i = 1;
		for (_It_app it = myApp.first; it != myApp.second; it++, i++) {
			time_t t = it->getAppTime();
			tm tm_t;
			localtime_s(&tm_t, &t);
			cout << setw(10) << setiosflags(ios::left) << i;
			//输出预约信息
			ostringstream oss, oss1;
			oss << tm_t.tm_year + 1900 << "年" << tm_t.tm_mon + 1 << "月" << tm_t.tm_mday << "日" << tm_t.tm_hour << "时" << tm_t.tm_min << "分";
			int timebegin = tm_t.tm_hour * 60 + tm_t.tm_min;
			int timeend = timebegin + it->getAppDuration();
			int endhour = timeend / 60;
			int endmin = timeend % 60;
			oss1 << tm_t.tm_year + 1900 << "年" << tm_t.tm_mon + 1 << "月" << tm_t.tm_mday << "日" << endhour << "时" << endmin << "分";
			cout << setw(10) << it->getRoomID() << setw(30) << oss.str() << setw(30) << oss1.str() << setw(10)
				<< it->getAppName() << setw(10) << it->getAppdepart() << endl;
		}
		system("pause");
	}
	return res;
}
//数据中心查看所有用户——由管理员删除用户时调用
bool OADataCenter::showUser()
{
	bool res = false;
	if (user.size() == 0) {
		cout << "当前没有用户" << endl;
	}
	else {
		res = true;
		cout << setw(10) << setiosflags(ios::left) << "序号"
			<< setw(10) << setiosflags(ios::left) << "用户名"
			<< setw(10) << setiosflags(ios::left) << "部门" << endl;
		int i = 1;
		for (_It_user it = OADataCenter::user.begin(); it != OADataCenter::user.end(); it++, i++) {
			cout << setw(10) << setiosflags(ios::left) << i
				<< setw(10) << setiosflags(ios::left) << it->getName()
				<< setw(10) << setiosflags(ios::left) << it->getDepart() << endl;
		}
	}
	return res;
}
//数据中心查看所有会议室——由管理员删除会议室时调用
bool OADataCenter::showRoom()
{
	bool res = false;
	if (OADataCenter::room.size() == 0) {
		cout << "当前没有会议室" << endl;
	}
	else {
		res = true;
		cout << setw(10) << setiosflags(ios::left) << "序号"
			<< setw(10) << setiosflags(ios::left) << "门牌号"
			<< setw(15) << setiosflags(ios::left) << "会议室名称"
			<< setw(10) << setiosflags(ios::left) << "容纳人数" << endl;
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
		cout << "当前没有会议室" << endl;
	}
	else {
		bool flag = 0;
		res = true;
		int num;
		cout << "请输入预约的人总数：" << endl;
		num = OAUtils::getNum();
		for (auto it = OADataCenter::roomcapacity.begin(); it != OADataCenter::roomcapacity.end(); it++) {
			if (*it >= num) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			cout << "您可以预约的会议室如下：" << endl;
			cout << setw(10) << setiosflags(ios::left) << "序号"
				<< setw(10) << setiosflags(ios::left) << "门牌号"
				<< setw(15) << setiosflags(ios::left) << "会议室名称"
				<< setw(10) << setiosflags(ios::left) << "容纳人数" << endl;
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
			cout << "当前没有足够的会议室容纳" << endl;
		}
	}
	return res;
}

using MeetingRoom = int;
using MeetingRoomname = string;
using MeetingRoomcapacity = int;
AdminData OADataCenter::admin("admin", "admin", "管理员");
vector<UserData> OADataCenter::user;
vector<MeetingRoom> OADataCenter::room;
vector<MeetingRoomname> OADataCenter::roomname;
vector<Appointment> OADataCenter::App;
vector<MeetingRoomcapacity> OADataCenter::roomcapacity;


//排序谓词
bool CompareName::operator()(const Appointment& a1, const Appointment& a2)
{
	return a1.getAppName() < a2.getAppName();
}

bool CompareRoomID::operator()(const Appointment& a1, const Appointment& a2)
{
	return a1.getRoomID() < a2.getRoomID();
}
//输出预约仿函数
void PrintApp::operator()(Appointment& a)
{
	time_t t = a.getAppTime();
	tm tm_t;
	localtime_s(&tm_t, &t);
	ostringstream oss;
	oss << tm_t.tm_year + 1900 << "年" << tm_t.tm_mon + 1 << "月" << tm_t.tm_mday << "日" << tm_t.tm_hour << "时" << tm_t.tm_min << "分";
	cout << setw(10) << a.getRoomID() << setw(30) << oss.str() << setw(10) << a.getAppDuration() << setw(10)
		<< a.getAppName() << setw(10) << a.getAppdepart() << endl;
}