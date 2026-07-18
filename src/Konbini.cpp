#include "Konbini.h"
#include "Cart.h"
#include "KonbiniUI.h"
#include "LanguageManager.h"
#include "Utils.h"
#include <functional>
#include <memory>
#include <windows.h>

Konbini::Konbini()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    lng = std::make_unique<LanguageManager>();
    ui = std::make_unique<KonbiniUI>();
    accounts = std::make_unique<Accounts>();
    cart = std::make_unique<Cart>();
}

void Konbini::run()
{
    LanguageManager::loadLangTypeFile();

    if (LanguageManager::isLangTypeAlreadySet())
    {
        setSystemLang(LanguageManager::getUserLang());
    }
    else
    {
        setSystemLang(userSelectingLanguage());
        LanguageManager::saveUserLangToFile();
    }
    products = std::make_unique<Products>(LanguageManager::getUserLang());
    Utils::printMsgNLine(LanguageManager::getText("REG_CUP"));
    while (true)
    {
        KonbiniUI::printMenu(LanguageManager::getMainMenu());
        Utils::printWarningMsgNLine(LanguageManager::getText("M_BACK_OPT"));

        if (const auto userCommand{getUserCommand()}; userCommand.has_value() && !executeMainMenuTask(
                                                          userCommand.value()))
        {
            return;
        }
        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_M_COMMAND"));

    }
}

std::optional<int> Konbini::getUserCommand()
{
    const std::string input{Utils::getInput(
        static_cast<std::string>(LanguageManager::getText("OPT_SELECT")))};

    if (Utils::isInt(input))
    {
        return stoi(input);
    }
    return std::nullopt;
}

std::string Konbini::userSelectingLanguage()
{
    KonbiniUI::printUserCanChangeLNG();
    while (true)
    {
        KonbiniUI::printLngMenu();
        if (std::string val = Utils::getInput(KonbiniUI::getLangMsg());
            Utils::isInt(val))
        {
            if (auto lang{LanguageManager::isCorrectUserLang(stoi(val))};
                lang.has_value())
            {
                return lang.value();
            }
        }
        KonbiniUI::printWrongLngInput();
    }
}

void Konbini::setSystemLang(const std::string& lang)
{
    LanguageManager::loadDict(lang);
    LanguageManager::loadMenus();
    LanguageManager::loadLoginMsgs();
}

bool Konbini::executeMainMenuTask(int userOption)
{
    switch (static_cast<MainMenuOPTS>(userOption))
    {
    case MainMenuOPTS::BrowseTheStore:
        browseTheStore();
        break;
    case MainMenuOPTS::CheckCart:
        checkCart();
        break;
    case MainMenuOPTS::AddItemToCart:
        addItemToCart();
        break;
    case MainMenuOPTS::FinalizePurchase:
        finalizePurchase();
        break;
    case MainMenuOPTS::Login:
    {
        if (const auto acc{login()}; acc.has_value())
        {
            Accounts::setLoggedAccEmail(acc.value());
            if (Accounts::getAccType() == Accounts::getUserAccType())
            {
                executeUserMenu();
            }
            else
            {
                executeAdminMenu();
            }
        }
    }
    break;
    case MainMenuOPTS::Register:
        registerNew(Accounts::getUserAccType());
        break;
    case MainMenuOPTS::BecomAEmployee:
        registerNew(Accounts::getAdminAccType());
        break;
    case MainMenuOPTS::RemindPassword:
        remindPassword();
        break;
    case MainMenuOPTS::ChangeLang:
        changeLanguage();
        break;
    case MainMenuOPTS::Exit:
        Utils::printSuccessMsg(LanguageManager::getText("BYE"));
        return false;
    default:
        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_M_COMMAND"));
    }
    return true;
}

bool Konbini::returnToMenu(const std::string& input)
{
    if (input == backToMenuKey)
    {
        Utils::printWarningMsgNLine(LanguageManager::getText("MENU_BACK"));
        return true;
    }
    return false;
}

void Konbini::browseTheStore()
{
    if (Products::isStoreEmpty())
    {
        Utils::printWarningMsgNLine(LanguageManager::getText("STORE_EMPT"));
        return;
    }

    KonbiniUI::printStoreProducts(Products::getProducts(),
                                  Products::getCurrency(),
                                  LanguageManager::getText("QNT"));
}

