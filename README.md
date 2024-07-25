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

## Implementation Phases

### Phase 1

I would like to implement this program using command pattern, by first looking at the problem I could see the repetitive form of command, `+ 1 2 3` is same as `f file.clc` as the first token is the command and the rest is argument(s).

Each command must be a structure with the following members, I would call it `Command` type:

- `char[]` for command name or `command` for short
- `char[]` for command help or `help` for short
- `invoke` which is a function pointer to the definition of a function accepting `int argc, char* argv[]` and returning `int`

I would also define all the commands in a `static` commands array that holds a couple of `Command`s.

## Phase 2

I have refactored all the codes to `commands.h`, `commands.c` and `colors.h`.

I also have created various macros to make my programming easier but I haven't forget to add comments for them!

At this phase all the main operations are finished

## Phase 3 - Loading from file

I would like to load the text file line by line and create a fake `argc`, `argv` and run the process for each line, getting the result and
add it at the top of the next line parameter lists.

I might need to change the invoker functions implementations to return actual result and manage failures using `exit` function instead.

## Phase 4 - clean ups and review the code

At this moment the code is working and finished and I would like to take a break and then review the code and make some improvements

The result for the input below (`input.clc`):

```plain
sub 1 2 3 4     4


add 5 6 7
mul 23 44

```

Is:

```bash
CLI Calculator
Processing calculations from 'input.clc':
line 1) 1.00 - 2.00 - 3.00 - 4.00 - 4.00 = -12.00
line 2) -12.00 + 5.00 + 6.00 + 7.00 = 6.00
line 3) 6.00 x 23.00 x 44.00 = 6072.00
```

result is made running `make run_input` or `./build/calc.exe f input.clc` manually.
