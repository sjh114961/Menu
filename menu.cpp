/*********************************************************************
* Menu system for Arduino code file
*
* Author: Stephen J. Heilman sj_h1@live.com
* Date: 03/31/2023
*
* This code represents an old school method of of a menuing system 
* (i.e. all text).
*
* The code uses 3 main pieces to operate. 
* 1) menu_command[] 
* 2)*menu_function[]
* 3) help file
*
**********************************************************************/

#include "menu.h"

#ifndef COMMAND_ARRAY
#define COMMAND_ARRAY
command_type command_record[MAX_MENU_ITEMS];

#endif
int select = 0;
int previousSelect = -1;

//void menu(command_type *command_record) {
int menu(int select) {

  char c;
  char compare_command;
  long p1 = 0;
  long p2 = 0;
  int data;
  int index = 0;
  int returned_value = -1;
  bool menu_up = 0;

  //  previousSelect = -1;  // set to -1 to show that nothing has been set as yet

  /* This the wrapper for the array since all fuction have to be the same.
If the parameter isn't needed then just put anything in there as a place holder
* and it will be ignored. In most cases there is no return value so the  wrapper
* needs to return NO_RETURN or any negative number. If a postivr number is 
* returned the value will be displayed.
*/
  int (*foo)(int, int);

  /* This is the command array. These characters are the commands that are availble.
1st command character will cakk 1st function in menu_function. Notice the last item 
in each array must be NULL
*/

  // if we are not showing the main main menu, change to it
  if (previousSelect != select) {
    initialize_main_menu(select);
    previousSelect = select;
    /*    
    Serial.print("Menu Initialized: ");
    Serial.print(previousSelect);
    Serial.print(" ");
    Serial.println(select);
*/
  }
  data = Serial.available();
  /*
  Serial.print("data: ");
  Serial.println(data);
*/

  if (data > 0) {
    index = 0;

#ifdef DEBUG
    Serial.print("data: ");
    Serial.println(data);
#endif

    c = Serial.read();
    p1 = Serial.parseInt();
    p2 = Serial.parseInt();

#ifdef DEBUG
    Serial.print("The char was ");
    Serial.print(c);
    Serial.print(" Parameters: ");
    Serial.print(p1);
    Serial.print(" ");
    Serial.println(p2);
#endif

    //Serial.flush();
    Serial.readString();
  } else {
    c = 255;
  }

  foo = NULL;

  //Serial.println("Start");

  do {
    if (c == command_record[index].menu_command) {
#ifdef DEBUG
      Serial.print("Command found: ");
      Serial.println(data);
#endif

      foo = command_record[index].menu_function;
    }
  } while (command_record[index++].menu_command != NULL);

  /*
  Serial.print("foo= ");
  Serial.print(foo);
  Serial.print(" ");
  Serial.print(*foo);
  Serial.print(" ");
  Serial.println(&foo);
*/

  if (foo != NULL) {
    if (foo == help) {
//      Serial.print("help found: ");
      p1 = select;
//     Serial.println(p1);
    }
    returned_value = foo(p1, p2);
    if (returned_value != NO_RETURN) {
      Serial.print("Returned value: ");
      Serial.println(returned_value);
    }
    foo = NULL;
  }

  //  Serial.println("End");
  return (select);
}


int gpio_write(int pin, int value) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, value);
  return (NO_RETURN);
}

int pwm(int p1, int p2) {
  analogWrite(p1, p2);
  return (NO_RETURN);
}

int analog_read(int pin, int value) {
  int returned_value = NO_RETURN;
  returned_value = analogRead(pin);
  return (returned_value);
}

// This function documents all viable commands.
int help(int p1, int p2) {
  switch (p1) {
    case 0:
      Serial.println("        MENU:");
      Serial.println("h: print this menu");
      Serial.println("d: digitalwrite(p1,p2) example:d2,1");
      Serial.println("p: PWM(pin, dutysysle(0-255)) example:p3,128");
      Serial.println("a: analogRead(pin, anything) example:a3,128");
      Serial.println("m: repeat submenu");
      Serial.println("");
      break;

    case 1:
      Serial.println("  Repeat MENU:");
      Serial.println("h: print this menu");
      Serial.println("y: PWM(pin, dutysysle(0-255)) example:p3,128");
      Serial.println("z: analogRead(pin, anything) example:a3,128");
      Serial.println("x: exit submenu");
      Serial.println("");
      break;
  }
  return (NO_RETURN);
}

int repeatMenu(int p1, int p2) {
  select = 1;
/*  
  Serial.print("repeatMenu: ");
  Serial.print(p1);
  Serial.print(" ");
  Serial.println(select);
*/
  return (NO_RETURN);
}

int exitSubMenu(int p1, int p2) {
  select = 0;
  Serial.print("exitSubMenu: ");
  Serial.print(p1);
  Serial.print(" ");
  Serial.println(select);
  return (NO_RETURN);
}

void initialize_main_menu(int select) {
/*  
  Serial.print("initialize_main_menu select: ");
  Serial.println(select);
*/
  switch (select) {
    case 0:
//      Serial.println("Menu 0");

      command_record[0].menu_command = 'd';
      command_record[0].menu_function = &gpio_write;

      command_record[1].menu_command = 'h';
      command_record[1].menu_function = &help;

      command_record[2].menu_command = 'p';
      command_record[2].menu_function = &pwm;

      command_record[3].menu_command = 'a';
      command_record[3].menu_function = &analog_read;

      command_record[4].menu_command = 'm';
      command_record[4].menu_function = &repeatMenu;

      command_record[5].menu_command = NULL;
      command_record[5].menu_function = NULL;
      break;
    case 1:
//      Serial.println("Menu 1");

      command_record[0].menu_command = 'h';
      command_record[0].menu_function = &help;

      command_record[1].menu_command = 'y';
      command_record[1].menu_function = &pwm;

      command_record[2].menu_command = 'z';
      command_record[2].menu_function = &analog_read;

      command_record[3].menu_command = 'x';
      command_record[3].menu_function = &exitSubMenu;

      command_record[4].menu_command = NULL;
      command_record[4].menu_function = NULL;

      break;
  }
  help(select, 0);
}