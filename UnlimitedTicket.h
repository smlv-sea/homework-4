#ifndef UNLIMITEDTICKET_H
#define UNLIMITEDTICKET_H

#include "BaseTicket.h"
#include <string>

//Бессрочный билет
class UnlimitedTicket : public BaseTicket {
private:
    std::string issueReason;
    int lastControlTime;

public:
    UnlimitedTicket(int num, const std::string& reason);

    bool tryControl(int currentTime) override;
    std::string getType() const override;
    void printInfo() const override;

    std::string getIssueReason() const;
    int getLastControlTime() const;
};

#endif
