#pragma once
#include <print>
#include <string_view>
#include <iostream>
#include <algorithm>
#include "Colors.h"



namespace Utils {

    inline void printMsgNLine(std::string_view msg) {
        std::println("{}", msg);
    }

    inline void printMsg(std::string_view msg) {
        std::print("{}", msg);
    }

    inline void printMsgSpace(std::string_view msg) {
        std::print("{} ", msg);
    }

    inline void printWrongMsgNLine(std::string_view msg) {
        std::println("{}{}{}", COLORS::RED, msg, COLORS::RESET);
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
};
