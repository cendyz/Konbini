#pragma once
#include "KonbiniUI.h"
#include "LanguageManager.h"
#include "Products.h"
#include <memory>

class Konbini {
    enum class MainMenuOPTS {
        BrowseTheStore = 1,
        CheckCart = 2,
        FinalizePurchase = 3,
        Login = 4,
        Register = 5,
        BecomAEmployee = 6,
        RemindPassword = 7,
        Exit = 8
    };

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
    std::unique_ptr<Products> items;

    [[nodiscard]] static std::string userSelectingLanguage();

    [[nodiscard]] static bool checkUserLang(const std::string &input);

    void setSystemLang(const std::string &lang) const;

    [[nodiscard]] bool executeMainMenuTaks(int userOption);

    [[nodiscard]] static bool isUserCommandOk(const std::string &input);

    void browseTheStore();
};
