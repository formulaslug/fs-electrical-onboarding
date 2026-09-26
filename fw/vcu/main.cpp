#include "etc_controller.h"
#include "mbed.h"
#include <cstdio>

ETCState& etc_state = etc.state;

int main() {
    printf("Hello World!!\n");

    CANMessage rx;
    while (true) {
        if (canP.read(rx)) {
            switch (rx.id) {
            case 0x391: {
            }
            }
        }

        etc.update_state();
    }

    return 0;
}

void send_etc_CAN_messages() {
    uint8_t tpdo_pedal_travel[8] = {0};
    uint16_t APPS1_scaled_voltage = static_cast<uint16_t>(etc_state.APPS1_voltage * 1000);
    uint16_t APPS2_scaled_voltage = static_cast<uint16_t>(etc_state.APPS2_voltage * 1000);
    uint16_t BPPS_scaled_voltage = static_cast<uint16_t>(etc_state.BPPS_voltage * 1000);
    tpdo_pedal_travel[0] = APPS1_scaled_voltage & 0xFF;
    tpdo_pedal_travel[1] = APPS1_scaled_voltage >> 8;
    tpdo_pedal_travel[2] = APPS2_scaled_voltage & 0xFF;
    tpdo_pedal_travel[3] = APPS2_scaled_voltage >> 8;
    tpdo_pedal_travel[4] = BPPS_scaled_voltage & 0xFF;
    tpdo_pedal_travel[5] = BPPS_scaled_voltage >> 8;
    tpdo_pedal_travel[6] = static_cast<uint8_t>(etc_state.APPS_position_avg * 100);
    tpdo_pedal_travel[7] = static_cast<uint8_t>(etc_state.BPPS_position * 100);

    CANMessage msg1{402, tpdo_pedal_travel, 8};
    can.write(msg1);
}
