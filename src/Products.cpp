#include "Products.h"
#include <fstream>
#include <istream>

Products::Products(const std::string &finalLang) {
    productsPath += finalLang + ".txt";

    if (finalLang == "jp") {
        currency = "円";
    } else {
        currency = "$";
    }
    loadProducts();
}

bool Products::isStoreEmpty() {
    return products.empty();
}

void Products::loadProducts() {
    std::ifstream filePath{productsPath};
    std::string line, id, name, price, quantity;

    while (getline(filePath, line)) {
        std::stringstream ss(line);

        getline(ss, id, ';');
        getline(ss, name, ';');
        getline(ss, price, ';');
        getline(ss, quantity, ';');

        products.try_emplace(id);
        products[id][static_cast<int>(Product::Name)] = name;
        products[id][static_cast<int>(Product::Price)] = price;
        products[id][static_cast<int>(Product::Quantity)] = quantity;
    }
}

std::unordered_map<std::string, std::array<std::string, 3>> &Products::getProducts() {
    return products;
}

std::string_view Products::getCurrency() {
    return currency;
}
