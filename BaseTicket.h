#ifndef BASETICKET_H
#define BASETICKET_H

#include <string>

class BaseTicket {
protected:
    int number;

public:
    BaseTicket(int num);
    virtual ~BaseTicket() = default;

    // Виртуальные методы
    virtual bool tryControl(int currentTime) = 0;
    virtual std::string getType() const = 0;
    virtual void printInfo() const = 0;

    // Геттеры
    int getNumber() const;

    // Операторы сравнения по номеру
    bool operator==(const BaseTicket& other) const;
    bool operator<(const BaseTicket& other) const;
};

#endif
