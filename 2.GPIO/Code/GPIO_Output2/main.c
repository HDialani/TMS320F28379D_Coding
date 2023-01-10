/*****************************************************************************************************************
 * @Author:  Hitesh Dialani
 * @Date:    Dec-14-2022
 * @Version: 1.0
 *****************************************************************************************************************
 *@Details: Make GPIO 25 High to train programming microcontroller
 *****************************************************************************************************************
 */

#include "F28x_Project.h"     // Device Header File and Examples Include File
#include "device.h"
#include "driverlib.h"

void main(void){
    InitSysCtrl();                       //Initialize System Control
    DINT;                                //Disable CPU interrupts
    InitPieCtrl();                       //Initialize PIE control registers to their default state
    IER = 0x0000;                        //Disable CPU interrupts
    IFR = 0x0000;                        //Clear all CPU flags
    InitPieVectTable();                  //Initialize the PIE vector table
    EINT;                                // Enable Global interrupt INTM
    ERTM;                                // Enable Global realtime interrupt DBGM


    // Setting up the hardware
    EALLOW;

    GpioCtrlRegs.GPAGMUX2.bit.GPIO25=0;  // Setup as GPIO
    GpioCtrlRegs.GPAODR.bit.GPIO25=0;    // Push-Pull
    GpioCtrlRegs.GPADIR.bit.GPIO25=1;    // Output

    EDIS;

    // Register value
    GpioDataRegs.GPADAT.bit.GPIO25=1; //Initially ON

   // Idle loop
    while(1)
   {

   }
}
