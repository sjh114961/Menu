
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
int select = 0;  // used for menu selection

// set to -1 to show that nothing has been set as yet
int previousSelect = -1;  // previous menu selection

// strcture to store data need for command repeation
repeat_type repeatData;
char c;
long p1 = 0;
long p2 = 0;

bool echo = FALSE;  // echo commands input. This will slow down code,


// main menu engine, select tells it what menu
// to display. select = 0 id th the 1st or main menu
int menu(int select) {

  char c;
  char compare_command;
  long p1 = 0;
  long p2 = 0;
  int data;
  int index = 0;
  int returned_value = -1;
  unsigned long currentTime;
  unsigned long next_interval;

  bool interval_up = FALSE;

  /* This the wrapper for the array since all fuction have to be the same.
*  If the parameter isn't needed then just put anything in there as a place holder
* and it will be ignored. In most cases there is no return value so the  wrapper
* needs to return NO_RETURN or any negative number. If a postivr number is 
* returned the value will be displayed.
*/
  int (*foo)(int, int);

  /* This is the command array. These characters are the commands that are availble.
1st command character will cakk 1st function in menu_function. Notice the last item 
in each array must be NULL
*/

  foo = NULL;
  // if we are not showing the main main menu, change to it
  if (previousSelect != select) {
    initialize_main_menu(select);
    previousSelect = select;

    delay(1000);
  }

  if (repeatData.activated) {
    if (repeatData.interval != 0L) {
      if (repeatData.count-- >= 0) {

        currentTime = micros();
        next_interval = currentTime + repeatData.interval;
      }

      if (currentTime > next_interval) {
        interval_up = TRUE;
        currentTime = micros();
        next_interval = currentTime + repeatData.interval;
      }
    }
  }

  if (repeatData.count <= 0) {
    repeatData.activated = FALSE;
    /*    Serial.println("ACTIVE IS FALSE");
    delay(5000);
*/
  }
  // is there any command input?
  data = Serial.available();
  /*
  Serial.print("data: ");
  Serial.println(data);
*/

  //  if ((data > 0) || interval_up) {
  if ((data > 0) || (repeatData.activated == TRUE)) {
    index = 0;

#ifdef DEBUG
    Serial.print("data: ");
    Serial.println(data);

    Serial.print("repeatData.activated: ");
    Serial.println(repeatData.activated);
#endif

    //    delay(1000);
    delay(100);

    //    if (!interval_up) {
    if (!repeatData.activated) {

#ifdef DEBUG
      Serial.print("data: ");
      Serial.println(data);
#endif

      c = Serial.read();       // command
      p1 = Serial.parseInt();  // 1st parameter of command
      p2 = Serial.parseInt();  // 2nd parameter of command

      if (echo) {
        if (isAlpha(c)) {
          Serial.print(c);
          Serial.print(p1);
          Serial.print(" ");
          Serial.println(p2);
        }
      }

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
    } else

      delay(1000);
    foo = NULL;


    if (repeatData.activated) {
      c = repeatData.commandChar;
      p1 = repeatData.p1;
      p2 = repeatData.p2;
    }

    do {
      if (c == command_record[index].menu_command) {
#ifdef DEBUG
        Serial.print("Command found: ");
        Serial.println(data);
#endif

        foo = command_record[index].menu_function;
      }
    } while (command_record[index++].menu_command != NULL);

  }  // moved here


  if (foo != NULL) {  // if there is a commag available
    if (foo == help) {
      //      Serial.print("help found: ");
      p1 = select;
      //     Serial.println(p1);
    }
    if (foo != NULL) {
      /*      
      Serial.println("Line: 177");
      delay(1000);

      Serial.print("returned_value = foo(p1, p2);");
*/
#ifdef LINE_DEBUG
      Serial.print("FILE: ");
      Serial.print(__FILE__);
      Serial.print(" Line: ");
      Serial.println(__LINE__);
#endif

      returned_value = foo(p1, p2);
    }
    /*
 if (returned_value != NO_RETURN) {
    Serial.print("Returned value: ");
    Serial.println(returned_value);
  }
*/
    foo = NULL;  // reset for next command
  }
  if (foo != NULL) {
#ifdef LINE_DEBUG
    Serial.print("FILE: ");
    Serial.print(__FILE__);
    Serial.print(" Line: ");
    Serial.println(__LINE__);
#endif
    delay(1000);

    returned_value = foo(p1, p2);
  }

  if (returned_value != NO_RETURN) {
#ifdef LINE_DEBUG
    Serial.print("FILE: ");
    Serial.print(__FILE__);
    Serial.print(" Line: ");
    Serial.println(__LINE__);
#endif

    Serial.print("Returned value: ");
    Serial.println(returned_value);
  }
  /*
#ifdef LINE_DEBUG
Serial.print("FILE: ");
Serial.print(__FILE__);
Serial.print(" Line: ");
Serial.println(__LINE__);
#endif
*/
  foo = NULL;  // reset for next command}

  //  Serial.println("End");

  return (select);
}


