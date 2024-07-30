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

#define MAX_TOK_PER_LINE 52
#define MAX_TOK_SIZE 50
#define MAX_LINE_SIZE (MAX_TOK_PER_LINE * MAX_TOK_SIZE)
#define WHITE_SPACE " \t\n"

/**
 * @brief Macro function to check if number of passed arguments exceeds the limit of maximum number of tokens per line
 *
 * @param ARGC_NAME is the name of the variable that holds the argument count in the scope
 * @param go_to_cleanup must be a true or false value to activate goto command
 */
#define check_argc_size(ARGC_NAME, go_to_cleanup)                                                                                                                                                                    \
    if (argc >= MAX_TOK_PER_LINE)                                                                                                                                                                                    \
    {                                                                                                                                                                                                                \
        printf(FG_RED "error: maximum token per line exceeded (got='%d'), allowed number of token per line including one reserved, one for command and the numbers is '%d' tokens.\n", ARGC_NAME, MAX_TOK_PER_LINE); \
        must_fail = true;                                                                                                                                                                                            \
        if (go_to_cleanup)                                                                                                                                                                                           \
            goto cleanup;                                                                                                                                                                                            \
    }

/**
 * @brief Macro function to check if size of each token (argument or command) exceeds the limit of maximum number of characters per token
 *
 * @param TOKEN is the name of the variable that holds the token in the scope
 * @param go_to_cleanup must be a true or false value to activate goto command
 */
#define check_token_size(TOKEN, go_to_cleanup)                                                                                                                                                      \
    if (strlen(TOKEN) > MAX_TOK_SIZE)                                                                                                                                                               \
    {                                                                                                                                                                                               \
        printf(FG_RED "error: maximum token character limit exceeded (got='%lld' for '%s'), allowed number of characters per each token is '%d' characters.\n", strlen(TOKEN), TOKEN, MAX_TOK_SIZE); \
        must_fail = true;                                                                                                                                                                           \
        if (go_to_cleanup)                                                                                                                                                                          \
            goto cleanup;                                                                                                                                                                           \
    }

/**
 * @brief for a 2-Dimensional array which holds all tokens per each line
 *
 * CHANGE `MAX_TOK_PER_LINE` and `MAX_TOK_SIZE` based on your requirements
 * in `command.h`
 */
typedef char line_token_t[MAX_TOK_PER_LINE][MAX_TOK_SIZE];

/**
 * @brief expands to argc checker
 *
 * This macro expands to minimum arg needed check and defines a
 * arg count starter integer variable.
 *
 * it also defines `arg_starts_at` as the starting point to get the args
 *
 * @param MIN_ARG the minimum argument number that have to be received via command line.
 */
#define do_arg_check(MIN_ARG)                                                                                                                     \
    if (argc < MIN_ARG)                                                                                                                           \
    {                                                                                                                                             \
        printf(FG_RED "error: " COLOR_RESET "not enough number of arguments for '%s'\nHelp: " FG_GREEN "%s\n" COLOR_RESET, cmd->name, cmd->help); \
                                                                                                                                                  \
        exit(-1);                                                                                                                                 \
    }                                                                                                                                             \
    int arg_starts_at = (MIN_ARG - 1)

struct Command; // forward declaration to make the function pointer field work
typedef struct Command
{
    char* name;
    char* help;
    double (*invoke)(struct Command* cmd, struct Command* commands, size_t cmd_count, int argc, char argv[MAX_TOK_PER_LINE][MAX_TOK_SIZE]);
} Command;

/**
 * @brief defines an invoker function
 *
 * This macro expands to function declaration for standard invoke functions
 *
 * @param CMD_FN_IDENTIFIER command identifier name, better to end with `_fn`.
 */
#define def_invoke_fn_as(CMD_FN_IDENTIFIER) double CMD_FN_IDENTIFIER(Command* cmd, Command* commands, size_t cmd_count, int argc, char argv[MAX_TOK_PER_LINE][MAX_TOK_SIZE])

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