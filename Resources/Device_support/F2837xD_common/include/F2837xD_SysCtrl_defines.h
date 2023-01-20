//###########################################################################
//
// FILE:	F2837xD_SysCtrl_defines.h
//
// TITLE:	F2837xD LPM support definitions
//
//###########################################################################
// $TI Release: F2837xD Support Library v200 $
// $Release Date: Tue Jun 21 13:00:02 CDT 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2837xD_SYSCTRL_DEFINES_H
#define F2837xD_SYSCTRL_DEFINES_H

//
// Defines
//
#define LPM_IDLE    0x0
#define LPM_STANDBY 0x1
#define LPM_HALT    0x2
#define LPM_HIB     0x3

//
//Key value used for write access to the flash pump semaphore register
//
#define IPC_PUMP_KEY 0x5a5a0000

#endif  // end of F2837xD_SYSCTRL_DEFINES_H definition

//
// End of file
//
