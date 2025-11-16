#include "CheckoutFacade.h"
#include <iostream>

CheckoutFacade::CheckoutFacade()
    : m_paymentSystem(std::make_unique<PaymentSystem>()),
      m_inventorySystem(std::make_unique<InventorySystem>()),
      m_shippingService(std::make_unique<ShippingService>()) {
}

bool CheckoutFacade::placeOrder(ShoppingCart& cart,
                                const std::string& address,
                                const std::string& creditCard) {

    std::cout << "[CheckoutFacade] Starting checkout process..." << std::endl;

    // 1. Check inventory for all items
    for (const auto& item : cart.getItems()) {
        if (!m_inventorySystem->checkStock(item->getSKU(), 1)) {
            std::cout << "[CheckoutFacade] Order failed: Item "
                      << item->getName() << " is out of stock." << std::endl;
            return false;
        }
    }
    std::cout << "[CheckoutFacade] All items are in stock." << std::endl;

    // 2. Process payment
    double finalTotal = cart.getTotalAfterDiscount();
    if (!m_paymentSystem->processPayment(finalTotal, creditCard)) {
        std::cout << "[CheckoutFacade] Order failed: Payment was declined." << std::endl;
        return false;
    }
    std::cout << "[CheckoutFacade] Payment successful." << std::endl;

    // 3. Reserve stock
    for (const auto& item : cart.getItems()) {
        m_inventorySystem->reserveStock(item->getSKU(), 1);
    }

    // 4. Arrange shipping
    m_shippingService->arrangeShipping(address);
    std::cout << "[CheckoutFacade] Shipping arranged." << std::endl;

    std::cout << "[CheckoutFacade] Checkout process completed successfully!" << std::endl;
    return true;
}