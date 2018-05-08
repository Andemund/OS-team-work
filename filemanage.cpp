/*����ϵͳ�ļ�����
���ô��̿ռ��ܴ�СMAX_SPACE��2048
���С 2
���� 1024
�ļ��洢�㷨����Ƭ���
ʹ������
����ϵͳ��ʼ����ʱ�����������ؽ����ڴ棿
�����������ݴ洢��ʽ��
�ļ�������ʽ���ṹ��-����-����-����ʱ��-·��-��С-��һ��ָ��/����

*/

//#include "stdafx.h"
#include "File_management.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<iomanip>
#include<math.h>
#include<Windows.h>
#include<map>
#include "shellapi.h"
using namespace std;

Available * find_disk_space();
void new_File();
//void init_diskpart();
File * get_file_info();

void new_File_Index(File *);
void get_folder_info();
bool already_exist(Folder *, File *);
void allocate_link(File *);
void allocate_index(File *);
void split_file_link(File *, Available *);
void change_prev_folder_size(Folder *, const char *, File *);
Folder * Located(char position[]);
void demo();
void Print(Folder * p1, File * p2);
//void show_disk_usage();

void init_block_space();
void show_current_block();
void allocate_block(File *);
void recover_link(File *);
void recover_index(File *);
void delete_File();
void delete_File_Index(File * );

File * find_name(Folder * ptr, char contact[]);
void find_type(Folder * ptr, char contact[]);
void Find(char arr[]);
void function();
char * Print_location(Folder * ptr);

void Open_file(char locate[], char name[]);
void Open(char arr[]);
char * Located_change(char source[]);
void print_current_ptr(Folder * ptr);
double Fsize(Folder * ptr);
void Order_by_size(char arr[]);
void Order(Folder * ptr, int op);


int main()
{
	Folder * ptr1;
	File * ptr2;
	demo();

	cout << "��ѡ����̿ռ���䷽ʽ��1-���ӣ�2-������3-������" << endl;
	cin >> org_method;
	getchar();
	cin.clear();
	cin.sync();
	if (org_method == 1 || org_method == 2 || org_method == 3)
	{
		init_block_space();
		show_current_block();
	}
	else 
	{
		cout << "�Ƿ�����" << endl;
		return 0;
	}
	function();

	system("pause");
	return 0;
}

//���ܺ���
void function()
{
	char instruct[300];
	char ch[100];
	cin.clear();
	cin.sync();
	cout << "D:/�ҵĵ���>";
	cin.clear();
	cin.sync();
	gets_s(instruct);


	while (true)
	{
		int j = 0;
		memset(ch, 0, sizeof(ch));
		for (int i = 0; instruct[i] != NULL; i++)
		{
			//ch[]�洢�����ָ��ǰ׺
			if (instruct[i] != ' ') {
				ch[j] = instruct[i];
				j++;
			}
			else {
				if (strcmp(ch, "cd") != 0) {
					break;
				}
				else {
					strcat_s(ch, " ");
					j++;
				}

			}
		}

		if (strcmp(ch, "-help") == 0)
		{
			cout << endl;
			cout << "	-cd		��ʾ��ǰĿ¼�����ƻ������" << endl;
			cout << "	-check		�鿴����Ŀ¼�ṹ" << endl;
			cout << "	-drop file	ɾ���ļ�" << endl;
			cout << "	-drop folder	ɾ���ļ���" << endl;
			cout << "	-find		����" << endl;
			cout << "	-help		����" << endl;
			cout << "	-new file	�����ļ�" << endl;
			cout << "	-new folder	�����ļ���" << endl;
			cout << "	-open		���ļ�" << endl;
			cout << "	-order		�����ļ���С����" << endl;
			cout << endl;
		}
		//��ʾ��ǰĿ¼����
		else if (strcmp(ch, "cd") == 0)
		{
			cout << "D:";
			print_current_ptr(current_ptr);
			cout << endl;

		}
		//���ظ�Ŀ¼
		else if (strcmp(ch, "cd \\") == 0)
		{
			current_ptr = init_folder;   //ָ������ҵĵ���

		}
		//���Ҳ���
		else if (strcmp(ch, "-find") == 0)
		{
			Find(instruct);
			if (tem == 0)
			{
				cout << "û����ò�������ƥ����ļ����ļ���" << endl;
			}
		}
		//�������ļ�
		else if (strcmp(ch, "-new file") == 0)
		{
			new_File();
		}
		//�������ļ���
		else if (strcmp(ch, "-new folder") == 0)
		{
			//	new_Folder();
		}
		//ɾ���ļ���
		else if (strcmp(ch, "-drop folder") == 0)
		{
			//	new_Folder();
		}
		//ɾ���ļ�
		else if (strcmp(ch, "-drop file") == 0)
		{
			delete_File();
		}
		//��ӡ��ǰĿ¼
		else if (strcmp(ch, "-check") == 0)
		{
			tab = 0;
			Print(current_ptr, init_file);
		}
		//���ļ�
		else if (strcmp(ch, "-open") == 0)
		{
			Open(instruct);
		}
		//������һ��
		else if (strcmp(ch, "cd..") == 0)
		{
			//���������һ�����򷵻���һ��
			//��������ڣ���current_ptr����
			if (current_ptr->return_to_pre != NULL) {
				current_ptr = current_ptr->return_to_pre;
			}
		}
		//��ǰĿ¼�°����ļ���С����
		else if (strcmp(ch, "-order") == 0)
		{
			Order_by_size(instruct);
		}
		else
		{
			int p = 0, i = 0;   //�жϱ�־

								//���� cd �ļ��� ���뵱ǰ�ļ��е��ж�
			char cd_op[20][30];
			char m[30];
			Folder * mptr = current_ptr->in_folder;

			for (int m = 0; m < 20; m++) {
				memset(cd_op[m], 0, sizeof(cd_op[m]));
			}

			for (i = 0; mptr != NULL; i++, mptr = mptr->next) {
				strcpy_s(cd_op[i], "cd");
				strcat_s(cd_op[i], " ");
				strcat_s(cd_op[i], mptr->name);
			}
			for (int j = 0; strcmp(cd_op[j], "") != 0; j++) {
				if (strcmp(ch, cd_op[j]) == 0)
				{
					//��λcurrent_ptr��ǰָ��
					for (current_ptr = current_ptr->in_folder; current_ptr != NULL; )
					{

						strcpy_s(m, "cd ");
						strcat_s(m, current_ptr->name);
						if (strcmp(m, cd_op[j]) != 0)
						{
							current_ptr = current_ptr->next;
						}
						else {
							p = 1;
							break;
						}
					}
					break;
				}
			}

			if (p == 0) {
				cout << ch << " �����ڲ����ⲿ���Ҳ���ǿ����еĳ�����������ļ���" << endl;
			}

		}
		cout << endl;
		memset(ch, 0, sizeof(ch));
		cout << "D:";
		print_current_ptr(current_ptr);
		cout << ">";
		cin.clear();
		cin.sync();
		//getchar();
		gets_s(instruct);
	}

}

