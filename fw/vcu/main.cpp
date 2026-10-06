#include "iostream"
#include "etc_controller.h"
#include "mbed.h"
#include <cstdio>

ETCController etc{PC_1 , PC_2};


CAN can{PB_8, PB_9, 500000};

// Predefined for use in main()
void send_etc_CAN_messages();
void send_sme_CAN_messages(); //just makes them exist to compiler

Ticker send_etc_CAN_messages_ticker;
Ticker send_sme_CAN_messages_ticker;

int main() {
    printf("Hello World!!\n");

    /*
        Make send_CAN messages loop consistently
        at 20hz (20 messages / second)
    */
   send_etc_CAN_messages_ticker.attach(&send_etc_CAN_messages, 20ms);
   send_sme_CAN_messages_ticker.attach(&send_sme_CAN_messages, 20ms);





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
    std::cout << "Sending ETC CAN messages..." << std::endl;

} //add functionality

/*
    Must send the SME_RPDO_Throttle_Demand CAN
    message with SME_THROTL_TorqueDemand set to the
    torque demand determined by the ETC.
*/
void send_sme_CAN_messages() {
    std::cout << "Sending SME CAN messages..." << std::endl;
}
