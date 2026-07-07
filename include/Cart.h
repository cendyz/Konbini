#pragma once
#include <string>
#include <unordered_map>
#include "Utils.h"

class Cart {
public:
  Cart() = default;

  [[nodiscard]] static bool isCartEmpty();

  [[nodiscard]] static std::unordered_map<std::string, ProductData> getCartItems();

  static void addProductToCart(std::string id, ProductData newProduct);

private:
  inline static std::unordered_map<std::string, ProductData> cartItems;
};
