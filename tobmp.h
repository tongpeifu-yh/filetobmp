#ifndef _TOBMP_H_
#define _TOBMP_H_


#define _CRT_SECURE_NO_WARNINGS
#pragma pack(1)
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<math.h>
#include<sys/types.h>
#include <sys/stat.h>
#define HIDE 1
#define SOLVE 0
#define YES 1
#define NO 0
#define LEN_OF_FILENAME 512

int my_strcmp(char * s1, char *s2);//相同返回1，不同返回0
long filesize(char * filename);
void ArguProcess(int argc, char **argv, int *opt, int *ifSame, int *ifBackup, char **InputFileName, char **OutputFileName);
int hide();
int solve();
char *invert_strchr();
void PutHelp();

typedef BITMAPFILEHEADER bmp_head;//bmp文件头
typedef BITMAPINFOHEADER bmp_info;//bmp信息头

#endif
