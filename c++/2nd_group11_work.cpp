#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class
class Order {
protected:
    int orderID;
    string status;

public:
    void setOrder(int id) {
        orderID = id;
        status = "Pending";
    }
    void updateStatus(string newStatus) {
        status = newStatus;
    }
    void displayOrder() {
        cout << "Order ID: " << orderID << endl;
        cout << "Status: " << status << endl;
    }
};

// Derived class - InHouseOrder
class InHouseOrder : public Order {
protected:
    string restaurantName;

public:
    void setRestaurant(string name) {
        restaurantName = name;
    }
    void showRestaurant() {
        cout << "Restaurant: " << restaurantName << endl;
    }
};

// Derived class - ExternalOrder
class ExternalOrder : public Order {
protected:
    string deliveryCompany;

public:
    void setCompany(string company) {
        deliveryCompany = company;
    }
    void showCompany() {
        cout << "Delivery Company: " << deliveryCompany << endl;
    }
};

// Multilevel inheritance
class TimedOrder : public InHouseOrder {
protected:
    int etaMinutes;

public:
    void setETA(int eta) {
        etaMinutes = eta;
    }
    void showETA() {
        cout << "ETA: " << etaMinutes << " mins" << endl;
    }
};

// Final class
class FoodDeliveryApp : public TimedOrder {
private:
    string driverName;

public:
    void assignDriver(string name) {
        driverName = name;
    }

    void displayFullDetails() {
        displayOrder();
        showRestaurant();
        showETA();
        cout << "Driver: " << driverName << endl;
    }
};

int main() {
    int choice;
    char again;

    do {
        cout << "\nChoose Order Type:\n";
        cout << "1. In-House Order\n";
        cout << "2. External Order\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        if (choice == 1) {
            FoodDeliveryApp order1;
            int id, eta;
            string restaurant, driver, status;

            cout << "Enter Order ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Restaurant Name: ";
            getline(cin, restaurant);

            cout << "Enter ETA in minutes: ";
            cin >> eta;
            cin.ignore();

            cout << "Enter Driver Name: ";
            getline(cin, driver);

            cout << "Enter Order Status: ";
            getline(cin, status);

            order1.setOrder(id);
            order1.setRestaurant(restaurant);
            order1.setETA(eta);
            order1.assignDriver(driver);
            order1.updateStatus(status);

            cout << "\n--- In-House Order Details ---\n";
            order1.displayFullDetails();

        } else if (choice == 2) {
            ExternalOrder extOrder;
            int id;
            string company, status;

            cout << "Enter Order ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Delivery Company Name: ";
            getline(cin, company);

            cout << "Enter Order Status: ";
            getline(cin, status);

            extOrder.setOrder(id);
            extOrder.setCompany(company);
            extOrder.updateStatus(status);

            cout << "\n--- External Order Details ---\n";
            extOrder.displayOrder();
            extOrder.showCompany();

        } else {
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << "\nDo you want to enter another order? (y/n): ";
        cin >> again;
        cin.ignore();

    } while (again == 'y' || again == 'Y');

    cout << "Thank you for using the Food Delivery App!" << endl;
    return 0;
}
