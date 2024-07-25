// ***************************************************************************************
//    Project: Calculator in C
//    File: main.c
//    Date: 2024-07-24
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

#include "colors.h"
#include "command.h"
#include <stdio.h>

//////////////////////////////// COMMANDS DEFINITIONS

/**
 * @brief invoke function for `version` command
 *
 * This function prints build information
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return 0 on succession and -1 on failure.
 */
def_invoke_fn_as(version_fn)
{
    (void)cmd;
    (void)argc;
    (void)argv;

    puts(FG_LRED "Version: 1.0.0" COLOR_RESET);
    puts(FG_LGREEN "Programmed by Navid Dezashibi" COLOR_RESET);
    puts(FG_LGREEN "Built on: "__DATE__
                   " - "__TIME__ COLOR_RESET);

    return 0;
}

/**
 * @brief invoke function for `add` command
 *
 * This function gets one or more numbers (doubles)
 * and prints the summation of them.
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return 0 on succession and -1 on failure.
 */
def_invoke_fn_as(addition_fn)
{
    do_arg_check(3);

    double result = atof(argv[2]);
    printf("%.2f", result);

    for (int i = arg_starts_at; i < argc; ++i)
    {
        double number = atof(argv[i]);
        printf(" + %.2f", number);
        result += number;
    }

    printf(" = %.2f\n", result);

    return 0;
}

/**
 * @brief invoke function for `sub` command
 *
 * This function gets one or more numbers (doubles)
 * and prints the subtraction of them.
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return 0 on succession and -1 on failure.
 */
def_invoke_fn_as(subtraction_fn)
{
    do_arg_check(3);

    double result = atof(argv[2]);
    printf("%.2f", result);
    for (int i = arg_starts_at; i < argc; ++i)
    {
        double number = atof(argv[i]);
        printf(" - %.2f", number);
        result -= number;
    }

    printf(" = %.2f\n", result);

    return 0;
}

/**
 * @brief invoke function for `mul` command
 *
 * This function gets one or more numbers (doubles)
 * and prints the multiplication of them.
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return 0 on succession and -1 on failure.
 */
def_invoke_fn_as(multiplication_fn)
{
    do_arg_check(3);

    double result = atof(argv[2]);
    printf("%.2f", result);

    for (int i = arg_starts_at; i < argc; ++i)
    {
        double number = atof(argv[i]);
        printf(" x %.2f", number);
        result *= number;
    }

    printf(" = %.2f\n", result);

    return 0;
}

/**
 * @brief invoke function for `div` command
 *
 * This function gets one or more numbers (doubles)
 * and prints the division of them.
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return 0 on succession and -1 on failure.
 */
def_invoke_fn_as(division_fn)
{
    do_arg_check(3);

    double result = atof(argv[2]);
    printf("%.2f", result);

    for (int i = arg_starts_at; i < argc; ++i)
    {
        double number = atof(argv[i]);
        printf(" / %.2f", number);
        if (number == 0)
        {
            printf(FG_RED "error: " COLOR_RESET "division by zero '%s'\nHelp: " FG_GREEN "%s\n" COLOR_RESET, ((Command*)cmd)->name, ((Command*)cmd)->help);

            return -1;
        }

        result /= number;
    }

    printf(" = %.2f\n", result);

    return 0;
}

static Command commands[] = {
    {"version", "shows version and build information", version_fn},
    {"add", "adds 2 or more arguments together, needs at least 1 number", addition_fn},
    {"sub", "subtracts 2 or more arguments from each other, needs at least 1 number", subtraction_fn},
    {"mul", "multiplies 2 or more arguments from each other, needs at least 1 number", multiplication_fn},
    {"div", "divides 2 or more arguments from each other, needs at least 1 number and non-zero numbers", division_fn},
};

//////////////////////////////// MAIN

int main(int argc, char* argv[])
{
    puts("CLI Calculator");

    if (argc < 2)
    {
        puts(FG_RED "error: " COLOR_RESET "not enough number of arguments\n\t" FG_GREEN "./calc.exe <op> <...args>\n" COLOR_RESET);

        show_help(commands);

        return -1;
    }

    Command* cmd = get_command(argv[1], commands);

    if (cmd == NULL)
    {
        printf(FG_RED "error: " COLOR_RESET "command '%s' not found\n", argv[1]);

        show_help(commands);

        return -1;
    }

    int result = cmd->invoke(cmd, argc, argv);

    if (result == -1)
        show_help(commands);

    return result;
}
