## Reverse File Data
The goal of the reversing program is to read in the data from the specified input file and reverse it; thus, the lines should be printed out in the reverse order of the input stream.
 Example:
 
 An input file might look like this: 
````
hello
this
is 
a file
````
the output should be:
```
a file
is
this
hello
```
**Ways to invoke**
The different ways to invoke the file (as above) all correspond to slightly different ways of using this simple new Unix utility.For example, when
invoked with two command-line arguments 
```
blazex@fedora:~/initial-reverse$ ./reverse input.txt output.txt
```
the program should read from the input file the user supplies and write the reversed version of said file to the output file the user supplies.

When invoked with just one command-line argument,
```
blazex@fedora:~/initial-reverse$ ./reverse input.txt 
```
the user supplies the input file, but the file should be printed to the screen. In Unix-based systems,
printing to the screen is the same as writing to a special file known as **standard output**, or `stdout` for short.

Finally, when invoked without any arguments, 
```
blazex@fedora:~/initial-reverse$ ./reverse 
```
or,
```
blazex@fedora:~/initial-reverse$ cat input.txt | ./reverse  
```
The reversing program should read from **standard input** (`stdin`), which is the input that a user types in (or passes through piping)
and write to standard output (i.e., the screen).
# Details
**Note:**  most of the details said here, is  about `revers.c` not `reverse_linked_list.c`. 
## Errors
- **Input is the same as output:** If the input file and output file are the same file, an error message "Input and output file must
differ" and exit with return code 1. and input should also be erased due to some reasons.

- **String and file length:** if program Runs without and arguments , the Max lines through `stdin`(standard input) allowed is `MAX_LINE_STDIN == 100000`
 and the ` Line Buffer size is 10KB` . so , reversing large number of lines in file can be reversed by using arguments options.
- **Invalid files:** If an input file or output file, and for some reason, program failes to open `input.txt` 
, it  print out the following error message: `error:cannot open file 'input.txt'` and then exit with return code 1
- **Malloc fails:** In `reverse_linked_list.c` If `malloc()` fails to allocate some memory,it print the error message `malloc failed` and exit
with return code 1.
- **Too many arguments passed to program:** If the user runs `reverse` with too many arguments, print `usage: reverse <input> <output>` and exit with
return code 1.

## `reverse.c` and `reverse_linked_list.c` 
- This project contain two codes  `reverse.c` And `reversed_linked_list.c` , where `reverse.c` is more optimal and performes better than `reversed_linked_list.c` .
-  `reversed_linked_list.c`  uses dynamic memory allocation for each and every line(through `malloc` calls). which consumes more memory (in MB) ,in case of very large files (1 million+ lines).while
   `reversed.c` has a `fixed line buffer of 10KB` .
- in both programs ,input files gets read character-by-character .
- `reversed_linked_list.c`  uses linked list method and data struc.  
