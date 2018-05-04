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
using namespace std;


//functions
Available * find_disk_space();
void new_File();
//void init_diskpart();
File * get_file_info();
void new_File_Index(File *);
Folder * get_folder_info();
bool already_exist(Folder *, File *);
void allocate(File *);
void split_file_link(File *, Available *);
void change_prev_folder_size(Folder *, const char *, File *);
Folder * Located(char position[]);
void demo();
void Print(Folder * p1, File * p2);
void show_disk_usage();

void init_block_space();
void show_current_block();
void allocate_block(File * );
void delete_block(File * );
void delete_File();

File * find_name(Folder * ptr, char contact[]);
void find_type(Folder * ptr, char contact[]);
void Find();
void function();
char * Print_location(Folder * ptr);



int main()
{
	Folder * ptr1;
	File * ptr2;

	demo();
	ptr1 = init_folder;
	ptr2 = init_file;

	//***- - -���Բ���·�� D:/�ҵĵ���/�������/ʵ���ļ�/
	char sentence[50];
	Folder * monument;  //���Ե�ǰָ��
	cout << "����Ĳ���·��Ϊ��D:/�ҵĵ���/�������/ʵ���ļ�/" << endl;
	cout << "���ҽ�����£�" << endl;
	strcpy_s(sentence, sizeof("D:/�ҵĵ���/�������/ʵ���ļ�/"), "D:/�ҵĵ���/�������/ʵ���ļ�/");
	monument = Located(sentence);
	cout << endl;
	cout << "��ǰָ��ָ����ǣ�" << monument->name << endl;
	//***- - - ���Բ���·������
	/*
	cout << "******************************************************" << endl;
	cout << "	��ǰ���е�Ŀ¼�ṹ��Ĭ�ϣ�D:/�ҵĵ���/��" << endl;
	cout << "******************************************************" << endl;
	Print(ptr1, ptr2);                 //��ӡ��ǰ��Ŀ¼�ṹ
	cout << "******************************************************" << endl;

	//***- - -���Բ���·�� D:/�ҵĵ���/�������/ʵ���ļ�/
	char sentence[50];
	Folder * monument;  //���Ե�ǰָ��
	cout << "����Ĳ���·��Ϊ��D:/�ҵĵ���/�������/ʵ���ļ�/" << endl;
	cout << "���ҽ�����£�" << endl;
	strcpy_s(sentence, sizeof("D:/�ҵĵ���/�������/ʵ���ļ�/"), "D:/�ҵĵ���/�������/ʵ���ļ�/");
	monument = Located(sentence);
	cout << endl;
	cout << "��ǰָ��ָ����ǣ�" << monument->name << endl;
	//***- - - ���Բ���·������
	*/
	cout << "Please select disk space allocation method:1-Link organization, 2-Index organization:" << endl;
	cin >> org_method;
	getchar();
	cin.clear();
	cin.sync();
	function();

	system("pause");
	return 0;
}

//���ܺ���
void function()
{
	char ch[100];
	cin.clear();
	cin.sync();
	cout << "D:/�ҵĵ��� >";
	cin.clear();
	cin.sync();
	gets_s(ch);
	while (true)
	{
		if (strcmp(ch, "-help") == 0)
		{
			cout << endl;
			cout << "	-find		����" << endl;
			cout << "	-new file	�����ļ�" << endl;
			cout << "	-new folder	�����ļ���" << endl;
			cout << "	-drop folder	ɾ���ļ���" << endl;
			cout << "	-drop file	ɾ���ļ�" << endl;
			cout << "	-check		�鿴����Ŀ¼�ṹ" << endl;
			cout << "	-help		����";
			cout << endl;
		}
		else if (strcmp(ch, "-find") == 0)
		{
			Find();
			if (tem == 0)
			{
				cout << "û����ò�������ƥ����ļ����ļ���" << endl;
			}
		}
		else if (strcmp(ch, "-new file") == 0)
		{
			new_File();
		}
		else if (strcmp(ch, "-new folder") == 0)
		{
			//	new_Folder();
		}
		else if (strcmp(ch, "-drop folder") == 0)
		{
			//	new_Folder();
		}
		else if (strcmp(ch, "-drop file") == 0)
		{
			delete_File();
		}
		else if (strcmp(ch, "-check") == 0)
		{
			Print(init_folder, init_file);
		}
		else
		{
			cout << ch << " �����ڲ����ⲿ���Ҳ���ǿ����еĳ�����������ļ���" << endl;
		}
		cout << endl;
		memset(ch, 0, sizeof(ch));
		cout << "D:/�ҵĵ��� >";
		cin.clear();
		cin.sync();
		//getchar();
		gets_s(ch);
	}

}


