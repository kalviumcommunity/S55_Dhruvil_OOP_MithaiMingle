#include <iostream>
#include <string>

using namespace std;

// Class definition for Sweet
class Sweet {
private:
    string name;
    double pricePerKg;

public:
    // Constructor
    Sweet(string n, double p) {
        this->name = n;
        this->pricePerKg = p;
    }

    // Accessor (Getter) for name
    string getName() {
        return name;
    }

    // Mutator (Setter) for name
    void setName(string newName) {
        name = newName;
    }

    // Accessor (Getter) for pricePerKg
    double getPricePerKg() {
        return pricePerKg;
    }

    // Mutator (Setter) for pricePerKg
    void setPricePerKg(double newPrice) {
        pricePerKg = newPrice;
    }

    // Member function to display details
    void displayDetails() {
        cout << "Sweet: " << name << ", Price per kg: ₹" << pricePerKg << endl;
    }
};

// Class definition for Customer
class Customer {
private:
    string name;
    double kgsWanted;
    double totalCost;

public:
    // Static variables
    static int totalCustomers;
    static double totalSweetsSold;

    // Constructor
    Customer(string n, double kgs) {
        this->name = n;
        this->kgsWanted = kgs;
        this->totalCost = 0.0;
        totalCustomers++;  // Increment total customers
    }

    // Accessor (Getter) for name
    string getName() {
        return name;
    }

    // Mutator (Setter) for name
    void setName(string newName) {
        name = newName;
    }

    // Accessor (Getter) for kgsWanted
    double getKgsWanted() {
        return kgsWanted;
    }

    // Mutator (Setter) for kgsWanted
    void setKgsWanted(double newKgsWanted) {
        kgsWanted = newKgsWanted;
    }

    // Accessor (Getter) for totalCost
    double getTotalCost() {
        return totalCost;
    }

    // Member function to calculate the total cost
    void calculateTotalCost(Sweet& sweet) {
        totalCost = kgsWanted * sweet.getPricePerKg();
        totalSweetsSold += kgsWanted;  // Add to total sweets sold
    }

    // Member function to display customer details
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
    // Dynamically allocate memory for Sweet objects
    Sweet* sweets[2];
    sweets[0] = new Sweet("Kaju Katli", 1600.0);
    sweets[1] = new Sweet("Mysore Pak", 760.0);

    // Display details of sweets using dynamic objects
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
        cin.ignore(); // Ignore the leftover newline character
        getline(cin, customerName);

        cout << "Enter kilograms of sweets wanted: ";
        cin >> kgsWanted;
        customers[i] = new Customer(customerName, kgsWanted);

        cout << "Choose a sweet (Kaju Katli/Mysore Pak): ";
        cin.ignore(); // Ignore the leftover newline character again
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
            delete[] customers;
            return 1;
        }

        customers[i]->displayDetails();

        // Ask if the user wants to update the kgs of sweets
        char updateChoice;
        cout << "Do you want to update the kilograms of sweets wanted by " << customers[i]->getName() << "? (y/n): ";
        cin >> updateChoice;

        if (updateChoice == 'y' || updateChoice == 'Y') {
            double newKgsWanted;
            cout << "Enter new kilograms of sweets wanted by " << customers[i]->getName() << ": ";
            cin >> newKgsWanted;
            customers[i]->setKgsWanted(newKgsWanted);

            if (sweetChoice == "Kaju Katli") {
                customers[i]->calculateTotalCost(*sweets[0]);
            } else if (sweetChoice == "Mysore Pak") {
                customers[i]->calculateTotalCost(*sweets[1]);
            }

            customers[i]->displayDetails();
        }
    }

    // Display summary of total customers and total sweets sold
    Customer::displaySummary();

    // Free dynamically allocated memory
    for (int i = 0; i < 2; ++i) {
        delete sweets[i];
    }
    for (int i = 0; i < numCustomers; ++i) {
        delete customers[i];
    }
    delete[] customers;

    return 0;
}

