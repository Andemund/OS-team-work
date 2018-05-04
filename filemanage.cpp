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

	//***- - -测试查找路径 D:/我的电脑/软件工程/实验文件/
	char sentence[50];
	Folder * monument;  //测试当前指针
	cout << "输入的查找路径为：D:/我的电脑/软件工程/实验文件/" << endl;
	cout << "查找结果如下：" << endl;
	strcpy_s(sentence, sizeof("D:/我的电脑/软件工程/实验文件/"), "D:/我的电脑/软件工程/实验文件/");
	monument = Located(sentence);
	cout << endl;
	cout << "当前指针指向的是：" << monument->name << endl;
	//***- - - 测试查找路径结束
	/*
	cout << "******************************************************" << endl;
	cout << "	当前所有的目录结构（默认：D:/我的电脑/）" << endl;
	cout << "******************************************************" << endl;
	Print(ptr1, ptr2);                 //打印当前的目录结构
	cout << "******************************************************" << endl;

	//***- - -测试查找路径 D:/我的电脑/软件工程/实验文件/
	char sentence[50];
	Folder * monument;  //测试当前指针
	cout << "输入的查找路径为：D:/我的电脑/软件工程/实验文件/" << endl;
	cout << "查找结果如下：" << endl;
	strcpy_s(sentence, sizeof("D:/我的电脑/软件工程/实验文件/"), "D:/我的电脑/软件工程/实验文件/");
	monument = Located(sentence);
	cout << endl;
	cout << "当前指针指向的是：" << monument->name << endl;
	//***- - - 测试查找路径结束
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

//功能函数
void function()
{
	char ch[100];
	cin.clear();
	cin.sync();
	cout << "D:/我的电脑 >";
	cin.clear();
	cin.sync();
	gets_s(ch);
	while (true)
	{
		if (strcmp(ch, "-help") == 0)
		{
			cout << endl;
			cout << "	-find		查找" << endl;
			cout << "	-new file	创建文件" << endl;
			cout << "	-new folder	创建文件夹" << endl;
			cout << "	-drop folder	删除文件夹" << endl;
			cout << "	-drop file	删除文件" << endl;
			cout << "	-check		查看所有目录结构" << endl;
			cout << "	-help		帮助";
			cout << endl;
		}
		else if (strcmp(ch, "-find") == 0)
		{
			Find();
			if (tem == 0)
			{
				cout << "没有与该查找条件匹配的文件或文件夹" << endl;
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
			cout << ch << " 不是内部或外部命令，也不是可运行的程序或批处理文件。" << endl;
		}
		cout << endl;
		memset(ch, 0, sizeof(ch));
		cout << "D:/我的电脑 >";
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
	//调用相关修改文件夹索引的函数
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
	while (already_exist(newf->return_to_pre, newf))
	{
		cout << "That file is already exist." << endl;
		cout << "Operation failed." << endl;
		newf = get_file_info();
		//enter what to exit?
	}

	//文件大小大于剩余空间
	if (newf == NULL)
	{
		cout << "Insufficient disk space." << endl;
		cout << "Operation failed." << endl;
		return;
	}
	//剩余空间可以存放该文件
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
	//调用相关修改文件夹索引的函数
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

	//读取当前系统时间作为首次修改时间
	return temp;
}

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
		allocate(newf);

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


	strcpy_s(init_folder->name, 20, "我的电脑");
	init_folder->in_folder = p1;
	init_folder->return_to_pre = NULL;
	init_folder->next = NULL;
	init_folder->in_file = NULL;
	init_file = NULL;

	p1->return_to_pre = init_folder;
	strcpy_s(p1->name, 20, "操作系统");   //名称
	strcpy_s(p1->location, 50, Print_location(p1->return_to_pre));   //位置
	p1->in_file = f1;
	p1->in_folder = NULL;

	strcpy_s(f1->name, 20, "课程设计.word");  //名称
	f1->fsize = 10;   //大小
	strcpy_s(f1->belong, 20, "word");  //属性
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
	strcpy_s(f2->name, 20, "课程作业.word");   //名称
	f2->fsize = 30;      //大小
	strcpy_s(f2->belong, 20, "word");   //位置
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
	strcpy_s(p3->name, 20, "实验文件");   //名称
	strcpy_s(p3->location, 50, Print_location(p3->return_to_pre));   //位置
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

	//add the init info to the index

	
	//---------Andemund------------
	return;
}


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
		p1 = p1->next;
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


//************ warning  第二次代码补充 *****************
/*
-name 按名字查找  find -name D:/我的电脑/软件工程/ ppt
-type 文件类型查找  find -type D:/我的电脑/软件工程/ txt
*/

//按照名称查找
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

//按照类型查找
void find_type(Folder * ptr, char contact[])
{

}
//打印位置的函数
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

//查找函数
void Find()
{

	char ch[100];    //用来临时存储读入的内容
	Folder * find_located = NULL;
	memset(ch, 0, sizeof(ch));
	int t = 0, j = 0, way = 0;
	char arr[100];     //承接输入的查找内容
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
			if (t == 3)
			{
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



/*------------after mid-term----------------*/


//输入新建文件夹信息
Folder * get_folder_info()
{
	Folder * temp = new Folder;
	Folder * a;	//the last folder in the uplevel folder
	cout << "Please input the location of the new folder:" << endl;
	cin >> temp->location;
	//调用相关修改文件夹索引的函数

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