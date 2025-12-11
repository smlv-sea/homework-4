#include "BaseTicket.h"
#include <iostream>

BaseTicket::BaseTicket(int num) : number(num) {}

int BaseTicket::getNumber() const {
    return number;
}

bool BaseTicket::operator==(const BaseTicket& other) const {
    return number == other.number;
}

bool BaseTicket::operator<(const BaseTicket& other) const {
    return number < other.number;
}