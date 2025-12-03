#include "../include/Flight.h"

Flight::Flight() {
    flightID = "";
    origin = "";
    destination = "";
    totalSeats = 0;
    availableSeats = 0;
}

Flight::Flight(string id, string from, string to, int seats) {
    flightID = id;
    origin = from;
    destination = to;
    totalSeats = seats;
    availableSeats = seats;
}
