#pragma once
#include "Accounts.h"
#include "Cart.h"
#include "KonbiniUI.h"
#include "LanguageManager.h"
#include "Products.h"
#include <regex>
#include <variant>

using newProductInputVariant = std::variant<std::string, int, double, std::monostate>;

class Konbini
{
    enum class MainMenuOPTS : std::uint8_t
    {
        BrowseTheStore = 1,
        CheckCart = 2,
        AddItemToCart = 3,
        ChangeQuantity = 4,
        RemoveProductFromCart = 5,
        FinalizePurchase = 6,
        Login = 7,
        Register = 8,
        BecomAEmployee = 9,
        RemindPassword = 10,
        ChangeLang = 11,
        Exit = 12,
    };

    enum class LoggedUserMenuOPTS : std::uint8_t
    {
        ShowAccountDetails = 1,
        ChangeEmail = 2,
        ChangePassword = 3,
        BrowseTheStore = 4,
        PurchaseHistory = 5,
        CheckCart = 6,
        AddItemToCart = 7,
        ChangeQuantity = 8,
        RemoveProductFromCart = 9,
        FinalizePurchase = 10,
        ChangelanguageToJapanese = 11,
        DeleteAccount = 12,
        Logout = 13,
        Exit = 14,
    };

    enum class LoggedAdminMenuOPTS : std::uint8_t
    {
        ShowAccountDetails = 1,
        ChangeEmail = 2,
        ChangePassword = 3,
        BrowseTheStore = 4,
        PurchaseHistory = 5,
        CheckCart = 6,
        AddItemToCart = 7,
        ChangeQuantity = 8,
        RemoveProductFromCart = 9,
        FinalizePurchase = 10,
        AddNewProductToStore = 11,
        ChangeStoreProductQuantity = 12,
        RemoveProductFromTheStore = 13,
        ChangelanguageToJapanese = 14,
        DeleteAccount = 15,
        Logout = 16,
        Exit = 17,
    };

  public:
    Konbini();
    void run();

  private:
    std::unique_ptr<KonbiniUI> ui{nullptr};
    std::unique_ptr<LanguageManager> lng{nullptr};
    std::unique_ptr<Products> products{nullptr};
    std::unique_ptr<Cart> cart{nullptr};
    std::unique_ptr<Accounts> accounts{nullptr};

    [[nodiscard]] std::string userSelectingLanguage() const;

    void setSystemLang(const std::string& lang) const;

    [[nodiscard]] std::optional<int> getUserCommand() const;

    [[nodiscard]] bool executeMainMenuTask(int userOption) const;

    [[nodiscard]] bool returnToMenu(const std::string& input) const;

    static constexpr std::string_view backToMenuKey{"0"};

    void browseTheStore() const;

    void checkCart(bool isUser = false) const;

    [[nodiscard]] std::optional<int> getOptionalPositiveInt(std::string_view inputMsg) const;

    void changeQuantity() const;

    void removeProductFromCart() const;

    [[nodiscard]] bool isNewQuantityOK(const std::string& id, int qnt) const;

    void registerNew(std::string_view accType) const;

    [[nodiscard]] std::optional<std::string>
    getOptionalCorrectInput(std::string_view inputMsg, const std::regex& inputRegex, std::string_view wrongInput) const;

    inline static const std::array<std::string, 3> inputMsgs{"NAME", "EMAIL", "PSWD"};
    inline static const std::array<std::string, 3> wrongInputsMsgs{"NAME_ERR", "EMAIL_ERR", "PSWD_ERR"};
    inline static const std::array<std::regex, 3> registerRegexes{
        std::regex{"^[a-zA-Z]{2,15}$"}, std::regex{"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+[.][a-zA-Z]{2,}$"},
        std::regex{"(?=.*[a-zA-Z])(?=.*[0-9])(?=.*[^a-zA-Z0-9]).{6,20}$"}};

    [[nodiscard]] std::optional<std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)>>
    getnewAcc(std::string_view accType) const;

    void remindPassword() const;

    [[nodiscard]] std::optional<std::string> getOptionalInput(std::string_view inputMsg) const;

    void addItemToCart() const;

    [[nodiscard]] std::optional<std::string> isValidUserProduct(std::string& product) const;

    [[nodiscard]] std::optional<std::string> getUserProductId() const;

    [[nodiscard]] std::optional<int> getUserQnt(const std::string& id) const;

    [[nodiscard]] bool isValidUserQnt(const std::string& id, const std::string& userQnt) const;

    void finalizePurchase() const;

    void changeLanguage() const;

    [[nodiscard]] std::optional<std::string> login() const;

    [[nodiscard]] bool isLoginOk(const std::string& email, const std::string& pass) const;

    void executeUserMenu() const;

    [[nodiscard]] bool executeLoggedUserTask(int command) const;

    void showAccountDetails() const;

    void changeEmail() const;

    void changePassword() const;

    void executeAdminMenu() const;

    [[nodiscard]] bool executeLoggedAdminTask(int command) const;

    void addNewProductToStore() const;

    [[nodiscard]] newProductInputVariant getNewProductName() const;

    [[nodiscard]] newProductInputVariant getNewProductQnt() const;

    [[nodiscard]] newProductInputVariant getNewPoductPrice() const;

    void removeProdcutFromStore() const;

    void changeStoreProductQuantity() const;
};