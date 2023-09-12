#define TELEGRAM_TOKEN "YOURAPITOKEN"
#define TELEGRAM_CHATID "YOURCHATID"
#include "teleprintf.h"

int main() {
    tprintf("This is a test message with a number: %d and a string: %s", 42, "hello world");
    return 0;
}