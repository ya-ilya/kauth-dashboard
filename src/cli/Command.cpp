#include "Command.h"

Command::Command(const string &name, const string &usage, const string &description,
                 const std::function<void(std::vector<string>)> &execute) {
    this->name = name;
    this->usage = usage;
    this->description = description;
    this->execute = execute;

    bool opened;
    for (auto const ch: usage) {
        if (ch == '<') {
            opened = true;
        } else if (ch == '>' && opened) {
            opened = false;
            argumentsCount++;
        }
    }
}