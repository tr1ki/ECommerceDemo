#pragma once

#include <string>
#include <iostream>

/**
 * @brief Interface for all products in the e-commerce system.
 * Defines the common contract for all items that can be added to a cart.
 */
class IProduct {
public:
    virtual ~IProduct() = default;
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
    virtual std::string getSKU() const = 0; // Stock Keeping Unit
    virtual void print() const {
        std::cout << "  - " << getName() << " (SKU: " << getSKU()
                  << ", Price: $" << getPrice() << ")" << std::endl;
    }
};