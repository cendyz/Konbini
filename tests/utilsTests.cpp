#include "../include/Utils.h"
#include "array"
#include "gtest/gtest.h"

TEST(IsDouble, RecognizesVariousFormatsCorrect)
{
    EXPECT_TRUE(Utils::isDouble("22.1"));
    EXPECT_TRUE(Utils::isDouble(".9"));
    EXPECT_TRUE(Utils::isDouble("3."));
}

TEST(IsDouble, RecognizesVariousFormatsIncorrect)
{
    EXPECT_FALSE(Utils::isDouble("2223..1"));
    EXPECT_FALSE(Utils::isDouble(""));
    EXPECT_FALSE(Utils::isDouble(" 3."));
    EXPECT_FALSE(Utils::isDouble("3.#11a"));
    EXPECT_FALSE(Utils::isDouble("w3.a3"));
    EXPECT_FALSE(Utils::isDouble("22222222111112.3"));
}

TEST(isInt, RecognizesVariousFormatsCorrectly)
{
    EXPECT_TRUE(Utils::isInt("93"));
    EXPECT_TRUE(Utils::isInt("3"));
}

TEST(isInt, RecognizesVariousFormatsInCorrectly)
{
    EXPECT_FALSE(Utils::isInt(""));
    EXPECT_FALSE(Utils::isInt(" 2"));
    EXPECT_FALSE(Utils::isInt("78 "));
    EXPECT_FALSE(Utils::isInt("78222222222222222222222222222222"));
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
    const std::string a{"iphone"};
    const std::string a1{"iphone "};
    const std::string a2{"iphone 2"};
    const std::string a3{"iphone pro"};

    EXPECT_EQ(Utils::upperFirstLetter(a), "Iphone");
    EXPECT_EQ(Utils::upperFirstLetter(a1), "Iphone ");
    EXPECT_EQ(Utils::upperFirstLetter(a2), "Iphone 2");
    EXPECT_EQ(Utils::upperFirstLetter(a3), "Iphone Pro");
}