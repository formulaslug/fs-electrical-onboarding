#include "etc_controller.h"
#include "mbed.h"
#include <cstdio>

ETCController etc{PinName APPS1_pin, PinName APPS2_pin};

CAN can{PB_8, PB_9, 500000};

// Predefined for use in main()
void send_etc_CAN_messages();
void send_sme_CAN_messages();

int main() {
    printf("Hello World!!\n");

    /*
        Make send_CAN messages loop consistently
        at 20hz (20 messages / second)
    */



    // No need to edit this while loop
    while (true) {
        // Must implement in etc/ subfolder
        etc.update_state();
    }

    return 0;
}

/* 
    Must send the VCU_TPDO_STATUS CAN message with
    VCU_ETC_READY_TO_DRIVE & VCU_ETC_MOTOR_ENABLED
    set to 1, and VCU_ETC_IMPLAUS_APPS_OUT_OF_RANGE
    & VCU_ETC_IMPLAUS_APPS_DEVIATION properly added.
*/
void send_etc_CAN_messages() {
    // 00000011
    // 1 = VCU_ETC_READY_TO_DRIVE
    // 2 = VCU_ETC_MOTOR_ENABLED
    // 4 = VCU_ETC_IMPLAUS_APPS_OUT_OF_RANGE
    // 6 = VCU_ETC_IMPLAUS_APPS_DEVIATION
    uint8_t message[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    message[0] = 1;
    message[0] |= 1 << 1;

    if (etc.implaus) {
        message[0] |= (1 << 4 | 1 << 6);
    } else {
        message[0] &= ~(1 << 4 | 1 << 6);
    }

    can.send(CANMessage(0x193, message, 8));
}

/*
    Must send the SME_RPDO_Throttle_Demand CAN
    message with SME_THROTL_TorqueDemand set to the
    torque demand determined by the ETC.
*/
void send_sme_CAN_messages() {}
