#include <LanguageManager.h>
#include <ios>
#include <iostream>

LanguageManager::LanguageManager() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}



std::string LanguageManager::getUserLang() {
    std::string input;
    std::cin >> input;
    return input;
}

bool LanguageManager::isUserLangOk() {
    return std::regex_match(getUserLang(), langRegex);
}
