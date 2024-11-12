#include <iostream>
#include <string>
using namespace std;

// Base class Person
class Person {
protected:
    string name;

public:
    Person(string n) : name(n) {}

    string getName() const {
        return name;
    }

    void setName(string newName) {
        name = newName;
    }

    virtual ~Person() {
        cout << "Destructor called for Person: " << name << endl;
    }
};

// Abstract Sweet class
class Sweet {
protected:
    string name;
    double pricePerKg;

public:
    Sweet(string n, double p) : name(n), pricePerKg(p) {}

    virtual ~Sweet() {
        cout << "Destructor called for Sweet: " << name << endl;
    }

    double getPricePerKg() const {
        return pricePerKg;
    }

    virtual double calculateFinalPrice(double kgsWanted) const {
        return kgsWanted * pricePerKg;
    }

    virtual void displayDetails() const {
        cout << "Sweet: " << name << ", Price per kg: ₹" << pricePerKg << endl;
    }
};

// DiscountedSweet inherits Sweet and overrides price calculation
class DiscountedSweet : public Sweet {
private:
    double discountRate;

public:
    DiscountedSweet(string n, double p, double d) : Sweet(n, p), discountRate(d) {}

    double calculateFinalPrice(double kgsWanted) const override {
        return kgsWanted * pricePerKg * (1 - discountRate);
    }

    void displayDetails() const override {
        cout << "Sweet: " << name << ", Price per kg: ₹" << pricePerKg << ", Discount: " << discountRate * 100 << "%" << endl;
    }
};

// Order class managing orders and cost calculations
class Order {
public:
    static double calculateTotalCost(double kgsWanted, const Sweet& sweet) {
        return sweet.calculateFinalPrice(kgsWanted);
    }
};

// Customer class inheriting from Person
class Customer : public Person {
private:
    double kgsWanted;
    double totalCost;

public:
    Customer(string n, double kgs) : Person(n), kgsWanted(kgs), totalCost(0.0) {}

    void setKgsWanted(double kgs) {
        kgsWanted = kgs;
    }

    void displayDetails() const {
        cout << "Customer: " << name << ", Wants: " << kgsWanted << " kg(s) of sweet, Total Cost: ₹" << totalCost << endl;
    }

    // Calculate and update total cost using Order class
    void updateTotalCost(const Sweet& sweet) {
        totalCost = Order::calculateTotalCost(kgsWanted, sweet);
    }
};

int main() {
    Sweet kajuKatli("Kaju Katli", 1600.0);
    DiscountedSweet mysorePak("Mysore Pak", 760.0, 0.10);

    kajuKatli.displayDetails();
    mysorePak.displayDetails();

    Customer customer("Amit", 2.0);

    customer.updateTotalCost(kajuKatli);
    customer.displayDetails();

    customer.updateTotalCost(mysorePak);
    customer.displayDetails();

    return 0;
}
