/**
*******************************************************************************
**
**  @file               logger.h
**  @brief              File description
**  @par				Detail description
**
**  @version            0.1.0
**  @date               2018-01-22
**
*******************************************************************************
**
**  @author				Javier Peces
**  @copyright
**
*******************************************************************************
**
**  @par VERSION HISTORY
**  @par
**  Version  | Date        | Revised by        | Description
**  -------- | ----------- | ----------------- | -----------------------------
** 	0.1.0    | 2018-01-22  | Javier Peces	   | File creation
**
*******************************************************************************
**/


#ifndef LOGGER_H_
#define LOGGER_H_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/


/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/


/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/
typedef enum {
	LOGGER_ERROR,
	LOGGER_WARN,
	LOGGER_SYSTEM,
	LOGGER_INFO
}LoggerLevel;

typedef struct _logger {
	LoggerLevel level;
	char *levelMsg;
	void (*setLevel)(struct _logger*, LoggerLevel);
	void (*log)(char* str);
}Logger;


/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/
Logger initLogger(void *logFunction);


#endif /* LOGGER_H_ */

/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
