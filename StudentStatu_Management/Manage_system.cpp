#include "Manage_system.h"
#include <iostream>
using namespace std;
#include "Student.h"
using namespace std;

Student_Manager::Student_Manager()
{
	ifstream ifs;
	ifstream clis;
	ifstream scofs;
	ifs.open(FILENAME, ios::in);//��ȡѧ����Ϣ�ļ�
	clis.open(CLANAME, ios::in);//��ȡѧ���γ��ļ�
	scofs.open(SCORENAME, ios::in);//��ȡѧ���ɼ��ļ�

	//���ļ�������ʱ�ĳ�ʼ��
	if (!ifs.is_open())
	{
		this->stu_num = 0;
		this->StuArr = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		if (!clis.is_open())clis.close();
		if (!scofs.is_open())scofs.close();
		return;
	}

	//�ļ�����������Ϊ��ʱ�ĳ�ʼ��
	char ch;	ifs >> ch;
	if (ifs.eof()) {
		//�����ļ�Ϊ��
		this->stu_num = 0;
		this->StuArr = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		if (clis.eof()) clis.close();
		if (!scofs.eof())scofs.close();
		return;
	}

	//�ļ����ڣ���¼����
	int num = get_Stunum();
	this->stu_num = num;


	//���ٿռ�
	this->StuArr = new Student * [this->stu_num];

	//���ļ��е����ݴ�ŵ�������
	this->Init_stu();
	this->Init_cla();
	this->Score_init();
}

Student_Manager::~Student_Manager()
{
	if (this->m_FileIsEmpty != NULL)
	{
		for (int i = 0; i < this->stu_num; i++)
		{
			if (this->StuArr[i] != NULL)
			{
				StuArr[i] = NULL;
			}
		}
		delete[]this->StuArr;
		this->StuArr = NULL;
	}
}

void Student_Manager::Show_menu()
{
	system("color 7f");
	system("color 9f");
	//���õ�ɫ ��ɫ��ֵ���£�0 = ��ɫ  8 = ��ɫ 1 = ��ɫ  9 = ����ɫ  2 = ��ɫ  A = ����ɫ 3 = ����ɫ B = ��ǳ��ɫ 4 = ��ɫ C = ����ɫ 5 = ��ɫ  D = ����ɫ 6 = ��ɫ  E = ����ɫ 7 = ��ɫ  F = ����ɫ
	//3������ɫ��f����ǰ��ɫ
	system("mode con cols=85 lines=30");//�������ÿ�Ⱥ͸߸߶ȵ�
	system("title ѧ����Ϣ����ϵͳ");//�������̨�ı���

	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "************************---ѧ������ϵͳ----***************************" << endl;
	cout << "************************   0.�˳�ϵͳ      ***************************" << endl;
	cout << "************************   1.�����ѧ��    ***************************" << endl;
	cout << "************************   2.ɾ��ѧ����Ϣ  ***************************" << endl;
	cout << "************************   3.��ʾѧ����Ϣ  ***************************" << endl;
	cout << "************************   4.�޸�ѧ����Ϣ  ***************************" << endl;
	cout << "************************   5.����ѧ����Ϣ  ***************************" << endl;
	cout << "************************   6.����ѧ����Ϣ  ***************************" << endl;
	cout << "************************   7.����ĵ�      ***************************" << endl;
	cout << "************************   8.ͳ��ѧ������  ***************************" << endl;
	cout << "************************   9.�γ̹���ϵͳ  ***************************" << endl;
	cout << "************************  10.�ɼ�����ϵͳ  ***************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << endl;
}

void Student_Manager::Exit_System()
{
	cout << "��ӭ�´�ʹ��!!" << endl;
	system("pause");
	exit(0);
}

