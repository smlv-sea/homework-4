#ifndef LIMITEDRIDESTICKET_H
#define LIMITEDRIDESTICKET_H

#include "BaseTicket.h"

//Билет с ограничеснным сроком действия (наследник базового билета)
class LimitedRidesTicket : public BaseTicket { 
private:
    int saleTime;
    int maxTrips;
    int remainingTrips;
    int lastControlTime;

public:
    LimitedRidesTicket(int num, int saleT, int maxT);

    bool tryControl(int currentTime) override;
    std::string getType() const override;
    void printInfo() const override;

    // Геттеры
    int getSaleTime() const;
    int getMaxTrips() const;
    int getRemainingTrips() const;
    int getLastControlTime() const;

    // Операторы сравнения по времени продажи
    bool operator==(const LimitedRidesTicket& other) const;
    bool operator<(const LimitedRidesTicket& other) const;
};

#endif
