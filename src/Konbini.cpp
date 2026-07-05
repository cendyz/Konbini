#include "Konbini.h"
#include "Cart.h"
#include "KonbiniUI.h"
#include "LanguageManager.h"
#include "Utils.h"
#include <memory>
#include <functional>
#include <windows.h>

Konbini::Konbini() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  lng = std::make_unique<LanguageManager>();
  ui = std::make_unique<KonbiniUI>();
  accounts = std::make_unique<Accounts>();
  cart = std::make_unique<Cart>();
}

void Konbini::run() {
  setSystemLang(userSelectingLanguage());
  products = std::make_unique<Products>(LanguageManager::getUserLang());
  while (true) {
    KonbiniUI::printMenu(LanguageManager::getMainMenu());
    KonbiniUI::printCanBackToMenu(LanguageManager::getText("M_BACK_OPT"));
    KonbiniUI::printWhatUserWantToDo(LanguageManager::getText("OPT_SELECT"));
    if (std::string input = Utils::getInput(); isUserCommandOk(input)) {
      if (!executeMainMenuTaks(stoi(input))) {
        return;
      }
    } else {
      KonbiniUI::printWrongExecuteCommand(
        LanguageManager::getText("WRN_M_COMMAND"));
    }
  }
}

std::string Konbini::userSelectingLanguage() {
  KonbiniUI::printUserCanChangeLNG();
  while (true) {
    KonbiniUI::printLngMenu();
    KonbiniUI::printChooseLangMsg();
    if (std::string val = Utils::getInput(); checkUserLang(val)) {
      if (auto lang{LanguageManager::isCorrectUserLang(stoi(val))};
        lang.has_value()) {
        return lang.value();
      }
    }
    KonbiniUI::printWrongLngInput();
  }
}

bool Konbini::checkUserLang(const std::string &input) {
  return !input.empty() && Utils::isInputANumber(input);
}

void Konbini::setSystemLang(const std::string &lang) {
  LanguageManager::loadDict(lang);
  LanguageManager::fullfillMainMenu(KonbiniUI::getMainMenuSize());
}

bool Konbini::executeMainMenuTaks(int userOption) {
  switch (static_cast<MainMenuOPTS>(userOption)) {
    case MainMenuOPTS::BrowseTheStore:
      browseTheStore();
    case MainMenuOPTS::CheckCart:
      break;
    case MainMenuOPTS::AddItemToCart:
      break;
    case MainMenuOPTS::FinalizePurchase:
      break;
    case MainMenuOPTS::Login:
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
    case MainMenuOPTS::Exit:
      KonbiniUI::printGoodbye(LanguageManager::getText("BYE"));
      return false;
    default:
      KonbiniUI::printWrongExecuteCommand(
        LanguageManager::getText("WRN_M_COMMAND"));
  }
  return true;
}

bool Konbini::isUserCommandOk(const std::string &input) {
  return !input.empty() &&
         std::ranges::all_of(input, [](const char c) { return isdigit(c); });
}

bool Konbini::returnToMenu(const std::string &input) {
  if (input == backToMenuKey) {
    Utils::printWarningMsg(LanguageManager::getText("MENU_BACK"));
    return true;
  }
  return false;
}

void Konbini::browseTheStore() {
  if (Products::isStoreEmpty()) {
    KonbiniUI::printStoreIsEmpty(LanguageManager::getText("STORE_EMPT"));
    return;
  }

  KonbiniUI::printStoreProducts(Products::getProducts(),
                                Products::getCurrency(),
                                LanguageManager::getText("QNT"));
}

void Konbini::checkCart() {
  if (Cart::isCartEmpty()) {
    return;
  }
}

std::optional<std::string> Konbini::getOptionalCorrectInput(const std::string &inputMsg, const std::regex &inputRegex,
                                                            const std::string &wrongInput) {
  while (true) {
    Utils::printMsgSpace(LanguageManager::getText(inputMsg));
    std::string input = Utils::getInput();

    if (returnToMenu(input)) {
      return std::nullopt;
    }

    if (std::regex_match(input, inputRegex)) {
      return input;
    }

    Utils::printWrongMsgNLine(LanguageManager::getText(wrongInput));
  }
}

std::optional<std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)> > Konbini::getnewAcc(
  const std::string_view accType) {
  std::array<std::string, static_cast<size_t>(Accounts::AccInfo::Size)> newAcc;

  for (size_t i{}; i < static_cast<size_t>(Accounts::AccInfo::Size) - 1; ++i) {
    const auto input{
      getOptionalCorrectInput(inputMsgs[i],
                              registerRegexes[i], wrongInputsMsgs[i])
    };
    if (!input.has_value()) {
      return std::nullopt;
    }
    newAcc[i] = input.value();
  }
  newAcc[static_cast<size_t>(Accounts::AccInfo::AccType)] = static_cast<std::string>(accType);
  return newAcc;
}

void Konbini::registerNew(const std::string_view accType) {
  if (const auto newAcc{getnewAcc(accType)}; newAcc.has_value()) {
    Accounts::addAccToDB(newAcc.value());
    KonbiniUI::printAccountCreated(LanguageManager::getText("ACC_CREATED"));
  }
}

void Konbini::remindPassword() {
  std::array<std::string, 2> acc;

  while (true) {
    for (size_t i{}; i < 2; ++i) {
      auto input{getOptionalInput(LanguageManager::getText(inputMsgs[i]))};

      if (!input.has_value()) {
        return;
      }
      acc[i] = input.value();
    }

    if (Accounts::isCorrectNameEmail(acc[static_cast<size_t>(Accounts::AccInfo::Email)],
                                     acc[static_cast<size_t>(Accounts::AccInfo::Name)])) {
      KonbiniUI::printPassword(LanguageManager::getText("YOUR_PASS"),
                               Accounts::getAccPassword(acc[static_cast<size_t>(Accounts::AccInfo::Email)]));
      return;
    }

    Utils::printWrongMsgNLine(LanguageManager::getText("WRN_NAME_EMAIL"));
  }
}

std::optional<std::string> Konbini::getOptionalInput(const std::string_view inputMsg) {
  std::string input;
  Utils::printMsgSpace(inputMsg);

  getline(std::cin, input);

  if (returnToMenu(input)) {
    return std::nullopt;
  }

  return input;
}
