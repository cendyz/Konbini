#include <Konbini.h>
#include "LanguageManager.h"
#include "Utils.h"
#include <iostream>

Konbini::Konbini() {
    lng = std::make_unique<LanguageManager>();
    ui = std::make_unique<KonbiniUI>();
}

void Konbini::run() {
    setSystemLang(userSelectingLanguage());
    while (true) {
        ui->printMenu(lng->getMainMenu());
        std::cout << "aaa?: ";
        std::string v = Utils::getInput();

        if (v == "a") {
            return;
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
