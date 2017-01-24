/*
 * WRITE_SD.h
 *
 *  Created on: Nov 27, 2016
 *      Author: Yulic_zhu
 */

#ifndef WRITE_SD_H_
#define WRITE_SD_H_

#define  LED	SIU.GPDO[76].B.PDO

void SYSTEM_Init(void);
void SIU_init(void);
void delay(void);
void init_SD_FatFs();
void WRITE_SD(uint32_t a[4]);
int close_file();
int READ_SD();
int file_create(unsigned long timestamp);
#endif /* WRITE_SD_H_ */
