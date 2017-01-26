#include "MPC5604B.h"
#include "WRITE_SD.h"
#include "MODULE_Init.h"
void Single_Collection();
struct mea_res result[1024];
int main(void) {
	SYSTEM_Init();
	SIU_Init();
	EMIOS_Cnf();
	ADC_Enable();
	init_SD_FatFs();
	INTC.CPR.B.PRI = 0;											//lowest priority for what?
	for(;;){
		//Measure_Conf();										//需要配置PWM电机参数;
		Single_Collection();
		//Show_Number();
	}
}
void Single_Collection(){
	long sys_clock_base,t,a[1024][4],ticktock;
	EMIOS_0.CH[18].CCR.B.MODE = 0x00;
	EMIOS_0.CH[18].CCR.B.MODE = 0x13; 							// Modulus Counter(MC),输入模式 ,external clock*/，启动计数器
	STM.CR.B.TEN = 1;											// STM enable and start
	ADC_Enable();
	sys_clock_base=Read_Stm();
	while(file_create(sys_clock_base)){}						//通过时间戳创建文件
	LED=0;
	/*Measuring*/
	for(t=0;t<1024;t++)
	{	while((ticktock=Read_Stm()-sys_clock_base)%7000>10){}	//调整，使7ms一个周期;容差10us
		result[t].ticktock=ticktock;							//时钟，分度值1us
		result[t].volt=ADC_Vcurrent();					 		//current_capture();
		result[t].current=ADC_Volt();							//volt_capture();
		result[t].counter=(uint32_t)EMIOS_0.CH[18].CCNTR.B.CCNTR;
	}															//使7ms1个
	/*Saving*/
	WRITE_SD(result);
	EMIOS_0.CH[18].CCR.B.MODE = 00;//MS计数器清零
} 
