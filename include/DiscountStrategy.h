#pragma once

/**
 * @brief (Strategy Pattern) The Strategy interface.
 * Declares a method for applying a discount to a total price.
 */
class IDiscountStrategy {
public:
    virtual ~IDiscountStrategy() = default;
    virtual double applyDiscount(double total) const = 0;
};

/**
 * @brief Concrete Strategy: Applies a percentage-based discount.
 */
class PercentageDiscount : public IDiscountStrategy {
public:
    explicit PercentageDiscount(double percentage) : m_percentage(percentage) {}

    double applyDiscount(double total) const override;

private:
    double m_percentage;
};

/**
 * @brief Concrete Strategy: Applies a fixed amount discount.
 */
class FixedAmountDiscount : public IDiscountStrategy {
public:
    explicit FixedAmountDiscount(double amount) : m_amount(amount) {}

    double applyDiscount(double total) const override;

private:
    double m_amount;
};