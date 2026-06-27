#include <Konbini.h>
#include "LanguageManager.h"
#include "Utils.h"
#include <iostream>

Konbini::Konbini() {
    lng = std::make_unique<LanguageManager>();
    ui = std::make_unique<KonbiniUI>();
    items = std::make_unique<Products>();
}

void Konbini::run() {
    setSystemLang(userSelectingLanguage());
    while (true) {
        KonbiniUI::printMenu(lng->getMainMenu());
        KonbiniUI::printWhatUserWantToDo(lng->getText("OPT_SELECT"));
        if (std::string input = Utils::getInput(); isUserCommandOk(input)) {
            if (!executeMainMenuTaks(stoi(input))) {
                return;
            }
        } else {
            KonbiniUI::printWrongExecuteCommand(lng->getText("WRN_M_COMMAND"));
        }
    }
}

std::string Konbini::userSelectingLanguage() {
    KonbiniUI::printUserCanChangeLNG();
    while (true) {
        KonbiniUI::printLngMenu();
        KonbiniUI::printChooseLangMsg();
        if (std::string val = Utils::getInput(); checkUserLang(val)) {
            if (auto lang{LanguageManager::isCorrectUserLang(stoi(val))};
                lang.has_value()) {
                return lang.value();
            }
        }
        KonbiniUI::printWrongLngInput();
    }
}

bool Konbini::checkUserLang(const std::string &input) {
    return !input.empty() && Utils::isInputANumber(input);
}

void Konbini::setSystemLang(const std::string &lang) const {
    lng->loadDict(lang);
    lng->fullfillMainMenu();
}

bool Konbini::executeMainMenuTaks(int userOption) {
    switch (static_cast<MainMenuOPTS>(userOption)) {
        case MainMenuOPTS::BrowseTheStore:
            browseTheStore();
        case MainMenuOPTS::CheckCart:
            break;
        case MainMenuOPTS::FinalizePurchase:
            break;
        case MainMenuOPTS::Login:
            break;
        case MainMenuOPTS::Register:
            break;
        case MainMenuOPTS::BecomAEmployee:
            break;
        case MainMenuOPTS::RemindPassword:
            break;
        case MainMenuOPTS::Exit:
            KonbiniUI::printGoodbye(lng->getText("BYE"));
            return false;
        default:
            KonbiniUI::printWrongExecuteCommand(lng->getText("WRN_M_COMMAND"));
    }
    return true;
}

bool Konbini::isUserCommandOk(const std::string &input) {
    return !input.empty() && std::ranges::all_of(input, [](const char c) {
        return isdigit(c);
    });
}

void Konbini::browseTheStore() {
    if (items->isStoreEmpty()) {
        KonbiniUI::printStoreIsEmpty(lng->getText("STORE_EMPT"));
    }
}
