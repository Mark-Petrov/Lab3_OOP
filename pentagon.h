#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <stdexcept>

class Pentagon : public Figure {
private:
    std::vector<std::pair<double, double>> vertices;
    bool isValidPentagon() const {
        if (vertices.size() != 5) return false;
        
        std::vector<double> sides;
        for (size_t i = 0; i < 5; ++i) {
            size_t j = (i + 1) % 5;
            sides.push_back(distance(vertices[i], vertices[j]));
        }
        
        const double epsilon = 1e-6;
        for (size_t i = 1; i < sides.size(); ++i) {
            if (std::abs(sides[i] - sides[0]) > epsilon) {
                return false;
            }
        }
        return true;
    }
    
public:
    Pentagon() = default;
    Pentagon(const std::vector<std::pair<double, double>>& verts) 
        : vertices(verts) {
        if (verts.size() != 5) {
            throw std::invalid_argument("Пятиугольник должен иметь 5 вершин");
        }
        if (!isValidPentagon()) {
            throw std::invalid_argument("Некорректный пятиугольник");
        }
    }
    
    Pentagon(const Pentagon& other) : vertices(other.vertices) {}
    Pentagon& operator=(const Pentagon& other) {
        if (this != &other) {
            vertices = other.vertices;
        }
        return *this;
    }
    
    Pentagon(Pentagon&& other) noexcept : vertices(std::move(other.vertices)) {}
    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }
    
    // Унаследованные методы от базы
    std::pair<double, double> getCenter() const override {
        return polygonCenter(vertices);
    }
    
    double getArea() const override {
        return polygonArea(vertices);
    }
    
    void printVertices(std::ostream& os) const override {
        os << "Пятиугольник: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            os << "(" << vertices[i].first << ", " << vertices[i].second << ")";
            if (i < vertices.size() - 1) os << " ";
        }
    }
    
    void readFromStream(std::istream& is) override {
        vertices.clear();
        for (int i = 0; i < 5; ++i) {
            double x, y;
            if (!(is >> x >> y)) {
                throw std::runtime_error("Ошибка чтения координат пятиугольника");
            }
            vertices.emplace_back(x, y);
        }
        
        if (!isValidPentagon()) {
            throw std::runtime_error("Некорректные координаты пятиугольника");
        }
    }
    
    operator double() const override {
        return getArea();
    }
    
    std::unique_ptr<Figure> clone() const override {
        return std::make_unique<Pentagon>(*this);
    }
    
    bool operator==(const Figure& other) const override {
        const Pentagon* ptr = dynamic_cast<const Pentagon*>(&other);
        if (!ptr) return false;
        
        if (vertices.size() != ptr->vertices.size()) return false;
        
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (std::abs(vertices[i].first - ptr->vertices[i].first) > 1e-6 ||
                std::abs(vertices[i].second - ptr->vertices[i].second) > 1e-6) {
                return false;
            }
        }
        return true;
    }
    
    // Геттеры
    const std::vector<std::pair<double, double>>& getVertices() const { return vertices; }
};

#endif