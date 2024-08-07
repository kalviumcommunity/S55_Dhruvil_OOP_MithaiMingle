#include <iostream>
#include <string>

using namespace std;

// Class definition for Sweet
class Sweet {
public:
    string name;
    double pricePerKg;

    // Constructor
    Sweet(string n, double p) {
        this->name = n;
        this->pricePerKg = p;
    }

    // Member function to display details
    void displayDetails() {
        cout << "Sweet: " << this->name << ", Price per kg: ₹" << this->pricePerKg << endl;
    }

    // Member function to get the price per kg
    double getPricePerKg() {
        return this->pricePerKg;
    }
};

// Class definition for Customer
class Customer {
public:
    string name;
    double kgsWanted;
    double totalCost;

    // Constructor
    Customer(string n, double kgs) {
        this->name = n;
        this->kgsWanted = kgs;
        this->totalCost = 0.0;
    }

    // Member function to display customer details
    void displayDetails() {
        cout << "Customer: " << this->name << ", Wants: " << this->kgsWanted << " kg(s) of sweet, Total Cost: ₹" << this->totalCost << endl;
    }

    // Member function to update kgs wanted
    void updateKgsWanted(double newKgsWanted) {
        this->kgsWanted = newKgsWanted;
    }

    // Member function to calculate the total cost
    void calculateTotalCost(Sweet& sweet) {
        this->totalCost = this->kgsWanted * sweet.getPricePerKg();
    }
};

int main() {
    // Creating objects of Sweet class
    Sweet kajuKatli("Kaju Katli", 1600.0);
    Sweet mysorePak("Mysore Pak", 760.0);

    // Display details of sweets
    kajuKatli.displayDetails();
    mysorePak.displayDetails();

    // Creating objects of Customer class with user input
    string customerName;
    double kgsWanted;
    string sweetChoice;

    cout << "Enter customer name: ";
    cin >> customerName;
    cout << "Enter kilograms of sweets wanted: ";
    cin >> kgsWanted;
    Customer customer1(customerName, kgsWanted);

    cout << "Choose a sweet (Kaju Katli/Mysore Pak): ";
    cin.ignore(); // To ignore any newline character left in the buffer
    getline(cin, sweetChoice);

    if (sweetChoice == "Kaju Katli") {
        customer1.calculateTotalCost(kajuKatli);
    } else if (sweetChoice == "Mysore Pak") {
        customer1.calculateTotalCost(mysorePak);
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    customer1.displayDetails();

    // Update the kgs of sweets wanted by the customer using user input
    double newKgsWanted;
    cout << "Enter new kilograms of sweets wanted by " << customer1.name << ": ";
    cin >> newKgsWanted;
    customer1.updateKgsWanted(newKgsWanted);

    if (sweetChoice == "Kaju Katli") {
        customer1.calculateTotalCost(kajuKatli);
    } else if (sweetChoice == "Mysore Pak") {
        customer1.calculateTotalCost(mysorePak);
    }

    customer1.displayDetails();

    return 0;
}
