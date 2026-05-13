#pragma once
#include <exception>
#include <string>

class StationException : public std::exception {
protected:
    std::string message;
public:
    StationException(std::string msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class PowerSurgeException : public StationException {
public:
    PowerSurgeException() : StationException("Скачок напряжения! Потеряно 50 энергии.") {}
};

class FirmwareGlitchException : public StationException {
public:
    FirmwareGlitchException() : StationException("Сбой матриц! Прошивка роботов упала на 10%.") {}
};

class MeteorStrikeException : public StationException {
public:
    MeteorStrikeException() : StationException("Микро-метеорит! Один из модулей поврежден.") {}
};

// Вариант 8
class CoolantLeakException : public StationException {
public:
    CoolantLeakException() : StationException("Утечка охладителя! Строительство и модернизация временно невозможны.") {}
};
