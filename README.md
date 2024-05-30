# ipc-challenge

For this project we would like you to demonstrate an IPC methodology. You are free to choose how you do it as long as it abides by the requirements below.

Language: C and/or C++
Must compile and run on Ubuntu 22.04.
Must pass the following data structure through the IPC process.
{
int,
float,
string data (C or C++ formatted your choice)
enum { type1, type2, type3 }
}
The receiving side should print out at minimum 10 different versions of the structure above in the following format:
int: {value}, float: {value}, string: {value}, enum {human readable, e.g type1}


# Compilation

Run the following two commands after installing the gcc C Compiler on your system.
`gcc server.c -o server -lrt`
`gcc client.c -o client -lrt`


# Usage

Ensure that the server is run first

`./server`

While the server is running, on a separate terminal tab/window, run the client

`./client`

The client code will appear not to do anything (unless you uncomment the debug code still present in the code). But the expected output for the server should show the data written to it:

## Sample Output:

`int: 0, float: 0.00, string: String0, enum: type1`  
`int: 1, float: 1.10, string: String1, enum: type2`  
`int: 2, float: 2.20, string: String2, enum: type3`  
`int: 3, float: 3.30, string: String3, enum: type1`  
`int: 4, float: 4.40, string: String4, enum: type2` 
`int: 5, float: 5.50, string: String5, enum: type3`  
`int: 6, float: 6.60, string: String6, enum: type1`  
`int: 7, float: 7.70, string: String7, enum: type2`  
`int: 8, float: 8.80, string: String8, enum: type3`  
`int: 9, float: 9.90, string: String9, enum: type1`  