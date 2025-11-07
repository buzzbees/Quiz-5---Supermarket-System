#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

struct Product {
    string name;
    float price;
    int quantity;
};

void displayMenu() {
    cout << "---*** MARKET MANAGER MENU ***---" << endl;
    cout << "1. View Inventory" << endl;
    cout << "2. Add Product" << endl;
    cout << "3. Remove Product" << endl;
    cout << "4. Restock Product" << endl;
    cout << "5. Handle Customer Purchase" << endl;
    cout << "6. End Of Day Report" << endl;
    cout << "7. Exit Manager System" << endl;
    cout << "---------------------------" << endl;
}
void viewInventory(vector<Product>& storeProduct) {
    if (storeProduct.empty()) {
        cout << "You have no products in your Inventory! Go back to the system and add a product" << endl;
        return;
    }
    cout << "---***Current Inventory***---" << endl;
    cout << left << setw(20) << "Product Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
    cout << "-----------------------------" << endl;
    for (Product& product : storeProduct) {
        if (product.quantity < 5) {
            cout << "Low stock alert! Please restock product!" << endl;
        }
        cout << left << setw(20) << product.name << fixed << setprecision(2) << setw(10) << product.price << setw(10) << product.quantity << endl;
    }
    cout << "-----------------------------" << endl;
};
void addProduct(vector<Product>& storeProduct) {
    Product newProduct;
    cout << "Enter product name: ";
    getline(cin, newProduct.name);
    cout << "Enter product price: ";
    cin >> newProduct.price;
    cout << "Enter product quantity: ";
    cin >> newProduct.quantity;
    cin.ignore(); // Consume the newline character

    storeProduct.push_back(newProduct);
    cout << newProduct.name << " added to inventory." << endl;
};
void removeProduct(vector<Product>& storeProduct) {
    if (storeProduct.empty()) {
        cout << "You have no products in your Inventory! Go back to the system and add a product" << endl;
        return;
    }
    string productName;
    cout << "Please enter the name of the prodcut you would like to remove: " << endl;
    getline(cin, productName);
    
    for (int i = 0; i < storeProduct.size(); i++) {
        if (storeProduct[i].name == productName) {
            cout << storeProduct[i].name << " has been removed from inventory." << endl;
            storeProduct.erase(storeProduct.begin() + i);
            return;
        }
    }
};
void restockProduct(vector<Product>& storeProduct) {
    string productName;
    int quantityToAdd;
    cout << "Enter name of product to restock: ";
    getline(cin, productName);

    for (Product& product : storeProduct) {
        if (product.name == productName) {
            cout << "Enter quantity to add: ";
            cin >> quantityToAdd;
            cin.ignore(); // Consume the newline character
            product.quantity += quantityToAdd;
            cout << productName << " restocked. New quantity: " << product.quantity << endl;
            return;
        }
    }
};
void handlePurchase(vector<Product>& storeProduct, float* storeBalance) {
    string productName;
    int quantityToBuy;
    float totalCost = 0.0;

    cout << "Enter name of product to purchase (or 'done' to finish): ";
    while (getline(cin, productName) && productName != "done") {
        bool found = false;
        for (Product& product : storeProduct) {
            if (product.name == productName) {
                found = true;
                cout << "Enter quantity to buy: ";
                cin >> quantityToBuy;
                cin.ignore(); // Consume the newline character

                if (quantityToBuy > 0 && quantityToBuy <= product.quantity) {
                    product.quantity -= quantityToBuy;
                    totalCost += (product.price * quantityToBuy);
                    cout << "Purchased " << quantityToBuy << " units of " << productName << "." << endl;
                } else {
                    cout << "Invalid quantity or insufficient stock for " << productName << ". Available: " << product.quantity << endl;
                }
                break;
            }
        }
        cout << "Enter name of product to purchase (or 'done' to finish): ";
    }
    *storeBalance += totalCost;
    cout << fixed << setprecision(2) << "Total purchase amount: $" << totalCost << endl;
    cout << "Store balance updated. New balance: $" << *storeBalance << endl;
};
void endOfDayReport (vector<Product>& storeProduct, float storeBalance) {
    vector<int> dailySales(storeProduct.size(), 0);
    cout << "End of day purchases" << endl;
    
    for (int i = 0; i < storeProduct.size(); i++) {
        dailySales[i] = rand() % (20 + 1);
        cout << "Product " << storeProduct[i].name << " sold " << dailySales[i] << " times." << endl;
    }
    float totalRevenue = 0;
    for (int i = 0; i < storeProduct.size(); i++) {
        totalRevenue += dailySales[i] * storeProduct[i].price;
    }
    storeBalance += totalRevenue;
    
    cout << "---***End Of Day Report***---" << endl;
    if (storeBalance < 1000) {
        cout << "Low funds! Improve store to generate more profit!" << endl;
    }
    cout << "Total Daily Revenue: $" << totalRevenue;
    viewInventory(storeProduct); // Display current inventory
    cout << fixed << setprecision(2) << "Final Store Balance: $" << storeBalance << endl;
    cout << "-------------------------" << endl;
};




int main() {
    // TODO: Declare variables for manager name, store name, and store balance
    string manager, storeName;
    float storeBalance = 0.00;
    // TODO: Get input and print welcome message
    cout << "Hello and welcome to your supermarket system! Please enter your name: " << endl;
    getline(cin, manager);
    cout << "Please enter the name of the supermarket: " << endl;
    getline(cin, storeName);
    cout << "Your current store balance is: $" << storeBalance << endl;

    // TODO: Initialize vector<Product> with some starting items
    vector<Product> products;
    products.push_back({"Apples", 2.50, 50});
    products.push_back({"Cheese", 5.00, 10});
    products.push_back({"Milk", 3.00, 15});
    products.push_back({"Bread", 1.25, 20});
    products.push_back({"Cereal", 4.99, 25});
    

    srand(time(0));
    int choice;

    do {
        // TODO: Display menu
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            // TODO: Implement menu logic calling functions
            case 1:
                viewInventory(products);
                break;
            case 2:
                addProduct(products);
                break;
            case 3:
                removeProduct(products);
                break;
            case 4:
                restockProduct(products);
                break;
            case 5:
                handlePurchase(products, &storeBalance);
                break;
            case 6:
                endOfDayReport(products, storeBalance);
                cout << "Great job " << manager << " it looks like you're well on your way!" << endl;
                break;
            case 7:
                cout << "Thanks for using the Sypermarket System! Goodbye!";
                break;
            default:
                cout << "Please enter a number 1-7" << endl;
                break;
        }
        cout << endl;
    } while (choice != 7);

    return 0;
}
