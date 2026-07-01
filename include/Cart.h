#pragma once

#include <array>
#include <string>
#include <unordered_map>
#include <variant>

class Cart {
public:
  Cart() = default;

  [[nodiscard]] static bool isCartEmpty();

  [[nodiscard]] static auto getCartItems();

private:
  inline static std::unordered_map<
      std::string, std::array<std::variant<std::string, int, double>, 3>>
      cartItems;
};
