#ifndef TELENOTE_H
#define TELENOTE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef TELEGRAM_TOKEN
  #error "You must define TELEGRAM_TOKEN before including this header."
#endif

#ifndef TELEGRAM_CHATID
  #error "You must define TELEGRAM_CHATID before including this header."
#endif


static void tnotify(const char *message) {
    // Calculate buffer size needed for the system command.
    size_t cmd_len = strlen("curl -s -X POST https://api.telegram.org/bot")
                    + strlen(TELEGRAM_TOKEN)
                    + strlen("/sendMessage -d chat_id=")
                    + strlen(TELEGRAM_CHATID)
                    + strlen(" -d text=\"\"")
                    + strlen(message)
                    + 1;  // Null-terminator

    // Allocate memory for the system command.
    char *cmd = (char *)malloc(cmd_len);
    if (cmd == NULL) {
        fprintf(stderr, "Failed to allocate memory for system command.\n");
        return;
    }

    // Construct the system command.
    snprintf(cmd, cmd_len, "curl -s -X POST https://api.telegram.org/bot%s/sendMessage -d chat_id=%s -d text=\"%s\"",
             TELEGRAM_TOKEN, TELEGRAM_CHATID, message);

    // Execute the system command.
    system(cmd);

    // Free the allocated memory.
    free(cmd);
}

#endif  // TELENOTE_H
