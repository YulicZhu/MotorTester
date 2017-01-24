/*
 * WRITE_SD.c
、
 *
 *  Created on: Nov 27, 2016
 *      Author: Yulic_zhu
 */
#include "MPC5604B.h"
#include "SD.h"
#include "WRITE_SD.h"
#include "includes.h"
#include "ff.h"
#include "stdio.h"
FATFS fatfs2;
uint16_t m;
uint16_t error;
struct buff{
	char clock[11];
	char current_val[5];
	char volt_val[5];
	char mscounter[11];

}*BUFFER;
FIL fil;
TCHAR tchar[30];

/************************************************************/
/*                          主函数                          */
/************************************************************/

void init_SD_FatFs(){
	SD_Init();
	LED=1;
	delay();
	FatFs_Init();
}
int file_create(unsigned long timestamp){
	sprintf(tchar,"%ld.txt",timestamp);
	if (FR_OK == f_open(&fil, tchar, FA_OPEN_ALWAYS))
	{
		if (FR_OK == f_close(&fil))
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 1;
	}
}
void WRITE_SD(uint32_t a[4])
{	unsigned short wr;
	char strbuff[40]={"\0"};
	sprintf(strbuff,"\r\n%d\t%d\t%d\t%d",a[0],a[1],a[2],a[3]);
if (FR_OK == f_open(&fil, tchar, FA_WRITE))
{
	f_lseek(&fil,f_size(&fil)); //移动指针位置
	f_write(&fil, (const void *)&(strbuff), sizeof(strbuff), &wr);	
	close_file();//必须每次都加上close_file，否则只能记录最后一次单行数据
}
}
int close_file(){
	if (FR_OK == f_close(&fil))
	{
		return 0;
	}
	else
	{
		return 5;
	}
}
