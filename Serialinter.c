#include <Windows.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int Serial_Conf(HANDLE hcom, DCB *dcb);
void *Serial_Read(void *arg);
void *Serial_Write(void *arg);

char bReadStat, bWriteState, ctrl;
char RecFSerial[1], OptTSerial[1];
DWORD rCount, wCount;//实际读取的字节数
HANDLE hCom;


int main(int argc, char *argv[])
{
	FILE *fp_data;
	char file_stat;
	pthread_t read_tid, write_tid;
	
	printf("\n\
######################################################################################\n\
Welcome ! \n\
The first parameter is your com port. \n\
And the second parameter is the file name you are going to create to record all... \n\
######################################################################################\n");

	hCom = CreateFile(argv[1],//COM1口 TEXT("com4")
						GENERIC_READ|GENERIC_WRITE, //允许读
						0, //指定共享属性，由于串口不能共享，所以该参数必须为0
						NULL,
						OPEN_EXISTING, //打开而不是创建
						FILE_ATTRIBUTE_NORMAL,//FILE_ATTRIBUTE_NORMAL, //属性描述，该值为FILE_FLAG_OVERLAPPED，表示使用异步I/O，该参数为0，表示同步I/O操作
						NULL);

	if (hCom == INVALID_HANDLE_VALUE){
		printf("Cannot Open The Com You Choose !\n");
		return FALSE;
	}
	else	printf("%s open successful !\n", argv[1]);
	
	/*****************************************配置串口***************************/
	DCB dcb;
	Serial_Conf(hCom, &dcb);

	pthread_create(&read_tid, NULL, Serial_Read, NULL);
	pthread_create(&write_tid, NULL, Serial_Write, NULL);
	pthread_join(read_tid, NULL);
	pthread_join(write_tid, NULL);

	CloseHandle(hCom);

	return 0;
}

int Serial_Conf(HANDLE hcom, DCB *dcb)
{
	GetCommState(hcom, dcb);
	(*dcb).BaudRate = 9600; //波特率为115200
	(*dcb).ByteSize = 8; //每个字节有8位
	(*dcb).Parity = NOPARITY; //无奇偶校验位
	(*dcb).StopBits = ONESTOPBIT; //一个停止位
	if(!SetCommState(hcom, dcb)){
		printf("Something wrong when set the serial !\n");
		return 1;
	}
	else	return 0;
}

void *Serial_Read(void *arg)
{
	while(1)
	{
		bReadStat = ReadFile(hCom, RecFSerial, sizeof(RecFSerial), &rCount, NULL);
 
		if(bReadStat)	printf("%c", *RecFSerial);
		else{
			printf("Error Reading Serial !\n");
			return FALSE;
		}
	}
}

void *Serial_Write(void *arg)
{
	while(1)
	{
		*OptTSerial = getchar();
		bWriteState = WriteFile(hCom, OptTSerial, 1, 0, NULL);
 		FlushFileBuffers(hCom);
		if(bWriteState)	printf("%c", *OptTSerial);
		else{
			printf("Error Writing Serial !\n");
			return FALSE;
		}
	}
}
