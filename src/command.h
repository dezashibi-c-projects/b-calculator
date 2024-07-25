// ***************************************************************************************
//    Project: Calculator in C
//    File: command.h
//    Date: 2024-07-25
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: refer to readme file.
// ***************************************************************************************

#ifndef COMMANDS__H__
#define COMMANDS__H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define def_invoke_fn_as(CMD) int CMD(int argc, char* argv[])

typedef int (*invoke_fn)(int argc, char* argv[]);

typedef struct
{
    char* name;
    char* help;
    invoke_fn invoke;

} Command;

Command* __get_command(char* name, Command commands[], size_t cmd_count);
void __show_help(Command commands[], size_t cmd_count);

#define get_command(NAME, COMMANDS) __get_command(NAME, COMMANDS, sizeof(COMMANDS) / sizeof(COMMANDS[0]))
#define show_help(COMMANDS) __show_help(COMMANDS, sizeof(COMMANDS) / sizeof(COMMANDS[0]))

#endif // COMMANDS__H__