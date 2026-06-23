#pragma once
#include <string>
#include <map>
#include <unordered_map>

class LanguageManager {
public:
    enum class lang {
        JP = 1,
        EN = 2
    };

    LanguageManager();

    [[nodiscard]] bool getUserLang(int val);

    [[nodiscard]] static bool checkUserLang(const std::string &input);

    void loadDict(const std::string & lang);

    [[nodiscard]] std::string_view getText(const std::string& text);

private:
    static constexpr std::string_view dictPath{"/data"};
    static constexpr std::string_view dictFormat{".txt"};
    std::unordered_map<std::string, std::string> dict;
};
