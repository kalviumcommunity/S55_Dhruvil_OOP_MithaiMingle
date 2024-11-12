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

    // Virtual method to allow overriding in derived classes
    virtual double calculateFinalPrice(double kgsWanted) const {
        return kgsWanted * pricePerKg;
    }

    virtual void displayDetails() const {
        cout << "Sweet: " << name << ", Price per kg: ₹" << pricePerKg << endl;
    }
};

// DiscountedSweet inherits Sweet and maintains the interface consistency
class DiscountedSweet : public Sweet {
private:
    double discountRate;

public:
    DiscountedSweet(string n, double p, double d) : Sweet(n, p), discountRate(d) {}

    // Overriding calculateFinalPrice to include discount
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
    // Method compatible with any class derived from Sweet
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
    string sweetName;
    double pricePerKg, discountRate, kgsWanted;
    string customerName;

    cout << "Enter sweet name: ";
    getline(cin, sweetName);
    cout << "Enter price per kg of " << sweetName << ": ";
    cin >> pricePerKg;

    Sweet kajuKatli(sweetName, pricePerKg);
    kajuKatli.displayDetails();

    cout << "Enter discounted sweet name: ";
    cin.ignore();
    getline(cin, sweetName);
    cout << "Enter price per kg of " << sweetName << ": ";
    cin >> pricePerKg;
    cout << "Enter discount rate (as a decimal): ";
    cin >> discountRate;

    DiscountedSweet mysorePak(sweetName, pricePerKg, discountRate);
    mysorePak.displayDetails();

    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter kgs wanted by " << customerName << ": ";
    cin >> kgsWanted;

    Customer customer(customerName, kgsWanted);

    customer.updateTotalCost(kajuKatli);
    customer.displayDetails();

    customer.updateTotalCost(mysorePak);
    customer.displayDetails();

    return 0;
}
