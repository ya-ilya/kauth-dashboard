#ifndef KAUTH_DASHBOARD_MENU_H
#define KAUTH_DASHBOARD_MENU_H

#include <vector>
#include <iostream>
#include <functional>
#include "Command.h"

using std::string;

class Menu {
public:
    string name;
    std::vector<Command> commands;

    Menu() = default;

    explicit Menu(const string &name);

    void AddCommand(const string &cName, const string &usage, const string &description,
                    const std::function<void(std::vector<string>)> &execute);

    void TryExecute(const std::vector<string> &args) const;
};


#endif //KAUTH_DASHBOARD_MENU_H
