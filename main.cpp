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
    TrainManager manager; // Создание объекта класса TrainManager
    char choice;        
    
    do {           
        displayMenu();   
        choice = _getch(); 
        
        try {             
            switch (choice) { 
                case '1': { 
                    TRAIN newTrain;  // Создание временного объекта TRAIN с именем newTrain
                    std::cin >> newTrain; // Использование перегруженного оператора >> для ввода данных поезда
                    manager.addTrain(newTrain); // Вызов метода addTrain объекта manager для добавления поезда
                    std::cout << "The train was added successfully!" << std::endl;
                    break; 
                }    
                case '2': { 
                    int position; // Объявление переменной для хранения позиции
                    std::cout << "Enter the position to add (1-" << manager.getSize() + 1 << "): "; 
                    std::cin >> position; // Чтение значения position из стандартного потока ввода
                    TRAIN newTrain; // Создание временного объекта TRAIN
                    std::cin >> newTrain; // Ввод данных поезда
                    manager.addTrainAtPosition(newTrain, position - 1); // Вызов метода добавления на позицию (position-1 для индексации с 0)
                    std::cout << "Train added to position " << position << "!" << std::endl; 
                    break; 
                }          
                case '3': {
                    if (manager.getSize() == 0) { // Проверка, пуст ли список поездов
                        std::cout << "The train list is empty!" << std::endl; 
                        break; 
                    }         
                    manager.displayAllTrains(); // Вызов метода отображения всех поездов
                    int index; 
                    std::cout << "Enter the number to delete: "; 
                    std::cin >> index; // Чтение значения index
                    manager.removeTrain(index - 1); // Вызов метода удаления (index-1 для индексации с 0)
                    std::cout << "The train was successfully deleted!" << std::endl; // Вывод подтверждения
                    break; 
                }          
                case '4': { 
                    if (manager.getSize() == 0) { // Проверка, пуст ли список
                        std::cout << "The train list is empty!" << std::endl; 
                        break; 
                    }  
                    manager.displayAllTrains(); // Отображение всех поездов
                    int index; 
                    std::cout << "Enter the number to edit: "; 
                    std::cin >> index; // Чтение значения index
                    manager.editTrain(index - 1); // Вызов метода редактирования (index-1 для индексации с 0)
                    std::cout << "The train was edited successfully!" << std::endl; // Подтверждение редактирования
                    break; 
                }    
                case '5': { 
                    manager.displayAllTrains(); // Вызов метода отображения всех поездов
                    break; 
                }          
                case '6': { 
                    if (manager.getSize() == 0) { // Проверка, пуст ли список
                        std::cout << "The train list is empty!" << std::endl;
                        break; 
                    }      
                    char destination[100]; // Объявление массива символов для хранения пункта назначения
                    std::cout << "Enter your destination: "; 
                    std::cin >> destination; // Чтение строки destination
                    manager.displayTrainsToDestination(destination); // Вызов метода поиска по назначению
                    break; 
                }         
                case '7': { 
                    std::cout << "Exiting the program..." << std::endl; // Вывод сообщения о выходе
                    break; 
                }         
                default: { 
                    break; 
                }         
            }             
        } catch (const std::exception& e) { // Начало блока catch для обработки исключений типа std::exception
            std::cout << "Error: " << e.what() << std::endl; 
        }                 
        
    } while (choice != '7'); 
    
    return 0;             
}                     