//�������ļ�
void new_File()
{
	//�жϴ����Ƿ���ʣ��ռ�
	//��������
	if (Remain_M <= 0)
	{
		cout << "Insufficient disk space." << endl;
		cout << "Operation failed." << endl;
		return;
	}

	//���̻���ʣ��ռ�
	File * newf;
	newf = get_file_info();

	
	//ͬ�ļ������Ƿ���ͬ���ļ�����
	if (already_exist(newf->return_to_pre, newf))
	{
		cout << "That file is already exist." << endl;
		cout << "Operation failed." << endl;
		return;
	}

	//�ļ���С����ʣ��ռ�
	if (newf == NULL)
	{
		cout << "Insufficient disk space." << endl;
		cout << "Operation failed." << endl;
		return;
	}


	//�����ַ�߼���ַ
	if (org_method == 1)//link
	{
		/*
		Available * maxpiece = find_disk_space();
		if (maxpiece != NULL)
		{
			
			split_file_link(newf, maxpiece);
		}
		else
		{
			cout << "Operation failed." << endl;
			return;
		}
		*/
		allocate_link(newf);
	}
	else if (org_method == 2)//index
	{
		//allocate_block(newf);
		allocate_index(newf);
	}
	else if (org_method == 3)//sequential
	{

	}
	else
	{
		cout << "allocating method is not exist." << endl;
		cout << "Operation failed." << endl;
		return;
	}
	//���ļ������Ӧ�ļ�����
	new_File_Index(newf);

	Remain_M = Remain_M - ceil(newf->fsize);
	show_current_block();
	cout << "��ǰʣ��ռ䣺" << Remain_M << endl;
	cout << "New file created." << endl;
	//Print(init_folder, init_file);
	return;
}


//------------------------ͨ�ò��� begin-----------------------------
//��ȡ�½��ļ���Ϣ    check
File * get_file_info()
{
	File * temp = new File;
	cin.clear();
	cin.sync();
	cout << "�½��ļ�·����" << endl;
	cin >> temp->location;
	cin.clear();
	cin.sync();
	//��������޸��ļ��������ĺ���
	Folder * a = Located(temp->location);
	temp->return_to_pre = a;
	cout << a << endl;
	cout << "�½��ļ����ƣ�";
	cin >> temp->name;
	cin.clear();
	cin.sync();
	cout << "�½��ļ����ͣ�";
	cin >> temp->belong;
	cin.clear();
	cin.sync();
	cout << "�½��ļ���С��";
	cin >> temp->fsize;
	cin.clear();
	cin.sync();

	if (temp->fsize >= Remain_M)
	{
		return NULL;
	}

	//��ȡ��ǰϵͳʱ����Ϊ�״��޸�ʱ��
	return temp;
}


//�ж��ļ������Ƿ��Ѿ�����ͬ���ļ�    check
bool already_exist(Folder * a, File * b)
{
	File * c = a->in_file;
	while (c != NULL)
	{
		if (!strcmp(c->name, b->name))
		{
			return true;
		}
		c = c->next;
	}

	return false;
}


//�޸��ļ����ڵ��ļ�����Ϣ    check
void new_File_Index(File * f)
{
	//call the fuction to get the path
	Folder * a = f->return_to_pre;	//current folder
	File * b = a->in_file;	//first file in this folder
	if (b == NULL)
	{
		a->in_file = f;
	}
	else
	{
		while (b->next != NULL)
		{
			b = b->next;
		}
	}
	b->next = f;
	f->next = NULL;
	change_prev_folder_size(a, "+", f);
	return;
}


//�ݹ飬�ı�һ���ļ������������������ϲ��ļ��еĴ�С�仯  check
void change_prev_folder_size(Folder * f, const char * a, File * t)
{

	if (f->return_to_pre == NULL)
	{
		return;
	}
	if (a == "+")
	{
		f->fsize = f->fsize + t->fsize;
		change_prev_folder_size(f->return_to_pre, "+", t);
	}
	else
	{
		if (a == "-")
		{
			f->fsize = f->fsize - t->fsize;
			change_prev_folder_size(f->return_to_pre, "-", t);
		}
		else
		{
			cout << "incorrect symbol" << endl;
			return;
		}
	}
}


