// FILE:   Lab1_cpu01.c

#include "F28x_Project.h"     // Device Header File and Examples Include File

// Variables
Uint16 ToggleCount1 = 0;


void main(void)
{
// Initialize System Control
    InitSysCtrl();

// Initialize GPIO
    InitGpio();
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
    GPIO_SetupPinOptions(34, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(34, GPIO_MUX_CPU2, 0);
    EDIS;
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;    // Turn off LED

    // Disable CPU interrupts and initialize PIE control registers
    DINT;
    InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags
    IER = 0x0000;
    IFR = 0x0000;

// Initialize the PIE vector table
    InitPieVectTable();

// Enable global interrupts and higher priority real-time debug events
    EINT;          // Enable Global interrupt INTM
    ERTM;          // Enable Global realtime interrupt DBGM

// Idle loop
    for(;;)
    {
        GpioDataRegs.GPADAT.bit.GPIO31 = 0;		// Turn on LD2
       	DELAY_US(1000 * 500);
        GpioDataRegs.GPADAT.bit.GPIO31 = 1;		// Turn off LD2
       	DELAY_US(1000 * 500);
    	ToggleCount1++;
    }
}

// end of file
