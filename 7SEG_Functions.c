/*
 * File:   7SEG_Functions.c
 * Author: chauv
 *
 * Created on 25 octobre 2023, 15:25
 */
#include "Config.h"

unsigned char binary_pattern[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void init_7seg(){
    TRISD = 0x00;       // PORTD as a output pin
    TRISAbits.RA0 = 0;  // RA0 as output
    TRISAbits.RA1 = 0;  // RA1 as output
    TRISAbits.RA2 = 0;  // RA2 as output
    TRISAbits.RA3 = 0;  // RA3 as output
}

int disp_number(int number){
    int tab_num[4]= {0,0,0,0};
    int cpt = 0;
    
    if(number > 9999){
       return -1; 
    }
    
    while(cpt < 4){
        tab_num[cpt] = number%10;
        cpt++;
        number /= 10;
    }
    
    PORTAbits.AN0 = 0;
    PORTAbits.AN1 = 0;
    PORTAbits.AN2 = 0;
    PORTAbits.AN3 = 0;
    
    PORTD = binary_pattern[tab_num[0]];
    PORTAbits.RA0 = 1;
    __delay_us(500);

    PORTD = binary_pattern[tab_num[1]];
    PORTAbits.RA1 = 1;
    __delay_us(500);

    PORTD = binary_pattern[tab_num[2]];
    PORTAbits.RA2 = 1;
    __delay_us(500);

    PORTD = binary_pattern[tab_num[3]];
    PORTAbits.RA3 = 1;
    __delay_us(500);
    return 0;
}