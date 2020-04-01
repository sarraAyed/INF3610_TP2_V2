/*
*********************************************************************************************************
*                                                 uC/OS-III
*                                          The Real-Time Kernel
*                                               PORT Windows
*
*
*												Benjamin Heinen
*                                  Ecole Polytechnique de Montreal, Qc, CANADA
*                                                  05/2019
*
* File : exo4.c
*
*********************************************************************************************************
*/

// Main include of µC-III
#include  <cpu.h>
#include  <lib_mem.h>
#include  <os.h>

#include  "os_app_hooks.h"
#include  "app_cfg.h"
/*
*********************************************************************************************************
*                                              CONSTANTS
*********************************************************************************************************
*/

#define TASK_STK_SIZE       16384            // Size of each task's stacks (# of WORDs)

#define ROBOT_A_PRIO        8                // Defining Priority of each task
#define ROBOT_B_PRIO        9
#define CONTROLLER_PRIO     10


/*
*********************************************************************************************************
*                                             VARIABLES
*********************************************************************************************************
*/

CPU_STK           prepRobotAStk[TASK_STK_SIZE];  //Stack of each task
CPU_STK           prepRobotBStk[TASK_STK_SIZE];
CPU_STK           controllerStk[TASK_STK_SIZE];


OS_TCB robotATCB;
OS_TCB robotBTCB;
OS_TCB controllerTCB;

/*
*********************************************************************************************************
*                                           SHARED  VARIABLES
*********************************************************************************************************
*/

// Utiliser des sémaphores au besoin

OS_MUTEX total_prep_time_mutex;;

OS_Q Q_controller_to_robot_A;
void* A_prep_time_msg[10];

OS_Q Q_robot_A_to_robot_B;
void* B_T1_prep_time_msg[10];


volatile int total_prep_time = 0;
int controller_done = 0;
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void    robotA(void* data);
void    robotB(void* data);
void    controller(void* data);
void    errMsg(OS_ERR err, char* errMSg);
int     readCurrentTotalPrepTime();
void    writeCurrentTotalPrepTime(int qty);

/*
*********************************************************************************************************
*                                             STRUCTURES
*********************************************************************************************************
*/

typedef struct work_data {
	int work_data_a;
	int work_data_b;
} work_data;

/*
*********************************************************************************************************
*                                                  MAIN
*********************************************************************************************************
*/

void main(void)
{
	OS_ERR err;


	/* TODO : Initialiser, creer les taches et demarer */

	return;
}

/*
*********************************************************************************************************
*                                            TASK FUNCTIONS
*********************************************************************************************************
*/

void doWorkRobotA(work_data workData, int orderNumber, int startTime)
{
	OS_ERR err;
	CPU_TS ts;
	

	/* TODO : Envoi de message à Robot B*/

	/* TODO : Proteger ce bloc avec un mutex*/
	int current = readCurrentTotalCount();
	writeCurrentTotalCount(current + itemCount);
		
	/* TODO : Faire l'attente active */
		
	printf("ROBOT A COMMANDE #%d avec %d items @ %d.\n", orderNumber, itemCount, OSTimeGet(&err) - startTime);

	// Synchronisation si requise (à justifier)

	orderNumber++;
}
void robotA(void* data)
{
	OS_ERR err;
	CPU_TS ts;
	int startTime = 0;
	int orderNumber = 1;
	work_data* workData;
	OS_MSG_SIZE msg_size;
	printf("%d: TACHE PREP_ROBOT_A @ %d : DEBUT.\n", OSTimeGet(&err) - startTime);

	while (1)
	{
		

		/* TODO : Recuperer la quantite*/
		
		doWorkRobotA(*workData, orderNumber, startTime);


		/* TODO : Liberer la memoire*/

	}
}

void robotB(void* data)
{
	OS_ERR err;
	CPU_TS ts;
	OS_MSG_SIZE msg_size;

	int startTime = 0;
	int orderNumber = 1;
	int* robotBPrepTime;
	printf("%d : TACHE PREP_ROBOT_B @ %d : DEBUT. \n", OSPrioCur, OSTimeGet(&err) - startTime);

	while (1)
	{
		/* TODO : Recuperer la quantite */
		
		/* TODO : Proteger ce bloc avec un mutex*/
		int current = readCurrentTotalCount();
		writeCurrentTotalCount(current + itemCount);
		
		/* TODO : Faire l'attente active */
		
		printf("ROBOT B COMMANDE #%d avec %d items @ %d.\n", orderNumber, itemCount, OSTimeGet(&err) - startTime);

		/* TODO : Synchronisation si requise (à justifier) */
		
		orderNumber++;

	}
}

void controller(void* data)
{
	OS_ERR err;
	CPU_TS ts;

	int startTime = 0;
	int randomTime = 0;
	work_data* workData;
	printf("TACHE CONTROLLER @ %d : DEBUT. \n", OSTimeGet(&err) - startTime);
	while (1)
	{
		for (int i = 1; i < 12; i++)
		{
			
			workData = malloc(sizeof(work_data));

			workData->work_data_a = (rand() % 7 + 1);
			workData->work_data_b = (rand() % 6 + 2);
			
			printf("TACHE CONTROLLER @ %d : COMMANDE #%d. \n prep time A = %d, prep time B = %d\n", OSTimeGet(&err) - startTime, i, workData->work_data_a, workData->work_data_b);

			/* TODO :  Envoi de la commande */
			
		    // Délai aléatoire avant nouvelle commande
               randomTime = (rand() % 9 + 5) * 4;
               OSTimeDly(randomTime, OS_OPT_TIME_DLY, &err);
			

		}
	}
}

int readCurrentTotalPrepTime()
{
	OS_ERR err;

	/*TODO : Effectuer un delai d'une duree de 2 ticks*/
	return total_prep_time;
}
void writeCurrentTotalPrepTime(int newCount)
{
	OS_ERR err;

	/*TODO : Effectuer un delai d'une duree de 2 ticks*/
	total_prep_time = newCount;
}

void errMsg(OS_ERR err, char* errMsg)
{
	if (err != OS_ERR_NONE)
	{
		printf(errMsg);
		exit(1);
	}
}