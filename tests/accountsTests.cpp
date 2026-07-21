#include "gtest/gtest.h"
#include "Accounts.h"


namespace
{
class IsCorrectAccountsFuncs : public testing::Test
{
protected:
    std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)> acc;
    
    void SetUp() override
    {
        acc[static_cast<size_t>(Accounts::AccInfo::Name)] = "jerry";
        acc[static_cast<size_t>(Accounts::AccInfo::Email)] = "jer@gm.com";
        Accounts::addAccToVar(acc);
        acc[static_cast<size_t>(Accounts::AccInfo::Name)] = "billy";
        acc[static_cast<size_t>(Accounts::AccInfo::Email)] = "bil@gm.com";
        Accounts::addAccToVar(acc);
    }

    void TearDown() override
    {
        Accounts::clearAccs();
    }

};
}


TEST_F(IsCorrectAccountsFuncs, ReturnIsAccExists)
{
    EXPECT_TRUE(Accounts::isAccExists("bil@gm.com"));
    EXPECT_TRUE(Accounts::isAccExists("jer@gm.com"));
    EXPECT_FALSE(Accounts::isAccExists("we222@gm.com"));
}

TEST_F(IsCorrectAccountsFuncs, ReturnIsNameMatchingEmail)
{
    EXPECT_TRUE(Accounts::isCorrectNameEmail("jer@gm.com", "jerry"));
    EXPECT_FALSE(Accounts::isCorrectNameEmail("bil@gm.com", "wrong_password"));
    EXPECT_FALSE(Accounts::isCorrectNameEmail("", ""));
    EXPECT_TRUE(Accounts::isCorrectNameEmail("bil@gm.com", "billy"));
    EXPECT_FALSE(Accounts::isCorrectNameEmail("", "invalid_password"));
    EXPECT_FALSE(Accounts::isCorrectNameEmail("this_is_not_email", "jerry"));
}