void Student_Manager::Add_stu()
{
	cout << "��������Ҫ��ӵ�ѧ������" << endl;
	int num = 0;
	cin >> num;

	if (num > 0)
	{
		int newsize = this->stu_num + num;//�¿ռ�Ĵ�С
		Student** newArray = new Student * [newsize];
		if (this->StuArr != NULL)
		{
			for (int i = 0; i < this->stu_num; i++)
			{
				newArray[i] = this->StuArr[i];
			}
		}
		for (int i = 0; i < num; i++)
		{
			string m_id;
			string m_name;
			int m_age;
			string m_sex;
			string m_major;

			cout << "������" << i + 1 << "��ѧ����������" << endl;
			cin >> m_name;

			cout << "������" << i + 1 << "��ѧ�������䣺" << endl;
			cin >> m_age;

			cout << "������" << i + 1 << "��ѧ�����Ա�" << endl;
			cin >> m_sex;

			cout << "������" << i + 1 << "��ѧ����רҵ��" << endl;
			cin >> m_major;

			cout << "������" << i + 1 << "��ѧ����ѧ�ţ�" << endl;
			cin >> m_id;

			Student* student = NULL;
			student = new Student(m_name, m_sex, m_age, m_id, m_major, 0);

			newArray[this->stu_num + i] = student;
		}
		delete[]this->StuArr;
		this->StuArr = newArray;
		this->stu_num = newsize;
		cout << "�ɹ����" << num << "��ѧ��" << endl;

		//�������ݵ��ļ�
		this->save();
		this->m_FileIsEmpty = false;
	}
	else {
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}

void Student_Manager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);			//������ķ�ʽ���ļ� -- д�ļ�

	for (int i = 0; i < stu_num; i++)
	{
		ofs << this->StuArr[i]->name << "  "
			<< this->StuArr[i]->id << "  "
			<< this->StuArr[i]->sex << "  "
			<< this->StuArr[i]->age << "  "
			<< this->StuArr[i]->major << endl;
	}
	ofs.close();
}

int Student_Manager::get_Stunum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	string id;
	string sex;
	int age;
	string major; int snum = 0;
	while (ifs >> name && ifs >> id && ifs >> sex && ifs >> age && ifs >> major)
	{
		snum++;
	}
	return snum;
}

void Student_Manager::Init_stu()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	string name;	string id;	string sex;	int age;	string major;
	int index = 0;
	while (ifs >> name && ifs >> id && ifs >> sex && ifs >> age && ifs >> major)
	{
		Student* student = NULL;
		student = new Student(name, sex, age, id, major, 0);
		this->StuArr[index++] = student;
	}
	ifs.close();
}

void Student_Manager::Show_stu()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->stu_num; i++)
			this->StuArr[i]->ShowInfo();
	}
	system("pause");
	system("cls");
}

void Student_Manager::Del_stu()
{
	if (this->m_FileIsEmpty)cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
	else
	{
		cout << "��������Ҫɾ����ѧ��ѧ�ţ�" << endl;
		string s_id = " "; cin >> s_id;

		int index = this->IsExist_stu(s_id);

		if (index != -1)
		{
			for (int i = index; i < this->stu_num - 1; i++)
				this->StuArr[i] = this->StuArr[i + 1];
			this->stu_num--;		//���������¼��Ա����
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ѧ��!" << endl;
	}
	this->save();
	this->clasave();
	this->Score_save();
	system("pause");
	system("cls");
	return;
}

int Student_Manager::IsExist_stu(string s_id)
{
	int index = -1;
	for (int i = 0; i < this->stu_num; i++)
		if (this->StuArr[i]->id == s_id)
		{
			index = i; break;
		}
	return index;
}

void Student_Manager::Mod_stu()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ������ڻ��ļ�Ϊ��!" << endl;
	else
	{
		cout << "�������޸�ѧ����ѧ�ţ�" << endl;
		string s_id;
		cin >> s_id;

		int ret = this->IsExist_stu(s_id);
		if (ret != -1)
		{
			string new_id = "";
			string new_name = "";
			string new_major = "";
			int new_age = 0;
			string new_sex = "";

			cout << "�ļ��д���ѧ��Ϊ��" << s_id << "��ѧ��" << endl;
			cout << "�������µ�ѧ��������" << endl;
			cin >> new_name;
			cout << "�������µ�ѧ���Ա�" << endl;
			cin >> new_sex;
			cout << "�������µ�ѧ�����䣺" << endl;
			cin >> new_age;
			cout << "�������µ�ѧ��ѧ�ţ�" << endl;
			cin >> new_id;
			cout << "�������µ�ѧ��רҵ��" << endl;
			cin >> new_major;

			Student* student = NULL;
			student = new Student(new_name, new_sex, new_age, new_id, new_major, 0);
			this->StuArr[ret] = student;
			cout << "�޸ĳɹ���" << endl;

			this->save();
			this->clasave();
			this->Score_save();
		}
		else cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
	}
	system("pause");
	system("cls");
}

