#include <string>
#include <vector>
#include <fstream>
#include <curl/curl.h>
// #include <filesystem>
#include <iostream>
// #include <format>

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *string)
{
    string->append(static_cast<char *>(ptr), size * nmemb);
    return size * nmemb;
}

void write_callback(void *data, size_t size, size_t nmemb, void *ptr)
{
    printf("%d %d\n", size, nmemb);
}

int main(int argc, char **argv)
{
    CURL *handle;
    /* global initialization */
    int rc = curl_global_init(CURL_GLOBAL_ALL);
    if (rc)
        return rc;

    /* initialization of easy handle */
    handle = curl_easy_init();
    if (!handle)
    {
        curl_global_cleanup();
        return CURLE_OUT_OF_MEMORY;
    }

    curl_easy_reset(handle);
    curl_easy_setopt(handle, CURLOPT_URL, "ftp://127.0.0.1/lamp_sample/");
    curl_easy_setopt(handle, CURLOPT_USERNAME, "user");
    curl_easy_setopt(handle, CURLOPT_PASSWORD, "12345");

    // curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "NLST");
    curl_easy_setopt(handle, CURLOPT_DIRLISTONLY, 1L);
    printf("%d\n", argc);
    if (argc > 1)
    {
        curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
    }
    curl_easy_setopt(handle, CURLOPT_NOPROXY, "*");
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);

    curl_easy_perform(handle);

    curl_easy_cleanup(handle);
    return 0;
}
