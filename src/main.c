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
#include "command_defs.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

def_commands{
    {"version", "shows version and build information", version_fn},
    {"add", "adds 2 or more arguments together, needs at least 1 number", addition_fn},
    {"sub", "subtracts 2 or more arguments from each other, needs at least 1 number", subtraction_fn},
    {"mul", "multiplies 2 or more arguments from each other, needs at least 1 number", multiplication_fn},
    {"div", "divides 2 or more arguments from each other, needs at least 1 number and non-zero numbers", division_fn},
    {"f", "opens the given file, runs each operations per line, insert the result of it at the beginning of the next line and continues until the end of file", file_fn},
};
def_commands_size();

int main(int argc, char* argv[])
{
    puts("CLI Calculator");

    if (argc < 2)
    {
        puts(FG_RED "error: " COLOR_RESET "not enough number of arguments\n\t" FG_GREEN "./calc.exe <op> <...args>\n" COLOR_RESET);

        show_help(commands, commands_size);

        return -1;
    }

    Command* cmd = get_command(argv[1], commands, commands_size);

    if (cmd == NULL)
    {
        printf(FG_RED "error: " COLOR_RESET "command '%s' not found\n", argv[1]);

        show_help(commands, commands_size);

        return -1;
    }

    line_token_t temp_argv;
    bool must_fail = false;

    check_argc_size(argc, false);

    for (int i = 0; i < argc; ++i)
    {

        check_token_size(argv[i], false);

        strcpy(temp_argv[i], argv[i]);
    }

    if (must_fail)
        return -1;

    cmd->invoke(cmd, commands, commands_size, argc, temp_argv);

cleanup:
    return 0;
}
