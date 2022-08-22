#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MCUinit.h"
#include "SCI.h"
#include "TASK.h"
#include "TPM.h"

static unsigned short Nc;
/* Estado actual del sistema */
type_system_state system_state; 

/* -------------------------------- FUNCIONES -------------------------------- */
unsigned short TPM_Get_Nc(){
	return Nc;
}

void TPM_Init(){
	/* ### Init_TPM init code */
	(void)(TPM1C1SC == 0U);		/* Channel 0 int. flag clearing (first part) */
	/* TPM1C1SC: CH1F=0,CH1IE=1,MS1B=0,MS1A=1,ELS1B=0,ELS1A=1 */
	TPM1C1SC = 0x54U;			/* Int. flag clearing (2nd part) and channel 0 contr. 
									register setting */
	TPM1C1V = 0x00U;			/* Compare 0 value setting */
	/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
	TPM1SC = 0x00U; 			/* Stop and reset counter */
	TPM1MOD = 0x00U;			/* Period value setting */
	(void)(TPM1SC == 0U);		/* Overflow int. flag clearing (first part) */
	/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=1,PS0=0 */
	Nc = 0;
	system_state = OFF;
}

void TPM_On(){
	if (Nc > 0){
		TPM1SC_CLKSB = 0x00;
		TPM1SC_CLKSA = 0x01;
		system_state = ON;
	}
}

void TPM_Generate(unsigned short freq){
	unsigned short prediv;
	/* Selecciono predivisor adecuado. */
	if ((freq >= 0x0A) && (freq <= 0x0F))
		prediv = 0x08;
	else if (freq > 0x0F)
		prediv = 0x04;
	/* Cuenta: 8MHz / 2 * prediv * frequency */
	Nc = BUS_CLK / (2 * prediv * freq);
}

void TPM_Off(){
	if ((Nc > 0) && (system_state == ON)){
		TPM1SC_CLKSB = 0x00;
		TPM1SC_CLKSA = 0x00;
		Nc = 0;
		system_state = OFF;
	}
}

void TPM_CH1_Handler(){
	TPM1C1V += TPM_Get_Nc();
	/* El flag CH1F se limpia leyéndolo y escribiendo 0 */ 
	TPM1C1SC;
	TPM1C1SC_CH1F = 0;
}

/* --------------------------------------------------------------------------- */
