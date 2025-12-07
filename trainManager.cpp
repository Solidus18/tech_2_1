#include "trainManager.h"        
#include <iostream>                
#include <algorithm>              
#include <cstring>             
#include <conio.h>             
#include <cstdlib>               

class InvalidIndexException : public std::exception {  // Объявление класса исключения для неверного индекса
private:                                             
    char* message;                                     // Указатель на строку с сообщением об ошибке
public:                                             
    InvalidIndexException(const char* msg) {           // Конструктор с параметром
        message = new char[strlen(msg) + 1];          
        strcpy(message, msg);                         
    }                                                 
    
    ~InvalidIndexException() {                         // Деструктор класса
        delete[] message;                            
    }                                                 
    
    const char* what() const noexcept override {       // Переопределение виртуальной функции what()
        return message;                              
    }                                                  
};                                                    

class EmptyListException : public std::exception {     // Объявление класса исключения для пустого списка
public:                                             
    const char* what() const noexcept override {       // Переопределение функции what()
        return "The train list is empty!";         
    }                                                  
};                                                    

int compareTrainsByTime(const void* a, const void* b) { // Функция сравнения для qsort
    TRAIN* trainA = *(TRAIN**)a;                       
    TRAIN* trainB = *(TRAIN**)b;                     
    
    return trainA->getTimeInMinutes() - trainB->getTimeInMinutes(); 
}                                                      

TrainManager::TrainManager() : capacity(10), size(0) {  // Конструктор с инициализацией
    trains = new TRAIN*[capacity];                     
    for (int i = 0; i < capacity; i++) {                
        trains[i] = nullptr;                           
    }                                             
    std::cout << "The constructor TrainManager is called" << std::endl; 
}                                             

TrainManager::~TrainManager() {                         // Реализация деструктора
    for (int i = 0; i < size; i++) {                    
        delete trains[i];                               
    }                                                   
    delete[] trains;                               
    std::cout << "The destructor TrainManager is called" << std::endl; 
}                                                       

void TrainManager::resize() {                           // Реализация метода расширения
    capacity *= 2;                                     
    TRAIN** newTrains = new TRAIN*[capacity];          
    for (int i = 0; i < capacity; i++) {               
        if (i < size) {                                
            newTrains[i] = trains[i];              
        } else {                                     
            newTrains[i] = nullptr;              
        }                                           
    }                                                
    delete[] trains;                               
    trains = newTrains;                              
}                                                    

void TrainManager::addTrain(const TRAIN& train) {       // Реализация метода добавления поезда
    if (size >= capacity) {                             // Проверка, заполнен ли массив
        resize();                                       
    }                                              
    trains[size] = new TRAIN(train);                
    size++;                                     
    sortByDepartureTime();                              
}                                                    

void TrainManager::addTrainAtPosition(const TRAIN& train, int position) { // Реализация метода добавления на позицию
    if (position < 0 || position > size) {              // Проверка корректности позиции
        throw InvalidIndexException("Incorrect position for adding a train!"); 
    }                                                  
    
    if (size >= capacity) {                             // Проверка, заполнен ли массив
        resize();                                       
    }                                                   
    
    for (int i = size; i > position; i--) {            
        trains[i] = trains[i - 1];                  
    }                                               
    trains[position] = new TRAIN(train);               
    size++;                                       
    sortByDepartureTime();                           
}                                                  

void TrainManager::removeTrain(int index) {             // Реализация метода удаления поезда
    if (size == 0) {                                    // Проверка, пуст ли список
        throw EmptyListException();                     
    }                                                   
    if (index < 0 || index >= size) {                   // Проверка корректности индекса
        throw InvalidIndexException("Invalid index for deleting a train!");
    }                                                  
    
    delete trains[index];                               // Освобождение памяти удаляемого объекта
    for (int i = index; i < size - 1; i++) {            
        trains[i] = trains[i + 1];                     
    }                                                 
    trains[size - 1] = nullptr;                        
    size--;                                     
}                                                  

