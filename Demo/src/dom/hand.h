/**
*******************************************************************************
**
**  @file               hand.h
**  @brief              Hand module definition for hand management
**  @par				Detail description
**  					...
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


#ifndef HAND_H_
#define HAND_H_


/******************************************************************************
**                     	DEFINITIONS AND MACROS                           	 **
******************************************************************************/


/******************************************************************************
**             			TYPEDEFS AND STRUCTURES                         	 **
******************************************************************************/

enum fingers {THUMB, INDEX, MIDDLE, RING, LITTLE};

typedef struct phalange {

}PHALANGE_T;

typedef struct finger {
	unsigned int id;
	PHALANGE_T phalanges[3];

}FINGER_T;

typedef struct palm {

}PALM_T;

typedef struct hand {
	FINGER_T fingers[5];
	PALM_T palm;

}HAND_T;

//typedef struct hand_shape {
//	HAND_T hand;
//	rot = 0; /* 0 - 2pi */
//
//	roll = 0;
//	yaw = 0;
//	pitch = 0;
//
//	pos = 0;
//}HAND_SHAPE_T;


/******************************************************************************
**                   	PUBLIC FUNCTIONS                               	     **
******************************************************************************/

void HAND_update(void);
void HAND_prepareData(void);
HAND_T HAND_getShape(void);
void HAND_setShape(HAND_T shape);
HAND_T HAND_getDefaultShape(void);
void HAND_setDefaultShape(void);
void HAND_moveFinger(/*...*/);
void HAND_changeRotation(int rot);

#endif /* HAND_H_ */

/******************************************************************************
**                  	EOF                                      	         **
******************************************************************************/
