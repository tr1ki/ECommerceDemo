#include "ProductFactory.h"

// Factory Method implementation for DigitalProduct
std::unique_ptr<IProduct> DigitalProductFactory::createProduct() const {
    return std::make_unique<DigitalProduct>(
        "SW-001", "Basic Software License", 49.99, "http://example.com/download"
    );
}

// Factory Method implementation for PhysicalProduct
std::unique_ptr<IProduct> PhysicalProductFactory::createProduct() const {
    // This factory creates a "default" physical product using the builder
    return ProductBuilder("BK-001", "Default Book")
        .setPrice(19.99)
        .setWeight(0.5)
        .build();
}