#include "tobmp.h"

int hide(char *InputFileName, char *OutputFileName,int ifSame,int ifBackup)
{
	FILE *iFile = fopen(InputFileName, "rb");
	FILE *oFile = fopen(OutputFileName, "wb");

	if (iFile == NULL || oFile == NULL)
	{
		puts("文件读写错误！");
		exit(-1);
	}
	int iFileSize = (int)filesize(InputFileName);
	int wid = 0, hei = 0;
	int pic_size = 0;
	char NameToWrite[LEN_OF_FILENAME] = { 0 };

	if (strlen(InputFileName)>LEN_OF_FILENAME)
	{
		strcpy(NameToWrite, InputFileName + (strlen(InputFileName) - LEN_OF_FILENAME));
	}
	else
	{
		strcpy(NameToWrite, InputFileName);
	}

	wid = hei = ((int)(sqrt(iFileSize / 3)) / 4 + 1) * 4;//图片宽度必须是4的倍数
	//若不是4的倍数，需要用0填充至4的倍数的字节数
	pic_size = wid*hei * 3;
	while (pic_size < iFileSize + 4 + LEN_OF_FILENAME)
	{
		wid += 4;
		pic_size = wid*hei * 3;
	}
	bmp_head head = {
		('M' * 256) + 'B',pic_size + 54,0,0,54
	};
	bmp_info info = {
		40,wid,hei,1,24,0,pic_size,0,0,0,0
	};

	fwrite(&head, 1, 14, oFile);
	fwrite(&info, 1, 40, oFile);
	fwrite(NameToWrite, 1, LEN_OF_FILENAME, oFile);
	fwrite(&iFileSize, 4, 1, oFile);

	int room_size = 5 * 1024 * 1024;
	char *room = malloc(room_size);
	memset(room, 0, room_size);

	int once_read, have_read = 0;
	while (have_read < iFileSize)
	{
		once_read = fread(room, 1, room_size, iFile);
		have_read += once_read;
		fwrite(room, once_read, 1, oFile);
	}
	memset(room, '0', room_size);
	fwrite(room, pic_size - 4 - LEN_OF_FILENAME - iFileSize, 1, oFile);

	free(room);
	fclose(iFile);
	fclose(oFile);

	printf("wid:%d\thei:%d\n", wid, hei);
	if (ifSame==YES)
	{
		if (ifBackup == YES)
		{
			char bakname[516] = { 0 };
			strcpy(bakname, InputFileName);
			strcat(bakname, ".bak");
			rename(InputFileName, bakname);
			rename(OutputFileName, InputFileName);
		}
		else 
		{
			remove(InputFileName);
			rename(OutputFileName, InputFileName);
		}
	}

	return 0;
}

int solve(char *InputFileName, char *OutputFileName,int ifSame,int ifBackup)
{
	FILE *iFile = fopen(InputFileName, "rb");
	FILE *oFile = fopen(OutputFileName, "wb");

	if (iFile == NULL || oFile == NULL)
	{
		puts("文件读写错误！");
		exit(-1);
	}
	int srcfilesize = 0;
	int room_size = 5 * 1024 * 1024;
	char *room = malloc(room_size);
	int once_read;

	memset(room, 0, room_size);

	fseek(iFile, 54L+LEN_OF_FILENAME, SEEK_SET);
	fread(&srcfilesize, 1, sizeof(int), iFile);

	for (int i = 0; i < srcfilesize / room_size; i++)
	{
		once_read=fread(room, 1, room_size, iFile);
		fwrite(room, 1, once_read, oFile);
	}
	once_read = fread(room, 1, srcfilesize%room_size, iFile);
	fwrite(room, 1, once_read, oFile);

	free(room);
	fclose(iFile);
	fclose(oFile);

	if (ifSame==YES)
	{
		if (ifBackup==YES)
		{
			char bakname[516] = { 0 };
			strcpy(bakname, InputFileName);
			strcat(bakname, ".bak");
			rename(InputFileName, bakname);
			rename(OutputFileName, InputFileName);
		} 
		else
		{
			remove(InputFileName);
			rename(OutputFileName, InputFileName);
		}
	}

	return 0;
}


