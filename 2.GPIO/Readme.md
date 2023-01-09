Here I explain the GPIO function. First a general pinout, then how to enable a specific pinout.

# External pinout

The LAUNCHXL-F28379D uses a TMS320F28379DZWTT pinout, the ZWTT means it is a BGA pinout. Below shows how the chip looks like


Physical chip             |  CAD pinout
:-------------------------:|:-------------------------:
<img src= "Images/BGA/ZWTT_IC.jfif" width=300 >  |  <img src= "Images/BGA/ZWTT_IC_pin.jpg" width=300 >


For those interested these are the pinouts. 

 Left                                             |  Right
:-------------------------:                       |:-------------------------:
<img src= "Images/BGA/Quadrant_A.jpg" width=500>  |  <img src= "Images/BGA/Quadrant_B.jpg" width=500 >
<img src= "Images/BGA/Quadrant_D.jpg" width=500 > |  <img src= "Images/BGA/Quadrant_C.jpg" width=500 >

Each GPIO pin could have different application depending on which multiplexer is used. For detailed explanation look at 
[Table 4-1. Signal Descriptions, Page 20-41](https://github.com/HDialani/TMS320F28379D_Coding/blob/main/Resources/tms320f28379d_datasheet.pdf)

# GPIO setup

Now to the software side. Below show the F2837xD GPIO Pin Block Diagram. Yes I know it looks scary, but I will to explain it. 
<p align="center">
 <img src= "Images/Pins/GPIO_Pin_Block_Diagram.jpg" width=600 >
</p>
For those interested you can read TI's explation here 
[Page 99](https://github.com/HDialani/TMS320F28379D_Coding/blob/main/Resources/WorkshopManual.pdf)


- First is the GPxPUD. This is to enable (GPxPUD=0;) or disable (GPxPUD=1;) the internal pull-up resistor. For those not familiar with digital electronics design the pull-up resistor need the resistor for current limiting when states change and
to make sure that there is no floating state. For more detailed explanation [read this](https://circuitdigest.com/tutorial/pull-up-and-pull-down-resistor).
 
- Next is GPxDIR. 
This sets the direction of the GPIO. GPxDIR=1; means output GPIO and GPxDIR=0; means input GPIO

- Next is GPxODR. 
it sets up the configuration. Normal aka Push-Pull(Totem Pole) or Open drain. Normal mode is commonly used since it switches faster and uses less power. Open drain is prefered for multi-device connection.
If interested read [1](https://cotorelay.com/wp-content/uploads/2019/12/Push-Pull-vs.-Open-Drain-Output-How-to-Choose.pdf), [2](https://open4tech.com/open-drain-output-vs-push-pull-output/), [3](https://electronics.stackexchange.com/questions/620150/difference-between-open-drain-and-push-pull-modes)
  
- Next is GPxINV. 
It select if you want an inverted signal GPxINV=1; or non-inverted signal GPxINV=0; This saves adding an inverter. 


- Next is GPxCTRL and GPxQSEL1/2. 
These effect the input qualification. Input qualification is usefull in remove noises from measurements. It does this by takin samples. Look at the figure below

<p align="center">
 <img src= "Images/Pins/Input_Qualification.jpg" width=400 >
<p>

- GPxCTRL sets sampling period and GPxQSEL1/2 selects which registers(Will explain register selection in next part)

- GPxCSEL1-4 lets you select which core is being used. The options are CPU1.CLA can run in parallel to CPU1. Same with CPU2.CLA. 

- Finally are the GPxGMUX1/2 and GPxMUX1/2. These will be explained in GPIO selection. GPxDAT(R) is a setting parameter which will also be explained in GPIO selection

# GPIO selection

This micro controller has 337 pins, but not all can be used some are POWER and GND. This leaves 192 pins over. Sadly I am using the Lauchpad and not the Controlcard so I have even less pins over <80. Below shows the how the 192 pins are dived 

<p align="center">
 <img src= "Images/Pins/GPIO_Grouping.jpg" width=600 >
<p>

<div align="center">

| GPIO number   | Port letter   | MUX |
| ------------- |:-------------:| -----:|
| GPIO 0-15     | A             | MUX1 |
| GPIO 16-31    | A             | MUX2 |
| GPIO 32-47    | B             | MUX1 |
| GPIO 48-63    | B             | MUX2 |
| GPIO 64-79    | C             | MUX1 |
| GPIO 80-95    | C             | MUX2 |
| GPIO 96-111   | D             | MUX1 |
| GPIO 112-127  | D             | MUX2 |
| GPIO 128-143  | E             | MUX1 |
| GPIO 144-159  | E             | MUX2 |
| GPIO 160-175  | F             | MUX1 |
| GPIO 176-191  | F             | MUX2 |

</div>

# Software

## Setting up the C.main

Lets start building up the code step by step. First starting off with an almost blank code. 

```C
/*****************************************************************************************************************
 * @Author:  Hitesh Dialani
 * @Date:    Dec-14-2022
 * @Version: 1.0
 *****************************************************************************************************************
 *@Details:  
 *****************************************************************************************************************
 */
    void main(void)
    {

    }

```

Only code inside of `void main(void){ }` will execute. Like any C code libraries are needed.

```C
/*****************************************************************************************************************
 * @Author:  Hitesh Dialani
 * @Date:    Dec-14-2022
 * @Version: 1.0
 *****************************************************************************************************************
 *@Details: 
 *****************************************************************************************************************
 */
    #include "F28x_Project.h"    
    #include "device.h"
    #include "driverlib.h"
    
    void main(void)
    {

    }

```

These new libraries will make setting up the microcontroller much easier. 

Now I haven't explained how to setup the hardware for programming yet. For example when you turn on a computer all you do is press the ON button, but the computer needs to setup a lot of things in the background inorder for you to do anything. I will first give you the code needed inorder to setup the microcontroller then will try to explain why this is needed.

```C
/*****************************************************************************************************************
 * @Author:  Hitesh Dialani
 * @Date:    Dec-14-2022
 * @Version: 1.0
 *****************************************************************************************************************
 *@Details:  
 *****************************************************************************************************************
 */
    #include "F28x_Project.h"    
    #include "device.h"
    #include "driverlib.h"
    
    void main(void)
    {
    InitSysCtrl();       //Initialize System Control
    DINT;                //Disable CPU interrupts
    InitPieCtrl();       //Initialize PIE control registers to their default state
    IER = 0x0000;        //Disable CPU interrupts
    IFR = 0x0000;        //Clear all CPU flags
    InitPieVectTable();  //Initialize the PIE vector table
    EINT;                // Enable Global interrupt INTM
    ERTM;                // Enable Global realtime interrupt DBGM
    
    }

```

I will start with the `InitSysCtrl();` In Code Composer Studio do CTRL+Left Mouse Click to follow a function. When I do that I get  

```C
void InitSysCtrl(void)
{
    //
    // Disable the watchdog
    //
    DisableDog();

#ifdef _FLASH
    //
    // Copy time critical code and Flash setup code to RAM. This includes the
    // following functions: InitFlash()
    //
    // The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    InitFlash();
#endif

    //
    //      *IMPORTANT*
    //
    // The Device_cal function, which copies the ADC & oscillator calibration
    // values from TI reserved OTP into the appropriate trim registers, occurs
    // automatically in the Boot ROM. If the boot ROM code is bypassed during
    // the debug process, the following function MUST be called for the ADC and
    // oscillators to function according to specification. The clocks to the
    // ADC MUST be enabled before calling this function.
    //
    // See the device data manual and/or the ADC Reference Manual for more
    // information.
    //
#ifdef CPU1
    EALLOW;

    //
    // Enable pull-ups on unbonded IOs as soon as possible to reduce power
    // consumption.
    //
    GPIO_EnableUnbondedIOPullups();

    //
    // Check if the device is trimmed
    //
    if((DevCfgRegs.PARTIDL.bit.QUAL == 0x0) &&
       (AnalogSubsysRegs.ANAREFTRIMA.all == 0x0))
    {
        ConfigureTMXAnalogTrim();
    }

    EDIS;

    //
    // Initialize the PLL control: SYSPLLMULT and SYSCLKDIVSEL.
    //
    // Defined options to be passed as arguments to this function are defined
    // in F2837xD_Examples.h.
    //
    // Note: The internal oscillator CANNOT be used as the PLL source if the
    // PLLSYSCLK is configured to frequencies above 194 MHz.
    //
    //  PLLSYSCLK = (XTAL_OSC) * (IMULT + FMULT) / (PLLSYSCLKDIV)
    //
#ifdef _LAUNCHXL_F28379D
    InitSysPll(XTAL_OSC,IMULT_40,FMULT_0,PLLCLK_BY_2);
#else
    InitSysPll(XTAL_OSC, IMULT_20, FMULT_0, PLLCLK_BY_2);
#endif // _LAUNCHXL_F28379D

#ifndef _FLASH
    //
    // Call Device_cal function when run using debugger
    // This function is called as part of the Boot code. The function is called
    // in the InitSysCtrl function since during debug time resets, the boot code
    // will not be executed and the gel script will reinitialize all the
    // registers and the calibrated values will be lost.
    //
    Device_cal();
#endif
#endif // CPU1

    //
    // Turn on all peripherals
    //
    InitPeripheralClocks();
}
```
If you do CTRL+Left Mouse Click on `DisableDog();` you get 
```C
//
// DisableDog - This function disables the watchdog timer.
//
void DisableDog(void)
{
    volatile Uint16 temp;

    //
    // Grab the clock config first so we don't clobber it
    //
    EALLOW;
    temp = WdRegs.WDCR.all & 0x0007;
    WdRegs.WDCR.all = 0x0068 | temp;
    EDIS;
}
```
So as you if you try to follow the software inorder to understand what is happening you become depressed very fast. 
Thanks to those libraries all you need to write is `InitSysCtrl();` and it does the rest.


EXPLANATION STILL MISSING !!!!!!! 

## Setting up GPIO as output

I will write a code to make GPIO 25 HIGH. To show that it works I will connect that pin to an LED.  The setup is shown below

First the general C code with all the setting up and enabling set.

```C
/*****************************************************************************************************************
 * @Author:  Hitesh Dialani
 * @Date:    Dec-14-2022
 * @Version: 1.0
 *****************************************************************************************************************
 *@Details: Make GPIO 25 High to train programming microcontroller
 *****************************************************************************************************************
 */
    #include "F28x_Project.h"    
    #include "device.h"
    #include "driverlib.h"
    
    void main(void)
    {
    InitSysCtrl();       //Initialize System Control
    DINT;                //Disable CPU interrupts
    InitPieCtrl();       //Initialize PIE control registers to their default state
    IER = 0x0000;        //Disable CPU interrupts
    IFR = 0x0000;        //Clear all CPU flags
    InitPieVectTable();  //Initialize the PIE vector table
    EINT;                // Enable Global interrupt INTM
    ERTM;                // Enable Global realtime interrupt DBGM
    
    }

```

There are 2 things I need to do. First I need to setup GPIO 25 to be an output and. Second thing is I need to make the GPIO HIGH. 
I will first give the code then I will explain. 

```C
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
    GpioCtrlRegs.GPADIR.bit.GPIO25=0;    // Output

    EDIS;

    // Register value
    GpioDataRegs.GPADAT.bit.GPIO25=1; //Initially ON

   // Idle loop
    while(1)
   {

   }
}

```

As you can see from the picture below it works.

//

Everything between `EALLOW;` and `EDIS;` is for setting up that specific pin to be an GPIO output. The `GpioCtrlRegs`sets the required muxing. The `GpioDataRegs` sets the output value of the register. Once the specific pin is set as an GPIO there are 4 commands that can effect the output value of that pin. They are shown below with an explanation as to what they do.

<div align="center">

| Register   |For OUTPUT  |
| ------------- |:-------------:|
| GP?DAT    | GPXDAT.bit.GPIO? = 1. Sets output HIGH. <br />GPXDAT.bit.GPIO? = 0. Sets output LOW|
| GP?SET    | GPXSET.bit.GPIO? = 1. Sets output HIGH. <br />GPXSET.bit.GPIO? = 0. Does nothing|
| GP?CLEAR  | GPXCLEAR.bit.GPIO? = 1. Sets output LOW.<br />GPXCLEAR.bit.GPIO? = 0. Does nothing|
| GP?TOGGLE    | GPXTOGGLE.bit.GPIO? = 1. Changes the to its inverse. <br />GPXSET.bit.GPIO? = 0. Does nothing|

</div>


