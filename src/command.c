// ***************************************************************************************
//    Project: Calculator in C
//    File: command.c
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

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "command.h"

#include "colors.h"

Command* get_command(char* name, Command commands[], size_t cmd_count)
{
    assert(cmd_count > 0 && "There is no command defined");

    Command* cmd = NULL;

    for (size_t i = 0; i < cmd_count; ++i)
    {
        if (strcmp(name, commands[i].name) == 0)
        {
            cmd = &commands[i];
            break;
        }
    }

    return cmd;
}

void show_help(Command commands[], size_t cmd_count)
{
    assert(cmd_count > 0 && "There is no command defined");

    puts(FG_GREEN "available commands:" COLOR_RESET);

    for (size_t i = 0; i < cmd_count; ++i)
    {
        printf("\t" FG_LGREEN "%s" COLOR_RESET " -> " FG_LBLUE "%s\n" COLOR_RESET, commands[i].name, commands[i].help);
    }
}