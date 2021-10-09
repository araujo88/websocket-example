@ECHO OFF
ECHO Compiling file ...
gcc client.c -o client.exe -lws2_32
PAUSE