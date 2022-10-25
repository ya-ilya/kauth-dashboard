#include <iostream>
#include <libcli/libcli.h>
#include "api/Api.h"

using namespace libcli;

int main() {
    Api api;
    Cli cli;
    std::string application_id;

    /** APPLICATION **/
    Menu application = cli.CreateMenu("application");

    application.AddCommand("info", "", "Info about current application", [&api, &application_id](const auto& args) {
        const auto& application = api.GetApplication(application_id);

        std::cout << "----------------------------" << std::endl;
        std::cout << "Application ID: " << application.id << std::endl;
        std::cout << "Application Name: " << application.name << std::endl;
        std::cout << "Application Users Count: " << std::to_string(application.users.size()) << std::endl;
        std::cout << "----------------------------" << std::endl;
    });

    application.AddCommand("getusers", "", "List of application users", [&api, &application_id](const auto& args) {
        const auto users = api.GetApplicationUsers(application_id);

        if (users.empty()) {
            std::cout << "Application doesn't have users" << std::endl;
            return;
        }

        for (const auto& user : api.GetApplicationUsers(application_id)) {
            std::cout << "----------------------------" << std::endl;
            std::cout << "User ID: " << user.id << std::endl;
            std::cout << "User Key: " << user.key << std::endl;
            std::cout << "User Hwid: " << user.hwid << std::endl;
            std::cout << "----------------------------" << std::endl;
        }
    });

    application.AddCommand("getuser", "<user_id>", "Get user by it's id", [&api, &application_id](const auto& args) {
        try {
            const auto& user = api.GetApplicationUser(application_id, args[0]);

            std::cout << "----------------------------" << std::endl;
            std::cout << "User ID: " << user.id << std::endl;
            std::cout << "User Key: " << user.key << std::endl;
            std::cout << "User Hwid: " << user.hwid << std::endl;
            std::cout << "----------------------------" << std::endl;
        } catch (const ApiException& ex) {
            std::cout << "User not found" << std::endl;
        }
    });

    application.AddCommand("createuser", "<key> <hwid>", "Create user with specifed key and hwid", [&api, &application_id](const auto& args) {
        const auto& user = api.CreateApplicationUser(application_id, args[0], args[1]);

        std::cout << "User with key " << user.key << ", hwid " << user.hwid << " created. ID: " << user.id << std::endl;
    });

    application.AddCommand("updateuser", "<user_id> <key> <hwid>", "Update user key and hwid", [&api, &application_id](const auto& args) {
        try {
            const auto& user = api.UpdateApplicationUser(application_id, args[0], args[1], args[2]);
            std::cout << "User " << user.id << " was updated";
        } catch (const ApiException& ex) {
            std::cout << "User not found" << std::endl;
        }
    });

    application.AddCommand("deleteuser", "<user_id>", "Delete user by it's id", [&api, &application_id](const auto& args) {
        try {
            api.DeleteApplicationUser(application_id, args[0]);

            std::cout << "User" << args[0] << " was deleted" << std::endl;
        } catch (const ApiException& ex) {
            std::cout << "User not found" << std::endl;
        }
    });

    application.AddCommand("getwebhooks", "", "List of application webhooks", [&api, &application_id](const auto& args) {
        const auto webhooks = api.GetApplicationWebhooks(application_id);

        if (webhooks.empty()) {
            std::cout << "Application doesn't have webhooks" << std::endl;
            return;
        }

        for (const auto& webhook : api.GetApplicationWebhooks(application_id)) {
            std::cout << "----------------------------" << std::endl;
            std::cout << "Webhook ID: " << webhook.id << std::endl;
            std::cout << "Webhook Trigger: " << webhook.trigger << std::endl;
            std::cout << "Webhook Url: " << webhook.url << std::endl;
            std::cout << "----------------------------" << std::endl;
        }
    });

    application.AddCommand("getwebhook", "<webhook_id>", "Get webhook by it's id", [&api, &application_id](const auto& args) {
        try {
            const auto& webhook = api.GetApplicationWebhook(application_id, args[0]);

            std::cout << "----------------------------" << std::endl;
            std::cout << "User ID: " << webhook.id << std::endl;
            std::cout << "User Trigger: " << webhook.trigger << std::endl;
            std::cout << "User Url: " << webhook.url << std::endl;
            std::cout << "----------------------------" << std::endl;
        } catch (const ApiException& ex) {
            std::cout << "Webhook not found" << std::endl;
        }
    });

    application.AddCommand("createwebhook", "<trigger> <url>", "Create webhook with specifed trigger and url", [&api, &application_id](const auto& args) {
        const auto& webhook = api.CreateApplicationWebhook(application_id, args[0], args[1]);

        std::cout << "Webhook with trigger " << webhook.trigger << ", url " << webhook.url << " created. ID: " << webhook.id << std::endl;
    });

    application.AddCommand("updatewebhook", "<webhook_id> <trigger> <url>", "Update webhook trigger and url", [&api, &application_id](const auto& args) {
        try {
            const auto& webhook = api.UpdateApplicationWebhook(application_id, args[0], args[1], args[2]);
            std::cout << "Webhook " << webhook.id << " was updated" << std::endl;
        } catch (const ApiException& ex) {
            std::cout << "Webhook not found" << std::endl;
        }
    });

    application.AddCommand("deletewebhook", "<webhook_id>", "Delete webhook by it's id", [&api, &application_id](const auto& args) {
        try {
            api.DeleteApplicationWebhook(application_id, args[0]);

            std::cout << "Webhook" << args[0] << " was deleted" << std::endl;
        } catch (const ApiException& ex) {
            std::cout << "Webhook not found" << std::endl;
        }
    });

    application.AddCommand("account", "", "Back to account", [&cli](const auto& args) {
        cli.SelectMenu("account");
    });

    /** ACCOUNT **/
    Menu account = cli.CreateMenu("account");

    account.AddCommand("getapplications", "", "List of your applications", [&api](const auto& args) {
        const auto applications = api.GetApplications();

        if (applications.empty()) {
            std::cout << "You don't have created applications" << std::endl;
            return;
        }

        for (const auto& application : applications) {
            std::cout << "----------------------------" << std::endl;
            std::cout << "Application ID: " << application.id << std::endl;
            std::cout << "Application Name: " << application.name << std::endl;
            std::cout << "Application Users Count: " << std::to_string(application.users.size()) << std::endl;
            std::cout << "----------------------------" << std::endl;
        }
    });

    account.AddCommand("getapplication", "<application_id>", "Get application by it's id", [&api](const auto& args) {
        try {
            const auto& application = api.GetApplication(args[0]);

            std::cout << "----------------------------" << std::endl;
            std::cout << "Application ID: " << application.id << std::endl;
            std::cout << "Application Name: " << application.name << std::endl;
            std::cout << "Application Users Count: " << std::to_string(application.users.size()) << std::endl;
            std::cout << "----------------------------" << std::endl;
        } catch (const ApiException& ex) {
            std::cout << "Application not found" << std::endl;
        }
    });

    account.AddCommand("createapplication", "<name>", "Create application with specifed name", [&api](const auto& args) {
        const auto& application = api.CreateApplication(args[0]);

        std::cout << "Application with name " << application.name << " created. ID: " << application.id << std::endl;
    });

    account.AddCommand("updateapplication", "<application_id> <name>", "Update applications name", [&api](const auto& args) {
        try {
            const auto& application = api.UpdateApplication(args[0], args[1]);

            std::cout << "Application " << application.id << " was updated";
        } catch (const ApiException& ex) {
            std::cout << "Application not found" << std::endl;
        }
    });

    account.AddCommand("deleteapplication", "<application_id>", "Delete application by it's id", [&api](const auto& args) {
        try {
            api.DeleteApplication(args[0]);

            std::cout << "Application" << args[0] << " was deleted";
        } catch (const ApiException& ex) {
            std::cout << "Application not found" << std::endl;
        }
    });

    account.AddCommand("applicationmenu", "<application_id>", "Open application menu_name", [&cli, &api, &application_id](const auto& args) {
        try {
            application_id = api.GetApplication(args[0]).id;
            cli.SelectMenu("application");
        } catch (ApiException& ex) {
            std::cout << "Application not found" << std::endl;
        }
    });
    /** END ACCOUNT **/

    /** ROOT **/
    Menu root = cli.CreateMenu("root");

    root.AddCommand("login", "<host> <email> <password>", "Login kauth account", [&cli, &api](const auto& args) {
        api = Api::Login(args[0], args[1], args[2]);
        cli.SelectMenu("account");
    });

    root.AddCommand("register", "<host> <email> <username> <password>", "Register kauth account", [&cli, &api](const auto& args) {
        api = Api::Register(args[0], args[1], args[2], args[3]);
        cli.SelectMenu("account");
    });

    root.AddCommand("validate", "<host> <application_id> <key> <hwid>", "Validate application user", [](const auto& args) {
        std::cout << "Validate Result: " << Api::Validate(args[0], args[1], args[2], args[3]) << std::endl;
    });
    /** END ROOT **/

    cli.SelectMenu("root");
    cli.Start();

    return 0;
}