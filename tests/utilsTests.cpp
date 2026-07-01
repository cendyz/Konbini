#include "gtest/gtest.h"
#include "Utils.h"


TEST(isNumber, RecognizesVariousFormatsCorrectly) {
    EXPECT_TRUE(Utils::isInputANumber("93"));
    EXPECT_TRUE(Utils::isInputANumber("3"));
    EXPECT_TRUE(Utils::isInputANumber(""));
    EXPECT_FALSE(Utils::isInputANumber(" 2"));
    EXPECT_FALSE(Utils::isInputANumber("78 "));
    EXPECT_FALSE(Utils::isInputANumber("ww"));
    EXPECT_FALSE(Utils::isInputANumber("ske$2a"));
}