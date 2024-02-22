#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

void mainMenu();

class Passenger{
private:
    static int count_num;
    string name;
    string surname;
    string gender;
    int passenger_number;

public:
    Passenger(const string& name1, const string& surname1, string& gender1){
        name = name1;
        surname = surname1;
        gender = gender1;
        passenger_number = count_num++;
    };

    int get_passenger_number() const{
        return passenger_number;
    }

    string get_surname() const{
        return surname;
    }

    string get_name() const{
        return name;
    }

    string get_gender() const{
        return gender;
    }
};
int Passenger::count_num = 1;

class Flight{
private:
    string Flight_No;
    vector<Passenger> passengerList;
    int Number_of_Passenger;
    int Max_Seat;
    int passenger_num=0;

public:
    Flight(const string& flightNo, int maxSeat, int num=1){
        Flight_No = flightNo;
        Max_Seat = maxSeat;
        Number_of_Passenger = 0;
        passenger_num = passenger_num + num;
    };

    bool ReserveSeat(const Passenger& passenger){
        if(Number_of_Passenger< Max_Seat){
            passengerList.push_back(passenger);
            Number_of_Passenger++;

            return true;
        }
        else{
            cout<<"There are no available seats to make a reservation."<<endl;

            return false;
        }
    }

    bool CancelReservation(const int FlightNum){
        auto it = find_if(passengerList.begin(), passengerList.end(), [FlightNum](const Passenger& p){return p.get_passenger_number()==FlightNum;});

        if (it !=passengerList.end()){
            passengerList.erase(it);
            Number_of_Passenger--;
            return true;
        }
        else{
            cout<<"The passenger with passenger number"<<  FlightNum <<"was not found in the reservation list."<<endl;
            return false;
        }
    }

    int numberOfPassengers() const{
        return Number_of_Passenger;
    }

    vector<Passenger> getPassengerList() const {
        return passengerList;
    }

    void printPassengers(){
        vector<Passenger> List = passengerList;
        sort(List.begin(), List.end(),[](const Passenger& a, const Passenger& b) {return a.get_surname() < b.get_surname(); });
        cout<<"-------------------------------------------------------------"<<endl;
        cout<<"List of passengers who made reservations (sorted by surname):"<<endl;

        for(const auto& passenger : List){
            cout<<"-------------------------------------------------------------"<<endl;
            cout<<"Passenger Number: "<<passenger.get_passenger_number()<<endl;
            cout<<"Name: "<<passenger.get_name()<<endl;
            cout<<"Surname: "<<passenger.get_surname()<<endl;
            cout<<"Gender: "<<passenger.get_gender()<<endl;
        }
    }
};

int main(){
    string flightNo;
    int maxSeats;

    cout<<"Enter Flight No:";
    cin>>flightNo;

    cout<<"Enter Maximum Number of Seats:";
    cin>>maxSeats;

    Flight testflight(flightNo,maxSeats);

    while(true){
        mainMenu();

        int choice;
        cin>>choice;

        switch (choice) {
            case 1:{
                string name;
                string surname;
                string gender;

                cout<<"-------------------------------------------------------------"<<endl;
                cout<<"Enter Passenger Information:"<<endl;

                cout<<"Name: ";
                cin>>name;

                cout<<"Surname: ";
                cin>>surname;

                while (true){
                    cout<<"What is your Gender?"<<endl<<"1. Male"<<endl<<"2. Female"<<endl;
                    int gen;
                    cin>>gen;
                    if(gen == 1){
                        gender = "Male";
                        break;
                    }
                    else if(gen == 2){
                        gender = "Female";
                        break;
                    }
                    else{
                        cout << "Invalid login" << endl;
                    }
                }
                Passenger passenger(name, surname,gender);
                testflight.ReserveSeat(passenger);
                cout<<"It was booked as passenger number "<<passenger.get_passenger_number()<<endl;
                break;
            }

            case 2:{
                int cancelled_num;
                cout<<"-------------------------------------------------------------"<<endl;
                cout<<"Enter the passenger number of the passenger whose reservation will be canceled: ";
                cin>>cancelled_num;
                cout<<"Reservation for passenger number"<< cancelled_num <<"has been canceled"<<endl;
                testflight.CancelReservation(cancelled_num);
                break;
            }

            case 3:{
                int check_num;
                cout<<"-------------------------------------------------------------"<<endl;
                cout<<"Enter Passenger Number:";
                cin>>check_num;

                const int Number_of_Passengers = testflight.numberOfPassengers();

                if(Number_of_Passengers > 0){
                    vector<Passenger> passengers = testflight.getPassengerList();

                    auto it = std::find_if(passengers.begin(), passengers.end(),[check_num](const Passenger& p) { return p.get_passenger_number() == check_num; });

                    if(it != passengers.end()){
                        cout<<"Passenger Number: "<<it->get_passenger_number()<<endl;
                        cout<<"Name: "<<it->get_name()<<endl;
                        cout<<"Surname: "<<it->get_surname()<<endl;
                        cout<<"Gender: "<<it->get_gender()<<endl;
                    }
                    else{
                        cout<<"No passenger with the specified passenger number was found."<<endl;
                    }

                }
                else{
                    cout<<"Reservation not found."<<endl;
                }
                break;
            }

            case 4:{
                testflight.printPassengers();
                break;
            }

            case 5:{
                cout<<"-------------------------------------------------------------"<<endl;
                cout<<"Exiting..."<<endl;
                break;
            }

            default:{
                cout<<"-------------------------------------------------------------"<<endl;
                cout<<"Invalid option. Try again."<<endl;
                break;
            }
        }
    }

    return 0;
}

void mainMenu(){
    cout<<"-------------------------------------------------------------"<<endl;
    cout << setfill(' ') << setw(15) << right << "Flight Menu" << endl;
    cout << setw(20) << left << "1. Reserve a Ticket" << endl;
    cout << setw(20) << left << "2. Cancel Reservation" << endl;
    cout << setw(20) << left << "3. Check Reservation" << endl;
    cout << setw(20) << left << "4. Display Passengers" << endl;
    cout << setw(20) << left << "5. Exit" << endl;
}