# CS325_Project1
##Maximum Sum Subarray
##Project 1

##Group Number: 44
##Group Members:
  Mark Giles
  Ryan Fleming

##Compiling
  The program is written in C and is self-contained in the single file called 'project1.c'.
  In order to compile, simply use the GCC compiler to produce the executable file. The zipped
  package contains 3 files:
    - project1.c - the primary C source code file
    - MSS_Problems.txt - the input source for arrays to be tested
    - README - this readme file with compiling and running instructions
  
  In order to compile the program, unzip the files and navigate to the folder they are in and 
  type the following command on the command line:
    gcc project1.c -o project1
  
##Running
  The previous command will produce the executable file called project1. On the same command
  line prompt, type:
    project1
  This will run the program and all output is directed to the file called MSS_Results.txt
  which can be reviewed for the results.
  
##Modifications
  In order to change the input file for input arrays to be tested, simply add a file to the
  same directory and modify fopen call on line 343. The line opens a file for reading to
  calculate array values. Simply change the file name to the file of your choosing, then
  re-compile and run the program again for new results. Note that this will overwrite the
  results file and results from the previous test will be lost.
