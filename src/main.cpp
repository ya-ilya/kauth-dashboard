#include <iostream>
#include <regex>
#include "api/models/Application.h"
#include "api/Api.h"
#include "cli/Menu.h"

using namespace std;

vector<string> Split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

int main() {
    Api api;
    string application_id;
    string menu_name = "root";

    /** APPLICATION **/
    Menu application("application");

    application.AddCommand("info", "", "Info about current application",
                           [&api, &application_id](const vector<string> &args) {
                               const auto &application = api.GetApplication(application_id);

                               cout << "----------------------------" << endl;
                               cout << "Application ID: " + application.id << endl;
                               cout << "Application Name: " + application.name << endl;
                               cout << "Application Users Count: " + to_string(application.users.size()) << endl;
                               cout << "----------------------------" << endl;
                           });

    application.AddCommand("getusers", "", "List of application users",
                           [&api, &application_id](const vector<string> &args) {
                               for (const auto &user: api.GetApplicationUsers(application_id)) {
                                   cout << "----------------------------" << endl;
                                   cout << "User ID: " + user.id << endl;
                                   cout << "User Key: " + user.key << endl;
                                   cout << "User Hwid: " + user.hwid << endl;
                                   cout << "----------------------------" << endl;
                               }
                           });

    application.AddCommand("getuser", "<user_id>", "Get user by it's id",
                           [&api, &application_id](const vector<string> &args) {
                               try {
                                   const auto &user = api.GetApplicationUser(application_id, args[0]);

                                   cout << "----------------------------" << endl;
                                   cout << "User ID: " + user.id << endl;
                                   cout << "User Key: " + user.key << endl;
                                   cout << "User Hwid: " + user.hwid << endl;
                                   cout << "----------------------------" << endl;
                               } catch (const ApiException &ex) {
                                   cout << "User not found" << endl;
                               }
                           });

    application.AddCommand("createuser", "<key> <hwid>", "Create user with specifed key and hwid",
                           [&api, &application_id](const vector<string> &args) {
                               const auto &user = api.CreateApplicationUser(application_id, args[0], args[1]);

                               cout << "User with key " + user.key + ", hwid " + user.hwid + " created. ID: " + user.id
                                    << endl;
                           });

    application.AddCommand("updateuser", "<user_id> <key> <hwid>", "Update user key and hwid",
                           [&api, &application_id](const vector<string> &args) {
                               try {
                                   const auto &user = api.UpdateApplicationUser(application_id, args[0], args[1],
                                                                                args[2]);

                                   cout << "User " + user.id + " was updated";
                               } catch (const ApiException &ex) {
                                   cout << "User not found" << endl;
                               }
                           });

    application.AddCommand("deleteuser", "<user_id>", "Delete user by it's id",
                           [&api, &application_id](const vector<string> &args) {
                               try {
                                   api.DeleteApplicationUser(application_id, args[0]);

                                   cout << "User" + args[0] + " was deleted" << endl;
                               } catch (const ApiException &ex) {
                                   cout << "User not found" << endl;
                               }
                           });

    application.AddCommand("accounts", "", "Back to accounts menu_name", [&menu_name](const vector<string> &args) {
        menu_name = "accounts";
    });

    /** ACCOUNT **/
    Menu account("account");

    account.AddCommand("getapplications", "", "List of your applications", [&api](const vector<string> &args) {
        const auto applications = api.GetApplications();

        if (applications.empty()) {
            cout << "You don't have created applications" << endl;
            return;
        }

        for (const auto &application: applications) {
            cout << "----------------------------" << endl;
            cout << "Application ID: " + application.id << endl;
            cout << "Application Name: " + application.name << endl;
            cout << "Application Users Count: " + to_string(application.users.size()) << endl;
            cout << "----------------------------" << endl;
        }
    });

    account.AddCommand("getapplication", "<application_id>", "Get application by it's id",
                       [&api](const vector<string> &args) {
                           try {
                               const auto &application = api.GetApplication(args[0]);

                               cout << "----------------------------" << endl;
                               cout << "Application ID: " + application.id << endl;
                               cout << "Application Name: " + application.name << endl;
                               cout << "Application Users Count: " + to_string(application.users.size()) << endl;
                               cout << "----------------------------" << endl;
                           } catch (const ApiException &ex) {
                               cout << "Application not found" << endl;
                           }
                       });

    account.AddCommand("createapplication", "<name>", "Create application with specifed name",
                       [&api](const vector<string> &args) {
                           const auto &application = api.CreateApplication(args[0]);

                           cout << "Application with name " + application.name + " created. ID: " + application.id
                                << endl;
                       });

    account.AddCommand("updateapplication", "<application_id> <name>", "Update applications name",
                       [&api](const vector<string> &args) {
                           try {
                               const auto &application = api.UpdateApplication(args[0], args[1]);

                               cout << "Application " + application.id + " was updated";
                           } catch (const ApiException &ex) {
                               cout << "Application not found" << endl;
                           }
                       });

    account.AddCommand("deleteapplication", "<application_id>", "Delete application by it's id",
                       [&api](const vector<string> &args) {
                           try {
                               api.DeleteApplication(args[0]);

                               cout << "Application" + args[0] + " was deleted";
                           } catch (const ApiException &ex) {
                               cout << "Application not found" << endl;
                           }
                       });

    account.AddCommand("applicationmenu", "<application_id>", "Open application menu_name",
                       [&application_id, &menu_name](const vector<string> &args) {
                           application_id = args[0];
                           menu_name = "application";
                       });
    /** END ACCOUNT **/

    /** ROOT **/
    Menu root("root");

    root.AddCommand("login", "<host> <email> <password>", "Login kauth account",
                    [&api, &menu_name](const vector<string> &args) {
                        api = Api::Login(args[0], args[1], args[2]);
                        menu_name = "account";
                    });

    root.AddCommand("register", "<host> <email> <username> <password>", "Register kauth account",
                    [&api, &menu_name](const vector<string> &args) {
                        api = Api::Register(args[0], args[1], args[2], args[3]);
                        menu_name = "account";
                    });

    root.AddCommand("validate", "<host> <application_id> <key> <hwid>", "Validate application user",
                    [](const vector<string> &args) {
                        cout << "Validate Result: " << Api::Validate(args[0], args[1], args[2], args[3]) << endl;
                    });
    /** END ROOT **/

    map<string, Menu> menus = {
            {"root",        root},
            {"account",     account},
            {"application", application}
    };

    while (true) {
        Menu current = menus[menu_name];
        cout << menu_name << "> ";
        string input;
        getline(cin, input);
        vector<string> args = Split(input, ' ');

        if (args[0] == "exit") {
            break;
        }

        current.TryExecute(args);
    }

    return 0;
}