#include "ShoppingCart.h"

void ShoppingCart::addItem(std::unique_ptr<IProduct> product) {
    if (product) {
        m_items.push_back(std::move(product));
        notify(); // Notify observers of the change
    }
}

void ShoppingCart::removeItem(const std::string& sku) {
    auto it = std::remove_if(m_items.begin(), m_items.end(),
        [&sku](const auto& item) {
            return item->getSKU() == sku;
        });

    if (it != m_items.end()) {
        m_items.erase(it, m_items.end());
        notify(); // Notify observers of the change
    }
}

double ShoppingCart::getTotal() const {
    // Sum the prices of all items in the cart
    return std::accumulate(m_items.begin(), m_items.end(), 0.0,
        [](double sum, const auto& item) {
            return sum + item->getPrice();
        });
}

double ShoppingCart::getTotalAfterDiscount() const {
    double total = getTotal();
    if (m_strategy) {
        return m_strategy->applyDiscount(total);
    }
    return total;
}

void ShoppingCart::setDiscountStrategy(std::unique_ptr<IDiscountStrategy> strategy) {
    m_strategy = std::move(strategy);
    notify(); // Notify observers that the price logic might have changed
}

const std::vector<std::unique_ptr<IProduct>>& ShoppingCart::getItems() const {
    return m_items;
}