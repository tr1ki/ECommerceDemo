#pragma once

#include "ShoppingCart.h"
#include "Subsystems.h"
#include <string>
#include <memory>

/**
 * @brief (Facade Pattern) The Facade class.
 * Provides a simple, unified interface to a complex set of subsystems
 * (Payment, Inventory, Shipping) required for the checkout process.
 */
class CheckoutFacade {
public:
    CheckoutFacade();

    // The simplified interface method
    bool placeOrder(ShoppingCart& cart,
                    const std::string& address,
                    const std::string& creditCard);

private:
    // The complex subsystems hidden by the facade
    std::unique_ptr<PaymentSystem> m_paymentSystem;
    std::unique_ptr<InventorySystem> m_inventorySystem;
    std::unique_ptr<ShippingService> m_shippingService;
};