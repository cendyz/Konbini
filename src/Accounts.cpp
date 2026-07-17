#include "Accounts.h"
#include<fstream>
#include <sstream>
#include <ranges>

Accounts::Accounts()
{
    loadAccounts();
}

void Accounts::loadAccounts()
{
    std::ifstream file{accsFile};
    std::string line, name, email, password, accType;

    while (getline(file, line))
    {
        std::stringstream ss(line);

        getline(ss, name, ';');
        getline(ss, email, ';');
        getline(ss, password, ';');
        getline(ss, accType, ';');

        accs.try_emplace(email, name, password, accType);
    }

}

void Accounts::addAccToVar(const std::array<std::string,
                                            static_cast<size_t>(AccInfo::Size)>& arr)
{
    accs.try_emplace(arr[static_cast<size_t>(AccInfo::Email)],
                     arr[static_cast<size_t>(AccInfo::Name)], arr[static_cast<size_t>(AccInfo::Pass)],
                     arr[static_cast<size_t>(AccInfo::AccType)]);
}

void Accounts::addAccToFile(const std::array<std::string, static_cast<size_t>(AccInfo::Size)>& arr)
{
    std::ofstream file{accsFile, std::ios::app};

    for (size_t i{}; i < static_cast<size_t>(AccInfo::Size); ++i)
    {
        if (i == static_cast<size_t>(AccInfo::Size) - 1)
        {
            file << arr[i] << '\n';
        }
        else
        {
            file << arr[i] << ';';
        }
    }
}

void Accounts::addAccToDB(const std::array<std::string, static_cast<size_t>(AccInfo::Size)>& arr)
{
    addAccToVar(arr);
    addAccToFile(arr);
}

std::string_view Accounts::getAdminAccType()
{
    return adminAccType;
}

std::string_view Accounts::getUserAccType()
{
    return userAccType;
}


bool Accounts::isCorrectNameEmail(const std::string& email, const std::string& name)
{
    return accs.contains(email) && accs[email].name == name;
}

std::string Accounts::getAccPassword(const std::string& email)
{
    return accs[email].password;
}

std::string_view Accounts::getUserType()
{
    return userAccType;
}

std::string_view Accounts::getAdminType()
{
    return adminAccType;
}

bool Accounts::isAccExists(const std::string& email)
{
    return accs.contains(email);
}

bool Accounts::isEmailMatchingPassword(const std::string& email, const std::string& password)
{
    return accs[email].password == password;
}