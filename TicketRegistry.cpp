#include "TicketRegistry.h"
#include <iostream>

void TicketRegistry::addTicket(std::shared_ptr<BaseTicket> ticket) {
    int number = ticket->getNumber();
    if (isTicketRegistered(number)) {
        std::cout << "Билет #" << number << " Уже зарегистрирован!\n";
        return;
    }
    tickets[number] = ticket;
    std::cout << "Билет #" << number << " [" << ticket->getType() << "] добавлен в регистр\n";
}

void TicketRegistry::addLimitedRidesTicket(int number, int saleTime, int maxTrips) {
    addTicket(std::make_shared<LimitedRidesTicket>(number, saleTime, maxTrips));
}

void TicketRegistry::addTimedTicket(int number, int saleTime, int validityPeriod) {
    addTicket(std::make_shared<TimedTicket>(number, saleTime, validityPeriod));
}

void TicketRegistry::addUnlimitedTicket(int number, const std::string& issueReason) {
    addTicket(std::make_shared<UnlimitedTicket>(number, issueReason));
}

TicketRegistry::ControlResult TicketRegistry::tryControl(int ticketNumber, int currentTime) {
    // Проверка наличия билета в регистре
    if (!isTicketRegistered(ticketNumber)) {
        std::cout << "Билет #" << ticketNumber << " не зарегистрирован!\n";
        return ALARM;
    }

    auto ticket = getTicket(ticketNumber);

    // Проверка на несоответствия (подозрение в подделке)
    if (checkForAlarm(ticket)) {
        return ALARM;
    }

    // Проверка допустимости прохода
    return checkTicketValidity(ticket, currentTime);
}

TicketRegistry::ControlResult TicketRegistry::checkTicketValidity(std::shared_ptr<BaseTicket> ticket, int currentTime) {
    // Пытаемся пройти контроль
    bool success = ticket->tryControl(currentTime);
    return success ? ALLOWED : DENIED;
}


bool TicketRegistry::isTicketRegistered(int number) const {
    return tickets.find(number) != tickets.end();
}

bool TicketRegistry::checkForAlarm(std::shared_ptr<BaseTicket> ticket) const {
    // Проверка для LimitedRidesTicket
    if (auto limited = std::dynamic_pointer_cast<LimitedRidesTicket>(ticket)) {
        // Проверка: оставшиеся поездки > максимальных
        if (limited->getRemainingTrips() > limited->getMaxTrips()) {
            std::cout << "Билет #" << ticket->getNumber()
                << " - остаток поездок (" << limited->getRemainingTrips()
                << ") больше максимума (" << limited->getMaxTrips() << ")!\n";
            return true;
        }

        // Проверка: отрицательное количество оставшихся поездок
        if (limited->getRemainingTrips() < 0) {
            std::cout << "Билет #" << ticket->getNumber()
                << " - отрицательное количество оставшихся поездок ("
                << limited->getRemainingTrips() << ")!\n";
            return true;
        }
    }

    return false;
}

void TicketRegistry::printAllTickets() const {
    std::cout << "\n=== Регистр билетов (всего " << tickets.size() << " билетов) ===\n";
    for (const auto& pair : tickets) {
        int number = pair.first;
        auto ticket = pair.second;
        ticket->printInfo();
    }
    std::cout << "============================================\n";
}

void TicketRegistry::printRegistryInfo() const {
    std::cout << "\n=== Информация о регистре ===\n";
    std::cout << "Всего билетов: " << tickets.size() << "\n";

    // Статистика по типам билетов
    int limitedCount = 0, timedCount = 0, unlimitedCount = 0;
    for (const auto& pair : tickets) {
        auto ticket = pair.second;
        if (dynamic_cast<LimitedRidesTicket*>(ticket.get())) limitedCount++;
        else if (dynamic_cast<TimedTicket*>(ticket.get())) timedCount++;
        else if (dynamic_cast<UnlimitedTicket*>(ticket.get())) unlimitedCount++;
    }

    std::cout << "Билетов с ограниченным числом поездок: " << limitedCount << "\n";
    std::cout << "Билетов с ограниченным сроком действия: " << timedCount << "\n";
    std::cout << "Бессрочных билетов: " << unlimitedCount << "\n";
    std::cout << "================================\n";
}

std::shared_ptr<BaseTicket> TicketRegistry::getTicket(int number) const {
    auto it = tickets.find(number);
    return it != tickets.end() ? it->second : nullptr;
}