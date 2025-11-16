#pragma once

#include <string>
#include <iostream>

/**
 * @brief (Facade Subsystem) Mock Payment Processing System.
 */
class PaymentSystem {
public:
    bool processPayment(double amount, const std::string& creditCard) {
        std::cout << "  [PaymentSystem] Processing payment of $" << amount
                  << " with card " << creditCard << std::endl;
        // In a real system, would connect to Stripe, PayPal, etc.
        if (amount > 0) {
            std::cout << "  [PaymentSystem] Payment Approved." << std::endl;
            return true;
        }
        std::cout << "  [PaymentSystem] Payment Declined." << std::endl;
        return false;
    }
};

/**
 * @brief (Facade Subsystem) Mock Inventory Management System.
 */
class InventorySystem {
public:
    bool checkStock(const std::string& sku, int quantity) {
        std::cout << "  [InventorySystem] Checking stock for SKU: " << sku
                  << ", Quantity: " << quantity << std::endl;
        // Mock logic: all items are in stock
        return true;
    }

    void reserveStock(const std::string& sku, int quantity) {
         std::cout << "  [InventorySystem] Reserving " << quantity
                   << " of " << sku << std::endl;
    }
};

/**
 * @brief (Facade Subsystem) Mock Shipping Service.
 */
class ShippingService {
public:
    void arrangeShipping(const std::string& address) {
        std::cout << "  [ShippingService] Arranging shipment to: "
                  << address << std::endl;
        std::cout << "  [ShippingService] Shipping label printed." << std::endl;
    }
};