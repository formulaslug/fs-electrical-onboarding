//
// Created by Jackson Pinsonneault on 3/24/26.
//

#include "etc_controller.h"

// Assign appropriate GPIO objects depending on pin parameters
ETCController::ETCController(PinName PC1, PinName PC2) {}

/* 
    Nice function to write which returns a wrapped version of the
    value given between 0 and 1 (-0.1 => 0, 10 => 1, 0.3 => 0.3).
*/
float ETCController::clamp(float value) {}
//if not faulting, clamp values, feed into update state

/*
    Simple function to write which returns a bool of true or false
    depending on whether low <= value <= high is true.
*/
bool ETCController::in_range(float value, float low, float high) {
    return (value >= low) && (value <= high);
}
//used to feed into implausibility logic, if one value is low, while the other is high, trigger fault

void ETCController::apps_1_pedal_position_calc(int apps1_voltage , int apps_1_volt_increment) {
    apps_1_pedal_position = (apps1_voltage - APPS1_MIN_VOLTAGE) / (apps_1_volt_increment);
}

void ETCController::apps_2_pedal_position_calc(int apps2_voltage , int apps_2_volt_increment) {
    apps_2_pedal_position = (apps2_voltage - APPS2_MIN_VOLTAGE) / (apps_2_volt_increment);
}

/*
    Complicated method with the goal of refreshing voltages,
    pedal positions, implausibilities, and motor torque demand.
*/
void ETCController::update_state() {
    /*
        Retrieve both APPS sensor voltages, determine pedal
        positions from globally set variables in header file, 
        then calculate a motor torque demand based off the 
        average if the two positions. 

        If you want an extra challenge, include the pedal
        deadzone percentage when determining pedal positions. 
        If you want to get really difficult, maybe even 
        include your own pedal mapping to make it non linear!
    */

    //if not faulting, calculate torque and send command
    if (!gen_faulting) {
    }



    /*
        Finish the step listed above.
    */

    // Here to simplify this function and readability.
    update_implausibilities();
}

/*
    Timer based logic for the ETC to be rules compliant. MUST
    include rules T.4.2.4, T.4.2.9 (out of range).
*/
void ETCController::update_implausibilities() {
    /*
        Start of implaus logic checking.
    */
   //implaus 1
    if (apps1_voltage == apps2_voltage) {
        if (!implaus_1) {
            implaus1_timer.start();
        }
    gen_implaus = true;
    implaus_1 = true;
   } else {
    implaus_1 = false;
    implaus1_timer.stop();
    implaus1_timer.reset();
    //need to add separate logic for gen_implaus so it isnt cleared by any of the other cases being false
   }  // fault if values are equal

  //implaus 2
   if (in_range(apps1_voltage, APPS1_MIN_VOLTAGE,    APPS1_MAX_VOLTAGE) == false) {
    if (!implaus_2) {
            implaus2_timer.start();
    }
    implaus_2 = true;
    gen_implaus = true;
   } else {
    implaus_2 = false;  
    implaus2_timer.stop();
    implaus2_timer.reset();
   } 

   //implaus 3
   if (in_range(apps2_voltage, APPS2_MIN_VOLTAGE, APPS2_MAX_VOLTAGE) == false) {
    if (!implaus_3) {
            implaus3_timer.start();
        }
    implaus_3 = true;
    gen_implaus = true;
   } else {
    implaus_3 = false;   
    implaus3_timer.stop();
    implaus3_timer.reset();
   } //fault if apps2 is outside range

   //implaus 4
   if (2 * abs(apps_1_pedal_position - apps_2_pedal_position) / (apps_1_pedal_position + apps_2_pedal_position) > 0.1) { //need to change to post offset values
    if (!implaus_4) {
            implaus4_timer.start();
        }
    implaus_4 = true;
    gen_implaus = true;
   } else {
    implaus_4 = false;  
    implaus4_timer.stop();
    implaus4_timer.reset();
   } //fault if values are too far apart

   if (gen_implaus) {
    int64_t implaus1_length  = implaus1_timer.elapsed_time().count(); //what happens if timer hasnt been started? does it return 0 or does it break?
    int64_t implaus2_length  = implaus2_timer.elapsed_time().count();
    int64_t implaus3_length  = implaus3_timer.elapsed_time().count();
    int64_t implaus4_length  = implaus4_timer.elapsed_time().count();

    if (implaus1_length >= 100 || implaus2_length >= 100 || implaus3_length >= 100 || implaus4_length >= 100) {
        gen_faulting = true;
        printf("Implaus 1 Timer: %lld\n", (long long)implaus1_length);
        printf("Implaus 2 Timer: %lld\n", (long long)implaus2_length);
        printf("Implaus 3 Timer: %lld\n", (long long)implaus3_length);
        printf("Implaus 4 Timer: %lld\n", (long long)implaus4_length);
    }
   } else { //start timer if implaus is true, if timer reaches 100ms, fault then read fault type and print message to console
    gen_faulting = false;
}

    //cross check APPS1 with APPS2
    //check pedal positions pre-offset calculations; pre-offset values should not match
    //check voltage readings; if values match, fault

    /*
        End of implaus logic checking.
    */


    /*
        Check how long each implaus has been active for and
        update the actual implaus result if it's been active 
        for too long.
    */
   //create logic for clearing fault
      

    //if values have been implausible for longer than 100ms, trigger fault

}