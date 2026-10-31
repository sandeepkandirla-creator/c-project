#include <iostream>
#include <string>

#include <iomanip>
using namespace std;

// ===============================
// Room Class
// ===============================
class Room {
private:
    int roomNumber;
    string roomType;
    double price;
    bool booked;

public:
    Room(int number, string type, double cost) {
        roomNumber = number;
        roomType = type;
        price = cost;
        booked = false;
    }

    int getRoomNumber() {
        return roomNumber;
    }

    string getRoomType() {
        return roomType;
    }

    double getPrice() {
        return price;
    }

    bool isBooked() {
        return booked;
    }

    void bookRoom() {
        booked = true;
    }

    void cancelRoom() {
        booked = false;
    }

    void displayRoom() {
        cout << left << setw(12) << roomNumber
             << setw(15) << roomType
             << "Rs." << setw(10) << price
             << (booked ? "Booked" : "Available") << endl;
    }
};

// ===============================
// Customer Class
// ===============================
class Customer {
private:
    int bookingID;
    string name;
    string phone;
    int roomNumber;
    int days;
    double totalBill;

public:
    Customer(int id, string n, string p, int room, int d, double bill) {
        bookingID = id;
        name = n;
        phone = p;
        roomNumber = room;
        days = d;
        totalBill = bill;
    }

    int getBookingID() {
        return bookingID;
    }

    string getName() {
        return name;
    }

    int getRoomNumber() {
        return roomNumber;
    }

    double getTotalBill() {
        return totalBill;
    }

    void displayCustomer() {
        cout << "\n---------- Booking Details ----------\n";
        cout << "Booking ID  : " << bookingID << endl;
        cout << "Customer    : " << name << endl;
        cout << "Phone       : " << phone << endl;
        cout << "Room Number : " << roomNumber << endl;
        cout << "Days        : " << days << endl;
        cout << "Total Bill  : Rs." << fixed << setprecision(2)
             << totalBill << endl;
        cout << "-------------------------------------\n";
    }
};

// ===============================
// Hotel Class
// ===============================
class Hotel {
private:
    vector<Room> rooms;
    vector<Customer> customers;
    int nextBookingID;

public:
    Hotel() {
        nextBookingID = 1001;

        // Room Number, Type, Price per Day
        rooms.push_back(Room(101, "Single", 1500));
        rooms.push_back(Room(102, "Single", 1500));
        rooms.push_back(Room(201, "Double", 2500));
        rooms.push_back(Room(202, "Double", 2500));
        rooms.push_back(Room(301, "Deluxe", 4000));
        rooms.push_back(Room(302, "Deluxe", 4000));
    }

    // Display all rooms
    void displayRooms() {
        cout << "\n============== ROOM DETAILS ==============\n";

        cout << left << setw(12) << "Room No."
             << setw(15) << "Room Type"
             << setw(14) << "Price/Day"
             << "Status" << endl;

        cout << "-------------------------------------------\n";

        for (int i = 0; i < rooms.size(); i++) {
            rooms[i].displayRoom();
        }

        cout << "===========================================\n";
    }

    // Book a room
    void bookRoom() {
        string name, phone;
        int roomNumber, days;

        cout << "\nEnter Customer Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        displayRooms();

        cout << "\nEnter Room Number: ";
        cin >> roomNumber;

        int roomIndex = -1;

        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].getRoomNumber() == roomNumber) {
                roomIndex = i;
                break;
            }
        }

        if (roomIndex == -1) {
            cout << "\nRoom not found!\n";
            return;
        }

        if (rooms[roomIndex].isBooked()) {
            cout << "\nSorry! Room is already booked.\n";
            return;
        }

        cout << "Enter Number of Days: ";
        cin >> days;

        if (days <= 0) {
            cout << "\nInvalid number of days!\n";
            return;
        }

        double bill = rooms[roomIndex].getPrice() * days;

        rooms[roomIndex].bookRoom();

        Customer customer(
            nextBookingID,
            name,
            phone,
            roomNumber,
            days,
            bill
        );

        customers.push_back(customer);

        cout << "\n====================================\n";
        cout << "       ROOM BOOKED SUCCESSFULLY!\n";
        cout << "====================================\n";

        cout << "Booking ID : " << nextBookingID << endl;
        cout << "Customer   : " << name << endl;
        cout << "Room No.   : " << roomNumber << endl;
        cout << "Room Type  : " << rooms[roomIndex].getRoomType() << endl;
        cout << "Days       : " << days << endl;
        cout << "Total Bill : Rs." << fixed << setprecision(2)
             << bill << endl;

        nextBookingID++;
    }

    // View all bookings
    void viewBookings() {
        if (customers.empty()) {
            cout << "\nNo bookings available.\n";
            return;
        }

        cout << "\n========== ALL BOOKINGS ==========\n";

        for (int i = 0; i < customers.size(); i++) {
            customers[i].displayCustomer();
        }
    }

    // Search booking
    void searchBooking() {
        int id;

        cout << "\nEnter Booking ID: ";
        cin >> id;

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getBookingID() == id) {
                customers[i].displayCustomer();
                return;
            }
        }

        cout << "\nBooking not found!\n";
    }

    // Cancel booking
    void cancelBooking() {
        int id;

        cout << "\nEnter Booking ID to cancel: ";
        cin >> id;

        for (int i = 0; i < customers.size(); i++) {

            if (customers[i].getBookingID() == id) {

                int roomNumber = customers[i].getRoomNumber();

                for (int j = 0; j < rooms.size(); j++) {
                    if (rooms[j].getRoomNumber() == roomNumber) {
                        rooms[j].cancelRoom();
                        break;
                    }
                }

                customers.erase(customers.begin() + i);

                cout << "\nBooking cancelled successfully!\n";
                cout << "Room " << roomNumber
                     << " is now available.\n";

                return;
            }
        }

        cout << "\nBooking ID not found!\n";
    }

    // Generate bill
    void generateBill() {
        int id;

        cout << "\nEnter Booking ID: ";
        cin >> id;

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getBookingID() == id) {

                cout << "\n========== HOTEL BILL ==========\n";
                customers[i].displayCustomer();
                cout << "Thank you for staying with us!\n";

                return;
            }
        }

        cout << "\nBooking not found!\n";
    }
};

// ===============================
// Main Function
// ===============================
int main() {

    Hotel hotel;

    int choice;

    do {

        cout << "\n\n";
        cout << "============================================\n";
        cout << "        HOTEL ROOM BOOKING SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Display Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. View All Bookings\n";
        cout << "4. Search Booking\n";
        cout << "5. Cancel Booking\n";
        cout << "6. Generate Bill\n";
        cout << "7. Exit\n";
        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            hotel.displayRooms();
            break;

        case 2:
            hotel.bookRoom();
            break;

        case 3:
            hotel.viewBookings();
            break;

        case 4:
            hotel.searchBooking();
            break;

        case 5:
            hotel.cancelBooking();
            break;

        case 6:
            hotel.generateBill();
            break;

        case 7:
            cout << "\nThank you for using Hotel Room Booking System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}