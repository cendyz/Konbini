#include "../include/Konbini.h"
#include "../include/Cart.h"
#include "../include/Colors.h"
#include "../include/KonbiniUI.h"
#include "../include/LanguageManager.h"
#include "../include/Utils.h"
#include <functional>
#include <variant>
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
    lng->loadLangTypeFile();

    if (lng->isLangTypeAlreadySet())
    {
        setSystemLang(lng->getUserLang());
    }
    else
    {
        setSystemLang(userSelectingLanguage());
        lng->saveUserLangToFile();
    }
    products = std::make_unique<Products>(lng->getUserLang());
    Utils::printColorfullMsgNLine(COLORS::GREEN, lng->getText("REG_CUP"));
    Utils::printMsgNLine("");
    while (true)
    {
        KonbiniUI::printMenu(lng->getMainMenu());
        Utils::printWarningMsgNLine(lng->getText("M_BACK_OPT"));

        if (const auto userCommand{getUserCommand()};
            userCommand.has_value() && !executeMainMenuTask(userCommand.value()))
        {
            return;
        }
    }
}

std::optional<int> Konbini::getUserCommand() const
{
    if (const std::string input{Utils::getFullLineInput(lng->getText("OPT_SELECT"))};
        input.size() < 3 && Utils::isInt(input))
    {
        return stoi(input);
    }
    Utils::printWrongMsgNLine(lng->getText("WRN_M_COMMAND"));
    Utils::printMsgNLine("");
    return std::nullopt;
}

std::string Konbini::userSelectingLanguage() const
{
    KonbiniUI::printUserCanChangeLNG();
    while (true)
    {
        KonbiniUI::printLngMenu();
        if (std::string val = Utils::getFullLineInput(KonbiniUI::getLangMsg()); Utils::isInt(val))
        {
            if (auto lang{lng->isCorrectUserLang(stoi(val))}; lang.has_value())
            {
                return lang.value();
            }
        }
        KonbiniUI::printWrongLngInput();
    }
}

void Konbini::setSystemLang(const std::string& lang) const
{
    lng->loadDict(lang);
    lng->loadMenus();
    lng->loadLoginMsgs();
}

std::optional<int> Konbini::getOptionalPositiveInt(const std::string_view inputMsg) const
{
    while (true)
    {
        std::string input;
        Utils::printMsgSpace(inputMsg);
        getline(std::cin, input);

        if (returnToMenu(input))
        {
            return std::nullopt;
        }

        if (Utils::isInt(input) && std::stoi(input) > 0)
        {
            return std::stoi(input);
        }
        Utils::printWrongMsgNLine(lng->getText("WRN_QNT"));
    }
}

std::optional<double> Konbini::getOptionalPositiveDouble(std::string_view inputMsg) const
{
    while (true)
    {
        std::string input;
        Utils::printMsgSpace(inputMsg);
        getline(std::cin, input);

        if (returnToMenu(input))
        {
            return std::nullopt;
        }

        if (std::regex_match(input, doubleRegex))
        {
            return std::stod(input);
        }
        Utils::printWrongMsgNLine(lng->getText("WRN_PRD_PRICE"));
    }
}

std::optional<std::string> Konbini::getOptionalInput(const std::string_view inputMsg) const
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

bool Konbini::returnToMenu(const std::string& input) const
{
    if (input == backToMenuKey)
    {
        Utils::printWarningMsgNLine(lng->getText("MENU_BACK"));
        return true;
    }
    return false;
}

bool Konbini::executeMainMenuTask(int userOption) const
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
            accounts->setLoggedAccEmail(acc.value());
            Utils::printSuccessMsg(lng->getText("SUCC_LOG"));
            Utils::printMsgNLine("");
            if (accounts->getAccType() == Accounts::getUserAccType())
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
        Utils::printSuccessMsg(lng->getText("BYE"));
        return false;
    default:
        Utils::printWrongMsgNLine(lng->getText("WRN_M_COMMAND"));
    }
    Utils::printMsgNLine("");
    return true;
}

void Konbini::browseTheStore() const
{
    if (products->isStoreEmpty())
    {
        Utils::printWarningMsgNLine(lng->getText("STORE_EMPT"));
        return;
    }
    KonbiniUI::printStoreProducts(products->getProducts(), products->getCurrency(), lng->getText("PRD_QNT"));
}

