#pragma once
#include "Utils.h"
#include <array>
#include <unordered_map>

class Products
{
    enum class ProductsLang : std::uint8_t
    {
        EN = 0,
        JP,
    };

  public:
    explicit Products(const std::string& finalLang);

    static void setCurrencyAndActualProductsLang(const std::string& finalLang);

    static void changeToOtherLangStore();

    [[nodiscard]] static bool isStoreEmpty();

    [[nodiscard]] static std::unordered_map<std::string, ProductData> getProducts();

    [[nodiscard]] static std::string getCurrency();

    [[nodiscard]] static std::string getProductName(const std::string& id);

    [[nodiscard]] static std::optional<std::string> isProductExists(const std::string& str);

    [[nodiscard]] static int getProductQnt(const std::string& id);

    [[nodiscard]] static double getProductPrice(const std::string& id);

    static void updateStoreAfterAddingToCart(const std::string& id, int qnt);

    void static updateStoreAfterQntChange(const std::string& id, int newQnt, int cartItemQnt);

    static void updateFilesAfterPurchase();

    [[nodiscard]] static std::unordered_map<std::string, ProductData> getProductList();

    static void updateStoreAfterCartItemRemoved(const std::string& id, int && qnt);

    static void updateStoreAfterDeletingAccount(std::unordered_map<std::string, ProductData> &&cartItems);

  private:
    inline static std::array<std::filesystem::path, Utils::numofLangs> productsPath{
        DATA_DIR "products_en.txt",
        DATA_DIR "products_jp.txt",
    };
    inline static std::size_t actualProductsLang{};
    inline static std::array<std::unordered_map<std::string, ProductData>, Utils::numofLangs> productsList;
    inline static std::array<std::unordered_map<std::string, ProductData>, Utils::numofLangs> productsByLang;
    inline static const std::array<std::string, Utils::numofLangs> currencies{"$", "円"};
    inline static std::string actualCurrency;
    inline static ProductsLang actualProductsLangEnumType;

    static void loadProducts();
};