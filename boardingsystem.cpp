#include "../include/BoardingSystem.h"

// Add passenger to the correct queue
void BoardingSystem::addPassenger(Passenger p) {
    // Priority 1 = VIP
    // Priority 2 = Business
    // Priority 3 = Economy
    if (p.priority == 1 || p.priority == 2) {
        vipQueue.insert(p);      // Min-heap
    } else {
        regularQueue.enqueue(p); // FIFO queue
    }
}

// Return next passenger to board
Passenger BoardingSystem::nextToBoard() {
    // VIP passengers board first
    if (!vipQueue.isEmpty()) {
        return vipQueue.extractMin();
    }

    // Then regular passengers
    if (!regularQueue.isEmpty()) {
        return regularQueue.dequeue();
    }

    // If no passengers remain
    return Passenger(); // empty object
}
