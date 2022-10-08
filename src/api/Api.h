#ifndef KAUTH_DASHBOARD_API_H
#define KAUTH_DASHBOARD_API_H

#include <iostream>
#include "models/Application.h"
#include "models/ApplicationUser.h"
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

    Application GetApplication(const std::string& applicationId) const;

    std::vector<Application> GetApplications() const;

    Application CreateApplication(const std::string& name) const;

    Application UpdateApplication(const std::string& applicationId, const std::string& name) const;

    void DeleteApplication(const std::string& applicationId) const;

    ApplicationUser GetApplicationUser(const std::string& applicationId, const std::string& user_id) const;

    std::vector<ApplicationUser> GetApplicationUsers(const std::string& applicationId) const;

    ApplicationUser CreateApplicationUser(const std::string& applicationId, const std::string& key, const std::string& hwid) const;

    ApplicationUser UpdateApplicationUser(const std::string& applicationId, const std::string& user_id, const std::string& key,
                                          const std::string& hwid) const;

    void DeleteApplicationUser(const std::string& applicationId, const std::string& user_id) const;

    json MakeRequest(const std::string& type, const std::map<std::string, std::string>& params = {}) const;
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
