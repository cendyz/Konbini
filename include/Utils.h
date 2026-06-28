#pragma once
#include <print>
#include <iostream>
#include <string>
#include <algorithm>
#include "Colors.h"


namespace Utils {
    inline void printMsgNLine(const std::string_view msg) {
        std::cout << msg << '\n';
    }

    inline void printMsg(const std::string_view msg) {
        std::cout << msg;
    }

    inline void printMsgSpace(std::string_view msg) {
        std::print("{} ", msg);
    }

    inline void printWrongMsgNLine(const std::string_view msg) {
        std::cout << COLORS::RED << msg << COLORS::RESET << '\n';
    }

    [[nodiscard]] inline std::string getInput() {
        std::string input;
        getline(std::cin, input);
        return input;
    }

    [[nodiscard]] inline bool isInputANumber(const std::string &input) {
        return std::ranges::all_of(input, [](const char c) {
            return isdigit(c);
        });
    }

    inline void printTabOptionNLine(const std::string_view msg, const size_t numOption, const std::string_view color) {
        std::cout << '\t' << numOption + 1 << ". " <<
                color << msg << COLORS::RESET << '\n';
    }

    inline void printWarningMsg(const std::string_view msg) {
        std::cout << COLORS::YELLOW << msg << COLORS::RESET << '\n';
    }

    inline void printSuccessMsg(const std::string_view msg) {
        std::cout << COLORS::GREEN << msg << COLORS::RESET << '\n';
    }
};


