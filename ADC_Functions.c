/*
 * File:   ADC_Functions.c
 * Author: chauv
 *
 * Created on 25 octobre 2023, 19:41
 */
#include "ADC_Functions.h"
#include "Config.h"


void init_adc(void)
{

/*set pin A05 as input*/
TRISAbits.RA5 = 1;
        

/*Select chanel 5 = 0101*/
//ADCON0bits.CHS0 = 1;
//ADCON0bits.CHS1 = 0;
//ADCON0bits.CHS2 = 1;
//ADCON0bits.CHS3 = 0;
ADCON0 = 0x11;


/* Select AN05 */
//ADCON1bits.PCFG0 = 1;
//ADCON1bits.PCFG1 = 0;
//ADCON1bits.PCFG2 = 0;
//ADCON1bits.PCFG3 = 1;
ADCON1 = 0x09;     // ---------- NE PAS CHANGER

/* result left justified */
ADCON2bits.ADFM = 0;
}

//00010001 00001001