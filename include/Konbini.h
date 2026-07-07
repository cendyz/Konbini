#pragma once
#include "Accounts.h"
#include "Cart.h"
#include "KonbiniUI.h"
#include "LanguageManager.h"
#include "Products.h"
#include <functional>
#include <memory>
#include <regex>

class Konbini {
  enum class MainMenuOPTS : std::uint8_t {
    BrowseTheStore = 1,
    CheckCart = 2,
    AddItemToCart = 3,
    FinalizePurchase = 4,
    Login = 5,
    Register = 6,
    BecomAEmployee = 7,
    RemindPassword = 8,
    Exit = 9
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

  static void setSystemLang(const std::string &lang);

  [[nodiscard]] bool executeMainMenuTaks(int userOption);

  [[nodiscard]] static bool returnToMenu(const std::string &input);

  static constexpr std::string_view backToMenuKey{"0"};

  static void browseTheStore();

  static void checkCart();

  static void registerNew(std::string_view accType);

  [[nodiscard]] static std::optional<std::string>
  getOptionalCorrectInput(const std::string &inputMsg,
                          const std::regex &inputRegex,
                          const std::string &wrongInput);

  inline static const std::array<std::string, 3> inputMsgs{"NAME", "EMAIL",
                                                           "PSWD"};
  inline static const std::array<std::string, 3> wrongInputsMsgs{
      "NAME_ERR", "EMAIL_ERR", "PSWD_ERR"};
  inline static const std::array<std::regex, 3> registerRegexes{
      std::regex{"^[a-zA-Z]{2,15}$"},
      std::regex{"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+[.][a-zA-Z]{2,}$"},
      std::regex{"(?=.*[a-zA-Z])(?=.*[0-9])(?=.*[^a-zA-Z0-9]).{6,20}$"}};

  [[nodiscard]] static std::optional<
      std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)>>
  getnewAcc(std::string_view accType);

  static void remindPassword();

  [[nodiscard]] static std::optional<std::string>
  getOptionalInput(std::string_view inputMsg);

  static void addItemToCart();

  [[nodiscard]] static std::optional<std::string> isValidUserProduct(std::string &product);

  [[nodiscard]] static std::optional<std::string> getUserProductId();

  [[nodiscard]] static std::optional<int> getUserQnt(const std::string &id);

  [[nodiscard]] static bool isValidUserQnt(const std::string &id,
                                           const std::string &userQnt);
};
