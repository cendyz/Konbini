#pragma once
#include "Cart.h"
#include "KonbiniUI.h"
#include "LanguageManager.h"
#include "Products.h"
#include "Accounts.h"
#include <memory>
#include <regex>

class Konbini {
  enum class MainMenuOPTS : std::uint8_t {
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

  std::unique_ptr<KonbiniUI> ui{nullptr};
  std::unique_ptr<LanguageManager> lng{nullptr};
  std::unique_ptr<Products> products{nullptr};
  std::unique_ptr<Cart> cart{nullptr};
  std::unique_ptr<Accounts> accounts{nullptr};

  [[nodiscard]] static std::string userSelectingLanguage();

  [[nodiscard]] static bool checkUserLang(const std::string &input);

  static void setSystemLang(const std::string &lang);

  [[nodiscard]] bool executeMainMenuTaks(int userOption);

  [[nodiscard]] static bool isUserCommandOk(const std::string &input);

  static void browseTheStore();

  static void checkCart();

  static void registerPerson();

  [[nodiscard]] static std::string getCorrectName();

  inline static std::wregex nameRegex{L"^[a-zA-Z\\u3040-\\u309F\\u30A0-\\u30FF\\u4E00-\\u9FAF]{2,15}$"};
};
