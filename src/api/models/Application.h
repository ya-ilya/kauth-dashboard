#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef DASHBOARD_APPLICATION_H
#define DASHBOARD_APPLICATION_H

#include <iostream>
#include "ApplicationUser.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;

struct Application {
    string id;
    string owner;
    string name;
    std::vector<ApplicationUser> users = {};

public:
    static Application Parse(const json &json);
};

#endif //DASHBOARD_APPLICATION_H

#pragma clang diagnostic pop