//��ʼ�����̿ռ䣬Ԥ��	check
void init_block_space()
{
	init_block = new Block;
	init_block->content = -1;
	init_block->next_no = 0;
	init_block->no = -1;
	block[0] = init_block;

	//Ԥ���ռ�
	for (int i = 1; i < INDEXSPACE / BLOCKSIZE; i++)
	{
		block[i] = new Block;
		block[i]->content = 2;
		block[i]->no = i;
		block[i]->next_no = i + 1;
	}
	block[INDEXSPACE / BLOCKSIZE] = new Block;
	block[INDEXSPACE / BLOCKSIZE]->content = 2;
	block[INDEXSPACE / BLOCKSIZE]->no = INDEXSPACE / BLOCKSIZE;
	block[INDEXSPACE / BLOCKSIZE]->next_no = 0;

	//��ʼ�����ļ�
	for (int i = INDEXSPACE / BLOCKSIZE + 1; i < BLOCKNUM; i++)
	{
		block[i] = new Block;
		block[i]->content = 0;
		block[i]->no = i;
		block[i]->next_no = i + 1;
	}
	block[BLOCKNUM] = new Block;
	block[BLOCKNUM]->content = 0;
	block[BLOCKNUM]->no = BLOCKNUM;
	block[BLOCKNUM]->next_no = 0;

	empty_block_begin = INDEXSPACE / BLOCKSIZE + 1;
	empty_block_end = BLOCKNUM;

	cout << "���п���ʼ��" << empty_block_begin << endl;
	cout << "���п������" << empty_block_end << endl;
	return;
}


//ʸ��ͼ����ʽչʾ��ǰ����ռ�����	check
void show_current_block()
{
	for (int i = 0; i < BLOCKNUM; i++)
	{
		cout << block[i]->content << " ";
		if (i % 32 == 31)
		{
			cout << endl;
		}
	}
	return;
}


//�����½��ļ�����Ϣ	check
void get_folder_info()
{
	Folder * temp = new Folder;
	char t[50];
	Folder * a;	//the last folder in the uplevel folder
	Folder * b;
	cout << "�½��ļ���·����" << endl;
	cin >> t;
	//��������޸��ļ��������ĺ���
	a = Located(t);
	cout << a->name << endl;
	temp->return_to_pre = a;
	b = a->in_folder;
	if (b == NULL)
	{
		cout << "b==NULL" << endl;
		a->in_folder = temp;
	}
	else
	{
		while (b->next != NULL)
		{
			b = b->next;
		}
		b->next = temp;
	}
	temp->fsize = 0;
	temp->in_file = NULL;
	temp->in_folder = NULL;
	temp->next = NULL;

	//temp->time = ;	//current system time

	cout << "�½��ļ������ƣ�";
	cin >> temp->name;
	cin.clear();
	cin.sync();

	return;
}

//ɾ���ļ�
void delete_File()
{
	//call the function
	char p[50];
	char n[20];
	cout << "�ļ�·����" << endl;
	cin >> p;
	cin.clear();
	cin.sync();
	cout << "�ļ�����" << endl;
	cin >> n;
	//��������޸��ļ��������ĺ���
	Folder * a = Located(p);
	cout << a->name;
	File * deletef = find_name(a, n);
	cout << deletef->name << endl;

	if (org_method == 1)//link
	{
		recover_link(deletef);
	}
	else if (org_method == 2)//index
	{
		recover_index(deletef);
	}
	else if (org_method == 3)//sequential
	{

	}
	else
	{
		cout << "drop method is not exist." << endl;
		cout << "Operation failed." << endl;
		return;
	}

	//�޸��ļ���
	delete_File_Index(deletef);

	Remain_M = Remain_M + ceil(deletef->fsize);
	show_current_block();
	cout << "��ǰʣ��ռ䣺" << Remain_M << endl;
	cout << "File dropped." << endl;
}


//ɾ���ļ����޸�����ļ��нṹ
void delete_File_Index(File * f)
{
	Folder * a = f->return_to_pre;
	if (a->in_file == f)
	{
		a->in_file = f->next;
	}
	else
	{
		File * b = a->in_file->next;
		File * c = a->in_file;
		while (b != f && b != NULL)
		{
			b = b->next;
			c = c->next;
		}
		c->next = b->next;
	}
	change_prev_folder_size(f->return_to_pre, "-", f);
	return;
}


//------------------------ͨ�ò��� end-----------------------------



//show current disk usage
/*void show_disk_usage()
{
	cout << "Disk usage:" << endl;
	for (int i = 0; i < Disk_M; i++)
	{
		cout << disk_block[i] << " ";
		if (i % 16 == 15)
		{
			cout << endl;
		}
	}
}
*/



//--------------------------��Ƭ��� begin------------------------------------
//when file size > current maxpiece, split the file
void split_file_link(File * newf, Available * maxpiece)
{
	//�������ʣ��ռ���Դ���ļ�
	if (maxpiece->length >= ceil(newf->fsize))
	{
		newf->phy_loc = maxpiece->start;
		newf->next = NULL;
		newf->piece = NULL;
		maxpiece->start = maxpiece->start + ceil(newf->fsize);
		maxpiece->length = maxpiece->length - ceil(newf->fsize);

		//ʵ�ʷ�������ռ�
		//allocate(newf);

		//��������ʣ��ռ�����
		Available * w = maxpiece->next;
		while (w != NULL)
		{
			if (maxpiece->length < w->length)
			{
				maxpiece->next = w;
				w->prev = maxpiece->prev;
				maxpiece->prev = w;
				w->next = maxpiece;
				w = maxpiece->next;
			}
			else
			{
				break;
			}
		}
		return;
	}
	//ʣ�������ռ䲻��
	else
	{
		newf->phy_loc = maxpiece->start;
		File * m = new File;
		//split_file(newf, maxpiece, m);
		newf->next = NULL;
		newf->piece = m;
		maxpiece->start = maxpiece->length - ceil(newf->fsize);
		maxpiece->prev->next = maxpiece->next;
		maxpiece->next->prev = maxpiece->prev;


		for (int i = 0; i<20; i++)
		{
			m->name[i] = newf->name[i];
			m->time[i] = newf->time[i];
		}
		m->next = NULL;
		m->piece = NULL;
		newf->fsize = maxpiece->length;
		m->fsize = newf->fsize - maxpiece->length;

		init_available->next = maxpiece->next;
		maxpiece->next->prev = maxpiece->prev;


		Available * n = find_disk_space();
		split_file_link(m, n);

		return;
	}
}

