#include <iostream>
#include <cstring>
#include <conio.h>
#include "trainManager.h"

void displayMenu() {
    std::cout << "\nTrain management menu" << std::endl;
    std::cout << "1. Add a train" << std::endl;
    std::cout << "2. Add a train to a specific position" << std::endl;
    std::cout << "3. Delete a train" << std::endl;
    std::cout << "4. Edit the train" << std::endl;
    std::cout << "5. Show all trains" << std::endl;
    std::cout << "6. Find trains by destination" << std::endl;
    std::cout << "7. Exit\n" << std::endl;
}

int main() {
    TrainManager manager;
    char choice;
    
    do {
        displayMenu();
        choice = _getch();
        
        try {
            switch (choice) {
                case '1': {
                    TRAIN newTrain;
                    std::cin >> newTrain;
                    manager.addTrain(newTrain);
                    std::cout << "The train was added successfully!" << std::endl;
                    break;
                }
                case '2': {
                    int position;
                    std::cout << "Enter the position to add (1-" << manager.getSize() + 1 << "): ";
                    std::cin >> position;
                    TRAIN newTrain;
                    std::cin >> newTrain;
                    manager.addTrainAtPosition(newTrain, position - 1);
                    std::cout << "Train added to position " << position << "!" << std::endl;
                    break;
                }
                case '3': {
                    if (manager.getSize() == 0) {
                        std::cout << "The train list is empty!" << std::endl;
                        break;
                    }
                    manager.displayAllTrains();
                    int index;
                    std::cout << "Enter the number to delete: ";
                    std::cin >> index;
                    manager.removeTrain(index - 1);
                    std::cout << "The train was successfully deleted!" << std::endl;
                    break;
                }
                case '4': {
                    if (manager.getSize() == 0) {
                        std::cout << "The train list is empty!" << std::endl;
                        break;
                    }
                    manager.displayAllTrains();
                    int index;
                    std::cout << "Enter the number to edit: ";
                    std::cin >> index;
                    manager.editTrain(index - 1);
                    std::cout << "The train was edited successfully!" << std::endl;
                    break;
                }
                case '5': {
                    manager.displayAllTrains();
                    break;
                }
                case '6': {
                    if (manager.getSize() == 0) {
                        std::cout << "The train list is empty!" << std::endl;
                        break;
                    }
                    char destination[100];
                    std::cout << "Enter your destination: ";
                    std::cin >> destination;
                    manager.displayTrainsToDestination(destination);
                    break;
                }
                case '7': {
                    std::cout << "Exiting the program..." << std::endl;
                    break;
                }
                default: {
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
    } while (choice != '7');
    
    return 0;
}