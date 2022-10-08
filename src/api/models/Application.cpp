#include "Application.h"

Application Application::Parse(const json& json) {
    Application out;

    json.at("id").get_to(out.id);
    json.at("owner").get_to(out.owner);
    json.at("name").get_to(out.name);

    for (const auto& userJson : json.at("users")) {
        out.users.push_back(ApplicationUser::Parse(userJson));
    }

    return out;
}