//�ҵ���ǰ�����Ƭ
Available * find_disk_space()
{
	//Available * temp;
	Available * m;
	m = init_available->next;
	if (m != NULL)
	{
		return m;
	}
	return NULL;
}

//--------------------------��Ƭ��� end------------------------------------



//--------------------------���ӷ�ʽ begin--------------------------------------
//���ӷ�ʽ�·�������ռ�	check
void allocate_link(File * f)
{
	int i = 0;
	f->phy_loc = empty_block_begin;
	for (i = 0; i < ceil(f->fsize) - 1; i++)
	{
		//1 means allcoated to one file
		block[empty_block_begin]->content = 1;
		empty_block_begin=block[empty_block_begin]->next_no;
	}
	block[empty_block_begin]->content = 1;
	block[empty_block_begin]->next_no = 0;
	empty_block_begin = block[empty_block_begin]->next_no;
	return;
}

//���ӷ�ʽ��ɾ���ļ�ʱ�ָ���Ӧ�������	check
void recover_link(File * f)
{
	Block * temp = block[f->phy_loc];
	while (temp->next_no > 0)
	{
		temp->content = 0;
		block[empty_block_end]->next_no = temp->no;
		empty_block_end = temp->no;
		temp = block[temp->next_no];
	}
	temp->content = 0;
	block[empty_block_end]->next_no = temp->no;
	empty_block_end = temp->no;
	block[empty_block_end]->next_no = 0;
	return;
}

//--------------------------���ӷ�ʽ end--------------------------------------

void allocate_block(File * f)
{
	f->phy_loc = block[INDEXSPACE / BLOCKSIZE]->next_no;
	Block * b = block[block[INDEXSPACE / BLOCKSIZE]->next_no];
	for (int i = 0; i < ceil(f->fsize / BLOCKSIZE); i++)
	{
		b->content = 1;
		block[INDEXSPACE / BLOCKSIZE]->next_no = b->next_no;
		b = block[block[INDEXSPACE / BLOCKSIZE]->next_no];
	}
	b->next_no = -1;
	return;
}

//--------------------------������ʽ begin--------------------------------------
//������ʽ�·�������ռ�	check
void allocate_index(File * f)
{
	f->phy_loc = empty_block_begin;
	int i = 0;
	while (i < ceil(f->fsize) - 1)
	{
		f->file_index.insert(pair<int, int>(i + 1, empty_block_begin));
		block[empty_block_begin]->content = 1;
		empty_block_begin = block[empty_block_begin]->next_no;
		i++;
	}
	f->file_index.insert(pair<int, int>(i + 1, empty_block_begin));
	block[empty_block_begin]->content = 1;
	block[empty_block_begin]->next_no = 0;
	empty_block_begin = block[empty_block_begin]->next_no;
	return;
}


//������ʽ��ɾ���ļ�ʱ�ָ���Ӧ�������	check
void recover_index(File * f)
{
	int i = 0;
	while (i < ceil(f->fsize) - 1)
	{
		block[f->file_index[i + 1]] = 0;
		block[empty_block_end]->next_no = block[f->file_index[i + 1]]->no;
		empty_block_end = block[f->file_index[i + 1]]->no;
		i++;
	}
	block[f->file_index[i + 1]] = 0;
	block[empty_block_end]->next_no = block[f->file_index[i + 1]]->no;
	empty_block_end = block[f->file_index[i + 1]]->no;
	block[empty_block_end]->next_no = 0;

	return;
}

//--------------------------������ʽ end--------------------------------------


//--------------------------˳��ʽ begin--------------------------------------
//˳��ʽ�·�������ռ�
void allocate_sequential(File * f)
{
	int i = 0;
	f->phy_loc = empty_block_begin;
	for (i = 0; i < ceil(f->fsize) - 1; i++)
	{
		//1 means allcoated to one file
		block[empty_block_begin]->content = 1;
		empty_block_begin = block[empty_block_begin]->next_no;
	}
	block[empty_block_begin]->content = 1;
	block[empty_block_begin]->next_no = 0;
	empty_block_begin = block[empty_block_begin]->next_no;
	return;
}



//--------------------------˳��ʽ end--------------------------------------



//* ********** * 
//*     YDY    *
//* ********** *

//---------------·����λ�á���ӡ���----------------------------------------------------
//����·������
Folder * Located(char position[])
{
	int i = 0, j = 0, level = -1;   //level��ʾ�ڼ���Ŀ¼��0��Ϊ��Ŀ¼
	char root[30];
	memset(root, 0, sizeof(root));
	Folder * ptr;   //��ʱ����ָ��

	ptr = init_folder;    //��ptrָ���Ŀ¼�µĵ�һ���ļ���
	for (i = 0, j = 0; position[i] != NULL; i++)
	{
		if (position[i] == '/')
		{
			//�жϴ���
			if (level == -1) {
				if (strcmp(root, "D:") != 0)
				{
					break;
				}
			}
			//�жϸ�Ŀ¼�Ƿ���ȷ
			else if (level == 0) {
				if (strcmp(root, "�ҵĵ���") != 0) {
					return NULL;
				}
				ptr = ptr->in_folder;
			}
			//�ж�������ļ���Ŀ¼�Ƿ���ȷ
			else
			{
				for (; (strcmp(ptr->name, root) != 0) && (ptr->next != NULL); )
				{
					ptr = ptr->next;  //ƥ���ļ��е����֣�����ȣ���ָ��ͬĿ¼����һ��
				}
				//�ҵ����ļ���
				if (strcmp(ptr->name, root) == 0)
				{
					//cout << level << "��Ŀ¼Ϊ ��" << root << endl;
					ptr = ptr->in_folder;
				}
				else {
					//cout << "û���ҵ���" << root << "��Ŀ¼����������·���Ƿ���ȷ��" << endl;
					return NULL;
				}
			}
			memset(root, 0, sizeof(root));
			j = 0;
			level++;
		}
		else
		{
			root[j] = position[i];
			j++;
		}
	}
	if (position[i] == NULL)
	{
		cout << endl;
		if (level == 1) {
			return init_folder;
		}
		else
		{
			cout << ptr->name << endl;
			return  ptr->return_to_pre;
		}
	}
}


