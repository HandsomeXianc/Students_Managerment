#include <iostream>
using namespace std;
#include "Student.h"

Student::Student(string s_name, string s_sex, int s_age, string s_id, string s_major,int Clasnum=0)
{
	this->name = s_name;
	this->age = s_age;
	this->major = s_major;
	this->id = s_id;
	this->sex = s_sex;
	this->Clasnum = Clasnum;
}

void Student::ShowInfo()
{
	cout << "ѧ��������" << this->name
		<< "\tѧ�����䣺" << this->age
		<< "\tѧ���Ա�" << this->sex
		<< "\tѧ��רҵ��" << this->major
		<< "\tѧ��ѧ�ţ�" << this->id << endl;
}