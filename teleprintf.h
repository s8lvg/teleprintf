#ifndef TELEPRINTF_H
#define TELEPRINTF_H

#include <curl/curl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *TELEGRAM_TOKEN = NULL;
char *TELEGRAM_CHATID = NULL;
char *bot_url = NULL;

static void tprintf_init(char *token, char *chatid) {
  TELEGRAM_TOKEN = token;
  TELEGRAM_CHATID = chatid;

  // Create bot request url
  int bot_url_len = strlen(TELEGRAM_TOKEN) +
                    strlen("https://api.telegram.org/bot/sendMessage")+1;
  bot_url = malloc(bot_url_len);
  if (bot_url == NULL) {
    fprintf(stderr, "[!] Failed to allocate memory for bot_url.\n");
    return;
  }
  snprintf(bot_url, bot_url_len, "https://api.telegram.org/bot%s/sendMessage",TELEGRAM_TOKEN);

  // Init libcurl
  curl_global_init(CURL_GLOBAL_ALL);
}

static void tprintf_destroy() {
  curl_global_cleanup();
  free(bot_url);
}

static void tprintf(const char *format, ...) {
  // Check if library has been initialized
  if (TELEGRAM_CHATID == NULL || TELEGRAM_TOKEN == NULL) {
    fprintf(
        stderr,
        "[!] tprintf_init has to be called first to initialize the library.n");
    return;
  }

  // Initialize va_list and process variable arguments
  va_list args;
  va_start(args, format);

  // Determine the length of the message
  int message_len = vsnprintf(NULL, 0, format, args);
  va_end(args); // Reset args to call va_start again

  if (message_len < 0) {
    fprintf(stderr, "[!] An error occurred while formatting the message.\n");
    return;
  }

  // Allocate buffer for the formatted message
  char *message = (char *)malloc(message_len + 1);
  if (message == NULL) {
    fprintf(stderr, "[!] Failed to allocate memory for message.\n");
    return;
  }

  // Generate the formatted message
  va_start(args, format);
  vsnprintf(message, message_len + 1, format, args);
  va_end(args);

  // Allocate and build post params
  int post_param_len =
      strlen("chat_id=&text=\"\"") + strlen(TELEGRAM_CHATID) + message_len;

  char *post_params = (char *)malloc(post_param_len + 1);
  if (post_params == NULL) {
    fprintf(stderr, "[!] Failed to allocate memory for post params.\n");
    free(message);
    return;
  }

  snprintf(post_params, post_param_len, "chat_id=%s&text=\"%s\"",
           TELEGRAM_CHATID, message);

  CURL *curl;
  CURLcode res;

  // get a curl handle
  curl = curl_easy_init();
  if (curl) {
    // Telegram bot api url
    curl_easy_setopt(curl, CURLOPT_URL, bot_url);

    // Set post data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_params);

    // Perform the request, res will get the return code
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      fprintf(stderr, "[!] curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    // Cleanup
    curl_easy_cleanup(curl);
  } else {
    fprintf(stderr, "[!] Could not get curl handle.\n");
  }

  free(message);
}

#endif // TELEPRINTF_H
