# Teleprintf
Teleprintf is a small header only wrapper that allows you to send telegram notifications from c code. 
It defines one function `tprintf` that works exactly like `printf` but sends the messages via telegram.
See `test.c` for example usage.

## Usage
Include `teleprintf.h` in your project and call `tprintf_init(char *token, char *chatid)` to initialize the library. 
In your code, call `tprintf` with whatever message you want to send.
To free all resources used by the library call `tprintf_destroy()`.

## Dependencies
Teleprintf requires libcurl, which, on ubuntu, you can install with 
```
sudo apt install curl
```
for linking pass the `-lcurl` argument like it is done in the example makefile.