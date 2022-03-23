#!/bin/bash

gcc -Wall -Werror -Wextra pipex.c environement.c -o pipex

printf "\033[1;33m--------------RUNNING THE TEST FOR WC--------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 wc file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 wc >file3 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE diff file2 file3\n\033[1;0m"
./pipex file1 wc file2
<file1 wc >file3
diff file2 file3 
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\033[1;0m"


printf "\033[1;33m--------------RUNNING THE TEST FOR LS--------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 ls file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 ls >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 ls file2
<file1 ls >file3
diff file2 file3 
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\033[1;0m"

printf "\033[1;33m--------------RUNNING THE TEST FOR LS WC --------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 ls wc file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 ls | wc >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 ls wc file2
<file1 ls | wc >file3
diff file2 file3 
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\033[1;0m"


printf "\033[1;33m--------------RUNNING THE TEST FOR LASS WC --------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 lass wc file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 lass | wc >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 lass wc file2
<file1 lass | wc >file3
diff file2 file3 
printf "\033[1;32mIF NO WHITE ON PROMPT YOU WON\n\033[1;0m"

printf "\033[1;33m--------------RUNNING THE TEST FOR WC LASS --------------\n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH ./pipex file1 wc lass file2 \n\033[1;0m"
printf "\033[1;34mSCRIPT TEST IS DONE WITH <file1 wc | lass >file3 \n\033[1;0m"
printf "\033[1;34mDIFF HAS BEEN DONE ON file2 file3\n\033[1;0m"
./pipex file1 wc lass file2
<file1 wc | lass >file3
diff file2 file3 
printf "\033[1;32mIF THE COMMANDS EXISTS NO WHITE ON PROMPT YOU WON\n\033[1;0m"

