#pragma once
#include <array>
#include <string_view>
#include <vector>

class KonbiniUI {
public:
    static void printUserCanChangeLNG();

    static void printChooseLangMsg();

    static void printWrongLngInput();

    static void printLngMenu();

    static void printMenu(const std::vector<std::string_view> &arr) ;


private:
    static constexpr std::string_view possibilityToChoseLng{
        "You can choose the Konbini language, control is done using numbers."
    };
    static constexpr std::string_view langMsg{"Which language do you prefer?"};
    static constexpr std::array<std::string_view, 2> lngMenu{"Japanese", "English"};

    static constexpr std::string_view wrongInputMsg{"Unknown language."};

};
