#ifndef _SCI_H
#define _SCI_H

/* ----------- CONSTANTES SIMBÓLICAS ----------- */
#define TX_BUFFER_LENGTH 32
#define RX_BUFFER_LENGTH 32
/* ----- DECLARACIÓN DE VARIABLES GLOBALES ----- */

/* ---------- PROTOTIPOS DE FUNCIONES ---------- */
/* SCI_Init(): inicializa el módulo SCI. */
void SCI_Init(short);

/* SCI_Reset_TX_Buffer: resetea los índices de TX_Buffer. */
void SCI_Reset_TX_Buffer(void);

/* SCI_Reset_RX_Buffer: resetea los índices de RX_Buffer. */
void SCI_Reset_RX_Buffer(void);

/* SCI_Write_Char_To_TX_Buffer: escribe un caracter en TX_Buffer, solo si hay espacio. */
void SCI_Write_Char_To_TX_Buffer(char);

/* SCI_Write_Char_To_RX_Buffer: escribe un caracter en RX_Buffer, solo si hay espacio. */
void SCI_Write_Char_To_RX_Buffer(char);

/* SCI_Get_Char_From_TX_Buffer: obtiene un dato de TX_Buffer. */
char SCI_Get_Char_From_TX_Buffer(char*);

/* SCI_Get_Char_From_RX_Buffer: obtiene un dato de RX_Buffer. */
char SCI_Get_Char_From_RX_Buffer(char*);

/* SCI_Write_String_To_Buffer: escribe datos de 'string' en el buffer indicado por 
 * el contenido de la variable 'buff_type'. */
void SCI_Write_String_To_Buffer(char*, unsigned char);

/* SCI_Send_Char: envía un dato a SCID para ser transmitdo. */
void SCI_Send_Char(char);

/* SCI_Receive_Char: guarda un dato recibido de SCID a 'data'. */
char SCI_Receive_Char(char*);

/* SCI_TX_Handler: se ejecuta en el ISR de la interrupción por TDRE. */
void SCI_TX_Handler(void);

/* SCI_RX_Handler: se ejecuta en el ISR de la interrupción por RDRF. */
void SCI_RX_Handler(void);
/* --------------------------------------------- */

#endif

