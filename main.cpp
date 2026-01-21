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

void showPortfolio(const vector<Holding>& myStocks, double balance) {
    cout << "\n--- 💼 MY PORTFOLIO ---" << endl;
    cout << "Cash Balance: PKR " << fixed << setprecision(2) << balance << endl;
    
    if (myStocks.empty()) {
        cout << "(You don't own any stocks)" << endl;
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

// Helper to find current market price of a stock
double getMarketPrice(const vector<Stock>& market, string symbol) {
    for(const auto& s : market) {
        if(s.symbol == symbol) return s.price;
    }
    return 0.0;
}

int main() {
    srand(time(0));
    double userBalance = 100000.00;
    vector<Holding> myPortfolio;

    vector<Stock> market = {
        {"OGDC", "Oil & Gas Dev", 118.50},
        {"TRG", "TRG Pakistan", 88.25},
        {"LUCK", "Lucky Cement", 650.00},
        {"SYS", "Systems Ltd", 430.75}
    };

    bool isRunning = true;
    int choice;

    cout << "Welcome to Quantum Park's PSX Simulator (v3.0)!" << endl;

    while (isRunning) {
        cout << "\n1. View Market" << endl;
        cout << "2. Buy Stock" << endl;
        cout << "3. Sell Stock (NEW)" << endl;
        cout << "4. View Portfolio" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            // Market fluctuation
            for (auto& s : market) {
                double change = (rand() % 10 - 5);
                s.price += change;
                if (s.price < 1.0) s.price = 1.0;
            }
            showMarket(market);
        }
        else if (choice == 2) {
            // BUY LOGIC
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
                        
                        // Add to portfolio
                        bool alreadyOwned = false;
                        for(auto& h : myPortfolio) {
                            if(h.symbol == symbol) {
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
            // SELL LOGIC
            string symbol;
            int qty;
            cout << "Enter Symbol to Sell: ";
            cin >> symbol;

            // Check if user owns it
            int index = -1;
            for(int i=0; i<myPortfolio.size(); i++) {
                if(myPortfolio[i].symbol == symbol) {
                    index = i;
                    break;
                }
            }

            if(index != -1) {
                cout << "You own " << myPortfolio[index].quantity << " shares. Enter Qty to Sell: ";
                cin >> qty;

                if(qty <= myPortfolio[index].quantity) {
                    double currentPrice = getMarketPrice(market, symbol);
                    double revenue = currentPrice * qty;
                    
                    userBalance += revenue;
                    myPortfolio[index].quantity -= qty;
                    
                    cout << "✅ Sold " << qty << " shares for " << revenue << " PKR!" << endl;

                    // Remove from list if 0 left
                    if(myPortfolio[index].quantity == 0) {
                        myPortfolio.erase(myPortfolio.begin() + index);
                    }
                } else {
                    cout << "❌ You don't have that many shares!" << endl;
                }
            } else {
                cout << "❌ You don't own this stock!" << endl;
            }
        }
        else if (choice == 4) {
            showPortfolio(myPortfolio, userBalance);
        }
        else if (choice == 5) {
            isRunning = false;
            cout << "Exiting. Happy Trading!" << endl;
        } else {
            cout << "Invalid Option." << endl;
        }
    }
    return 0;
}
