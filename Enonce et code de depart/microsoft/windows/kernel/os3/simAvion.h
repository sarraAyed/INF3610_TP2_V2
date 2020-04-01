/*
 * tourControleAvions.h
 *
 *  Created on: 14 sept. 2018
 *      Author: evter
 */

#ifndef SRC_SIMAVION_H_
#define SRC_SIMAVION_H_

#include <os.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

 /*
 *********************************************************************************************************
 *                                              CONSTANTS
 *********************************************************************************************************
 */

#define TASK_STK_SIZE       16384            // Size of each task's stacks (# of WORDs)

#define fit_timer_1s_isr_PRIO 20 // Defining Priority of each task
#define fit_timer_3s_isr_PRIO 21
#define    gpio_isr_PRIO 22

#define VERIFICATION_PRIO         23 // Defining Priority of each task
#define GENERATION_PRIO 24
#define STATISTIQUES_PRIO        25
#define ATTERRISSAGE_PRIO        26
#define TERMINAL0_PRIO        27
#define TERMINAL1_PRIO        28
#define DECOLLAGE_PRIO        29

 //Intervalles criteres de retard
#define BORNE_INF_LOW      	0
#define BORNE_SUP_LOW      	2
#define BORNE_INF_MEDIUM   	3
#define BORNE_SUP_MEDIUM  	5
#define BORNE_INF_HIGH     	6
#define BORNE_SUP_HIGH     	8

#define ROUGE_SIZE 10
#define JAUNE_SIZE 10
#define VERT_SIZE 10
/*
*********************************************************************************************************
*                                             VARIABLES
*********************************************************************************************************
*/
static CPU_STK generationStk[TASK_STK_SIZE]; //Stack of each task
static CPU_STK atterrissageStk[TASK_STK_SIZE];
static CPU_STK terminal0Stk[TASK_STK_SIZE];
static CPU_STK terminal1Stk[TASK_STK_SIZE];
static CPU_STK decollageStk[TASK_STK_SIZE];
static CPU_STK statistiquesStk[TASK_STK_SIZE];
static CPU_STK verificationStk[TASK_STK_SIZE];
static CPU_STK fit_timer_1sStk[TASK_STK_SIZE];
static CPU_STK fit_timer_3sStk[TASK_STK_SIZE];
static CPU_STK gpio_isr_Stk[TASK_STK_SIZE];

static OS_TCB generationTCB;
static OS_TCB atterrissageTCB;
static OS_TCB terminal0TCB;
static OS_TCB terminal1TCB;
static OS_TCB decollageTCB;
static OS_TCB statistiquesTCB;
static OS_TCB verificationTCB;
static OS_TCB verificationTCB;
static OS_TCB fit_timer_1sTCB;
static OS_TCB fit_timer_3sTCB;
static OS_TCB gpio_isr_TCB;

/*
*********************************************************************************************************
*                                               QUEUES
*********************************************************************************************************
*/
OS_Q PrioriteRouge;
void* prioriteRougeQueue[ROUGE_SIZE];

OS_Q PrioriteJaune;
void* prioriteJauneQueue[JAUNE_SIZE];

OS_Q PrioriteVert;
void* prioriteVertQueue[VERT_SIZE];


/*
*********************************************************************************************************
*                                              FLAGS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              SEMAPHORES
*********************************************************************************************************
*/
OS_SEM Timer1sSynchro;
OS_SEM Timer3sSynchro;
OS_SEM GpioSynchro;



/*
*********************************************************************************************************
*                                             ENUMERATIONS
*********************************************************************************************************
*/

enum Aeroport { YUL, YYZ, YVR, PEK, DBX, LGA, HND, LAX, CDG, AMS, NB_AEROPORTS };

/*
*********************************************************************************************************
*                                             STRUCTURES
*********************************************************************************************************
*/

typedef struct Avion {
	int id;
	int retard;
	enum Aeroport origine;
	enum Aeroport destination;
} Avion;

/*
*********************************************************************************************************
*                                             SHARED VAIRABLES
*********************************************************************************************************
*/
bool stopSimDebordement;
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void create_application();
int create_tasks();
int create_events();

void	generation(void* data);
void	atterrissage(void* data);
void    terminal(void* data);
void    decollage(void* data);
void	remplirAvion(Avion* avion);
void	statistiques(void* data);
void 	verification(void* data);

void gpio_isr_PRIOF(void* p_int_arg, CPU_INT32U source_cpu);
void fit_timer_3s(void* p_int_arg, CPU_INT32U source_cpu);
void fit_timer_1s(void* p_int_arg, CPU_INT32U source_cpu);

#endif /* SRC_SIMAVION_H_ */