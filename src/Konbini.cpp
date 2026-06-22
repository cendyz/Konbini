#include <Konbini.h>
#include <print>

Konbini::Konbini() {
    lng = std::make_unique<LanguageManager>();
    ui = std::make_unique<KonbiniUI>();

    if (userSelectingLanguage() == "japanese") {
        std::println("jp");
    } else {
        std::println("en");
    }
}

std::string Konbini::userSelectingLanguage() {
    KonbiniUI::printUserCanChangeLNG();
    while (true) {
        KonbiniUI::printLngMenu();
        KonbiniUI::printChooseLangMsg();
        if (std::string val = LanguageManager::getUserLang();
            LanguageManager::checkUserLang(val)) {
            return val;
        }
        KonbiniUI::printWrongLngInput();
    }
}
