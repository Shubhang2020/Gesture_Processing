

#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "ei_run_classifier.h"
#include "hardware/pwm.h"
#include "hardware/pio.h"

#define SCL 1
#define SDA 0
#define BUTTON_PIN 14


#define I2C_PORT i2c0

#define MPU6050_ADDRESS 0x68

void mpu6050_reset();
volatile bool timer0_occur=false,timer1_occur=false;
void mpu6050_read(int16_t accelerometer[3]);


static bool debug_nn = false;
const uint LED_PIN = 15;

const uint PINS[] = {16, 17, 18};
const size_t NUM_PINS = sizeof(PINS) / sizeof(PINS[0]);

void set_pins_high_for_label(int label) {
    // Reset all pins to low
    for (size_t i = 0; i < NUM_PINS; i++) {
        gpio_put(PINS[i], 0);
    }

    // Set pins high based on the label
    if (label == 0) {
        gpio_put(16, 0);
        gpio_put(17, 0);
        gpio_put(18, 1); // 001
    } else if (label== 1) {
        gpio_put(16, 0);
        gpio_put(17, 1);
        gpio_put(18, 0); // 010
    } else if (label == 2) {
        gpio_put(16, 1);
        gpio_put(17, 1);
        gpio_put(18, 0); // 110
    }

    else if(label == 3){
        gpio_put(16, 1);
        gpio_put(17, 1);
        gpio_put(18, 1);    //111

    }
    // Add more combinations for other labels if needed
}


int main()
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);


    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    for (size_t i = 0; i < NUM_PINS; i++) {
        gpio_init(PINS[i]);
        gpio_set_dir(PINS[i], GPIO_OUT);
    }


// Initialize I2C port 0 and configuring Pins 0 and 1 for MPU6050
    i2c_init(I2C_PORT,100000);
    gpio_set_function(SCL,GPIO_FUNC_I2C);
    gpio_set_function(SDA,GPIO_FUNC_I2C);
    gpio_pull_up(SCL);
    gpio_pull_up(SDA);
    mpu6050_reset();

    ei_impulse_result_t result = {0};


   int16_t accelerometer[3];



    bool button_pressed = false; // Track the button state

    while (true) 
    
    {

    bool current_button_state = !gpio_get(BUTTON_PIN); // Active low

    
    if (current_button_state && !button_pressed) {
        // Button was just pressed
        button_pressed = true;

    gpio_put(LED_PIN,1);  //Indicating wait operation
    sleep_ms(3000);
    gpio_put(LED_PIN,0);

    // Allocate a buffer here for the values we'll read from the IMU
    float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };

        for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 3) {
        // Determine the next tick (and then sleep later)
        //uint64_t next_tick = micros() + (EI_CLASSIFIER_INTERVAL_MS * 1000);
        uint64_t next_tick = ei_read_timer_us() + (EI_CLASSIFIER_INTERVAL_MS * 1000);
    
        mpu6050_read(accelerometer);
        buffer[ix + 0]= accelerometer[0];
        buffer[ix + 1]= accelerometer[1];
        buffer[ix + 2]= accelerometer[2];
        //IMU.readAcceleration(buffer[ix], buffer[ix + 1], buffer[ix + 2]);
        
        sleep_us(next_tick - ei_read_timer_us());
        //delayMicroseconds(next_tick - micros());
    }
   /* if(accelerometer[2]>=8000)
    multicore_fifo_push_blocking(4);
    else if(accelerometer[2]<=-7000)
    multicore_fifo_push_blocking(5);*/
    // Turn the raw buffer in a signal which we can the classify
    signal_t signal;
    int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
    if (err != 0) {
        break;
    }

    // Run the classifier
    ei_impulse_result_t result = { 0 };

    err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK) {
        break;
    }

    // print the predictions


    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    if (result.classification[ix].value > 0.8) {
        printf("FINAL PREDICTION: %s\n", result.classification[ix].label);
        set_pins_high_for_label(ix);
        break;
    }
}



    #if EI_CLASSIFIER_HAS_ANOMALY == 1
    #endif
    button_pressed= false;
    }

    else if (!current_button_state && button_pressed) {
            // Button was just released
        }

    sleep_ms(10);
    
    
    }
    
    
    return 0;
}