void Konbini::checkCart(const bool isUser) const
{
    if (cart->isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(lng->getText("EMP_CART"));
    }
    else
    {
        KonbiniUI::printCartItems(cart->getCartItems(), products->getCurrency());
        const std::string_view msg{isUser ? lng->getText("DSC_CRT_SUM") : lng->getText("CRT_SUM")};
        KonbiniUI::printCartSummary(cart->getCartSummaries(isUser), products->getCurrency(), msg, isUser);
    }
}

void Konbini::changeQuantity() const
{

    if (cart->isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(lng->getText("EMP_CART"));
        return;
    }

    while (true)
    {
        const auto productId{getUserProductId()};

        if (!productId.has_value())
        {
            return;
        }
        if (!cart->isItemIdInCart(productId.value()))
        {
            Utils::printWrongMsgNLine(lng->getText("NOT_IN_C"));
            continue;
        }

        const auto newQuantity{getOptionalPositiveInt(lng->getText("PRD_N_QNT"))};

        if (!newQuantity.has_value())
        {
            return;
        }

        if (!isNewQuantityOK(productId.value(), newQuantity.value()))
        {
            Utils::printWrongMsgNLine(lng->getText("WRN_QNT"));
            continue;
        }

        const int newQnt{newQuantity.value()};

        products->updateStoreAfterQntChange(productId.value(), newQnt, cart->getCartItemQnt(productId.value()));
        cart->setNewProductQnty(productId.value(), newQnt);
        Utils::printSuccessMsg(lng->getText("SUCC_CHNQ"));
        return;
    }
}

bool Konbini::isNewQuantityOK(const std::string& id, const int qnt) const
{
    const int qntFromStore{products->getProductQnt(id)};
    const bool isToLowerQntOk{qnt <= qntFromStore};
    const bool isToBiggerQntOK{qnt <= qntFromStore + cart->getCartItemQnt(id)};
    return qnt != cart->getCartItemQnt(id) && qnt > 0 && (isToLowerQntOk || isToBiggerQntOK);
}

std::optional<std::string> Konbini::getOptionalCorrectInput(const std::string_view inputMsg,
                                                            const std::regex& inputRegex,
                                                            const std::string_view wrongInput) const
{
    while (true)
    {
        auto input{getOptionalInput(lng->getText(inputMsg.data()))};
        if (!input.has_value())
        {
            return std::nullopt;
        }

        if (std::regex_match(input.value(), inputRegex))
        {
            return input.value();
        }

        Utils::printWrongMsgNLine(lng->getText(wrongInput.data()));
    }
}

void Konbini::removeProductFromCart() const
{
    if (cart->isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(lng->getText("EMP_CART"));
        return;
    }

    while (true)
    {
        const auto input{getUserProductId()};

        if (!input.has_value())
        {
            return;
        }
        if (cart->isItemIdInCart(input.value()))
        {
            products->updateStoreAfterCartItemRemoved(input.value(), cart->getCartItemQnt(input.value()));
            cart->removeCartItem(input.value());
            Utils::printSuccessMsg(lng->getText("ITM_REMV"));
            return;
        }
        Utils::printWrongMsgNLine(lng->getText("NOT_IN_C"));
    }
}

std::optional<std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)>>
Konbini::getnewAcc(const std::string_view accType) const
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

        if (i == static_cast<size_t>(Accounts::AccInfo::Name))
        {
            Utils::lowerString(input.value());
        }

        if (i == static_cast<size_t>(Accounts::AccInfo::Email))
        {
            Utils::lowerString(input.value());
            if (accounts->isAccExists(input.value()))
            {
                --i;
                Utils::printWrongMsgNLine(lng->getText("EMAIL_EXST"));
                continue;
            }
        }

        newAcc[i] = input.value();
    }
    newAcc[static_cast<size_t>(Accounts::AccInfo::AccType)] = static_cast<std::string>(accType);
    return newAcc;
}

void Konbini::registerNew(const std::string_view accType) const
{
    if (const auto newAcc{getnewAcc(accType)}; newAcc.has_value())
    {
        accounts->addAccToVar(newAcc.value());
        accounts->addAccToFile(newAcc.value());
        Utils::printSuccessMsg(lng->getText("ACC_CREATED"));
    }
}

