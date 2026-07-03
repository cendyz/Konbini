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

  [[nodiscard]] static bool returnToMenu(const std::string &input);

  static constexpr std::string_view backToMenuKey{"0"};

  static void browseTheStore();

  static void checkCart();

  static void registerPerson();

  [[nodiscard]] static std::optional<std::string> getCorrectRegisterInfo(
    const std::string &inputMsg, const std::regex &inputRegex, const std::string &wrongInput);

  inline static const std::array<std::string, 3> inputMsgs{"NAME", "PSWD", "EMAIL"};
  inline static const std::array<std::string, 3> wrongInputsMsgs{"NAME_ERR", "PSWD_ERR", "EMAIL_ERR"};
  inline static const std::array<std::regex, 3> registerRegexes{
    std::regex{"^[a-zA-Z]{2,15}$"},
    std::regex{"(?=.*[a-zA-Z])(?=.*[0-9])(?=.*[^a-zA-Z0-9]).{6,20}$"},
    std::regex{"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+[.][a-zA-Z]{2,}$"}
  };
  inline static const std::string userAccType{"user"};

  [[nodiscard]] static std::optional<std::array<std::string,
    static_cast<size_t>(Accounts::AccInfo::Size)> > getnewAcc();
};
