#include "HX711.h"
#include "avr_uart.h"
#include <util/delay.h>

float calibration_factor = 12800;

void init(void) {
    avr_uart_init();
    stdout = &avr_uart_output;
    stdin  = &avr_uart_input_echo;
    HX711_init(128);
}

int main(void) {
    init();

    printf("HX711 calibration sketch\n");
    printf("Remove all weight from scale\n");
    printf("After readings begin, place known weight on scale\n");
    printf("Press + or a to increase calibration factor\n");
    printf("Press - or z to decrease calibration factor\n");

    HX711_set_scale(1.0);
    HX711_tare(10);	//Reset the scale to 0

    long zero_factor = HX711_read_average(10); //Get a baseline reading
    printf("Zero factor: %ld", zero_factor); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.

    while(1) {
        HX711_set_scale(calibration_factor); //Adjust to this calibration factor

        printf("Reading: %.2f Kg calibration_factor: %f\n", HX711_get_mean_units(1), calibration_factor);

        if(avr_uart_data_available())
        {
            char temp = avr_uart_getchar(stdin);
            if(temp == '+' || temp == 'a')
                calibration_factor += 10;
            else if(temp == '-' || temp == 'z')
                calibration_factor -= 10;
        }

        _delay_ms(500);
    }
}
