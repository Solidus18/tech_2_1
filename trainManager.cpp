#include "trainManager.h"
#include <iostream>
#include <algorithm>
#include <cstring>

class InvalidIndexException : public std::exception {
private:
    char* message;
public:
    InvalidIndexException(const char* msg) {
        message = new char[strlen(msg) + 1];
        strcpy(message, msg);
    }
    
    ~InvalidIndexException() {
        delete[] message;
    }
    
    const char* what() const noexcept override {
        return message;
    }
};

class EmptyListException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Список поездов пуст!";
    }
};

TrainManager::TrainManager() : capacity(10), size(0) {
    trains = new TRAIN*[capacity];
    for (int i = 0; i < capacity; i++) {
        trains[i] = nullptr;
    }
    std::cout << "Вызван конструктор TrainManager" << std::endl;
}

TrainManager::~TrainManager() {
    for (int i = 0; i < size; i++) {
        delete trains[i];
    }
    delete[] trains;
    std::cout << "Вызван деструктор TrainManager" << std::endl;
}

void TrainManager::resize() {
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

void TrainManager::addTrain(const TRAIN& train) {
    if (size >= capacity) {
        resize();
    }
    trains[size] = new TRAIN(train);
    size++;
    sortByDepartureTime();
}

void TrainManager::addTrainAtPosition(const TRAIN& train, int position) {
    if (position < 0 || position > size) {
        throw InvalidIndexException("Неверная позиция для добавления поезда!");
    }
    
    if (size >= capacity) {
        resize();
    }
    
    for (int i = size; i > position; i--) {
        trains[i] = trains[i - 1];
    }
    trains[position] = new TRAIN(train);
    size++;
    sortByDepartureTime();
}

void TrainManager::removeTrain(int index) {
    if (size == 0) {
        throw EmptyListException();
    }
    if (index < 0 || index >= size) {
        throw InvalidIndexException("Неверный индекс для удаления поезда!");
    }
    
    delete trains[index];
    for (int i = index; i < size - 1; i++) {
        trains[i] = trains[i + 1];
    }
    trains[size - 1] = nullptr;
    size--;
}

void TrainManager::editTrain(int index) {
    if (index < 0 || index >= size) {
        throw InvalidIndexException("Неверный индекс для редактирования поезда!");
    }
    
    std::cout << "Редактирование поезда #" << index + 1 << std::endl;
    std::cin >> *trains[index];
    sortByDepartureTime();
}

void TrainManager::displayAllTrains() const {
    if (size == 0) {
        std::cout << "Список поездов пуст!" << std::endl;
        return;
    }
    
    std::cout << "\n=== Все поезда ===" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << ". " << *trains[i] << std::endl;
    }
}

void TrainManager::displayTrainsToDestination(const char* destination) const {
    if (size == 0) {
        throw EmptyListException();
    }
    
    bool found = false;
    std::cout << "\n=== Поезда в пункт: " << destination << " ===" << std::endl;
    
    for (int i = 0; i < size; i++) {
        if (strcmp(trains[i]->getDestination(), destination) == 0) {
            std::cout << *trains[i] << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "Поездов в указанный пункт назначения не найдено!" << std::endl;
    }
}

void TrainManager::sortByDepartureTime() {
    if (size <= 1) return;
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (trains[j]->getTimeInMinutes() > trains[j + 1]->getTimeInMinutes()) {
                TRAIN* temp = trains[j];
                trains[j] = trains[j + 1];
                trains[j + 1] = temp;
            }
        }
    }
}

TRAIN* TrainManager::getTrain(int index) const {
    if (index < 0 || index >= size) {
        throw InvalidIndexException("Неверный индекс поезда!");
    }
    return trains[index];
}