# Simple_Linux_Shell
A simple linux shell written by C
```This is a simple shell that can read and interpret commands(no more than 10 parameters), also has the capability to deal with many kinds of inputs.``` 

```functions:

```w4118_sh.c: the main function, run() function(run the loop to access user's input) and generate_pipe() function(recursive function, which can pipe and fork).

```prompt.c: prompt function, which shows the prompt for the user.

```interpret_input.c: interpret user's input and translate it to parameters.

```add_history.c: add items to history list.

```built_in: deal with the built_in commands(exit, cd , and history).

```s2i.c: translate a string into an integer.

```clear_history: clear the history list.

```interpret_line: interpret a line with the delimtor.

```builtin_pipe:deal with the builtin commands in a pipe situation.

```and the header: w4118_sh.h, which defines all the functions and macro definitions

```Makefile: make the binary file to generate and clean it. 
