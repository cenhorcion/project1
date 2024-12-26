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
		cout << "�����ʽ�������������룺";
		cin >> str;
	}
	return str;
}
void OAUtils::save_str(ofstream& ofs, string& str)
{
	size_t size = str.size();  // ��ȡ�ַ�������
	ofs << size << endl;       // ��д���ַ������ȣ��ı���ʽ��

	// Ȼ���ַ�����ÿ���ַ����ı���ʽд��
	ofs << str << endl;        // ���ַ���д���ļ���������
}

//���ļ��ж�ȡ�ַ���

void OAUtils::read_str(ifstream& ifs, string& str)
{
	size_t size = 0;
	ifs >> size;  // ��ȡ�ַ����ĳ���
	ifs.ignore();  // �������з�

	// ��ȡ�ַ���
	str.resize(size);
	ifs.read(&str[0], size);  // ��ȡָ�����ȵ��ַ�
}
