#pragma once
#include <LanguageManager.h>
#include <array>
#include <string_view>

class KonbiniUI {
public:
    KonbiniUI() = default;

    static void printUserCanChangeLNG();

    static void printChooseLangMsg();

    static void printWrongLngInput();

    static void printLngMenu();

private:
    static constexpr std::string_view possibilityToChoseLng{
        "You can choose the Konbini language, control is done using numbers."
    };
    static constexpr std::string_view langMsg{"Which language do you prefer?"};
    static constexpr std::array<std::string_view, 2> lngMenu{"Japanese", "English"};

    static constexpr std::string_view wrongInputMsg{"Unknown language."};
};
