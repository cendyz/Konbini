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

    [[nodiscard]] static std::string getProductName(const std::string &id);

    [[nodiscard]] static std::optional<std::string> isProductExists(const std::string &str);

    [[nodiscard]] static int getProductQnt(const std::string &id);

    [[nodiscard]] static double getProductPrice(const std::string &id);

private:
    inline static std::filesystem::path productsPath{DATA_DIR "products"};
    inline static std::unordered_map<std::string, ProductData > products;
    inline static std::string currency;

    static void loadProducts() ;
};