void Konbini::checkCart()
{
    if (Cart::isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(LanguageManager::getText("EMP_CART"));
    }
    else
    {
        KonbiniUI::printCartItems(Cart::getCartItems(), Products::getCurrency());
        KonbiniUI::printCartSummary(Cart::getCartItems(), Products::getCurrency());
    }
}

std::optional<std::string>
Konbini::getOptionalCorrectInput(const std::string& inputMsg,
                                 const std::regex& inputRegex,
                                 const std::string& wrongInput)
{
    while (true)
    {
        std::string input = Utils::getInput(
            static_cast<std::string>(LanguageManager::getText(inputMsg)));

        if (returnToMenu(input))
        {
            return std::nullopt;
        }

        if (std::regex_match(input, inputRegex))
        {
            return input;
        }

        Utils::printWrongMsgNLine(LanguageManager::getText(wrongInput));
    }
}

std::optional<
    std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)> >
Konbini::getnewAcc(const std::string_view accType)
{
    std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)> newAcc;

    for (size_t i{}; i < static_cast<size_t>(Accounts::AccInfo::Size) - 1; ++i)
    {
        const auto input{getOptionalCorrectInput(inputMsgs[i], registerRegexes[i],
                                                 wrongInputsMsgs[i]),};
        if (!input.has_value())
        {
            return std::nullopt;
        }
        newAcc[i] = input.value();
    }
    newAcc[static_cast<size_t>(Accounts::AccInfo::AccType)] =
        static_cast<std::string>(accType);
    return newAcc;
}

void Konbini::registerNew(const std::string_view accType)
{
    if (const auto newAcc{getnewAcc(accType)}; newAcc.has_value())
    {
        Accounts::addAccToDB(newAcc.value());
        Utils::printSuccessMsg(LanguageManager::getText("ACC_CREATED"));
    }
}

void Konbini::remindPassword()
{
    std::array<std::string, 2> acc;

    while (true)
    {
        for (size_t i{}; i < 2; ++i)
        {
            auto input{getOptionalInput(LanguageManager::getText(inputMsgs[i]))};

            if (!input.has_value())
            {
                return;
            }
            acc[i] = input.value();
        }

        if (Accounts::isCorrectNameEmail(
            acc[static_cast<size_t>(Accounts::AccInfo::Email)],
            acc[static_cast<size_t>(Accounts::AccInfo::Name)]))
        {
            KonbiniUI::printPassword(
                LanguageManager::getText("YOUR_PASS"),
                Accounts::getAccPassword(
                    acc[static_cast<size_t>(Accounts::AccInfo::Email)]));
            return;
        }

        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_NAME_EMAIL"));
    }
}

std::optional<std::string>
Konbini::getOptionalInput(const std::string_view inputMsg)
{
    std::string input;
    Utils::printMsgSpace(inputMsg);

    getline(std::cin, input);

    if (returnToMenu(input))
    {
        return std::nullopt;
    }

    return input;
}

void Konbini::addItemToCart()
{
    if (Products::isStoreEmpty())
    {
        Utils::printWarningMsgNLine(LanguageManager::getText("STORE_EMPT"));
        return;
    }

    const auto productId{getUserProductId()};

    if (!productId.has_value())
    {
        return;
    }

    const std::string prdName{Products::getProductName(productId.value())};

    const auto quantity{getUserQnt(productId.value())};

    if (!quantity.has_value())
    {
        return;
    }

    const ProductData newProduct{.name = prdName,
                                 .price = Products::getProductPrice(productId.value()) *
                                          quantity.value(),
                                 .qnt = quantity.value(),};
    Cart::addProductToCart(productId.value(), newProduct);
    Products::updateStoreAfterAddingToCart(productId.value(), quantity.value());

    Utils::printSuccessMsg(LanguageManager::getText("PRD_ADD_CART"));
}

std::optional<std::string> Konbini::getUserProductId()
{
    while (true)
    {
        std::string input{Utils::getInput(
            static_cast<std::string>(LanguageManager::getText("PRD_NAME"))),};

        if (returnToMenu(input))
        {
            return std::nullopt;
        }

        if (const auto id{isValidUserProduct(input)}; id.has_value())
        {
            return id.value();
        }

        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_PRD"));
    }
}

