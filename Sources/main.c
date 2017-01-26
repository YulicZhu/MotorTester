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
		//Measure_Conf();										//��Ҫ����PWM�������;
		Single_Collection();
		//Show_Number();
	}
}
void Single_Collection(){
	long sys_clock_base,t,a[1024][4],ticktock;
	EMIOS_0.CH[18].CCR.B.MODE = 0x00;
	EMIOS_0.CH[18].CCR.B.MODE = 0x13; 							// Modulus Counter(MC),����ģʽ ,external clock*/������������
	STM.CR.B.TEN = 1;											// STM enable and start
	ADC_Enable();
	sys_clock_base=Read_Stm();
	while(file_create(sys_clock_base)){}						//ͨ��ʱ��������ļ�
	LED=0;
	/*Measuring*/
	for(t=0;t<1024;t++)
	{	while((ticktock=Read_Stm()-sys_clock_base)%7000>10){}	//������ʹ7msһ������;�ݲ�10us
		result[t].ticktock=ticktock;							//ʱ�ӣ��ֶ�ֵ1us
		result[t].volt=ADC_Vcurrent();					 		//current_capture();
		result[t].current=ADC_Volt();							//volt_capture();
		result[t].counter=(uint32_t)EMIOS_0.CH[18].CCNTR.B.CCNTR;
	}															//ʹ7ms1��
	/*Saving*/
	WRITE_SD(result);
	EMIOS_0.CH[18].CCR.B.MODE = 00;//MS����������
} 
