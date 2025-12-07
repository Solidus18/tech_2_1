#include "train.h"        
#include <iostream>      
#include <cstring>      
#include <cctype>        
#include <cstdlib>        

class InvalidTrainNumberException : public std::exception {  // Объявление класса исключения для неверного номера поезда
public:                                                      
    const char* what() const noexcept override {            // Переопределение виртуальной функции what()
        return "Invalid train number! Must be positive integer.";
    }                                                     
};                                                          

class InvalidTimeFormatException : public std::exception {   // Объявление класса исключения для неверного формата времени
public:                                                    
    const char* what() const noexcept override {            // Переопределение функции what()
        return "Invalid time format! Must be exactly 5 characters: HH:MM (example: 08:30)."; 
    }                                               
};                                                        

class InvalidTimeValuesException : public std::exception {   // Объявление класса исключения для неверных значений времени
public:                                                     
    const char* what() const noexcept override {            // Переопределение функции what()
        return "Invalid time values! Hours: 00-23, Minutes: 00-59."; 
    }                                                   
};                                                      

TRAIN::TRAIN() : destination(nullptr), trainNumber(0), departureTime(nullptr) { // Конструктор по ум с иниц списком
    destination = new char[1];     
    destination[0] = '\0';         
    departureTime = new char[6];   
    strcpy(departureTime, "00:00"); 
    std::cout << "Default constructor called for TRAIN" << std::endl; 
}                                                                   

TRAIN::TRAIN(const char* dest, int number, const char* time) {      // Конструктор с параметрами
    if (!isValidTrainNumber(number)) {                 // Проверка номера поезда
        throw InvalidTrainNumberException();           
    }                                                 
    
    if (!isValidTimeFormat(time)) {                    // Проверка формата времени
        throw InvalidTimeFormatException();           
    }                                            
    
    if (!isValidTimeValues(time)) {                    // Проверка значений времени
        throw InvalidTimeValuesException();          
    }                                                 
    
    destination = new char[strlen(dest) + 1];          // Выделение памяти под destination (длина строки + 1 для '\0')
    strcpy(destination, dest);                         // Копирование строки dest в destination
    
    trainNumber = number;                              
    
    departureTime = new char[6];                       
    strcpy(departureTime, time);                       // Копирование строки time в departureTime
    
    std::cout << "Parameterized constructor called for TRAIN: " << destination << std::endl; 
}                                                                   

TRAIN::TRAIN(const TRAIN& other) : trainNumber(other.trainNumber) { // Конструктор копирования с иниц
    destination = new char[strlen(other.destination) + 1];         
    strcpy(destination, other.destination);                         // Копирование destination из другого объекта
    
    departureTime = new char[6];                                    
    strcpy(departureTime, other.departureTime);                     // Копирование departureTime из другого объекта
    
    std::cout << "Copy constructor called for TRAIN: " << destination << std::endl;
}                                                                  

TRAIN::~TRAIN() {                                                   // Реализация деструктора
    std::cout << "Destructor called for TRAIN: " << (destination ? destination : "unknown") << std::endl;
    delete[] destination;              
    delete[] departureTime;            
}                                    

TRAIN& TRAIN::operator=(const TRAIN& other) {                        // Реализация оператора присваивания
    if (this != &other) {                     // Проверка на самоприсваивание (self-assignment check)
        delete[] destination;                 
        delete[] departureTime;               
        
        destination = new char[strlen(other.destination) + 1]; 
        strcpy(destination, other.destination);               
        
        departureTime = new char[6];                    
        strcpy(departureTime, other.departureTime);       
        
        trainNumber = other.trainNumber;                      
    }                                                       
    return *this;                                         
}                                                       

void TRAIN::setDestination(const char* dest) {                 // Реализация сеттера для destination
    delete[] destination;                               
    destination = new char[strlen(dest) + 1];           
    strcpy(destination, dest);                              
}                                                           

void TRAIN::setTrainNumber(int number) {                       // Реализация сеттера для trainNumber
    if (!isValidTrainNumber(number)) {                         // Проверка валидности номера
        throw InvalidTrainNumberException();                
    }                                                     
    trainNumber = number;                                    
}                                                         

void TRAIN::setDepartureTime(const char* time) {               // Реализация сеттера для departureTime
    if (!isValidTimeFormat(time)) {                            // Проверка формата времени
        throw InvalidTimeFormatException();            
    }                                                   
    
    if (!isValidTimeValues(time)) {                            // Проверка значений времени
        throw InvalidTimeValuesException();                
    }                                                 
    
    delete[] departureTime;                          
    departureTime = new char[6];                          
    strcpy(departureTime, time);                        
}                                                            

bool TRAIN::isValidTrainNumber(int number) {                   // Реализация статического метода проверки номера
    return number > 0;                                      
}                                                           

