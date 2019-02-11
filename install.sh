#!/bin/bash

# imports per el parser


# compile and run server

#make server && ./server
g++ DataManager.cc -c DataManager.hh
g++ -o test test.cc DataManager.o
./test 
