#include "KonbiniUI.h"
#include "Colors.h"
#include "LanguageManager.h"
#include "Utils.h"
#include "format"
#include "ranges"

void KonbiniUI::printUserCanChangeLNG()
{
    Utils::printMsgNLine(possibilityToChoseLng);
}

std::string KonbiniUI::getLangMsg()
{
    return langMsg;
}

void KonbiniUI::printWrongLngInput()
{
    Utils::printWrongMsgNLine(wrongInputMsg);
}

void KonbiniUI::printLngMenu()
{
    for (size_t i{}; i < lngMenu.size(); ++i)
    {
        Utils::printTabOptionNLine(lngMenu[i], i, COLORS::PURPLE);
    }
}


void KonbiniUI::printStoreProducts(
    std::unordered_map<std::string, ProductData>&& products,
    const std::string_view currency, const std::string_view qnt)
{
    for (const auto& [name, price, quantity] : products | std::views::values)
    {
        std::cout << COLORS::BLU << name << COLORS::RESET << " | " << price
            << currency << " | " << qnt << quantity << '\n';
    }
}

void KonbiniUI::printCartItems(
    const std::unordered_map<std::string, ProductData>& cartItems,
    const std::string_view currency)
{
    for (const auto& [name, price, qnt] : cartItems | std::views::values)
    {
        std::cout << COLORS::BLU << name << COLORS::RESET << " | " << qnt << " | "
            << price << currency << '\n';
    }
}

void KonbiniUI::printCartSummary(const std::unordered_map<std::string, ProductData>& cartItems,
                                 const std::string_view currency)
{
    double summary{};
    for (const auto& prd : cartItems | std::views::values)
    {
        summary += prd.price;
    }
    Utils::printSeparator();
    const std::string textSum{LanguageManager::getText("CRT_SUM")};
    std::string label{textSum};

    std::cout << std::format("{:>17}", label) << " " <<
        std::format("{:.2f}", summary) << currency << '\n';
}

void KonbiniUI::printCartIsEmpty(const std::string_view msg)
{
    Utils::printWarningMsgNLine(msg);
}


void KonbiniUI::printPassword(const std::string_view msg,
                              const std::string_view password)
{
    std::cout << COLORS::YELLOW << msg << COLORS::RESET << " " << password
        << '\n';
}

