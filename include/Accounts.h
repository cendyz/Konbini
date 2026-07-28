#pragma once
#include <array>
#include <filesystem>
#include <string>
#include <unordered_map>

struct AccData
{
    std::string name, password, accType;
};

class Accounts
{
  public:
    enum class AccInfo : std::uint8_t
    {
        Name,
        Email,
        Pass,
        AccType,
        Size,
    };

    Accounts();

    void addAccToDB(const std::array<std::string, static_cast<size_t>(AccInfo::Size)>& arr);
    [[nodiscard]] static std::string_view getAdminAccType() ;
    [[nodiscard]] static std::string_view getUserAccType() ;

    [[nodiscard]] bool isCorrectNameEmail(const std::string& email, const std::string& name) const;

    [[nodiscard]] std::string getAccPassword(const std::string& email);

    [[nodiscard]] bool isAccExists(const std::string& email) const;

    [[nodiscard]] bool isEmailMatchingPassword(const std::string& email, const std::string& password) const;

    void addAccToVar(const std::array<std::string, static_cast<size_t>(AccInfo::Size)>& arr);

    void addAccToFile(const std::array<std::string, static_cast<size_t>(AccInfo::Size)>& arr) const;

    void setLoggedAccEmail(const std::string& email);

    [[nodiscard]] std::string_view getAccType();

    [[nodiscard]] std::array<std::string, static_cast<size_t>(AccInfo::Size)>& getLoggedAcc();

    [[nodiscard]] std::string getAccEmail();

    void updateAccsFile();

    void deleteAccFromVar();

    void setNewEmail(const std::string& newEmail);

    void setNewPassword(const std::string& newPass);

    void clearAccs();

  private:
    std::unordered_map<std::string, AccData> accs;

    void loadAccounts();

    std::filesystem::path accsFile{DATA_DIR "accounts.txt"};

    static constexpr std::string_view userAccType{"user"};
    static constexpr std::string_view adminAccType{"admin"};

    std::string loggedAccEmail;
    std::array<std::string, static_cast<size_t>(AccInfo::Size)> allAccInfo;

    void setActualAccInfo(const std::string& email);
};
