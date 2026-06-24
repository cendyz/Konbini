#pragma once
#include "KonbiniUI.h"
#include "LanguageManager.h"
#include <memory>

class Konbini {
public:
    Konbini(const Konbini &obj) = delete;

    Konbini &operator=(Konbini &obj) = delete;

    static Konbini &getInstance() {
        static Konbini obj;
        return obj;
    }

    void run();

private:
    Konbini();

    std::unique_ptr<KonbiniUI> ui;
    std::unique_ptr<LanguageManager> lng;

    [[nodiscard]] static std::string userSelectingLanguage();

    [[nodiscard]] static bool checkUserLang(const std::string &input);

    void setSystemLang(const std::string &lang) const;
};
