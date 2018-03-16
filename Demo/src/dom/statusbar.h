/**
*******************************************************************************
**
**  @file               statusbar.h
**  @brief              Statusbar module definition for log visualization
**  @par				Detail description
**						...
**
**  @version            0.1.0
**  @date               2018-01-18
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
** 	0.1.0    | 2018-01-18  | Javier Peces	   | File creation
**
*******************************************************************************
**/


#ifndef STATUSBAR_H_
#define STATUSBAR_H_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "logger.h"

/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/

/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/


/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/
void STATUSBAR_init(void);
void STATUSBAR_update(void);
void STATUSBAR_setStatus(char *status, LoggerLevel level);

#endif /* STATUSBAR_H_ */

/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
