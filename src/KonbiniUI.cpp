#include "KonbiniUI.h"
#include "Utils.h"


void KonbiniUI::printChooseLangMsg() {
    Utils::printMsgSpace(langMsg);
}

void KonbiniUI::userSelectingLanguage() {
    while (true) {
        if (lng->isUserLangOk()) {
            return;
        }
        printWrongLngInput();
    }
}


void KonbiniUI::printWrongLngInput() {
    Utils::printWrongMsgNLine(wrongInputMsg);
}
