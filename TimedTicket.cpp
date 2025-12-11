#include "TimedTicket.h"
#include <iostream>

TimedTicket::TimedTicket(int num, int saleT, int validity)
    : LimitedRidesTicket(num, saleT, 1), validityPeriod(validity) {
}

bool TimedTicket::tryControl(int currentTime) {
    // Проверка срока действия
    if ((currentTime - getSaleTime()) > validityPeriod) {
        std::cout << "Отказ: истек срок действия (билет №" << getNumber() << ")\n";
        return false;
    }

    // Используем проверки из базового класса
    return LimitedRidesTicket::tryControl(currentTime);
}

std::string TimedTicket::getType() const {
    return "Билет с ограниченным сроком действия";
}

void TimedTicket::printInfo() const {
    std::cout << "№" << getNumber() << " [" << getType() << "] "
        << "Срок: " << validityPeriod << " сек"
        << ", Продажа: " << getSaleTime() << " сек\n";
}

int TimedTicket::getValidityPeriod() const {
    return validityPeriod;
}