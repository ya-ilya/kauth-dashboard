#include "ApplicationFile.h"

ApplicationFile ApplicationFile::Parse(const json& json) {
    ApplicationFile out;

    json.at("id").get_to(out.id);
    json.at("applicationId").get_to(out.applicationId);
    json.at("fileName").get_to(out.fileName);

    return out;
}