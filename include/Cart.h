#pragma once
import std;
#include "Utils.h"

class Cart
{
public:
    Cart() = default;

    [[nodiscard]] static bool isCartEmpty();

    [[nodiscard]] static std::unordered_map<std::string, ProductData> getCartItems();

    static void cleanCart();

    static void addProductToCart(std::string id, const ProductData& newProduct);

    static void reloadCartAfterLangChange(
        const std::unordered_map<std::string, ProductData>& allItemsList);

    [[nodiscard]] static std::array<double, 2> getCartSummaries(bool isUser = false);

private:
    inline static std::unordered_map<std::string, ProductData> cartItems;
};