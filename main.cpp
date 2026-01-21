#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For random numbers
#include <ctime>   // For time
#include <iomanip> // For currency formatting

using namespace std;

// 1. Define the Structure of a Stock
struct Stock {
    string symbol;
    string name;
    double price;
};

// Helper function to display market status
void showMarket(const vector<Stock>& market) {
    cout << "\n--- 📈 PSX LIVE MARKET STATUS ---" << endl;
    cout << left << setw(10) << "SYMBOL" << setw(20) << "NAME" << "PRICE (PKR)" << endl;
    cout << "---------------------------------------------" << endl;
    for (const auto& s : market) {
        cout << left << setw(10) << s.symbol << setw(20) << s.name << fixed << setprecision(2) << s.price << endl;
    }
    cout << "---------------------------------------------" << endl;
}

int main() {
    // Seed random number generator
    srand(time(0));

    // Initialize User
    double userBalance = 100000.00; // 1 Lakh PKR Start

    // Initialize Market Data (Dummy PSX Data)
    vector<Stock> market = {
        {"OGDC", "Oil & Gas Dev", 118.50},
        {"TRG", "TRG Pakistan", 88.25},
        {"LUCK", "Lucky Cement", 650.00},
        {"SYS", "Systems Ltd", 430.75}
    };

    bool isRunning = true;
    int choice;

    cout << "Welcome to Quantum Park's PSX Simulator!" << endl;

    while (isRunning) {
        cout << "\n💰 Your Balance: PKR " << fixed << setprecision(2) << userBalance << endl;
        cout << "1. View Market" << endl;
        cout << "2. Buy Stock (Simulation)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            // Fluctuate prices slightly before showing to simulate "Live Market"
            for (auto& s : market) {
                double change = (rand() % 10 - 5); // Random shift between -5 and +5
                s.price += change;
                if (s.price < 0) s.price = 1.0; // Prevent negative stock prices
            }
            showMarket(market);
        }
        else if (choice == 2) {
            // Simple Buy Logic
            string symbol;
            int qty;
            cout << "Enter Symbol (e.g., TRG): ";
            cin >> symbol;
            cout << "Enter Quantity: ";
            cin >> qty;

            // Find stock (Simple search)
            bool found = false;
            for (auto& s : market) {
                if (s.symbol == symbol) {
                    double cost = s.price * qty;
                    if (userBalance >= cost) {
                        userBalance -= cost;
                        cout << "✅ Successfully bought " << qty << " shares of " << s.name << "!" << endl;
                    } else {
                        cout << "❌ Insufficient Funds! You need " << cost << " PKR." << endl;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "❌ Symbol not found!" << endl;
        }
        else if (choice == 3) {
            isRunning = false;
            cout << "Exiting Simulator. Goodbye!" << endl;
        } else {
            cout << "Invalid Option." << endl;
        }
    }

    return 0;
}
