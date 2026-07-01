#include "Accounts.h"
#include<fstream>
#include <sstream>
#include <ranges>

Accounts::Accounts() {
    loadAccounts();
}

void Accounts::loadAccounts() {
    std::ifstream file{accsFile};
    std::string line, name, email, password, accType;
    std::array<std::string, 4> newAcc;

    while (getline(file, line)) {
        std::stringstream ss(line);

        for (std::string &s: newAcc) {
            getline(ss, s, ';');
        }

        accs.try_emplace(newAcc[static_cast<size_t>(AccInfo::Email)], newAcc);
    }
}

void Accounts::addAccToVar(const std::array<std::string,
    static_cast<size_t>(AccInfo::Size)> &arr) {
    accs.try_emplace(arr[static_cast<size_t>(AccInfo::Email)], arr);
}

void Accounts::addAccToFile() {
    std::ofstream file{accsFile, std::ios::app};

    for (size_t i{}; i < static_cast<size_t>(AccInfo::Size); ++i) {
        if (i == static_cast<size_t>(AccInfo::Size) - 1) {
            file << singleAcc[i] << '\n';
        } else {
            file << singleAcc[i] << ';';
        }
    }
}