void delete_File()
{
	//call the function
	char p[50];
	char n[20];
		
	cin.clear();
	cin.sync(); 
	cout << "Please input the path of file you want to delete:" << endl;
	cin >> p;
	cin.clear();
	cin.sync();
	cout << "Please input the name of file you want to delete:" << endl;
	cin >> n;
	//��������޸��ļ��������ĺ���
	Folder * a = Located(p);
	File * deletef = find_name(a,n);


	if (org_method == 1)//link
	{
		
		Remain_M = Remain_M + ceil(deletef->fsize);
		show_disk_usage();
	}
	else if (org_method == 2)//index
	{
		
		show_current_block();
	}
	else
	{
		cout << "Managing method is not exist." << endl;
		cout << "Operation failed." << endl;
		return;
	}
}




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
	while (already_exist(newf->return_to_pre, newf))
	{
		cout << "That file is already exist." << endl;
		cout << "Operation failed." << endl;
		newf = get_file_info();
		//enter what to exit?
	}

	//�ļ���С����ʣ��ռ�
	if (newf == NULL)
	{
		cout << "Insufficient disk space." << endl;
		cout << "Operation failed." << endl;
		return;
	}
	//ʣ��ռ���Դ�Ÿ��ļ�
	//add the information into the index
	//find the physical space

	
	if (org_method == 1)//link
	{
		Available * maxpiece = find_disk_space();
		if (maxpiece != NULL)
		{
			new_File_Index(newf);
			split_file_link(newf, maxpiece);
		}
		else
		{
			cout << "Operation failed." << endl;
			return;
		}
		Remain_M = Remain_M - ceil(newf->fsize);
		show_disk_usage();
	}
	else if (org_method == 2)//index
	{
		init_block_space();
		allocate_block(newf);
		new_File_Index(newf);
		show_current_block();
	}
	else
	{
		cout << "allocating method is not exist." << endl;
		cout << "Operation failed." << endl;
		return;
	}

	cout << "New file created." << endl;
	//Print(init_folder, init_file);
	return;
}


//show current disk usage
void show_disk_usage()
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



//---------------for link method----------------------------------------------------------
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

//get information of the new file


void allocate(File * f)
{
	int i = 0;
	for (i = 0; i < ceil(f->fsize); i++)
	{
		//1 means allcoated to one file
		disk_block[f->phy_loc + i] = 1;
	}
	return;
}

void delete_File_Index(File * f)
{
	Folder * a = f->return_to_pre;
	if (a->in_file == f)
	{
		a->in_file = f->next;
	}
	else
	{
		File * b=a->in_file->next;
		File * c = a->in_file;
		while (b != f)
		{
			b = b->next;
			c = c->next;
		}
		c->next = b->next;
	}
	change_prev_folder_size(f->return_to_pre, "-", f);
	return;
}

void delete_link(File * f)
{
	change_prev_folder_size(f->return_to_pre, "-", f);

	return;
}

//-----------------------------------------------------------------------------------------


