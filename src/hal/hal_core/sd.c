/**
****************************************************************************
* @file			sd.c
* @brief 		Lib for using the SD in the Zybo
* @version		0.1.0
* @date			18 mar. 2018
*
* @author		Javier Peces 
*
* @par Version history
* @par
*  Version   | Date         |  Revised by        |  Description
*  --------- | ------------ | -----------------  | ----------------------------
*   0.1.0    | 30-10-2017   |  Javier Peces      | file creation
****************************************************************************/

/***************************************************************************
 **                      MODULES USED                                     **
 ***************************************************************************/
#include <ff.h>
#include "xsdps.h"
#include <integer.h>
#include <stdio.h>
#include <xil_types.h>
#include <xstatus.h>
#include "sd.h"

/***************************************************************************
 **                      DEFINITIONS AND MACROS                           **
 ***************************************************************************/
static FIL fil;		/* File object */
static FATFS fatfs;
static char *SD_File;
u32 Platform;

#ifdef __ICCARM__
#pragma data_alignment = 32
u8 DestinationAddress[10*1024*1024];
u8 SourceAddress[10*1024*1024];
#pragma data_alignment = 4
#else
u8 DestinationAddress[10*1024*1024] __attribute__ ((aligned(32)));
u8 SourceAddress[10*1024*1024] __attribute__ ((aligned(32)));
#endif

#define TEST 7

/***************************************************************************
 **                      PROTOTYPES OF LOCAL FUNCTIONS                    **
 ***************************************************************************/

/***************************************************************************
 **                      EXTERN VARIABLES                                 **
 ***************************************************************************/

/***************************************************************************
 **                      GLOBAL VARIABLES                                 **
 ***************************************************************************/
FRESULT Res;
UINT NumBytesRead;
UINT NumBytesWritten;
u32 BuffCnt;
u32 FileSize = (8*1024*1024);
TCHAR *Path = "0:/";
FILINFO fno;

/***************************************************************************
 **                      LOCAL FUNCTIONS                                  **
 ***************************************************************************/
/**
 * @brief Stores the string introduced in a new line of the SD card.
 * @par
 * @param "newStr": string to be introduced in the SD card.
 * @return integer: the process has been successful (0) or error code.
 */
int SD_saveInSD(char * newStr, char * fileName){

	FRESULT Res;
	UINT NumBytesRead;
	UINT NumBytesWritten;
	u32 BuffCnt;
	u32 FileSize = (8*1024*1024);
	TCHAR *Path = "0:/";
	FILINFO fno;
	int i = 0;
	int charac = 0;
	char str[MAX_ARRAY];

	/* Pointer to beginning of file */
	Res = f_mount(&fatfs, Path, 0);
	if (Res != FR_OK) {
		xil_printf("Error mounting the SD\n\r");
		return XST_FAILURE;
	}

	/*
	 * Open file with required permissions.
	 * Here - Creating new file with read/write permissions. .
	 * To open file with write permissions, file system should not
	 * be in Read Only mode.
	 */
	SD_File = fileName;

	Res = f_open(&fil, SD_File, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	if (Res) {
		xil_printf("Error reading that file\n\r");
		return XST_FAILURE;
	}

	Res = f_lseek(&fil, 0);
	if (Res) {
		xil_printf("Error getting to the start of the file\n\r");
		return XST_FAILURE;
	}

	do{
		Res = f_read(&fil, &charac, 1, &NumBytesRead);

		i++;
	}while( (NumBytesRead!= 0 ) && ( charac != 0) );

	f_lseek(&fil,i-1);
	sprintf(str,newStr);
	sprintf(SourceAddress, "%s\r\n", str);
	Res = f_write(&fil, (const void*)SourceAddress,  MAX_ARRAY , &NumBytesWritten);//strlen(str)+400
	if (Res) {
		xil_printf("Error writing the new file\n\r");
		return XST_FAILURE;
	}

	Res = f_close(&fil);
	if (Res) {
		xil_printf("Error closing the SD\n\r");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int SD_readSD(char * newStr, char * fileName){

	FRESULT Res;
	UINT NumBytesRead;
	UINT NumBytesWritten;
	u32 BuffCnt;
	u32 FileSize = (8*1024*1024);
	TCHAR *Path = "0:/";
	FILINFO fno;
	int i = 1;
	int lineSize=38;
	int charac = 0;
	char letter;
	char str[MAX_ARRAY];
	char line[MAX_ARRAY];

	/* Pointer to beginning of file */
	Res = f_mount(&fatfs, Path, 0);
	if (Res != FR_OK) {
		xil_printf("Error mounting the SD\n\r");
		return XST_FAILURE;
	}

	/*
	 * Open file with required permissions.
	 * Here - Creating new file with read/write permissions. .
	 * To open file with write permissions, file system should not
	 * be in Read Only mode.
	 */
	SD_File = fileName;

	Res = f_open(&fil, SD_File, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	if (Res) {
		xil_printf("Error reading that file\n\r");
		return XST_FAILURE;
	}
	 /* Pointer to beginning of file 38*/
	Res = f_lseek(&fil, 0);
	if (Res) {
		xil_printf("Error getting to the start of the file\n\r");
		return XST_FAILURE;
	}
	memset(line, 0, sizeof(line));
	do{
		Res = f_read(&fil, &charac, 1, &NumBytesRead);
		letter=charac;
		if (letter=='$'){
			xil_printf("%s\n\r",line);
			i++;
			memset(line, 0, sizeof(line));
		}else{
			if((letter!='\n')&&(letter!='\r')){
				strncat(line,&letter,1);
			}
		}

	}while( (NumBytesRead!= 0 ) && ( charac != 0) );
	Res = f_close(&fil);
	if (Res) {
		xil_printf("Hello6\n\r");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int SD_clearSD(char * fileName){
	FRESULT Res;
	Res=f_unlink(fileName);
	return XST_SUCCESS;
}