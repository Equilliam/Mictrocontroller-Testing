/*
 * main.c
 *
 * Created: 10/15/2025 7:18:14 PM
 *  Author: Ashton Dudley
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void reset();
void row1();
void row2();
void row3();
void row4();

int main(void)
{
    
    DDRD |= 0b11111111; // outputs for 7 segment
    PORTD = 0x00;
    DDRB |= 0b00111111;
    PORTB = 0x00;
    DDRC |= 0b00110000;
    
    while(1)
    {
        row1();
        _delay_ms(50);
        reset();
        
        row2();
        _delay_ms(50);
        reset();
        
        row3();
        _delay_ms(50);
        reset();
        
        row4();
        _delay_ms(50);
        reset();
        
    }
}

void reset() 
{
    PORTD = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
}

void row1()
{
    /*
    Pin B5 is made high for this cycle
    We will be detecting if any pin is pressed in Row 1
    If a key is pressed its corresponding value will be display on the display
    */

    PORTB |= 0b00100000;
    
    _delay_ms(50);
    
    if (PINC == 0x01)
    {
        // The corresponding pins have to be highlighted for output 'A'
        PORTD = 0x1C;
        PORTB = 0x01;
        PORTC = 0x30;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x02)
    {
        // The corresponding pins have to be highlighted for output '3'
        PORTD = 0x3C;
        PORTB = 0x01;
        PORTC = 0x00;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x04)
    {
        // The corresponding pins have to be highlighted for output '2'
        PORTD = 0x2C;
        PORTB = 0x01;
        PORTC = 0x10;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x08)
    {
        // The corresponding pins have to be highlighted for output '1'
        PORTD = 0x18;
        PORTB = 0x00;
        PORTC = 0x00;
        _delay_ms(500);
        return;
    }
}

void row2()
{
    /*
    Pin B4 is made high for this cycle
    We will be detecting if any pin is pressed in Row2
    If a key is pressed its corresponding value will be displayed on the display
    */

    PORTB |= 0b00010000;
    
    _delay_ms(50);
    
    if (PINC == 0x01)
    {
        // The corresponding pins have to be highlighted for output 'B'
        PORTD = 0x3C;
        PORTB = 0x01;
        PORTC = 0x30;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x02)
    {
        // The corresponding pins have to be highlighted for output '6'
        PORTD = 0x34;
        PORTB = 0x01;
        PORTC = 0x30;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x04)
    {
        // The corresponding pins have to be highlighted for output '5'
        PORTD = 0x34;
        PORTB = 0x01;
        PORTC = 0x20;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x08)
    {
        // The corresponding pins have to be highlighted for output 'B'
        PORTD = 0x18;
        PORTB = 0x01;
        PORTC = 0x20;
        _delay_ms(500);
        return;
    }
}

void row3()
{
    /*
    Pin B3 is made high for this cycle
    We will be detecting if any pin is pressed in Row 3
    If a key is pressed its corresponding value will be displayed on the display
    */

    PORTB |= 0b00001000;
    
    _delay_ms(50);
    
    if (PINC == 0x01)
    {
        // The corresponding pins have to be highlighted for output 'C'
        PORTD = 0x24;
        PORTB = 0x00;
        PORTC = 0x30;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x02)
    {
        // The corresponding pins have to be highlighted for output '9'
        PORTD = 0x3C;
        PORTB = 0x01;
        PORTC = 0x20;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x04)
    {
        // The corresponding pins have to be highlighted for output '8'
        PORTD = 0x3C;
        PORTB = 0x01;
        PORTC = 0x30;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x08)
    {
        // The corresponding pins have to be highlighted for output '7'
        PORTD = 0x1C;
        PORTB = 0x00;
        PORTC = 0x00;
        _delay_ms(500);
        return;
    }
}

void row4()
{
    /*
    Pin B2 is made high for this cycle
    We will be detecting if any pin is pressed in Row 4
    If a key is pressed its corresponding value will be displayed on the display
    */

    PORTB |= 0b00000100;
    
    _delay_ms(50);
    
    if (PINC == 0x01)
    {
        // The corresponding pins have to be highlighted for output 'D'
        PORTD = 0x3C;
        PORTB = 0x00;
        PORTC = 0x30;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x02)
    {
        // When '#' is pressed the output will be the decimal point.
        PORTD = 0x00;
        PORTB = 0x02;
        PORTC = 0x00;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x04)
    {
        // The corresponding pins have to be highlighted for output '0'
        PORTD = 0x3C;
        PORTB = 0x00;
        PORTC = 0x30;
        _delay_ms(500);
        return;
    }
    else if (PINC == 0x08)
    {
        // When '*' is pressed the output will be the decimal point
        PORTD = 0x00;
        PORTB = 0x00;
        PORTC = 0x02;
        _delay_ms(500);
        return;
    }
}