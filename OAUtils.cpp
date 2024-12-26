#include "OAUtils.h"

int OAUtils::getNum()
{
	int res = -1;
	cin >> res;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> res;
	}
	return res;
}

string OAUtils::getStr()
{
	string str;
	cin >> str;
	while (cin.fail() || str.size() > 16 || str.size() == 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "输入格式有误，请重新输入：";
		cin >> str;
	}
	return str;
}
void OAUtils::save_str(ofstream& ofs, string& str)
{
	size_t size = str.size();  // 获取字符串长度
	ofs << size << endl;       // 先写入字符串长度（文本格式）

	// 然后将字符串的每个字符按文本格式写入
	ofs << str << endl;        // 将字符串写入文件，并换行
}

//从文件中读取字符串

void OAUtils::read_str(ifstream& ifs, string& str)
{
	size_t size = 0;
	ifs >> size;  // 读取字符串的长度
	ifs.ignore();  // 跳过换行符

	// 读取字符串
	str.resize(size);
	ifs.read(&str[0], size);  // 读取指定长度的字符
}
