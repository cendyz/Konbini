#include "KonbiniUI.h"
#include "Colors.h"
#include "LanguageManager.h"
#include "Utils.h"
#include <ranges>

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

void KonbiniUI::printStoreProducts(std::unordered_map<std::string, ProductData>&& products,
                                   const std::string_view currency, const std::string_view qnt)
{

    for (const auto& [name, price, quantity] : products | std::views::values)
    {
        std::cout << COLORS::BLU << name << COLORS::RESET << " | " << price << currency << " | " << qnt << quantity
                  << '\n';
    }
}

void KonbiniUI::printCartItems(const std::unordered_map<std::string, ProductData>& cartItems,
                               const std::string_view currency)
{
    for (const auto& [name, price, qnt] : cartItems | std::views::values)
    {
        std::cout << COLORS::BLU << name << COLORS::RESET << " | " << qnt << " | " << price << currency << '\n';
    }
}

void KonbiniUI::printCartSummary(const std::array<double, 2>& summaries, const std::string& currency, const bool isUser)
{

    Utils::printSeparator();
    const std::string textSum{isUser ? LanguageManager::getText("DSC_CRT_SUM") : LanguageManager::getText("CRT_SUM")};
    std::string label{textSum};
    const size_t i{static_cast<size_t>(isUser ? 1 : 0)};
    std::cout << std::format("{:>17}", label) << " ";
    std::string priceBeforeDiscount{
        isUser ? "\033[9;93m" +
                     (currency == "円" ? std::format("{:.0f}", summaries[0]) : std::format("{:.2f}", summaries[0])) +
                     currency + "\033[0m "
               : ""};

    if (currency == "円")
    {
        std::cout << priceBeforeDiscount << summaries[i] << currency << '\n';
    }
    else
    {
        std::cout << priceBeforeDiscount << std::format("{:.2f}", summaries[i]) << currency << '\n';
    }
}

void KonbiniUI::printCartIsEmpty(const std::string_view msg)
{
    Utils::printWarningMsgNLine(msg);
}

void KonbiniUI::printPassword(const std::string_view msg, const std::string_view password)
{
    std::cout << COLORS::YELLOW << msg << COLORS::RESET << " " << password << '\n';
}