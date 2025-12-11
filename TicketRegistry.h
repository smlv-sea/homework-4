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

    // Коды ошибок для добавления билетов
    enum AddResult {
        ADD_SUCCESS = 0,           // Успешное добавление
        ADD_DUPLICATE_NUMBER = 1,  // Дубликат номера
        ADD_INVALID_NUMBER = 2,    // Неверный номер
        ADD_INVALID_PARAM = 3,     // Неверные параметры
        ADD_REGISTRY_FULL = 4,     // Реестр заполнен
        ADD_MEMORY_ERROR = 5,      // Ошибка памяти
        ADD_UNKNOWN_ERROR = 6      // Неизвестная ошибка
    };

private:
    std::map<int, std::shared_ptr<BaseTicket>> tickets; // Упорядоченный по номеру список

public:
    TicketRegistry() = default;

    // Добавление билетов разных типов с возвращаемым значением
    AddResult addTicket(std::shared_ptr<BaseTicket> ticket);
    AddResult addLimitedRidesTicket(int number, int saleTime, int maxTrips);
    AddResult addTimedTicket(int number, int saleTime, int validityPeriod);
    AddResult addUnlimitedTicket(int number, const std::string& issueReason);

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
