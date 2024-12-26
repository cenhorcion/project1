#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<map>
#include"OAUtils.h"
using namespace std;

using MeetingRoom = int;
using MeetingRoomname = string;
using MeetingRoomCapacity = int;

using _It_room = vector<MeetingRoom>::iterator;
using _It_roomname = vector<MeetingRoomname>::iterator;
using _It_roomcapacity = vector<MeetingRoomCapacity>::iterator;

//用户信息类
class UserData {
private:
	string _name;
	string _password;
	string _depart;
public:
	UserData();
	UserData(string name, string password, string depart);

	string& getName();
	string& getPasw();
	string& getDepart();
	const string& getName()const;
	const string& getPasw()const;
	const string& getDepart()const;
	//用户登陆函数——通过多态实现管理员的不同登陆功能
	virtual UserData* Login();
	bool showApp();
	bool showApp1();
	bool showRoom();
	bool showAppAdvice();
	//添加预约——返回-1，会议室不存在，返回0时间冲突
	int addApp(tm& t, time_t duration, MeetingRoom roomid);
	bool delApp(int id);
	//写入或读取文件
	void save(ofstream& ofs);
	void read(ifstream& ifs);
};
class AdminData :public UserData {
public:
	AdminData();
	AdminData(string name, string password, string depart);

	AdminData* Login()override;
	bool showUser()const;
	void AddUser(const UserData& userdata);
	void DelUser(const string& name)const;
	bool AddMeetingRoom(int id);
	bool showRoom();
	bool showAppAdvice();
	bool DelMeetingRoom(int roomid);
	bool checkName(const string& name)const;
	void CleAppPage();
};
//预约类
class Appointment {
private:
	tm _t;
	time_t _duration;
	int _roomnum;
	string _username;
	string _userdepart;
public:
	Appointment();
	Appointment(const tm& t, time_t duration, int roomid, string name, string depart);
	const time_t getAppTime()const;
	const time_t getAppDuration()const;
	const int getRoomID()const;
	const string& getAppName()const;
	const string& getAppdepart()const;
	void save(ofstream& ofs);
	void read(ifstream& ifs);
};

using _It_user = vector<UserData>::iterator;
using _It_app = vector<Appointment>::iterator;

//数据中心类
class OADataCenter {
private:
	static AdminData admin;
	static vector<UserData> user;
	static vector<MeetingRoom> room;
	static vector<MeetingRoomname> roomname;
	static vector<MeetingRoomCapacity> roomcapacity;
	static vector<Appointment> App;
public:
	//删插增改和登陆功能函数
	static UserData* Login(const UserData& userdata);
	static AdminData* Login(const AdminData& admindata);
	static void AddUser(const UserData& userdata);
	static void DelUser(const string& name);
	static bool AddMeetingRoom(int id);
	static bool DelMeetingRoom(MeetingRoom roomid);
	static void AddApp(const Appointment& app);
	static bool DelApp(const UserData& data, int id);
	static void CleApp();
	static bool showApp(const string& name);
	static bool showApp1(const string& name);
	static bool showUser();
	static bool showRoom();
	static bool showAppAdvice();
	//数据读取和写入
	static void init_OADataCenter();
	static void save_OADataCenter();
	//核对姓名、密码、时间，获取用户和预约的迭代器
	static bool checkTime(time_t time, time_t duration, MeetingRoom roomid);
	static _It_user get_It_User(const string& name);
	static _It_room get_It_Room(const MeetingRoom& id);
	static pair<_It_user, bool> checkName(const string& name);
	static bool checkPasw(const _It_user& it, const string& password);
	static pair<_It_room, bool> checkRoom(const MeetingRoom& id);

};
//排序谓词
struct CompareName {
	bool operator()(const Appointment& a1, const Appointment& a2);
};
struct CompareRoomID {
	bool operator()(const Appointment& a1, const  Appointment& a2);
};
struct PrintApp {
	void operator()(Appointment& a);
};