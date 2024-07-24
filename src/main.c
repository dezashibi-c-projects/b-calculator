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

#include <stdio.h>

int main(int argc, char *argv[])
{
    puts("Welcome!");

    for (int i = 1; i < argc; ++i)
        printf("%s\n", argv[i]);

    return 0;
}