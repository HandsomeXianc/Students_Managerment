#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Student
{
public:
	//���εĹ��캯��
	Student(string s_name, string s_sex, int s_age, string s_id, string s_major, int Clasnum);
	~Student();
	//��ʾѧ��������Ϣ�ĺ����ӿ�
	void ShowInfo();
public:
	string id;//��¼ѧ����ѧ��
	string name;//��¼ѧ��������
	string major;//��¼ѧ����רҵ
	int age;//��¼ѧ��������
	string sex;//��¼ѧ�����Ա�

	string* Clas;//��ſγ�
	string* Sco_re;//��ſγ̳ɼ�
	int Clasnum;//��¼���ڿγ�����
};