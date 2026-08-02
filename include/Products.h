#pragma once
#include "Utils.h"
#include <array>
#include <map>
#include <unordered_map>

class Products
{
    enum class ProductsLang : std::uint8_t
    {
        EN = 0,
        JP = 1
    };

  public:
    explicit Products(const std::string& finalLang);

    void setCurrencyAndActualProductsLang(const std::string& finalLang);

    void changeToOtherLangStore();

    [[nodiscard]] bool isStoreEmpty() const;

    [[nodiscard]] const std::unordered_map<std::string, ProductData>& getProducts();

    [[nodiscard]] std::string getCurrency();

    [[nodiscard]] std::string getProductName(const std::string& id);

    [[nodiscard]] std::optional<std::string> isProductExistsInDatabase(const std::string& name);

    [[nodiscard]] bool isItemExistInStore(const std::string &id) const;

    [[nodiscard]] int getProductQnt(const std::string& id) const;

    [[nodiscard]] double getProductPrice(const std::string& id) const;

    void updateStoreAfterAddingToCart(const std::string& id, int qnt);

    void updateStoreAfterQntChange(const std::string& id, int newQnt, int cartItemQnt);

    void updateFilesAfterStoreUpdate();

    [[nodiscard]] const std::map<std::string, ProductData>& getProductList();

    void updateStoreAfterCartItemRemoved(const std::string& id, int&& qnt);

    void updateStoreAfterDeletingAccount(const std::unordered_map<std::string, ProductData>& cartItems);

    void addNewProductToDatabase(const ProductData& prdData);
    static constexpr double jpCurrency{163.67};

    void deleteProductFromStore(const std::string& id);

    void updateProductQuantity(const std::string& id, int newQnt);

  private:
    inline static const std::array<std::filesystem::path, Utils::numofLangs> productsPath{
        DATA_DIR "products_en.txt",
        DATA_DIR "products_jp.txt",
    };
    std::size_t actualProductsLang{};
    std::array<std::map<std::string, ProductData>, Utils::numofLangs> productsList;
    std::array<std::unordered_map<std::string, ProductData>, Utils::numofLangs> productsByLang;
    inline static const std::array<std::string, Utils::numofLangs> currencies{"$", "円"};
    std::string actualCurrency;
    ProductsLang actualProductsLangEnumType{};

    void loadProducts();
};