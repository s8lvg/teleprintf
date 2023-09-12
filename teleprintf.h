#ifndef TELEPRINTF_H
#define TELEPRINTF_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h> 

#ifndef TELEGRAM_TOKEN
  #error "You must define TELEGRAM_TOKEN before including this header."
#endif

#ifndef TELEGRAM_CHATID
  #error "You must define TELEGRAM_CHATID before including this header."
#endif

static void tprintf(const char *format, ...) {
    // Initialize va_list and process variable arguments
    va_list args;
    va_start(args, format);

    // Determine the length of the message
    int message_len = vsnprintf(NULL, 0, format, args);
    va_end(args);  // Reset args to call va_start again

    if (message_len < 0) {
        fprintf(stderr, "An error occurred while formatting the message.\n");
        return;
    }

    // Allocate buffer for the formatted message
    char *message = (char *)malloc(message_len + 1);
    if (message == NULL) {
        fprintf(stderr, "Failed to allocate memory for message.\n");
        return;
    }

    // Generate the formatted message
    va_start(args, format);
    vsnprintf(message, message_len + 1, format, args);
    va_end(args);

    // Calculate buffer size needed for the system command
    size_t cmd_len = strlen("curl -s -X POST https://api.telegram.org/bot")
                    + strlen(TELEGRAM_TOKEN)
                    + strlen("/sendMessage -d chat_id=")
                    + strlen(TELEGRAM_CHATID)
                    + strlen(" -d text=\"\"")
                    + message_len
                    + 1;  // Null-terminator

    // Allocate memory for the system command
    char *cmd = (char *)malloc(cmd_len);
    if (cmd == NULL) {
        fprintf(stderr, "Failed to allocate memory for system command.\n");
        free(message);
        return;
    }

    // Construct the system command
    snprintf(cmd, cmd_len, "curl -s -X POST https://api.telegram.org/bot%s/sendMessage -d chat_id=%s -d text=\"%s\"",
             TELEGRAM_TOKEN, TELEGRAM_CHATID, message);

    // Execute the system command
    system(cmd);

    // Free the allocated memory
    free(cmd);
    free(message);
}

#endif  // TELEPRINTF_H
