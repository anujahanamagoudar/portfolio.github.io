#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

struct Application {
    string name;
    int meritScore;
    string applicationTime;
    string documentStatus; // Verified or Pending

    Application(string n, int m, string t, string d)
        : name(n), meritScore(m), applicationTime(t), documentStatus(d) {}

    bool operator<(const Application &other) const {
        return meritScore < other.meritScore; // Higher merit scores get higher priority
    }
};

class SeatAllocator {
private:
    int totalSeats;
    map<string, string> allocatedSeats; // Student Name -> Seat Status

public:
    SeatAllocator(int seats) : totalSeats(seats) {}

    bool allocateSeat(const Application &app) {
        if (totalSeats > 0 && app.documentStatus == "Verified") {
            allocatedSeats[app.name] = "Seat Allocated";
            totalSeats--;
            return true;
        } else {
            allocatedSeats[app.name] = "Seat Not Allocated";
            return false;
        }
    }

    void displayAllocation() {
        cout << "\nSeat Allocation Results:\n";
        for (const auto &entry : allocatedSeats) {
            cout << "Name: " << entry.first << " - " << entry.second << endl;
        }
    }
};

int main() {
    priority_queue<Application> applicationQueue;
    SeatAllocator seatAllocator(5); // Set the number of available seats

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Submit Application\n";
        cout << "2. Process Application\n";
        cout << "3. Display Seat Allocation\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, time, docStatus;
            int score;
            cin.ignore();
            cout << "Enter Applicant Name: ";
            getline(cin, name);
            cout << "Enter Merit Score: ";
            cin >> score;
            cin.ignore();
            cout << "Enter Application Time: ";
            getline(cin, time);
            cout << "Enter Document Status (Verified/Pending): ";
            getline(cin, docStatus);
            applicationQueue.push(Application(name, score, time, docStatus));
            cout << "Application submitted successfully.\n";
            break;
        }
        case 2: {
            if (applicationQueue.empty()) {
                cout << "No applications to process.\n";
            } else {
                Application topApp = applicationQueue.top();
                applicationQueue.pop();
                cout << "Processing Application:\n";
                cout << "Name: " << topApp.name
                     << ", Merit Score: " << topApp.meritScore
                     << ", Application Time: " << topApp.applicationTime
                     << ", Document Status: " << topApp.documentStatus << endl;

                if (seatAllocator.allocateSeat(topApp)) {
                    cout << "Seat allocated successfully.\n";
                } else {
                    cout << "Seat allocation failed. Ensure documents are verified or seats are available.\n";
                }
            }
            break;
        }
        case 3:
            seatAllocator.displayAllocation();
            break;
        case 4:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
