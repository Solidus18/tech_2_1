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
    TRAIN();
    TRAIN(const char* dest, int number, const char* time);
    TRAIN(const TRAIN& other);
    
    ~TRAIN();
    
    TRAIN& operator=(const TRAIN& other);
    
    const char* getDestination() const { return destination; }
    int getTrainNumber() const { return trainNumber; }
    const char* getDepartureTime() const { return departureTime; }
    
    void setDestination(const char* dest);
    void setTrainNumber(int number);
    void setDepartureTime(const char* time);
    
    static bool isValidTrainNumber(int number);
    static bool isValidTimeFormat(const char* time);
    static bool isValidTimeValues(const char* time);
    
    int getTimeInMinutes() const;
    
    friend std::ostream& operator<<(std::ostream& os, const TRAIN& train);
    friend std::istream& operator>>(std::istream& is, TRAIN& train);
};

#endif