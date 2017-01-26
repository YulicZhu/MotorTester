

#include "MODULE_Init.h"
#ifndef WRITE_SD_H_
#define WRITE_SD_H_
extern struct mea_res result[];
#define  LED	SIU.GPDO[76].B.PDO	//¸Ä

void SYSTEM_Init(void);
void SIU_init(void);
void delay(void);
void init_SD_FatFs();
int WRITE_SD(struct mea_res result[]);
int READ_SD();
short file_create(long timestamp);
#endif /* WRITE_SD_H_ */
