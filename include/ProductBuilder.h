#pragma once

#include "IProduct.h"
#include <string>
#include <memory>

// Forward declaration
class PhysicalProduct;

/**
 * @brief (Builder Pattern) Concrete builder for creating complex PhysicalProduct objects.
 * This allows for step-by-step construction of a product with multiple
 * optional attributes.
 */
class ProductBuilder {
public:
    ProductBuilder(std::string sku, std::string name);

    ProductBuilder& setPrice(double price);
    ProductBuilder& setDescription(const std::string& description);
    ProductBuilder& setWeight(double weight);

    std::unique_ptr<PhysicalProduct> build();

private:
    std::string m_sku;
    std::string m_name;
    double m_price{0.0};
    std::string m_description;
    double m_weight{0.0};
};