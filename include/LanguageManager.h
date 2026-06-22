#pragma once
#include <string>
#include <regex>

class LanguageManager {
public:
    enum class lang {
        JP = 1,
        EN = 2
    };

    LanguageManager();

    [[nodiscard]] static std::string getUserLang();

    [[nodiscard]] static bool checkUserLang(const std::string &input);

private:
    inline static const std::regex lngRegex{"^(japanese|english)$", std::regex::icase};
};
