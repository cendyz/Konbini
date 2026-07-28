#include "../include/Utils.h"
#include "array"
#include "gtest/gtest.h"

TEST(isNumber, RecognizesVariousFormatsCorrectly)
{
    EXPECT_TRUE(Utils::isInt("93"));
    EXPECT_TRUE(Utils::isInt("3"));
    EXPECT_FALSE(Utils::isInt(""));
    EXPECT_FALSE(Utils::isInt(" 2"));
    EXPECT_FALSE(Utils::isInt("78 "));
    EXPECT_FALSE(Utils::isInt("782222222222222222222222222222"));
    EXPECT_FALSE(Utils::isInt("ww"));
    EXPECT_FALSE(Utils::isInt("ske$2a"));
}

TEST(isLoweringString, ChangeBigCharsToLow)
{
    std::array<std::string, 4> strs{"AWER", "aWe4R", "", " ra R9 4aAb"};

    for (size_t i{}; i < 4; ++i)
    {
        const std::array<std::string, 4> exps{"awer", "awe4r", "", " ra r9 4aab"};
        Utils::lowerString(strs[i]);
        EXPECT_EQ(strs[i], exps[i]);
    }
}

TEST(isUpperingFirstLetter, firstLetterGoUp)
{
    std::string a{"iphone"};
    std::string a1{"iphone "};
    std::string a2{"iphone 2"};
    std::string a3{"iphone pro"};

    EXPECT_EQ(Utils::lowerFirstLetter(a), "Iphone");
    EXPECT_EQ(Utils::lowerFirstLetter(a1), "Iphone ");
    EXPECT_EQ(Utils::lowerFirstLetter(a2), "Iphone 2");
    EXPECT_EQ(Utils::lowerFirstLetter(a3), "Iphone Pro");
}