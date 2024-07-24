# Calculator in C

Combine basic programming concepts to create a command-line calculator.

## User Story

As an aspiring C programmer, I want to implement a command-line calculator tool to assist with various calculations as described below.

- General usage: `./calc <command> <argument(s)>`.
- Possible commands are:
  - `+` : Add all the arguments together.
  - `-` : Subtract all the arguments from each other.
  - `*` : Multiply all the arguments together.
  - `/` : Divide all the arguments by each other.
  - `f` : Load instructions from a file, perform the calculations, and display the results on the screen.

### Example of file input for the `f` command

#### **input.clc**

```plain
- 1 2 3 4
+ 5 6 7
* 23 44
```

**NOTE:** Each line's result will be used as the first parameter of the next line, and the result of the last line will be printed out on the screen.

## Project Structure

- Use a multiple file structure with a proper `Makefile`.
- The `Makefile` uses 3 different folder for better file organization.
  - `src` for source files
  - `obj` for object files
  - `build` for executables and build artifact
  - as always I've used `.exe` only for making the `Makefile` work easier on windows too.
