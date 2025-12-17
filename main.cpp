#include "figure.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"
#include "array.h"
#include <iostream>
#include <memory>
#include <limits>

// Функция для создания фигуры по выбору пользователя
std::unique_ptr<Figure> createFigure(int choice) {
    std::cout << "Введите координаты вершин (x y):\n";
    
    if (choice == 1) {
        // Трапеция
        std::vector<std::pair<double, double>> vertices;
        std::cout << "Трапеция (4 вершины):\n";
        for (int i = 0; i < 4; ++i) {
            double x, y;
            std::cout << "Вершина " << i + 1 << ": ";
            if (!(std::cin >> x >> y)) {
                throw std::runtime_error("Ошибка ввода координат");
            }
            vertices.emplace_back(x, y);
        }
        return std::make_unique<Trapezoid>(vertices);
    }
    else if (choice == 2) {
        // Ромб
        std::vector<std::pair<double, double>> vertices;
        std::cout << "Ромб (4 вершины):\n";
        for (int i = 0; i < 4; ++i) {
            double x, y;
            std::cout << "Вершина " << i + 1 << ": ";
            if (!(std::cin >> x >> y)) {
                throw std::runtime_error("Ошибка ввода координат");
            }
            vertices.emplace_back(x, y);
        }
        return std::make_unique<Rhombus>(vertices);
    }
    else if (choice == 3) {
        // Пятиугольник
        std::vector<std::pair<double, double>> vertices;
        std::cout << "Пятиугольник (5 вершин):\n";
        for (int i = 0; i < 5; ++i) {
            double x, y;
            std::cout << "Вершина " << i + 1 << ": ";
            if (!(std::cin >> x >> y)) {
                throw std::runtime_error("Ошибка ввода координат");
            }
            vertices.emplace_back(x, y);
        }
        return std::make_unique<Pentagon>(vertices);
    }
    
    return nullptr;
}

int main() {
    FigureArray figures;
    
    std::cout << "Программа для работы с фигурами вращения\n";
    std::cout << "Для запуска тестов запустить - ./geometry_figures\n";
    std::cout << "========================================\n";
    
    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить фигуру\n";
        std::cout << "2. Удалить фигуру по индексу\n";
        std::cout << "3. Вывести информацию о всех фигурах\n";
        std::cout << "4. Вывести общую площадь\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите действие: ";
        
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод!\n";
            continue;
        }
        
        try {
            switch (choice) {
                case 1: {
                    std::cout << "\nВыберите тип фигуры:\n";
                    std::cout << "1. Трапеция\n";
                    std::cout << "2. Ромб\n";
                    std::cout << "3. Пятиугольник\n";
                    std::cout << "Выбор: ";
                    
                    int figureType;
                    if (!(std::cin >> figureType)) {
                        throw std::runtime_error("Ошибка ввода типа фигуры");
                    }
                    
                    if (figureType >= 1 && figureType <= 3) {
                        auto figure = createFigure(figureType);
                        if (figure) {
                            figures.addFigure(std::move(figure));
                            std::cout << "Фигура добавлена успешно!\n";
                        }
                    } else {
                        std::cout << "Некорректный тип фигуры!\n";
                    }
                    break;
                }
                
                case 2: {
                    if (figures.size() == 0) {
                        std::cout << "Нет фигур для удаления.\n";
                        break;
                    }
                    
                    std::cout << "Введите индекс фигуры (1-" << figures.size() << "): ";
                    size_t index;
                    if (!(std::cin >> index)) {
                        throw std::runtime_error("Ошибка ввода индекса");
                    }
                    
                    if (index >= 1 && index <= figures.size()) {
                        figures.removeFigure(index - 1);
                        std::cout << "Фигура удалена успешно!\n";
                    } else {
                        std::cout << "Некорректный индекс!\n";
                    }
                    break;
                }
                
                case 3: {
                    if (figures.size() == 0) {
                        std::cout << "Нет фигур для отображения.\n";
                    } else {
                        figures.printAll();
                    }
                    break;
                }
                
                case 4: {
                    double total = figures.totalArea();
                    std::cout << "Общая площадь всех фигур: " << total << "\n";
                    break;
                }
                
                case 5: {
                    std::cout << "Выход из программы.\n";
                    return 0;
                }
                
                default: {
                    std::cout << "Некорректный выбор!\n";
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
    return 0;
}