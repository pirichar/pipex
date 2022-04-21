#!/bin/bash

gcc main.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=1000
 valgrind --leak-check=full  --show-leak-kinds=all -s ./a.out Makefile
 rm -rf a.out
 rm -rf a.out.dSYM
