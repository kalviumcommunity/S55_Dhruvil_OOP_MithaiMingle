#include <iostream>
#include <string>

using namespace std;

// Base class Person
class Person {
protected:
    string name;

public:
    Person(string n) : name(n) {}

    string getName() {
        return name;
    }

    void setName(string newName) {
        name = newName;
    }

    // Destructor for Person
    virtual ~Person() {
        cout << "Destructor called for Person: " << name << endl;
    }
};

// Class definition for Sweet
class Sweet {
protected:
    string name;
    double pricePerKg;

public:
    // Constructor
    Sweet(string n, double p) : name(n), pricePerKg(p) {}

    // Destructor
    virtual ~Sweet() {
        cout << "Destructor called for Sweet: " << name << endl;
    }

    // Accessor for price
    double getPricePerKg() {
        return pricePerKg;
    }

    // Function to display sweet details
    virtual void displayDetails() {
        cout << "Sweet: " << name << ", Price per kg: ₹" << pricePerKg << endl;
    }
};

// Derived class for discounted sweets (Single Inheritance)
class DiscountedSweet : public Sweet {
private:
    double discountRate;

public:
    DiscountedSweet(string n, double p, double d) : Sweet(n, p), discountRate(d) {}

    // Override to display discounted sweet details
    void displayDetails() override {
        cout << "Sweet: " << name << ", Price per kg: ₹" << pricePerKg << ", Discount rate: " << discountRate * 100 << "%" << endl;
    }

    // Function to calculate price with discount
    double getDiscountedPrice() {
        return pricePerKg * (1 - discountRate);
    }
};

// Class definition for Customer (Multilevel Inheritance from Person)
class Customer : public Person {
private:
    double kgsWanted;
    double totalCost;

public:
    static int totalCustomers;
    static double totalSweetsSold;

    // Constructor
    Customer(string n, double kgs) : Person(n), kgsWanted(kgs), totalCost(0.0) {
        totalCustomers++;
    }

    // Destructor
    ~Customer() {
        cout << "Destructor called for Customer: " << name << endl;
    }

    // Function to calculate the total cost
    void calculateTotalCost(Sweet& sweet) {
        totalCost = kgsWanted * sweet.getPricePerKg();
        totalSweetsSold += kgsWanted;
    }

    // Overloaded function to calculate cost with discount
    void calculateTotalCost(DiscountedSweet& sweet) {
        totalCost = kgsWanted * sweet.getDiscountedPrice();
        totalSweetsSold += kgsWanted;
    }

    // Function to display customer details
    void displayDetails() {
        cout << "Customer: " << name << ", Wants: " << kgsWanted << " kg(s) of sweet, Total Cost: ₹" << totalCost << endl;
    }

    // Static function to display summary
    static void displaySummary() {
        cout << "Total customers: " << totalCustomers << endl;
        cout << "Total sweets sold: " << totalSweetsSold << " kg(s)" << endl;
    }
};

// Initialize static variables
int Customer::totalCustomers = 0;
double Customer::totalSweetsSold = 0.0;

int main() {
    // Create Sweet and DiscountedSweet objects
    Sweet* sweets[2];
    sweets[0] = new Sweet("Kaju Katli", 1600.0);
    sweets[1] = new DiscountedSweet("Mysore Pak", 760.0, 0.10); // 10% discount

    // Display details of sweets
    for (int i = 0; i < 2; ++i) {
        sweets[i]->displayDetails();
    }

    int numCustomers;
    cout << "Enter the number of customers: ";
    cin >> numCustomers;

    // Dynamically allocate memory for Customer objects based on user input
    Customer** customers = new Customer*[numCustomers];

    string customerName;
    double kgsWanted;
    string sweetChoice;

    for (int i = 0; i < numCustomers; ++i) {
        cout << "Enter customer name for Customer " << (i + 1) << ": ";
        cin.ignore();
        getline(cin, customerName);

        cout << "Enter kilograms of sweets wanted: ";
        cin >> kgsWanted;
        customers[i] = new Customer(customerName, kgsWanted);

        cout << "Choose a sweet (Kaju Katli/Mysore Pak): ";
        cin.ignore();
        getline(cin, sweetChoice);

        if (sweetChoice == "Kaju Katli") {
            customers[i]->calculateTotalCost(*sweets[0]);
        } else if (sweetChoice == "Mysore Pak") {
            customers[i]->calculateTotalCost(*dynamic_cast<DiscountedSweet*>(sweets[1])); // Discount applied
        } else {
            cout << "Invalid choice!" << endl;
            delete customers[i];
            for (int j = 0; j < 2; ++j) {
                delete sweets[j];
            }
            delete[] customers;
            return 1;
        }

        customers[i]->displayDetails();
    }

    // Display summary
    Customer::displaySummary();

    // Free memory
    for (int i = 0; i < 2; ++i) {
        delete sweets[i];
    }
    for (int i = 0; i < numCustomers; ++i) {
        delete customers[i];
    }
    delete[] customers;

    return 0;
}
