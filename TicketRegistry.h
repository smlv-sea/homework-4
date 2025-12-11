#ifndef TICKETREGISTRY_H
#define TICKETREGISTRY_H

#include "BaseTicket.h"
#include "LimitedRidesTicket.h"
#include "TimedTicket.h"
#include "UnlimitedTicket.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <string>

class TicketRegistry {
public:
    enum ControlResult {
        ALLOWED,    // Разрешение прохода
        DENIED,     // Запрещение прохода
        ALARM       // Подозрение в подделке билета (тревога)
    };

private:
    std::map<int, std::shared_ptr<BaseTicket>> tickets; // Упорядоченный по номеру список

public:
    TicketRegistry() = default;

    // Добавление билетов разных типов
    void addTicket(std::shared_ptr<BaseTicket> ticket);
    void addLimitedRidesTicket(int number, int saleTime, int maxTrips);
    void addTimedTicket(int number, int saleTime, int validityPeriod);
    void addUnlimitedTicket(int number, const std::string& issueReason);

    // Проверка билета
    ControlResult tryControl(int ticketNumber, int currentTime);
    ControlResult checkTicketValidity(std::shared_ptr<BaseTicket> ticket, int currentTime);

    // Проверки на подделку
    bool isTicketRegistered(int number) const;
    bool checkForAlarm(std::shared_ptr<BaseTicket> ticket) const;

   
    void printAllTickets() const; // Печать всех билетов
    void printRegistryInfo() const; // Общая информация о билете
    size_t getTicketCount() const { return tickets.size(); } // Количество билетов

    // Получение билета по номеру
    std::shared_ptr<BaseTicket> getTicket(int number) const;
};

#endif
