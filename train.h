#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <cstring>

class TRAIN {
private:
    char* destination;
    int trainNumber;
    char* departureTime;
    
public:
    // Конструкторы
    TRAIN();
    TRAIN(const char* dest, int number, const char* time);
    TRAIN(const TRAIN& other);
    
    // Деструктор
    ~TRAIN();
    
    // Операторы присваивания
    TRAIN& operator=(const TRAIN& other);
    
    // Get методы
    const char* getDestination() const { return destination; }
    int getTrainNumber() const { return trainNumber; }
    const char* getDepartureTime() const { return departureTime; }
    
    // Set методы
    void setDestination(const char* dest);
    void setTrainNumber(int number) { trainNumber = number; }
    void setDepartureTime(const char* time);
    
    // Методы для работы со временем
    int getTimeInMinutes() const;
    
    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const TRAIN& train);
    friend std::istream& operator>>(std::istream& is, TRAIN& train);
};

#endif