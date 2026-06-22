#pragma once
#include "KonbiniUI.h"
#include <memory>

class Konbini {
public:
    Konbini(const Konbini &obj) = delete;

    Konbini &operator=(Konbini &obj) = delete;

    static Konbini &getInstance() {
        static Konbini obj;
        return obj;
    }

private:
    Konbini();
    std::unique_ptr<KonbiniUI> ui;
    std::unique_ptr<LanguageManager> lng;

    [[nodiscard]] static std::string userSelectingLanguage();
};
