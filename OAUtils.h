#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
class OAUtils
{
public:
	static int getNum();
	static string getStr();
	static void save_str(ofstream& ofs, string& str);
	static void read_str(ifstream& ifs, string& str);
};
