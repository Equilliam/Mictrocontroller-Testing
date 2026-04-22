#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// --- Pin Definitions ---
#define LED_PIN     PB0  
#define BUTTON_PIN  PD2  
const uint8_t SEGMENT_PATTERNS[] = {
  // 2 is corrupted and I display a 3 somewhere, hexadecimal codes are correct I believe
    0x5B, // 2 (0b01011011) 
    0x3F, // 0 (0b00111111)
    0x5B, // 2 (0b01011011) 
    0x6D  // 5 (0b01101101) 
};

// Array of digits to display: 2, 0, 2, 5
#define SEQUENCE_LENGTH 4

#define DELAY_CHUNK_MS      100    
#define CHUNKS_PER_STEP     20      // Number of chunks needed for 2 seconds

void setup_io(void);

void setup_io(void) {
    DDRB |= (1 << LED_PIN);     // PB0 as output
    DDRC = 0b01111111;          // PC0-PC6 as outputs
    DDRD &= ~(1 << BUTTON_PIN); // Port D (Button) - PD2 as input

    PORTD |= (1 << BUTTON_PIN); // Button: Enable internal pull-up on PD2
    PORTB &= ~(0 << LED_PIN);   // LED: Initially OFF
    PORTC = 0x00;               // 7-Segment: Initially OFF (CC)
}

#define LED_ON() PORTB |= (1 << PB0)

int main(void) {
    setup_io();
    LED_ON(); 
    static uint8_t is_active = 0;       
    static uint8_t sequence_index = 0;  // Index of the current digit in the 2, 0, 2, 5 sequence
    static uint8_t delay_counter = 0;   // Counter for the 2-second delay

    // --- State 1: Initial State (LED ON, 7-SEG OFF) ---
    PORTB |= (1 << LED_PIN); //LED should be ON but is not. . . .
    PORTC = 0x00;            
    while (1) {
        //I haven't been able to set up a toggle for my button, so I can't turn the system off
        if (!(PIND & (1 << BUTTON_PIN))) {
            
            _delay_ms(20); 
            
            if (!(PIND & (1 << BUTTON_PIN))) {
                
                is_active = !is_active; 
                
                if (is_active) {
                    sequence_index = 0;
                    delay_counter = 0;
                    
                    PORTB &= ~(1 << LED_PIN);          
                    PORTC = SEGMENT_PATTERNS[sequence_index];
                } else {
                    PORTB |= (1 << LED_PIN);  // LED ON
                    PORTC = 0x00;             // 7-Seg OFF
                }

                while (!(PIND & (1 << BUTTON_PIN))) {
                    _delay_ms(10);
                }
            }
        }
        
        if (is_active) {
            
            if (delay_counter >= CHUNKS_PER_STEP) { //has enough time passed?
                
                delay_counter = 0;
                sequence_index++;
                if (sequence_index >= SEQUENCE_LENGTH) {
                    sequence_index = 0; // Loop the sequence 2->0->2->5
                }
                
                if (sequence_index == 1 || sequence_index == 3) {
                    PORTB |= (1 << LED_PIN);  // LED ON
                } else {
                    PORTB &= ~(1 << LED_PIN); // LED OFF
                }

                PORTC = SEGMENT_PATTERNS[sequence_index];
            }

            _delay_ms(DELAY_CHUNK_MS);
            delay_counter++;

        } else {
            PORTB |= (1 << LED_PIN);
            PORTC = 0x00;
            _delay_ms(10);
        }
    }
  return 0; //failsafe - the loop should never be left
}