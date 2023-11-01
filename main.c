#include "Config.h" 
#include "7SEG_Functions.h"
#include "ADC_Functions.h"
#include "GLCD_Functions.h"


uint16_t volatile valAdc = 0;
uint16_t dispVal = 0;

void init_timer_it(){
    T0CONbits.T08BIT = 1;
    T0CONbits.PSA = 1;
    INTCONbits.TMR0IF = 0;  // T0 int flag bit cleared before starting
    T0CONbits.TMR0ON = 1;   // timer0 START
}

void init_interrupt(){
    //ADC interrupt
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
    
    //periph. Int.
    INTCONbits.PEIE = 1;
    
    //Enable Global Interrupts 
    INTCONbits.GIE = 1;   
    
    //Enable Timer0 Interrupt
    //INTCONbits.TMR0IE = 1;    
}

void __interrupt(high_priority) hight_it_handler(void){
    // TIMER0 Overflow
    if (INTCONbits.TMR0IF)
    {
       // valAdc = get_adc_result();
        INTCONbits.TMR0IF = 0;           // Clear the interrupt flag
    }
    
    if (PIR1bits.ADIF)
    {
        valAdc = (uint16_t) (ADRESH << 8) | ADRESL;
        // Convertir la valeur de l'ADC en millivolts (mV) 65536 nombre de valeurs possible sur 16bits
        uint32_t valAdc_milli = (uint32_t)valAdc * 5000 / 65536;
        dispVal = valAdc_milli;
        
        PIR1bits.ADIF = 0;           // Clear the interrupt flag
    }
}

void main()
{
    init_timer_it();
    init_interrupt();
    init_7seg();
    init_adc();
    glcd_Init(GLCD_ON);
    
    TRISC = 0;
    PORTC = 0;
    
    //TRISD = 0x00;
    //PORTD = 0xFF;
    
    //TRISB = 0x00;
    //LATBbits.LATB4 = 0x01;
    
    while(1){
        disp_number(dispVal);
        ADCON0bits.GODONE = 1;
    }
  
    return;
}
