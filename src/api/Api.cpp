#include "Api.h"

void Api::CheckResponse(const cpr::Response& response) {
    std::string error;
    std::string message;

    try {
        const auto responseJson = json::parse(response.text);

        if (responseJson.contains("error")) {
            error = responseJson.at("error").get<std::string>();

            if (responseJson.contains("message")) {
                message = responseJson.at("message").get<std::string>();
            }
        }
    } catch (...) {
        // Ignored
    }

    if (!error.empty()) {
        throw ApiException(error, message);
    }
}

Api Api::Login(const std::string& host, const std::string& email, const std::string& password) {
    auto response = Get(Url{host + "/login?email=" + email + "&password=" + password}, Timeout{2000});
    CheckResponse(response);
    Api api;
    api.host = host;
    api.token = json::parse(response.text).at("token").get<std::string>();
    return api;
}

Api Api::Register(const std::string& host, const std::string& email, const std::string& username,
                  const std::string& password) {
    auto response = Get(Url{host + "/register?email=" + email + "&username=" + username + "&password=" + password},
                        Timeout{2000});
    CheckResponse(response);
    Api api;
    api.host = host;
    api.token = json::parse(response.text).at("token").get<std::string>();
    return api;
}

bool Api::Validate(const std::string& host, const std::string& applicationId, const std::string& key, const std::string& hwid) {
    auto response = Get(Url{host + "/validate?application_id=" + applicationId + "&key=" + key + "&hwid=" + hwid},
                        Timeout{2000});
    CheckResponse(response);
    return json::parse(response.text).at("valid").get<bool>();
}

Application Api::GetApplication(const std::string& applicationId) const {
    return Application::Parse(MakeRequest("get_application", {
            {"application_id", applicationId}
    }));
}

std::vector<Application> Api::GetApplications() const {
    std::vector<Application> out = {};

    for (const auto& applicationJson : MakeRequest("get_applications")) {
        out.push_back(Application::Parse(applicationJson));
    }

    return out;
}

Application Api::CreateApplication(const std::string& name) const {
    return Application::Parse(MakeRequest("create_application", {
            {"name", name}
    }));
}

Application Api::UpdateApplication(const std::string& applicationId, const std::string& name) const {
    return Application::Parse(MakeRequest("update_application", {
            {"application_id", applicationId},
            {"name",           name}
    }));
}

void Api::DeleteApplication(const std::string& applicationId) const {
    MakeRequest("delete_application", {{"application_id", applicationId}});
}

ApplicationUser Api::GetApplicationUser(const std::string& applicationId, const std::string& user_id) const {
    return ApplicationUser::Parse(MakeRequest("get_application_user", {
            {"application_id", applicationId},
            {"user_id",        user_id}
    }));
}

std::vector<ApplicationUser> Api::GetApplicationUsers(const std::string& applicationId) const {
    std::vector<ApplicationUser> out = {};

    for (const auto& userJson : MakeRequest("get_application_users", {{"application_id", applicationId}})) {
        out.push_back(ApplicationUser::Parse(userJson));
    }

    return out;
}

ApplicationUser Api::CreateApplicationUser(const std::string& applicationId, const std::string& key, const std::string& hwid) const {
    return ApplicationUser::Parse(MakeRequest("create_application_user", {
            {"application_id", applicationId},
            {"key",            key},
            {"hwid",           hwid}
    }));
}

ApplicationUser Api::UpdateApplicationUser(const std::string& applicationId, const std::string& user_id, const std::string& key,
                                           const std::string& hwid) const {
    return ApplicationUser::Parse(MakeRequest("update_application_user", {
            {"application_id", applicationId},
            {"user_id",        user_id},
            {"key",            key},
            {"hwid",           hwid}
    }));
}

void Api::DeleteApplicationUser(const std::string& applicationId, const std::string& user_id) const {
    MakeRequest("delete_application_user", {
            {"application_id", applicationId},
            {"user_id",        user_id}
    });
}

json Api::MakeRequest(const std::string& type, const std::map<std::string, std::string>& params) const {
    auto url = host + "/api?type=" + type;

    for (const auto& [key, value] : params) {
        url = url.append("&").append(key)
                .append("=").append(value);
    }

    auto response = Get(Url{url}, Bearer{token}, Timeout{2000});
    CheckResponse(response);

    try {
        return json::parse(response.text);
    } catch (...) {
        return json::parse("{}");
    }
}