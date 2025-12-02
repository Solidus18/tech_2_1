#include "train.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>

class InvalidTrainNumberException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid train number! Must be positive integer.";
    }
};

class InvalidTimeFormatException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid time format! Must be exactly 5 characters: HH:MM (example: 08:30).";
    }
};

class InvalidTimeValuesException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid time values! Hours: 00-23, Minutes: 00-59.";
    }
};

TRAIN::TRAIN() : destination(nullptr), trainNumber(0), departureTime(nullptr) {
    destination = new char[1];
    destination[0] = '\0';
    departureTime = new char[6];
    strcpy(departureTime, "00:00");
    std::cout << "Default constructor called for TRAIN" << std::endl;
}

TRAIN::TRAIN(const char* dest, int number, const char* time) {
    if (!isValidTrainNumber(number)) {
        throw InvalidTrainNumberException();
    }
    
    if (!isValidTimeFormat(time)) {
        throw InvalidTimeFormatException();
    }
    
    if (!isValidTimeValues(time)) {
        throw InvalidTimeValuesException();
    }
    
    destination = new char[strlen(dest) + 1];
    strcpy(destination, dest);
    
    trainNumber = number;
    
    departureTime = new char[6];
    strcpy(departureTime, time);
    
    std::cout << "Parameterized constructor called for TRAIN: " << destination << std::endl;
}

TRAIN::TRAIN(const TRAIN& other) : trainNumber(other.trainNumber) {
    destination = new char[strlen(other.destination) + 1];
    strcpy(destination, other.destination);
    
    departureTime = new char[6];
    strcpy(departureTime, other.departureTime);
    
    std::cout << "Copy constructor called for TRAIN: " << destination << std::endl;
}

TRAIN::~TRAIN() {
    std::cout << "Destructor called for TRAIN: " << (destination ? destination : "unknown") << std::endl;
    delete[] destination;
    delete[] departureTime;
}

TRAIN& TRAIN::operator=(const TRAIN& other) {
    if (this != &other) {
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

void TRAIN::setDestination(const char* dest) {
    delete[] destination;
    destination = new char[strlen(dest) + 1];
    strcpy(destination, dest);
}

void TRAIN::setTrainNumber(int number) {
    if (!isValidTrainNumber(number)) {
        throw InvalidTrainNumberException();
    }
    trainNumber = number;
}

void TRAIN::setDepartureTime(const char* time) {
    if (!isValidTimeFormat(time)) {
        throw InvalidTimeFormatException();
    }
    
    if (!isValidTimeValues(time)) {
        throw InvalidTimeValuesException();
    }
    
    delete[] departureTime;
    departureTime = new char[6];
    strcpy(departureTime, time);
}

bool TRAIN::isValidTrainNumber(int number) {
    return number > 0;
}

bool TRAIN::isValidTimeFormat(const char* time) {
    if (time == nullptr || strlen(time) == 0) {
        return false;
    }
    
    if (strlen(time) != 5) {
        return false;
    }
    
    for (int i = 0; i < 5; i++) {
        if (i == 2) {
            if (time[i] != ':') {
                return false;
            }
        } else {
            if (!isdigit(time[i])) {
                return false;
            }
        }
    }
    
    return true;
}

bool TRAIN::isValidTimeValues(const char* time) {
    char hourStr[3] = {time[0], time[1], '\0'};
    char minuteStr[3] = {time[3], time[4], '\0'};
    
    int hours = atoi(hourStr);
    int minutes = atoi(minuteStr);
    
    if (hours < 0 || hours > 23) {
        return false;
    }
    
    if (minutes < 0 || minutes > 59) {
        return false;
    }
    
    return true;
}

int TRAIN::getTimeInMinutes() const {
    char hourStr[3] = {departureTime[0], departureTime[1], '\0'};
    char minuteStr[3] = {departureTime[3], departureTime[4], '\0'};
    
    int hours = atoi(hourStr);
    int minutes = atoi(minuteStr);
    
    return hours * 60 + minutes;
}

std::ostream& operator<<(std::ostream& os, const TRAIN& train) {
    os << "Destination: " << train.destination 
       << ", Train number: " << train.trainNumber 
       << ", Departure time: " << train.departureTime;
    return os;
}

std::istream& operator>>(std::istream& is, TRAIN& train) {
    char buffer[100];
    int number;
    
    bool validInput = false;
    while (!validInput) {
        std::cout << "Enter destination: ";
        is >> buffer;
        
        if (strlen(buffer) > 0) {
            train.setDestination(buffer);
            validInput = true;
        } else {
            std::cout << "Error: Destination cannot be empty!" << std::endl;
        }
    }
    
    validInput = false;
    while (!validInput) {
        std::cout << "Enter train number (positive integer): ";
        
        if (!(is >> number)) {
            std::cout << "Error: Please enter a valid integer number!" << std::endl;
            is.clear();
            is.ignore(10000, '\n');
            continue;
        }
        
        if (!TRAIN::isValidTrainNumber(number)) {
            std::cout << "Error: Train number must be positive (greater than 0)!" << std::endl;
            is.ignore(10000, '\n');
            continue;
        }
        
        try {
            train.setTrainNumber(number);
            validInput = true;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    validInput = false;
    is.ignore(10000, '\n');
    
    while (!validInput) {
        std::cout << "Enter departure time (HH:MM, 00:00 to 23:59, exactly 5 characters): ";
        
        is.getline(buffer, 100);
        
        if (strlen(buffer) == 0) {
            std::cout << "Error: Time cannot be empty!" << std::endl;
            continue;
        }
        
        if (!TRAIN::isValidTimeFormat(buffer)) {
            std::cout << "Error: Invalid time format! Must be exactly 5 characters: HH:MM (example: 08:30, 14:05)" << std::endl;
            continue;
        }
        
        if (!TRAIN::isValidTimeValues(buffer)) {
            std::cout << "Error: Invalid time values! Hours must be 00-23, minutes must be 00-59" << std::endl;
            continue;
        }
        
        try {
            train.setDepartureTime(buffer);
            validInput = true;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    return is;
}