void Student_Manager::Find_stu() {
	if (this->m_FileIsEmpty)
	{
		cout << "��ǰ�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�����" << endl;
		cout << "1---����ѧ����ѧ�Ų��ң�" << endl;
		cout << "2---����ѧ�����������ң�" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			string s;
			cout << "��������ҵ�ѧ����ѧ�ţ�" << endl;
			cin >> s;

			int ret = IsExist_stu(s);
			if (ret != -1)
			{
				cout << "���ҳɹ�������" << endl;
				this->StuArr[ret]->ShowInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2)
		{
			string sname;
			cout << "��������ҵ�������" << endl;
			cin >> sname;

			bool flag = false;

			for (int i = 0; i < this->stu_num; i++)
			{
				if (this->StuArr[i]->name == sname)
				{
					cout << "���ҳɹ���ѧ��ѧ��Ϊ��"
						<< this->StuArr[i]->id
						<< "����Ϣ���£�" << endl;

					this->StuArr[i]->ShowInfo();

					flag = true;
				}
			}
			if (!flag)cout << "����ʧ�ܣ����޴��ˣ�" << endl;
		}
		else {
			cout << "����ѡ������!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void Student_Manager::Sort_stu()
{
	if (this->m_FileIsEmpty)
		cout << "��ǰ�ļ�Ϊ�ջ��ļ������ڣ�����" << endl;
	else {
		cout << "��ѡ������ķ�ʽ" << endl;
		cout << "1---��ѧ����������" << endl;
		cout << "2---��ѧ�Ž�������" << endl;

		int choice = 0;
		cin >> choice;
		if (choice == 1)
		{
			for (int end = this->stu_num - 1; end > 0; end--)
				for (int begin = 0; begin < end; begin++)
				{
					if (StuArr[begin]->id.length() > StuArr[end]->id.length()
						|| ((StuArr[begin]->id.length() == StuArr[end]->id.length())
							&& StuArr[begin]->id > StuArr[end]->id))
					{
						string tempname = StuArr[begin]->name;
						string tempid = StuArr[begin]->id;
						string tempmajor = StuArr[begin]->major;
						string tempsex = StuArr[begin]->sex;
						int tempage = StuArr[begin]->age;

						StuArr[begin]->name = StuArr[end]->name;
						StuArr[begin]->id = StuArr[end]->id;
						StuArr[begin]->major = StuArr[end]->major;
						StuArr[begin]->sex = StuArr[end]->sex;
						StuArr[begin]->age = StuArr[end]->age;

						StuArr[end]->name = tempname;
						StuArr[end]->id = tempid;
						StuArr[end]->major = tempmajor;
						StuArr[end]->sex = tempsex;
						StuArr[end]->age = tempage;
					}
				}
		}
		else if (choice == 2)
		{
			for (int end = this->stu_num - 1; end > 0; end--)
				for (int begin = 0; begin < end; begin++)
				{
					if (StuArr[begin]->id.length() < StuArr[end]->id.length()
						|| ((StuArr[begin]->id.length() == StuArr[end]->id.length())
							&& StuArr[begin]->id < StuArr[end]->id))
					{
						string tempname = StuArr[begin]->name;
						string tempid = StuArr[begin]->id;
						string tempmajor = StuArr[begin]->major;
						string tempsex = StuArr[begin]->sex;
						int tempage = StuArr[begin]->age;

						StuArr[begin]->name = StuArr[end]->name;
						StuArr[begin]->id = StuArr[end]->id;
						StuArr[begin]->major = StuArr[end]->major;
						StuArr[begin]->sex = StuArr[end]->sex;
						StuArr[begin]->age = StuArr[end]->age;

						StuArr[end]->name = tempname;
						StuArr[end]->id = tempid;
						StuArr[end]->major = tempmajor;
						StuArr[end]->sex = tempsex;
						StuArr[end]->age = tempage;
					}
				}
		}
		else cout << "��������!!!" << endl;
		this->save();
	}
	system("pause");
	system("cls");
}

void Student_Manager::Clean_File()
{
	cout << "ȷ�����?" << endl;
	cout << "1---ȷ��" << endl;
	cout << "2---ȡ��" << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1)
	{
		ofstream cofs(CLANAME, ios::trunc);//�γ�ϵͳ�ļ�������
		cofs.close();

		if (this->StuArr != NULL)
		{
			for (int i = 0; i < this->stu_num; i++)
			{
				this->StuArr[i]->Clasnum = 0;
				delete[]this->StuArr[i]->Clas;
				this->StuArr[i]->Clas = NULL;
			}
		}
		/*------------------------------------------------------------------------*/
		ofstream sfs(SCORENAME, ios::trunc);//�ɼ�ϵͳ�ļ�������
		sfs.close();
		if (this->StuArr != NULL)
		{
			for (int i = 0; i < this->stu_num; i++)
			{
				delete[]this->StuArr[i]->Sco_re;
				this->StuArr[i]->Sco_re = NULL;
			}
		}


		/*------------------------------------------------------------------------*/
		ofstream ofs(FILENAME, ios::trunc);//ѧ��ϵͳ�ļ�������
		ofs.close();

		if (this->StuArr != NULL)
		{
			for (int i = 0; i < this->stu_num; i++)
			{
				//delete this->StuArr[i];
				this->StuArr[i] = NULL;
			}


			delete[]this->StuArr;
			this->StuArr = NULL;
			this->stu_num = 0;
			this->m_FileIsEmpty = true;
		}
	}
}

/*******************************************************************************/
void Student_Manager::Clas_Menu()
{
	system("color 7f");
	system("color 2f");
	//���õ�ɫ ��ɫ��ֵ���£�0 = ��ɫ  8 = ��ɫ 1 = ��ɫ  9 = ����ɫ  2 = ��ɫ  A = ����ɫ 3 = ����ɫ B = ��ǳ��ɫ 4 = ��ɫ C = ����ɫ 5 = ��ɫ  D = ����ɫ 6 = ��ɫ  E = ����ɫ 7 = ��ɫ  F = ����ɫ
	//3������ɫ��f����ǰ��ɫ
	system("mode con cols=85 lines=30");//�������ÿ�Ⱥ͸߸߶ȵ�
	system("title ѧ���γ̹���ϵͳ");//�������̨�ı���
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "************************----�γ̹���ϵͳ----***************************" << endl;
	cout << "************************   0.�����ϼ�����  ***************************" << endl;
	cout << "************************   1.���ѧ���γ�  ***************************" << endl;
	cout << "************************   2.ɾ��ѧ���γ�  ***************************" << endl;
	cout << "************************   3.����ѧ���γ�  ***************************" << endl;
	cout << "************************   4.�޸�ѧ���γ�  ***************************" << endl;
	cout << "************************   5.��ʾѧ���γ�  ***************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
}
void Student_Manager::Enter_ClassManager()
{
	while (true)
	{
		Clas_Menu();
		cout << "���������ѡ�� " << endl;
		int choose; cin >> choose;
		switch (choose)
		{
		case 0:
		{
			cout << "ȷ�Ϸ��أ���" << endl;
			cout << "1---ȷ��" << endl; cout << "2---ȡ��" << endl;
			int cho; cin >> cho;
			if (cho == 1)
			{
				system("cls");
				return;
			}
			else
			{
				system("cls");
				break;
			}
		}
		case 1:
			add_class();
			break;
		case 2:Del_Cla();
			break;
		case 3:Find_Cla();
			break;
		case 4:Mod_Cla();
			break;
		case 5:Show_Cla();
			break;
		}
	}system("pause"); system("cls");
}
void Student_Manager::add_class() {
	if (this->m_FileIsEmpty)
		cout << "��ǰ��¼Ϊ�գ��޷���ӣ���" << endl;
	else
	{
		cout << "��������Ҫ��ӿγ̵�ѧ����ţ�" << endl;
		string idd;
		cin >> idd;
		int ret = IsExist_stu(idd);
		if (ret != -1) {
			cout << "ѧ��  " << StuArr[ret]->name << "  Ŀǰ���пγ�����:    " << StuArr[ret]->Clasnum << endl;
			cout << "��������Ҫ��ӿγ̵�����" << endl;
			int num; cin >> num;
			int rnum = this->StuArr[ret]->Clasnum;
			if (rnum == 0 || StuArr[ret]->Clas == NULL)
			{
				this->StuArr[ret]->Clas = new string[num];
				//����������������������������������������������������������������������������
				this->StuArr[ret]->Sco_re = new string[num];
				//����������������������������������������������������������������������������
			}
			else
			{
				string* temp = new string[rnum + num];
				//����������������������������������������������������������������������������
				string* scotemp = new string[rnum + num];
				//����������������������������������������������������������������������������
				for (int i = 0; i < rnum; i++)
				{
					temp[i] = StuArr[ret]->Clas[i];
					//����������������������������������������������������������������������������
					scotemp[i] = StuArr[ret]->Sco_re[i];
					//����������������������������������������������������������������������������
				}
				delete[]StuArr[ret]->Clas;
				//����������������������������������������������������������������������������
				delete[]StuArr[ret]->Sco_re;
				//����������������������������������������������������������������������������
				//����������������������������������������������������������������������������
				StuArr[ret]->Sco_re = scotemp;
				//����������������������������������������������������������������������������
				StuArr[ret]->Clas = temp;
			}
			for (int i = rnum; i < num + rnum; i++)
			{
				cout << "������ӵĵ�" << i + 1 << "�ſγ̣�" << endl;
				cin >> StuArr[ret]->Clas[i]; StuArr[ret]->Sco_re[i] = "0";
			}

			this->StuArr[ret]->Clasnum += num;
			cout << "��ӿγ���ϣ���ǰ�γ�����Ϊ��" << this->StuArr[ret]->Clasnum << endl;
		}
		else cout << "��ѧ��������" << endl;
	}
	if (!this->m_FileIsEmpty)this->clasave();
	if (!this->m_FileIsEmpty)this->Score_save();
	system("pause");
	system("cls");
}
void Student_Manager::Show_Cla() {
	if (this->m_FileIsEmpty)
		cout << "��ǰ������ѧ�����޷���ʾ�γ�" << endl;
	else
	{
		cout << "������ѧ�ţ���ʾ��ѧ�ſγ���Ϣ" << endl;
		string stuid; cin >> stuid;
		int ret = IsExist_stu(stuid);
		if (ret != -1)
		{
			cout << "ѧ��Ϊ" << stuid << "��ѧ����" << StuArr[ret]->name
				<< "��ǰ�γ�������" << StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "�γ̣�" << i + 1 << "     " << StuArr[ret]->Clas[i] << endl;
		}
		else cout << "�����ڸ�ѧ��ѧ�����˳�" << endl;
	}
	system("pause");
	system("cls");
}
void Student_Manager::Mod_Cla() {
	if (!m_FileIsEmpty)
	{
		cout << "��������Ҫ�޸Ŀγ̵�ѧ��ѧ�ţ�" << endl;
		string idd; cin >> idd;
		int ret = IsExist_stu(idd);
		if (ret != -1)
		{
			cout << "����ѧ��Ϊ�� " << idd << " ��ѧ��" << endl;
			cout << "��ѧ��Ŀǰ�γ�����Ϊ�� " << this->StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "�γ̣�" << i + 1 << "     " << StuArr[ret]->Clas[i] << endl;
			cout << "��������Ҫ�޸ĵĿγ���" << endl;
			string mod_name; cin >> mod_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == mod_name)
				{
					cout << "�������޸ĺ�Ŀγ�  : " << endl;
					cin >> mod_name;
					StuArr[ret]->Clas[i] = mod_name;
					cout << "�޸ĳɹ�������" << endl;
					system("pause");
					this->clasave();
					return;
				}
				cout << "ѧ���� " << StuArr[ret]->name << " �����ڸÿγ̣���" << endl;
		}
		else
			cout << "������ѧ��Ϊ�� " << idd << " ��ѧ��" << endl;
	}
	else
		cout << "�ļ������ڣ���" << endl;
	system("pause");
	system("cls");
}
void Student_Manager::Del_Cla() {
	if (!this->m_FileIsEmpty)
	{
		cout << "��������Ҫ����ɾ��������ѧ����ţ�" << endl;
		string idd; cin >> idd;
		int ret = IsExist_stu(idd);
		if (ret != -1)
		{
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "�γ̣�" << i + 1 << "     " << StuArr[ret]->Clas[i] << endl;
			cout << "��������Ҫɾ���Ŀγ����ƣ�" << endl;
			string del_name; cin >> del_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++) {
				if (StuArr[ret]->Clas[i] == del_name)
				{
					for (int j = i + 1; j < StuArr[ret]->Clasnum; j++)
					{
						StuArr[ret]->Clas[j - 1] = StuArr[ret]->Clas[j];
						StuArr[ret]->Sco_re[j - 1] = StuArr[ret]->Sco_re[j];
					}
					this->StuArr[ret]->Clasnum--;
					this->Score_save(); this->clasave();
					cout << "ɾ���ɹ�����" << endl;
					system("pause"); return;
					return;
				}
			}
			cout << "ɾ��ʧ�ܣ��γ̲�����" << endl;
		}
		else cout << "������ѧ��Ϊ�� " << idd << " ��ѧ��" << endl;
	}
	else cout << "��ǰ������ѧ�����޷����пγ̹���" << endl;
}
void Student_Manager::Find_Cla() {
	if (!m_FileIsEmpty)
	{
		cout << "��������ҵ�ѧ�� �� " << endl;
		string stu_id; cin >> stu_id;
		int ret = IsExist_stu(stu_id);
		if (ret != -1)
		{
			cout << "��������Ҫ���ҵĿγ� ���� ��" << endl;
			string cla_name; cin >> cla_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == cla_name)
				{
					cout << "���� �γ̣�" << cla_name << endl;
					system("pause"); return;
				}
			cout << "�����ڿγ̣� " << cla_name << endl;
		}
		else cout << "������ѧ��Ϊ�� " << stu_id << " ��ѧ��" << endl;
	}
	else
		cout << "��ǰѧ������Ϊ�գ��޷����пγ̹�����" << endl;
	system("pause");
	system("cls");
}
void Student_Manager::Init_cla() {
	ifstream clis;
	clis.open(CLANAME, ios::in);
	string cname, cid, clas; int clsnum;

	int index = 0;

	while (clis >> cname && clis >> cid && clis >> clsnum)
	{
		this->StuArr[index]->Clas = new string[1000];
		this->StuArr[index]->Sco_re = new string[1000];
		this->StuArr[index]->Clasnum = clsnum;

		for (int i = 0; i < this->StuArr[index]->Clasnum; i++)
		{
			clis >> this->StuArr[index]->Clas[i];
		}
		index++;
	}
	clis.close();
}
void Student_Manager::clasave() {
	ofstream cofs;
	cofs.open(CLANAME, ios::out);

	for (int i = 0; i < this->stu_num; i++)
	{
		cofs << StuArr[i]->name << " " << StuArr[i]->id << " " << StuArr[i]->Clasnum << " ";
		for (int j = 0; j < this->StuArr[i]->Clasnum; j++)
			cofs << this->StuArr[i]->Clas[j] << " ";
		cofs << endl;
	}
	cofs.close();
}
/*******************************************************************************/