//��ӡ��ǰ�ļ�Ŀ¼�ṹ��Ƕ�״�ӡ
void Print(Folder * p1, File * p2)
{
	Folder * ptr1;
	File * ptr2;
	int m;

	//Ŀ¼�µ��ļ��в�Ϊ��
	for (; p1 != NULL;)
	{
		for (m = 0; m < tab; m++)
		{
			cout << "	";        //һ������
		}
		cout << p1->name << endl;      //��ӡ��ǰ�ļ��е�����

									   //ָ����ļ�����������ļ�
		ptr1 = p1->in_folder;
		ptr2 = p1->in_file;
		if (ptr2 != NULL || ptr1 != NULL)
		{
			tab++;
		}
		for (; ptr2 != NULL; )
		{

			for (m = 0; m < tab; m++)
			{
				cout << "	";        //һ������
			}
			//��ӡ�ļ��������ļ����ļ���
			cout << ptr2->name << endl;
			ptr2 = ptr2->next;
		}
		//��ӡ�ļ��������ļ��У���Ҫ���õݹ��㷨
		if (ptr1 != NULL)
		{
			Print(ptr1, ptr2);
		}
		//��ӡ��Ŀ¼�µ��ֵ��ļ�
		tab--;
		if (p1 != current_ptr) {
			p1 = p1->next;
		}
		else {
			break;
		}

	}


	//��Ŀ¼�µ��ļ���Ϊ��
	for (; p2 != NULL;)
	{
		for (int m = 0; m < tab; m++)
		{
			cout << "	";        //һ������
		}
		cout << p2->name << endl;
		p2 = p2->next;
	}

	if (p1 == NULL && p2 == NULL)
	{
		return;
	}
}

//����λ�õĺ���
char * Print_location(Folder * ptr)
{
	char way[10][20];
	char way2[50];
	memset(way2, 0, sizeof(way2));
	int i = 0, j = 0;
	while (ptr->return_to_pre != NULL)
	{
		strcpy_s(way[i], 20, ptr->name);
		ptr = ptr->return_to_pre;
		i++;
	}
	i = i - 1;
	strcat_s(way2, "D:/�ҵĵ���/");
	for (i, j; i >= 0; i--, j++)
	{
		strcat_s(way2, way[i]);
		strcat_s(way2, "/");
	}
	return way2;
}

//��ӡ����ǰָ��ĺ���
void print_current_ptr(Folder * ptr)
{
	Folder *m = ptr;
	int i = 0;
	char cname[20][30];

	strcpy_s(current_locate,sizeof("D:"), "D:");
	for (i = 0, m; m != NULL; i++) {
		strcpy_s(cname[i],sizeof(m->name), m->name);
		m = m->return_to_pre;
	}
	i--;
	for (i; i >= 0; i--) {
		cout << "/" << cname[i];
		strcat_s(current_locate, "/");
		strcat_s(current_locate, cname[i]);
	}
	strcat_s(current_locate, "/");

}

//---------------·����λ�á���ӡ��ؽ���------------------------------------------------
//---------------��  ��  ��  ��----------------------------------------------------------
//���Һ���
/*
-name �����ֲ���  -find -name D:/�ҵĵ���/�������/ ���.ppt
-type �ļ����Ͳ���  -find -type D:/�ҵĵ���/�������/ source.cpp
*/
void Find(char arr[])
{

	char ch[100];    //������ʱ�洢���������
	Folder * find_located = NULL;
	memset(ch, 0, sizeof(ch));
	int t = 0, j = 0, way = 0;
	int blank = 0;  //�ո�ĸ���

	tem = 0;
	//�ж���ȫ�ֲ��һ��ǵ�ǰĿ¼����
	for (int i = 0; arr[i] != NULL; i++)
	{
		if (arr[i] == ' ') {
			blank++;
		}
	}
	//blank==2����ǰĿ¼�²���
	if (blank == 2) {
		//	find_located = Located(current_locate);
		find_located = current_ptr;
	}

	for (int i = 0; arr[i] != NULL; i++)
	{
		if (arr[i] != ' ')
		{
			ch[j] = arr[i];
			j++;
		}
		else
		{
			t++;
			//��������ĵ�һ�Σ��ж�ָ��

			if (t == 1)
			{
				if (strcmp(ch, "-find") != 0) {
					cout << "�����ָ������" << endl;
					tem = -1;
					return;
				}
			}
			//��������ĵڶ��Σ�ȷ�����ҷ�ʽ
			if (t == 2)
			{
				if (strcmp(ch, "-name") == 0) {
					way = 1;       //�����Ʋ���
				}
				else if (strcmp(ch, "-type") == 0) {
					way = 2;       //�����Ͳ���
				}
				else
				{
					cout << "����Ĳ��ҷ�ʽ��Ч��" << endl;
					tem = -1;
					return;
				}
			}
			//t=3,�жϵ������ַ���·��
			if (blank == 3 && t == 3)
			{
				if (strcmp(ch, "/") == 0) {
					strcpy_s(ch, 20, "D:/�ҵĵ���/");
				}
				find_located = Located(ch);

				if (find_located == NULL)
				{
					cout << "�����·��Ϊ��Ч·����" << endl;
					tem = -1;
					return;
				}
			}

			memset(ch, 0, sizeof(ch));
			j = 0;
		}
	}
	if (way == 1) {
		find_name(find_located, ch);
		memset(ch, 0, sizeof(ch));
	}
	if (way == 2) {
		find_type(find_located, ch);
		memset(ch, 0, sizeof(ch));
	}
}
//�������Ʋ���
File * find_name(Folder * ptr, char * contact)
{
	Folder * ptr1;
	File * ptr2;
	File * point = NULL;
	if (ptr == NULL) {
		return NULL;
	}
	else
	{
		ptr1 = ptr->in_folder;
		ptr2 = ptr->in_file;
	}


	//��ƥ�䵱ǰĿ¼�µ��ļ�
	for (; ptr2 != NULL; )
	{
		if (strcmp(contact, ptr2->name) == 0) {
			tem = 1;
			////�ҵ��˾ʹ�ӡ����Ϣ
			cout << "���� - " << ptr2->name << endl;
			cout << "��С - " << ptr2->fsize << endl;
			cout << "���� - " << ptr2->belong << endl;
			cout << "λ�� - " << ptr2->location << endl;
			cout << endl;
			//	return;
			point = ptr2;
		}
		ptr2 = ptr2->next;
	}
	//ƥ�䵱ǰĿ¼�µ��ļ���
	for (; ptr1 != NULL; )
	{
		if (strcmp(contact, ptr1->name) == 0) {
			tem = 1;
			////�ҵ��˾ʹ�ӡ����Ϣ
			cout << "���� - " << ptr1->name << endl;
			cout << "λ�� - " << ptr1->location << endl;
			//		cout << "�޸�ʱ�� - " << ptr1->time << endl;
			cout << endl;
		}
		if (ptr1->in_file != NULL || ptr1->in_folder != NULL)
		{
			find_name(ptr1, contact);
		}
		ptr1 = ptr1->next;
	}
	if (ptr1 == NULL&&ptr2 == NULL)
	{
		return point;
	}
}

