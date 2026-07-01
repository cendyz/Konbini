#include "Cart.h"
#include <unordered_map>

bool Cart::isCartEmpty() { return cartItems.empty(); }

auto Cart::getCartItems() { return cartItems; }