File * get_file_info()
{
	File * temp = new File;
	cin.clear();
	cin.sync();
	cout << "Please input the file path:" << endl;
	cin >> temp->location;
	cin.clear();
	cin.sync();
	//��������޸��ļ��������ĺ���
	Folder * a = Located(temp->location);
	temp->return_to_pre = a;
	cout << "Please input the name of the new file:";
	cin >> temp->name;
	cin.clear();
	cin.sync();
	cout << "Please input the type of the file:";
	cin >> temp->belong;
	cin.clear();
	cin.sync();
	cout << "Please input the size of the file:";
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
		allocate(newf);

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


//add the information about the new file to the index
void new_File_Index(File * f)
{
	//call the fuction to get the path
	Folder * a = f->return_to_pre;	//current folder
	File * b = a->in_file;	//last file in this folder
	if (b == NULL)
	{
		a->in_file = f;
	}
	else
	{
		b->next = f;
	}
	change_prev_folder_size(a, "+", f);
	return;
}



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

//---------------for index method----------------------------------------------------------
//init the disk space
void init_block_space()
{
	init_block = new Block;
	init_block->content = -1;
	init_block->next_no = 0;
	init_block->no = -1;
	block[0] = init_block;

	for (int i = 1; i <= INDEXSPACE/BLOCKSIZE; i++)
	{
		block[i] = new Block;
		block[i]->content = 2;
		block[i]->no = i;
		block[i]->next_no = i+1;
	}


	for (int i = INDEXSPACE / BLOCKSIZE + 1; i <= BLOCKNUM; i++)
	{
		block[i] = new Block;
		block[i]->content = 0;
		block[i]->no = i;
		block[i]->next_no = i+1;
	}
	return;
}

void show_current_block()
{
	for (int i = 0; i < BLOCKNUM; i++)
	{
		cout << block[i]->content << " ";
		if (i % 16 == 15)
		{
			cout << endl;
		}
	}
	return;
}

void allocate_block(File * f)
{
	f->phy_loc = block[INDEXSPACE / BLOCKSIZE]->next_no;
	Block * b = block[block[INDEXSPACE / BLOCKSIZE]->next_no];
	for (int i = 0; i < ceil(f->fsize/BLOCKSIZE); i++)
	{
		b->content = 1;
		block[INDEXSPACE / BLOCKSIZE]->next_no = b->next_no;
		b = block[block[INDEXSPACE / BLOCKSIZE]->next_no];
	}
	b->next_no = -1;
	return;
}

void delete_block(File * f) 
{
	Block * b = block[f->phy_loc];
	Block * t = b;
	for (; t->next_no != -1; )
	{
		t = block[b->next_no];
		b->content = 0;
		b->next_no = block[INDEXSPACE / BLOCKSIZE]->next_no;
		block[INDEXSPACE / BLOCKSIZE]->next_no = b->no;
		b = t;
	}
	show_current_block();
	return;
}




//-----------------------------------------------------------------------------------------

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
	init_folder->return_to_pre = NULL;
	init_folder->next = NULL;
	init_folder->in_file = NULL;
	init_file = NULL;

	p1->return_to_pre = init_folder;
	strcpy_s(p1->name, 20, "����ϵͳ");   //����
	strcpy_s(p1->location, 50, Print_location(p1->return_to_pre));   //λ��
	p1->in_file = f1;
	p1->in_folder = NULL;

	strcpy_s(f1->name, 20, "�γ����.word");  //����
	f1->fsize = 10;   //��С
	strcpy_s(f1->belong, 20, "word");  //����
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
	strcpy_s(f2->name, 20, "�γ���ҵ.word");   //����
	f2->fsize = 30;      //��С
	strcpy_s(f2->belong, 20, "word");   //λ��
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
	strcpy_s(p3->name, 20, "ʵ���ļ�");   //����
	strcpy_s(p3->location, 50, Print_location(p3->return_to_pre));   //λ��
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

	//add the init info to the index

	
	//---------Andemund------------
	return;
}


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
					break;
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
		p1 = p1->next;
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


//************ warning  �ڶ��δ��벹�� *****************
/*
-name �����ֲ���  find -name D:/�ҵĵ���/�������/ ppt
-type �ļ����Ͳ���  find -type D:/�ҵĵ���/�������/ txt
*/

