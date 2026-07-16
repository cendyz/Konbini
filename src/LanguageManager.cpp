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

void LanguageManager::loadMenus()
{
    fullfillMenu(mainMenu, "M_OPT_");
    fullfillMenu(userMenu, "U_MENU_");
    fullfillMenu(adminMenu, "A_MENU_");
}

std::string_view LanguageManager::getText(const std::string& text)
{
    return dict[text];
}


std::array<std::string_view, LanguageManager::mainMenuSize> LanguageManager::getMainMenu()
{
    return mainMenu;
}

std::array<std::string_view, LanguageManager::userMenuSize> LanguageManager::getUserMenu()
{
    return userMenu;
}

std::array<std::string_view, LanguageManager::adminMenuSize> LanguageManager::getAdminMenu()
{
    return adminMenu;
}

size_t LanguageManager::getMainMenuSize()
{
    return mainMenuSize;
}

size_t LanguageManager::getUserMenuSize()
{
    return userMenuSize;
}

size_t LanguageManager::getAdminMenuSize()
{
    return adminMenuSize;
}

void LanguageManager::changeLang()
{
    currLang = currLang == ActualLang::EN ? ActualLang::JP : ActualLang::EN;
    userLang = langsType[static_cast<size_t>(currLang)];
}

void LanguageManager::clearDict()
{
    dict.clear();
}
