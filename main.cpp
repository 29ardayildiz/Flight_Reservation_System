#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

void TopLevelMenu();
void Second_LevelMenu();
char toLower(char c);
void toLower(string& str);

class Passenger {
private:
    static int count_num;
    string name;
    string surname;
    string gender;
    int passenger_number;

public:
    Passenger(const string& name1, const string& surname1, const string& gender1)
            : name(name1), surname(surname1), gender(gender1), passenger_number(count_num++) {}

    int get_passenger_number() const {
        return passenger_number;
    }

    string get_surname() const {
        return surname;
    }

    string get_name() const {
        return name;
    }

    string get_gender() const {
        return gender;
    }
};

int Passenger::count_num = 1;

class Flight {
private:
    string Flight_No;
    string destination;
    vector<Passenger> passengerList;
    int Number_of_Passenger;
    int Max_Seat;
    vector<pair<int, char>> RSeats;

    bool isOccupied(int row, char seatLabel) const {
        for (const auto& seat : RSeats) {
            if (seat.first == row && seat.second == seatLabel) {
                return true;
            }
        }
        return false;
    }

    string getSeatLabel() const {
        int rowNumber;
        char seatLetter;

        cout << "Select Row: ";
        cin >> rowNumber;

        cout << "Select Column: ";
        cin >> seatLetter;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter numeric values for row and column again." << endl;
            cout << "Select Row: ";
            cin >> rowNumber;
            cout << "Select Column: ";
            cin >> seatLetter;
        }

        return to_string(rowNumber) + seatLetter;
    }

public:
    Flight(const string& flightNo, const string& Destination, int maxSeat = 40)
            : Flight_No(flightNo), destination(Destination), Max_Seat(maxSeat), Number_of_Passenger(0) {}

    bool ReserveSeat(const Passenger& passenger) {
        SeatPlanDisplay();

        if (numberOfPassengers() >= Max_Seat) {
            cout << "Sorry, the flight is fully booked. No more seats available." << endl;
            return false;
        }

        string seatLabel = getSeatLabel();

        if (!isOccupied(seatLabel[0] - '0', seatLabel[1])) {
            passengerList.push_back(passenger);
            RSeats.push_back({seatLabel[0] - '0', seatLabel[1]});
            cout << "Seat reserved for " << passenger.get_name() << " " << passenger.get_surname() << " on Flight " << Flight_No << endl;
            return true;
        } else {
            cout << "Sorry, the seat is already occupied." << endl;
            return false;
        }
    }

    bool CancelReservation(int passengerNumber) {
        auto it = find_if(passengerList.begin(), passengerList.end(),
                          [passengerNumber](const Passenger& passenger) { return passenger.get_passenger_number() == passengerNumber; });

        if (it != passengerList.end()) {
            int row = RSeats[it - passengerList.begin()].first;
            char seatLabel = RSeats[it - passengerList.begin()].second;

            passengerList.erase(it);
            RSeats.erase(RSeats.begin() + (it - passengerList.begin()));

            cout << "Reservation canceled for Passenger Number " << passengerNumber << " on Flight " << Flight_No << endl;
            return true;
        } else {
            cout << "Passenger with Number " << passengerNumber << " not found on this flight." << endl;
            return false;
        }
    }

    void viewPassengerList() const {
        cout << setw(5) << left << "Seat" << setw(15) << "Passenger Name" << setw(7) << "Gender" << setw(1) << endl;
        cout << "----|---------------|------" << endl;

        for (size_t i = 0; i < passengerList.size(); ++i) {
            string seatLabel = to_string(RSeats[i].first) + RSeats[i].second;
            cout << setw(5) << left << seatLabel.substr(0, 5) << setw(15) << passengerList[i].get_name() + " " + passengerList[i].get_surname() << setw(7) << passengerList[i].get_gender() << setw(1) << endl;
        }
    }

    int numberOfPassengers() const {
        return passengerList.size();
    }

    bool isFlyingTo(const string& destination) const {
        string dest = this->destination;
        string input = destination;

        toLower(dest);
        toLower(input);

        return dest == input;
    }

    string getFlightNo() const {
        return Flight_No;
    }

    string getDestination() const {
        return destination;
    }

    int get_MaxSeat() const {
        return Max_Seat;
    }

    void SeatPlanDisplay() const {
        cout << "-------------Front------------" << endl;
        for (int row = 1; row <= Max_Seat / 4; ++row) {
            for (char seatLabel : {'A', 'B', 'C', 'D'}) {
                cout << row << seatLabel << " " << (isOccupied(row, seatLabel) ? "X" : "O") << " | ";
            }
            cout << endl;
        }
    }
};

class FlightManager {
private:
    vector<Flight> flights;

public:
    void addFlight(const Flight& flight) {
        flights.push_back(flight);
    }

    void removeFlight(const string& flightNumber) {
        auto it = find_if(flights.begin(), flights.end(), [flightNumber](const Flight& flight) { return flight.getFlightNo() == flightNumber; });

        if (it != flights.end()) {
            flights.erase(it);
            cout << "Flight " << flightNumber << " removed successfully." << endl;
        } else {
            cout << "Flight " << flightNumber << " not found." << endl;
        }
    }

