#include "Cart.h"
#include <unordered_map>

bool Cart::isCartEmpty()
{
    return cartItems.empty();
}

std::unordered_map<std::string, ProductData> Cart::getCartItems()
{
    return cartItems;
}

void Cart::addProductToCart(std::string id, const ProductData& newProduct)
{
    cartItems.try_emplace(std::move(id), newProduct);
}

void Cart::reloadCartAfterLangChange(
    const std::unordered_map<std::string, ProductData>& allItemsList)
{
    for (const std::string& fst : cartItems | std::views::keys)
    {
        cartItems[fst].name = allItemsList.at(fst).name;
        cartItems[fst].price = allItemsList.at(fst).price * cartItems[fst].qnt;
    }
}

void Cart::cleanCart()
{
    cartItems.clear();
}