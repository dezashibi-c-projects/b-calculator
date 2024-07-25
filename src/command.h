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

#include <stdio.h>
#include <stdlib.h>

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
        exit(-1);                                                                                                                                                         \
    }                                                                                                                                                                     \
    int arg_starts_at = (MIN_ARG - 1)

struct Command; // forward declaration to make the function pointer field work
typedef struct Command
{
    char* name;
    char* help;
    double (*invoke)(struct Command* cmd, struct Command* commands, size_t cmd_count, int argc, char* argv[]);
} Command;

/**
 * @brief defines an invoker function
 *
 * This macro expands to function declaration for standard invoke functions
 *
 * @param CMD_FN_IDENTIFIER command identifier name, better to end with `_fn`.
 */
#define def_invoke_fn_as(CMD_FN_IDENTIFIER) double CMD_FN_IDENTIFIER(Command* cmd, Command* commands, size_t cmd_count, int argc, char* argv[])

/**
 * @brief get certain commands from commands array
 *
 * This function searches the array of commands and return pointer to the
 * found `Command` element with the `name` field equal to the given name.
 *
 * @param name the command name got from the cli argument
 * @param commands the reference to the commands array
 * @param cmd_count size of the commands array
 *
 * @return Command* -> pointer to the found command in the array
 */
Command* get_command(char* name, Command commands[], size_t cmd_count);

/**
 * @brief shows usage message when something happens
 *
 *
 * @param commands the reference to the commands array
 * @param cmd_count size of the commands array
 *
 * @return void
 */
void show_help(Command commands[], size_t cmd_count);

#define def_commands static Command commands[] =
#define def_commands_size() static const size_t commands_size = (sizeof(commands) / sizeof(commands[0]))

#endif // COMMANDS__H__