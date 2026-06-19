#pragma once
#include <LanguageManager.h>
#include <memory>
#include <string_view>

class KonbiniUI {
public:
    KonbiniUI() {
        lng = std::make_unique<LanguageManager>();
        printChooseLangMsg();
        userSelectingLanguage();
    }

private:
    std::unique_ptr<LanguageManager> lng;


    static void printChooseLangMsg();

    static constexpr std::string_view langMsg{"Which language you prefer? (jp | en):"};

    void userSelectingLanguage();

    static void printWrongLngInput();

    static constexpr std::string_view wrongInputMsg{"Unknown language."};
};