//�������Բ���
void find_type(Folder * ptr, char contact[])
{
	Folder * ptr1;
	File * ptr2;
	//	File * point;
	if (ptr == NULL) {
		return;
	}
	else
	{
		ptr1 = ptr->in_folder;
		ptr2 = ptr->in_file;
	}

	//��ƥ�䵱ǰĿ¼�µ��ļ�
	for (; ptr2 != NULL; )
	{
		if (strcmp(contact, ptr2->belong) == 0) {
			tem = 1;
			////�ҵ��˾ʹ�ӡ����Ϣ
			cout << "���� - " << ptr2->name << endl;
			cout << "��С - " << ptr2->fsize << endl;
			cout << "���� - " << ptr2->belong << endl;
			cout << "λ�� - " << ptr2->location << endl;
			cout << endl;
		}
		ptr2 = ptr2->next;
	}
	//ƥ�䵱ǰĿ¼�µ��ļ���
	for (; ptr1 != NULL; )
	{
		if (ptr1->in_file != NULL || ptr1->in_folder != NULL)
		{
			find_type(ptr1, contact);
		}
		ptr1 = ptr1->next;
	}
	if (ptr1 == NULL&&ptr2 == NULL)
	{
		return;
	}
}

//---------------��  ��  ��  ��  ��  ��--------------------------------------------------

//---------------��  ��  ��  ��----------------------------------------------------------
//���ļ�����
/*ָ���ʽ��-open
����򿪵��ļ����֣�-open D:/�ҵĵ���/����ϵͳ/ 1.txt
����ǰĿ¼�£���-open ���.ppt
*/
void Open(char arr[])
{
	char ch[100], lo[100];    //������ʱ�洢���������
	Folder * find_located = NULL;
	memset(ch, 0, sizeof(ch));
	memset(lo, 0, sizeof(lo));
	int t = 0, j = 0, way = 0;
	int blank = 0;

	//�ж���ȫ�ִ򿪻��ǵ�ǰĿ¼��
	for (int i = 0; arr[i] != NULL; i++)
	{
		if (arr[i] == ' ') {
			blank++;
		}
	}

	if (blank == 1) {
		strcpy_s(lo,100, Located_change(current_locate));
	}

	for (int i = 0; arr[i] != NULL; i++)
	{
		if (arr[i] != ' ')
		{
			ch[j] = arr[i];
			j++;
		}
		else
		{
			t++;
			//��������ĵ�һ�Σ��ж�ָ��
			if (t == 1)
			{
				if (strcmp(ch, "-open") != 0) {
					cout << "�����ָ������" << endl;
					tem = -1;
					return;
				}
			}

			//t=2,�жϵڶ����ַ���·��
			if (t == 2 && blank == 2)
			{
				strcpy_s(lo,100,Located_change(ch));
			}
			//�ҵ��������ֵ��ļ�����
			memset(ch, 0, sizeof(ch));
			j = 0;
		}
	}

	Open_file(lo, ch);
}

//��ַ��ʽת������
char * Located_change(char source[])
{
	char c[100];
	int j = 0;
	memset(c, 0, sizeof(c));
	for (int i = 0; source[i + 1] != NULL; i++)
	{
		if (source[i] == '/')
		{
			c[j] = '\\';
			j++;

		}
		else
		{
			c[j] = source[i];
			j++;
		}
	}
	return c;
}

