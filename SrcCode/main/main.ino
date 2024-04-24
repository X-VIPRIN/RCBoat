#include <IRremote.h>

/*
A controller program for a RC-Boat, ATMega 2560.
*/

//Infared reciever information.
int infaredRecieverOne_pin = 2;
IRrecv irrecv_one(infaredRecieverOne_pin);     //Infared reciever one IR reciever library and reciever controlled.
decode_results results_infaredRecieverOne;      //results for the first IR reciever.


void setup() {
  Serial.begin(9600); //Start Serial IO communication.
  Serial.print("Application Started");
}

void loop() {
  
  infaredRecieverController(); //Check inputs from all recievers.

}

//Controls/Manages all Infared recievers onboard of the RC Boat; Manages input and possibly output.
void infaredRecieverController() {
  
  //If a signal was detected to be recieved, then check to see the input.
  if (irrecv_one.decode(&results_infaredRecieverOne)) {
    infaredRecieverOneController();
  }
}

//Manages data/input from infared reciever one.
void infaredRecieverOneController() {
  
  Serial.print("Recieved data!");

  //Infared reciever one input avaluation is complete.
  irrecv_one.resume(); // receive the next value / delete/destroy the previously recieved value and check for the next input.
}
