/*
 * File:   lab4_pt_i.c
 * Author: desau && LM
 *
 * Created on November 6, 2025, 8:40 AM
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_ON() PORTD |= (1 << PORTD7)
#define LED_OFF() PORTD &= ~(1 << PORTD7)

volatile uint16_t tick = 0;
volatile uint8_t led_state = 0;

int main(void) {
    
    DDRD |= (1 << DDD7); // Set PD7 as output
    LED_OFF(); // Start with LED off
 
    TCCR0A = 0x00; // Normal mode
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler = 64
    TCNT0 = 0; // Start from 0
    TIMSK0 |= (1 << TOIE0); // Enable overflow interrupt

    sei(); 

    while (1) {
        
    }
}

ISR(TIMER0_OVF_vect) {
    tick++;
    
    // With 16MHz clock and prescaler 64:
    // Timer frequency = 16MHz / 64 = 250kHz
    // Timer period = 4us
    // Overflow every 256 counts = 256 * 4us = 1.024ms
    // For 5 seconds: 5 / 0.001024 ≈ 4883 overflows
    
    if (tick >= 4883) { // Approximately 5 seconds
        tick = 0;
        
        // Toggle LED state
        if (led_state) {
            LED_OFF();
            led_state = 0;
        } else {
            LED_ON();
            led_state = 1;
        }
    }
}