#pragma once
#include "Colors.h"
#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <string>

struct ProductData
{
    std::string name;
    double price{};
    int qnt{};
};


namespace Utils
{
static constexpr size_t numofLangs{2};

inline void printMsgNLine(const std::string_view msg)
{
    std::cout << msg << '\n';
}

inline void printMsg(const std::string_view msg)
{
    std::cout << msg;
}

inline void printMsgSpace(std::string_view msg)
{
    std::print("{} ", msg);
}

inline void printWrongMsgNLine(const std::string_view msg)
{
    std::cout << COLORS::RED << msg << COLORS::RESET << '\n';
}

[[nodiscard]] inline std::string getInput(const std::string& inputMsg)
{
    std::string input;
    printMsgSpace(inputMsg);
    getline(std::cin, input);
    return input;
}

inline void printTabOptionNLine(const std::string_view msg,
                                const size_t numOption,
                                const std::string_view color)
{
    std::cout << '\t' << numOption + 1 << ". " << color << msg << COLORS::RESET
        << '\n';
}

inline void printWarningMsgNLine(const std::string_view msg)
{
    std::cout << COLORS::YELLOW << msg << COLORS::RESET << '\n';
}

inline void printSuccessMsg(const std::string_view msg)
{
    std::cout << COLORS::GREEN << msg << COLORS::RESET << '\n';
}

inline void lowerString(std::string& str)
{
    std::ranges::transform(str, str.begin(),
                           [](const char c)
                           {
                               return tolower(c);
                           });
}

[[nodiscard]] inline bool isInt(const std::string& str)
{
    return !str.empty() && std::ranges::all_of(str, [](const char c)
    {
        return isdigit(c);
    });
}

inline void printSeparator()
{
    std::cout << std::string(10, '-') << '\n';
}
}; // namespace Utils