//���ļ��Ĳ�������
void Open_file(char locate[], char name[])
{
	HINSTANCE value;
	//��char * ת��ΪLPCWSTR
	WCHAR   wstr1[MAX_PATH] = { 0 };
	WCHAR   wstr2[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, locate, -1, wstr1, sizeof(wstr1));
	MultiByteToWideChar(CP_ACP, 0, name, -1, wstr2, sizeof(wstr2));

	/*���ļ��ĺ�������������Ϊ:
	hWnd: HWND; {ָ�������ھ��}
	Operation: PChar; {ָ������, Ʃ��: open��runas��print��edit��explore...}
	FileName: PChar; {ָ��Ҫ�򿪵��ļ������}
	Parameters: PChar; {��Ҫ�򿪵ĳ���ָ������; ����򿪵����ļ�����Ӧ���� null}
	Directory: PChar; {ȱʡĿ¼}
	ShowCmd: Integer {��ѡ��}
	*/
	//	cout << locate << endl;
	//	cout << name << endl;
	//	value = ShellExecute(NULL, _T("open"), _T("1.txt"), NULL, _T("D:/�ҵĵ���/����ϵͳ/"), SW_SHOWNORMAL);


//	value = ShellExecute(NULL, _T("open"), wstr2, NULL, wstr1, SW_SHOWNORMAL);

	if ((int)value == 0) { cout << "�ڴ治�㡣" << endl; }
	else if ((int)value == 2) { cout << "�ļ�������" << endl; }
	else if ((int)value == 3) { cout << "·��������" << endl; }
	else if ((int)value == 11) { cout << "EXE �ļ���Ч��" << endl; }
	else if ((int)value == 26) { cout << "�����������" << endl; }
	else if ((int)value == 27) { cout << "�ļ�������ȫ����Ч��" << endl; }
	else if ((int)value == 28) { cout << "��ʱ��" << endl; }
	else if ((int)value == 29) { cout << "DDE ����ʧ�ܡ�" << endl; }
	else if ((int)value == 30) { cout << "���ڴ������� DDE �����������ɸ� DDE ����" << endl; }
	else if ((int)value == 31) { cout << "û���������Ӧ�ó���" << endl; }
	else {
		cout << "ָ���ļ��Ѵ򿪡�" << endl;
	}
}

//---------------��  ��  ��  ��  ��  ��--------------------------------------------------


//---------------ģ  ��  ��  ��----------------------------------------------------------
void demo() {
	Folder * p1 = (struct Folder *)malloc(sizeof(struct Folder));
	p1->in_file = (struct File *)malloc(sizeof(struct File));
	p1->in_folder = (struct Folder *)malloc(sizeof(struct Folder));
	p1->next = (struct Folder *)malloc(sizeof(struct Folder));
	p1->return_to_pre = (struct Folder *)malloc(sizeof(struct Folder));

	Folder * p2 = (struct Folder *)malloc(sizeof(struct Folder));
	p2->in_file = (struct File *)malloc(sizeof(struct File));
	p2->in_folder = (struct Folder *)malloc(sizeof(struct Folder));
	p2->next = (struct Folder *)malloc(sizeof(struct Folder));
	p2->return_to_pre = (struct Folder *)malloc(sizeof(struct Folder));


	Folder * p3 = (struct Folder *)malloc(sizeof(struct Folder));
	p3->in_file = (struct File *)malloc(sizeof(struct File));
	p3->in_folder = (struct Folder *)malloc(sizeof(struct Folder));
	p3->next = (struct Folder *)malloc(sizeof(struct Folder));
	p3->return_to_pre = (struct Folder *)malloc(sizeof(struct Folder));

	File * f3 = (struct File *)malloc(sizeof(struct File));
	f3->next = (struct File *)malloc(sizeof(struct File));
	f3->piece = (struct File *)malloc(sizeof(struct File));
	f3->return_to_pre = (struct Folder *)malloc(sizeof(struct Folder));

	File * f1 = (struct File *)malloc(sizeof(struct File));
	f1->next = (struct File *)malloc(sizeof(struct File));
	f1->piece = (struct File *)malloc(sizeof(struct File));
	f1->return_to_pre = (struct Folder *)malloc(sizeof(struct Folder));

	File * f2 = (struct File *)malloc(sizeof(struct File));
	f2->next = (struct File *)malloc(sizeof(struct File));
	f2->piece = (struct File *)malloc(sizeof(struct File));
	f1->return_to_pre = (struct Folder *)malloc(sizeof(struct Folder));

	init_folder = (struct Folder *)malloc(sizeof(struct Folder));
	init_folder->in_file = (struct File *)malloc(sizeof(struct File));
	init_folder->in_folder = (struct Folder *)malloc(sizeof(struct Folder));
	init_folder->next = (struct Folder *)malloc(sizeof(struct Folder));
	init_folder->return_to_pre = (struct Folder *)malloc(sizeof(struct Folder));

	init_file = (struct File *)malloc(sizeof(struct File));
	init_file->next = (struct File *)malloc(sizeof(struct File));
	init_file->piece = (struct File *)malloc(sizeof(struct File));


	strcpy_s(init_folder->name, 20, "�ҵĵ���");
	init_folder->in_folder = p1;
	strcpy_s(init_folder->location, 50, "D:/�ҵĵ���/");   //λ��
	init_folder->return_to_pre = NULL;
	init_folder->next = NULL;
	init_folder->in_file = NULL;
	init_file = NULL;

	p1->return_to_pre = init_folder;
	strcpy_s(p1->name, 20, "����ϵͳ");   //����
	strcpy_s(p1->location, 50, Print_location(p1->return_to_pre));   //λ��
	p1->in_file = f1;
	p1->in_folder = NULL;

	strcpy_s(f1->name, 20, "�γ����.docx");  //����
	f1->fsize = 10;   //��С
	strcpy_s(f1->belong, 20, "docx");  //����
	f1->return_to_pre = p1;
	strcpy_s(f1->location, 50, Print_location(f1->return_to_pre));   //λ��
	f1->next = NULL;

	p1 = p1->next;
	p1->return_to_pre = init_folder;
	strcpy_s(p1->name, 20, "�������");   //����
	strcpy_s(p1->location, 50, Print_location(p1->return_to_pre));   //λ��
	p1->next = NULL;

	p1->in_file = f2;
	f2->return_to_pre = p1;
	strcpy_s(f2->name, 20, "�γ���ҵ.docx");   //����
	f2->fsize = 30;      //��С
	strcpy_s(f2->belong, 20, "docx");   //λ��
	strcpy_s(f2->location, 50, Print_location(f2->return_to_pre));   //λ��

	f2 = f2->next;
	f2->return_to_pre = p1;
	strcpy_s(f2->name, 20, "���.ppt");    //����
	f2->fsize = 15;      //��С
	strcpy_s(f2->belong, 20, "ppt");   //λ��
	strcpy_s(f2->location, 50, Print_location(f2->return_to_pre));   //λ��
	f2->next = NULL;

	p1->in_folder = p2;
	p2->return_to_pre = p1;
	strcpy_s(p2->name, 20, "ʵ���ļ�");    //����
	strcpy_s(p2->location, 50, Print_location(p2->return_to_pre));   //λ��
	p2->next = NULL;

	p3 = p2->in_folder;
	p3->return_to_pre = p2;
	strcpy_s(p3->name, 20, "ʵ���ļ�");   //����,�ļ���
	strcpy_s(p3->location, 50, Print_location(p3->return_to_pre));   //λ��
	p3->fsize = 0;
	p3->next = NULL;
	p3->in_folder = NULL;
	p3->in_file = NULL;

	f3 = p2->in_file;
	f3->return_to_pre = p2;
	strcpy_s(f3->name, 20, "source.cpp");  //����
	f3->fsize = 25;      //��С
	strcpy_s(f3->belong, 20, "cpp");   //λ��
	strcpy_s(f3->location, 50, Print_location(f3->return_to_pre));   //λ��
	f3->next = NULL;


	//---------WARNING------------
	Remain_M = Disk_M - INDEXSPACE;
	Available * p = new Available;
	init_available = new Available;
	p->start = INDEXSPACE;
	p->next = NULL;
	p->prev = init_available;
	p->length = Remain_M;
	init_available->start = -1;
	init_available->length = Remain_M;
	init_available->next = p;
	init_available->prev = NULL;


	//---------Andemund------------

	Fsize(init_folder);
	return;
}
//����ÿһ���ļ��еĴ�С
double Fsize(Folder * ptr)
{
	Folder * ptr1 = ptr->in_folder;
	File * ptr2 = ptr->in_file;
	double a = 0, b = 0;    //a���ļ��ģ�b���ļ��еĴ�С
	if (ptr1 == NULL) {
		b = 0;
	}
	if (ptr2 == NULL) {
		a = 0;
	}
	for (; ptr2 != NULL;) {
		a = a + ptr2->fsize;
		ptr2 = ptr2->next;
	}
	for (; ptr1 != NULL;)
	{
		b = b + Fsize(ptr1);
		ptr1 = ptr1->next;
	}
	ptr->fsize = a + b;
	//	cout << ptr->name << "	" << ptr->fsize << endl;
	return ptr->fsize;
}

