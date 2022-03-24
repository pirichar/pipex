#!/bin/bash

gcc -Wall -Werror -Wextra ./src/*.c ./docs/illegal_functions.c -o pipex



printf "\033[1;33m--------------RUNNING THE TEST WITH A FACTIS INPUT FILE--------------\n\033[1;0m"
printf "\033[1;31m--------------SHOULD BE AN ERROR--------------\n\033[1;33m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex YOURMOMA3 wc file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <YOURMOMA3 wc >file3 \n\033[1;0m"
./pipex YOURMOMA3 wc file2
<YOURMOMA3 wc >file3

printf "\n\033[1;33m--------------RUNNING THE TEST WITH A FACTIS OUTPUT FILE--------------\n\033[1;0m"
printf "\033[1;32m--------------SHOULD NOT BE AN ERROR--------------\n\033[1;33m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 ls wc YOURMOMA \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 ls wc >YOURMOMA2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE diff YOURMOMA YOURMOMA2\n\033[1;0m"
./pipex file1 ls wc YOURMOMA
<file1 ls | wc >YOURMOMA2
diff YOURMOMA YOURMOMA2
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\n\033[1;0m"



printf "\033[1;33m--------------RUNNING THE TEST FOR WC \033[1;31mMIGHT BE AN ERROR\033[1;33m--------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 wc file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 wc >file3 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE diff file2 file3\n\033[1;0m"
./pipex file1 wc file2
<file1 wc >file3
diff file2 file3 
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\n\033[1;0m"


printf "\033[1;33m--------------RUNNING THE TEST FOR LS--------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 ls file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 ls >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 ls file2
<file1 ls >file3
diff file2 file3 
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\n\033[1;0m"

printf "\033[1;33m--------------RUNNING THE TEST FOR LS WC --------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 ls wc file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 ls | wc >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 ls wc file2
<file1 ls | wc >file3
diff file2 file3 
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\n\033[1;0m"


printf "\033[1;33m--------------RUNNING THE TEST FOR LASS WC \033[1;31mSHOULD BE AN ERROR\033[1;33m  --------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 lass wc file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 lass | wc >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 lass wc file2
<file1 lass | wc >file3
diff file2 file3 
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\n\033[1;0m"

printf "\033[1;33m--------------RUNNING THE TEST FOR WC LASS \033[1;31mSHOULD BE AN ERROR\033[1;33m --------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 wc lass file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 wc | lass >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 wc lass file2
<file1 wc | lass >file3
diff file2 file3 
printf "\033[1;32mIF THE COMMANDS WORKED NO WHITE ON PROMPT YOU WON\n\n\033[1;0m"

printf "\033[1;33m--------------RUNNING THE TEST FOR ls -l and wc -l --------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 \"ls -l\" \"wc -l\" lass file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 ls -l | wc -l >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 "ls -l" "wc -l" file2
<file1 ls -l | wc -l >file3
diff file2 file3 
printf "\033[1;32mIF THE COMMANDS WORKED NO WHITE ON PROMPT YOU WON\n\n\033[1;0m"

printf "\033[1;33m--------------RUNNING THE TEST FOR CAT GREP a1 WC -l --------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 \"cat\" \"grep a1\" \"wc -l\" lass file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 cat | grep a1 | wc -l >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 "cat" "grep a1" "wc -l" file2
<file1 cat | grep a1 | wc -l >file3
diff file2 file3 
printf "\033[1;32mIF THE COMMANDS WORKED NO WHITE ON PROMPT YOU WON\n\n\033[1;0m"







