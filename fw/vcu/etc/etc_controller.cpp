//
// Created by Jackson Pinsonneault on 3/24/26.
//
// Adding something to Test Git Committ :)
// Adding something else to ensure everything is fine!


#include "etc_controller.h"


// Assign appropriate GPIO objects depending on pin parameters
ETCController::ETCController(PinName APPS1_pin, PinName APPS2_pin)
    : APPS_sensor_1(APPS1_pin), //Initialize AnalogIn Pin so we can read their voltages later when we need them
    APPS_sensor_2(APPS2_pin)
{

}  







/* 
    Nice function to write which returns a wrapped version of the
    value given between 0 and 1 (-0.1 => 0, 10 => 1, 0.3 => 0.3).
*/
float ETCController::clamp(float value) {
    if( value < 0.0){
        return 0.0;
    }else if( value > 1.0){
        return 1.0;
    }else{
        return value;
    }
}





/*
    Simple function to write which returns a bool of true or false
    depending on whether low <= value <= high is true.
*/
bool ETCController::in_range(float value, float low, float high) {
    return( value >= low && value <= high );
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
    
    float APPS1_Volatge = APPS_sensor_1.read() * 3.3; //Read the percentage from 0.0 to 1.0 -> convert it to a voltage
    float APPS2_Volatge = APPS_sensor_2.read() * 3.3;

    //Now determine the pedal postions

    


    //Now determine the pedal postions
    float APPS1_Pedal_Postion = APPS1_Voltage/ (APPS1_MAX_VOLTAGE - APPS1_MIN_VOLTAGE  ); //Determine Pedal Position Percentage
    float APPS2_Pedal_Postion = APPS2_Voltage/ (APPS2_MAX_VOLTAGE - APPS2_MIN_VOLTAGE  ); //Determine Pedal Position Percentage

    //Clamp Pedal position percentages to be from 0% to 100%, i.e. 0.0 to 1.0
    float Clamped_APPS1_Pedal_Position = clamp( APPS1_Pedal_Postion ); 
    float Clamped_APPS2_Pedal_Position = clamp( APPS2_Pedal_Postion ); 


    //Calculate a motor torque demanad
    float Motor_Torque_Demand = (Clamped_APPS1_Pedal_Postion + Clamped_APPS2_Pedal_Postion) / 2.0f;

    
        

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



    /*
        End of implaus logic checking.
    */

    /*
        Check how long each implaus has been active for and
        update the actual implaus result if it's been active 
        for too long.
    */

    
}
