#include "MPC5604B.h"
void Show_Number(int num){
	int seg_sel[4]={10,63,62,76};			//A10,D15,D14,E12
	int bit_sel[7]={8,61,6,121,67,3,34};	//A8,D13,A6,H9,E3,A3,C2
	int i,temp=num;
	//67
	for(i=0;i<4;i++){
		SIU.GPDO[chip_sel[i]].B.PDO=1;
		display(temp%10);
		delay();
		temp/=10;
	}
}
void display(int num){
	//有点不知道怎么处理了
	
}