void Konbini::remindPassword() const
{
    std::array<std::string, 2> acc;

    while (true)
    {
        for (size_t i{}; i < 2; ++i)
        {
            auto input{getOptionalInput(lng->getText(inputMsgs[i]))};

            if (!input.has_value())
            {
                return;
            }
            Utils::lowerString(input.value());
            acc[i] = input.value();
        }

        if (accounts->isAccExists(acc[static_cast<size_t>(Accounts::AccInfo::Email)]) &&
            accounts->isCorrectNameEmail(acc[static_cast<size_t>(Accounts::AccInfo::Email)],
                                         acc[static_cast<size_t>(Accounts::AccInfo::Name)]))
        {
            KonbiniUI::printPassword(lng->getText("YOUR_PASS"),
                                     accounts->getAccPassword(acc[static_cast<size_t>(Accounts::AccInfo::Email)]));
            return;
        }

        Utils::printWrongMsgNLine(lng->getText("WRN_NAME_EMAIL"));
    }
}

void Konbini::addItemToCart() const
{
    if (products->isStoreEmpty())
    {
        Utils::printWarningMsgNLine(lng->getText("STORE_EMPT"));
        return;
    }

    while (true)
    {
        const auto productId{getUserProductId()};

        if (!productId.has_value())
        {
            return;
        }

        if (!products->isItemExistInStore(productId.value()))
        {
            Utils::printWrongMsgNLine(lng->getText("WRN_PRD"));
            continue;
        }

        const std::string prdName{products->getProductName(productId.value())};

        const auto quantity{getUserQnt(productId.value())};

        if (!quantity.has_value())
        {
            return;
        }

        const ProductData newProduct{
            .name = prdName,
            .price = products->getProductPrice(productId.value()) * quantity.value(),
            .qnt = quantity.value(),
        };
        cart->addProductToCart(productId.value(), newProduct);
        products->updateStoreAfterAddingToCart(productId.value(), quantity.value());
        Utils::printSuccessMsg(lng->getText("PRD_ADD_CART"));
        return;
    }
}

std::optional<std::string> Konbini::getUserProductId() const
{
    while (true)
    {
        auto input{getOptionalInput(lng->getText("PRD_NAME"))};

        if (!input.has_value())
        {
            return std::nullopt;
        }
        if (const auto id{isValidUserProduct(input.value())}; id.has_value())
        {
            return id.value();
        }
        Utils::printWrongMsgNLine(lng->getText("WRN_PRD"));
    }
}

std::optional<std::string> Konbini::isValidUserProduct(std::string& product) const
{
    Utils::lowerString(product);

    if (const auto id{products->isProductExistsInDatabase(product)}; id.has_value())
    {
        return id.value();
    }

    return std::nullopt;
}

std::optional<int> Konbini::getUserQnt(const std::string& id) const
{
    while (true)
    {
        auto input{getOptionalInput(lng->getText("PRD_QNT"))};

        if (!input.has_value())
        {
            return std::nullopt;
        }

        if (isValidUserQnt(id, input.value()))
        {
            return stoi(input.value());
        }

        Utils::printWrongMsgNLine(lng->getText("WRN_QNT"));
    }
}

bool Konbini::isValidUserQnt(const std::string& id, const std::string& userQnt) const
{
    const int productQnt{products->getProductQnt(id)};
    return Utils::isInt(userQnt) && stoi(userQnt) > 0 && productQnt >= stoi(userQnt);
}

void Konbini::finalizePurchase() const
{
    if (cart->isCartEmpty())
    {
        KonbiniUI::printCartIsEmpty(lng->getText("EMP_CART"));
        return;
    }

    products->updateFilesAfterStoreUpdate();
    cart->cleanCart();
    Utils::printSuccessMsg(lng->getText("THNK_SHP"));
}

void Konbini::changeLanguage() const
{
    lng->clearDict();
    lng->changeLang();
    products->setCurrencyAndActualProductsLang(lng->getUserLang());
    lng->saveUserLangToFile();
    lng->loadDict(lng->getUserLang());
    cart->reloadCartAfterLangChange(products->getProductList());
    lng->loadMenus();
    lng->loadLoginMsgs();
    Utils::printSuccessMsg(lng->getText("LNG_CHN"));
}

