#pragma once
#include "Utils.h"
#include <map>
#include <unordered_map>

class Cart
{
  public:
    [[nodiscard]] bool isCartEmpty() const;

    [[nodiscard]] std::unordered_map<std::string, ProductData> getCartItems();

    [[nodiscard]] bool isItemInCart(const std::string& id) const;

    [[nodiscard]] int getCartItemQnt(const std::string& id) const;

    void setNewProductQnty(const std::string& id, int newQnt);

    void cleanCart();

    void addProductToCart(const std::string& id, const ProductData& newProduct);

    void reloadCartAfterLangChange(const std::map<std::string, ProductData>& allItemsList);

    [[nodiscard]] std::array<double, 2> getCartSummaries(bool isUser = false);

    void removeCartItem(const std::string& id);

  private:
    std::unordered_map<std::string, ProductData> cartItems;
};