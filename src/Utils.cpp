#include "Utils.h"
#include "Colors.h"
#include <iostream>
#include <print>

void Utils::printMsgNLine(const std::string_view msg)
{
    std::cout << msg << '\n';
}

void Utils::printMsg(const std::string_view msg)
{
    std::cout << msg;
}

void Utils::printColorfullMsg(const std::string_view color, const std::string_view msg)
{
    std::cout << color << msg << COLORS::RESET;
}

void Utils::printColorfullMsgNLine(const std::string_view color, const std::string_view msg)
{
    std::cout << color << msg << COLORS::RESET << '\n';
}

void Utils::printColonWSpace()
{
    std::cout << ": ";
}

void Utils::printMsgSpace(std::string_view msg)
{
    std::print("{} ", msg);
}

void Utils::printWrongMsgNLine(const std::string_view msg)
{
    std::cout << COLORS::RED << msg << COLORS::RESET << '\n';
}

std::string Utils::getFullLineInput(const std::string_view inputMsg)
{
    std::string input;
    printMsgSpace(inputMsg);
    getline(std::cin, input);
    return input;
}

void Utils::printTabOptionNLine(const std::string_view msg, const size_t numOption, const std::string_view color)
{
    std::cout << '\t' << numOption + 1 << ". " << color << msg << COLORS::RESET << '\n';
}

void Utils::printWarningMsgNLine(const std::string_view msg)
{
    std::cout << COLORS::YELLOW << msg << COLORS::RESET << '\n';
}

void Utils::printSuccessMsg(const std::string_view msg)
{
    std::cout << COLORS::GREEN << msg << COLORS::RESET << '\n';
}

void Utils::lowerString(std::string& str)
{
    std::ranges::transform(str, str.begin(),
                           [](const char c)
                           {
                               return std::tolower(c);
                           });
}

std::string Utils::upperFirstLetter(const std::string& str)
{
    std::string newStr{str};
    for (size_t i{}; i < str.size(); ++i)
    {
        if (str[i] == ' ' && str[i + 1] != ' ')
        {
            newStr[i + 1] = static_cast<char>(std::toupper(str[i + 1]));
        }
        else if (i == 0)
        {
            newStr[i] = static_cast<char>(std::toupper(str[i]));
        }
    }
    return newStr;
}

bool Utils::isInt(const std::string& str)
{
    return !str.empty() && str.size() < 11 &&
           std::ranges::all_of(
               str,
               [](const char c)
               {
                   return std::isdigit(c);
               });
}

void Utils::printSeparator()
{
    std::cout << std::string(15, '-') << '\n';
}

bool Utils::isDouble(const std::string& str)
{
    return str.size() < 7 && std::regex_match(str, doubleRegex);
}
