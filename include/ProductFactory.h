#pragma once

#include "IProduct.h"
#include "ProductBuilder.h"
#include <memory>
#include <string>

// --- Concrete Products ---

/**
 * @brief Concrete implementation of a physical product.
 * Its construction is complex, so we use a Builder.
 */
class PhysicalProduct : public IProduct {
public:
    // Builder is a friend to access the private constructor
    friend class ProductBuilder;

    std::string getName() const override { return m_name; }
    double getPrice() const override { return m_price; }
    std::string getSKU() const override { return m_sku; }

private:
    // Private constructor to enforce creation via Builder
    PhysicalProduct(const std::string& sku, const std::string& name, double price,
                    const std::string& description, double weight)
        : m_sku(sku), m_name(name), m_price(price),
          m_description(description), m_weight(weight) {}

    std::string m_sku;
    std::string m_name;
    double m_price;
    std::string m_description;
    double m_weight;
};


/**
 * @brief Concrete implementation of a digital product.
 */
class DigitalProduct : public IProduct {
public:
    DigitalProduct(std::string sku, std::string name, double price, std::string downloadUrl)
        : m_sku(sku), m_name(name), m_price(price), m_downloadUrl(downloadUrl) {}

    std::string getName() const override { return m_name; }
    double getPrice() const override { return m_price; }
    std::string getSKU() const override { return m_sku; }

private:
    std::string m_sku;
    std::string m_name;
    double m_price;
    std::string m_downloadUrl;
};

// --- Factory ---

/**
 * @brief (Factory Method Pattern) The Creator interface.
 * Declares the factory method that returns an IProduct object.
 */
class ProductFactory {
public:
    virtual ~ProductFactory() = default;

    // The "Factory Method"
    virtual std::unique_ptr<IProduct> createProduct() const = 0;
};

/**
 * @brief Concrete Creator for basic digital products (e.g., software license).
 */
class DigitalProductFactory : public ProductFactory {
public:
    std::unique_ptr<IProduct> createProduct() const override;
};

/**
 * @brief Concrete Creator for basic physical products (e.g., a book).
 */
class PhysicalProductFactory : public ProductFactory {
public:
    std::unique_ptr<IProduct> createProduct() const override;
};