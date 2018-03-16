/**
*******************************************************************************
**
**  @file               statusbar.c
**  @brief              Statusbar module implementation for log visualization
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


#define STATUSBAR_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "statusbar.h"
#include "new_types.h"
#include "display.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/
#define STATUSBAR_WIDTH				0
#define STATUSBAR_HEIGHT			0

/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/


/******************************************************************************
**                      PROTOTYPES OF LOCAL FUNCTIONS                        **
******************************************************************************/
void STATUSBAR_printMsg(char *str);

/******************************************************************************
**                     	GLOBAL VARIABLES                                 	 **
******************************************************************************/
char *p_status = NULL;
static vec2_t g_pos = {50, 550};
static color_t g_color = {0, 255, 0};
Logger g_logger;

/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/
/**
*******************************************************************************
* @brief   STATUSBAR_init
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void STATUSBAR_init(void) {
	g_logger = initLogger(STATUSBAR_printMsg);
}

/**
*******************************************************************************
* @brief   STATUSBAR_update
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void STATUSBAR_update(void) {
	/* update statusbar drawing */
	DISPLAY_drawStatusBar(&g_pos, STATUSBAR_WIDTH, STATUSBAR_HEIGHT, &g_color);

	/* update status string */
	g_logger.log(p_status);
}

void STATUSBAR_setStatus(char *status, LoggerLevel level) {
	p_status = status;
	g_logger.setLevel(&g_logger, level);


}

/******************************************************************************
**                      LOCAL FUNCTIONS                                  	 **
******************************************************************************/
void STATUSBAR_printMsg(char *str) {
	char *msg = (char *) malloc(1 + strlen(g_logger.levelMsg) + strlen(str));
	strcpy(msg, g_logger.levelMsg);
	strcat(msg, str);

	DISPLAY_printString(msg, &g_pos, &g_color);

	free(msg);
}

/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