//�������Ʋ���
File * find_name(Folder * ptr, char * contact)
{
	Folder * ptr1;
	File * ptr2;
	File * point=NULL;
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

//�������Ͳ���
void find_type(Folder * ptr, char contact[])
{

}
//��ӡλ�õĺ���
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

//���Һ���
void Find()
{

	char ch[100];    //������ʱ�洢���������
	Folder * find_located = NULL;
	memset(ch, 0, sizeof(ch));
	int t = 0, j = 0, way = 0;
	char arr[100];     //�н�����Ĳ�������
	cout << "Please input the way you want to find:";
	gets_s(arr);
	tem = 0;
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
			if (t == 3)
			{
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



/*------------after mid-term----------------*/


//�����½��ļ�����Ϣ
Folder * get_folder_info()
{
	Folder * temp = new Folder;
	Folder * a;	//the last folder in the uplevel folder
	cout << "Please input the location of the new folder:" << endl;
	cin >> temp->location;
	//��������޸��ļ��������ĺ���

	a->next = temp;
	temp->fsize = 0;
	temp->next = NULL;
	temp->return_to_pre = a;
	temp->in_file = NULL;
	temp->in_folder = NULL;
	//temp->time = ;	//current system time

	cout << "Please input the name of the new folder:";
	cin >> temp->name;

	cout << "successed" << endl;

	return temp;
}


void Modify_File(File * f)
{
	cout << "1-modify the location,2-modify the infomation" << endl;
	string choice = 0;
	cin >> choice;
	File * t1,t3;
	Folder * t2;

	if (choice == "1")
	{
		t2 = f->return_to_pre;
		t1 = t2->in_file;
		for (t3 = t1->next; t3 != NULL; )
		{
			if (t3 == f)
			{
				t1->next = f->next;
				t2->fsize = t2->fsize - f->fsize;
				break;
			}
			t1 = t3;
			t3 = t1->next;
		}
		cout << "Please input the new location of the file:" << endl;
		cin >> f->location;
		//Find t2
		f->next = t2->in_file;
		t2->in_file = f;
		t2->fsize = t2->fsize + f->fsize;
		cout << "succssed." << endl;

	}
	else
	{
		if (choice == "2")
		{
			string a;
			cout << "Please input the new information of the file (.for not change):" << endl;
			cout << "File name:" << endl;
			cin >> a;
			if (a != ".")
			{
				strcpy(f->name, 20, a);
			}
			cout << "File size:" << endl;
			cin >> a;
			if (a != ".")
			{
				f->fsize = double(a);
			}
			cout << "File type:" << endl;
			cin >> a;
			if (a != ".")
			{
				strcpy(f->belong, 20, a);
			}
			cout << "succssed." << endl;
		}
		else
		{
			cout << "Invalid input. Operation failed." << endl;
		}
	}
	return;
}


void Modify_Folder(Folder * f)
{
	cout << "1-modify the location,2-modify the infomation" << endl;
	string choice = 0;
	cin >> choice;
	Folder t1 = f->return_to_pre;
	Folder t2 = t1->in_folder;
	if (choice == "1")
	{
		if (t2 == f)
		{
			t1->in_folder = f->next;

		}
		else
		{
			for (; t2->next != NULL; t2 = t2->next)
			{
				if (t2->next == f)
				{
					t1->fsize = t1->fsize - f->fsize;
					t2->next = f->next;
					break;
				}
			}
		}
		cout << "succssed." << endl;

	}
	else
	{
		if (choice == "2")
		{
			string a;
			cout << "Please input the new name of the file (.for not change):" << endl;
			cout << "File name:" << endl;
			cin >> a;
			if (a != ".")
			{
				strcpy(f->name, 20, a);
			}
			cout << "succssed." << endl;
		}
		else
		{
			cout << "Invalid input. Operation failed." << endl;
		}
	}
	return;
}



/*------------------------------------------*/