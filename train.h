#ifndef TRAIN_H        
#define TRAIN_H          

#include <iostream>      
#include <cstring>       

class TRAIN {            
private:                 
    char* destination;   // Указатель на динамически выделенную память для строки назначения
    int trainNumber;     // Целочисленная переменная для хранения номера поезда
    char* departureTime; // Указатель на динамически выделенную память для строки времени отправления
    
public:                 
    TRAIN();                                               // Декларация конструктора по умолчанию
    TRAIN(const char* dest, int number, const char* time); // Декларация конструктора с параметрами
    TRAIN(const TRAIN& other);                             // Декларация конструктора копирования
    
    ~TRAIN();            // Декларация деструктора
    
    TRAIN& operator=(const TRAIN& other); // Декларация оператора присваивания
    
    const char* getDestination() const { return destination; }   // Геттер для destination
    int getTrainNumber() const { return trainNumber; }           // Геттер для trainNumber
    const char* getDepartureTime() const { return departureTime; } // Геттер для departureTime
    
    void setDestination(const char* dest);     // Сеттер для destination
    void setTrainNumber(int number);           // Сеттер для trainNumber
    void setDepartureTime(const char* time);   // Сеттер для departureTime
    
    static bool isValidTrainNumber(int number);      // Статический метод валидации номера поезда
    static bool isValidTimeFormat(const char* time); // Статический метод валидации формата времени
    static bool isValidTimeValues(const char* time); // Статический метод валидации значений времени
    
    int getTimeInMinutes() const;  // Метод для преобразования времени в минуты для сортировки
    
    friend std::ostream& operator<<(std::ostream& os, const TRAIN& train); // Дружественная функция для вывода
    friend std::istream& operator>>(std::istream& is, TRAIN& train);       // Дружественная функция для ввода
};

#endif