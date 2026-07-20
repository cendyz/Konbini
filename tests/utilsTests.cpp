#include "gtest/gtest.h"
#include "../include/Utils.h"


TEST(isNumber, RecognizesVariousFormatsCorrectly) {
    EXPECT_TRUE(Utils::isInt("93"));
    EXPECT_TRUE(Utils::isInt("3"));
    EXPECT_TRUE(Utils::isInt(""));
    EXPECT_FALSE(Utils::isInt(" 2"));
    EXPECT_FALSE(Utils::isInt("78 "));
    EXPECT_FALSE(Utils::isInt("ww"));
    EXPECT_FALSE(Utils::isInt("ske$2a"));
}