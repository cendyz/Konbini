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
    Konbini(const Konbini& obj) = delete;

    Konbini& operator=(Konbini& obj) = delete;

    static Konbini& getInstance()
    {
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

    static void setSystemLang(const std::string& lang);

    [[nodiscard]] static std::optional<int> getUserCommand();

    [[nodiscard]] static bool executeMainMenuTask(int userOption);

    [[nodiscard]] static bool returnToMenu(const std::string& input);

    static constexpr std::string_view backToMenuKey{"0"};

    static void browseTheStore();

    static void checkCart(bool isUser = false);

    static void changeQuantity();

    static void removeProductFromCart();

    [[nodiscard]] static bool isNewQuantityOK(const std::string& id, int qnt);

    static void registerNew(std::string_view accType);

    [[nodiscard]] static std::optional<std::string>
    getOptionalCorrectInput(std::string_view inputMsg, const std::regex& inputRegex, std::string_view wrongInput);

    inline static const std::array<std::string, 3> inputMsgs{"NAME", "EMAIL", "PSWD"};
    inline static const std::array<std::string, 3> wrongInputsMsgs{"NAME_ERR", "EMAIL_ERR", "PSWD_ERR"};
    inline static const std::array<std::regex, 3> registerRegexes{
        std::regex{"^[a-zA-Z]{2,15}$"}, std::regex{"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+[.][a-zA-Z]{2,}$"},
        std::regex{"(?=.*[a-zA-Z])(?=.*[0-9])(?=.*[^a-zA-Z0-9]).{6,20}$"}};

    [[nodiscard]] static std::optional<std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)>>
    getnewAcc(std::string_view accType);

    static void remindPassword();

    [[nodiscard]] static std::optional<std::string> getOptionalInput(std::string_view inputMsg);

    static void addItemToCart();

    [[nodiscard]] static std::optional<std::string> isValidUserProduct(std::string& product);

    [[nodiscard]] static std::optional<std::string> getUserProductId();

    [[nodiscard]] static std::optional<int> getUserQnt(const std::string& id);

    [[nodiscard]] static bool isValidUserQnt(const std::string& id, const std::string& userQnt);

    static void finalizePurchase();

    static void changeLanguage();

    [[nodiscard]] static std::optional<std::string> login();

    [[nodiscard]] static bool isLoginOk(const std::string& email, const std::string& pass);

    static void executeUserMenu();

    [[nodiscard]] static bool executeLoggedUserTask(int command);

    static void showAccountDetails();

    static void changeEmail();

    static void changePassword();

    static void executeAdminMenu();

    [[nodiscard]] static bool executeLoggedAdminTask(int command);

    static void addNewProductToStore();

    [[nodiscard]] static newProductInputVariant getNewProductName();

    [[nodiscard]] static newProductInputVariant getNewProductQnt();

    [[nodiscard]] static newProductInputVariant getNewPoductPrice();

    static void removeProdcutFromStore();
};