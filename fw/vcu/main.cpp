#include "etc_controller.h"
#include "mbed.h"
#include <cstdio>

ETCController etc{PC_1, PC_2};

CAN can{PB_8, PB_9, 500000};

// Predefined for use in main()
void send_etc_CAN_messages();
void send_sme_CAN_messages();

Ticker CANTicker;

int main() {
    printf("Hello World!!\n");

    /*
        Make send_CAN messages loop consistently
        at 20hz (20 messages / second)
    */

    CANTicker.attach(&send_etc_CAN_messages, 50ms); // 50ms is 20hz
    CANTicker.attach(&send_sme_CAN_messages, 50ms);


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

    // Implaus APPS out of range
    // ID: 403, length 8 on VCU
    // VCU_ETC_IMPLAUS_APPS_OUT_OF_RANGE 4|1@1+ (1,0) [0|1] ""
    //Sends READ_TO_DRIVE and MOTOR_ENABLED, as well as _OUT_OF_RANGE and IMPLAUS_APPS_DEViATION

    int8_t vcu_tpdo_status[8];
    vcu_tpdo_status[0] =
            etc.t_4_2_10_error << 6 |
            etc.t_4_2_4_error << 4 |
            0b00000011;


    const CANMessage status_message{403, reinterpret_cast<const unsigned char *>(vcu_tpdo_status), 8};

    can.write(status_message);



}

/*
    Must send the SME_RPDO_Throttle_Demand CAN
    message with SME_THROTL_TorqueDemand set to the
    torque demand determined by the ETC.
*/
void send_sme_CAN_messages() {
    CANMessage sme_rpdo_throttle[8];

    sme_rpdo_throttle[0] = etc.target_torque & 0xFF;
    sme_rpdo_throttle[1] = etc.target_torque >> 8;

    const CANMessage status_message{390, reinterpret_cast<const unsigned char *>(sme_rpdo_throttle), 8};

    can.write(status_message);
}
