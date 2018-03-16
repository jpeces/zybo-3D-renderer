/**
*******************************************************************************
**
**  @file               menu.h
**  @brief              Menu module definition for menu management
**  @par				Detail description
**  					@image html state_machine.png
**
**  @version            0.1.0
**  @date               2017-11-21
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
**  -------- | ----------- | ----------------- | ----------------------------
**  0.1.0    | 2017-11-21  | Javier Peces      | File creation
**
*******************************************************************************
**/


#ifndef MENU_H_
#define MENU_H_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "new_types.h"
#include "color.h"

/******************************************************************************
**                     	DEFINITIONS AND MACROS                           	 **
******************************************************************************/

/* MENU GRAPHICS */
#define XPOS					(float)50
#define YPOS					(float)50
#define OPTION_OFFSET  			(float)30
#define MENU_COLOR				(color_t){0, 255, 0}

/* MENU LOGIC */
#define N_MENU_OPTION 			5

#define BTN_MENU_FORWARD		0x1
#define BTN_MENU_BACKWARD		0x2
#define BTN_MENU_APPLY			0x8

#define MENU_NEXT				1
#define MENU_PREV			    -1

/* State machine macros */
#define IDLE		 			0
#define START_TRACKING 			1
#define STOP_TRACKING 			2
#define RESET_HAND_SHAPE 		3
#define QUIT 					4

#define INIT_STATE 				START_TRACKING

/******************************************************************************
**             			TYPEDEFS AND STRUCTURES                         	 **
******************************************************************************/

/******************************************************************************
**                   	PUBLIC FUNCTIONS                               	     **
******************************************************************************/

void MENU_update(void);
unsigned int MENU_getOptionSelected(void);
bool_t MENU_isTrackingActive(void);
bool_t MENU_shouldCloseApp(void);
void MENU_selectOption(int inc);
void MENU_applyOption(void);



#endif /* MENU_H_ */

/******************************************************************************
**                  	EOF                                      	         **
******************************************************************************/
