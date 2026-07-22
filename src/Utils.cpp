#include "Utils.h"

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

std::string Utils::getInput(const std::string& inputMsg)
{
    std::string input;
    printMsgSpace(inputMsg);
    getline(std::cin, input);
    return input;
}

void Utils::printTabOptionNLine(const std::string_view msg,
                                const size_t numOption,
                                const std::string_view color)
{
    std::cout << '\t' << numOption + 1 << ". " << color << msg << COLORS::RESET
        << '\n';
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

bool Utils::isInt(const std::string& str)
{
    return !str.empty() && std::ranges::all_of(str, [](const char c)
    {
        return std::isdigit(c);
    });
}

void Utils::printSeparator()
{
    std::cout << std::string(10, '-') << '\n';
}
