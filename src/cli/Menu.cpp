#include "Menu.h"

template<typename T>
std::vector<T> Skip(std::vector<T> const &input, int count) {
    std::vector<string> out;

    for (int i = count; i < input.size(); ++i) {
        out.push_back(input[i]);
    }

    return out;
}

Menu::Menu(const string &name) {
    this->name = name;

    AddCommand("help", "", "List of all commands in this menu", [this](const std::vector<string> &args) {
        for (auto const &command: commands) {
            cout << ": " + command.name;

            if (!command.usage.empty()) {
                cout << " " + command.usage;
            }

            cout << " - " + command.description << endl;
        }
    });
}

void Menu::AddCommand(const std::string &cName, const std::string &usage, const std::string &description,
                      const std::function<void(std::vector<std::string>)> &execute) {
    commands.emplace_back(cName, usage, description, execute);
}

void Menu::TryExecute(const std::vector<std::string> &args) const {
    for (const auto &command: commands) {
        if (command.name == args[0]) {
            if (command.argumentsCount > args.size() - 1) {
                cout << "Not enough arguments, correct usage is - " + command.name;

                if (!command.usage.empty()) {
                    cout << " " << command.usage;
                }

                cout << endl;
                return;
            }

            try {
                command.execute(Skip(args, 1));
            } catch (std::exception &ex) {
                cout << "E: << " << ex.what() << endl;
            }
        }
    }
}