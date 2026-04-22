/*
 * main.c
 *
 * Created: 10/29/2025 10:35:46 PM
 *  Author: Ashton Dudley
 */ 

# define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>


int on_when_pressed(void) {

    // Set port D7 to OUTPUT
    // Set port B4 to INPUT
    DDRD |= (1 << PORTD7);
    DDRB &= ~(1 << PORTB4);
    PORTD = 0x00; // ??
    
    // Turn on PORT B4 Pull up
    PORTB |= (1 << PORTB4); 

    while (1) {
        if (!(PINB & (1 << PORTB4))) {
            PORTD = (1 << PORTD7);
        } 
        else { 
            PORTD &= ~(1 << 7);   // Turn off PORT D7
        } 
    }
    return 0;
}


int toggle_when_pressed(void) {
    
    DDRD |= 1 << 7;     // D7 -> Output
    DDRB &= ~(1 << 4);  // Clears B4 to input
    PORTB = 1 << 4;     // Set PINB4 to turn on pull-up resistor

    unsigned char ledstate = 1;
    unsigned char buttonstate = 0;
    unsigned char lastbuttonstate = 0;
    unsigned char tempbuttonstate = 0;

    while (1) {
        
        // No debounce
        //buttonstate = PINB & (1<<4);
        
        //Debounce
        tempbuttonstate = PINB & (1<<4);
        _delay_ms(20);
        if ((PINB & (1<<4)) == tempbuttonstate) {
            buttonstate = tempbuttonstate;
        }
        
        
        if ((buttonstate != lastbuttonstate) && (buttonstate == 0)) {
            ledstate ^= 1;
        }
    
        lastbuttonstate = buttonstate;

        if(ledstate) {
            PORTD |= (1 << 7);
        } else {
            PORTD &= ~(1 << 7);
        }

    }
}

unsigned char read_button(unsigned char row, unsigned char col) {
    unsigned char buttonState = 0;

    PORTD = 0xF0;

    if (row < 2) {
        DDRC |= 1 << row;
    } else {
        DDRD |= 1 << row;
    }
    
    _delay_us(10);

    if ((PIND & (1<<(col+4))) == 0) {
        _delay_ms(20); 
        if ((PIND & (1<<(col+4))) == 0) {
            buttonState = 1;
        }
    } 

    if (row < 2) {
        DDRC &= ~(1<<row); // this was a * which made the lights flash in order
    } else {
        DDRD &= ~(1<<row);
    }
    return buttonState;
}

void set_led(unsigned char lednum) {
    switch (lednum) {
        case 0:
            DDRB = 1<<0 | 1<<2;
            PORTB = 1<<0;
            break;
        case 1:
            DDRB = 1<<1 | 1<<2;
            PORTB = 1<<1;
            break;
        case 2:
            DDRB = 1<<0 | 1<<3;
            PORTB = 1<<0;
            break;
        case 3:
            DDRB = 1<<1 | 1<<3;
            PORTB = 1<<1;
            break;
        default:
            break;
    }
}

unsigned char decode_buttons(void) {
    unsigned char row, col;
    unsigned char button = 0x0ff;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (read_button(row, col)) {
                button = row | (col << 4);
            }
        }
    }
        switch(button) {
        case (0<<4) | 0: return 0x0F;
        case (0<<4) | 1: return 0x0E;
        case (0<<4) | 2: return 0x0D;
        case (0<<4) | 3: return 0x0C;
        case (1<<4) | 0: return 0x0B;
        case (1<<4) | 1: return 0x0A;
        case (1<<4) | 2: return 0x09;
        case (1<<4) | 3: return 0x08;
        case (2<<4) | 0: return 0x07;
        case (2<<4) | 1: return 0x06;
        case (2<<4) | 2: return 0x05;
        case (2<<4) | 3: return 0x04;
        case (3<<4) | 0: return 0x03;
        case (3<<4) | 1: return 0x02;
        case (3<<4) | 2: return 0x01;
        case (3<<4) | 3: return 0x00;
        default: return 0xFF;
    }
}

int main(void) { 

    unsigned char button, tempbutton;

    while(1) {

        tempbutton = decode_buttons();

        if (tempbutton != 0xFF) {
            button = tempbutton;
        } else {
            _delay_ms(30);
        }

        switch (button) {
            case 0x00: // Button 0
                set_led(0);
                break;
            case 0x01: // Button 1
                set_led(1);
                break;
            case 0x02: // Button 2
                set_led(2);
                break;
            case 0x03: // Button 3
                set_led(3);
                break;
            case 0x04: // Button 4
                set_led(0);
                _delay_ms(100);
                set_led(1);
                break;
            case 0x05: // Button 5
                set_led(2);
                _delay_ms(100);
                set_led(3);
                break;
            case 0x06: // Button 6
                set_led(1);
                _delay_ms(100);
                set_led(0);
                break;
            case 0x07: // Button 7
                set_led(3);
                _delay_ms(50);
                set_led(2);
                break;
            case 0x08: // Button 8
                set_led(0);
                _delay_ms(50);
                set_led(1);
                _delay_ms(50);
                set_led(2);
                _delay_ms(50);
                set_led(3);
                break;
            case 0x09: // Button 9
                set_led(3);
                _delay_ms(50);
                set_led(2);
                _delay_ms(50);
                set_led(1);
                _delay_ms(50);
                set_led(0);
                break;
            case 0x0A: // Button 10
                set_led(0);
                _delay_ms(100);
                set_led(2);
                break;
            case 0x0B: // Button 11
                set_led(1);
                _delay_ms(100);
                set_led(3);
                break;
            case 0x0C: // Button 12
                set_led(0);
                _delay_ms(100);
                set_led(1);
                _delay_ms(100);
                set_led(2);
                _delay_ms(100);
                set_led(3);
                break;
            case 0x0D: // Button 13
                set_led(3);
                _delay_ms(100);
                set_led(2);
                _delay_ms(100);
                set_led(1);
                _delay_ms(100);
                set_led(0);
                break;
            case 0x0E: // Button 14
                set_led(0);
                _delay_ms(50);
                set_led(1);
                _delay_ms(50);
                set_led(2);
                _delay_ms(50);
                set_led(3);
                break;
            case 0x0F: // Button 15
                // Toggle all LEDs rapidly
                for (int i = 0; i < 4; i++) {
                    set_led(i);
                    _delay_ms(100);
                }
                break;
            default:
                break;
        }
    }
}




/*

# TODOs 

- [ ] LED turns on/off when button pressed (ON WHEN LOW)
- [ ] LED toggles when button pressed (TOGGLE WHEN LOW)

*/