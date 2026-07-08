#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <filesystem>

class LanguageManager
{
public:
    LanguageManager() = default;

    void static loadLangTypeFile();

    [[nodiscard]] static bool isLangTypeAlreadySet();

    static void saveUserLangToFile();

    [[nodiscard]] static std::optional<std::string> isCorrectUserLang(int val);

    static void loadDict(const std::string& lang);

    [[nodiscard]] static std::string getUserLang();

    [[nodiscard]] static std::string_view getText(const std::string& text);

    static void fullfillMainMenu(size_t mainMenuSize);

    [[nodiscard]] static std::vector<std::string_view> getMainMenu();

    void static changeLang();

    void static clearDict();

private:
    enum class lang
    {
        JP = 1,
        EN = 2
    };

    inline static std::filesystem::path dictPath{DATA_DIR};
    inline static std::filesystem::path langTypePath{DATA_DIR "langType.txt"};
    inline static std::string userLang;
    static constexpr std::string_view dictFormat{".txt"};
    inline static std::unordered_map<std::string, std::string> dict;
    inline static std::vector<std::string_view> mainMenu;
};
