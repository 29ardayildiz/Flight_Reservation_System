#ifndef FLIGHT_RESERVATION_SYSTEM_RESERVATIONSYSTEM_H
#define FLIGHT_RESERVATION_SYSTEM_RESERVATIONSYSTEM_H
#include <iostream>

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
    string destination;
    vector<Passenger> passengerList;
    int Number_of_Passenger;
    int Max_Seat;
    int passenger_num=0;

public:
    Flight(const string& flightNo, const string& Destination ,int maxSeat=40, int num=1){
        Flight_No = flightNo;
        destination = Destination;
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

    bool isFliyingTo(const string& destination) const{
        string dest = this->destination;
        string input = destination;

        for (auto& c : dest) {
            c = toLower(c);
        }

        for (auto& c : input) {
            c = toLower(c);
        }

        return dest == input;
    }

    string getFlightNo() const {
        return Flight_No;
    }

    string getDestination() const {
        return destination;
    }

    int get_MaxSeat() const{
        return Max_Seat;
    }
};

class FlightManager {
private:
    vector<Flight> flights;

public:
    void addFlight(const Flight& flight){
        flights.push_back(flight);
    }

    void removeFlight(const string& flightNumber){
        auto it = std::find_if(flights.begin(), flights.end(),[flightNumber](const Flight& flight) { return flight.getFlightNo() == flightNumber; });

        if (it != flights.end()) {
            flights.erase(it);
            std::cout << "Flight " << flightNumber << " removed successfully." << std::endl;
        } else {
            std::cout << "Flight " << flightNumber << " not found." << std::endl;
        }
    }

    void listAllFlights(){
        cout<<"-------------------------------------------------------------"<<endl;
        cout<<"Flights:"<<endl;
        for(const Flight& f: flights){
            cout<<"Flight No: "<< f.getFlightNo()<<endl;
            cout<<"Destination: "<< f.getDestination()<<endl;
            cout<<"Maximum Number of Seats: "<< f.get_MaxSeat()<<endl;
            cout<<"Number of Passenger: "<<f.numberOfPassengers()<<endl;
            cout<<"-------------------------------------------------------------"<<endl;
        }
    }

    Flight getFlightByNumber(const string& flightNumber){

    }

    Flight getFlightByDestination(const std::string& destination) const {

    }

};



#endif //FLIGHT_RESERVATION_SYSTEM_RESERVATIONSYSTEM_H
