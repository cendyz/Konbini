#pragma once
#include "Colors.h"

struct ProductData
{
    std::string name{};
    double price{};
    int qnt{};
};

namespace Utils
{
constexpr size_t numofLangs{2};
const std::filesystem::path tempPath{DATA_DIR"temp.txt"};

void printMsgNLine(std::string_view msg);

void printMsg(std::string_view msg);

void printColorfullMsg(std::string_view color, std::string_view msg);

void printColonWSpace();

void printMsgSpace(std::string_view msg);

void printWrongMsgNLine(std::string_view msg);

[[nodiscard]] std::string getInput(const std::string& inputMsg);

void printTabOptionNLine(std::string_view msg,
                                size_t numOption,
                                std::string_view color);

void printWarningMsgNLine(std::string_view msg);

void printSuccessMsg(std::string_view msg);

void lowerString(std::string& str);

[[nodiscard]] bool isInt(const std::string& str);

void printSeparator();

}