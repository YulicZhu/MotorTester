/*
 * MODULE_Init.h

 *
 *  Created on: Nov 27, 2016
 *      Author: Yulic_zhu
 */

#ifndef MODULE_INIT_H_
#define MODULE_INIT_H_
struct mea_res{
	uint32_t ticktock;
	uint16_t volt;
	uint16_t current;
	uint32_t counter;
};						 //结构体的声明，不能在.h中定义结构体
void SYSTEM_Init();
void SIU_Init();
void EMIOS_Cnf();
long Read_Stm();
void ADC_Enable();
uint16_t ADC_Volt();
uint16_t ADC_Vcurrent();

#endif /* MODULE_INIT_H_ */
