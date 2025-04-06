/*
 * File: cloud.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef CLOUD_H
#define CLOUD_H

#include <curl/curl.h>
#include <string>
#include <stdexcept>

class CloudClient {
private:
    CURL* curl;
    std::string apiEndpoint;
    std::string apiKey;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
        data->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
public:
    CloudClient(const std::string& endpoint, const std::string& key)
        : apiEndpoint(endpoint), apiKey(key) {
        curl = curl_easy_init();
        if (!curl) throw std::runtime_error("Failed to initialize libcurl");
    }
    ~CloudClient() { if (curl) curl_easy_cleanup(curl); }
    void uploadData(float temperature) {
        std::string json = "{\"temperature\": " + std::to_string(temperature) + "}";
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, apiEndpoint.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(nullptr, ("Authorization: Bearer " + apiKey).c_str()));
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) throw std::runtime_error("curl_easy_perform() failed");
    }
};

#endif // CLOUD_H
