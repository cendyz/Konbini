#include "Products.h"
#include <fstream>
#include <istream>

Products::Products(const std::string& finalLang)
{
    setCurrencyAndActualCart(finalLang);
}

void Products::setCurrencyAndActualCart(const std::string& finalLang)
{
    if (finalLang == "jp")
    {
        actualCartEnumType = CartType::JP;
    }
    else
    {
        actualCartEnumType = CartType::EN;
    }
    actualCurrency = currencies[static_cast<size_t>(actualCartEnumType)];
    actualCart = static_cast<size_t>(actualCartEnumType);
    loadProducts();
}

bool Products::isStoreEmpty()
{
    return carts[actualCart].empty();
}

void Products::loadProducts()
{
    std::string line, id, name, price, quantity;

    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        std::ifstream filePath{cartsPath[i]};
        while (getline(filePath, line))
        {
            std::stringstream ss(line);

            getline(ss, id, ';');
            getline(ss, name, ';');
            getline(ss, price, ';');
            getline(ss, quantity, ';');

            ProductData newProduct{
                .name = name, .price = stod(price), .qnt = stoi(quantity)
            };
            carts[i].try_emplace(id, std::move(newProduct));
        }
    }
}

std::unordered_map<std::string, ProductData> Products::getProducts()
{
    return carts[actualCart];
}

std::string_view Products::getCurrency()
{
    return actualCurrency;
}

std::string Products::getProductName(const std::string& id)
{
    return carts[actualCart][id].name;
}

std::optional<std::string> Products::isProductExists(const std::string& str)
{
    for (const auto& [id, data] : carts[actualCart])
    {
        if (data.name == str)
        {
            return id;
        }
    }
    return std::nullopt;
}

double Products::getProductPrice(const std::string& id)
{
    return carts[actualCart][id].price;
}

int Products::getProductQnt(const std::string& id)
{
    return carts[actualCart][id].qnt;
}


void Products::updateStoreAfterAddingToCart(const std::string& id, const int qnt)
{
    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        if (const int newQnt{carts[i][id].qnt - qnt}; newQnt == 0)
        {
            carts[i].erase(id);
        }
        else
        {
            carts[i][id].qnt = newQnt;
        }
    }
}


void Products::updateFilesAfterPurchase()
{
    const std::filesystem::path tempPath{DATA_DIR"temp.txt"};

    for (size_t i{}; i < Utils::numofLangs; ++i)
    {
        std::ofstream temp{tempPath};

        for (const auto& [id, data] : carts[i])
        {
            temp << id << ";" << data.name << ";" << data.price << ";" << data.qnt << '\n';
        }
        temp.close();

        std::filesystem::remove(cartsPath[i]);
        std::filesystem::rename(tempPath, cartsPath[i]);
    }
}

void Products::changeToNewCart()
{
    actualCartEnumType = actualCartEnumType == CartType::JP ? CartType::EN : CartType::JP;
    actualCart = static_cast<size_t>(actualCartEnumType);
}