std::optional<std::string> Konbini::login() const
{
    std::array<std::string, 2> acc;
    size_t i{};
    while (true)
    {
        auto input{getOptionalInput(lng->getLoginMsg(i + 1))};

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
            Utils::printWrongMsgNLine(lng->getText("WRN_LOGIN"));
        }
        else
        {
            ++i;
        }
    }
}

bool Konbini::isLoginOk(const std::string& email, const std::string& pass) const
{
    return accounts->isAccExists(email) && accounts->isEmailMatchingPassword(email, pass);
}

void Konbini::executeUserMenu() const
{
    while (true)
    {
        KonbiniUI::printMenu(lng->getUserMenu());
        if (const auto userCommand{getUserCommand()}; userCommand.has_value())
        {
            if (!executeLoggedUserTask(userCommand.value()))
            {
                return;
            }
        }
    }
}

bool Konbini::executeLoggedUserTask(int command) const
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
        products->updateStoreAfterDeletingAccount(cart->getCartItems());
        accounts->deleteAccFromVar();
        accounts->updateAccsFile();
        Utils::printSuccessMsg(lng->getText("ACC_DEL"));
        return false;
    case LoggedUserMenuOPTS::Logout:
        Utils::printWarningMsgNLine(lng->getText("LOG_OUT"));
        return false;
    case LoggedUserMenuOPTS::Exit:
        Utils::printSuccessMsg(lng->getText("BYE"));
        std::exit(EXIT_SUCCESS);
    default:
        Utils::printWrongMsgNLine(lng->getText("WRN_M_COMMAND"));
    }
    Utils::printMsgNLine("");
    return true;
}

void Konbini::showAccountDetails() const
{
    const auto acc{accounts->getLoggedAcc()};
    for (size_t i{}; i < acc.size(); ++i)
    {
        Utils::printColorfullMsg(COLORS::PURPLE, lng->getText("S_ACC_" + std::to_string(i)));
        Utils::printColonWSpace();
        Utils::printMsgNLine(acc[i]);
    }
}

void Konbini::changeEmail() const
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

        if (!accounts->isAccExists(input.value()))
        {
            accounts->setNewEmail(input.value());
            accounts->updateAccsFile();
            Utils::printSuccessMsg(lng->getText("EMAIL_CHANGED"));
            return;
        }

        Utils::printWrongMsgNLine(lng->getText("EMAIL_EXST"));
    }
}

void Konbini::changePassword() const
{
    const auto input{
        getOptionalCorrectInput("NEW_PASS", registerRegexes[static_cast<size_t>(Accounts::AccInfo::Pass)], "PSWD_ERR")};

    if (!input.has_value())
    {
        return;
    }

    accounts->setNewPassword(input.value());
    accounts->updateAccsFile();
    Utils::printSuccessMsg(lng->getText("NEW_PASS_CHNGD"));
}

void Konbini::executeAdminMenu() const
{
    while (true)
    {
        KonbiniUI::printMenu(lng->getAdminMenu());
        if (const auto userCommand{getUserCommand()}; userCommand.has_value())
        {
            if (!executeLoggedAdminTask(userCommand.value()))
            {
                return;
            }
        }
    }
}

bool Konbini::executeLoggedAdminTask(int command) const
{
    switch (static_cast<LoggedAdminMenuOPTS>(command))
    {
    case LoggedAdminMenuOPTS::ShowAccountDetails:
        showAccountDetails();
        break;
    case LoggedAdminMenuOPTS::ChangeEmail:
        changeEmail();
        accounts->updateAccsFile();
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
        addNewProductToStore();
        break;
    case LoggedAdminMenuOPTS::ChangeStoreProductQuantity:
        changeStoreProductQuantity();
        break;
    case LoggedAdminMenuOPTS::RemoveProductFromTheStore:
        removeProductFromStore();
        break;
    case LoggedAdminMenuOPTS::ChangelanguageToJapanese:
        changeLanguage();
        break;
    case LoggedAdminMenuOPTS::DeleteAccount:
        products->updateStoreAfterDeletingAccount(cart->getCartItems());
        accounts->deleteAccFromVar();
        accounts->updateAccsFile();
        Utils::printSuccessMsg(lng->getText("ACC_DEL"));
        return false;
    case LoggedAdminMenuOPTS::Logout:
        Utils::printWarningMsgNLine(lng->getText("LOG_OUT"));
        return false;
    case LoggedAdminMenuOPTS::Exit:
        Utils::printSuccessMsg(lng->getText("BYE"));
        std::exit(EXIT_SUCCESS);
    default:
        Utils::printWrongMsgNLine(lng->getText("WRN_M_COMMAND"));
    }
    Utils::printMsgNLine("");

    return true;
}

