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
    switch (static_cast<Langs>(val))
    {
    case Langs::JP:
        currLang = ActualLang::JP;
        break;
    case Langs::EN:
        currLang = ActualLang::EN;
        break;
    default:
        return std::nullopt;
    }
    userLang = langsType[static_cast<size_t>(currLang)];
    return langsType[static_cast<size_t>(currLang)];
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
    currLang = (currLang == ActualLang::EN) ? ActualLang::JP : ActualLang::EN;
    userLang = langsType[static_cast<size_t>(currLang)];
}

void LanguageManager::clearDict()
{
    dict.clear();
    mainMenu.clear();
}
