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
    InitSysCtrl();                                   //Initialize System Control
    DINT;                                            //Disable CPU interrupts
    InitPieCtrl();                                   //Initialize PIE control registers to their default state
    IER = 0x0000;                                    //Disable CPU interrupts
    IFR = 0x0000;                                    //Clear all CPU flags
    InitPieVectTable();                              //Initialize the PIE vector table
    EINT;                                            // Enable Global interrupt INTM
    ERTM;                                            // Enable Global realtime interrupt DBGM


    // Setting up the hardware
    EALLOW;

    GPIO_setPinConfig(GPIO_25_GPIO25);              // Setup as GPIO
    GPIO_setDirectionMode(25, GPIO_DIR_MODE_OUT);   // Setup as OUTPUT
    GPIO_setMasterCore(25, GPIO_CORE_CPU1);         // Setup as CPU1
    GPIO_setPadConfig(25, GPIO_PIN_TYPE_STD);       // Set as push-pull
    EDIS;

    // Register value
    GPIO_writePin(25, 1);  //HIGH

   // Idle loop
    while(1)
   {

   }
}
