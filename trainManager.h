#ifndef TRAINMANAGER_H    
#define TRAINMANAGER_H    

#include "train.h"       

class TrainManager {      
private:                  
    TRAIN** trains;       // Указатель на массив указателей на объекты TRAIN
    int capacity;         // Текущая вместимость массива 
    int size;             // Фактическое количество элементов в массиве
    
    void resize();       
    
public:                
    TrainManager();       // Конструктор
    ~TrainManager();      // Деструктор
    
    // Основные методы управления поездами:
    void addTrain(const TRAIN& train);                          // Добавить поезд в конец
    void addTrainAtPosition(const TRAIN& train, int position);  // Добавить поезд на указанную позицию
    void removeTrain(int index);                                // Удалить поезд по индексу
    void editTrain(int index);                                  // Редактировать поезд по индексу
    
    // Методы отображения информации:
    void displayAllTrains() const;                                  // Показать все поезда
    void displayTrainsToDestination(const char* destination) const; // Найти поезда по пункту назначения
    
    void sortByDepartureTime();                                 // Сортировать поезда по времени отправления
    
    int getSize() const { return size; }                        // Получить количество поездов
    
    TRAIN* getTrain(int index) const;                           // Получить поезд по индексу
};

#endif 