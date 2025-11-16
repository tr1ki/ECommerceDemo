#include "DiscountStrategy.h"
#include <algorithm> // for std::max

double PercentageDiscount::applyDiscount(double total) const {
    if (m_percentage < 0.0 || m_percentage > 100.0) {
        return total; // Invalid percentage
    }
    return total * (1.0 - m_percentage / 100.0);
}

double FixedAmountDiscount::applyDiscount(double total) const {
    return std::max(0.0, total - m_amount);
}