void TrainManager::editTrain(int index) {               // Реализация метода редактирования поезда
    if (index < 0 || index >= size) {                   // Проверка корректности индекса
        throw InvalidIndexException("Invalid index for editing train!"); 
    }                                       
    
    TRAIN* train = trains[index];                       
    char choice;                                       
    char buffer[100];                               
    int number;                                        
    bool editing = true;                            
    
    std::cout << "\nEditing train #" << (index + 1) << std::endl; 
    std::cout << "Current data: " << *train << std::endl;
    
    while (editing) {                             
        std::cout << "\nEdit Menu" << std::endl; 
        std::cout << "1. Change destination" << std::endl; 
        std::cout << "2. Change train number" << std::endl; 
        std::cout << "3. Change departure time" << std::endl; 
        std::cout << "4. Finish editing\n" << std::endl;
        
        choice = _getch();                             
        
        switch (choice) {                               
            case '1': {                                 
                std::cout << "Current destination: " << train->getDestination() << std::endl; 
                std::cout << "Enter new destination: "; 
                std::cin >> buffer;                      
                train->setDestination(buffer);         
                std::cout << "Destination updated!" << std::endl; 
                break;                                
            }                                   
            
            case '2': {                                
                std::cout << "Current train number: " << train->getTrainNumber() << std::endl; 
                bool validInput = false;           
                while (!validInput) {                   
                    std::cout << "Enter new train number (positive integer): ";
                    
                    if (!(std::cin >> number)) {         
                        std::cout << "Error: Please enter a valid integer number!" << std::endl; 
                        std::cin.clear();                // Сброс флагов ошибок потока
                        std::cin.ignore(10000, '\n');   // Очистка буфера потока
                        continue;                 
                    }                            
                    
                    if (TRAIN::isValidTrainNumber(number)) { // Проверка валидности номера
                        try {                            // Блок для обработки исключений
                            train->setTrainNumber(number);
                            validInput = true;           
                            std::cout << "Train number updated!" << std::endl;
                        } catch (const std::exception& e) { // Обработка исключения от сеттера
                            std::cout << "Error: " << e.what() << std::endl; 
                        }                       
                    } else {                     
                        std::cout << "Error: Train number must be positive (greater than 0)!" << std::endl;
                        std::cin.ignore(10000, '\n');   // Очистка буфера
                    }                           
                }                            
                break;                          
            }                                          
            
            case '3': {                              
                std::cout << "Current departure time: " << train->getDepartureTime() << std::endl;
                
                bool validInput = false;                 // Флаг валидности ввода
                std::cin.ignore(10000, '\n');           // Очистка буфера перед чтением строки
                
                while (!validInput) {                    // Цикл, пока ввод не будет валидным
                    std::cout << "Enter new departure time (HH:MM, 00:00 to 23:59, exactly 5 characters): "; 
                    std::cin.getline(buffer, 100);       
                    
                    if (strlen(buffer) == 0) {           // Проверка на пустую строку
                        std::cout << "Error: Time cannot be empty!" << std::endl;
                        continue;                        
                    }                                
                    
                    if (!TRAIN::isValidTimeFormat(buffer)) { // Проверка формата времени
                        std::cout << "Error: Invalid time format! Must be exactly 5 characters: HH:MM" << std::endl;
                        continue;                
                    }                                    

                    if (!TRAIN::isValidTimeValues(buffer)) { // Проверка значений времени
                        std::cout << "Error: Invalid time values! Hours must be 00-23, minutes must be 00-59" << std::endl;
                        continue;                 
                    }                        
                    
                    try {                                // Блок для обработки исключений
                        train->setDepartureTime(buffer); 
                        validInput = true;            
                        std::cout << "Departure time updated!" << std::endl; 
                    } catch (const std::exception& e) {  // Обработка исключения от сеттера
                        std::cout << "Error: " << e.what() << std::endl; 
                    }                                
                }                                    
                break;                               
            }                                          
            
            case '4': {                           
                editing = false;                        
                std::cout << "Editing completed!" << std::endl; 
                sortByDepartureTime();                 
                break;                               
            }                                        
            
            default: {                                
                break;                            
            }                                       
        }                                           
    }                                              
}                                                    

void TrainManager::displayAllTrains() const {           // Реализация метода отображения всех поездов
    if (size == 0) {                                    // Проверка, пуст ли список
        std::cout << "The train list is empty!" << std::endl; 
        return;                                      
    }                                               
    
    std::cout << "\nAll trains" << std::endl;           // Заголовок вывода
    for (int i = 0; i < size; i++) {                    
        std::cout << i + 1 << ". " << *trains[i] << std::endl; 
    }                                                 
}                                                       

void TrainManager::displayTrainsToDestination(const char* destination) const { // Метод поиска поездов по назначению
    if (size == 0) {                                    // Проверка, пуст ли список
        throw EmptyListException();                     
    }                                               
    
    bool found = false;                                 // Флаг, найден ли хотя бы один поезд
    std::cout << "\nTrains to the destination: " << destination << std::endl;
    
    for (int i = 0; i < size; i++) {                   
        if (strcmp(trains[i]->getDestination(), destination) == 0) { 
            std::cout << *trains[i] << std::endl;       
            found = true;                               
        }                                            
    }                                                  
    
    if (!found) {                                       // Если ни один поезд не найден
        std::cout << "No trains to the specified destination were found!" << std::endl;
    }                                                  
}                                                    

void TrainManager::sortByDepartureTime() {              // Реализация метода сортировки по времени отправления
    if (size <= 1) return;                              // Проверка на необходимость
    
    qsort(trains, size, sizeof(TRAIN*), compareTrainsByTime); 
    
    std::cout << "Trains sorted by departure time using qsort" << std::endl; 
}                                               

TRAIN* TrainManager::getTrain(int index) const {        // Реализация метода получения поезда по индексу
    if (index < 0 || index >= size) {                   // Проверка корректности индекса
        throw InvalidIndexException("Incorrect train index!"); 
    }                                                   
    return trains[index];                               
}                                                      