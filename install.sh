#!/bin/bash

sudo apt-get install mplayer -y
g++ DataManager.cc -c DataManager.hh && g++ -o server server.cc DataManager.o && ./server
