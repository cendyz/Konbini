#pragma once
#include "Utils.h"
#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class KonbiniUI
{
    enum class menuSizes : uint8_t { MainMenu = 10 };

public:
    static void printUserCanChangeLNG();

    static void printWrongLngInput();

    static void printLngMenu();

    [[nodiscard]] static std::string getLangMsg();

    [[nodiscard]] static size_t getMainMenuSize();

    static void printMenu(const std::vector<std::string_view>& arr);

    static void
    printStoreProducts(std::unordered_map<std::string, ProductData>& products,
                       std::string_view currency, std::string_view qnt);

    static void printPassword(std::string_view msg, std::string_view password);

    static void
    printCartItems(const std::unordered_map<std::string, ProductData>& cartItems,
                   std::string_view currency);

    static void printCartSummary(const std::unordered_map<std::string, ProductData>& cartItems,
                                 std::string_view currency);

private:
    static constexpr std::string_view possibilityToChoseLng{
        "You can choose the Konbini language, control is done using numbers."};
    inline static const std::string langMsg{"Which language do you prefer?"};
    static constexpr std::array<std::string_view, 2> lngMenu{"Japanese",
                                                             "English"};

    static constexpr std::string_view wrongInputMsg{"Unknown language."};
};