void Student_Manager::Score_menu()
{
	system("color 7f");
	system("color 6f");
	//���õ�ɫ ��ɫ��ֵ���£�0 = ��ɫ  8 = ��ɫ 1 = ��ɫ  9 = ����ɫ  2 = ��ɫ  A = ����ɫ 3 = ����ɫ B = ��ǳ��ɫ 4 = ��ɫ C = ����ɫ 5 = ��ɫ  D = ����ɫ 6 = ��ɫ  E = ����ɫ 7 = ��ɫ  F = ����ɫ
	//3������ɫ��f����ǰ��ɫ	
	system("mode con cols=85 lines=30");//�������ÿ�Ⱥ͸߸߶ȵ�
	system("title ѧ���ɼ�����ϵͳ");//�������̨�ı���
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "************************----�ɼ�����ϵͳ----***************************" << endl;
	cout << "************************   0.�����ϼ�����  ***************************" << endl;
	cout << "************************   1.���ѧ���ɼ�  ***************************" << endl;
	cout << "************************   2.����ѧ���ɼ�  ***************************" << endl;
	cout << "************************   3.��ѯѧ���ɼ�  ***************************" << endl;
	cout << "************************   4.�޸�ѧ���ɼ�  ***************************" << endl;
	cout << "************************   5.��ʾѧ���ɼ�  ***************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
}
void Student_Manager::Enter_ScoreManager()
{
	while (true)
	{
		Score_menu();
		cout << "���������ѡ�� " << endl;
		int cho; cin >> cho;
		switch (cho)
		{
		case 0:
		{
			cout << "ȷ�Ϸ��أ���" << endl;
			cout << "1---ȷ��" << endl; cout << "2---ȡ��" << endl;
			int chio; cin >> chio;
			if (chio == 1)
			{
				system("cls");
				return;
			}
			else
			{
				system("cls");
				break;
			}
		}
		case 1:
			add_score();
			break;
		case 2:Del_Score();
			break;
		case 3:Find_Score();
			break;
		case 4:Mod_Score();
			break;
		case 5:Show_Score();
			break;
		}
	}system("pause"); system("cls");
}
void Student_Manager::add_score()
{
	if (this->m_FileIsEmpty)cout << "��ǰϵͳ�޼�¼ѧ��������ʧ�� ! ! !" << endl;
	else {
		cout << "������Ҫ��Ҫ���в�����ѧ��ѧ�ţ� " << endl;
		string id;
		cin >> id;
		int ret = IsExist_stu(id);
		if (ret != -1) {
			cout << "ѧ��  " << StuArr[ret]->name << "  Ŀǰ���пγ�����:    " << StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "�γ̣�" << i + 1 << "     " << StuArr[ret]->Clas[i] << endl;
			cout << "��������Ҫ�����Ŀγ̵�����" << endl;
			string mod_name; cin >> mod_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == mod_name)
				{
					cout << "�����¼������" << endl;
					string tempscore = ""; cin >> tempscore;
					this->StuArr[ret]->Sco_re[i] = tempscore;
					cout << "�ɼ��޸ĳɹ� ! ! ! " << endl;
					break;
				}
		}
		else cout << "������ѧ��Ϊ�� " << id << "��ѧ��" << endl;
	}
	if (!this->m_FileIsEmpty)this->Score_save();
	system("pause");
	system("cls");
}
void Student_Manager::Score_save()
{
	ofstream scofs;
	scofs.open(SCORENAME, ios::out);

	for (int i = 0; i < this->stu_num; i++)
	{
		for (int j = 0; j < this->StuArr[i]->Clasnum; j++)
			scofs << StuArr[i]->name << " " << StuArr[i]->id << " " << this->StuArr[i]->Clas[j] << " " << this->StuArr[i]->Sco_re[j] << endl;
	}
	scofs.close();
}
void Student_Manager::Score_init()
{
	ifstream scis;
	scis.open(SCORENAME, ios::in);
	string cname, cid, scname, sco;

	int index = 0;

	while (scis >> cname && scis >> cid && scis >> scname && scis >> sco)
	{
		int tret = this->IsExist_stu(cid);
		if (tret != -1)
			for (int i = 0; i < this->StuArr[tret]->Clasnum; i++)
				if (this->StuArr[tret]->Clas[i] == scname)
				{
					this->StuArr[tret]->Sco_re[i] = sco;
					break;
				}
	}
	scis.close();
}
void Student_Manager::Show_Score()