// menu wrapper for digitalWrite
int gpio_write(int pin, int value) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, value);
  return (NO_RETURN);
}

// menu wrapper fir digitalRead
int gpio_Read(int pin, int value) {
  int data = NO_RETURN;

  pinMode(pin, INPUT);
  data = digitalRead(pin);
  return (data);
}

// menu wrapper for analogWrite
int pwm(int p1, int p2) {
  analogWrite(p1, p2);
  return (NO_RETURN);
}

// menu wrapper for analog_read
int analog_read(int pin, int value) {
  int returned_value = NO_RETURN;
  int data;
  returned_value = analogRead(pin);
  return (returned_value);
}

int echoFunction(int p1, int p2) {
  echo = p1;
  Serial.print("ECHO: ");
  Serial.println(echo);

  return (NO_RETURN);
}

// This function documents all viable commands.
int help(int p1, int p2) {
  switch (p1) {
    case 0:  // main menu
      Serial.println("        MENU:");
      Serial.println("h: print this menu");
      Serial.println("d: digitalwrite(p1,p2) example:d2,1");
      Serial.println("D: digitalRead(p1,p2) example:d2,anything");
      Serial.println("p: PWM(pin, dutysysle(0-255)) example:p3,128");
      Serial.println("a: analogRead(pin, anything) example:a3,128");
      Serial.println("e: echo 0= off 1=on, default is off");
      Serial.println("m: repeat submenu");
      Serial.println("");
      break;

    case 1:  // repeat menu
      Serial.println("  Repeat MENU:");
      Serial.println("h: print this menu");
      Serial.println("t: Set interval time in millisecds (t1000, anything)");
      Serial.println("c: Set repeat function command");
      Serial.println("d: display repeat function parameters");
      Serial.println("n: # of times to repeat");
      Serial.println("x: exit submenu");
      Serial.println("");
      break;
  }
  return (NO_RETURN);
}

// Sets menu system to display 1st sub menu (repeat menu)
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

// literally does nothing
int doNothing(int p1, int p2) {
  return (NO_RETURN);
}

// exit sub menu and return to main menu
int exitSubMenu(int p1, int p2) {
  select = 0;
  if (repeatData.count > 0) {
    repeatData.activated = TRUE;
    Serial.println("Repeat Activated!");
  }

  return (NO_RETURN);
}

// Sets repeat interval
int setInterval(int p1, int p2) {
  repeatData.interval = p1;
  Serial.print("SetInterval: ");
  Serial.println((unsigned)p1);
  Serial.println("");

  return (NO_RETURN);
}

// Sets nuber of tomes to repeat
int setCount(int p1, int p2) {
  repeatData.count = p1 + 1;  // account for the 0 to 1 based differance
  Serial.print("SetCount: ");
  Serial.println((unsigned)p1);
  Serial.println("");

  return (NO_RETURN);
}

// Sets repeat parameters
int setParms(int p1, int p2) {
  repeatData.p1 = p1;
  repeatData.p2 = p2;
  Serial.print("setParms: ");
  Serial.print(p1);
  Serial.print(" ");
  Serial.println(p2);
  Serial.println("");
  return (NO_RETURN);
}

