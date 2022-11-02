#pragma once
#include <iostream>
#include "Student.h"

#include <fstream>
#define FILENAME "stuFile.txt"
#define CLANAME "claFile.txt"
#define SCORENAME "scoFile.txt"

using namespace std;

class Student_Manager	
{
public:
	Student_Manager();
	void Show_menu();
	//�����ļ�
	void save();
	//ͳ���ļ��е�����
	int get_Stunum();

	//ѧ������
	/***************************************************************************************/
	void Add_stu();				//���ѧ����Ϣ
	void Show_stu();			//��ʾѧ��������Ϣ
	void Del_stu();				//���ѧ����Ϣ
	void Mod_stu();				//�޸�ѧ����Ϣ
	void Find_stu();			//����ѧ����Ϣ
	void Sort_stu();			//��ѧ����Ϣ�ɰ��� ����/���� ����
	void Clean_File();			//����ļ������е���Ϣ
	int IsExist_stu(string id);	//�ж��Ƿ����ѧ��Ϊid��ѧ�������ظ�λ��
	void Init_stu();			//��ʼ���ļ��Լ����ļ� stuFile.txt �д��ڵ�ѧ����Ϣ��¼������
	~Student_Manager();			//ѧ��ϵͳ�����������Զ���Ķѱ��������������
	void Exit_System();			//�˳�ϵͳ
	Student** StuArr;			//��ά���飬�洢ѧ�����ݵ�Ԫ
	int stu_num;				//��¼��ǰ��¼��ѧ������
	bool m_FileIsEmpty;			//�ж��ļ��Ƿ�Ϊ��
	/***************************************************************************************/
	//�γ�ϵͳ����
	void clasave();				//���γ���Ϣ�������ļ� claFile.txt ��
	void Init_cla();			//���ļ��ж�ȡѧ���γ���Ϣ����ʼ���γ�ϵͳ
	void Enter_ClassManager();	//�γ�ϵͳ�ӿں������Դ˺�������γ̹���ϵͳ
	void Clas_Menu();			//ϵͳ�˵���ʾ���ṩͼ�λ�����
	void add_class();			//���ѧ���Ŀγ���Ϣ
	void Show_Cla();			//��ӡѧ���Ŀγ���Ϣ
	void Mod_Cla();				//�޸�ѧ���Ŀγ���Ϣ
	void Del_Cla();				//���ѧ���Ŀγ���Ϣ
	void Find_Cla();			//��ѯ�γ̴������
	/***************************************************************************************/
	//�ɼ�����ϵͳ
	void Score_menu();			//�ɼ�ϵͳ�Ĳ˵���ʾ�����û��ṩ���õĽ�����ʾ
	void Score_save();			//����ɼ���Ϣ�����ɼ���Ϣ������ĵ� scoFile.txt
	void Score_init();			//��ʼ��ϵͳ���� scoFile.txt �ĵ��������ĵ���Ϊ�����ȡ��ǰ�ļ�����
	void Enter_ScoreManager();  //�ɼ�ϵͳ�Ľӿں���
	void add_score();			//��ӿγ̳ɼ���Ϣ
	void Show_Score();			//��ʾѧ���γ̳ɼ�
	void Mod_Score();			//��Ŀ��ѧ��ѧ���ɼ������޸�
	void Del_Score();			//����ѧ���ɼ�
	void Find_Score();			//��ѯ���Ƴɼ���Ϣ
	/***************************************************************************************/
};