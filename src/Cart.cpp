#include "Cart.h"
#include <unordered_map>

bool Cart::isCartEmpty() { return cartItems.empty(); }

std::unordered_map<std::string, ProductData> Cart::getCartItems() {
  return cartItems;
}

void Cart::addProductToCart(std::string id, ProductData newProduct) {
  cartItems.try_emplace(std::move(id), std::move(newProduct));
}