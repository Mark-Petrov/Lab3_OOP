#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <stdexcept>

class Rhombus : public Figure {
private:
    std::vector<std::pair<double, double>> vertices;
    bool isValidRhombus() const {
        if (vertices.size() != 4) return false;
        
        double side1 = distance(vertices[0], vertices[1]);
        double side2 = distance(vertices[1], vertices[2]);
        double side3 = distance(vertices[2], vertices[3]);
        double side4 = distance(vertices[3], vertices[0]);
        
        const double epsilon = 1e-6;
        return std::abs(side1 - side2) < epsilon &&
               std::abs(side2 - side3) < epsilon &&
               std::abs(side3 - side4) < epsilon;
    }
    
public:
    Rhombus() = default;
    Rhombus(const std::vector<std::pair<double, double>>& verts) 
        : vertices(verts) {
        if (verts.size() != 4) {
            throw std::invalid_argument("Ромб должен иметь 4 вершины");
        }
        if (!isValidRhombus()) {
            throw std::invalid_argument("Некорректный ромб");
        }
    }
    
    Rhombus(const Rhombus& other) : vertices(other.vertices) {}
    Rhombus& operator=(const Rhombus& other) {
        if (this != &other) {
            vertices = other.vertices;
        }
        return *this;
    }
    
    Rhombus(Rhombus&& other) noexcept : vertices(std::move(other.vertices)) {}
    Rhombus& operator=(Rhombus&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }
    
    std::pair<double, double> getCenter() const override {
        return polygonCenter(vertices);
    }
    
    double getArea() const override {
        double d1 = distance(vertices[0], vertices[2]);
        double d2 = distance(vertices[1], vertices[3]);
        return 0.5 * d1 * d2;
    }
    
    void printVertices(std::ostream& os) const override {
        os << "Ромб: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            os << "(" << vertices[i].first << ", " << vertices[i].second << ")";
            if (i < vertices.size() - 1) os << " ";
        }
    }
    
    void readFromStream(std::istream& is) override {
        vertices.clear();
        for (int i = 0; i < 4; ++i) {
            double x, y;
            if (!(is >> x >> y)) {
                throw std::runtime_error("Ошибка чтения координат ромба");
            }
            vertices.emplace_back(x, y);
        }
        
        if (!isValidRhombus()) {
            throw std::runtime_error("Некорректные координаты ромба");
        }
    }
    
    operator double() const override {
        return getArea();
    }
    
    std::unique_ptr<Figure> clone() const override {
        return std::make_unique<Rhombus>(*this);
    }
    
    bool operator==(const Figure& other) const override {
        const Rhombus* ptr = dynamic_cast<const Rhombus*>(&other);
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