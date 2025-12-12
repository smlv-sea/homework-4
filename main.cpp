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

        // 1. Управление реестром
    TICKET_API void* CreateTicketRegistry() {
        try {
            return new TicketRegistry();
        }
        catch (...) {
            return nullptr;
        }
    }

    TICKET_API void DeleteTicketRegistry(void* registry) {
        if (registry) {
            delete static_cast<TicketRegistry*>(registry);
        }
    }

    // 2. Добавление билетов с возвращаемыми значениями
    TICKET_API int AddLimitedTicket(void* registry, int number, int saleTime, int maxTrips) {
        if (!registry) return 6;  // UNKNOWN_ERROR

        auto reg = static_cast<TicketRegistry*>(registry);
        auto result = reg->addLimitedRidesTicket(number, saleTime, maxTrips);

        return static_cast<int>(result);
    }

    TICKET_API int AddTimedTicket(void* registry, int number, int saleTime, int validityPeriod) {
        if (!registry) return 6;  // UNKNOWN_ERROR

        auto reg = static_cast<TicketRegistry*>(registry);
        auto result = reg->addTimedTicket(number, saleTime, validityPeriod);

        return static_cast<int>(result);
    }

    TICKET_API int AddUnlimitedTicket(void* registry, int number, const char* issueReason) {
        if (!registry) return 6;  // UNKNOWN_ERROR

        auto reg = static_cast<TicketRegistry*>(registry);
        auto result = reg->addUnlimitedTicket(number, std::string(issueReason));

        return static_cast<int>(result);
    }

    // 3. Проверка билета
    TICKET_API int TryControl(void* registry, int ticketNumber, int currentTime) {
        if (!registry) return 2;  // ALARM

        auto reg = static_cast<TicketRegistry*>(registry);
        return static_cast<int>(reg->tryControl(ticketNumber, currentTime));
    }

    // 4. Информация
    TICKET_API int GetTicketCount(void* registry) {
        if (!registry) return 0;

        auto reg = static_cast<TicketRegistry*>(registry);
        return static_cast<int>(reg->getTicketCount());
    }

    TICKET_API void PrintAllTickets(void* registry) {
        if (!registry) return;

        auto reg = static_cast<TicketRegistry*>(registry);
        reg->printAllTickets();
    }

    // 5. Тестовые функции
    TICKET_API void RunSimpleTest() {
        std::cout << "\n=== SIMPLE DLL TEST ===" << std::endl;

        TicketRegistry registry;

        // Создаем несколько билетов
        auto r1 = registry.addLimitedRidesTicket(1, 1000, 3);
        auto r2 = registry.addTimedTicket(2, 2000, 3600);
        auto r3 = registry.addUnlimitedTicket(3, "Test VIP");

        std::cout << "Create results: " << r1 << ", " << r2 << ", " << r3 << std::endl;
        std::cout << "Created " << registry.getTicketCount() << " test tickets" << std::endl;

        // Тестируем дубликаты
        std::cout << "\nTesting duplicate ticket #1:" << std::endl;
        auto r4 = registry.addLimitedRidesTicket(1, 1200, 5);
        std::cout << "Duplicate add result: " << r4 << " (should be 1 = DUPLICATE)" << std::endl;

        // Тестируем проходы
        std::cout << "\nTesting ticket #1 (limited):" << std::endl;
        auto c1 = registry.tryControl(1, 1100);
        std::cout << "Result: " << (c1 == TicketRegistry::ALLOWED ? "ALLOWED" : "DENIED") << std::endl;

        std::cout << "\nTesting ticket #2 (timed):" << std::endl;
        auto c2 = registry.tryControl(2, 2100);
        std::cout << "Result: " << (c2 == TicketRegistry::ALLOWED ? "ALLOWED" : "DENIED") << std::endl;

        std::cout << "\nTesting ticket #3 (unlimited):" << std::endl;
        auto c3 = registry.tryControl(3, 3000);
        std::cout << "Result: " << (c3 == TicketRegistry::ALLOWED ? "ALLOWED" : "DENIED") << std::endl;

        // Тестируем несуществующий билет
        std::cout << "\nTesting non-existent ticket #999:" << std::endl;
        auto c4 = registry.tryControl(999, 4000);
        std::cout << "Result: " << (c4 == TicketRegistry::ALLOWED ? "ALLOWED" :
            c4 == TicketRegistry::DENIED ? "DENIED" : "ALARM") << std::endl;

        std::cout << "\n=== TEST COMPLETE ===" << std::endl;
    }

    // 6. Получение строки результата проверки
    TICKET_API const char* GetControlResultString(int result) {
        switch (result) {
        case 0: return "ALLOWED";
        case 1: return "DENIED";
        case 2: return "ALARM";
        default: return "UNKNOWN";
        }
    }

    // 7. Получение строки сообщения об ошибке добавления билета
    TICKET_API const char* GetAddTicketErrorString(int errorCode) {
        switch (errorCode) {
        case 0: return "Success - ticket added successfully";
        case 1: return "Duplicate ticket number - ticket with this number already exists";
        case 2: return "Invalid ticket number - number must be positive";
        case 3: return "Invalid parameters - check ticket parameters";
        case 4: return "Registry full - cannot add more tickets";
        case 5: return "Memory error - failed to allocate memory";
        case 6: return "Unknown error - internal DLL error";
        default: return "Invalid error code";
        }
    }

} // extern "C"