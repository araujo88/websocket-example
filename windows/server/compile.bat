@ECHO OFF
ECHO Compiling file ...
gcc server.c -o server.exe -lws2_32
PAUSE