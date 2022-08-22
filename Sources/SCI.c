#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MCUinit.h"
#include "SCI.h"
#include "TASK.h"
#include "TPM.h"

volatile unsigned char TX_read_index = 0, TX_write_index = 0;
volatile unsigned char RX_read_index = 0, RX_write_index = 0;
char TX_Buffer[TX_BUFFER_LENGTH];
char RX_Buffer[RX_BUFFER_LENGTH];

/* -------------------------------- FUNCIONES -------------------------------- */

/* SCI_Reset_RX_Buffer: resetea los índices de RX_Buffer. */
void SCI_Reset_RX_Buffer(){
	RX_read_index = 0;
	RX_write_index = 0;
}

/* SCI_Reset_TX_Buffer: resetea los índices de TX_Buffer. */
void SCI_Reset_TX_Buffer(){
	TX_read_index = 0;
	TX_write_index = 0;
}

/* SCI_Init(): inicializa el módulo SCI. */
void SCI_Init(short baud){
	/* SCIC2: TIE=0,TCIE=0,RIE=0,ILIE=0,TE=0,RE=0,RWU=0,SBK=0 */
	SCIC2 = 0x00U;			/* Disable the SCI module */
	(void)(SCIS1 == 0U);	/* Dummy read of the SCIS1 register to clear flags */
	(void)(SCID == 0U);		/* Dummy read of the SCID register to clear flags */
	/* SCIS2: LBKDIF=1,RXEDGIF=1,RXINV=0,RWUID=0,BRK13=0,LBKDE=0,RAF=0 */
	SCIS2 = 0xC0U;                                      
	/* SCIBDH: LBKDIE=0,RXEDGIE=0,SBR12=0,SBR11=0,SBR10=0,SBR9=0,SBR8=0 */
	SCIBDH = 0x00U; 
	if (baud == 9600){
		/* SCIBDL: SBR7=0,SBR6=0,SBR5=1,SBR4=1,SBR3=0,SBR2=1,SBR1=0,SBR0=0 */
		SCIBDL = 0x34U;  
	}
	/* SCIC1: LOOPS=0,SCISWAI=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
	SCIC1 = 0x00U;                                      
	/* SCIC3: R8=0,T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
	SCIC3 = 0x00U;                                      
	/* SCIC2: TIE=0,TCIE=0,RIE=1,ILIE=0,TE=1,RE=1,RWU=0,SBK=0 */
	SCIC2 = 0x2CU;
	SCI_Reset_RX_Buffer();
}

/* SCI_Write_Char_To_TX_Buffer: escribe un caracter en TX_Buffer, solo si hay espacio. */
void SCI_Write_Char_To_TX_Buffer(char data){
	if (TX_write_index < TX_BUFFER_LENGTH){
		TX_Buffer[TX_write_index] = data;
		TX_write_index++;
	} //else
		//Error_code = ERROR_UART_FULL_BUFF;
}

/* SCI_Write_Char_To_RX_Buffer: escribe un caracter en RX_Buffer, solo si hay espacio. */
void SCI_Write_Char_To_RX_Buffer(char data){
	if (RX_write_index < RX_BUFFER_LENGTH){
		RX_Buffer[RX_write_index] = data;
		RX_write_index++;
	} //else
		//Error_code = ERROR_UART_FULL_BUFF;
}

/* SCI_Get_Char_From_TX_Buffer: obtiene un dato de TX_Buffer. */
char SCI_Get_Char_From_TX_Buffer(char* data){
	/* ¿Hay dato nuevo en el buffer? */
	if (TX_read_index < TX_write_index){
		*data = TX_Buffer[TX_read_index];
		TX_read_index++;
		return 1;
	} else 
		return 0;	/* No hay dato nuevo en el buffer. */
}

/* SCI_Get_Char_From_RX_Buffer: obtiene un dato de RX_Buffer. */
char SCI_Get_Char_From_RX_Buffer(char* data){
	/* ¿Hay dato nuevo en el buffer? */
	if (RX_read_index < RX_write_index){
		*data = RX_Buffer[RX_read_index];
		RX_read_index++;
		return 1;
	} else {
		//SCI_Reset_RX_Buffer();
		return 0;	/* No hay dato nuevo en el buffer. */
	}
}

/* SCI_Write_String_To_Buffer: escribe datos de 'string' en el buffer indicado por 
 * el contenido de la variable 'buff_type'. */
void SCI_Write_String_To_Buffer(char * string, unsigned char buff_type){
	switch(buff_type){
	/* RX */
	case 0:
		while (*string != '\0'){
			SCI_Write_Char_To_RX_Buffer(*string);
			string++;
		}
		break;
	/* TX */
	case 1:
		while (*string != '\0'){
			SCI_Write_Char_To_TX_Buffer(*string);
			string++;
		}
		SCIC2_TIE = 1;	/* Habilito la interrupcion del TX. */
		break;
	}
}

/* SCI_Send_Char: envía un dato a SCID para ser transmitdo. */
void SCI_Send_Char(char data){
	/* Cuando el registro SCIS1_TDRE = 1, el registro de datos SCID está vacío y se 
	 * puede escribir un dato para transmitir. */
	while(SCIS1_TDRE == 0);
	SCID = data;
}

/* SCI_Receive_Char: guarda un dato recibido de SCID en "data". */
char SCI_Receive_Char(char *data){
	/* Cuando el registro SCIS1_TDRF = 1, se indica que se ha recibido un dato el 
	 * cual se encuentra en SCID. */
	if (SCIS1_RDRF == 1){
		*data = SCID;
		return 1;
	} else
		return 0;
}

/* SCI_TX_Handler: se ejecuta en el ISR de la interrupción por TDRE. */
void SCI_TX_Handler(){
	/* ¿Hay datos para transmitir en el buffer TX? */
	if (TX_read_index < TX_write_index){
		SCI_Send_Char(TX_Buffer[TX_read_index]);
		TX_read_index++;
	} else {
		SCI_Reset_TX_Buffer();
		SCIC2_TIE = 0;	/* Deshabilito interrupcion de TX */
	}
}

/* SCI_RX_Handler: se ejecuta en el ISR de la interrupción por RDRF. */
void SCI_RX_Handler(){
	char data;
	/* ¿Se recibió un dato? */
	if (SCI_Receive_Char(&data) != 0){
		/* Guardo el dato en RX_Buffer */
		SCI_Write_Char_To_RX_Buffer(data);
	}
}

/* --------------------------------------------------------------------------- */



