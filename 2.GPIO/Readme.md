Here I explain the GPIO function. First a general pinout, then how to enable a specific pinout.

# External pinout

The LAUNCHXL-F28379D uses a TMS320F28379DZWTT pinout, the ZWTT means it is a BGA pinout. Below shows how the chip looks like



Physical chip             |  CAD pinout
:-------------------------:|:-------------------------:
<img src= "Images/BGA/ZWTT_IC.jfif" width=300 >  |  <img src= "Images/BGA/ZWTT_IC_pin.jpg" width=300 >

For those interested these are the pinouts. 

 Left                                             |  Right
:-------------------------:                       |:-------------------------:
<img src= "Images/BGA/Quadrant_A.jpg" width=300>  |  <img src= "Images/BGA/Quadrant_B.jpg" width=300 >
<img src= "Images/BGA/Quadrant_D.jpg" width=300 > |  <img src= "Images/BGA/Quadrant_C.jpg" width=300 >

Each GPIO pin could have different application depending on which multiplexer is used. For detailed explanation look at 
[Table 4-1. Signal Descriptions, Page 20-41](https://github.com/HDialani/TMS320F28379D_Coding/blob/main/Resources/tms320f28379d_datasheet.pdf)

# GPIO setup

Now to the software side. Below show the F2837xD GPIO Pin Block Diagram. Yes I know it looks scary, but I will to explain it. 
 
<img src= "Images/Pins/GPIO_Pin_Block_Diagram.jpg" width=400 >

For those interested you can read TI's explation here 
[Page 99](https://github.com/HDialani/TMS320F28379D_Coding/blob/main/Resources/WorkshopManual.pdf)


First is the GPxPUD. This is to enable (GPxPUD=0;) or disable (GPxPUD=1;) the internal pull-up resistor. For those not familiar with digital electronics design the pull-up resistor need the resistor for current limiting when states change and
to make sure that there is no floating state. For more detailed explanation [read this](https://circuitdigest.com/tutorial/pull-up-and-pull-down-resistor).
 
Next is GPxDIR. This sets the direction of the GPIO. GPxDIR=1; means output GPIO and GPxDIR=0; means input GPIO

Next is GPxODR it sets up the configuration. Normal aka Push-Pull(Totem Pole) or Open drain. Normal mode is commonly used since it switches faster and uses less power. Open drain is prefered for multi-device connection.
If interested read [1](https://cotorelay.com/wp-content/uploads/2019/12/Push-Pull-vs.-Open-Drain-Output-How-to-Choose.pdf), [2](https://open4tech.com/open-drain-output-vs-push-pull-output/), [3](https://electronics.stackexchange.com/questions/620150/difference-between-open-drain-and-push-pull-modes)
  
Next is GPxINV. It select if you want an inverted signal GPxINV=1; or non-inverted signal GPxINV=0; This saves adding an inverter. 


Next is GPxINV. It select if you want an inverted signal GPxINV=1; or non-inverted signal GPxINV=0; This saves adding an inverter. 


Next is GPxCTRL and GPxQSEL1/2. These effect the input qualification. Input qualification is usefull in remove noises from measurements. It does this by takin samples. Look at the figure below
<img src= "Images/Pins/Input_Qualification.jpg" width=400 >

GPxCTRL sets sampling period and GPxQSEL1/2 selects which registers(Will explain register selection in next part)

GPxCSEL1-4 lets you select which core is being used. The options are CPU1.CLA can run in parallel to CPU1. Same with CPU2.CLA. 

Finally are the GPxGMUX1/2 and GPxMUX1/2. These will be explained in GPIO selection. GPxDAT(R) is a setting parameter which will also be explained in GPIO selection

# GPIO selection


<img src= "Images/Pins/GPIO_Grouping.jpg" width=400 >