    void listAllFlights() const {
        cout << "Flights:" << endl << endl;
        for (const Flight& f : flights) {
            cout << "Flight No: " << f.getFlightNo() << endl;
            cout << "Destination: " << f.getDestination() << endl;
            cout << "Maximum Number of Seats: " << f.get_MaxSeat() << endl;
            cout << "Number of Passenger: " << f.numberOfPassengers() << endl << endl;
        }
    }

    Flight getFlightByNumber(const string& flightNumber) const {
        auto it = find_if(flights.begin(), flights.end(), [flightNumber](const Flight& flight) { return flight.getFlightNo() == flightNumber; });

        if (it != flights.end()) {
            return *it;
        } else {
            return Flight("", "");
        }
    }

    Flight getFlightByDestination(const string& destination) const {
        auto it = find_if(flights.begin(), flights.end(), [destination](const Flight& flight) { return flight.getDestination() == destination; });

        if (it != flights.end()) {
            return *it;

        } else {
            return Flight("", "");
        }
    }
};

int main() {
    FlightManager FM;

    int choice;
    do {
        TopLevelMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string fN, d;
                int maxSeat;

                cout << "Enter Flight Number: ";
                cin >> fN;
                cout << "Enter Destination: ";
                cin >> d;

                int cw = 1;
                cout << "Enter Maximum Seats: ";
                while (cw) {
                    cin >> maxSeat;
                    if (maxSeat % 2 == 0 && maxSeat <= 80) {
                        cw = 0;
                    } else {
                        cout << "Wrong Number of Seats Entry (Must be even and less than 80)." << endl << "Entry again." << endl;
                        cout << "Enter Maximum Seats: ";
                    }
                }

                Flight af(fN, d, maxSeat);
                FM.addFlight(af);

                cout << "Flight Added" << endl;
                break;
            }

            case 2: {
                string fN;

                cout << "Enter Flight Number: ";
                cin >> fN;

                FM.removeFlight(fN);
                break;
            }

            case 3:
                cout << "-------------------------------------------------------------" << endl;
                FM.listAllFlights();
                break;

            case 4: {
                string fN;

                cout << "Enter Flight Number: ";
                cin >> fN;

                Flight sF = FM.getFlightByNumber(fN);

                if (!sF.getFlightNo().empty()) {
                    int c = 1;
                    do {
                        Second_LevelMenu();

                        int pChoice;
                        cout << "Enter your choice: ";
                        cin >> pChoice;

                        switch (pChoice) {
                            case 1: {
                                string name, surname, gender;

                                cout << "Enter Passenger Information:" << endl;
                                cout << "Name: ";
                                cin >> name;

                                cout << "Surname: ";
                                cin >> surname;

                                while (true) {
                                    cout << "What is your Gender?" << endl << "1. Male" << endl << "2. Female" << endl;
                                    int gen;
                                    cin >> gen;
                                    if (gen == 1) {
                                        gender = "Male";
                                        break;
                                    } else if (gen == 2) {
                                        gender = "Female";
                                        break;
                                    } else {
                                        cout << "Invalid input" << endl;
                                    }
                                }

                                Passenger passenger(name, surname, gender);
                                if (sF.ReserveSeat(passenger)) {
                                    cout << "It was booked as passenger number " << passenger.get_passenger_number() << endl;
                                }

                                break;
                            }

                            case 2: {
                                int cancelled_num;
                                cout << "Enter the passenger number of the passenger whose reservation will be canceled: ";
                                cin >> cancelled_num;

                                sF.CancelReservation(cancelled_num);
                                break;
                            }

                            case 3:
                                sF.viewPassengerList();
                                break;

                            case 4:
                                c = 0;
                                break;

                            default:
                                cout << "Invalid choice. Try again." << endl;
                        }
                    } while (c);
                } else {
                    cout << "Invalid flight number. Please try again." << endl;
                }

                break;
            }

            case 5:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

void TopLevelMenu() {
    cout << "-------------------------------------------------------------" << endl;
    cout << setfill(' ') << setw(10) << right << "Flight Management Menu" << endl;
    cout << setw(20) << left << "1. Add a Flight" << endl;
    cout << setw(20) << left << "2. Remove a Flight" << endl;
    cout << setw(20) << left << "3. List All Flight" << endl;
    cout << setw(20) << left << "4. Select a Flight and Manage passengers" << endl;
    cout << setw(20) << left << "5. Exit" << endl;
}

void Second_LevelMenu() {
    cout << "-------------------------------------------------------------" << endl;
    cout << setfill(' ') << setw(15) << right << "Flight Menu" << endl;
    cout << setw(20) << left << "1. Reserve a Ticket" << endl;
    cout << setw(20) << left << "2. Cancel Reservation" << endl;
    cout << setw(20) << left << "3. View Passenger List" << endl;
    cout << setw(20) << left << "4. Back to Flight Management Menu" << endl;
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

void toLower(string& str) {
    for (char& c : str) {
        c = toLower(c);
    }
}