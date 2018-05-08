/*操作系统文件部分
设置磁盘空间总大小MAX_SPACE：2048
块大小 2
块数 1024
文件存储算法：碎片最大
使用索引
操作系统开始工作时，将索引加载进入内存？
设置索引内容存储形式：
文件表现形式：结构体-名称-类型-创建时间-路径-大小-下一块指针/结束

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

	cout << "请选择磁盘空间分配方式：1-链接，2-索引，3-连续：" << endl;
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
		cout << "非法输入" << endl;
		return 0;
	}
	function();

	system("pause");
	return 0;
}

//功能函数
void function()
{
	char instruct[300];
	char ch[100];
	cin.clear();
	cin.sync();
	cout << "D:/我的电脑>";
	cin.clear();
	cin.sync();
	gets_s(instruct);


	while (true)
	{
		int j = 0;
		memset(ch, 0, sizeof(ch));
		for (int i = 0; instruct[i] != NULL; i++)
		{
			//ch[]存储输入的指令前缀
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
			cout << "	-cd		显示当前目录的名称或将其更改" << endl;
			cout << "	-check		查看所有目录结构" << endl;
			cout << "	-drop file	删除文件" << endl;
			cout << "	-drop folder	删除文件夹" << endl;
			cout << "	-find		查找" << endl;
			cout << "	-help		帮助" << endl;
			cout << "	-new file	创建文件" << endl;
			cout << "	-new folder	创建文件夹" << endl;
			cout << "	-open		打开文件" << endl;
			cout << "	-order		按照文件大小排序" << endl;
			cout << endl;
		}
		//显示当前目录名称
		else if (strcmp(ch, "cd") == 0)
		{
			cout << "D:";
			print_current_ptr(current_ptr);
			cout << endl;

		}
		//返回根目录
		else if (strcmp(ch, "cd \\") == 0)
		{
			current_ptr = init_folder;   //指向的是我的电脑

		}
		//查找操作
		else if (strcmp(ch, "-find") == 0)
		{
			Find(instruct);
			if (tem == 0)
			{
				cout << "没有与该查找条件匹配的文件或文件夹" << endl;
			}
		}
		//创建新文件
		else if (strcmp(ch, "-new file") == 0)
		{
			new_File();
		}
		//创建新文件夹
		else if (strcmp(ch, "-new folder") == 0)
		{
			//	new_Folder();
		}
		//删除文件夹
		else if (strcmp(ch, "-drop folder") == 0)
		{
			//	new_Folder();
		}
		//删除文件
		else if (strcmp(ch, "-drop file") == 0)
		{
			delete_File();
		}
		//打印当前目录
		else if (strcmp(ch, "-check") == 0)
		{
			tab = 0;
			Print(current_ptr, init_file);
		}
		//打开文件
		else if (strcmp(ch, "-open") == 0)
		{
			Open(instruct);
		}
		//返回上一层
		else if (strcmp(ch, "cd..") == 0)
		{
			//如果存在上一级，则返回上一级
			//如果不存在，则current_ptr不变
			if (current_ptr->return_to_pre != NULL) {
				current_ptr = current_ptr->return_to_pre;
			}
		}
		//当前目录下按照文件大小排序
		else if (strcmp(ch, "-order") == 0)
		{
			Order_by_size(instruct);
		}
		else
		{
			int p = 0, i = 0;   //判断标志

								//输入 cd 文件名 进入当前文件夹的判断
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
					//定位current_ptr当前指针
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
				cout << ch << " 不是内部或外部命令，也不是可运行的程序或批处理文件。" << endl;
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

//创建新文件
void new_File()
{
	//判断磁盘是否还有剩余空间
	//磁盘已满
	if (Remain_M <= 0)
	{
		cout << "Insufficient disk space." << endl;
		cout << "Operation failed." << endl;
		return;
	}

	//磁盘还有剩余空间
	File * newf;
	newf = get_file_info();

	
	//同文件夹内是否有同名文件存在
	if (already_exist(newf->return_to_pre, newf))
	{
		cout << "That file is already exist." << endl;
		cout << "Operation failed." << endl;
		return;
	}

	//文件大小大于剩余空间
	if (newf == NULL)
	{
		cout << "Insufficient disk space." << endl;
		cout << "Operation failed." << endl;
		return;
	}


	//物理地址逻辑地址
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
	//将文件加入对应文件夹下
	new_File_Index(newf);

	Remain_M = Remain_M - ceil(newf->fsize);
	show_current_block();
	cout << "当前剩余空间：" << Remain_M << endl;
	cout << "New file created." << endl;
	//Print(init_folder, init_file);
	return;
}


//------------------------通用部分 begin-----------------------------
//读取新建文件信息    check
File * get_file_info()
{
	File * temp = new File;
	cin.clear();
	cin.sync();
	cout << "新建文件路径：" << endl;
	cin >> temp->location;
	cin.clear();
	cin.sync();
	//调用相关修改文件夹索引的函数
	Folder * a = Located(temp->location);
	temp->return_to_pre = a;
	cout << a << endl;
	cout << "新建文件名称：";
	cin >> temp->name;
	cin.clear();
	cin.sync();
	cout << "新建文件类型：";
	cin >> temp->belong;
	cin.clear();
	cin.sync();
	cout << "新建文件大小：";
	cin >> temp->fsize;
	cin.clear();
	cin.sync();

	if (temp->fsize >= Remain_M)
	{
		return NULL;
	}

	//读取当前系统时间作为首次修改时间
	return temp;
}


//判断文件夹内是否已经有了同名文件    check
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


//修改文件所在的文件夹信息    check
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


//递归，改变一个文件的增减带来的所有上层文件夹的大小变化  check
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


//初始化磁盘空间，预留	check
void init_block_space()
{
	init_block = new Block;
	init_block->content = -1;
	init_block->next_no = 0;
	init_block->no = -1;
	block[0] = init_block;

	//预留空间
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

	//初始化无文件
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

	cout << "空闲块起始：" << empty_block_begin << endl;
	cout << "空闲块结束：" << empty_block_end << endl;
	return;
}


//矢量图的形式展示当前磁盘占用情况	check
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


//输入新建文件夹信息	check
void get_folder_info()
{
	Folder * temp = new Folder;
	char t[50];
	Folder * a;	//the last folder in the uplevel folder
	Folder * b;
	cout << "新建文件夹路径：" << endl;
	cin >> t;
	//调用相关修改文件夹索引的函数
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

	cout << "新建文件夹名称：";
	cin >> temp->name;
	cin.clear();
	cin.sync();

	return;
}

//删除文件
void delete_File()
{
	//call the function
	char p[50];
	char n[20];
	cout << "文件路径：" << endl;
	cin >> p;
	cin.clear();
	cin.sync();
	cout << "文件名：" << endl;
	cin >> n;
	//调用相关修改文件夹索引的函数
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

	//修改文件夹
	delete_File_Index(deletef);

	Remain_M = Remain_M + ceil(deletef->fsize);
	show_current_block();
	cout << "当前剩余空间：" << Remain_M << endl;
	cout << "File dropped." << endl;
}


//删除文件后修改相关文件夹结构
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


//------------------------通用部分 end-----------------------------



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



//--------------------------碎片最大化 begin------------------------------------
//when file size > current maxpiece, split the file
void split_file_link(File * newf, Available * maxpiece)
{
	//有整块的剩余空间可以存放文件
	if (maxpiece->length >= ceil(newf->fsize))
	{
		newf->phy_loc = maxpiece->start;
		newf->next = NULL;
		newf->piece = NULL;
		maxpiece->start = maxpiece->start + ceil(newf->fsize);
		maxpiece->length = maxpiece->length - ceil(newf->fsize);

		//实际分配物理空间
		//allocate(newf);

		//重新排序剩余空间链表
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
	//剩余完整空间不足
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

//找到当前最大碎片
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

//--------------------------碎片最大化 end------------------------------------



//--------------------------链接方式 begin--------------------------------------
//连接方式下分配物理空间	check
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

//链接方式下删除文件时恢复对应的物理块	check
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

//--------------------------链接方式 end--------------------------------------

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

//--------------------------索引方式 begin--------------------------------------
//索引方式下分配物理空间	check
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


//索引方式下删除文件时恢复对应的物理块	check
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

//--------------------------索引方式 end--------------------------------------


//--------------------------顺序方式 begin--------------------------------------
//顺序方式下分配物理空间
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



//--------------------------顺序方式 end--------------------------------------



//* ********** * 
//*     YDY    *
//* ********** *

//---------------路径、位置、打印相关----------------------------------------------------
//查找路径函数
Folder * Located(char position[])
{
	int i = 0, j = 0, level = -1;   //level表示第几级目录，0则为根目录
	char root[30];
	memset(root, 0, sizeof(root));
	Folder * ptr;   //临时查找指针

	ptr = init_folder;    //令ptr指向根目录下的第一个文件夹
	for (i = 0, j = 0; position[i] != NULL; i++)
	{
		if (position[i] == '/')
		{
			//判断磁盘
			if (level == -1) {
				if (strcmp(root, "D:") != 0)
				{
					break;
				}
			}
			//判断根目录是否正确
			else if (level == 0) {
				if (strcmp(root, "我的电脑") != 0) {
					return NULL;
				}
				ptr = ptr->in_folder;
			}
			//判断输入的文件夹目录是否正确
			else
			{
				for (; (strcmp(ptr->name, root) != 0) && (ptr->next != NULL); )
				{
					ptr = ptr->next;  //匹配文件夹的名字，不相等，则指向同目录的下一个
				}
				//找到该文件夹
				if (strcmp(ptr->name, root) == 0)
				{
					//cout << level << "级目录为 ：" << root << endl;
					ptr = ptr->in_folder;
				}
				else {
					//cout << "没有找到【" << root << "】目录，请检查输入路径是否正确！" << endl;
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


//打印当前文件目录结构，嵌套打印
void Print(Folder * p1, File * p2)
{
	Folder * ptr1;
	File * ptr2;
	int m;

	//目录下的文件夹不为空
	for (; p1 != NULL;)
	{
		for (m = 0; m < tab; m++)
		{
			cout << "	";        //一个缩进
		}
		cout << p1->name << endl;      //打印当前文件夹的名字

									   //指向该文件夹里面的子文件
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
				cout << "	";        //一个缩进
			}
			//打印文件夹里子文件的文件名
			cout << ptr2->name << endl;
			ptr2 = ptr2->next;
		}
		//打印文件夹里子文件夹，需要调用递归算法
		if (ptr1 != NULL)
		{
			Print(ptr1, ptr2);
		}
		//打印根目录下的兄弟文件
		tab--;
		if (p1 != current_ptr) {
			p1 = p1->next;
		}
		else {
			break;
		}

	}


	//根目录下的文件不为空
	for (; p2 != NULL;)
	{
		for (int m = 0; m < tab; m++)
		{
			cout << "	";        //一个缩进
		}
		cout << p2->name << endl;
		p2 = p2->next;
	}

	if (p1 == NULL && p2 == NULL)
	{
		return;
	}
}

//返回位置的函数
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
	strcat_s(way2, "D:/我的电脑/");
	for (i, j; i >= 0; i--, j++)
	{
		strcat_s(way2, way[i]);
		strcat_s(way2, "/");
	}
	return way2;
}

//打印到当前指针的函数
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

//---------------路径、位置、打印相关结束------------------------------------------------
//---------------查  找  函  数----------------------------------------------------------
//查找函数
/*
-name 按名字查找  -find -name D:/我的电脑/软件工程/ 设计.ppt
-type 文件类型查找  -find -type D:/我的电脑/软件工程/ source.cpp
*/
void Find(char arr[])
{

	char ch[100];    //用来临时存储读入的内容
	Folder * find_located = NULL;
	memset(ch, 0, sizeof(ch));
	int t = 0, j = 0, way = 0;
	int blank = 0;  //空格的个数

	tem = 0;
	//判断是全局查找还是当前目录查找
	for (int i = 0; arr[i] != NULL; i++)
	{
		if (arr[i] == ' ') {
			blank++;
		}
	}
	//blank==2，当前目录下查找
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
			//分析输入的第一段，判断指令

			if (t == 1)
			{
				if (strcmp(ch, "-find") != 0) {
					cout << "输入的指令有误。" << endl;
					tem = -1;
					return;
				}
			}
			//分析输入的第二段，确定查找方式
			if (t == 2)
			{
				if (strcmp(ch, "-name") == 0) {
					way = 1;       //按名称查找
				}
				else if (strcmp(ch, "-type") == 0) {
					way = 2;       //按类型查找
				}
				else
				{
					cout << "输入的查找方式无效。" << endl;
					tem = -1;
					return;
				}
			}
			//t=3,判断第三段字符的路径
			if (blank == 3 && t == 3)
			{
				if (strcmp(ch, "/") == 0) {
					strcpy_s(ch, 20, "D:/我的电脑/");
				}
				find_located = Located(ch);

				if (find_located == NULL)
				{
					cout << "输入的路径为无效路径。" << endl;
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
//按照名称查找
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


	//先匹配当前目录下的文件
	for (; ptr2 != NULL; )
	{
		if (strcmp(contact, ptr2->name) == 0) {
			tem = 1;
			////找到了就打印其信息
			cout << "名称 - " << ptr2->name << endl;
			cout << "大小 - " << ptr2->fsize << endl;
			cout << "属性 - " << ptr2->belong << endl;
			cout << "位置 - " << ptr2->location << endl;
			cout << endl;
			//	return;
			point = ptr2;
		}
		ptr2 = ptr2->next;
	}
	//匹配当前目录下的文件夹
	for (; ptr1 != NULL; )
	{
		if (strcmp(contact, ptr1->name) == 0) {
			tem = 1;
			////找到了就打印其信息
			cout << "名称 - " << ptr1->name << endl;
			cout << "位置 - " << ptr1->location << endl;
			//		cout << "修改时间 - " << ptr1->time << endl;
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

//按照属性查找
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

	//先匹配当前目录下的文件
	for (; ptr2 != NULL; )
	{
		if (strcmp(contact, ptr2->belong) == 0) {
			tem = 1;
			////找到了就打印其信息
			cout << "名称 - " << ptr2->name << endl;
			cout << "大小 - " << ptr2->fsize << endl;
			cout << "属性 - " << ptr2->belong << endl;
			cout << "位置 - " << ptr2->location << endl;
			cout << endl;
		}
		ptr2 = ptr2->next;
	}
	//匹配当前目录下的文件夹
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

//---------------查  找  函  数  结  束--------------------------------------------------

//---------------打  开  函  数----------------------------------------------------------
//打开文件内容
/*指令格式：-open
输入打开的文件名字：-open D:/我的电脑/操作系统/ 1.txt
若当前目录下，则：-open 设计.ppt
*/
void Open(char arr[])
{
	char ch[100], lo[100];    //用来临时存储读入的内容
	Folder * find_located = NULL;
	memset(ch, 0, sizeof(ch));
	memset(lo, 0, sizeof(lo));
	int t = 0, j = 0, way = 0;
	int blank = 0;

	//判断是全局打开还是当前目录打开
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
			//分析输入的第一段，判断指令
			if (t == 1)
			{
				if (strcmp(ch, "-open") != 0) {
					cout << "输入的指令有误。" << endl;
					tem = -1;
					return;
				}
			}

			//t=2,判断第二段字符的路径
			if (t == 2 && blank == 2)
			{
				strcpy_s(lo,100,Located_change(ch));
			}
			//找到输入名字的文件并打开
			memset(ch, 0, sizeof(ch));
			j = 0;
		}
	}

	Open_file(lo, ch);
}

//地址格式转换函数
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

//打开文件的操作函数
void Open_file(char locate[], char name[])
{
	HINSTANCE value;
	//将char * 转化为LPCWSTR
	WCHAR   wstr1[MAX_PATH] = { 0 };
	WCHAR   wstr2[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, locate, -1, wstr1, sizeof(wstr1));
	MultiByteToWideChar(CP_ACP, 0, name, -1, wstr2, sizeof(wstr2));

	/*打开文件的函数，参数依次为:
	hWnd: HWND; {指定父窗口句柄}
	Operation: PChar; {指定动作, 譬如: open、runas、print、edit、explore...}
	FileName: PChar; {指定要打开的文件或程序}
	Parameters: PChar; {给要打开的程序指定参数; 如果打开的是文件这里应该是 null}
	Directory: PChar; {缺省目录}
	ShowCmd: Integer {打开选项}
	*/
	//	cout << locate << endl;
	//	cout << name << endl;
	//	value = ShellExecute(NULL, _T("open"), _T("1.txt"), NULL, _T("D:/我的电脑/操作系统/"), SW_SHOWNORMAL);


//	value = ShellExecute(NULL, _T("open"), wstr2, NULL, wstr1, SW_SHOWNORMAL);

	if ((int)value == 0) { cout << "内存不足。" << endl; }
	else if ((int)value == 2) { cout << "文件名错误。" << endl; }
	else if ((int)value == 3) { cout << "路径名错误。" << endl; }
	else if ((int)value == 11) { cout << "EXE 文件无效。" << endl; }
	else if ((int)value == 26) { cout << "发生共享错误。" << endl; }
	else if ((int)value == 27) { cout << "文件名不完全或无效。" << endl; }
	else if ((int)value == 28) { cout << "超时。" << endl; }
	else if ((int)value == 29) { cout << "DDE 事务失败。" << endl; }
	else if ((int)value == 30) { cout << "正在处理其他 DDE 事务而不能完成该 DDE 事务。" << endl; }
	else if ((int)value == 31) { cout << "没有相关联的应用程序。" << endl; }
	else {
		cout << "指定文件已打开。" << endl;
	}
}

//---------------打  开  函  数  结  束--------------------------------------------------


//---------------模  拟  文  件----------------------------------------------------------
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


	strcpy_s(init_folder->name, 20, "我的电脑");
	init_folder->in_folder = p1;
	strcpy_s(init_folder->location, 50, "D:/我的电脑/");   //位置
	init_folder->return_to_pre = NULL;
	init_folder->next = NULL;
	init_folder->in_file = NULL;
	init_file = NULL;

	p1->return_to_pre = init_folder;
	strcpy_s(p1->name, 20, "操作系统");   //名称
	strcpy_s(p1->location, 50, Print_location(p1->return_to_pre));   //位置
	p1->in_file = f1;
	p1->in_folder = NULL;

	strcpy_s(f1->name, 20, "课程设计.docx");  //名称
	f1->fsize = 10;   //大小
	strcpy_s(f1->belong, 20, "docx");  //属性
	f1->return_to_pre = p1;
	strcpy_s(f1->location, 50, Print_location(f1->return_to_pre));   //位置
	f1->next = NULL;

	p1 = p1->next;
	p1->return_to_pre = init_folder;
	strcpy_s(p1->name, 20, "软件工程");   //名称
	strcpy_s(p1->location, 50, Print_location(p1->return_to_pre));   //位置
	p1->next = NULL;

	p1->in_file = f2;
	f2->return_to_pre = p1;
	strcpy_s(f2->name, 20, "课程作业.docx");   //名称
	f2->fsize = 30;      //大小
	strcpy_s(f2->belong, 20, "docx");   //位置
	strcpy_s(f2->location, 50, Print_location(f2->return_to_pre));   //位置

	f2 = f2->next;
	f2->return_to_pre = p1;
	strcpy_s(f2->name, 20, "设计.ppt");    //名称
	f2->fsize = 15;      //大小
	strcpy_s(f2->belong, 20, "ppt");   //位置
	strcpy_s(f2->location, 50, Print_location(f2->return_to_pre));   //位置
	f2->next = NULL;

	p1->in_folder = p2;
	p2->return_to_pre = p1;
	strcpy_s(p2->name, 20, "实验文件");    //名称
	strcpy_s(p2->location, 50, Print_location(p2->return_to_pre));   //位置
	p2->next = NULL;

	p3 = p2->in_folder;
	p3->return_to_pre = p2;
	strcpy_s(p3->name, 20, "实验文件");   //名称,文件夹
	strcpy_s(p3->location, 50, Print_location(p3->return_to_pre));   //位置
	p3->fsize = 0;
	p3->next = NULL;
	p3->in_folder = NULL;
	p3->in_file = NULL;

	f3 = p2->in_file;
	f3->return_to_pre = p2;
	strcpy_s(f3->name, 20, "source.cpp");  //名称
	f3->fsize = 25;      //大小
	strcpy_s(f3->belong, 20, "cpp");   //位置
	strcpy_s(f3->location, 50, Print_location(f3->return_to_pre));   //位置
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
//计算每一个文件夹的大小
double Fsize(Folder * ptr)
{
	Folder * ptr1 = ptr->in_folder;
	File * ptr2 = ptr->in_file;
	double a = 0, b = 0;    //a存文件的，b存文件夹的大小
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

//---------------模  拟  文  件  结  束--------------------------------------------------

//---------------排  序  函  数----------------------------------------------------------
//对当前目录下的文件以及文件夹，按照大小排序
//指令格式为：-order by size desc ; -order by size asc
void Order_by_size(char arr[])
{

	char ch[100];    //用来分段存储字符
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
					cout << "命令格式错误。" << endl;
					return;
				}
			}
			if (t == 2) {
				if (strcmp(ch, "by") != 0) {
					cout << "命令格式错误。" << endl;
					return;
				}
			}
			if (t == 3) {
				if (strcmp(ch, "size") != 0) {
					cout << "命令格式错误。" << endl;
					return;
				}
			}
			memset(ch, 0, sizeof(ch));
			j = 0;
		}
	}
	//降序排列
	if (strcmp(ch, "desc") == 0) {
		Order(current_ptr, 1);
		return;
	}
	//升序排列
	if (strcmp(ch, "asc") == 0) {
		Order(current_ptr, 2);
		return;
	}
}

//op==1，降序；op==2,升序
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

	//选择排序
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
	//降序
	if (op == 1) {
		//	cout << "降序排列输入结果：" << endl;
		cout << endl;
		for (int j = 0; j < i; j++)
		{
			cout << "	" << fsize[j] << "	" << fname[j] << "	" << current_locate << endl;
		}
	}
	//升序
	else {
		//	cout << "升序排列输入结果：" << endl;
		cout << endl;
		for (i = i - 1; i >= 0; i--)
		{
			cout << "	" << fsize[i] << "	" << fname[i] << "	" << current_locate << endl;
		}
	}

}
//---------------排  序  函  数  结  束--------------------------------------------------