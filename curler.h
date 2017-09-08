#ifndef CURLER_H
#define CURLER_H

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

std::string get(std::string url);
#endif
