#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class KonbiniUI {
    enum class menuSizes : uint8_t {
        MainMenu = 8
    };
public:
    static void printUserCanChangeLNG();

    static void printChooseLangMsg();

    static void printWrongLngInput();

    static void printLngMenu();

    static void printMenu(const std::vector<std::string_view> &arr);

    static void printWhatUserWantToDo(std::string_view msg);

    static void printWrongExecuteCommand(std::string_view msg);

    static void printStoreIsEmpty(std::string_view msg);

    static void printStoreProducts(std::unordered_map<std::string,
        std::array<std::string, 3> > &products, std::string_view currency, std::string_view qnt);

    static void printGoodbye(std::string_view msg);

    [[nodiscard]] static size_t getMainMenuSize();

private:
    static constexpr std::string_view possibilityToChoseLng{
        "You can choose the Konbini language, control is done using numbers."
    };
    static constexpr std::string_view langMsg{"Which language do you prefer?"};
    static constexpr std::array<std::string_view, 2> lngMenu{"Japanese", "English"};

    static constexpr std::string_view wrongInputMsg{"Unknown language."};
};
