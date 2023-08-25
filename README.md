# Simple Shell

A simplified shell program that allows you to run basic commands with or without arguments. It includes essential shell functionalities like `ls`, `exit`, and `env`, among others. It uses fork to carry these functions out.

## Introduction

The Simple Shell project is a command-line program that provides a basic shell environment for running commands. It allows users to execute simple commands with both interactive and non-interactive mode (using echo and a pipe to send the input to the simplified shell).
e.g. [echo "ls" | ./hsh]

## Usage

1. Clone the repository to your local machine:

   git clone https://github.com/samcalde/holbertonschool-simple_shell

2. Compile all files ending in .c using the command 'gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh'

3. Execute the program using the command ./hsh

## Functions

echo - print a string to stdout

ls - list files in current directory

pwd - print working directory

rm - remove file

## Authors

Made by Samuel Calderón and Luis Miguel Gallo while studying at Holberton School Colombia, as part of the full stack software engineering program.