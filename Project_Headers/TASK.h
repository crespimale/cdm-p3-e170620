#ifndef _TASK_H
#define _TASK_H

/* ---------- PROTOTIPOS DE FUNCIONES ---------- */
unsigned char TASK_Get_Command(void);
unsigned char TASK_Calculate_Cheksum(unsigned char*, unsigned char);
unsigned char TASK_Check_Frequency ();
unsigned char TASK_Check_Command();
void TASK_Process_Command(void);
void TASK_Operate();
/* --------------------------------------------- */

#endif