bool TRAIN::isValidTimeFormat(const char* time) {              // Реализация статического метода проверки формата времени
    if (time == nullptr || strlen(time) == 0) {                // Проверка на null или пустую строку
        return false;                                  
    }                                            
    
    if (strlen(time) != 5) {                                   // Проверка длины строки 
        return false;                                  
    }                                                   
    
    for (int i = 0; i < 5; i++) {                          
        if (i == 2) {                                       
            if (time[i] != ':') {                              // Проверка, что третий символ - двоеточие
                return false;                                
            }                                                
        } else {                                           
            if (!isdigit(time[i])) {                           // Проверка, является ли символ цифрой
                return false;                            
            }                                            
        }                                         
    }                                                      
    
    return true;                                            
}                                                      

bool TRAIN::isValidTimeValues(const char* time) {              // Реализация статического метода проверки значений времени
    char hourStr[3] = {time[0], time[1], '\0'};             
    char minuteStr[3] = {time[3], time[4], '\0'};          
    
    int hours = atoi(hourStr);                                
    int minutes = atoi(minuteStr);                          
    
    if (hours < 0 || hours > 23) {                             // Проверка диапазона часов
        return false;                                
    }                                                    
    
    if (minutes < 0 || minutes > 59) {                         // Проверка диапазона минут 
        return false;                                     
    }                                                  
    
    return true;                                       
}                                                         

int TRAIN::getTimeInMinutes() const {                                 // Реализация метода получения времени в минутах
    char hourStr[3] = {departureTime[0], departureTime[1], '\0'}; 
    char minuteStr[3] = {departureTime[3], departureTime[4], '\0'};
    
    int hours = atoi(hourStr);                               
    int minutes = atoi(minuteStr);                             
    
    return hours * 60 + minutes;                              
}                                                          

std::ostream& operator<<(std::ostream& os, const TRAIN& train) { // Реализация оператора вывода
    os << "Destination: " << train.destination                
       << ", Train number: " << train.trainNumber            
       << ", Departure time: " << train.departureTime;       
    return os;                                                
}                                                      

std::istream& operator>>(std::istream& is, TRAIN& train) {    // Реализация оператора ввода
    char buffer[100];                                         
    int number;                                            
    
    bool validInput = false;                                  
    while (!validInput) {                                     // Цикл, пока ввод не будет валидным
        std::cout << "Enter destination: ";                   
        is >> buffer;                                       
        
        if (strlen(buffer) > 0) {                             // Проверка, что строка не пустая
            train.setDestination(buffer);                   
            validInput = true;                           
        } else {                                              
            std::cout << "Error: Destination cannot be empty!" << std::endl; 
        }                                                
    }                                                      

    validInput = false;                                       // Сброс флага валидности
    while (!validInput) {                                     // Цикл для ввода номера поезда
        std::cout << "Enter train number (positive integer): "; 
        if (!(is >> number)) {                            
            std::cout << "Error: Please enter a valid integer number!" << std::endl;
            is.clear();                                       // Сброс флагов ошибок потока
            is.ignore(10000, '\n');                          // Очистка буфера потока до символа новой строки
            continue;                                        
        }                                                    
        
        if (!TRAIN::isValidTrainNumber(number)) {             // Проверка валидности номера
            std::cout << "Error: Train number must be positive (greater than 0)!" << std::endl;
            is.ignore(10000, '\n');                      
            continue;                                    
        }                                                
        
        try {                                                 // Блок для обработки исключений
            train.setTrainNumber(number);                 
            validInput = true;                              
        } catch (const std::exception& e) {                   // Обработка исключения
            std::cout << "Error: " << e.what() << std::endl;  
        }                                              
    }                                              
    
    validInput = false;                                       // Сброс флага валидности
    is.ignore(10000, '\n');                                  // Очистка буфера потока
    
    while (!validInput) {                                     // Цикл для ввода времени
        std::cout << "Enter departure time (HH:MM, 00:00 to 23:59, exactly 5 characters): "; 
        is.getline(buffer, 100);                         
        
        if (strlen(buffer) == 0) {                            // Проверка на пустую строку
            std::cout << "Error: Time cannot be empty!" << std::endl; 
            continue;                                  
        }                                         
        
        if (!TRAIN::isValidTimeFormat(buffer)) {              // Проверка формата времени
            std::cout << "Error: Invalid time format! Must be exactly 5 characters: HH:MM (example: 08:30, 14:05)" << std::endl;
            continue;                                      
        }                                                
        
        if (!TRAIN::isValidTimeValues(buffer)) {              // Проверка значений времени
            std::cout << "Error: Invalid time values! Hours must be 00-23, minutes must be 00-59" << std::endl;
            continue;                              
        }                                           
        
        try {                                                 // Блок для обработки исключений
            train.setDepartureTime(buffer);               
            validInput = true;                            
        } catch (const std::exception& e) {                   // Обработка исключения
            std::cout << "Error: " << e.what() << std::endl;  
        }                                                    
    }                                                       
    
    return is;                                      
}                                                       