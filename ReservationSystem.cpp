#include "ReservationSystem.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

    FlightManager FM;

    int b=1;

    while(b){
        TopLevelMenu();

        int choice;
        cin>>choice;

        if(choice==1){
            string fN, d;
            int maxSeat;

            cout << "Enter Flight Number: ";
            cin >> fN;
            cout << "Enter Destination: ";
            cin >> d;

            int cw=1;
            cout << "Enter Maximum Seats: ";
            while(cw){
                cin >> maxSeat;
                if(maxSeat%2==0 && maxSeat<=80){
                    cw=0;
                }
            }

            Flight af(fN, d, maxSeat);
            FM.addFlight(af);
        }

        else if(choice==2){
            string fN;

            cout << "Enter Flight Number: ";
            cin >> fN;

            FM.removeFlight(fN);
        }

        else if(choice==3){
            FM.listAllFlights();
        }

        else if(choice==4){
            string fN;

            cout << "Enter Flight Number: ";
            cin >> fN;

            Flight sF = FM.getFlightByNumber(fN);

            int c=1;

            if(!sF.getFlightNo().empty()){
                while(c){
                    Second_LevelMenu();

                    int pChoice;
                    cin>>pChoice;

                    if(pChoice==1){
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
                        sF.ReserveSeat(passenger);
                        cout<<"It was booked as passenger number "<<passenger.get_passenger_number()<<endl;
                    }

                    else if(pChoice==2){
                        int cancelled_num;
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"Enter the passenger number of the passenger whose reservation will be canceled: ";
                        cin>>cancelled_num;
                        cout<<"Reservation for passenger number"<< cancelled_num <<"has been canceled"<<endl;
                        sF.CancelReservation(cancelled_num);
                    }

                    else if(pChoice==3){
                        sF.printPassengers();
                    }

                    else if(pChoice==4){
                        c=0;
                    }
                }
            }

            else{
                cout << "Invalid flight number. Please try again." << endl;
            }
        }

        else if(choice==5){
            cout<<"-------------------------------------------------------------"<<endl;
            cout<<"Exiting..."<<endl;
            b=0;
        }
    }

    return 0;
}

void TopLevelMenu(){
    cout<<"-------------------------------------------------------------"<<endl;
    cout << setfill(' ') << setw(10) << right << "Flight Management Menu" << endl;
    cout << setw(20) << left << "1. Add a Flight" << endl;
    cout << setw(20) << left << "2. Remove a Flight" << endl;
    cout << setw(20) << left << "3. List All Flight" << endl;
    cout << setw(20) << left << "4. Select a Flight and Manage passengers" << endl;
    cout << setw(20) << left << "5. Exit" << endl;
}

void Second_LevelMenu(){
    cout<<"-------------------------------------------------------------"<<endl;
    cout << setfill(' ') << setw(15) << right << "Flight Menu" << endl;
    cout << setw(20) << left << "1. Reserve a Ticket" << endl;
    cout << setw(20) << left << "2. Cancel Reservation" << endl;
    cout << setw(20) << left << "3. View Passenger List" << endl;
    cout << setw(20) << left << "4.Back to Flight Management Menu" << endl;
    cout << setw(20) << left << "5. Exit" << endl;
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}