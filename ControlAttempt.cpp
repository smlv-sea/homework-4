#include "ControlAttempt.h"
#include <iostream>

ControlAttempt::ControlAttempt(std::shared_ptr<BaseTicket> t, int time)
    : ticket(t), controlTime(time) {
    success = ticket->tryControl(time);
}



void ControlAttempt::printInfo() const {
    std::cout << "Попытка прохода: Билет №" << ticket->getNumber()
        << " [" << ticket->getType() << "]"
        << " время прохода " << controlTime << " сек - " << getResult() << "\n";
}