void Konbini::addNewProductToStore() const
{
    std::variant<std::string, int, double> newPrd;
    const std::array<std::function<newProductInputVariant()>, 3> inputFuncs{[this]
                                                                            {
                                                                                return getNewProductName();
                                                                            },
                                                                            [this]
                                                                            {
                                                                                return getNewProductQnt();
                                                                            },
                                                                            [this]
                                                                            {
                                                                                return getNewPoductPrice();
                                                                            }};
    std::array<newProductInputVariant, 3> newProductInfo;

    for (size_t i{}; i < 3; ++i)
    {
        auto input{inputFuncs[i]()};

        if (std::holds_alternative<std::monostate>(input))
        {
            return;
        }
        newProductInfo[i] = input;
    }
    ProductData newPrdData;
    newPrdData.name = std::get<std::string>(newProductInfo[0]);
    newPrdData.qnt = std::get<int>(newProductInfo[1]);
    newPrdData.price = std::get<double>(newProductInfo[2]);
    products->addNewProductToDatabase(newPrdData);
    Utils::printSuccessMsg(lng->getText("PRD_ADD_ST"));
}

newProductInputVariant Konbini::getNewProductName() const
{
    std::string enJPprdName;
    const std::array<std::string, 2> inputMsg{"EN_PRD_NAME", "JP_PRD_NAME"};
    for (size_t i{}; i < 2; ++i)
    {
        while (true)
        {
            auto input{getOptionalInput(lng->getText(inputMsg[i]))};

            if (!input.has_value())
            {
                return std::monostate{};
            }

            if (!std::regex_match(input.value(), registerRegexes[static_cast<size_t>(Accounts::AccInfo::Name)]))
            {
                Utils::printWrongMsgNLine(lng->getText("WRN_PRD_NAME"));
                continue;
            }

            Utils::lowerString(input.value());

            if (products->isProductExistsInDatabase(input.value()))
            {
                Utils::printWrongMsgNLine(lng->getText("PRD_AL_EXT"));
                continue;
            }

            enJPprdName += input.value();
            if (i == 0)
            {
                enJPprdName += ';';
            }
            break;
        }
    }
    return enJPprdName;
}

newProductInputVariant Konbini::getNewProductQnt() const
{
    auto input{getOptionalPositiveInt(lng->getText("PRD_QNT"))};

    if (!input.has_value())
    {
        return std::monostate{};
    }

    return input.value();
}

newProductInputVariant Konbini::getNewPoductPrice() const
{

    auto input{getOptionalPositiveDouble(lng->getText("NEW_PRD_PRICE"))};

    if (!input.has_value())
    {
        return std::monostate{};
    }

    return input.value();
}

void Konbini::removeProductFromStore() const
{
    const auto productId{getUserProductId()};

    if (!productId.has_value())
    {
        return;
    }

    if (products->isItemExistInStore(productId.value()))
    {
        products->deleteProductFromStore(productId.value());
    }
    if (cart->isItemIdInCart(productId.value()))
    {
        cart->removeCartItem(productId.value());
    }

    Utils::printSuccessMsg(lng->getText("PRD_REM_ST"));
}

void Konbini::changeStoreProductQuantity() const
{
    const auto productId{getUserProductId()};

    if (!productId.has_value())
    {
        return;
    }

    const auto quantity{getOptionalPositiveInt(lng->getText("PRD_N_QNT"))};

    if (!quantity.has_value())
    {
        return;
    }

    products->updateProductQuantity(productId.value(), quantity.value());
    Utils::printSuccessMsg(lng->getText("QNT_CHN"));
}