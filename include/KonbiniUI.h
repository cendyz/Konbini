#pragma once
import std;
#include "../src/Utils.cpp"


class KonbiniUI
{

public:
    static void printUserCanChangeLNG();

    static void printWrongLngInput();

    static void printLngMenu();

    [[nodiscard]] static std::string getLangMsg();

    template <size_t S>
    static void printMenu(const std::array<std::string_view, S>& arr)
    {
        for (size_t i{}; i < S; ++i)
        {
            Utils::printTabOptionNLine(arr[i], i, COLORS::BLU);
        }
    }

    static void
    printStoreProducts(std::unordered_map<std::string, ProductData>&& products,
                       std::string_view currency, std::string_view qnt);

    static void printPassword(std::string_view msg, std::string_view password);

    static void
    printCartItems(const std::unordered_map<std::string, ProductData>& cartItems,
                   std::string_view currency);

    static void printCartSummary(const std::unordered_map<std::string, ProductData>& cartItems,
                                 std::string_view currency);

    static void printCartIsEmpty(std::string_view msg);

    template <size_t S>
    static void printLoggedMenu(const std::array<std::string_view, S>& arr)
    {
        for (size_t i{}; i < S; ++i)
        {
            std::cout << i + 1 << ". " << arr[i] << '\n';
        }
    }

private:
    static constexpr std::string_view possibilityToChoseLng{
        "You can choose the Konbini language, control is done using numbers."};
    inline static const std::string langMsg{"Which language do you prefer?"};
    static constexpr std::array<std::string_view, 2> lngMenu{"Japanese",
                                                             "English"};

    static constexpr std::string_view wrongInputMsg{"Unknown language."};
};