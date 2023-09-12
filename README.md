# Telenote
Telenote is a small header-only wrapper that allows you to send telegram notifications from C code. 
See `test.c` for example usage.

## Usage
Include `telenote.h` in your project and set the `TELEGRAM_TOKEN` and `TELEGRAM_CHATID`.
In your code, call `tnotify(your_message)` with whatever message you want to send. 

## Dependencies
Telenote requires curl, which, on ubuntu, you can install with 
```
sudo apt install curl
```
