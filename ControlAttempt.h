#ifndef CONTROLATTEMPT_H
#define CONTROLATTEMPT_H

#include "BaseTicket.h"
#include <memory>

class ControlAttempt {
private:
    std::shared_ptr<BaseTicket> ticket;
    int controlTime;
    bool success;

public:
    ControlAttempt(std::shared_ptr<BaseTicket> t, int time);

    // Изменено: возвращает bool вместо string
    bool getResult() const { return success; }

    bool isSuccessful() const { return success; }
    std::shared_ptr<BaseTicket> getTicket() const { return ticket; }
    int getControlTime() const { return controlTime; }
    void printInfo() const;
};

#endif
