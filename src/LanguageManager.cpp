#include <LanguageManager.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "Utils.h"

bool LanguageManager::isLangTypeAlreadySet()
{
    return userLang.size() > 1;
}

void LanguageManager::loadLangTypeFile()
{
    std::ifstream file{langTypePath};
    std::string line;
    getline(file, line);
    userLang = line;
}

void LanguageManager::saveUserLangToFile()
{
    std::ofstream file{langTypePath};
    file << userLang << '\n';
}

std::optional<std::string> LanguageManager::isCorrectUserLang(int val)
{
    switch (static_cast<lang>(val))
    {
    case lang::JP:
        userLang = "jp";
        return "jp";
    case lang::EN:
        userLang = "en";
        return "en";
    }
    return std::nullopt;
}

std::string LanguageManager::getUserLang()
{
    return userLang;
}

void LanguageManager::loadDict(const std::string& lang)
{
    std::filesystem::path path{dictPath.string() + lang + dictFormat.data()};
    std::ifstream dictionary{path};
    std::string line;
    std::string key;
    std::string text;

    while (getline(dictionary, line))
    {
        std::istringstream ss(line);
        getline(ss, key, ';');
        getline(ss, text, ';');

        dict.try_emplace(key, text);
    }
}

std::string_view LanguageManager::getText(const std::string& text)
{
    return dict[text];
}

void LanguageManager::fullfillMainMenu(const size_t mainMenuSize)
{
    for (size_t i{}; i < mainMenuSize; ++i)
    {
        mainMenu.emplace_back(dict["M_OPT_" + std::to_string(i + 1)]);
    }
}

std::vector<std::string_view> LanguageManager::getMainMenu()
{
    return mainMenu;
}

void LanguageManager::changeLang()
{
    if (userLang == "jp")
    {
        userLang = "en";
    }
    else
    {
        userLang = "jp";
    }
}

void LanguageManager::clearDict()
{
    dict.clear();
    mainMenu.clear();
}
