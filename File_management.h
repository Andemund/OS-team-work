#pragma once
//#define Disk_M 2048;    //������̴�СΪ 2048 MB
//#define INDEXSPACE 10;	//Ϊ��������Ԥ��һ���Ĵ洢�ռ� 10MB
//#define ADJUST 100;	//��ʣ����Ƭ�������С�ڴ�ֵ�������·�������ռ�
int Disk_M = 2048;
int BLOCKSIZE = 2;
int INDEXSPACE = 10;
int BLOCKNUM = Disk_M / BLOCKSIZE;

int empty_block_begin;
int empty_block_end;


double Remain_M;        //����ʣ��ռ�
//int disk_block[2048];	//���̷ֿ�
int org_method = 0;	//1-Link organization, 2-Index organization, 3-sequential organization
int tab = 0;    //������ӡtab���з�
//int disk_empty=Disk_M;
int tem = 0;   //�����ж��Ƿ���ҵ��ļ�

//�ļ��Ľṹ��
typedef struct File
{
	char name[20];   //�ļ���
	double fsize;     //�ļ���С
	char belong[20];      //�ļ�����
	int phy_loc;	//�����ַ��ʼλ��
	char location[50];   //�ļ���λ��
	char  time[20];      //�ļ�������޸�ʱ��	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
	struct File * next;  //ָ������ͬĿ¼�µ��ļ�����Ϊnull��û��
	struct File * piece; //���ļ����ֿ��洢����pieceָ��������һ��Ƭ��null���޷�Ƭ
	struct Folder * return_to_pre;  //ָ����һ��Ŀ¼
	int length;//������ʽ����ռ�Ŀ���
	map<int, int> file_index;	//������ʽ�����ڱ����߼���ź�������
}File;

 
//Ŀ¼(�ļ���)�Ľṹ��
typedef struct Folder
{
	char name[20];    //�ļ�������
	double fsize;      //�ļ��д�С=�ں������ļ�+�ļ��д�С
	char location[50];   //�ļ���λ��
	char  time[20];      //�ļ�������޸�ʱ��
	struct Folder * next;   //ָ��ͬĿ¼�µ��ļ��У���Ϊnull��û��
	struct Folder * in_folder;  //ָ���ļ����ڵ��ļ��У���Ϊnull��û��
	struct File * in_file;   //ָ���ļ����ڵ��ļ�����Ϊnull��û��
	struct Folder * return_to_pre;  //ָ����һ��Ŀ¼
}Folder;

typedef struct Available
{
	//�ڲ���Ƭ���
	int start;
	int length;
	struct Available * prev;
	struct Available * next;
}Available;

//for link method
typedef struct Block
{
	//�ֿ�
	int content;	//0 is empty, 1 is used, 2 is index
	int no;
	int next_no;
};


File * init_file;      //ָ���Ŀ¼�ĵ�һ���ļ�
Folder * init_folder;   //ָ���Ŀ¼
Available * init_available;
Block * init_block;
Block *  block[1025];
Folder * current_ptr = init_folder;   //����·���ĵ�ǰָ��
char current_locate[100] = { " D:/�ҵĵ���/" };   //�洢��ǰ·��


//���̷ֿ�	2018-05-07