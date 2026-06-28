#pragma once
#include <unordered_map>
#include <array>
#include <string>
#include <filesystem>

class Products {
    enum class Product {
        Name = 0,
        Price,
        Quantity
    };

public:
    explicit Products(const std::string &finalLang);

    [[nodiscard]] static bool isStoreEmpty() ;

    [[nodiscard]] static std::unordered_map<std::string, std::array<std::string, 3>> &getProducts();

    [[nodiscard]] static std::string_view getCurrency() ;
private:
    std::filesystem::path productsPath{"data/products"};
    inline static std::unordered_map<std::string, std::array<std::string, 3>> products;
    inline static std::string currency;
    void loadProducts() const;
};