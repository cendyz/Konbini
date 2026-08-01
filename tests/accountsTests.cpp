#include "Accounts.h"
#include "gtest/gtest.h"
#include <array>

namespace
{
class IsCorrectAccountsFuncs : public ::testing::Test
{
  protected:
    Accounts accounts;

    void SetUp() override
    {
        accounts.clearAccs();

        accounts.addAccToVar({"billy", "bil@gm.com", "pass123", "user"});
        accounts.addAccToVar({"jerry", "jer@gm.com", "pass456", "admin"});
    }
};
} // namespace

TEST_F(IsCorrectAccountsFuncs, ReturnIsAccExists)
{
    EXPECT_TRUE(IsCorrectAccountsFuncs::accounts.isAccExists("bil@gm.com"));
    EXPECT_TRUE(IsCorrectAccountsFuncs::accounts.isAccExists("jer@gm.com"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isAccExists("we222@gm.com"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isAccExists("we222.com"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isAccExists("jer.com"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isAccExists(""));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isAccExists("   bil@gm.com"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isAccExists("   bil@gm.com   "));
}

TEST_F(IsCorrectAccountsFuncs, ReturnIsNameMatchingEmail)
{
    EXPECT_TRUE(IsCorrectAccountsFuncs::accounts.isCorrectNameEmail("bil@gm.com", "billy"));
    EXPECT_TRUE(IsCorrectAccountsFuncs::accounts.isCorrectNameEmail("jer@gm.com", "jerry"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isCorrectNameEmail("bil@gm.com", "billy7"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isCorrectNameEmail("bil@gm.com", "wewewq222"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isCorrectNameEmail("bil@gm.com", ""));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isCorrectNameEmail("bil@gm.com", "  billy"));
}

TEST_F(IsCorrectAccountsFuncs, IsEmailMatchingPassword)
{
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isEmailMatchingPassword("bil@gm.com", "wleww2"));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isEmailMatchingPassword("bil@gm.com", " pass123  "));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isEmailMatchingPassword("bil@gm.com", ""));
    EXPECT_FALSE(IsCorrectAccountsFuncs::accounts.isEmailMatchingPassword("bil@gm.com", "pass1234 "));
    EXPECT_TRUE(IsCorrectAccountsFuncs::accounts.isEmailMatchingPassword("bil@gm.com", "pass123"));
    EXPECT_TRUE(IsCorrectAccountsFuncs::accounts.isEmailMatchingPassword("jer@gm.com", "pass456"));
}
