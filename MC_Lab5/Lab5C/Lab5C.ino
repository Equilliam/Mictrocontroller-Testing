#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void init_uart(void)
{
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);   // enable rx and tx
    UBRR0 = 16;                         // set baud rate to 57.6k
}

void write_char(char c)
{
    // Wait for UDR0 to be ready for writing
    while ((UCSR0A & (1<<UDRE0)) == 0); // or loop until bit set

    // Write data byte
    UDR0 = c;
}

char check_char(void)
{
    // Check if data ready for reading
    return (UCSR0A & (1<<RXC0));
}

char read_char(void)
{
    // Wait for data
    while ((UCSR0A & (1<<RXC0)) == 0);

    // Return data
    return UDR0;
}

int main(void)
{
    init_uart();

    // until a character is received, transmit B.
    // Once any character is received, transmit A.
   /** while (1)
    {
        if (check_char())
        {
            write_char('A');
        }
        else
        {
            write_char('B');
        }

        _delay_ms(500);
       **/ 
        while (1) { write_char(read_char());
    }
}