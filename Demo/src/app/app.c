/**
*******************************************************************************
**
**  @file               app.c
**  @brief              Main file
**  @par				Detail description
**  					This file contain the initializations and the
**  					application main loop. It also manage the application
**  					shut down
**
**  @version            0.1.0
**  @date               2017-11-15
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
**  0.1.0    | 2017-11-15  | Javier Peces      | File creation
**
*******************************************************************************
**/


#define _APP_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "frame.h"
#include "menu.h"

void APP_init(void);
void APP_loop(void);

/******************************************************************************
**                  	LOCAL FUNCTIONS                                  	 **
******************************************************************************/

int main()
{
	APP_init();
	APP_loop();

	return 0;
}

void APP_init(void) {
	FRAME_init();
}

/**
*******************************************************************************
* @brief   Application loop
* @par 	   Detail description
*              ...
*
* @param       	Empty
* @return      	None
*
* @todo 		Frame rate cap
*******************************************************************************
**/
void APP_loop(void) {
	while(!MENU_shouldCloseApp()){
		FRAME_prepare();
		FRAME_update();
		FRAME_pollEvents();
	}

	FRAME_stop();
}

/******************************************************************************
**             			EOF                           			 			 **
******************************************************************************/
