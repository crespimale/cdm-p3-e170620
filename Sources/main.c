#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MCUinit.h"
#include "SCI.h"
#include "TASK.h"
#include "TPM.h"

#ifdef __cplusplus
extern "C"
#endif

void MCU_Init(void); /* Device initialization function declaration */

void main(void) {
	MCU_Init();
	SCI_Init(9600);
	TPM_Init();
	for(;;) {
		if (TASK_Get_Command() == 1){
			TASK_Process_Command();
		}
	}
}



