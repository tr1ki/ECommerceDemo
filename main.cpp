// ECommerceProject/main.cpp

#include <iostream>
#include <iomanip> // For setting precision

#include "ShoppingCart.h"
#include "ProductFactory.h"
#include "ProductBuilder.h"
#include "ProductDecorator.h"
#include "DiscountStrategy.h"
#include "CheckoutFacade.h"

/**
 * @brief (Observer Pattern) A concrete observer that simulates a UI component.
 * It attaches to a ShoppingCart and prints its contents whenever the
 * cart is updated (notified).
 */
class CartUI : public IObserver {
public:
    explicit CartUI(ShoppingCart& cart) : m_cart(cart) {
        m_cart.attach(this); // Attach itself to the subject
    }

    ~CartUI() {
        m_cart.detach(this); // Detach itself on destruction
    }

    // The update method called by the Subject (ShoppingCart)
    void update() override {
        std::cout << "\n--- CART UI UPDATED ---" << std::endl;
        const auto& items = m_cart.getItems();
        if (items.empty()) {
            std::cout << "Cart is empty." << std::endl;
            return;
        }

        for (const auto& item : items) {
            item->print();
        }
        std::cout << "-------------------------" << std::endl;
        std::cout << "Subtotal:       $" << m_cart.getTotal() << std::endl;
        std::cout << "Final Total:    $" << m_cart.getTotalAfterDiscount() << std::endl;
        std::cout << "-------------------------\n" << std::endl;
    }

private:
    ShoppingCart& m_cart; // Reference to the Subject
};


int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "======= E-Commerce Shopping Cart Demo =======\n" << std::endl;

    // === 1. OBSERVER Pattern Setup ===
    // Create the Subject (ShoppingCart) and the Observer (CartUI)
    ShoppingCart cart;
    CartUI ui(cart); // The UI observes the cart

    std::cout << "--- DEMO: Adding items (triggers Observer) ---" << std::endl;

    // === 2. FACTORY METHOD Pattern ===
    // Use factories to create different types of products
    auto physicalFactory = std::make_unique<PhysicalProductFactory>();
    auto digitalFactory = std::make_unique<DigitalProductFactory>();

    cart.addItem(physicalFactory->createProduct()); // Adds "Default Book"
    cart.addItem(digitalFactory->createProduct());  // Adds "Software License"

    // === 3. BUILDER Pattern ===
    // Create a complex, configured product using the Builder
    std::cout << "--- DEMO: Adding complex product (Builder) ---" << std::endl;
    ProductBuilder laptopBuilder("LT-001", "15in Laptop");
    auto laptop = laptopBuilder.setPrice(1200.00)
                               .setDescription("A powerful laptop")
                               .setWeight(2.5)
                               .build();
    cart.addItem(std::move(laptop));

    // === 4. DECORATOR Pattern ===
    // Add a product and then decorate it with options
    std::cout << "--- DEMO: Adding decorated product (Decorator) ---" << std::endl;

    // Create a base product (headphones)
    ProductBuilder headphonesBuilder("HP-001", "Noise-Canceling Headphones");
    auto headphones = headphonesBuilder.setPrice(150.00).build();

    // Wrap it with two decorators
    auto wrappedHeadphones = std::make_unique<GiftWrapDecorator>(
        std::make_unique<ExtendedWarrantyDecorator>(
            std::move(headphones)
        )
    );

    // The name and price will be modified by the decorators
    cart.addItem(std::move(wrappedHeadphones));


    // === 5. STRATEGY Pattern ===
    // Apply different discount strategies to the cart
    std::cout << "--- DEMO: Applying 10% discount (Strategy) ---" << std::endl;
    cart.setDiscountStrategy(
        std::make_unique<PercentageDiscount>(10.0)
    );

    // The UI updates automatically (due to Observer) to show the new final price

    std::cout << "--- DEMO: Changing to $50 off (Strategy) ---" << std::endl;
    cart.setDiscountStrategy(
        std::make_unique<FixedAmountDiscount>(50.0)
    );

    // === 6. FACADE Pattern ===
    // Simplify the complex checkout process
    std::cout << "\n--- DEMO: Checking out (Facade) ---" << std::endl;
    CheckoutFacade checkout;
    bool success = checkout.placeOrder(cart,
                                        "123 Design Pattern St, Cppville",
                                        "4444-4444-4444-4444");

    if (success) {
        std::cout << "\nOrder placed successfully!" << std::endl;
    } else {
        std::cout << "\nFailed to place order." << std::endl;
    }

    std::cout << "\n======= Demo Finished =======\n" << std::endl;
    return 0;
}