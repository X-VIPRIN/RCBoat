#include <IRremote.h>

/*
A controller program for a RC-Boat, ATMega 2560.
*/

//Infared reciever information.
int infaredRecieverOne_pin = 2;
IRrecv irrecv_one(infaredRecieverOne_pin);     //Infared reciever one IR reciever library and reciever controlled.
decode_results results_infaredRecieverOne;      //results for the first IR reciever.

//Remote Information
int JVC_main_remote_current_input = 0; //Main infared remote for boat control. Current input ID stored here. Input IDs: 0 == null

void setup() {
  Serial.begin(9600); //Start Serial IO communication.
  Serial.print("Application Started");
}

void loop() {
  
  infaredRecieverController(); //Check inputs from all recievers.

}

//Controls/Manages all Infared recievers onboard of the RC Boat; Manages input and possibly output.
void infaredRecieverController() {
  
  //Each frame/application cycle, check to see the input, if nothing, then do nothing.
  //Check JVC Remote controller, "RM-C3012".
  infaredRecieverOneController();

}



//Manages data/input from infared reciever one.
void infaredRecieverOneController() {
  
  //Get the results from the IR Module, and store them in results, to be looped through latter in this method, which will then determine the current Main Ir Remote input stored @ "JVC_main_remote_current_input"
  irrecv_one.decode(&results_infaredRecieverOne);

  //Loop through the results, and set the variable "JVC_main_remote_current_input" to the remotes current input status.
  switch (results_infaredRecieverOne.value) {
    
  }

  //Infared reciever one input avaluation is complete.
  irrecv_one.resume(); // receive the next value / delete/destroy the previously recieved value and check for the next input.
}
