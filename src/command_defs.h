// ***************************************************************************************
//    Project: Calculator in C
//    File: command_defs.h
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

#ifndef COMMAND_DEFS__H__
#define COMMAND_DEFS__H__

#include "command.h"

/**
 * @brief invoke function for `version` command
 *
 * This function prints build information
 *
 * @param cmd reference to the invoked command
 * @param commands reference to the definition of commands in main
 * @param cmd_count size of commands (number of defined commands)
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return 0
 */
def_invoke_fn_as(version_fn);

/**
 * @brief invoke function for `add` command
 *
 * This function gets one or more numbers (doubles)
 * and prints the summation of them.
 *
 * @param cmd reference to the invoked command
 * @param commands reference to the definition of commands in main
 * @param cmd_count size of commands (number of defined commands)
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return the result of the operation.
 */
def_invoke_fn_as(addition_fn);

/**
 * @brief invoke function for `sub` command
 *
 * This function gets one or more numbers (doubles)
 * and prints the subtraction of them.
 *
 * @param cmd reference to the invoked command
 * @param commands reference to the definition of commands in main
 * @param cmd_count size of commands (number of defined commands)
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return the result of the operation.
 */
def_invoke_fn_as(subtraction_fn);

/**
 * @brief invoke function for `mul` command
 *
 * This function gets one or more numbers (doubles)
 * and prints the multiplication of them.
 *
 * @param cmd reference to the invoked command
 * @param commands reference to the definition of commands in main
 * @param cmd_count size of commands (number of defined commands)
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return the result of the operation.
 */
def_invoke_fn_as(multiplication_fn);

/**
 * @brief invoke function for `div` command
 *
 * This function gets one or more numbers (doubles)
 * and prints the division of them.
 *
 * @param cmd reference to the invoked command
 * @param commands reference to the definition of commands in main
 * @param cmd_count size of commands (number of defined commands)
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return the result of the operation.
 */
def_invoke_fn_as(division_fn);

/**
 * @brief invoke function for `f` command - loads file
 *
 * This function loads the given file and calculates
 * results for each line then insert the result at the beginning
 * of the next line parameters until the end.
 *
 * @param cmd reference to the invoked command
 * @param commands reference to the definition of commands in main
 * @param cmd_count size of commands (number of defined commands)
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return the result of the operation.
 */
def_invoke_fn_as(file_fn);

#endif // COMMAND_DEFS__H__
