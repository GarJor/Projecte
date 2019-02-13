#!/bin/bash


g++ DataManager.cc -c DataManager.hh && g++ -o server server.cc DataManager.o && ./server
