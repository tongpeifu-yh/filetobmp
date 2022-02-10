#include "tobmp.h"


int main(int argc, char* argv[])
{
	//��������
	int opt = HIDE;//ȱʡ����
	int ifSame=NO;//ǰ���ļ����Ƿ���ͬ
	int ifBackup=YES;//��ǰ���ļ�����ͬ����˲������� �Ƿ񱸷�Դ�ļ� ȱʡ����
	char *InputFileName=NULL, *OutputFileName=NULL;

	ArguProcess(argc,argv,&opt,&ifSame,&ifBackup,&InputFileName,&OutputFileName);
	if (opt==HIDE)
	{
		hide(InputFileName,OutputFileName,ifSame,ifBackup);
	} 
	else
	{
		solve(InputFileName, OutputFileName,ifSame,ifBackup);
	}
	
	//printf("ͼƬ��%d���أ���%d����\n", wid,hei);
	return 0;
}



void ArguProcess(int argc, char **argv, int *opt, int *ifSame,int *ifBackup, char **InputFileName, char **OutputFileName)
{
	int i;
	for (i = 1; i < argc; i++)
	{
		if (my_strcmp(argv[i],"hide"))
		{
			*opt = HIDE;
		}
		else if (my_strcmp(argv[i], "solve"))
		{
			*opt = SOLVE;
		}
		else if (my_strcmp(argv[i], "file") || my_strcmp(argv[i], "f"))
		{
			if(++i<argc)
				*InputFileName = argv[i];
		}
		else if (my_strcmp(argv[i], "output") || my_strcmp(argv[i], "o"))
		{
			if (++i<argc)
				*OutputFileName = argv[i];
		}
		else if (my_strcmp(argv[i], "nobackup"))
		{
			*ifBackup = NO;
		}
		else if (my_strcmp(argv[i],"backup"))
		{
			*ifBackup = YES;
		}
		else if (my_strcmp(argv[i],"?")|| my_strcmp(argv[i], "help")|| my_strcmp(argv[i], "/?")|| my_strcmp(argv[i], "-h")|| my_strcmp(argv[i], "--help"))
		{
			PutHelp();
		}
		else
		{
			printf("\"%s\":����ȷ�Ĳ���\n",argv[i]);
		}
	}
	if (*InputFileName==NULL)
	{
		puts("�������ļ�����");
		static char temp0[LEN_OF_FILENAME] = { 0 };
		fgets(temp0, LEN_OF_FILENAME, stdin);
		temp0[strlen(temp0) - 1] = 0;
		*InputFileName = temp0;
	}

	if (*OutputFileName==NULL)
	{
		if (*opt == HIDE)
		{
			static char temp1[LEN_OF_FILENAME] = { 0 };
			strcpy(temp1, *InputFileName);
			strcat(temp1, ".bmp");
			*OutputFileName = temp1;
		}
		else
		{
			puts("δָ����Ч������ļ�������ʹ�ú�׺��\".temp\"��");
			static char temp2[LEN_OF_FILENAME] = { 0 };
			strcpy(temp2, *InputFileName);
			strcat(temp2, ".temp");
		}
	}
	else if (my_strcmp(*InputFileName,*OutputFileName))
	{
		*ifSame = YES;
		strcat(*OutputFileName, ".temp");
	}
}

int my_strcmp(char * s1, char *s2)//��ͬ����1����ͬ����0
{
	int i = 0;
	while (1)
	{
		if (s1[i] != s2[i])return 0;
		if (s1[i] == 0)return 1;
		i++;
	}
}
long filesize(char * filename)
{
	struct stat file_message;
	stat(filename, &file_message);
	return file_message.st_size;
}

char * invert_strchr(char *s, char c)
{
	int n = strlen(s) - 1;
	for (int i = n; i >= 0; i--)
	{
		if (s[i] == c)return s + i;
	}
	return NULL;
}

void PutHelp()
{
	puts(
		"\t*************************************************\n"
		"\t        �ļ�����ת��bmpλͼ�ļ�-by ͨ���\n"
		"\t                  2021.11.14\n"
		"\t*************************************************\n"
		"\n\n"
		"ʹ�÷�����filetobmp hide/solve file/f Դ�ļ��� output/o ���ļ���\n"
		"hide������Դ�ļ�\n"
		"solve�����ԭ�ļ�\n"
		"file/f��Դ�ļ�\n"
		"output/o������ļ�\n"
		"help��������Ϣ\n"
		);
}