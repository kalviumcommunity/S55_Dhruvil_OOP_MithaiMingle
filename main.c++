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
    // Dynamically allocate memory for Sweet objects
    Sweet* sweets[2];
    sweets[0] = new Sweet("Kaju Katli", 1600.0);
    sweets[1] = new Sweet("Mysore Pak", 760.0);

    // Display details of sweets using dynamic objects
    for (int i = 0; i < 2; ++i) {
        sweets[i]->displayDetails();
    }

    // Dynamically allocate memory for Customer objects
    Customer* customers[2];
    
    string customerName;
    double kgsWanted;
    string sweetChoice;

    for (int i = 0; i < 2; ++i) {
        cout << "Enter customer name for Customer " << (i + 1) << ": ";
        cin >> customerName;
        cout << "Enter kilograms of sweets wanted: ";
        cin >> kgsWanted;
        customers[i] = new Customer(customerName, kgsWanted);

        cout << "Choose a sweet (Kaju Katli/Mysore Pak): ";
        cin.ignore(); // To ignore any newline character left in the buffer
        getline(cin, sweetChoice);

        if (sweetChoice == "Kaju Katli") {
            customers[i]->calculateTotalCost(*sweets[0]);
        } else if (sweetChoice == "Mysore Pak") {
            customers[i]->calculateTotalCost(*sweets[1]);
        } else {
            cout << "Invalid choice!" << endl;
            // Free dynamically allocated memory before exiting
            delete customers[i];
            for (int j = 0; j < 2; ++j) {
                delete sweets[j];
            }
            return 1;
        }

        customers[i]->displayDetails();

        // Update the kgs of sweets wanted by the customer using user input
        double newKgsWanted;
        cout << "Enter new kilograms of sweets wanted by " << customers[i]->name << ": ";
        cin >> newKgsWanted;
        customers[i]->updateKgsWanted(newKgsWanted);

        if (sweetChoice == "Kaju Katli") {
            customers[i]->calculateTotalCost(*sweets[0]);
        } else if (sweetChoice == "Mysore Pak") {
            customers[i]->calculateTotalCost(*sweets[1]);
        }

        customers[i]->displayDetails();
    }

    // Free dynamically allocated memory
    for (int i = 0; i < 2; ++i) {
        delete sweets[i];
        delete customers[i];
    }

    return 0;
}
