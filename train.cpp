#include "train.h"
#include <iostream>
#include <cstring>

// Конструктор по умолчанию
TRAIN::TRAIN() : destination(nullptr), trainNumber(0), departureTime(nullptr) {
    destination = new char[1];
    destination[0] = '\0';
    departureTime = new char[1];
    departureTime[0] = '\0';
    std::cout << "Вызван конструктор по умолчанию для TRAIN" << std::endl;
}

// Конструктор с параметрами
TRAIN::TRAIN(const char* dest, int number, const char* time) : trainNumber(number) {
    destination = new char[strlen(dest) + 1];
    strcpy(destination, dest);
    
    departureTime = new char[strlen(time) + 1];
    strcpy(departureTime, time);
    std::cout << "Вызван конструктор с параметрами для TRAIN: " << destination << std::endl;
}

// Конструктор копирования
TRAIN::TRAIN(const TRAIN& other) : trainNumber(other.trainNumber) {
    destination = new char[strlen(other.destination) + 1];
    strcpy(destination, other.destination);
    
    departureTime = new char[strlen(other.departureTime) + 1];
    strcpy(departureTime, other.departureTime);
    std::cout << "Вызван конструктор копирования для TRAIN: " << destination << std::endl;
}

// Деструктор
TRAIN::~TRAIN() {
    std::cout << "Вызван деструктор для TRAIN: " << (destination ? destination : "unknown") << std::endl;
    delete[] destination;
    delete[] departureTime;
}

// Оператор присваивания
TRAIN& TRAIN::operator=(const TRAIN& other) {
    if (this != &other) {
        delete[] destination;
        delete[] departureTime;
        
        destination = new char[strlen(other.destination) + 1];
        strcpy(destination, other.destination);
        
        departureTime = new char[strlen(other.departureTime) + 1];
        strcpy(departureTime, other.departureTime);
        
        trainNumber = other.trainNumber;
    }
    return *this;
}

void TRAIN::setDestination(const char* dest) {
    delete[] destination;
    destination = new char[strlen(dest) + 1];
    strcpy(destination, dest);
}

void TRAIN::setDepartureTime(const char* time) {
    delete[] departureTime;
    departureTime = new char[strlen(time) + 1];
    strcpy(departureTime, time);
}

int TRAIN::getTimeInMinutes() const {
    int hours, minutes;
    if (sscanf(departureTime, "%d:%d", &hours, &minutes) == 2) {
        return hours * 60 + minutes;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, const TRAIN& train) {
    os << "Пункт назначения: " << train.destination 
       << ", Номер поезда: " << train.trainNumber 
       << ", Время отправления: " << train.departureTime;
    return os;
}

std::istream& operator>>(std::istream& is, TRAIN& train) {
    char buffer[100];
    
    std::cout << "Введите пункт назначения: ";
    is >> buffer;
    train.setDestination(buffer);
    
    std::cout << "Введите номер поезда: ";
    is >> train.trainNumber;
    
    std::cout << "Введите время отправления (ЧЧ:ММ): ";
    is >> buffer;
    train.setDepartureTime(buffer);
    
    return is;
}