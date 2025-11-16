#pragma once

#include "IProduct.h"
#include "IObserver.h"
#include "DiscountStrategy.h"
#include <vector>
#include <memory>
#include <numeric> // for std::accumulate

/**
 * @brief The main ShoppingCart class.
 *
 * This class demonstrates two patterns:
 * 1. (Observer Pattern): It is a Concrete Subject. It notifies observers (like UI)
 * when its state (items) changes.
 * 2. (Strategy Pattern): It is the Context. It holds a reference to a discount
 * strategy and uses it to calculate the final price.
 */
class ShoppingCart : public Subject {
public:
    ShoppingCart() = default;

    void addItem(std::unique_ptr<IProduct> product);
    void removeItem(const std::string& sku);

    double getTotal() const;
    double getTotalAfterDiscount() const;

    void setDiscountStrategy(std::unique_ptr<IDiscountStrategy> strategy);

    // Provide read-only access to items for Observers
    const std::vector<std::unique_ptr<IProduct>>& getItems() const;

private:
    std::vector<std::unique_ptr<IProduct>> m_items;
    std::unique_ptr<IDiscountStrategy> m_strategy;
};