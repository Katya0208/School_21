# School_21. Description of projects

School21 - Sberbank programming school.

## Projects:

### 1. Polish notation - output of the function graph on the command line based on Polish notation.

The [graph.c](https://github.com/Katya0208/School_21/blob/main/Polish_notation/graph.c) program has been developed for plotting functions defined by arbitrary expressions. To calculate the values of expressions, Dijkstra's algorithm was used to translate the expression into Polish notation. The program is assembled using a Makefile.

### 2. ping-pong - a pong game implemented on the command line.

Two versions of the game are offered:
* the usual (keyboard control) - [pong.c](https://github.com/Katya0208/School_21/blob/main/ping-pong/pong.c)
* interactive version - [pong_interactive.c](https://github.com/Katya0208/School_21/blob/main/ping-pong/pong_interactive.c)

### 3. bash-utils - a project that implements cat and grep utilities.

Supported flags cat: -b -e -n -s -t
Program: [cat.c](https://github.com/Katya0208/School_21/blob/main/bash-utils/cat/cat.c)

Supported flags grep: -e -i -v -c -l -n
Program: [grep.c](https://github.com/Katya0208/School_21/blob/main/bash-utils/grep/grep.c)

To run programs, Makefiles are located in the corresponding folders.

### 4. linux-basics - analysis of basic commands in working with linux.

Report on the work done: [report_s21.c](https://github.com/Katya0208/School_21/blob/main/linux-basics/report_s21.md)

### 5. linux-network - working with the network in linux.

Report on the work done: [report_s21.c](https://github.com/Katya0208/School_21/blob/main/linux-network/report_s21.md)

### 6. string-functions - implementation of the string.h library.

Implementation of all library functions: [s21_string.c](https://github.com/Katya0208/School_21/blob/main/string-functions/s21_string.c)

To run programs, Makefiles are located in the corresponding folders. Goal to launch [test.c] is called [test](https://github.com/Katya0208/School_21/blob/main/string-functions/Makefile). 
Gcov_report is launched via a target [gcov_report](https://github.com/Katya0208/School_21/blob/main/string-functions/Makefile).

### 7. math-functions - implementation of the math.h library.

Implementation of all library functions: [files](https://github.com/Katya0208/School_21/tree/main/math-functions/files)

To run programs, Makefiles are located in the corresponding folders. Goal to launch [test.c] is called [test](https://github.com/Katya0208/School_21/blob/main/math-functions/Makefile). 








