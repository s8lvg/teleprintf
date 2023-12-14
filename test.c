#include "teleprintf.h"

int main() {
    tprintf_init("<your-bot-token>","<your-chat-id>");
    tprintf("This is a test message with a number: %d and a string: %s", 42, "hello world");
    tprintf_destroy();
    return 0;
}