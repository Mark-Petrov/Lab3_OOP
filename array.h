#ifndef ARRAY_H
#define ARRAY_H

#include "figure.h"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>

class FigureArray {
private:
    std::vector<std::unique_ptr<Figure>> figures;
    
public:
    FigureArray() = default;
    FigureArray(const FigureArray& other) {
        for (const auto& fig : other.figures) {
            figures.push_back(fig->clone());
        }
    }
    
    FigureArray(FigureArray&& other) noexcept 
        : figures(std::move(other.figures)) {
    }
    
    // Операторы присваиваний
    FigureArray& operator=(const FigureArray& other) {
        if (this != &other) {
            figures.clear();
            for (const auto& fig : other.figures) {
                figures.push_back(fig->clone());
            }
        }
        return *this;
    }
    
    FigureArray& operator=(FigureArray&& other) noexcept {
        if (this != &other) {
            figures = std::move(other.figures);
        }
        return *this;
    }
    
    void addFigure(std::unique_ptr<Figure> figure) {
        figures.push_back(std::move(figure));
    }
    
    void removeFigure(size_t index) {
        if (index < figures.size()) {
            figures.erase(figures.begin() + index);
        } else {
            throw std::out_of_range("Индекс вне диапазона");
        }
    }
    
    Figure* getFigure(size_t index) const {
        if (index < figures.size()) {
            return figures[index].get();
        }
        throw std::out_of_range("Индекс вне диапазона");
    }
    
    size_t size() const { return figures.size(); }
    
    void printAll() const {
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << "Фигура " << i + 1 << ":\n";
            std::cout << "  Вершины: " << *figures[i] << "\n";
            
            auto center = figures[i]->getCenter();
            std::cout << "  Центр: (" << center.first << ", " << center.second << ")\n";
            
            std::cout << "  Площадь: " << static_cast<double>(*figures[i]) << "\n";
            std::cout << std::endl;
        }
    }
    
    double totalArea() const {
        double total = 0.0;
        for (const auto& fig : figures) {
            total += static_cast<double>(*fig);
        }
        return total;
    }
    
    void clear() { figures.clear(); }
    
    // Оператор сравнения
    bool operator==(const FigureArray& other) const {
        if (figures.size() != other.figures.size()) {
            return false;
        }
        
        for (size_t i = 0; i < figures.size(); ++i) {
            if (!(*figures[i] == *other.figures[i])) {
                return false;
            }
        }
        return true;
    }
    
    bool operator!=(const FigureArray& other) const { 
        return !(*this == other); 
    }
};

#endif