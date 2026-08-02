#include "LanguageManager.h"
#include "gtest/gtest.h"

namespace
{
class LanguageManagerTest : public testing::Test
{
  protected:
    LanguageManager lng;

    inline static const std::array<std::string, 2> langs{"jp", "en"};
    static constexpr size_t numOfLines{95};
    inline static const std::array<std::string, numOfLines> dictKeys{
        "MENU_WELCOME", "REG_CUP",    "M_BACK_OPT",     "M_OPT_1",     "M_OPT_2",    "M_OPT_3",        "M_OPT_4",
        "M_OPT_5",      "M_OPT_6",    "M_OPT_7",        "M_OPT_8",     "M_OPT_9",    "M_OPT_10",       "M_OPT_11",
        "M_OPT_12",     "OPT_SELECT", "WRN_M_COMMAND",  "STORE_EMPT",  "BYE",        "PRD_QNT",        "PRD_N_QNT",
        "SUCC_CHNQ",    "WRN_QNT",    "PRD_ADD_CART",   "MENU_BACK",   "NAME",       "NAME_ERR",       "LOGIN",
        "WRN_LOGIN",    "PSWD",       "PSWD_ERR",       "EMAIL",       "EMAIL_ERR",  "EMAIL_EXST",     "EMAIL_CHANGED",
        "ACC_CREATED",  "SUCC_LOG",   "WRN_NAME_EMAIL", "YOUR_PASS",   "NEW_PASS",   "NEW_PASS_CHNGD", "EMP_CART",
        "WRN_PRD",      "PRD_NAME",   "NOT_IN_C",       "ITM_REMV",    "CRT_SUM",    "DSC_CRT_SUM",    "LNG_CHN",
        "THNK_SHP",     "LOG_OUT",    "ACC_DEL",        "U_MENU_1",    "U_MENU_2",   "U_MENU_3",       "U_MENU_4",
        "U_MENU_5",     "U_MENU_6",   "U_MENU_7",       "U_MENU_8",    "U_MENU_9",   "U_MENU_10",      "U_MENU_11",
        "U_MENU_12",    "U_MENU_13",  "S_ACC_0",        "S_ACC_1",     "S_ACC_2",    "S_ACC_3",        "N_EMAIL",
        "A_MENU_1",     "A_MENU_2",   "A_MENU_3",       "A_MENU_4",    "A_MENU_5",   "A_MENU_6",       "A_MENU_7",
        "A_MENU_8",     "A_MENU_9",   "A_MENU_10",      "A_MENU_11",   "A_MENU_12",  "A_MENU_13",      "A_MENU_14",
        "A_MENU_15",    "A_MENU_16",  "EN_PRD_NAME",    "JP_PRD_NAME", "PRD_AL_EXT", "NEW_PRD_PRICE",  "WRN_PRD_PRICE",
        "PRD_ADD_ST",   "PRD_REM_ST", "QNT_CHN",        "WRN_PRD_NAME"};
};
} // namespace

TEST_F(LanguageManagerTest, isDictLinesCorrect)
{

    for (size_t i{}; i < langs.size(); ++i)
    {
        lng.loadDict(langs[i]);
        EXPECT_EQ(lng.getDictSize(), numOfLines);
        lng.clearDict();
    }
}

TEST_F(LanguageManagerTest, isDictContainsAllKeys)
{
    for (size_t i{}; i < langs.size(); ++i)
    {
        lng.loadDict(langs[i]);
        for (const std::string& key : dictKeys)
        {
            EXPECT_EQ(lng.isKeyExist(key), true);
        }
        lng.clearDict();
    }
}