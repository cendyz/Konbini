#include <LanguageManager.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "Utils.h"

std::optional<std::string> LanguageManager::isCorrectUserLang(int val) {
    switch (static_cast<lang>(val)) {
        case lang::JP:
            userLang = "JP";
            return "jp";
        case lang::EN:
            userLang = "EN";
            return "en";
    }
    return std::nullopt;
}

std::string LanguageManager::getUserLang() {
    return userLang;
}

void LanguageManager::loadDict(const std::string &lang) {
    std::filesystem::path path{dictPath.data() + lang + dictFormat.data()};
    std::ifstream dictionary{path};
    std::string line;
    std::string key;
    std::string text;

    while (getline(dictionary, line)) {
        std::istringstream ss(line);
        getline(ss, key, ';');
        getline(ss, text, ';');

        dict.try_emplace(key, text);
    }
}

std::string_view LanguageManager::getText(const std::string &text) {
    return dict[text];
}

void LanguageManager::fullfillMainMenu() {
    for (size_t i{}; i < 8; ++i) {
        mainMenu.emplace_back(dict["M_OPT_" + std::to_string(i + 1)]);
    }
}

std::vector<std::string_view> LanguageManager::getMainMenu() {
    return mainMenu;
}
