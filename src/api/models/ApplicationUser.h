#ifndef KAUTH_DASHBOARD_APPLICATIONUSER_H
#define KAUTH_DASHBOARD_APPLICATIONUSER_H

#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct ApplicationUser {
    std::string id;
    std::string applicationId;
    std::string key;
    std::string hwid;

public:
    static ApplicationUser Parse(const json& json);
};

#endif //KAUTH_DASHBOARD_APPLICATIONUSER_H