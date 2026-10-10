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
    
    APPS1_Volatge = APPS_sensor_1.read() * 3.3; //Read the percentage from 0.0 to 1.0 -> convert it to a voltage
    APPS2_Volatge = APPS_sensor_2.read() * 3.3;

    //Now determine the pedal postions

    


    //Now determine the pedal postions
    APPS1_Pedal_Postion = ( APPS1_Voltage - APPS1_MIN_VOLTAGE) / (APPS1_MAX_VOLTAGE - APPS1_MIN_VOLTAGE  ); //Determine Pedal Position Percentage
    APPS2_Pedal_Postion = ( APPS2_Voltage - APPS2_MIN_VOLTAGE) / (APPS2_MAX_VOLTAGE - APPS2_MIN_VOLTAGE  ); //Determine Pedal Position Percentage

    //Clamp Pedal position percentages to be from 0% to 100%, i.e. 0.0 to 1.0
    Clamped_APPS1_Pedal_Position = clamp( APPS1_Pedal_Postion - PEDAL_DEADZONE_PERCENTAGE/(1.0 - 2.0 * PEDAL_DEADZONE_PERCENTAGE));// Subtract by DeadZone percentage to adjust to our "new" 0% 
    Clamped_APPS2_Pedal_Position = clamp( APPS2_Pedal_Postion - PEDAL_DEADZONE_PERCENTAGE/(1.0 - 2.0 * PEDAL_DEADZONE_PERCENTAGE)); // Then divide by 1-PEDAL_DEADZONE_PERCENTAGE to get our "new" 100% pedal position


    //Calculate a motor torque demanad
    Motor_Torque_Demand = ((Clamped_APPS1_Pedal_Postion + Clamped_APPS2_Pedal_Postion) / 2.0f) * (MAX_TORQUE);

    
        

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
    
    

    //Check if Volatages corresponding to APPS1 and APPS2 are valid!!!!!


    
    int64_t duration_Range_Implaus = 0; //Timer For Range Implaus
    int64_t duration_Percent_Implaus = 0; //Timer for Percent Implaus

    bool APPS_Sensors_Range_Implaus = !(in_range(APPS1_Volatge, APPS1_MIN_VOLTAGE, APPS1_MAX_VOLTAGE) && in_range(APPS2_Volatge, APPS2_MIN_VOLTAGE, APPS2_MAX_VOLTAGE));
    //Determines weather the APPS Sensors are in Valid Voltage Range, if in range sets it to false, 
    
    if (APPS_Sensors_Range_Implaus) { //If there is a Range Implaus,start the timer to see how long it is occuring
        Timer_Range_Implaus.start(); //Start Timer
        
        duration_Range_Implaus = my_timer_Range.elapsed_time().count() / 1000;  
        //Record Time that has passed since timer was initially started 

        

    }

    if(!APPS_Sensors_Range_Implaus){
        Timer_Range_Implaus.stop();
        Timer_Range_Implaus.reset();
    }
    
    if( duration_Range_Implaus > 100){
        APPS_Range_Implausibility_Confirmed = true;
    }



    //Check if two pedal postions are within 10%
    //Then time for 100msec and if problem persists, stop power

    

    float Percentage_Difference = std::abs(APPS1_Pedal_Position - APPS2_Pedal_Position); 
    if( Percentage_Difference <= 0.10){
        Timer_Percent_Implaus.stop();
        Timer_Percent_Implaus.reset();
    }else{
        // Valid_Voltages = false;
        timer_Percent_Implaus.start();

        duration_ms_Percent_Implaus = my_timer_Percent_Implaus.elapsed_time().count() / 1000;
        
        if( duration_Percent_Implaus > 100){
            APPS_Percent_Implausibility_Confirmed = true;
        }
        
    }

    
   

    

    /*
        End of implaus logic checking.
    */

    /*
        Check how long each implaus has been active for and
        update the actual implaus result if it's been active 
        for too long.
    */



    
}
