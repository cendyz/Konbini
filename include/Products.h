#pragma once
#include <unordered_map>
#include <string>
#include <filesystem>
#include "Utils.h"

class Products
{
    enum class CartType : std::uint8_t
    {
        EN = 0,
        JP,
    };

public:
    explicit Products(const std::string& finalLang);

    static void setCurrencyAndActualCart(const std::string& finalLang);

    static void changeToNewCart();

    [[nodiscard]] static bool isStoreEmpty();

    [[nodiscard]] static std::unordered_map<std::string, ProductData> getProducts();

    [[nodiscard]] static std::string_view getCurrency();

    [[nodiscard]] static std::string getProductName(const std::string& id);

    [[nodiscard]] static std::optional<std::string> isProductExists(const std::string& str);

    [[nodiscard]] static int getProductQnt(const std::string& id);

    [[nodiscard]] static double getProductPrice(const std::string& id);

    static void updateStoreAfterAddingToCart(const std::string& id, int qnt);

    static void clearProducts();

    static void updateFilesAfterPurchase();

private:
    inline static std::array<std::filesystem::path, Utils::numofLangs> cartsPath{DATA_DIR"products_en.txt",
        DATA_DIR "products_jp.txt"};
    inline static std::size_t actualCart{};
    inline static std::array<std::unordered_map<std::string, ProductData>, Utils::numofLangs> carts;
    inline static const std::array<std::string, Utils::numofLangs> currencies{"$", "円"};
    inline static std::string actualCurrency;
    inline static CartType actualCartEnumType;

    static void loadProducts();
};
