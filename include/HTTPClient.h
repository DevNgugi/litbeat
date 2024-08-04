#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>

class HTTPClient {
public:
    HTTPClient();
    ~HTTPClient();

    std::string get(const std::string& url);

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif