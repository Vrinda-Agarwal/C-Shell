# Operating Systems Assignment 2 | C Shell
## Roll No:2021101110
### Name:Vrinda Agarwal


* > Running Shell
- - Run the command make
- -  then do ./a.out

* > main.c
- - This contains the main Shell Loop
- - Extract Arguments from command
- - Bind functions from different files together

* > echo.c
- - Prints user input after removing excess spaces.

* > pwd.c
- - Prints the present working directory.
- - Uses the getcwd function to extract the current working directory of the terminal.

* > ls.c
- - Prints all the files and directories according to the flags given.
- - Flags can be -l and -a.


* > foreground.c
- - Brings a process to the state of running.

* > background.c
- - Change the status of background process from stop to running.

* >cd.c
- - Navigates through different directories.

* > history.c
- - Prints the last 10 commands we executed on the terminal.
- - The implementation goes as follows.first we read the file and store it's contents in an array and checks if the number of commands is greater,less or equal to 20.Then accordingly commands are deleted and new commnads are added and finally written in the "history.txt" file.

* >discover.c
- - This prints all the directories and files present in the arguement.
- - This works on a recursive approach.




