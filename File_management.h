#pragma once
//#define Disk_M 2048;    //定义磁盘大小为 2048 MB
//#define INDEXSPACE 10;	//为索引部分预留一定的存储空间 10MB
//#define ADJUST 100;	//若剩余碎片最大容量小于此值，则重新分配物理空间
int Disk_M = 2048;
int BLOCKSIZE = 2;
int INDEXSPACE = 10;
int BLOCKNUM = Disk_M / BLOCKSIZE;

int empty_block_begin;
int empty_block_end;


double Remain_M;        //磁盘剩余空间
//int disk_block[2048];	//磁盘分块
int org_method = 0;	//1-Link organization, 2-Index organization, 3-sequential organization
int tab = 0;    //用来打印tab换行符
//int disk_empty=Disk_M;
int tem = 0;   //用来判断是否查找到文件

//文件的结构体
typedef struct File
{
	char name[20];   //文件名
	double fsize;     //文件大小
	char belong[20];      //文件属性
	int phy_loc;	//物理地址起始位置
	char location[50];   //文件的位置
	char  time[20];      //文件的最后修改时间	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
	struct File * next;  //指向与它同目录下的文件，若为null则没有
	struct File * piece; //若文件被分开存储，则piece指向他的下一个片，null则无分片
	struct Folder * return_to_pre;  //指向上一级目录
	int length;//连续方式下所占的块数
	map<int, int> file_index;	//索引方式下用于保存逻辑块号和物理块号
}File;

 
//目录(文件夹)的结构体
typedef struct Folder
{
	char name[20];    //文件夹名称
	double fsize;      //文件夹大小=内含所有文件+文件夹大小
	char location[50];   //文件夹位置
	char  time[20];      //文件夹最后修改时间
	struct Folder * next;   //指向同目录下的文件夹，若为null则没有
	struct Folder * in_folder;  //指向文件夹内的文件夹，若为null则没有
	struct File * in_file;   //指向文件夹内的文件，若为null则没有
	struct Folder * return_to_pre;  //指向上一级目录
}Folder;

typedef struct Available
{
	//内部碎片最大
	int start;
	int length;
	struct Available * prev;
	struct Available * next;
}Available;

//for link method
typedef struct Block
{
	//分块
	int content;	//0 is empty, 1 is used, 2 is index
	int no;
	int next_no;
};


File * init_file;      //指向根目录的第一个文件
Folder * init_folder;   //指向根目录
Available * init_available;
Block * init_block;
Block *  block[1025];
Folder * current_ptr = init_folder;   //查找路径的当前指针
char current_locate[100] = { " D:/我的电脑/" };   //存储当前路径


//磁盘分块	2018-05-07