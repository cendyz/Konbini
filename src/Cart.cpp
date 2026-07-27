#include "Cart.h"
#include <ranges>

bool Cart::isCartEmpty()
{
    return cartItems.empty();
}

std::unordered_map<std::string, ProductData> Cart::getCartItems()
{
    return cartItems;
}

bool Cart::isItemInCart(const std::string& id)
{
    return cartItems.contains(id);
}

int Cart::getCartItemQnt(const std::string& id)
{
    return cartItems[id].qnt;
}

void Cart::addProductToCart(const std::string& id, const ProductData& newProduct)
{
    if (cartItems.contains(id))
    {
        cartItems[id].qnt += newProduct.qnt;
        cartItems[id].price += newProduct.price;
    }
    else
    {
        cartItems.try_emplace(id, newProduct);
    }
}

void Cart::reloadCartAfterLangChange(const std::map<std::string, ProductData>& allItemsList)
{
    for (const std::string& fst : cartItems | std::views::keys)
    {
        cartItems[fst].name = allItemsList.at(fst).name;
        cartItems[fst].price = allItemsList.at(fst).price * cartItems[fst].qnt;
    }
}

std::array<double, 2> Cart::getCartSummaries(const bool isUser)
{
    std::array<double, 2> cartSummaries{};
    double summary{};
    for (const auto& prd : cartItems | std::views::values)
    {
        summary += prd.price;
    }
    cartSummaries[0] = summary;
    cartSummaries[1] = 0;
    if (isUser)
    {
        cartSummaries[1] = summary - (10 * summary / 100);
    }
    return cartSummaries;
}

void Cart::cleanCart()
{
    cartItems.clear();
}

void Cart::setNewProductQnty(const std::string& id, const int newQnt)
{
    cartItems[id].price = (cartItems[id].price / cartItems[id].qnt) * newQnt;
    cartItems[id].qnt = newQnt;
}

void Cart::removeCartItem(const std::string& id)
{
    cartItems.erase(id);
}