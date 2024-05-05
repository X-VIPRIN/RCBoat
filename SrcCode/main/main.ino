#include <IRremote.h>

/*
A controller program for a RC-Boat, ATMega 2560.
*/

//Infared reciever information.
int infaredRecieverOne_pin = 2;
IRrecv irrecv_one(infaredRecieverOne_pin);     //Infared reciever one IR reciever library and reciever controlled.
decode_results results_infaredRecieverOne;      //results for the first IR reciever.

//Motor power variables; Holds booleans, controlling weather motors should be on or off.
int rearLeftIsPowered = 0; //0 = false, 1 = true
int rearRightIsPowered = 0;

//Motor ports
const int rearLeftMotorPort = 3;
const int rearRightMotorPort = 4;

void setup() {

  //Set both drive motor ports to output mode
  pinMode(rearLeftMotorPort, OUTPUT);
  pinMode(rearRightMotorPort, OUTPUT);

  irrecv_one.enableIRIn(); //Enable inputs and detection from "irrecv_one" (IR reciever one for control inputs) IR module.
  Serial.begin(9600); //Start Serial IO communication.
  Serial.print("Application Started"); //Log application start.
}

void loop() {
  
  //If input is detected from the "irrecv_one" main IR input reciever for boat control, the loop through all the known inputs, and carry out an action or set a value for other parts of the application to use.
  if (irrecv_one.decode(&results_infaredRecieverOne)) {
    irrecv_one_inputSwitch(); //Loop through all inputs, and carry out an action or set a value for later use in the application
    irrecv_one.resume(); //Start checking for IR inputs on the main IR input reciever for boat control.
  }

  drive_motorPowerController(); //Manage/Control the motors, based on boolean values, as to weather the motors should be on or not. These values are mainly originating from inputs from the IR remote in method "irrecv_one_inputSwitch()";
}


//Controls the main drive motors.
//Controls boats motors based on the motor power variables.
void drive_motorPowerController() {
  //If the rear left drive motor has its power status set to on, then power it.
  if (rearLeftIsPowered == 1) {
    digitalWrite(rearLeftMotorPort, 255);
  } else {
    digitalWrite(rearLeftMotorPort, 0);
  }

  //If the rear right drive motor has its power status set to on, then power it.
  if (rearRightIsPowered == 1) {
    digitalWrite(rearRightMotorPort, 255);
  } else {
    digitalWrite(rearRightMotorPort, 0);
  }
}


//Sets values and carries out actions based on the input from "irrcev_one", the main IR input reciever.
//Inputs for boat control.
void irrecv_one_inputSwitch() {
  switch (results_infaredRecieverOne.value) {
    //If "up-arrow" is pressed, drive forward.
    case 3772778233:
      rearLeftIsPowered = 1;
      rearRightIsPowered = 1;
      break;
    
    //If "left-arrow", then spin the right motor to turn left.
    case 3772819033:
      rearLeftIsPowered = 0;
      rearRightIsPowered = 1;
      break;

    //If the "right-arrow" is pressed, then spin the left motor to turn right.
    case 3772794553:
      rearLeftIsPowered = 1;
      rearRightIsPowered = 0;
      break;

    //If "OK" is pressed, break/stop (cut the motors power).
    case 3772782313:
      rearLeftIsPowered = 0;
      rearRightIsPowered = 0;
      break;
  }
}





