#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef DASHBOARD_APPLICATIONUSER_H
#define DASHBOARD_APPLICATIONUSER_H

#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;

struct ApplicationUser {
    string id;
    string applicationId;
    string key;
    string hwid;

public:
    static ApplicationUser Parse(const json &json);
};

#endif //DASHBOARD_APPLICATIONUSER_H

#pragma clang diagnostic pop