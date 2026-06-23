#include <Konbini.h>
#include "Utils.h"

Konbini::Konbini() {
    lng = std::make_unique<LanguageManager>();
    ui = std::make_unique<KonbiniUI>();
}

void Konbini::run() {
    userSelectingLanguage();
}

void Konbini::userSelectingLanguage() const {
    KonbiniUI::printUserCanChangeLNG();
    while (true) {
        KonbiniUI::printLngMenu();
        KonbiniUI::printChooseLangMsg();
        if (std::string val{Utils::getInput()}; LanguageManager::checkUserLang(val) &&
                                                lng->getUserLang(stoi(val))) {
            return;
        }
        KonbiniUI::printWrongLngInput();
    }
}
