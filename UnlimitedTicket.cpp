#include "UnlimitedTicket.h"
#include <iostream>

UnlimitedTicket::UnlimitedTicket(int num, const std::string& reason)
    : BaseTicket(num), issueReason(reason), lastControlTime(-1) {
}

bool UnlimitedTicket::tryControl(int currentTime) {
    // Проверка временного ограничения (3 минуты = 180 секунд)
    if (lastControlTime != -1 && (currentTime - lastControlTime) < 180) {
        std::cout << "Отказ: повторный проход менее чем через 3 минуты (билет №" << number << ")\n";
        return false;
    }

    lastControlTime = currentTime;
    std::cout << "Успех: проход разрешен (бессрочный билет №" << number << ")\n";
    return true;
}

std::string UnlimitedTicket::getType() const {
    return "Бессрочный билет";
}

void UnlimitedTicket::printInfo() const {
    std::cout << "№" << number << " [" << getType() << "] "
        << "Основание: " << issueReason << "\n";
}

std::string UnlimitedTicket::getIssueReason() const {
    return issueReason;
}

int UnlimitedTicket::getLastControlTime() const {
    return lastControlTime;
}