#pragma once
#include <unordered_map>
#include <array>
#include <string>

class Products {
public:
    Products() = default;

    [[nodiscard]] bool isStoreEmpty() const;
private:
    std::unordered_map<std::string, std::array<std::string, 3>> items;
};