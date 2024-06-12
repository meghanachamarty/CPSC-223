# **Pset3: Ahoy Matey!**
### **Due Wed, Mar 1 2023**
Ahoy, matey! This exercise will get you started programming Hookbook. In this assignment, you will be practicing **file I/O operations**, **structs**, **dynamic memory allocation**, **array lists**, **sorting**, and **software engineering** in C.
## **The Assignment**
HookBook is a hot new social media platform built for pirates, by pirates (bulldogs are kind of piratey, right?). To create a HookBook, you'll load a list of pirates from a file and add them to a list that you've created. For this assignment, the only information about each pirate that you will be given is their name. 

However, your swashbuckling clientele is in the process of creating profiles for themselves that they will give you at a later date. This means that your Hookbook program must easily transform to accept a list of pirates that includes all kinds of additional information about them:

- Their current vessel of employ
- Their current captain (who is another pirate!)
- The number of treasures they've found
- Their favorite port of call
- Maybe other things

After the list of pirates is loaded by your program, your job will be to display the name of each pirate, sorted in alphabetical order, with each one followed by a newline.

**Note**: As with input, the printing of names only is something of a placeholder until the pirates give you their full profiles. You'll be given instructions on how to display the pirates' profiles later, but your program must be ready to easily adapt to that future requirement.
### **To summarize**
Your program must:

1. Load a list of pirate names from a file whose name is given to you as a command-line argument
1. Add those pirates into a list, and sort that list in alphabetical order
1. Display the names of the pirates, sorted alphabetically
1. All of the above steps must be taken with the fact in mind that future requirements will increase the information you will hold about each pirate.
## **Files you are given**
- pirate.h (Type Definition), with the following (partial) type definition. You must complete the task marked by TODO.

// Type of a pirate

typedef /\* TODO: complete this typedef \*/ pirate;

- pirate\_list.h (Interface), with the following declarations. **You may not change anything in this file**.

// Type of a list of pirates

typedef struct implementation pirate\_list;

/\*

` `\* Allocate memory for a new pirate\_list and return a pointer to it

` `\*/

pirate\_list \*list\_create();

/\*

` `\* Return the index of the pirate with the same name as p, or a value greater than or equal to the length of the list if the pirate is not in the list.

` `\*/

size\_t list\_index\_of(pirate\_list\* pirates, pirate\* p);

/\*

` `\* Only if there is no pirate in the list with the same name as p, insert pirate p into the list at index idx by copying the pointer, shifting the latter part of the list one â€œslotâ€ to the right.

` `\* If there is a pirate in the list with the same name as p, do nothing, and return a pointer to the pirate that was not inserted.

` `\* If the pirate was inserted into the list, return NULL

` `\*/

pirate\* list\_insert(pirate\_list\* pirates, pirate\* p, size\_t idx);

/\*

` `\* Remove the pirate from the list with the same name as p, and return a pointer to it.

` `\* If there is no pirate in the list with the same name as p, return NULL

` `\*/

pirate\* list\_remove(pirate\_list\* pirates, pirate\* p);

/\*

` `\* Return a pointer to the pirate pointed to by index idx in the list, or NULL if idx is not a valid index (i.e., it is >= the length of the list).

` `\*/

pirate\* list\_access(pirate\_list\* pirates, size\_t idx);

/\*

` `\* Sort the list of pirates in alphabetical order by name

` `\*/

void list\_sort(pirate\_list\* pirates);

/\*

` `\* Return the number of pirates in the list.

` `\*/

size\_t list\_length(pirate\_list\* pirates);

/\*

