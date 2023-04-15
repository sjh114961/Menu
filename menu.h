/*********************************************************************
* Menu system for Arduino prototype file
*
* Author: Stephen J. Heilman sj_h1@live.com
* Date: 03/31/2023
*
* This code represents an old school method of of a menuing system 
* (i.e. all text).

**********************************************************************/

#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#define MAX_MENU_ITEMS 10
#define MAX_COMMAND_LENGTH 10
#define COMMAND_WAIT 100  // 1= 100 millisec
#define RECEIVE_TIMEOUT 100L

#ifndef MENU_SELECT
#define MENU_SELECT
extern int select;
extern int previousSelect;
#endif

#define FALSE 0
#define TRUE 1

//void parseString(String theString, char &c, int &p1, int &p2);

extern  char c;
extern  long p1;
extern  long p2;


int gpio_write(int pin, int value);
int pwm(int p1, int p2);
int analog_read(int pin, int value);
int help(int p1, int p2);
int echoFunction(int p1, int p2);

typedef struct
{
  char menu_command;
  int (*menu_function)(int, int);
} command_type;

typedef struct
{
  bool activated;           // turn on repeat
  int count;                // # of times to repeat
  unsigned long interval;   // time between execution in ms.
  String responseString;    // String to use for response
  String command;           // input command string, pre-parse
  char commandChar;         // command to execute see help
  int p1;                   // 1st parameter for command
  int p2;                   // 2nd parameter fot command
} repeat_type;

extern repeat_type repeatData;
extern bool echo;
//command_type command_record[6] = { { 'd', &gpio_write }, { 'h', &help }, { 'p', &pwm }, { 'a', &analog_read }, { NULL, NULL } };


//int help(int p1, int p2);

#define NO_RETURN -1

//#define DEBUG
//#define LINE_DEBUG 

int menu(int select);
int help(int p1, int p2);
int gpio_write(int pin, int value);
int pwm(int p1, int p2);
int analog_read(int pin, int value);
int repeatMenu(int p1, int p2);
int exitSubMenu(int p1, int p2);
int doNothing(int p1, int p2);
int setParms(int p1, int p2);
int displayRepeat(int p1, int p2);

void initialize_main_menu(int select);

#endif