#pragma once
#include <string>
#include <regex>

class LanguageManager {
public:
    LanguageManager();

    [[nodiscard]] static bool isUserLangOk();

private:
    [[nodiscard]] static std::string getUserLang();

    inline static const std::regex langRegex{"^(jp|en)$", std::regex::icase};
};
