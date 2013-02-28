#include <avr/io.h>
#include <util/delay.h>
#include "psx/psx.h"
#define MAX_PWM 0x3ff

typedef _Bool bool;

enum gerak {maju,mundur};
uint_fast8_t saveGerak01=1;
uint_fast8_t saveGerak02=1;

void motorKiri(enum gerak arah01,uint16_t speed)
{
    if(saveGerak01!=arah01)
    {
        OCR1A=MAX_PWM+1;
        _delay_ms(10);
        switch(arah01)
        {
        case maju:
            PORTD|=_BV(PD2);
            PORTD&=~_BV(PD3);
            break;
        case mundur:
            PORTD&=~_BV(PD2);
            PORTD|=_BV(PD3);
            break;
        }
    }
    OCR1A=speed;
    saveGerak01=arah01;
}

void motorKanan(enum gerak arah01,uint16_t speed)
{
    if(saveGerak01!=arah01)
    {
        OCR1B=MAX_PWM+1;
        _delay_ms(10);
        switch(arah01)
        {
        case maju:
            PORTD|=_BV(PD0);
            PORTD&=~_BV(PD1);
            break;
        case mundur:
            PORTD&=~_BV(PD0);
            PORTD|=_BV(PD1);
            break;
        }
    }
    OCR1B=speed;
    saveGerak02=arah01;
}

void avr_init(void)
{
//setup PWM timer1
    DDRB |=_BV(PB1)|_BV(PB2);
    DDRD |=_BV(PD0)|_BV(PD1)|_BV(PD2)|_BV(PD3);
    PORTC|=_BV(PC0);
    DDRC |=_BV(PC0);
    ICR1=MAX_PWM;
    TCCR1A|=_BV(WGM11)|_BV(COM1A1)|_BV(COM1B1);
    TCCR1B|=_BV(WGM12)|_BV(WGM13)|_BV(CS10);
    DDRC|=_BV(PC0);
    psxPadSetup();
    _delay_ms(1);
}

int main(void)
{
    uint16_t tom[5]= {0};
    avr_init();
    while(1)
    {
        PsxReadPad(tom);
        if(tom[0]&PSXXBtn)
        {
            PORTC|=_BV(PC0);
        }
        else
        {
            PORTC&=~_BV(PC0);
        }
    }
    return 0;
}
