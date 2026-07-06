#pragma once
#include <unordered_map>
#include <string>
#include <filesystem>
#include "Utils.h"


class Products {
public:
    explicit Products(const std::string &finalLang);

    [[nodiscard]] static bool isStoreEmpty();

    [[nodiscard]] static std::unordered_map<std::string, ProductData > &getProducts();

    [[nodiscard]] static std::string_view getCurrency();

    [[nodiscard]] static bool isProductExists(const std::string &str);

    [[nodiscard]] static bool getProductQnt(const std::string &str);

private:
    inline static std::filesystem::path productsPath{DATA_DIR "products"};
    inline static std::unordered_map<std::string, ProductData > products;
    inline static std::string currency;

    static void loadProducts() ;
};
