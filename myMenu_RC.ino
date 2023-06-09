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
  String buffer = "t1000 9";

  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Code Started: ");

  select = 0;  // select main menu
  previousSelect = -1;

#ifdef LINE_DEBUG
  Serial.print("FILE: ");
  Serial.print(__FILE__);
  Serial.print(" Line: ");
  Serial.println(__LINE__);
#endif

  Serial.setTimeout(RECEIVE_TIMEOUT);
  digitalWrite(LED_BUILTIN, HIGH);

  repeatData.activated = FALSE;
  repeatData.count = 0;
  repeatData.interval = 0;
  repeatData.responseString = "The repeated reponse was : ";
  repeatData.p1 = 0;
  repeatData.p2 = 0;
  }

  void loop() {

    previousSelect = menu(select);
   }
