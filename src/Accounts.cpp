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

void Accounts::addAccToFile(const std::array<std::string, static_cast<size_t>(AccInfo::Size)> &arr) {
    std::ofstream file{accsFile, std::ios::app};

    for (size_t i{}; i < static_cast<size_t>(AccInfo::Size); ++i) {
        if (i == static_cast<size_t>(AccInfo::Size) - 1) {
            file << arr[i] << '\n';
        } else {
            file << arr[i] << ';';
        }
    }
}

void Accounts::addAccToDB(const std::array<std::string, static_cast<size_t>(AccInfo::Size)> &arr) {
    addAccToVar(arr);
    addAccToFile(arr);
}

std::string_view Accounts::getAdminAccType() {
    return adminAccType;
}

std::string_view Accounts::getUserAccType() {
    return userAccType;
}


bool Accounts::isCorrectNameEmail(const std::string &email, const std::string &name) {
    return accs.contains(email) && accs[email][static_cast<size_t>(AccInfo::Name)] == name;
}

std::string Accounts::getAccPassword(const std::string &email) {
    return accs[email][static_cast<size_t>(AccInfo::Password)];
}

std::string_view Accounts::getUserType(){
    return userAccType;
}

std::string_view Accounts::getAdminType(){
    return adminAccType;
}
