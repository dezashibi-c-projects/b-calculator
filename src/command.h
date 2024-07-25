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

#include <stdlib.h>

/**
 * @brief defines an invoker function
 *
 * This macro expands to function declaration for standard invoke functions
 *
 * @param CMD command identifier name, better to end with `_fn`.
 */
#define def_invoke_fn_as(CMD) int CMD(void* cmd, int argc, char* argv[])

/**
 * @brief expands to argc checker
 *
 * This macro expands to minimum arg needed check and defines a
 * arg count starter integer variable.
 *
 * @param MIN_ARG the minimum argument number that have to be received via command line.
 */
#define do_arg_check(MIN_ARG)                                                                                                                                             \
    if (argc < MIN_ARG)                                                                                                                                                   \
    {                                                                                                                                                                     \
        printf(FG_RED "error: " COLOR_RESET "not enough number of arguments for '%s'\nHelp: " FG_GREEN "%s\n" COLOR_RESET, ((Command*)cmd)->name, ((Command*)cmd)->help); \
                                                                                                                                                                          \
        return -1;                                                                                                                                                        \
    }                                                                                                                                                                     \
    int arg_starts_at = MIN_ARG

typedef int (*invoke_fn)(void* cmd, int argc, char* argv[]);

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