//---------------ģ  ��  ��  ��  ��  ��--------------------------------------------------

//---------------��  ��  ��  ��----------------------------------------------------------
//�Ե�ǰĿ¼�µ��ļ��Լ��ļ��У����մ�С����
//ָ���ʽΪ��-order by size desc ; -order by size asc
void Order_by_size(char arr[])
{

	char ch[100];    //�����ֶδ洢�ַ�
	int j = 0, t = 0;
	for (int i = 0; arr[i] != NULL; i++)
	{
		if (arr[i] != ' ') {
			ch[j] = arr[i];
			j++;
		}

		else {
			t++;
			if (t == 1) {
				if (strcmp(ch, "-order") != 0) {
					cout << "�����ʽ����" << endl;
					return;
				}
			}
			if (t == 2) {
				if (strcmp(ch, "by") != 0) {
					cout << "�����ʽ����" << endl;
					return;
				}
			}
			if (t == 3) {
				if (strcmp(ch, "size") != 0) {
					cout << "�����ʽ����" << endl;
					return;
				}
			}
			memset(ch, 0, sizeof(ch));
			j = 0;
		}
	}
	//��������
	if (strcmp(ch, "desc") == 0) {
		Order(current_ptr, 1);
		return;
	}
	//��������
	if (strcmp(ch, "asc") == 0) {
		Order(current_ptr, 2);
		return;
	}
}

//op==1������op==2,����
void Order(Folder * ptr, int op)
{
	Folder * ptr1 = ptr->in_folder;
	File * ptr2 = ptr->in_file;
	double fsize[50];
	char fname[50][50];
	int i;
	char ch[50];
	double tem;

	for (i = 0; ptr1 != NULL; i++) {
		strcpy_s(fname[i], ptr1->name);
		fsize[i] = ptr1->fsize;
		ptr1 = ptr1->next;
	}
	for (i; ptr2 != NULL; i++) {
		strcpy_s(fname[i], ptr2->name);
		fsize[i] = ptr2->fsize;
		ptr2 = ptr2->next;
	}

	//ѡ������
	for (int m = 0; m < i; m++)
	{
		for (int k = 0; k < i; k++) {
			if (fsize[m] > fsize[k]) {
				tem = fsize[m];
				strcpy_s(ch, fname[m]);

				fsize[m] = fsize[k];
				fsize[k] = tem;
				memset(fname[m], 0, sizeof(fname[m]));
				strcpy_s(fname[m], fname[k]);
				memset(fname[k], 0, sizeof(fname[k]));
				strcpy_s(fname[k], ch);
			}
		}
	}
	//����
	if (op == 1) {
		//	cout << "����������������" << endl;
		cout << endl;
		for (int j = 0; j < i; j++)
		{
			cout << "	" << fsize[j] << "	" << fname[j] << "	" << current_locate << endl;
		}
	}
	//����
	else {
		//	cout << "����������������" << endl;
		cout << endl;
		for (i = i - 1; i >= 0; i--)
		{
			cout << "	" << fsize[i] << "	" << fname[i] << "	" << current_locate << endl;
		}
	}

}
//---------------��  ��  ��  ��  ��  ��--------------------------------------------------