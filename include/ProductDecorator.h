#pragma once

#include "IProduct.h"
#include <memory>

/**
 * @brief (Decorator Pattern) The abstract Decorator class.
 * It implements the IProduct interface and holds a reference to the
 * IProduct it wraps.
 */
class ProductDecorator : public IProduct {
public:
    explicit ProductDecorator(std::unique_ptr<IProduct> product)
        : m_wrappedProduct(std::move(product)) {}

    // Delegate calls to the wrapped object by default
    std::string getName() const override {
        return m_wrappedProduct->getName();
    }
    double getPrice() const override {
        return m_wrappedProduct->getPrice();
    }
    std::string getSKU() const override {
        return m_wrappedProduct->getSKU();
    }

protected:
    std::unique_ptr<IProduct> m_wrappedProduct;
};

/**
 * @brief Concrete Decorator: Adds gift wrapping to a product.
 */
class GiftWrapDecorator : public ProductDecorator {
public:
    explicit GiftWrapDecorator(std::unique_ptr<IProduct> product)
        : ProductDecorator(std::move(product)) {}

    // Override methods to add new behavior
    std::string getName() const override {
        return m_wrappedProduct->getName() + " (Gift Wrapped)";
    }
    double getPrice() const override {
        return m_wrappedProduct->getPrice() + 5.00; // Gift wrap fee
    }
};

/**
 * @brief Concrete Decorator: Adds extended warranty.
 */
class ExtendedWarrantyDecorator : public ProductDecorator {
public:
    explicit ExtendedWarrantyDecorator(std::unique_ptr<IProduct> product)
        : ProductDecorator(std::move(product)) {}

    std::string getName() const override {
        return m_wrappedProduct->getName() + " (Ext. Warranty)";
    }
    double getPrice() const override {
        return m_wrappedProduct->getPrice() + 25.50; // Warranty fee
    }
};