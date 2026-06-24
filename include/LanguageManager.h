#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

class LanguageManager {
public:
    LanguageManager() = default;

    [[nodiscard]] static std::optional<std::string> isCorrectUserLang(int val);

    void loadDict(const std::string &lang);

    [[nodiscard]] std::string_view getText(const std::string &text);

    void fullfillMainMenu();

    [[nodiscard]] std::vector<std::string_view> getMainMenu();

private:
    enum class lang {
        JP = 1,
        EN = 2
    };

    static constexpr std::string_view dictPath{"data/"};
    static constexpr std::string_view dictFormat{".txt"};
    std::unordered_map<std::string, std::string> dict;
    std::vector<std::string_view> mainMenu;
};
