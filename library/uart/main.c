
/* -----------------------------------------
* G.Raf^engineering
* www.sunriax.at (github.com/0x007e)
* -----------------------------------------
*    Platform: Independent
*    Hardware: ATTiny406/1606/...
* -----------------------------------------
*     Version: 1.0 Release
*      Author: G.Raf
* Description:
*	Sample for initializing uart
* -----------------------------------------
*/

#define F_CPU 20000000UL

// System libraries
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// User libraries
#include "uart.h"
#include "../system/system.h"

// Static test variables for printf
static unsigned int x = 123;            // Numeric
static unsigned char a = 'A';           // Character
static unsigned char str[] = "Test";    // String
static double z = 123.43;               // Floating Point

int main(void)
{
    // Initialize UART
    //       Baud: 9600
    //     Parity: None
    // Stopbit(s): 1
    uart_init();

    // Put a single char without printf
    uart_putchar('0');
    uart_putchar('x');
    uart_putchar('0');
    uart_putchar('0');
    uart_putchar('7');
    uart_putchar('E');
    uart_putchar('\n');
    uart_putchar('\r');

    // Print a String
    printf("Hello, world!\n\r");
    
    // Print different variables
    printf("Variables -> %d, %c, %s\n\r", x, a, str);
    
    // Linker parameter necessary:
    //  ->     Libraries: libprintf_flt
    //  ->       General: Use vprintf
    //  -> Miscellaneous: -Wl,-u,vfprintf -lprintf_flt -lm
    printf("Variable y: %f\n\n\r", z);

    while (1)
    {
        // Scan for a char blocking
        UART_Data status;
        uart_putchar(uart_getchar(&status));

        // Scan for a char non-blocking
        printf("\n\rPress a key to abort: ");

        for (unsigned char i=0; i < 50; i++)
        {
            uart_putchar('+');
            
            char temp;

            if(uart_scanchar(&temp) == UART_Received)
            {
                break;
            }
        }
        uart_putchar('\n');
        uart_putchar('\r');

        // Make a request from console
        printf("Please enter a number: ");
        unsigned int zahl1;
        
        if(scanf("%3u", &zahl1) == 1)
        {
            printf("\n\n\rThe result of %u * 5 equals: %u\n\n\r", zahl1, (zahl1 * 5));
        }
        else
        {
            uart_clear();
            printf("\n\rInput error!\n\n\r");
        }
        
        printf("Please insert 10 characters: ");
        char test[11];
        
        if(scanf("%10s", test) != 0)
        {
            printf("\n\n\rInput result: %s\n\n\r", test);
        }
        else
        {
            uart_clear();
            printf("\n\rInput error!\n\n\r");
        }
        
        printf("Please enter a decimal number: ");
        float zahl2;
        
        // Linker parameter necessary:
        //  ->     Libraries: libscanf_flt
        //  ->       General: Use vprintf
        //  -> Miscellaneous: -Wl,-u,vfscanf -lscanf_flt -lm
        if(scanf("%f", &zahl2) == 1)
        {
            printf("\n\n\rThe result of %f * 5.23 equals: %f\n\n\r", zahl2, (zahl2 * 5.23));
        }
        else
        {
            uart_clear();
            printf("\n\rInput error!\n\n\r");
        }
        
        _delay_ms(1000);
    }
}