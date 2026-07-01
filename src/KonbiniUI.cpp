#include "KonbiniUI.h"
#include "Utils.h"
#include "Colors.h"
#include "ranges"
#include "format"

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
        Utils::printTabOptionNLine(lngMenu[i], i, COLORS::PURPLE);
    }
}

void KonbiniUI::printMenu(const std::vector<std::string_view> &arr) {
    for (size_t i{}; i < arr.size(); ++i) {
        Utils::printTabOptionNLine(arr[i], i, COLORS::BLU);
    }
}

void KonbiniUI::printWhatUserWantToDo(const std::string_view msg) {
    Utils::printMsgSpace(msg);
}

void KonbiniUI::printWrongExecuteCommand(const std::string_view msg) {
    Utils::printWrongMsgNLine(msg);
}

void KonbiniUI::printStoreIsEmpty(const std::string_view msg) {
    Utils::printWarningMsg(msg);
}

void KonbiniUI::printGoodbye(const std::string_view msg) {
    Utils::printSuccessMsg(msg);
}

void KonbiniUI::printStoreProducts(std::unordered_map<std::string,
                                       std::array<std::string, 3> > &products,
                                   const std::string_view currency, const std::string_view qnt) {
    std::string label;
    for (const auto &[name, price, quantity]:
         products | std::views::values) {
        label.reserve(name.size());
        label += COLORS::BLU;
        label += name;
        label += COLORS::RESET;
        std::cout << std::format("{:<10}", label) << " | " << price << currency
                << " | " << qnt << quantity << '\n';
    }
}

size_t KonbiniUI::getMainMenuSize() {
    return static_cast<size_t>(menuSizes::MainMenu);
}
