#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class Ticket {
private:
    string boarding, destination;
    float distance, fare;
    string driverID, conductorID, depot;
    string dateTime;

public:
    Ticket() {}

    void getDetails() {
        cout << "Enter Boarding Point : ";
        cin >> boarding;
        cout << "Enter Destination    : ";
        cin >> destination;
        cout << "Enter Distance (km)  : ";
        cin >> distance;

        fare = distance * 2.5; // ₹2.5 per km

        // Get current date & time
        time_t now = time(0);
        dateTime = ctime(&now);
        dateTime.pop_back(); // remove newline
    }

    void setBusDetails(string dID, string cID, string dep) {
        driverID = dID;
        conductorID = cID;
        depot = dep;
    }

    float getFare() const { return fare; }

    void printTicket() const {
        cout << "\n----------------------------";
        cout << "\n       RTC BUS TICKET";
        cout << "\n----------------------------";
        cout << "\nBoarding Point : " << boarding;
        cout << "\nDestination    : " << destination;
        cout << "\nDistance (km)  : " << distance;
        cout << "\nFare (Rs)      : " << fare;
        cout << "\nDate & Time    : " << dateTime;
        cout << "\nDriver ID      : " << driverID;
        cout << "\nConductor ID   : " << conductorID;
        cout << "\nDepot Name     : " << depot;
        cout << "\n----------------------------\n";
    }

    void saveToFile() const {
        ofstream file("tickets.txt", ios::out | ios::app); // we’ll handle append manually below
        if (!file) {
            cout << "Error opening file!\n";
            return;
        }

        file << "Boarding: " << boarding
             << ", Destination: " << destination
             << ", Distance: " << distance << " km"
             << ", Fare: Rs." << fare
             << ", DateTime: " << dateTime
             << ", Driver: " << driverID
             << ", Conductor: " << conductorID
             << ", Depot: " << depot << endl;
        file.close();
    }
};

class Waybill {
private:
    float totalCollection = 0;
    int ticketCount = 0;

public:
    void addTicket(float fare) {
        totalCollection += fare;
        ticketCount++;
    }

    void printWaybill() const {
        cout << "\n===================================";
        cout << "\n          DAILY WAYBILL";
        cout << "\n===================================";
        cout << "\nTotal Tickets   : " << ticketCount;
        cout << "\nTotal Collection: Rs. " << totalCollection;
        cout << "\n===================================\n";

        ofstream file;
        file.open("waybill.txt", ios::out | ios::app); // append manually
        if (file) {
            time_t now = time(0);
            file << "Date: " << ctime(&now);
            file << "Total Tickets: " << ticketCount << "\n";
            file << "Total Collection: Rs. " << totalCollection << "\n";
            file << "-----------------------------------\n";
            file.close();
        }
    }

    void clearFiles() {
        ofstream file1("tickets.txt");
        ofstream file2("waybill.txt");
        file1.close();
        file2.close();

        totalCollection = 0;
        ticketCount = 0;
        cout << "\nAll data cleared successfully!\n";
    }
};

// ------------------- MAIN FUNCTION -------------------
int main() {
    string driverID, conductorID, depot;
    int choice;
    Waybill wb;

    cout << "Enter Driver ID      : ";
    cin >> driverID;
    cout << "Enter Conductor ID   : ";
    cin >> conductorID;
    cout << "Enter Depot Name     : ";
    cin >> depot;

    do {
        cout << "\n========== RTC BUS TICKETING ==========\n";
        cout << "1. Print New Ticket\n";
        cout << "2. Print Waybill (Show Summary)\n";
        cout << "3. Clear File Data\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Ticket t;
            t.getDetails();
            t.setBusDetails(driverID, conductorID, depot);
            t.printTicket();
            t.saveToFile();
            wb.addTicket(t.getFare());
        }
        else if (choice == 2) {
            wb.printWaybill();
        }
        else if (choice == 3) {
            wb.clearFiles();
        }
        else if (choice == 4) {
            cout << "\nExiting the system. Have a nice day!\n";
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}