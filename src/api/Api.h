#ifndef DASHBOARD_API_H
#define DASHBOARD_API_H

#include <iostream>
#include "models/Application.h"
#include "models/ApplicationUser.h"
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

using namespace cpr;
using json = nlohmann::json;
using std::string;

struct Api {
    string token;
    string host;

public:
    static void CheckResponse(const Response &response);

    static Api Login(const string &host, const string &email, const string &password);

    static Api Register(const string &host, const string &email, const string &username, const string &password);

    static bool Validate(const string &host, const string &applicationId, const string &key, const string &hwid);

    Application GetApplication(const string &applicationId) const;

    std::vector<Application> GetApplications() const;

    Application CreateApplication(const string &name) const;

    Application UpdateApplication(const string &applicationId, const string &name) const;

    void DeleteApplication(const string &applicationId) const;

    ApplicationUser GetApplicationUser(const string &applicationId, const string &user_id) const;

    std::vector <ApplicationUser> GetApplicationUsers(const string &applicationId) const;

    ApplicationUser CreateApplicationUser(const string &applicationId, const string &key, const string &hwid) const;

    ApplicationUser UpdateApplicationUser(const string &applicationId, const string &user_id, const string &key,
                                          const string &hwid) const;

    void DeleteApplicationUser(const string &applicationId, const string &user_id) const;

    json MakeRequest(const string &type, const std::map<string, string> &params = {}) const;
};

class ApiException : public std::runtime_error {
public:
    string error;
    string message;

    ApiException(const string &error, const string &message) : std::runtime_error(error + ". " + message) {
        this->error = error;
        this->message = message;
    }
};

#endif //DASHBOARD_API_H
