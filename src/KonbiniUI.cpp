#include "KonbiniUI.h"
#include "Utils.h"
#include "Colors.h"
#include <print>

void KonbiniUI::printUserCanChangeLNG() {
    Utils::printMsgNLine(possibilityToChoseLng);
}

void KonbiniUI::printChooseLangMsg() {
    Utils::printMsgSpace(langMsg);
}

void KonbiniUI::printWrongLngInput() {
    Utils::printWrongMsgNLine(wrongInputMsg);
}

void KonbiniUI::printLngMenu() {
    for (size_t i{}; i < lngMenu.size(); ++i) {
        std::println("\t{}. {}{}{}", i + 1, COLORS::PURPLE, lngMenu[i], COLORS::RESET);
    }
}
