#include "trainManager.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <conio.h>

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
        return "The train list is empty!";
    }
};

TrainManager::TrainManager() : capacity(10), size(0) {
    trains = new TRAIN*[capacity];
    for (int i = 0; i < capacity; i++) {
        trains[i] = nullptr;
    }
    std::cout << "The constructor TrainManager is called" << std::endl;
}

TrainManager::~TrainManager() {
    for (int i = 0; i < size; i++) {
        delete trains[i];
    }
    delete[] trains;
    std::cout << "The destructor TrainManager is called" << std::endl;
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
        throw InvalidIndexException("Incorrect position for adding a train!");
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
        throw InvalidIndexException("Invalid index for deleting a train!");
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
        std::cout << "\n--- Edit Menu ---" << std::endl;
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
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        continue;
                    }
                    
                    if (TRAIN::isValidTrainNumber(number)) {
                        try {
                            train->setTrainNumber(number);
                            validInput = true;
                            std::cout << "Train number updated!" << std::endl;
                        } catch (const std::exception& e) {
                            std::cout << "Error: " << e.what() << std::endl;
                        }
                    } else {
                        std::cout << "Error: Train number must be positive (greater than 0)!" << std::endl;
                        std::cin.ignore(10000, '\n');
                    }
                }
                break;
            }
            
            case '3': { 
                std::cout << "Current departure time: " << train->getDepartureTime() << std::endl;
                
                bool validInput = false;
                std::cin.ignore(10000, '\n');
                
                while (!validInput) {
                    std::cout << "Enter new departure time (HH:MM, 00:00 to 23:59, exactly 5 characters): ";
                    std::cin.getline(buffer, 100);
                    
                    if (strlen(buffer) == 0) {
                        std::cout << "Error: Time cannot be empty!" << std::endl;
                        continue;
                    }
                    
                    if (!TRAIN::isValidTimeFormat(buffer)) {
                        std::cout << "Error: Invalid time format! Must be exactly 5 characters: HH:MM" << std::endl;
                        continue;
                    }
                    
                    if (!TRAIN::isValidTimeValues(buffer)) {
                        std::cout << "Error: Invalid time values! Hours must be 00-23, minutes must be 00-59" << std::endl;
                        continue;
                    }
                    
                    try {
                        train->setDepartureTime(buffer);
                        validInput = true;
                        std::cout << "Departure time updated!" << std::endl;
                    } catch (const std::exception& e) {
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

void TrainManager::displayAllTrains() const {
    if (size == 0) {
        std::cout << "The train list is empty!" << std::endl;
        return;
    }
    
    std::cout << "\nAll trains" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << ". " << *trains[i] << std::endl;
    }
}

void TrainManager::displayTrainsToDestination(const char* destination) const {
    if (size == 0) {
        throw EmptyListException();
    }
    
    bool found = false;
    std::cout << "\nTrains to the destination: " << destination << std::endl;
    
    for (int i = 0; i < size; i++) {
        if (strcmp(trains[i]->getDestination(), destination) == 0) {
            std::cout << *trains[i] << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No trains to the specified destination were found!" << std::endl;
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
        throw InvalidIndexException("Incorrect train index!");
    }
    return trains[index];
}