#include "../include/bookingsystem.h"

BookingSystem::BookingSystem() {}

void BookingSystem::addFlight(Flight f) {
    flights.insert(f);
}

bool BookingSystem::bookSeat(string flightID, Passenger p, string seat) {
    passengers.insert(p);

    Action a;
    a.type = "BOOK";
    a.passengerID = p.passengerID;
    a.flightID = flightID;
    a.newSeat = seat;
    undo.push(a);

    return true;
}

bool BookingSystem::cancelSeat(string flightID, string passengerID) {
    Action a;
    a.type = "CANCEL";
    a.passengerID = passengerID;
    a.flightID = flightID;
    undo.push(a);

    return true;
}

void BookingSystem::undoLastAction() {
    if (undo.isEmpty()) return;
    Action a = undo.pop();
}

vector<Flight> BookingSystem::getAllFlights() {
    vector<Flight> list;
    flights.getAllFlights(list);
    return list;
}
