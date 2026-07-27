#include "../include/Konbini.h"
#include "../include/Cart.h"
#include "../include/Colors.h"
#include "../include/KonbiniUI.h"
#include "../include/LanguageManager.h"
#include "../include/Utils.h"
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
    Utils::printColorfullMsgNLine(COLORS::GREEN, LanguageManager::getText("REG_CUP"));
    while (true)
    {
        KonbiniUI::printMenu(LanguageManager::getMainMenu());
        Utils::printWarningMsgNLine(LanguageManager::getText("M_BACK_OPT"));

        if (const auto userCommand{getUserCommand()};
            userCommand.has_value() && !executeMainMenuTask(userCommand.value()))
        {
            return;
        }
    }
}

std::optional<int> Konbini::getUserCommand()
{
    if (const std::string input{Utils::getInput(LanguageManager::getText("OPT_SELECT"))};
        input.size() < 3 && Utils::isInt(input))
    {
        return stoi(input);
    }
    Utils::printWrongMsgNLine(LanguageManager::getText("WRN_M_COMMAND"));
    Utils::printMsgNLine("");
    return std::nullopt;
}

std::string Konbini::userSelectingLanguage()
{
    KonbiniUI::printUserCanChangeLNG();
    while (true)
    {
        KonbiniUI::printLngMenu();
        if (std::string val = Utils::getInput(KonbiniUI::getLangMsg()); Utils::isInt(val))
        {
            if (auto lang{LanguageManager::isCorrectUserLang(stoi(val))}; lang.has_value())
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

std::optional<std::string> Konbini::getOptionalInput(const std::string_view inputMsg)
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

bool Konbini::returnToMenu(const std::string& input)
{
    if (input == backToMenuKey)
    {
        Utils::printWarningMsgNLine(LanguageManager::getText("MENU_BACK"));
        return true;
    }
    return false;
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
    case MainMenuOPTS::ChangeQuantity:
        changeQuantity();
        break;
    case MainMenuOPTS::RemoveProductFromCart:
        removeProductFromCart();
        break;
    case MainMenuOPTS::FinalizePurchase:
        finalizePurchase();
        break;
    case MainMenuOPTS::Login:
    {
        if (const auto acc{login()}; acc.has_value())
        {
            Accounts::setLoggedAccEmail(acc.value());
            Utils::printSuccessMsg(LanguageManager::getText("SUCC_LOG"));
            Utils::printMsgNLine("");
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
    Utils::printMsgNLine("");
    return true;
}

void Konbini::browseTheStore()
{
    if (Products::isStoreEmpty())
    {
        Utils::printWarningMsgNLine(LanguageManager::getText("STORE_EMPT"));
        return;
    }

    KonbiniUI::printStoreProducts(Products::getProducts(), Products::getCurrency(), LanguageManager::getText("QNT"));
}

void Konbini::checkCart(const bool isUser)
{
    if (Cart::isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(LanguageManager::getText("EMP_CART"));
    }
    else
    {
        KonbiniUI::printCartItems(Cart::getCartItems(), Products::getCurrency());
        KonbiniUI::printCartSummary(Cart::getCartSummaries(isUser), Products::getCurrency(), isUser);
    }
}

void Konbini::changeQuantity()
{

    if (Cart::isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(LanguageManager::getText("EMP_CART"));
        return;
    }

    while (true)
    {
        const auto productId{getUserProductId()};

        if (!productId.has_value())
        {
            return;
        }

        if (!Cart::isItemInCart(productId.value()))
        {
            Utils::printWrongMsgNLine(LanguageManager::getText("NOT_IN_C"));
            continue;
        }

        const auto newQuantity{getOptionalInput(LanguageManager::getText("PRD_N_QNT"))};

        if (!newQuantity.has_value())
        {
            return;
        }

        if (!Utils::isInt(newQuantity.value()) || !isNewQuantityOK(productId.value(), std::stoi(newQuantity.value())))
        {
            Utils::printWrongMsgNLine(LanguageManager::getText("WRN_QNT"));
            continue;
        }

        const int newQnt{std::stoi(newQuantity.value())};

        Products::updateStoreAfterQntChange(productId.value(), newQnt, Cart::getCartItemQnt(productId.value()));
        Cart::setNewProductQnty(productId.value(), newQnt);
        Utils::printSuccessMsg(LanguageManager::getText("SUCC_CHNQ"));
        return;
    }
}

bool Konbini::isNewQuantityOK(const std::string& id, const int qnt)
{

    const int qntFromStore{Products::getProductQnt(id)};
    const bool isToLowerQntOk{qnt < qntFromStore};
    const bool isToBiggerQntOK{qnt <= qntFromStore + Cart::getCartItemQnt(id)};
    return qnt != Cart::getCartItemQnt(id) && qnt > 0 && (isToLowerQntOk || isToBiggerQntOK);
}

std::optional<std::string> Konbini::getOptionalCorrectInput(const std::string_view inputMsg,
                                                            const std::regex& inputRegex,
                                                            const std::string_view wrongInput)
{
    while (true)
    {
        auto input{getOptionalInput(LanguageManager::getText(inputMsg.data()))};
        if (!input.has_value())
        {
            return std::nullopt;
        }

        if (std::regex_match(input.value(), inputRegex))
        {
            return input.value();
        }

        Utils::printWrongMsgNLine(LanguageManager::getText(wrongInput.data()));
    }
}

void Konbini::removeProductFromCart()
{
    if (Cart::isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(LanguageManager::getText("EMP_CART"));
        return;
    }

    while (true)
    {
        const auto input{getUserProductId()};

        if (!input.has_value())
        {
            return;
        }

        if (Cart::isItemInCart(input.value()))
        {
            Products::updateStoreAfterCartItemRemoved(input.value(), Cart::getCartItemQnt(input.value()));
            Cart::removeCartItem(input.value());
            Utils::printSuccessMsg(LanguageManager::getText("ITM_REMV"));
            return;
        }

        Utils::printWrongMsgNLine(LanguageManager::getText("NOT_IN_C"));
    }
}

std::optional<std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)>>
Konbini::getnewAcc(const std::string_view accType)
{
    std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)> newAcc;

    for (size_t i{}; i < static_cast<size_t>(Accounts::AccInfo::Size) - 1; ++i)
    {
        auto input{
            getOptionalCorrectInput(inputMsgs[i], registerRegexes[i], wrongInputsMsgs[i]),
        };
        if (!input.has_value())
        {
            return std::nullopt;
        }
        if (i == static_cast<size_t>(Accounts::AccInfo::Email) || i == static_cast<size_t>(Accounts::AccInfo::Name))
        {
            Utils::lowerString(input.value());
        }
        newAcc[i] = input.value();
    }
    newAcc[static_cast<size_t>(Accounts::AccInfo::AccType)] = static_cast<std::string>(accType);
    return newAcc;
}

void Konbini::registerNew(const std::string_view accType)
{
    if (const auto newAcc{getnewAcc(accType)}; newAcc.has_value())
    {
        Accounts::addAccToVar(newAcc.value());
        Accounts::addAccToFile(newAcc.value());
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
            Utils::lowerString(input.value());
            acc[i] = input.value();
        }

        if (Accounts::isCorrectNameEmail(acc[static_cast<size_t>(Accounts::AccInfo::Email)],
                                         acc[static_cast<size_t>(Accounts::AccInfo::Name)]))
        {
            KonbiniUI::printPassword(LanguageManager::getText("YOUR_PASS"),
                                     Accounts::getAccPassword(acc[static_cast<size_t>(Accounts::AccInfo::Email)]));
            return;
        }

        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_NAME_EMAIL"));
    }
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

    const ProductData newProduct{
        .name = prdName,
        .price = Products::getProductPrice(productId.value()) * quantity.value(),
        .qnt = quantity.value(),
    };
    Cart::addProductToCart(productId.value(), newProduct);
    Products::updateStoreAfterAddingToCart(productId.value(), quantity.value());

    Utils::printSuccessMsg(LanguageManager::getText("PRD_ADD_CART"));
}

std::optional<std::string> Konbini::getUserProductId()
{
    while (true)
    {
        auto input{getOptionalInput(LanguageManager::getText("PRD_NAME"))};

        if (!input.has_value())
        {
            return std::nullopt;
        }

        if (const auto id{isValidUserProduct(input.value())}; id.has_value())
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
        auto input{getOptionalInput(LanguageManager::getText("PRD_QNT"))};

        if (!input.has_value())
        {
            return std::nullopt;
        }

        if (isValidUserQnt(id, input.value()))
        {
            return stoi(input.value());
        }

        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_QNT"));
    }
}

bool Konbini::isValidUserQnt(const std::string& id, const std::string& userQnt)
{
    const int productQnt{Products::getProductQnt(id)};
    return Utils::isInt(userQnt) && stoi(userQnt) > 0 && productQnt >= stoi(userQnt);
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
    Products::setCurrencyAndActualProductsLang(LanguageManager::getUserLang());
    LanguageManager::saveUserLangToFile();
    LanguageManager::loadDict(LanguageManager::getUserLang());
    Cart::reloadCartAfterLangChange(Products::getProductList());
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
        auto input{getOptionalInput(LanguageManager::getLoginMsg(i))};

        if (!input.has_value())
        {
            return std::nullopt;
        }
        Utils::lowerString(input.value());
        acc[i] = input.value();

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
        showAccountDetails();
        break;
    case LoggedUserMenuOPTS::ChangeEmail:
        changeEmail();
        break;
    case LoggedUserMenuOPTS::ChangePassword:
        changePassword();
        break;
    case LoggedUserMenuOPTS::BrowseTheStore:
        browseTheStore();
        break;
    case LoggedUserMenuOPTS::PurchaseHistory:
        break;
    case LoggedUserMenuOPTS::CheckCart:
        checkCart(true);
        break;
    case LoggedUserMenuOPTS::AddItemToCart:
        addItemToCart();
        break;
    case LoggedUserMenuOPTS::ChangeQuantity:
        changeQuantity();
        break;
    case LoggedUserMenuOPTS::RemoveProductFromCart:
        removeProductFromCart();
        break;
    case LoggedUserMenuOPTS::FinalizePurchase:
        finalizePurchase();
        break;
    case LoggedUserMenuOPTS::ChangelanguageToJapanese:
        changeLanguage();
        break;
    case LoggedUserMenuOPTS::DeleteAccount:
        Products::updateStoreAfterDeletingAccount(Cart::getCartItems());
        Accounts::deleteAccFromVar();
        Accounts::updateAccsFile();
        Utils::printSuccessMsg(LanguageManager::getText("ACC_DEL"));
        return false;
    case LoggedUserMenuOPTS::Logout:
        Utils::printWarningMsgNLine(LanguageManager::getText("LOG_OUT"));
        return false;
    case LoggedUserMenuOPTS::Exit:
        Utils::printSuccessMsg(LanguageManager::getText("BYE"));
        std::exit(EXIT_SUCCESS);
    default:
        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_M_COMMAND"));
    }
    Utils::printMsgNLine("");
    return true;
}

void Konbini::showAccountDetails()
{
    const auto acc{Accounts::getLoggedAcc()};
    for (size_t i{}; i < acc.size(); ++i)
    {
        Utils::printColorfullMsg(COLORS::PURPLE, LanguageManager::getText("S_ACC_" + std::to_string(i)));
        Utils::printColonWSpace();
        Utils::printMsgNLine(acc[i]);
    }
}

void Konbini::changeEmail()
{
    while (true)
    {
        auto input{getOptionalCorrectInput("N_EMAIL", registerRegexes[static_cast<size_t>(Accounts::AccInfo::Email)],
                                           "EMAIL_ERR")};

        if (!input.has_value())
        {
            return;
        }

        Utils::lowerString(input.value());

        if (!Accounts::isAccExists(input.value()))
        {
            Accounts::setNewEmail(input.value());
            Accounts::updateAccsFile();
            Utils::printSuccessMsg(LanguageManager::getText("EMAIL_CHANGED"));
            return;
        }

        Utils::printWrongMsgNLine(LanguageManager::getText("EMAIL_EXST"));
    }
}

void Konbini::changePassword()
{
    const auto input{
        getOptionalCorrectInput("NEW_PASS", registerRegexes[static_cast<size_t>(Accounts::AccInfo::Pass)], "PSWD_ERR")};

    if (!input.has_value())
    {
        return;
    }

    Accounts::setNewPassword(input.value());
    Accounts::updateAccsFile();
    Utils::printSuccessMsg(LanguageManager::getText("NEW_PASS_CHNGD"));
}

void Konbini::executeAdminMenu()
{
    while (true)
    {
        KonbiniUI::printMenu(LanguageManager::getAdminMenu());
        if (const auto userCommand{getUserCommand()}; userCommand.has_value())
        {
            if (!executeLoggedAdminTask(userCommand.value()))
            {
                return;
            }
        }
    }
}

std::optional<bool> Konbini::executeLoggedAdminTask(int command)
{
    switch (static_cast<LoggedAdminMenuOPTS>(command))
    {
    case LoggedAdminMenuOPTS::ShowAccountDetails:
        showAccountDetails();
        break;
    case LoggedAdminMenuOPTS::ChangeEmail:
        changeEmail();
        Accounts::updateAccsFile();
        break;
    case LoggedAdminMenuOPTS::ChangePassword:
        changePassword();
        break;
    case LoggedAdminMenuOPTS::BrowseTheStore:
        browseTheStore();
        break;
    case LoggedAdminMenuOPTS::PurchaseHistory:
        break;
    case LoggedAdminMenuOPTS::CheckCart:
        checkCart(true);
        break;
    case LoggedAdminMenuOPTS::AddItemToCart:
        addItemToCart();
        break;
    case LoggedAdminMenuOPTS::ChangeQuantity:
        changeQuantity();
        break;
    case LoggedAdminMenuOPTS::RemoveProductFromCart:
        removeProductFromCart();
        break;
    case LoggedAdminMenuOPTS::FinalizePurchase:
        finalizePurchase();
        break;
    case LoggedAdminMenuOPTS::AddNewProductToStore:
        break;
    case LoggedAdminMenuOPTS::ChangeStoreProductQuantity:
        break;
    case LoggedAdminMenuOPTS::RemoveProductFromTheStore:
        break;
    case LoggedAdminMenuOPTS::ChangelanguageToJapanese:
        break;
    case LoggedAdminMenuOPTS::DeleteAccount:
        Products::updateStoreAfterDeletingAccount(Cart::getCartItems());
        Accounts::deleteAccFromVar();
        Accounts::updateAccsFile();
        Utils::printSuccessMsg(LanguageManager::getText("ACC_DEL"));
        break;
    case LoggedAdminMenuOPTS::Logout:
        Utils::printWarningMsgNLine(LanguageManager::getText("LOG_OUT"));
        return false;
    case LoggedAdminMenuOPTS::Exit:
        Utils::printSuccessMsg(LanguageManager::getText("BYE"));
        std::exit(EXIT_SUCCESS);
    default:
        Utils::printWrongMsgNLine(LanguageManager::getText("WRN_M_COMMAND"));
    }
    Utils::printMsgNLine("");

    return true;
}