std::optional<std::string> Konbini::isValidUserProduct(std::string& product)
{
    Utils::lowerString(product);
    if (const auto id{Products::isProductExists(product)}; id.has_value())
    {
        return id.value();
    }

    return std::nullopt;
}

std::optional<int> Konbini::getUserQnt(const std::string& id)
{
    while (true)
    {
        std::string input{Utils::getInput(
            static_cast<std::string>(LanguageManager::getText("PRD_QNT"))),};

        if (returnToMenu(input))
        {
            return std::nullopt;
        }

        if (isValidUserQnt(id, input))
        {
            return stoi(input);
        }

        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_QNT"));
    }
}

bool Konbini::isValidUserQnt(const std::string& id,
                             const std::string& userQnt)
{
    const int productQnt{Products::getProductQnt(id)};
    return Utils::isInt(userQnt) && stoi(userQnt) > 0 &&
           productQnt >= stoi(userQnt);
}

void Konbini::finalizePurchase()
{
    if (Cart::isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(LanguageManager::getText("EMP_CART"));
        return;
    }

    Products::updateFilesAfterPurchase();
    Cart::cleanCart();
    Utils::printSuccessMsg(LanguageManager::getText("THNK_SHP"));
}

void Konbini::changeLanguage()
{
    LanguageManager::clearDict();
    LanguageManager::changeLang();
    Products::setCurrencyAndActualCart(LanguageManager::getUserLang());
    LanguageManager::saveUserLangToFile();
    LanguageManager::loadDict(LanguageManager::getUserLang());
    Cart::reloadCartAfterLangChange(Products::getProducts());
    LanguageManager::loadMenus();
    LanguageManager::loadLoginMsgs();
    Utils::printSuccessMsg(LanguageManager::getText("LNG_CHN"));
}


std::optional<std::string> Konbini::login()
{
    std::array<std::string, 2> acc;
    size_t i{};
    while (true)
    {
        std::string input = Utils::getInput(LanguageManager::getLoginMsg(i));

        if (returnToMenu(input))
        {
            return std::nullopt;
        }
        acc[i] = input;

        if (i == 1 && isLoginOk(acc[0], acc[i]))
        {
            return acc[0];
        }

        if (i == 1)
        {
            --i;
            Utils::printWrongMsgNLine(LanguageManager::getText("WRN_LOGIN"));
        }
        else
        {
            ++i;
        }
    }
}

bool Konbini::isLoginOk(const std::string& email, const std::string& pass)
{
    return Accounts::isAccExists(email) && Accounts::isEmailMatchingPassword(email, pass);
}


void Konbini::executeUserMenu()
{
    while (true)
    {
        KonbiniUI::printMenu(LanguageManager::getUserMenu());
        if (const auto userCommand{getUserCommand()}; userCommand.has_value())
        {
            if (!executeLoggedUserTask(userCommand.value()))
            {
                return;
            }
        }
    }
}

bool Konbini::executeLoggedUserTask(int command)
{
    switch (static_cast<LoggedUserMenuOPTS>(command))
    {
    case LoggedUserMenuOPTS::ShowAccountDetails:
        break;
    case LoggedUserMenuOPTS::ChangeEmail:
        break;
    case LoggedUserMenuOPTS::ChangePassword:
        break;
    case LoggedUserMenuOPTS::BrowseTheStore:
        browseTheStore();
        break;
    case LoggedUserMenuOPTS::PurchaseHistory:
        break;
    case LoggedUserMenuOPTS::CheckCart:
        checkCart();
        break;
    case LoggedUserMenuOPTS::AddItemToCart:
        addItemToCart();
        break;
    case LoggedUserMenuOPTS::FinalizePurchase:
        finalizePurchase();
        break;
    case LoggedUserMenuOPTS::ChangelanguageToJapanese:
        changeLanguage();
        break;
    case LoggedUserMenuOPTS::DeleteAccount:
        break;
    case LoggedUserMenuOPTS::Logout:
        return false;
        break;
    case LoggedUserMenuOPTS::Exit:
        std::exit(EXIT_SUCCESS);
        break;
    default:
        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_M_COMMAND"));
        break;
    }

    return true;
}

void Konbini::executeAdminMenu()
{

}