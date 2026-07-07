#include "Products.h"
#include <fstream>
#include <istream>

Products::Products(const std::string &finalLang) {
  productsPath += finalLang + ".txt";
  std::cout << "to jest final lang: " <<finalLang << '\n';
  if (finalLang == "JP") {
    currency = "円";
  } else {
    currency = "$";
  }
  loadProducts();
}

bool Products::isStoreEmpty() { return products.empty(); }

void Products::loadProducts() {
  std::ifstream filePath{productsPath};
  std::string line, id, name, price, quantity;

  while (getline(filePath, line)) {
    std::stringstream ss(line);

    getline(ss, id, ';');
    getline(ss, name, ';');
    getline(ss, price, ';');
    getline(ss, quantity, ';');

    ProductData newProduct{
        .name = name, .price = stod(price), .qnt = stoi(quantity)};
    products.try_emplace(id, std::move(newProduct));
  }
}

std::unordered_map<std::string, ProductData> &Products::getProducts() {
  return products;
}

std::string_view Products::getCurrency() { return currency; }

std::string Products::getProductName(const std::string &id) {
  return products[id].name;
}

std::optional<std::string> Products::isProductExists(const std::string &str) {
  for (const auto &[id, data] : products) {
    if (data.name == str) {
      return id;
    }
  }
  return std::nullopt;
}

double Products::getProductPrice(const std::string &id) {
  return products[id].price;
}

int Products::getProductQnt(const std::string &id) { return products[id].qnt; }