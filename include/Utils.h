#pragma once
#include <filesystem>
#include <regex>
#include <string>

enum class ActualLang : std::uint8_t
{
    EN = 0,
    JP = 1,
};

struct ProductData
{
    std::string name;
    double price{};
    int qnt{};
};

namespace Utils
{
constexpr size_t numofLangs{2};
const std::filesystem::path tempPath{DATA_DIR "temp.txt"};
static const std::regex doubleRegex{R"(^[+-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?$)"};

void printMsgNLine(std::string_view msg);

void printMsg(std::string_view msg);

void printColorfullMsg(std::string_view color, std::string_view msg);

void printColorfullMsgNLine(std::string_view color, std::string_view msg);

void printColonWSpace();

void printMsgSpace(std::string_view msg);

void printWrongMsgNLine(std::string_view msg);

[[nodiscard]] std::string getFullLineInput(std::string_view inputMsg);

void printTabOptionNLine(std::string_view msg, size_t numOption, std::string_view color);

void printWarningMsgNLine(std::string_view msg);

void printSuccessMsg(std::string_view msg);

void lowerString(std::string& str);

std::string upperFirstLetter(const std::string& str);

[[nodiscard]] bool isInt(const std::string& str);

[[nodiscard]] bool isDouble(const std::string& str);

void printSeparator();

} // namespace Utils