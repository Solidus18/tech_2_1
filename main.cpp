#include <iostream>
#include <cstring>
#include "trainManager.h"

void displayMenu() {
    std::cout << "\n=== Меню управления поездами ===" << std::endl;
    std::cout << "1. Добавить поезд" << std::endl;
    std::cout << "2. Добавить поезд на определенную позицию" << std::endl;
    std::cout << "3. Удалить поезд" << std::endl;
    std::cout << "4. Редактировать поезд" << std::endl;
    std::cout << "5. Показать все поезда" << std::endl;
    std::cout << "6. Найти поезда по пункту назначения" << std::endl;
    std::cout << "7. Выход" << std::endl;
    std::cout << "Выберите опцию: ";
}

int main() {
    TrainManager manager;
    int choice;
    
    // Добавим несколько тестовых поездов
    try {
        manager.addTrain(TRAIN("Москва", 101, "08:30"));
        manager.addTrain(TRAIN("Санкт-Петербург", 205, "14:15"));
        manager.addTrain(TRAIN("Москва", 78, "22:45"));
    } catch (const std::exception& e) {
        std::cout << "Ошибка при инициализации: " << e.what() << std::endl;
    }
    
    do {
        displayMenu();
        std::cin >> choice;
        
        try {
            switch (choice) {
                case 1: {
                    TRAIN newTrain;
                    std::cin >> newTrain;
                    manager.addTrain(newTrain);
                    std::cout << "Поезд добавлен успешно!" << std::endl;
                    break;
                }
                case 2: {
                    int position;
                    std::cout << "Введите позицию для добавления (1-" << manager.getSize() + 1 << "): ";
                    std::cin >> position;
                    TRAIN newTrain;
                    std::cin >> newTrain;
                    manager.addTrainAtPosition(newTrain, position - 1);
                    std::cout << "Поезд добавлен на позицию " << position << "!" << std::endl;
                    break;
                }
                case 3: {
                    if (manager.getSize() == 0) {
                        std::cout << "Список поездов пуст!" << std::endl;
                        break;
                    }
                    manager.displayAllTrains();
                    int index;
                    std::cout << "Введите номер поезда для удаления: ";
                    std::cin >> index;
                    manager.removeTrain(index - 1);
                    std::cout << "Поезд удален успешно!" << std::endl;
                    break;
                }
                case 4: {
                    if (manager.getSize() == 0) {
                        std::cout << "Список поездов пуст!" << std::endl;
                        break;
                    }
                    manager.displayAllTrains();
                    int index;
                    std::cout << "Введите номер поезда для редактирования: ";
                    std::cin >> index;
                    manager.editTrain(index - 1);
                    std::cout << "Поезд отредактирован успешно!" << std::endl;
                    break;
                }
                case 5: {
                    manager.displayAllTrains();
                    break;
                }
                case 6: {
                    if (manager.getSize() == 0) {
                        std::cout << "Список поездов пуст!" << std::endl;
                        break;
                    }
                    char destination[100];
                    std::cout << "Введите пункт назначения: ";
                    std::cin >> destination;
                    manager.displayTrainsToDestination(destination);
                    break;
                }
                case 7: {
                    std::cout << "Выход из программы..." << std::endl;
                    break;
                }
                default: {
                    std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        
    } while (choice != 8);
    
    return 0;
}