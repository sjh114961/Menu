/*********************************************************************
* Menu system for Arduino execution shell
*
* Author: Stephen J. Heilman sj_h1@live.com
* Date: 03/31/2023
*
* This code represents an old school method of of a menuing system 
* (i.e. all text).
**********************************************************************/

#include "menu.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Code Started: ");

  select = 0;  // select main menu
  previousSelect = -1;
  digitalWrite(LED_BUILTIN, HIGH);
//  help(0, 0); 

  repeatData.interval = 0;
  repeatData.testTime = 0;
  repeatData.responseString = "The repeated reponse was : ";
  repeatData.Function = &doNothing;
  repeatData.p1 = 0;
  repeatData.p2 = 0;
}

void loop() {
  //command_type command_record[6] = { { 'd', &gpio_write }, { 'h', &help }, { 'p', &pwm }, { 'a', &analog_read }, { NULL, NULL } };

  previousSelect = menu(select);
/*
  delay(1000);
      
    Serial.print("select != previousSelect ");
    Serial.print(previousSelect);
    Serial.print(" ");
    Serial.println(select);

    previousSelect = menu(select);
    delay(1000);
*/  

}

