#pragma once
#include <Utils.h>
#include <array>
#include <filesystem>
#include <optional>
#include <unordered_map>

class LanguageManager
{
    static constexpr size_t mainMenuSize{12};
    static constexpr size_t userMenuSize{14};
    static constexpr size_t adminMenuSize{17};

  public:
    enum class Langs : std::uint8_t
    {
        EN = 1,
        JP = 2,
    };

    enum class LoginMsg : std::uint8_t
    {
        Email = 1,
        Password = 2,
        Size = 3,
    };

    void loadLangTypeFile();

    [[nodiscard]] bool isLangTypeAlreadySet() const;

    void saveUserLangToFile() const;

    [[nodiscard]] std::optional<std::string> isCorrectUserLang(int val);

    void loadDict(const std::string& lang);

    void loadMenus();

    [[nodiscard]] std::string getUserLang();

    [[nodiscard]] std::string_view getText(const std::string& text);

    [[nodiscard]] static size_t getMainMenuSize();

    [[nodiscard]] static size_t getUserMenuSize();

    [[nodiscard]] static size_t getAdminMenuSize();

    [[nodiscard]] std::array<std::string_view, mainMenuSize> getMainMenu() const;

    [[nodiscard]] std::array<std::string_view, userMenuSize> getUserMenu() const;

    [[nodiscard]] std::array<std::string_view, adminMenuSize> getAdminMenu() const;

    void loadLoginMsgs();

    [[nodiscard]] std::string getLoginMsg(size_t i);

    void changeLang();

    void clearDict();

    [[nodiscard]] size_t getDictSize() const;

    [[nodiscard]] bool isKeyExist(const std::string& key) const;

  private:
    std::filesystem::path dictPath{DATA_DIR};
    inline static const std::filesystem::path langTypePath{DATA_DIR "langType.txt"};
    inline static std::array<std::string, 2> langsType{"en", "jp"};
    ActualLang currLang{};
    std::string userLang;

    static constexpr std::string_view dictFormat{".txt"};
    std::unordered_map<std::string, std::string> dict;
    std::array<std::string_view, mainMenuSize> mainMenu;
    std::array<std::string_view, userMenuSize> userMenu;
    std::array<std::string_view, adminMenuSize> adminMenu;

    std::array<std::string, static_cast<size_t>(LoginMsg::Size)> loginMsgs;

    template <size_t S> void fullfillMenu(std::array<std::string_view, S>& arr, const std::string& msg)
    {
        for (size_t i{}; i < S; ++i)
        {
            arr[i] = dict[msg + std::to_string(i + 1)];
        }
    }
};