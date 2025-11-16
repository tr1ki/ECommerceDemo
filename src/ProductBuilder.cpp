#include "ProductBuilder.h"
#include "ProductFactory.h" // For PhysicalProduct definition

ProductBuilder::ProductBuilder(std::string sku, std::string name)
    : m_sku(std::move(sku)), m_name(std::move(name)) {}

ProductBuilder& ProductBuilder::setPrice(double price) {
    m_price = price;
    return *this;
}

ProductBuilder& ProductBuilder::setDescription(const std::string& description) {
    m_description = description;
    return *this;
}

ProductBuilder& ProductBuilder::setWeight(double weight) {
    m_weight = weight;
    return *this;
}

/**
 * @brief The final construction step.
 * Note: We use 'new' here because the constructor is private.
 * std::make_unique cannot access it. The unique_ptr will manage the memory.
 */
std::unique_ptr<PhysicalProduct> ProductBuilder::build() {
    return std::unique_ptr<PhysicalProduct>(
        new PhysicalProduct(m_sku, m_name, m_price, m_description, m_weight)
    );
}