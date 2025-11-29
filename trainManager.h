#ifndef TRAINMANAGER_H
#define TRAINMANAGER_H

#include "train.h"

class TrainManager {
private:
    TRAIN** trains;
    int capacity;
    int size;
    
    void resize();
    
public:
    TrainManager();
    ~TrainManager();
    
    void addTrain(const TRAIN& train);
    void addTrainAtPosition(const TRAIN& train, int position);
    void removeTrain(int index);
    void editTrain(int index);
    void displayAllTrains() const;
    void displayTrainsToDestination(const char* destination) const;
    void sortByDepartureTime();
    int getSize() const { return size; }
    TRAIN* getTrain(int index) const;
};

#endif