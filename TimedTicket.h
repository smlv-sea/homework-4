#ifndef TIMEDTICKET_H
#define TIMEDTICKET_H

#include "LimitedRidesTicket.h"

//Билет с ограниченным сроком действия
class TimedTicket : public LimitedRidesTicket {
private:
    int validityPeriod;

public:
    TimedTicket(int num, int saleT, int validity);

    bool tryControl(int currentTime) override;
    std::string getType() const override;
    void printInfo() const override;

    int getValidityPeriod() const;
};

#endif
