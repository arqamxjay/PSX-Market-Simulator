#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Stock {
    string symbol;
    string name;
    double price;
};

// NEW: Structure to track what you own
struct Holding {
    string symbol;
    int quantity;
    double avgCost;
};

void showMarket(const vector<Stock>& market) {
    cout << "\n--- 📈 PSX LIVE MARKET STATUS ---" << endl;
    cout << left << setw(10) << "SYMBOL" << setw(20) << "NAME" << "PRICE (PKR)" << endl;
    cout << "---------------------------------------------" << endl;
    for (const auto& s : market) {
        cout << left << setw(10) << s.symbol << setw(20) << s.name << fixed << setprecision(2) << s.price << endl;
    }
    cout << "---------------------------------------------" << endl;
}

// NEW: Function to show your portfolio
void showPortfolio(const vector<Holding>& myStocks, double balance) {
    cout << "\n--- 💼 MY PORTFOLIO ---" << endl;
    cout << "Cash Balance: PKR " << fixed << setprecision(2) << balance << endl;
    
    if (myStocks.empty()) {
        cout << "(You don't own any stocks yet)" << endl;
    } else {
        cout << "---------------------------------------------" << endl;
        cout << left << setw(10) << "SYMBOL" << setw(10) << "QTY" << "AVG COST" << endl;
        cout << "---------------------------------------------" << endl;
        for (const auto& h : myStocks) {
            cout << left << setw(10) << h.symbol << setw(10) << h.quantity << fixed << setprecision(2) << h.avgCost << endl;
        }
    }
    cout << "---------------------------------------------" << endl;
}

int main() {
    srand(time(0));
    double userBalance = 100000.00;
    
    // NEW: Vector to store owned stocks
    vector<Holding> myPortfolio;

    vector<Stock> market = {
        {"OGDC", "Oil & Gas Dev", 118.50},
        {"TRG", "TRG Pakistan", 88.25},
        {"LUCK", "Lucky Cement", 650.00},
        {"SYS", "Systems Ltd", 430.75}
    };

    bool isRunning = true;
    int choice;

    cout << "Welcome to Quantum Park's PSX Simulator (v2.0)!" << endl;

    while (isRunning) {
        cout << "\n1. View Market" << endl;
        cout << "2. Buy Stock" << endl;
        cout << "3. View Portfolio (NEW)" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            for (auto& s : market) {
                double change = (rand() % 10 - 5);
                s.price += change;
                if (s.price < 1.0) s.price = 1.0;
            }
            showMarket(market);
        }
        else if (choice == 2) {
            string symbol;
            int qty;
            cout << "Enter Symbol: ";
            cin >> symbol;
            cout << "Enter Quantity: ";
            cin >> qty;

            bool found = false;
            for (auto& s : market) {
                if (s.symbol == symbol) {
                    double cost = s.price * qty;
                    if (userBalance >= cost) {
                        userBalance -= cost;
                        
                        // NEW: Add to portfolio logic
                        bool alreadyOwned = false;
                        for(auto& h : myPortfolio) {
                            if(h.symbol == symbol) {
                                // Update average cost
                                double totalValue = (h.quantity * h.avgCost) + cost;
                                h.quantity += qty;
                                h.avgCost = totalValue / h.quantity;
                                alreadyOwned = true;
                                break;
                            }
                        }
                        if(!alreadyOwned) {
                            myPortfolio.push_back({symbol, qty, s.price});
                        }

                        cout << "✅ Bought " << qty << " shares of " << s.name << "!" << endl;
                    } else {
                        cout << "❌ Insufficient Funds!" << endl;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "❌ Symbol not found!" << endl;
        }
        else if (choice == 3) {
            showPortfolio(myPortfolio, userBalance);
        }
        else if (choice == 4) {
            isRunning = false;
            cout << "Exiting. Good luck with the market!" << endl;
        } else {
            cout << "Invalid Option." << endl;
        }
    }
    return 0;
}
