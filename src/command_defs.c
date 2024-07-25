// ***************************************************************************************
//    Project: Calculator in C
//    File: command_defs.c
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

#include "command_defs.h"
#include "colors.h"
#include "command.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

def_invoke_fn_as(version_fn)
{
    (void)cmd;
    (void)argc;
    (void)argv;
    (void)cmd;
    (void)commands;
    (void)cmd_count;

    puts(FG_LRED "Version: 1.0.0" COLOR_RESET);
    puts(FG_LGREEN "Programmed by Navid Dezashibi" COLOR_RESET);
    puts(FG_LGREEN "Built on: "__DATE__
                   " - "__TIME__ COLOR_RESET);

    return 0;
}

def_invoke_fn_as(addition_fn)
{
    (void)cmd;
    (void)commands;
    (void)cmd_count;

    do_arg_check(3);

    double result = atof(argv[arg_starts_at]);
    printf("%.2f", result);

    for (int i = arg_starts_at + 1; i < argc; ++i)
    {
        double number = atof(argv[i]);
        printf(" + %.2f", number);
        result += number;
    }

    printf(FG_LBLUE " = %.2f\n" COLOR_RESET, result);

    return result;
}

def_invoke_fn_as(subtraction_fn)
{
    (void)cmd;
    (void)commands;
    (void)cmd_count;

    do_arg_check(3);

    double result = atof(argv[arg_starts_at]);
    printf("%.2f", result);
    for (int i = arg_starts_at + 1; i < argc; ++i)
    {
        double number = atof(argv[i]);
        printf(" - %.2f", number);
        result -= number;
    }

    printf(FG_LBLUE " = %.2f\n" COLOR_RESET, result);

    return result;
}

def_invoke_fn_as(multiplication_fn)
{
    (void)cmd;
    (void)commands;
    (void)cmd_count;

    do_arg_check(3);

    double result = atof(argv[arg_starts_at]);
    printf("%.2f", result);

    for (int i = arg_starts_at + 1; i < argc; ++i)
    {
        double number = atof(argv[i]);
        printf(" x %.2f", number);
        result *= number;
    }

    printf(FG_LBLUE " = %.2f\n" COLOR_RESET, result);

    return result;
}

def_invoke_fn_as(division_fn)
{
    (void)commands;
    (void)cmd_count;

    do_arg_check(3);

    double result = atof(argv[arg_starts_at]);
    printf("%.2f", result);

    for (int i = arg_starts_at + 1; i < argc; ++i)
    {
        double number = atof(argv[i]);
        printf(" / %.2f", number);
        if (number == 0)
        {
            printf(FG_RED "error: " COLOR_RESET "division by zero '%s'\nHelp: " FG_GREEN "%s\n" COLOR_RESET, cmd->name, cmd->help);

            exit(-1);
        }

        result /= number;
    }

    printf(FG_LBLUE " = %.2f\n" COLOR_RESET, result);

    return result;
}

def_invoke_fn_as(file_fn)
{
    do_arg_check(3);

    bool must_fail = false;

    FILE* file = fopen(argv[arg_starts_at], "r");

    if (file == NULL)
    {
        printf(FG_RED "error: " COLOR_RESET "cannot open the file '%s', '%s'\nHelp: " FG_GREEN "%s\n" COLOR_RESET, argv[arg_starts_at], ((Command*)cmd)->name, ((Command*)cmd)->help);
        exit(-1);
    }

    printf("Processing calculations from '" FG_LGREEN "%s" COLOR_RESET "':\n", argv[arg_starts_at]);

    char buffer[255];           // each line can be a maximum of 255 characters
    char* temp_argv[100] = {0}; // temporary argument holder with 100 places (args) per line including 1 executable name, 1 command name, and 98 arguments
    int temp_argc;              // temporary argument count holder
    double curr_result = 0;
    int curr_line = 1;
    char* curr_tok;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // ./calc.exe <cmd> args
        // 0           1    2 3 ...
        // we always have 2 args available
        temp_argc = 2;

        // Tokenize buffer based on ' ' (whitespace) and get each word separately
        curr_tok = strtok(buffer, " \t\n");

        if (curr_tok == NULL)
            continue;

        // Allocate memory and copy command to temp_argv
        temp_argv[1] = strdup(curr_tok);
        if (temp_argv[1] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            goto cleanup;
        }

        // Copy the results for the lines after the first line
        // It will copy the result at the top of the arguments
        if (curr_line > 1)
        {
            temp_argv[arg_starts_at] = (char*)malloc(10); // Allocate sufficient memory for the result (10 digits or command letter size)
            if (temp_argv[arg_starts_at] == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                goto cleanup;
            }
            sprintf(temp_argv[arg_starts_at], "%.2f", curr_result);

            // we've already got an argument from the previous line
            ++temp_argc;
        }

        while (curr_tok != NULL)
        {
            curr_tok = strtok(NULL, " \t\n");
            if (curr_tok != NULL)
            {
                temp_argv[temp_argc] = strdup(curr_tok); // Allocate memory for each token
                if (temp_argv[temp_argc] == NULL)
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    goto cleanup;
                }
                ++temp_argc;
            }
        }

        Command* cmd = get_command(temp_argv[1], commands, cmd_count);
        if (cmd == NULL)
        {
            printf(FG_RED "error: " COLOR_RESET "command '%s' not found\n", temp_argv[1]);
            show_help(commands, cmd_count);
            goto cleanup;
        }

        printf("line %d) ", curr_line);
        curr_result = cmd->invoke(cmd, commands, cmd_count, temp_argc, temp_argv);

        ++curr_line;

        // Free allocated memory for tokens
        for (int i = 1; i < temp_argc; i++)
        {
            free(temp_argv[i]);
            temp_argv[i] = NULL;
        }
    }

cleanup:
    if (file)
        fclose(file);
    if (must_fail)
        exit(-1);
    return 0;
}