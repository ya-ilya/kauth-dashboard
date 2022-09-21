#ifndef KAUTH_DASHBOARD_COMMAND_H
#define KAUTH_DASHBOARD_COMMAND_H

#include <vector>
#include <iostream>
#include <functional>

using std::string, std::cout, std::endl;

class Command {
public:
    string name;
    string usage;
    string description;
    int argumentsCount = 0;
    std::function<void(std::vector<string>)> execute;

    Command(const string &name, const string &usage, const string &description,
            const std::function<void(std::vector<string>)> &execute);
};


#endif //KAUTH_DASHBOARD_COMMAND_H
