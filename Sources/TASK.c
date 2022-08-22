#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MCUinit.h"
#include "SCI.h"
#include "TASK.h"
#include "TPM.h"

/* Si el comando es válido, el sistema responde con 'response' */
unsigned char response[6] = {0x02,0x02,0x01,0xAA,0x00,0x03};
unsigned char command[7];
unsigned short frequency;

/* -------------------------------- FUNCIONES -------------------------------- */

/* TASK_Get_Command: captura los comandos ingresados */
unsigned char TASK_Get_Command(){
	static char i = 0;
	char RX_data;
	/* No hay datos en RX_Buffer. */
	if (SCI_Get_Char_From_RX_Buffer(&RX_data) == 0)
		return 0;
	command[i++] = RX_data;
	/* Si recibí 'ETX' */
	if ((RX_data == 0x03) && (i == 6 || i == 7)){
		i = 0;
		SCI_Reset_RX_Buffer();
		return 1;
	}
	return 0;
}

/* TASK_Calculate_Checksum: calcula el cheksum */
unsigned char TASK_Calculate_Cheksum (unsigned char *array, unsigned char length){
	unsigned char CHKS_aux = 0x00, i = 0;
	while (i < length)
		CHKS_aux ^= array[i++];
	return CHKS_aux;
}

unsigned char TASK_Check_Frequency (){
	/* ¿La operación es 'Especificar Frecuencia'? */
	if (command[1] == 0x02){
		switch(command[2]){
		case 0x01:
			frequency = command[3];
			break;
		case 0x02:
			frequency = ((command[3] << 4) | command[4]);
			break;
		}
		/* ¿La frecuencia está entre 10Hz y 1000Hz? */
		if ((frequency >= 0x0A) && (frequency <= 0x3E8))
			return 1;
		else {
			frequency = 0;
			return 0;
		}
	/* ¿La operación es de encendido / apagado? */
	} else {
		if ((command[2] == 0x01) && (command[3] == 0x00))
			return 1;
		else
			return 0;
	}
}

unsigned char TASK_Check_Cheksum(){
	unsigned char CHKS, CHKS_aux;
	switch(command[2]){
	case 0x01:
		CHKS = command[4];
		CHKS_aux = TASK_Calculate_Cheksum(command,4);
		break;
	case 0x02:
		CHKS = command[5];
		CHKS_aux = TASK_Calculate_Cheksum(command,5);
		break;
	}
	if (CHKS == CHKS_aux){
		return 1;
	} else 
		return 0;
}

unsigned char TASK_Check_Command(){
	unsigned char Check_Cheksum, Check_Frequency;
	Check_Cheksum = TASK_Check_Cheksum();
	Check_Frequency = TASK_Check_Frequency(); 
	if ((Check_Cheksum == 1) && (Check_Frequency == 1)){
		response[1] = command[1];
		response[3] = 0xAA;
		response[4] = TASK_Calculate_Cheksum(response,4);
		return 1;
	} 
	else if (Check_Cheksum != 1)
		response[3] = 0xFF;
	else if (Check_Frequency != 1)
		response[3] = 0x55; 
	response[1] = command[1];
	response[4] = TASK_Calculate_Cheksum(response,4);
	return 0;
}

void TASK_Operate(){
	switch(command[1]){
	case 0x01:
		TPM_On();
		break;
	case 0x02:
		TPM_Generate(frequency);
		break;
	case 0x03:
		TPM_Off();
		break;
	}
}

void TASK_Process_Command(){
	/* Comprueba que el comando sea correcto */
	if (TASK_Check_Command() == 1)
		TASK_Operate();
	SCI_Write_String_To_Buffer(response,1);
}

/* --------------------------------------------------------------------------- */
