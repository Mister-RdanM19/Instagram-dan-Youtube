#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

// Callback function for libcurl
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void getYouTubeData(const std::string& videoID, const std::string& apiKey) {
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://www.googleapis.com/youtube/v3/videos?part=snippet&id=" + videoID + "&key=" + apiKey;
        std::string response_string;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;

        Json::Reader reader;
        Json::Value root;
        if (reader.parse(response_string, root)) {
            std::cout << "Title: " << root["items"][0]["snippet"]["title"].asString() << std::endl;
            std::cout << "Description: " << root["items"][0]["snippet"]["description"].asString() << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    std::string videoID = "dQw4w9WgXcQ";  // Example YouTube video ID
    std::string apiKey = "YOUR_YOUTUBE_API_KEY"; // Replace with your API Key
    getYouTubeData(videoID, apiKey);
    return 0;
}
