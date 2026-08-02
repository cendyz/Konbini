#include "Products.h"
#include "LanguageManager.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <ranges>

Products::Products(const std::string& finalLang)
{
    setCurrencyAndActualProductsLang(finalLang);
    loadProducts();
}

void Products::setCurrencyAndActualProductsLang(const std::string& finalLang)
{
    if (finalLang == "jp")
    {
        actualProductsLangEnumType = ProductsLang::JP;
    }
    else
    {
        actualProductsLangEnumType = ProductsLang::EN;
    }
    actualCurrency = currencies.at(static_cast<size_t>(actualProductsLangEnumType));
    actualProductsLang = static_cast<size_t>(actualProductsLangEnumType);
}

bool Products::isStoreEmpty() const
{
    return productsByLang.at(actualProductsLang).empty();
}

void Products::loadProducts()
{
    std::string line, id, name, price, quantity;

    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        std::ifstream filePath{productsPath[i]};
        while (getline(filePath, line))
        {
            std::stringstream ss(line);

            getline(ss, id, ';');
            getline(ss, name, ';');
            getline(ss, price, ';');
            getline(ss, quantity, ';');

            ProductData newProduct{
                .name = name,
                .price = stod(price),
                .qnt = stoi(quantity),
            };
            productsByLang[i].try_emplace(id, newProduct);
            productsList[i].try_emplace(id, std::move(newProduct));
        }
    }
}

const std::unordered_map<std::string, ProductData>& Products::getProducts()
{
    return productsByLang.at(actualProductsLang);
}

std::string Products::getCurrency()
{
    return actualCurrency;
}

std::string Products::getProductName(const std::string& id)
{
    return productsList[actualProductsLang].at(id).name;
}

std::optional<std::string> Products::isProductExistsInDatabase(const std::string& name)
{
    for (const auto& [id, data] : productsList.at(actualProductsLang))
    {
        if (data.name == name)
        {
            return id;
        }
    }
    return std::nullopt;
}

bool Products::isItemExistInStore(const std::string& id) const
{
    return productsByLang[actualProductsLang].contains(id);
}

double Products::getProductPrice(const std::string& id) const
{
    return productsByLang[actualProductsLang].at(id).price;
}

int Products::getProductQnt(const std::string& id) const
{
    if (!productsByLang[actualProductsLang].contains(id))
    {
        return 0;
    }
    return productsByLang[actualProductsLang].at(id).qnt;
}

void Products::updateStoreAfterAddingToCart(const std::string& id, const int qnt)
{
    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        if (const int newQnt{productsByLang[i].at(id).qnt - qnt}; newQnt == 0)
        {
            productsByLang[i].erase(id);
        }
        else
        {
            productsByLang[i].at(id).qnt = newQnt;
        }
    }
}

void Products::updateStoreAfterQntChange(const std::string& id, const int newQnt, const int cartItemQnt)
{
    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        if (!productsByLang[i].contains(id))
        {
            ProductData restored{productsList[i][id]};
            restored.qnt = newQnt;
            productsByLang[i].try_emplace(id, restored);
            continue;
        }

        if (newQnt < cartItemQnt)
        {
            productsByLang[i][id].qnt += cartItemQnt - newQnt;
        }
        else
        {
            if (const int storePrdQnt{productsByLang[i][id].qnt}; storePrdQnt - (newQnt - cartItemQnt) <= 0)
            {
                productsByLang[i].erase(id);
            }
            else
            {
                productsByLang[i][id].qnt -= newQnt - cartItemQnt;
            }
        }
    }
}

const std::map<std::string, ProductData>& Products::getProductList()
{
    return productsList.at(actualProductsLang);
}

void Products::updateFilesAfterStoreUpdate()
{
    const std::filesystem::path tempPath{DATA_DIR "temp.txt"};

    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        std::ofstream temp{tempPath};

        for (const auto& [id, data] : productsByLang[i])
        {
            temp << id << ";" << data.name << ";" << data.price << ";" << data.qnt << '\n';
        }
        temp.close();

        std::filesystem::remove(productsPath[i]);
        std::filesystem::rename(tempPath, productsPath[i]);
    }
}

void Products::changeToOtherLangStore()
{
    actualProductsLangEnumType = actualProductsLangEnumType == ProductsLang::JP ? ProductsLang::EN : ProductsLang::JP;
    actualProductsLang = static_cast<size_t>(actualProductsLangEnumType);
}

void Products::updateStoreAfterCartItemRemoved(const std::string& id, int&& qnt)
{
    for (size_t i{}; i < static_cast<size_t>(Utils::numofLangs); ++i)
    {
        if (!productsByLang[i].contains(id))
        {
            ProductData data{};
            data.name = productsList[i][id].name;
            data.price = productsList[i][id].price;
            data.qnt = qnt;

            productsByLang[i].try_emplace(id, data);
        }
        else
        {
            productsByLang[i][id].qnt += qnt;
        }
    }
}

void Products::updateStoreAfterDeletingAccount(const std::unordered_map<std::string, ProductData>& cartItems)
{
    for (const auto& [fst, snd] : cartItems)
    {
        updateStoreAfterQntChange(fst, 0, snd.qnt);
    }
}

void Products::addNewProductToDatabase(const ProductData& prdData)
{
    int newId{1};

    if (!productsList[0].empty())
    {
        newId = std::stoi(productsList[0].rbegin()->first) + 1;
    }
    std::string enName, jpName;
    std::stringstream ss(prdData.name);
    std::getline(ss, enName, ';');
    std::getline(ss, jpName, ';');
    ProductData enProduct{prdData};
    enProduct.name = enName;
    ProductData jpProduct{prdData};
    jpProduct.price = std::round(enProduct.price * jpCurrency);
    jpProduct.name = jpName;

    std::string strNewId{std::to_string(newId)};

    productsList[static_cast<size_t>(ActualLang::EN)].emplace(strNewId, enProduct);
    productsList[static_cast<size_t>(ActualLang::JP)].emplace(strNewId, jpProduct);
    productsByLang[static_cast<size_t>(ActualLang::JP)].emplace(strNewId, jpProduct);
    productsByLang[static_cast<size_t>(ActualLang::EN)].emplace(strNewId, enProduct);
    updateFilesAfterStoreUpdate();
}

void Products::deleteProductFromStore(const std::string& id)
{
    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        productsList[i].erase(id);
        productsByLang[i].erase(id);
    }
    updateFilesAfterStoreUpdate();
}

void Products::updateProductQuantity(const std::string& id, const int newQnt)
{
    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        productsList[i].at(id).qnt = newQnt;
        productsByLang[i].at(id).qnt = newQnt;
    }
    updateFilesAfterStoreUpdate();
}