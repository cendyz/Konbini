#pragma once

#include <array>
#include <unordered_map>
#include <string>
#include <filesystem>

class Accounts {
public:
    enum class AccInfo : uint8_t {
        Name = 0,
        Email,
        Password,
        AccType,
        Size
    };

    Accounts();
    static void addAccToDB(const std::array<std::string, static_cast<size_t>(AccInfo::Size)> &arr);

    [[nodiscard]] static std::string_view getAdminAccType();
    [[nodiscard]] static std::string_view getUserAccType();

    [[nodiscard]] static bool isCorrectNameEmail(const std::string &email, const std::string &name);

    [[nodiscard]] static std::string getAccPassword(const std::string &email);

private:
    inline static std::unordered_map<std::string, std::array<std::string,
        static_cast<size_t>(AccInfo::Size)> > accs;

    static void loadAccounts();

    inline static std::filesystem::path accsFile{DATA_DIR "accounts.txt"};

    static constexpr std::string_view userAccType{"user"};
    static constexpr std::string_view adminAccType{"admin"};

    static void addAccToVar(const std::array<std::string, static_cast<size_t>(AccInfo::Size)> &arr);
    static void addAccToFile(const std::array<std::string, static_cast<size_t>(AccInfo::Size)> &arr);
};
