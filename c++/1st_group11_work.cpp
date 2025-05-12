#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip> 

using namespace std;

class Order {
private:
    int orderId;
    vector<string> foodItems;
    double totalPrice;
    bool isAssigned;

public:
    Order(int id, const vector<string>& items, double price)
        : orderId(id), foodItems(items), totalPrice(price), isAssigned(false) {}

    int getOrderId() const { return orderId; }
    vector<string> getFoodItems() const { return foodItems; }
    double getTotalPrice() const { return totalPrice; }
    bool getIsAssigned() const { return isAssigned; }

    void assignOrder() { isAssigned = true; }

    void displayOrder() const {
        cout << fixed << setprecision(2);
        cout << "Order ID: " << orderId << endl;
        cout << "Food Items: ";
        for (size_t i = 0; i < foodItems.size(); ++i) {
            cout << foodItems[i];
            if (i < foodItems.size() - 1) cout << ", ";
        }
        cout << "\nTotal Price: $" << totalPrice << endl;
        cout << "Status: " << (isAssigned ? "Assigned" : "Not Assigned") << endl;
        cout << "-------------------------\n";
    }
};

class Delivery {
private:
    string driverName;
    string deliveryStatus;
    vector<int> assignedOrderIds;

public:
    Delivery(const string& name)
        : driverName(name), deliveryStatus("Available") {}

    string getDriverName() const { return driverName; }
    string getDeliveryStatus() const { return deliveryStatus; }
    vector<int> getAssignedOrderIds() const { return assignedOrderIds; }

    void assignOrder(int orderId) {
        assignedOrderIds.push_back(orderId);
        deliveryStatus = "On Delivery";
    }

    void updateStatus(const string& status) {
        deliveryStatus = status;
    }

    void displayDelivery() const {
        cout << "Driver Name: " << driverName << endl;
        cout << "Delivery Status: " << deliveryStatus << endl;
        cout << "Assigned Order IDs: ";
        for (int id : assignedOrderIds) {
            cout << id << " ";
        }
        cout << "\n-------------------------\n";
    }
};

class DeliverySystem {
private:
    vector<Order> orders;
    vector<Delivery> deliveryAgents;
    unordered_map<int, string> orderToDriverMap;

public:
    void addOrder(const Order& order) {
        orders.push_back(order);
    }

    void addDeliveryAgent(const Delivery& agent) {
        deliveryAgents.push_back(agent);
    }

    bool assignDriverToOrder(int orderId, const string& driverName) {
        for (auto& order : orders) {
            if (order.getOrderId() == orderId && !order.getIsAssigned()) {
                for (auto& agent : deliveryAgents) {
                    if (agent.getDriverName() == driverName) {
                        order.assignOrder();
                        agent.assignOrder(orderId);
                        orderToDriverMap[orderId] = driverName;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool updateDeliveryStatus(int orderId, const string& status) {
        auto it = orderToDriverMap.find(orderId);
        if (it != orderToDriverMap.end()) {
            string driverName = it->second;
            for (auto& agent : deliveryAgents) {
                if (agent.getDriverName() == driverName) {
                    agent.updateStatus(status);
                    return true;
                }
            }
        }
        return false;
    }

    void trackOrder(int orderId) const {
        bool orderFound = false;
        for (const auto& order : orders) {
            if (order.getOrderId() == orderId) {
                orderFound = true;
                order.displayOrder();
                auto it = orderToDriverMap.find(orderId);
                if (it != orderToDriverMap.end()) {
                    string driverName = it->second;
                    cout << "Assigned to driver: " << driverName << endl;
                    for (const auto& agent : deliveryAgents) {
                        if (agent.getDriverName() == driverName) {
                            cout << "Delivery Status: " << agent.getDeliveryStatus() << endl;
                            break;
                        }
                    }
                } else {
                    cout << "Not yet assigned to a driver." << endl;
                }
                break;
            }
        }
        if (!orderFound) {
            cout << "Order with ID " << orderId << " not found." << endl;
        }
    }

    void displayAllOrders() const {
        cout << "\nAll Orders:\n";
        for (const auto& order : orders) {
            order.displayOrder();
        }
    }

    void displayAllDeliveryAgents() const {
        cout << "\nAll Delivery Agents:\n";
        for (const auto& agent : deliveryAgents) {
            agent.displayDelivery();
        }
    }
};

int main() {
    DeliverySystem system;
    system.addDeliveryAgent(Delivery("John Doe"));
    system.addDeliveryAgent(Delivery("Jane Smith"));

    int choice;
    do {
        cout << "\n--- Delivery System Menu ---\n";
        cout << "1. Add Order\n";
        cout << "2. Assign Driver to Order\n";
        cout << "3. Update Delivery Status\n";
        cout << "4. Track Order\n";
        cout << "5. Display All Orders\n";
        cout << "6. Display All Delivery Agents\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            int id, itemCount;
            double price;
            vector<string> items;

            cout << "Enter Order ID: ";
            cin >> id;
            cout << "Enter number of food items: ";
            cin >> itemCount;
            cin.ignore();

            for (int i = 0; i < itemCount; ++i) {
                string item;
                cout << "Enter item " << (i + 1) << ": ";
                getline(cin, item);
                items.push_back(item);
            }

            cout << "Enter total price: ";
            cin >> price;

            system.addOrder(Order(id, items, price));
            break;
        }
        case 2: {
            int orderId;
            string driverName;
            cout << "Enter Order ID to assign: ";
            cin >> orderId;
            cin.ignore();
            cout << "Enter Driver Name: ";
            getline(cin, driverName);
            if (system.assignDriverToOrder(orderId, driverName)) {
                cout << "Driver assigned successfully.\n";
            } else {
                cout << "Failed to assign driver.\n";
            }
            break;
        }
        case 3: {
            int orderId;
            string status;
            cout << "Enter Order ID to update status: ";
            cin >> orderId;
            cin.ignore();
            cout << "Enter new status: ";
            getline(cin, status);
            if (system.updateDeliveryStatus(orderId, status)) {
                cout << "Status updated.\n";
            } else {
                cout << "Failed to update status.\n";
            }
            break;
        }
        case 4: {
            int orderId;
            cout << "Enter Order ID to track: ";
            cin >> orderId;
            system.trackOrder(orderId);
            break;
        }
        case 5:
            system.displayAllOrders();
            break;
        case 6:
            system.displayAllDeliveryAgents();
            break;
        case 0:
            cout << "Exiting system.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
	
	return 0;
}
