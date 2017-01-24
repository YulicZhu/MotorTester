//对应开的板子，有些地方还没配好，这个ms计数器刚刚试没试成功，SD部分是可以的
#include "MPC5604B.h"
#include "WRITE_SD.h"
#include "MODULE_Init.h"
void Single_Collection();
uint32_t volt_capture(void);
long Read_Stm();
int main(void) {
	SYSTEM_Init();
	SIU_Init();
	EMIOS_Cnf();
	init_SD_FatFs();
	INTC.CPR.B.PRI = 0;	
	for(;;){
		Single_Collection();
		//		emios_0_modual_counter=EMIOS_0.CH[8].CCNTR.B.CCNTR;
	}
}
uint32_t volt_capture(void){
	ADC.NCMR[0].B.CH0 = 1;

	ADC.MCR.B.NSTART =1;

	while(ADC.CDR[0].B.VALID!=1){}

	return (uint32_t)ADC.CDR[0].B.CDATA*5000/0x3FF;//volt_val

}
long Read_Stm(){
	//STM.CH[0].CCR.B.CEN = 1;//enable
	STM.CR.B.CPS=0xf;//1MHz;
	STM.CR.B.TEN = 1;//enable
	return STM.CNT.R;
}
void Single_Collection(){
	unsigned long sys_clock_base,t,i,FLAG=0;
	unsigned long emios_0_modual_counter=0;
	uint32_t a[4],a0;
	EMIOS_0.CH[18].CCR.B.MODE = 0x00;
	EMIOS_0.CH[18].CCR.B.MODE = 0x13; // Modulus Counter(MC),输入模式 ,external clock*/，启动计数器
	sys_clock_base=Read_Stm();
	while(file_create(sys_clock_base));//创建文件
	for(t=0;t<100;t++)
	{	//while(((uint32_t)Read_Stm()-sys_clock_base)%50);
		a[0]=(uint32_t)Read_Stm()-sys_clock_base;
		a[1]=t*2;//volt_capture();//current_capture();
		a[2]=t;//volt_capture();
		a[3]=(uint32_t)EMIOS_0.CH[18].CCNTR.B.CCNTR;
		LED=(FLAG^=1);
		WRITE_SD(a);
		//for(i=0;i<100;i++);
	}//70ms一个//改回7ms1个
	
	close_file();
	EMIOS_0.CH[18].CCR.B.MODE = 00;//MS计数器清零
}
