// main.cpp - DLL версия для Visual Studio
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "BaseTicket.h"
#include "LimitedRidesTicket.h"
#include "TimedTicket.h"
#include "UnlimitedTicket.h"
#include "ControlAttempt.h"
#include "TicketRegistry.h"

// Определение макроса для экспорта функций
#ifdef TICKETSYSTEMDLL_EXPORTS
#define TICKET_API __declspec(dllexport)
#else
#define TICKET_API __declspec(dllimport)
#endif

extern "C" {

    // Простая структура для взаимодействия
    struct TICKET_API TicketSimpleInfo {
        int number;
        char type[50];
        int remaining;
    };

    // === УПРОЩЕННЫЙ ИНТЕРФЕЙС DLL ===

    // 1. Управление реестром
    TICKET_API void* CreateTicketRegistry() {
        return new TicketRegistry();
    }

    TICKET_API void DeleteTicketRegistry(void* registry) {
        delete static_cast<TicketRegistry*>(registry);
    }

    // 2. Добавление билетов
    TICKET_API void AddLimitedTicket(void* registry, int number, int saleTime, int maxTrips) {
        auto reg = static_cast<TicketRegistry*>(registry);
        reg->addLimitedRidesTicket(number, saleTime, maxTrips);
        std::cout << "[DLL] Added limited ticket #" << number << std::endl;
    }

    TICKET_API void AddTimedTicket(void* registry, int number, int saleTime, int validityPeriod) {
        auto reg = static_cast<TicketRegistry*>(registry);
        reg->addTimedTicket(number, saleTime, validityPeriod);
        std::cout << "[DLL] Added timed ticket #" << number << std::endl;
    }

    TICKET_API void AddUnlimitedTicket(void* registry, int number, const char* issueReason) {
        auto reg = static_cast<TicketRegistry*>(registry);
        reg->addUnlimitedTicket(number, std::string(issueReason));
        std::cout << "[DLL] Added unlimited ticket #" << number << std::endl;
    }

    // 3. Проверка билета
    TICKET_API int TryControl(void* registry, int ticketNumber, int currentTime) {
        auto reg = static_cast<TicketRegistry*>(registry);
        return static_cast<int>(reg->tryControl(ticketNumber, currentTime));
    }

    // 4. Информация
    TICKET_API int GetTicketCount(void* registry) {
        auto reg = static_cast<TicketRegistry*>(registry);
        return static_cast<int>(reg->getTicketCount());
    }

    TICKET_API void PrintAllTickets(void* registry) {
        auto reg = static_cast<TicketRegistry*>(registry);
        reg->printAllTickets();
    }

    // 5. Тестовые функции
    TICKET_API void RunSimpleTest() {
        std::cout << "\n=== SIMPLE DLL TEST ===" << std::endl;

        TicketRegistry registry;

        // Создаем несколько билетов
        registry.addLimitedRidesTicket(1, 1000, 3);
        registry.addTimedTicket(2, 2000, 3600);
        registry.addUnlimitedTicket(3, "Test VIP");

        std::cout << "Created 3 test tickets" << std::endl;

        // Тестируем
        std::cout << "\nTesting ticket #1 (limited):" << std::endl;
        auto r1 = registry.tryControl(1, 1100);
        std::cout << "Result: " << (r1 == TicketRegistry::ALLOWED ? "ALLOWED" : "DENIED") << std::endl;

        std::cout << "\nTesting ticket #2 (timed):" << std::endl;
        auto r2 = registry.tryControl(2, 2100);
        std::cout << "Result: " << (r2 == TicketRegistry::ALLOWED ? "ALLOWED" : "DENIED") << std::endl;

        std::cout << "\nTesting ticket #3 (unlimited):" << std::endl;
        auto r3 = registry.tryControl(3, 3000);
        std::cout << "Result: " << (r3 == TicketRegistry::ALLOWED ? "ALLOWED" : "DENIED") << std::endl;

        std::cout << "\n=== TEST COMPLETE ===" << std::endl;
    }

    // 6. Получение строки результата
    TICKET_API const char* GetControlResultString(int result) {
        switch (result) {
        case 0: return "ALLOWED";
        case 1: return "DENIED";
        case 2: return "ALARM";
        default: return "UNKNOWN";
        }
    }

} // extern "C"