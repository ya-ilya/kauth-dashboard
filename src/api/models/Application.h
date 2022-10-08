#ifndef KAUTH_DASHBOARD_APPLICATION_H
#define KAUTH_DASHBOARD_APPLICATION_H

#include <iostream>
#include <nlohmann/json.hpp>
#include "ApplicationUser.h"

using json = nlohmann::json;

struct Application {
    std::string id;
    std::string owner;
    std::string name;
    std::vector<ApplicationUser> users = {};

public:
    static Application Parse(const json& json);
};

#endif //KAUTH_DASHBOARD_APPLICATION_H