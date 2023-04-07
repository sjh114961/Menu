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

#ifndef MENU_SELECT
#define MENU_SELECT
extern int select;
extern int previousSelect;
#endif


int gpio_write(int pin, int value);
int pwm(int p1, int p2);
int analog_read(int pin, int value);
int help(int p1, int p2);

typedef struct
{
  char menu_command;
  int (*menu_function)(int, int);
} command_type;


//command_type command_record[6] = { { 'd', &gpio_write }, { 'h', &help }, { 'p', &pwm }, { 'a', &analog_read }, { NULL, NULL } };


//int help(int p1, int p2);

#define NO_RETURN -1

//#define DEBUG

int menu(int select);
int help(int p1, int p2);
int gpio_write(int pin, int value);
int pwm(int p1, int p2);
int analog_read(int pin, int value);
int repeatMenu(int p1, int p2);
int exitSubMenu(int p1, int p2);

void initialize_main_menu(int select);

#endif