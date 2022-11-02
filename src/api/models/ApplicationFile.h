#ifndef KAUTH_DASHBOARD_APPLICATIONFILE_H
#define KAUTH_DASHBOARD_APPLICATIONFILE_H

#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct ApplicationFile {
    std::string id;
    std::string applicationId;
    std::string fileName;

public:
    static ApplicationFile Parse(const json& json);
};

#endif //KAUTH_DASHBOARD_APPLICATIONFILE_H