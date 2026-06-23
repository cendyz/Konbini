#include <LanguageManager.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "Utils.h"

LanguageManager::LanguageManager() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

bool LanguageManager::getUserLang(int val) {
    switch (static_cast<lang>(val)) {
        case lang::JP:
            loadDict("jp");
            break;
        case lang::EN:
            loadDict("en");
            break;
        default:
            return false;
    }
    return true;
}

bool LanguageManager::checkUserLang(const std::string &input) {
    return !input.empty() && Utils::isInputANumber(input);
}

void LanguageManager::loadDict(const std::string &lang) {
    std::filesystem::path path{dictPath.data() + lang + dictFormat.data()};
    std::ifstream dictionary{path};
    std::string line;
    std::string key;
    std::string text;
    std::istringstream ss;

    while (getline(dictionary, line)) {
        getline(ss, key, ';');
        getline(ss, text, ';');

        dict.try_emplace(key, text);
    }
}

std::string_view LanguageManager::getText(const std::string &text) {
    return dict[text];
}
