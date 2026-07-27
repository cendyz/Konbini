#pragma once
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
        JP,
    };

    enum class ActualLang : std::uint8_t
    {
        EN,
        JP,
    };

    enum class LoginMsg : std::uint8_t
    {
        Email,
        Password,
        Size,
    };

    LanguageManager() = default;

    void static loadLangTypeFile();

    [[nodiscard]] static bool isLangTypeAlreadySet();

    static void saveUserLangToFile();

    [[nodiscard]] static std::optional<std::string> isCorrectUserLang(int val);

    static void loadDict(const std::string& lang);

    static void loadMenus();

    [[nodiscard]] static std::string getUserLang();

    [[nodiscard]] static std::string_view getText(const std::string& text);

    [[nodiscard]] static size_t getMainMenuSize();

    [[nodiscard]] static size_t getUserMenuSize();

    [[nodiscard]] static size_t getAdminMenuSize();

    [[nodiscard]] static std::array<std::string_view, mainMenuSize> getMainMenu();

    [[nodiscard]] static std::array<std::string_view, userMenuSize> getUserMenu();

    [[nodiscard]] static std::array<std::string_view, adminMenuSize> getAdminMenu();

    void static loadLoginMsgs();

    [[nodiscard]] static std::string getLoginMsg(size_t i);

    void static changeLang();

    void static clearDict();

  private:
    inline static std::filesystem::path dictPath{DATA_DIR};
    inline static std::filesystem::path langTypePath{DATA_DIR "langType.txt"};
    inline static std::array<std::string, 2> langsType{"en", "jp"};
    inline static ActualLang currLang;
    inline static std::string userLang;

    static constexpr std::string_view dictFormat{".txt"};
    inline static std::unordered_map<std::string, std::string> dict;
    inline static std::array<std::string_view, mainMenuSize> mainMenu;
    inline static std::array<std::string_view, userMenuSize> userMenu;
    inline static std::array<std::string_view, adminMenuSize> adminMenu;

    inline static std::array<std::string, static_cast<size_t>(LoginMsg::Size)> loginMsgs;

    template <size_t S> static void fullfillMenu(std::array<std::string_view, S>& arr, const std::string& msg)
    {
        for (size_t i{}; i < S; ++i)
        {
            arr[i] = dict[msg + std::to_string(i + 1)];
        }
    }
};