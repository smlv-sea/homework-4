#include "LimitedRidesTicket.h"
#include <iostream>

LimitedRidesTicket::LimitedRidesTicket(int num, int saleT, int maxT)
    : BaseTicket(num), saleTime(saleT), maxTrips(maxT),
    remainingTrips(maxT), lastControlTime(-1) {
}

bool LimitedRidesTicket::tryControl(int currentTime) {
    if (remainingTrips <= 0) {
        std::cout << "Отказ: закончились поездки (билет №" << number << ")\n";
        return false;
    }

    if (lastControlTime != -1 && (currentTime - lastControlTime) < 3) {
        std::cout << "Отказ: повторный проход слишком скоро (билет №" << number << ")\n";
        return false;
    }

    remainingTrips--;
    lastControlTime = currentTime;
    std::cout << "Успех: проход разрешен (билет №" << number << ")\n";
    return true;
}

std::string LimitedRidesTicket::getType() const {
    return "Билет на заданное число поездок";
}

void LimitedRidesTicket::printInfo() const {
    std::cout << "№" << number << " [" << getType() << "] "
        << "Поездки: " << remainingTrips << "/" << maxTrips
        << ", Продажа: " << saleTime << " сек\n";
}

int LimitedRidesTicket::getSaleTime() const { return saleTime; }
int LimitedRidesTicket::getMaxTrips() const { return maxTrips; }
int LimitedRidesTicket::getRemainingTrips() const { return remainingTrips; }
int LimitedRidesTicket::getLastControlTime() const { return lastControlTime; }

bool LimitedRidesTicket::operator==(const LimitedRidesTicket& other) const {
    return saleTime == other.saleTime;
}

bool LimitedRidesTicket::operator<(const LimitedRidesTicket& other) const {
    return saleTime < other.saleTime;
}