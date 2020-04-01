/*
*********************************************************************************************************
*                                                 uC/OS-III
*                                          The Real-Time Kernel
*                                               PORT Windows
*
*
*												Guy Bois
*                                  Ecole Polytechnique de Montreal, Qc, CANADA
*                                                  28/01/2020
*
* File : exo2.c
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

#define ROBOT_A_PRIO        8               // Defining Priority of each task
#define ROBOT_B_PRIO        9
#define CONTROLLER_PRIO     7


#define ROBOT_A_READY  0x01
#define ROBOT_B_READY  0x02
#define ROBOT_A_DONE   0x04
#define ROBOT_B_DONE   0x08
#define COMMAND_READY  0x10


/*
*********************************************************************************************************
*                                             VARIABLES
*********************************************************************************************************
*/

CPU_STK           robotAStk[TASK_STK_SIZE];  //Stack of each task
CPU_STK           robotBStk[TASK_STK_SIZE];
CPU_STK           controllerStk[TASK_STK_SIZE];

OS_TCB robotATCB;
OS_TCB robotBTCB;
OS_TCB controllerTCB;


/*
*********************************************************************************************************
*                                           SHARED  VARIABLES
*********************************************************************************************************
*/
//OS_SEM sem_controller_to_robot_A;
//OS_SEM sem_robot_A_to_robot_B;
//OS_SEM sem_robot_B_to_controller;

OS_MUTEX total_item_cout_mutex;
OS_FLAG_GRP flags;

volatile int total_item_count = 0;

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void    robotA(void* data);
void    robotB(void* data);
void    controller(void* data);
void    errMsg(OS_ERR err, char* errMSg);
int     readCurrentTotalCount();
void    writeCurrentTotalCount(int qty);

/*
*********************************************************************************************************
*                                                  MAIN
*********************************************************************************************************
*/

void main(void)
{
	OS_ERR err;

	CPU_IntInit();

	Mem_Init();                                                 // Initialize Memory Managment Module                   
	CPU_IntDis();                                               // Disable all Interrupts                               
	CPU_Init();                                                 // Initialize the uC/CPU services                       

	OSInit(&err);                                            // Initialize uC/OS-III                                 
	if (err != OS_ERR_NONE) {
		while (1);
	}

	App_OS_SetAllHooks();                                       // Set all applications hooks                      

	/* TODO : Creer Mutex au besoin*/
	/* TODO : Creer Flags*/

	/* TODO : Creer tache */
	/* TODO : Start */


	if (err == OS_ERR_NONE)
	{
		printf("End of task creation ! \n");
		OSStart(&err);                                          //Start multitasking (i.e. give control to uC/OS-III)
	}
	else
	{
		printf("Error while creating tasks !");
	}
	
	while (DEF_ON);

	return;
}

/*
*********************************************************************************************************
*                                            TASK FUNCTIONS
*********************************************************************************************************
*/


void robotA(void* data)
{
	OS_ERR err;
	CPU_TS ts;
	OS_TICK actualticks = 0;

	int startTime = 0;
	int orderNumber = 1;
	int itemCount;
	printf("ROBOT A @ %d : DEBUT.\n", OSTimeGet(&err) - startTime);
	while (DEF_ON)
	{

		OSFlagPost(&flags, ROBOT_A_READY, OS_OPT_POST_FLAG_SET, &err);
		errMsg(err, "flags");
		
		// À compléter avec fonctionalité similaire à exo2 mais avec flags plutôt que sémaphore
		
		
		// En terminant le corps de boucle on doit donner la mains à robotB 
	}

}

void robotB(void* data)
{
	OS_ERR err;	
	CPU_TS ts;
	OS_TICK actualticks = 0;

	int startTime = 0;
	int orderNumber = 1;
	int itemCount;
	printf("ROBOT B @ %d : DEBUT. \n", OSTimeGet(&err) - startTime);
	while (DEF_ON)
	{
		
		OSFlagPost(&flags, ROBOT_B_READY, OS_OPT_POST_FLAG_SET, &err);
		errMsg(err, "flags");
		
		// À compléter avec fonctionalité similaire à exo2 mais avec flags plutôt que sémaphore
		
		// En terminant le corps de boucle on doit donner la main à controleur
	}
}

void controller(void* data)
{
	OS_ERR err;
	CPU_TS ts;
	
	int startTime = 0;
	int randomTime = 0;
	printf("CONTROLLER @ %d : DEBUT. \n", OSTimeGet(&err) - startTime);
	for (int i = 1; i < 11; i++)
	{
		
		OSFlagPend(&flags, ROBOT_A_READY + ROBOT_B_READY, 0, OS_OPT_PEND_FLAG_SET_ALL, &ts, &err);
		errMsg(err, "flags");
		
		// À compléter

	}
}

int readCurrentTotalCount()
{
	OS_ERR err;
	/*TODO : Effectuer un delai d'une duree de 2 ticks*/
	return total_item_count;
}
void writeCurrentTotalCount(int newCount)
{
	OS_ERR err;
	/*TODO : Effectuer un delai d'une duree de 2 ticks*/
	total_item_count = newCount;
}
void errMsg(OS_ERR err, char* errMsg)
{
	if (err != OS_ERR_NONE)
	{
		printf(errMsg);
		printf("%d", err);
		while (DEF_ON);
	}
}