int activateRepeat(int p1, int p2) {
  char c = 0;

  c = (char)p1;

  repeatData.activated = p1;
  //  c = Serial.parseInt();
  Serial.print(" Activate: ");
  Serial.println(p1);
  return (NO_RETURN);
}

// Display all repeat dara
int displayRepeat(int p1, int p2) {
  String buffer;

  Serial.println("     Repeat Data");

  buffer = "Active: ";
  buffer += repeatData.activated;
  Serial.println(buffer);
  buffer = "Count: ";
  buffer += repeatData.count;
  Serial.println(buffer);

  buffer = "Interval: ";
  buffer += (unsigned)repeatData.interval;
  Serial.println(buffer);
  buffer = "Command: ";
  buffer += repeatData.commandChar;
  Serial.println(buffer);
  buffer = "Parameter 1: ";
  buffer += repeatData.p1;
  buffer += "\r\n";
  buffer += "Parameter 2: ";
  buffer += repeatData.p2;
  Serial.println(buffer);
  Serial.println("");

  return (NO_RETURN);
}

int commandRepeat(int p1, int p2) {
  //  String buffer;
  int count = 0;
  bool noSkip = FALSE;

  Serial.print("Enter Command to repeat: ");
  Serial.flush();
  Serial.setTimeout(3000);

  //  delay(1000);


  while (!Serial.available()) {
    noSkip = TRUE;
    delay(100);
    count++;
    if (count > COMMAND_WAIT) {
      Serial.println("Timeout");
      noSkip = FALSE;
      break;
    }
  }
  if (noSkip) {
    repeatData.commandChar = Serial.read();  // command function
    repeatData.p1 = Serial.parseInt();       // 1st parameter of command
    repeatData.p2 = Serial.parseInt();       // 2nd parameter of command

    /*buffer = Serial.readStringUntil('\n');
    Serial.setTimeout(1000);
    Serial.print("Command: ");
    Serial.println(buffer);

    repeatData.command = buffer;
    */

    Serial.println("");
    Serial.print("command: ");
    Serial.print(repeatData.commandChar);
    Serial.print(repeatData.p1);
    Serial.print(" ");
    Serial.println(repeatData.p2);
  }

  Serial.setTimeout(RECEIVE_TIMEOUT);
  Serial.println("");
  return (NO_RETURN);
}

// Actually this function now initializes all menus
// select=0 for main menu
void initialize_main_menu(int select) {
  int index = 0;

  /*  
  Serial.print("initialize_main_menu select: ");
  Serial.println(select);
 */
  switch (select) {

    case 0:
      //      Serial.println("Menu 0");

      command_record[index].menu_command = 'h';
      command_record[index++].menu_function = &help;

      command_record[index].menu_command = 'd';
      command_record[index++].menu_function = &gpio_write;

      command_record[index].menu_command = 'D';
      command_record[index++].menu_function = &gpio_Read;

      command_record[index].menu_command = 'p';
      command_record[index++].menu_function = &pwm;

      command_record[index].menu_command = 'a';
      command_record[index++].menu_function = &analog_read;

      command_record[index].menu_command = 'e';
      command_record[index++].menu_function = &echoFunction;

      command_record[index].menu_command = 'm';
      command_record[index++].menu_function = &repeatMenu;

      command_record[index].menu_command = NULL;
      command_record[index++].menu_function = NULL;
      break;

    case 1:
      command_record[index].menu_command = 'h';
      command_record[index++].menu_function = &help;

      command_record[index].menu_command = 't';
      command_record[index++].menu_function = &setInterval;

      command_record[index].menu_command = 'c';

      command_record[index++].menu_function = &commandRepeat;

      command_record[index].menu_command = 'd';
      command_record[index++].menu_function = &displayRepeat;

      command_record[index].menu_command = 'x';
      command_record[index++].menu_function = &exitSubMenu;

      command_record[index].menu_command = 'n';
      command_record[index++].menu_function = &setCount;

      command_record[index].menu_command = NULL;
      command_record[index++].menu_function = NULL;

      break;
  }

  help(select, 0);
}