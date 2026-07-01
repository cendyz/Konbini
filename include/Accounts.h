#pragma once

#include <array>
#include <unordered_map>
#include <string>
#include <filesystem>

class Accounts {
    enum class AccInfo : uint8_t {
        Name = 0,
        Email,
        Password,
        AccType,
        Size
    };

public:
    Accounts();

private:
    inline static std::array<std::string, static_cast<size_t>(AccInfo::Size)> singleAcc;
    inline static std::unordered_map<std::string, std::array<std::string,
        static_cast<size_t>(AccInfo::Size)> > accs;

    static void loadAccounts();

    inline static std::filesystem::path accsFile{DATA_DIR "accounts.txt"};

    static void addAccToVar(const std::array<std::string, static_cast<size_t>(AccInfo::Size)> &arr);

    static void addAccToFile();
};
