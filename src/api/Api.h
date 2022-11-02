#ifndef KAUTH_DASHBOARD_API_H
#define KAUTH_DASHBOARD_API_H

#include <fstream>
#include <iostream>
#include "models/Application.h"
#include "models/ApplicationUser.h"
#include "models/ApplicationWebhook.h"
#include "models/ApplicationFile.h"
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

using namespace cpr;
using json = nlohmann::json;

struct Api {
    std::string token;
    std::string host;

public:
    static void CheckResponse(const Response& response);

    static Api Login(const std::string& host, const std::string& email, const std::string& password);

    static Api Register(const std::string& host, const std::string& email, const std::string& username, const std::string& password);

    static bool Validate(const std::string& host, const std::string& applicationId, const std::string& key, const std::string& hwid);

    static bool Validate(const std::string& host, const std::string& applicationId, const std::string& key, const std::string& hwid,
                         const std::string& fileId);

    Application GetApplication(const std::string& applicationId) const;

    std::vector<Application> GetApplications() const;

    Application CreateApplication(const std::string& name) const;

    Application UpdateApplication(const std::string& applicationId, const std::string& name) const;

    void DeleteApplication(const std::string& applicationId) const;

    ApplicationUser GetApplicationUser(const std::string& applicationId, const std::string& userId) const;

    std::vector<ApplicationUser> GetApplicationUsers(const std::string& applicationId) const;

    ApplicationUser CreateApplicationUser(const std::string& applicationId, const std::string& key, const std::string& hwid) const;

    ApplicationUser UpdateApplicationUser(const std::string& applicationId, const std::string& userId, const std::string& key,
                                          const std::string& hwid) const;

    void DeleteApplicationUser(const std::string& applicationId, const std::string& userId) const;

    ApplicationWebhook GetApplicationWebhook(const std::string& applicationId, const std::string& webhookId) const;

    std::vector<ApplicationWebhook> GetApplicationWebhooks(const std::string& applicationId) const;

    ApplicationWebhook CreateApplicationWebhook(const std::string& applicationId, const std::string& trigger, const std::string& url) const;

    ApplicationWebhook UpdateApplicationWebhook(const std::string& applicationId, const std::string& webhookId, const std::string& trigger,
                                                const std::string& url) const;

    void DeleteApplicationWebhook(const std::string& applicationId, const std::string& webhookId) const;

    ApplicationFile GetApplicationFile(const std::string& applicationId, const std::string& fileId) const;

    std::vector<ApplicationFile> GetApplicationFiles(const std::string& applicationId) const;

    ApplicationFile CreateApplicationFile(const std::string& applicationId, const std::string& fileName, char*& byteArray) const;

    void DeleteApplicationFile(const std::string& applicationId, const std::string& fileId) const;

    json MakeRequest(const std::string& type, const std::map<std::string, std::string>& params = {}) const;

    json MakeRequest(const std::string& type, const std::map<std::string, std::string>& params, const std::string& contentType,
                     const std::string& body) const;
};

class ApiException : public std::runtime_error {
public:
    std::string error;
    std::string message;

    ApiException(const std::string& error, const std::string& message) : std::runtime_error(error + ". " + message) {
        this->error = error;
        this->message = message;
    }
};

#endif //KAUTH_DASHBOARD_API_H
