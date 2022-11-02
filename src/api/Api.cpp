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

bool Api::Validate(const std::string& host, const std::string& applicationId, const std::string& key, const std::string& hwid,
                   const std::string& fileId) {
    if (!Validate(host, applicationId, key, hwid)) {
        return false;
    }

    auto stream = std::ofstream("client.jar");
    Download(stream, Url{host + "/validate?application_id=" + applicationId + "&key=" + key + "&hwid=" + hwid + "&file_id=" + fileId},
                        Timeout{2000});
    stream.close();

    return true;
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

ApplicationUser Api::GetApplicationUser(const std::string& applicationId, const std::string& userId) const {
    return ApplicationUser::Parse(MakeRequest("get_application_user", {
            {"application_id", applicationId},
            {"user_id",        userId}
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

ApplicationUser Api::UpdateApplicationUser(const std::string& applicationId, const std::string& userId, const std::string& key,
                                           const std::string& hwid) const {
    return ApplicationUser::Parse(MakeRequest("update_application_user", {
            {"application_id", applicationId},
            {"user_id",        userId},
            {"key",            key},
            {"hwid",           hwid}
    }));
}

void Api::DeleteApplicationUser(const std::string& applicationId, const std::string& userId) const {
    MakeRequest("delete_application_user", {
            {"application_id", applicationId},
            {"user_id",        userId}
    });
}

ApplicationWebhook Api::GetApplicationWebhook(const std::string& applicationId, const std::string& webhookId) const {
    return ApplicationWebhook::Parse(MakeRequest("get_application_webhook", {
            {"application_id", applicationId},
            {"webhook_id",     webhookId}
    }));
}

std::vector<ApplicationWebhook> Api::GetApplicationWebhooks(const std::string& applicationId) const {
    std::vector<ApplicationWebhook> out = {};

    for (const auto& userJson : MakeRequest("get_application_webhooks", {{"application_id", applicationId}})) {
        out.push_back(ApplicationWebhook::Parse(userJson));
    }

    return out;
}

ApplicationWebhook Api::CreateApplicationWebhook(const std::string& applicationId, const std::string& trigger, const std::string& url) const {
    return ApplicationWebhook::Parse(MakeRequest("create_application_webhook", {
            {"application_id", applicationId},
            {"trigger",        trigger},
            {"url",            url}
    }));
}

ApplicationWebhook Api::UpdateApplicationWebhook(const std::string& applicationId, const std::string& webhookId, const std::string& trigger,
                                                 const std::string& url) const {
    return ApplicationWebhook::Parse(MakeRequest("update_application_webhook", {
            {"application_id", applicationId},
            {"webhook_id",     webhookId},
            {"trigger",        trigger},
            {"url",            url}
    }));
}

void Api::DeleteApplicationWebhook(const std::string& applicationId, const std::string& webhookId) const {
    MakeRequest("delete_application_webhook", {
            {"application_id", applicationId},
            {"webhook_id",     webhookId}
    });
}

ApplicationFile Api::GetApplicationFile(const std::string& applicationId, const std::string& fileId) const {
    return ApplicationFile::Parse(MakeRequest("get_application_file", {
            {"application_id", applicationId},
            {"file_id",        fileId}
    }));
}

std::vector<ApplicationFile> Api::GetApplicationFiles(const std::string& applicationId) const {
    std::vector<ApplicationFile> out = {};

    for (const auto& userJson : MakeRequest("get_application_files", {{"application_id", applicationId}})) {
        out.push_back(ApplicationFile::Parse(userJson));
    }

    return out;
}

ApplicationFile Api::CreateApplicationFile(const std::string& applicationId, const std::string& fileName, char*& byteArray) const {
    std::stringstream body;
    body << "------KauthDashboardFile123456789\r\n";
    body << "Content-Type: multipart/form-data\r\n";
    body << "Content-Disposition: form-data; filename=\"" + fileName + "\"\r\n\r\n";
    body << byteArray << "\r\n";
    body << "------KauthDashboardFile123456789--";

    return ApplicationFile::Parse(MakeRequest("create_application_file", {
            {"application_id", applicationId}
    }, "multipart/form-data; boundary=----KauthDashboardFile123456789", body.str()));
}

void Api::DeleteApplicationFile(const std::string& applicationId, const std::string& fileId) const {
    MakeRequest("delete_application_file", {
            {"application_id", applicationId},
            {"file_id",        fileId}
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

json Api::MakeRequest(const std::string& type, const std::map<std::string, std::string>& params, const std::string& contentType,
                      const std::string& body) const {
        auto url = host + "/api?type=" + type;

    for (const auto& [key, value] : params) {
        url = url.append("&").append(key)
                .append("=").append(value);
    }

    auto response = Post(Url{url}, Header{{"Content-Type", contentType}}, Body{body}, Bearer{token}, Timeout{2000});
    CheckResponse(response);

    try {
        return json::parse(response.text);
    } catch (...) {
        return json::parse("{}");
    }
}
