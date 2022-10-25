#ifndef KAUTH_DASHBOARD_APPLICATIONWEBHOOK_H
#define KAUTH_DASHBOARD_APPLICATIONWEBHOOK_H

#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct ApplicationWebhook {
    std::string id;
    std::string applicationId;
    std::string trigger;
    std::string url;

public:
    static ApplicationWebhook Parse(const json& json);
};

#endif //KAUTH_DASHBOARD_APPLICATIONWEBHOOK_H