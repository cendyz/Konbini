#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include "Utils.h"
#include <cstdint>
#include <vector>

class KonbiniUI {
    enum class menuSizes : uint8_t {
        MainMenu = 9
    };

public:
    static void printUserCanChangeLNG();

    static void printChooseLangMsg();

    static void printWrongLngInput();

    static void printLngMenu();

    [[nodiscard]] static size_t getMainMenuSize();

    static void printMenu(const std::vector<std::string_view> &arr);

    static void printCanBackToMenu(std::string_view msg);

    static void printWhatUserWantToDo(std::string_view msg);

    static void printWrongExecuteCommand(std::string_view msg);

    static void printStoreIsEmpty(std::string_view msg);

    static void printStoreProducts(std::unordered_map<std::string, ProductData> &products, std::string_view currency,
                                   std::string_view qnt);

    static void printGoodbye(std::string_view msg);

    static void printAccountCreated(std::string_view msg);

    static void printPassword(std::string_view msg, std::string_view password);

    static void printCartIsEmpty(std::string_view msg);

private:
    static constexpr std::string_view possibilityToChoseLng{
        "You can choose the Konbini language, control is done using numbers."
    };
    static constexpr std::string_view langMsg{"Which language do you prefer?"};
    static constexpr std::array<std::string_view, 2> lngMenu{"Japanese", "English"};

    static constexpr std::string_view wrongInputMsg{"Unknown language."};
};
