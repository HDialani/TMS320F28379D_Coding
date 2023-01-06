Here I explain the GPIO function. First a general pinout, then how to enable a specific pinout.

# Hardware pinout

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
