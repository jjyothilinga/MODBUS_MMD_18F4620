#ifndef DEVICE_H
#define DEVICE_H

/*
*------------------------------------------------------------------------------
* device.h
*
* Include file for port pin assignments
*

*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* File				: device.h
*------------------------------------------------------------------------------
*

*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------
*/

#include <p18f4620.h>
#include <delays.h>
#include <timers.h>
#include "typedefs.h"
#include "config.h"


/*
*------------------------------------------------------------------------------
* Hardware Port Allocation
*------------------------------------------------------------------------------
*/

//Heart Beat
#define 	HEART_BEAT					PORTCbits.RC0
#define 	HEART_BEAT_DIRECTION		TRISCbits.TRISC0

// Rs485 / RS232 Serial commnunicaton port
#define		TX_EN					PORTCbits.RC2			// TX control for RS485 communication
#define		TX_EN_DIR				TRISCbits.TRISC2
#define 	SER_TX					PORTCbits.RC6   		// serial transmit
#define		SER_TX_DIR				TRISCbits.TRISC6
#define 	SER_RX					PORTCbits.RC7			// serial receive
#define		SER_RX_DIR				TRISCbits.TRISC7

// MMD PORTS
#define 	DISPLAY_CONTROL				PORTEbits.RE2
#define 	DISPLAY_CONTROL_DIRECTION	TRISEbits.TRISE2

#define		DATA_PORT				PORTD	//LATD	 				// 7seg display data (DB0-DB7)
#define 	DATA_PORT_DIR			TRISD
#define		DIGIT_PORT				PORTB	//LATB	 				// digit drivers(upto 128 digits)
#define		DIGIT_PORT_DIR			TRISB	//LATB	 				// digit drivers(upto 128 digits)

#define		ROW_SEL_H				PORTAbits.RA0		// decoder digit sel A
#define		ROW_SEL_H_DIR			TRISAbits.TRISA0
#define		ROW_SEL_G				PORTAbits.RA1		// decoder digit sel B
#define		ROW_SEL_G_DIR			TRISAbits.TRISA1
#define		ROW_SEL_F				PORTAbits.RA2		// decoder digit sel C
#define		ROW_SEL_F_DIR			TRISAbits.TRISA2
#define		ROW_SEL_E				PORTAbits.RA3		// decoder digit sel D
#define		ROW_SEL_E_DIR			TRISAbits.TRISA3
#define		ROW_SEL_D				PORTAbits.RA4		// decoder digit sel E
#define		ROW_SEL_D_DIR			TRISAbits.TRISA4
#define		ROW_SEL_C				PORTAbits.RA5		// decoder digit sel F
#define		ROW_SEL_C_DIR			TRISAbits.TRISA5
#define		ROW_SEL_B				PORTEbits.RE0		// decoder digit sel G
#define		ROW_SEL_B_DIR			TRISEbits.TRISE0
#define		ROW_SEL_A				PORTEbits.RE1		// decoder digit sel G
#define		ROW_SEL_A_DIR			TRISEbits.TRISE1	



/*------------------------------------------------------------------------------
* Public Defines
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Macros
*------------------------------------------------------------------------------
*/

#define DEVICE_ID			(0x00)


//#define SYSTEM_CLOCK			(20000000UL)	// Hz		// 20MHz external crystal  used

#define SYSTEM_CLOCK			(40000000UL)	// Hz		// 10MHz external crystal x4 PLL

#define PERIPHERA_CLOCK			(SYSTEM_CLOCK / 4)UL

#define PERIPHERA_CLOCK_PERIOD 	(1 / PERIPHERA_CLOCK)UL



// Direction controle bit is processor specific ,
#define PORT_OUT				(BOOL)(0)
#define PORT_IN					(BOOL)(1)

#define OFF_FOREVER				(BOOL)(0)
#define LOOP_FOREVER			(BOOL)(1)

#define SWITCH_OFF				(BOOL)(0)
#define SWITCH_ON				(BOOL)(1)


#define DISPLAY_DISABLE			(BOOL)(1)
#define DISPLAY_ENABLE			(BOOL)(0)

void EnableInterrupts(void);
/*
#ifdef __74LS374__
#undef DISPLAY_DISABLE
#undef DISPLAY_ENABLE

#define DISPLAY_DISABLE			(BOOL)(0)
#define DISPLAY_ENABLE			(BOOL)(1)

#endif 			//__74LS374__
*/


#define GetSystemClock()		(SYSTEM_CLOCK)      // Hz
#define GetInstructionClock()	(GetSystemClock()/4)
#define GetPeripheralClock()	GetInstructionClock()


#define BUZZER_ON()			BUZ_OP = SWITCH_ON;
#define BUZZER_OFF()		BUZ_OP = SWITCH_OFF;

// Disable global interrupt bit.
#define ENTER_CRITICAL_SECTION()	INTCONbits.GIE = 0;

// Enable global interrupt bit.
#define EXIT_CRITICAL_SECTION()		INTCONbits.GIE = 1;

#define ENABLE_GLOBAL_INT()			EXIT_CRITICAL_SECTION()


#define DISABLE_INT0_INTERRUPT()	INTCONbits.INT0IE = 0
#define ENABLE_INT0_INTERRUPT()		INTCONbits.INT0IE = 1
#define CLEAR_INTO_INTERRUPT()		INTCONbits.INT0IF = 0


#define DISABLE_TMR0_INTERRUPT()	INTCONbits.TMR0IE = 0
#define ENABLE_TMR0_INTERRUPT()		INTCONbits.TMR0IE = 1

#define DISABLE_TMR1_INTERRUPT()	PIE1bits.TMR1IE = 0
#define ENABLE_TMR1_INTERRUPT()		PIE1bits.TMR1IE = 1


#define HOLD_ATKBD_CLOCK()		    ATKBD_CLK_DIR= PORT_OUT;\
									ATKBD_CLK = 0;

#define RELEASE_ATKBD_CLOCK()	  	ATKBD_CLK_DIR = PORT_IN;\
									ATKBD_CLK = 1;

#define SET_INT0_FALLING_EDGE_TRIGGER()	INTCON2bits.INTEDG0 = 0

#define	ATKBD_INTERRUPT_EDGE	INTCON2.INTEDG0		

#define ENB_485_TX()	TX_EN = 1;
#define ENB_485_RX()	TX_EN = 0

#define DISABLE_UART_RX_INTERRUPT()	PIE1bits.RCIE = 0
#define ENABLE_UART_RX_INTERRUPT()	PIE1bits.RCIE = 1

#define Delay10us(us)		Delay10TCYx(((GetInstructionClock()/1000000)*(us)))
#define DelayMs(ms)												\
	do																\
	{																\
		unsigned int _iTemp = (ms); 								\
		while(_iTemp--)												\
			Delay1KTCYx((GetInstructionClock()+999999)/1000000);	\
	} while(0)

/*
*------------------------------------------------------------------------------
* Public Data Types
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Variables (extern)
*------------------------------------------------------------------------------
*/


/*
*------------------------------------------------------------------------------
* Public Constants (extern)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Function Prototypes (extern)
*------------------------------------------------------------------------------
*/

extern void BRD_init(void);

#endif
/*
*  End of device.h
*/