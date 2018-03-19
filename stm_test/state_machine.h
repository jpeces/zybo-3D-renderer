/**
*******************************************************************************
**
**  @file               state_machine.h
**  @brief              File description
**  @par				Detail description
**
**  @version            0.1.0
**  @date               2017-12-10
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
** 	0.1.0    | 2017-12-10  | Javier Peces	   | File creation
**
*******************************************************************************
**/


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include <stdint.h>

/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/
#define TRUE 		1
#define FALSE 		0

/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/
typedef uint8_t bool_t;
typedef unsigned char byte_t;

typedef void            (*TPFN_ACC)(void); /* Puntero a una función acción */
typedef bool_t          (*TPFN_EVE)(void); /* Puntero a una función evento */

typedef struct {
	byte_t          next_id;  		/* next state identifier */
	char*         	name;         	/* debug name */
	TPFN_EVE      	event;         	/* Pointer to an event function */
	TPFN_ACC      	action;         /* Pointer to an action function */
} STM_EVEACC;

typedef struct {
	byte_t          id;             /* state identifier */
	char*         	name;         	/* debug name */
	TPFN_ACC      	controls;      	/* Funcion de control del estado */
	STM_EVEACC*		transitions;    /* Punteros las functions del estado */
} STM_STATE;

typedef struct {
	char*		 	name;         	/* name identificativo de depuraci¢n */
	byte_t			id;				/* machine identifier */
	byte_t			id_act_st;		/* current state identifier */
	TPFN_EVE      	StopCond;       /* Condici¢n necesaria para la ejecuci¢n */
	STM_STATE**		state;          /* Matriz de punteros a los ESTADOS */
} STM_MACHINE;


/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/

void STM_execute(STM_MACHINE *machine);

#endif /* STATE_MACHINE_H_ */

/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
