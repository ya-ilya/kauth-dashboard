#include "ApplicationWebhook.h"

ApplicationWebhook ApplicationWebhook::Parse(const json& json) {
    ApplicationWebhook out;

    json.at("id").get_to(out.id);
    json.at("applicationId").get_to(out.applicationId);
    json.at("trigger").get_to(out.trigger);
    json.at("url").get_to(out.url);

    return out;
}