{
	if (this->m_FileIsEmpty)
		cout << "��ǰ������ѧ�����޷���ʾ�γ�" << endl;
	else
	{
		cout << "������ѧ�ţ���ʾ��ѧ�ſγ̳ɼ���Ϣ" << endl;
		string stuid; cin >> stuid;
		int ret = IsExist_stu(stuid);
		if (ret != -1)
		{
			cout << "ѧ��Ϊ" << stuid << "��ѧ����" << StuArr[ret]->name
				<< "��ǰ�γ�������" << StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "�γ�:     " << StuArr[ret]->Clas[i] << "   ����Ϊ�� " << StuArr[ret]->Sco_re[i] << endl;
		}
		else  cout << "�����ڸ�ѧ��ѧ�����˳�" << endl;
	}
	system("pause");
	system("cls");
}
void Student_Manager::Mod_Score()	
{
	if (!m_FileIsEmpty)
	{
		cout << "��������Ҫ�޸ĳɼ���ѧ��ѧ�ţ�" << endl;
		string idd; cin >> idd;
		int ret = IsExist_stu(idd);
		if (ret != -1)
		{
			cout << "����ѧ��Ϊ�� " << idd << " ��ѧ��" << endl;
			cout << "��ѧ��Ŀǰ�γ�����Ϊ�� " << this->StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "�γ̣�" << i + 1 << "     " << StuArr[ret]->Clas[i] << "		Ŀǰ����Ϊ��" << StuArr[ret]->Sco_re[i] << endl;
			cout << "��������Ҫ�޸ĳɼ��Ŀγ���" << endl;
			string mod_score; cin >> mod_score;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == mod_score)
				{
					cout << "�������޸ĺ�ĳɼ�  : " << endl;
					cin >> mod_score;
					StuArr[ret]->Sco_re[i] = mod_score;
					cout << "�޸ĳɹ�������" << endl;
					break;
				}
		}
		else
			cout << "������ѧ��Ϊ�� " << idd << " ��ѧ��" << endl;
	}
	else
		cout << "�ļ������ڣ���" << endl;
	this->Score_save();
	system("pause");
	system("cls");
}
void Student_Manager::Del_Score()
{
	if (this->m_FileIsEmpty)cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
	else
	{
		cout << "��������Ҫ���óɼ���ѧ��ѧ�ţ�" << endl;
		string s_id = " "; cin >> s_id;

		int index = this->IsExist_stu(s_id);

		if (index != -1)
		{
			for (int i = 0; i < StuArr[index]->Clasnum; i++)
				this->StuArr[index]->Sco_re[i] = "0";
			this->Score_save();
			cout << "���óɹ�" << endl;
		}
		else
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ѧ��!" << endl;
	}
	system("pause");
	system("cls");
	return;
}
void Student_Manager::Find_Score()
{
	if (!m_FileIsEmpty)
	{
		cout << "�������ѯ��ѧ�� �� " << endl;
		string stu_id; cin >> stu_id;
		int ret = IsExist_stu(stu_id);
		if (ret != -1)
		{
			cout << "��������Ҫ��ѯ�Ŀγ� ���� ��" << endl;
			string cla_name; cin >> cla_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == cla_name)
				{
					cout << "�γ̣�" << cla_name <<"�ɼ�Ϊ��"<<StuArr[ret]->Sco_re[i] << endl;
					system("pause"); return;
				}
			cout << "�����ڿγ̣� " << cla_name << endl;
		}
		else cout << "������ѧ��Ϊ�� " << stu_id << " ��ѧ��" << endl;
	}
	else
		cout << "��ǰѧ������Ϊ�գ��޷����пγ̹�����" << endl;
	system("pause");
	system("cls");

}