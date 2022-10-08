#include "ApplicationUser.h"

ApplicationUser ApplicationUser::Parse(const json& json) {
    ApplicationUser out;

    json.at("id").get_to(out.id);
    json.at("applicationId").get_to(out.applicationId);
    json.at("key").get_to(out.key);
    json.at("hwid").get_to(out.hwid);

    return out;
}