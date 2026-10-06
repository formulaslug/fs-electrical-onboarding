#include <cstdio>
#include <string.h>
#include "analogin_api.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"
#include "mbed.h"
#include "objects.h"

extern UART_HandleTypeDef huart2;
AnalogIn APPS1_adc{PC_1};
AnalogIn APPS2_adc{PC_2};
CAN can{PB_8, PB_9, 500000};

ADC_HandleTypeDef *APPS1_hadc = &(((analogin_t*)&APPS1_adc)->handle);
ADC_HandleTypeDef *APPS2_hadc = &(((analogin_t*)&APPS2_adc)->handle);
CAN_HandleTypeDef *hcan = &(((can_t*)&can)->CanHandle);

static constexpr float PEDAL_DEADZONE_PERCENTAGE = 0.03;
static constexpr int16_t MAX_TORQUE = 32767 * 0.1;

static constexpr float APPS1_MIN_VOLTAGE = 0.396;
static constexpr float APPS1_MAX_VOLTAGE = 1.086f;

static constexpr float APPS2_MIN_VOLTAGE = 0.439f;
static constexpr float APPS2_MAX_VOLTAGE = 1.133f;

int main(void) {

    char msg[] = "Hello world!\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY); // Sending "Hello world!\n" over Serial

    while (true) {
        /*
            Add lines where you start the ADC, poll from it, then
            convert it to voltage from a 12 bit number.

            Next, you should add two TIM_HandleTypeDef objects for
            creating timers and using them for implaus checks.

            After confirming your approach works, try to research
            a way to get CAN communication going aswell.
        */
        float APPS1_voltage = ADCtoVoltage(readADC(APPS1_hadc), 3.3f);
        HAL_Delay(100)

        float APPS2_voltage = ADCtoVoltage(readADC(APPS2_hadc), 3.3f);

        float APPS1_pos = (APPS1_voltage - APPS1_MIN_VOLTAGE) / (APPS1_MAX_VOLTAGE - APPS1_MIN_VOLTAGE);
        float APPS2_pos = (APPS2_voltage - APPS2_MIN_VOLTAGE) / (APPS2_MAX_VOLTAGE - APPS2_MIN_VOLTAGE);

        float apps_avg_position = (APPS1_pos + APPS2_pos) / 2;

        if (apps_avg_position < PEDAL_DEADZONE_PERCENTAGE) {
            apps_avg_position = 0;
        }

        float motor_torque_demand = apps_avg_position * MAX_TORQUE;

        bool implaus_out_of_range = !(in_range(APPS1_voltage, APPS1_MIN_VOLTAGE, APPS1_MAX_VOLTAGE) && 
                                in_range(APPS2_voltage, APPS2_MIN_VOLTAGE, APPS2_MAX_VOLTAGE));
        
        bool implaus_deviation = false;
        if (APPS1_pos > 0.1 || APPS2_pos > 0.1){
            if (std::abs(APPS1_pos - APPS2_pos) < 0.1) {
                implaus_deviation = false;
            } else {
                implaus_deviation = true;
            }
        } else {
            implaus_deviation = false;
        }

        
    }

    return 0;
}

uint32_t readADC(ADC_HandleTypeDef ADC_pin){
    HAL_ADC_Start(&ADC_pin);

    uint32_t output = 0;
    if (HAL_ADC_PollForConversion(&ADC_pin, 20) == HAL_OK) {
        output = HAL_ADC_GetValue(&ADC_pin);
    }

    HAL_ADC_Stop(&ADC_pin);

    return output;
}

float ADCtoVoltage (uinst32_t analogOut, float voltage = 3.3f){
    float voltage = ((float) analogOut * voltage) / 4095.0f;
    return voltage;
}