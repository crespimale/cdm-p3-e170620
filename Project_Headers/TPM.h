#ifndef _TPM_H
#define _TPM_H

/* ----------- CONSTANTES SIMB�LICAS ----------- */
#define BUS_CLK 0x7A1200
/* ----------- DECLARACI�N DE TIPOS ------------ */
typedef enum {
	ON, 
	OFF
} type_system_state;
/* ---------- PROTOTIPOS DE FUNCIONES ---------- */
unsigned short TPM_Get_Nc(void);
void TPM_Init(void);
void TPM_Generate(unsigned short);
void TPM_On(void);
void TPM_Off(void);
void TPM_CH1_Handler(void);
/* --------------------------------------------- */

#endif
