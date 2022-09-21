#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#include "ApplicationUser.h"

ApplicationUser ApplicationUser::Parse(const json &json) {
    ApplicationUser out;

    json.at("id").get_to(out.id);
    json.at("applicationId").get_to(out.applicationId);
    json.at("key").get_to(out.key);
    json.at("hwid").get_to(out.hwid);

    return out;
}

#pragma clang diagnostic pop