#include "gtest/gtest.h"
#include "../include/Utils.h"


TEST(isNumber, RecognizesVariousFormatsCorrectly)
{
    EXPECT_TRUE(Utils::isInt("93"));
    EXPECT_TRUE(Utils::isInt("3"));
    EXPECT_FALSE(Utils::isInt(""));
    EXPECT_FALSE(Utils::isInt(" 2"));
    EXPECT_FALSE(Utils::isInt("78 "));
    EXPECT_FALSE(Utils::isInt("ww"));
    EXPECT_FALSE(Utils::isInt("ske$2a"));
}

TEST(isLowering, ChangeBigCharsToLow)
{
    std::array<std::string, 4> strs{"AWER", "aWe4R", "", " ra R9 4aAb"};
    const std::array<std::string, 4> exps{"awer", "awe4r", "", " ra r9 4aab"};

    for (size_t i{}; i < 4; ++i)
    {
        Utils::lowerString(strs[i]);
        EXPECT_EQ(strs[i], exps[i]);
    }

}