` `\* Free all memory associated with the pirate\_list, but leave the memory associated with the pirates in the list untouched (it is someone else's job to free the pirates; maybe that dog with the keys in the Pirates of the Caribbean).

` `\*/

void list\_destroy(pirate\_list\* pirates);

- makefile (Incomplete)
  - The provided makefile defines two variables, CC and CFLAGS. You must submit a makefile having identical values for those two variables:

CC = gcc

CFLAGS = -std=c17 -Wall -Werror -pedantic -g

- The first target, HookBook, is incomplete and you must complete it, however, you must not change its name or its position in the file.
- The rest of makefile is up to you.
## **Files you must create**
- hookbook.c (Driver)
  - This will be the file where your main function is going to be. Your main function must:
    - Take as the only command-line argument the path to a file containing the pirates' names who will be placed into our HookBook.
    - Open that file and read from it the list of pirate names, appearing one on each line, storing them in a pirate\_list\*
    - Sort the list in [lexicographic (TODO: fix link)](https://wikipedia.org/lexicographic_ordering) order by pirate name
    - Print the sorted list to stdout, with one pirate name per line, following the last pirate's name with a newline character
    - Release all resources (files, memory, *etc.*)
- pirate\_list.c (Implementation), containing a body for every function declared in pirate\_list.h, and a definition for struct implementation
  - pirate\_list must be implemented as an **array list**, *a.k.a.* **resizing array**
  - The initial capacity of the list must be defined as a constant named INITIAL\_CAPACITY, having value 25
  - When the array capacity changes, it must change by a factor of 2, which must be the value of a constant named RESIZE\_FACTOR
  - In addition to functions declared in pirate\_list.h, pirate\_list.c must contain a declaration and implementation for each of the following two "helper" functions that are not declared in the header file:

/\*

` `\* Check if the actual number of pirates in the array is "too large"; if it is, increase the capacity of the array by a factor of RESIZE\_FACTOR.

` `\* If the array capacity was changed, print to stderr the string "Expand to ", followed by the new capacity of the list and a newline. Here is a possible print statement:

` `\*

` `\*     fprintf(stderr, "Expand to %zu\n", new\_capacity);

` `\*

` `\* If the capacity was not changed, do nothing.

` `\*/

void list\_expand\_if\_necessary(pirate\_list\* pirates);

/\*

` `\* Check if the actual number of pirates in the array is "too small"; if it is, decrease the capacity of the array by a factor of RESIZE\_FACTOR.

` `\* If the array capacity was changed, print to stderr the string "Contract to " followed by the new capacity of the list. Here is a possible print statement:

` `\*

` `\*     fprintf(stderr, Contract to %zu\n, new\_capacity);

` `\*

` `\* If the capacity was not changed, do nothing.

` `\*

` `\* The capacity of the array must never fall below INITIAL\_CAPACITY!

` `\*/

void list\_contract\_if\_necessary(pirate\_list\* pirates);
## **Other requirements**
- If you factor out some or all of the functionality of main into helper functions (such as a function to print the list), you must create a header file and a source file **separate from hookbook.c** with their declarations and bodies, respectively. The additional files may be named anything you like, but it must be a "good" name to earn full style points. We suggest "libhookbook".
- You may modify pirate.h as you see fit (except that there *must* remain a declaration of a type named pirate). This includes declaring functions in that file or making the struct an **opaque struct**. If you make such modifications, you must also create a C source file named pirate.c with bodies for functions declared in pirate.h and/or the definition of the opaque struct.
- Each header and source file must use #include directives to include things that are *directly* used by that file—no more, no less. Style points will be deducted for clearly extraneous #include directives or directives that rely on transitive inclusions.
- You may not use qsort to sort the list, nor any other pre-implemented sorting function. You **must** implement a sorting algorithm on your own, and it must run in $O(n^2)$ time or better and use $O(n)$ additional memory (or less), where $n$ is the number of items in the list.

**Note**: These efficiency bounds are quite permissive. In a later assignmnet you will have an opportunity to implement a faster sorting algorithm, running in average-case $O(n \log n)$ time and using $O(1)$ additional memory.

- You must create *exactly one* pirate for each name in the input file—you may not create copies of pirates (copying *pointers* to pirates is OK)
## **Suggestions and Notes**
- In class, we implemented a naive array list to which you could append and remove ints from just one end. Use that to jump start your implementation of pirate\_list.
- Factor out the functionality of main into several well-named, easily-understood functions
- Do not use a raw char\* for pirate information—remember, your program must easily adapt to store additional information about each pirate later on!
- To help manage #include directives, draw a "map" of your project's files, with arrows marking direct dependencies, and use that to write your include directives
- NULL is a special pointer value that means "points to nothing". Attempting to dereference NULL will result in a segmentation fault, which your program must avoid.
## **Correctness**
We will release a downloadable testing script on Feb 17 with which you can test that your code conforms to the prescribed output format (which is quite a bit more straightforward than in previous assignments) on a limited set of test cases. The README file associated with that download will contain instructions for adding your own test cases to the tests directory. We recommend that you add some to increase the breadth of tests for your project.

Your code will also be tested against an autograder running on Gradescope's servers. In the event that your code produces output from the autograder that does not match what you expect—or if the Gradescope autograder simply does not cooperate—your submission will be run on the Zoo, which will be treated as the "official" output from your code. **It is therefore imperative that you test your program on the Zoo to confirm its behavior.**
### **Examples**
Here are several example runs of the program showing the output both to stdout and to stderr.

1. File with three names

File: A\_list.txt

jack sparrow

william turner

elizabeth swan

Command and output:

$ ./HookBook A\_list.txt

elizabeth swan

jack sparrow

william turner

1. File with 30 names

File: B\_list.txt

TODO: 30 names here

Command and output:

$ ./HookBook B\_list.txt

Expand to 50

TODO: 30 names here
## **Assumptions**
You may assume the following about the command-line arguments to the program:

- **Nothing!** We will run your program with no command-line arguments, many command-line arguments, and a single command-line argument that is the name of a file that does not exist. In all cases where the first command-line argument is not the name of file from which you can read, your program must exit with status code 1 and not cause any errors such as segmentation faults.

You may assume the following about the file referred to by the command-line argument, if you can open it for reading:

- It is a text file. That is, we will not try to open a binary file, *e.g.*, an image
- Every line contains exactly one name
- No name in the file will be longer than 64 characters
- No name in the file will contain any non-ASCII characters
## **Submission**
Submit your project to Gradescope by uploading all files needed to run your program. An easy way to do so is by creating a zip file containing those files and uploading that to Gradescope. Be careful to zip *only the files*, and not the *directory* containing those files.

You may also upload the files individually to Gradescope through its upload interface.
