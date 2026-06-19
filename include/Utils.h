#pragma once
#include <print>
#include <string_view>
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
};
