#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <stdexcept>

class Trapezoid : public Figure {
private:
    std::vector<std::pair<double, double>> vertices;
    bool isValidTrapezoid() const {
        if (vertices.size() != 4) return false;
        
        double dx1 = vertices[1].first - vertices[0].first;
        double dy1 = vertices[1].second - vertices[0].second;
        double dx2 = vertices[2].first - vertices[3].first;
        double dy2 = vertices[2].second - vertices[3].second;
        
        double cross1 = dx1 * dy2 - dy1 * dx2;
        
        dx1 = vertices[3].first - vertices[0].first;
        dy1 = vertices[3].second - vertices[0].second;
        dx2 = vertices[2].first - vertices[1].first;
        dy2 = vertices[2].second - vertices[1].second;
        
        double cross2 = dx1 * dy2 - dy1 * dx2;
        
        const double epsilon = 1e-6;
        return std::abs(cross1) < epsilon || std::abs(cross2) < epsilon;
    }
    
public:
    Trapezoid() = default;
    Trapezoid(const std::vector<std::pair<double, double>>& verts) 
        : vertices(verts) {
        if (verts.size() != 4) {
            throw std::invalid_argument("Трапеция должна иметь 4 вершины");
        }
        if (!isValidTrapezoid()) {
            throw std::invalid_argument("Некорректная трапеция");
        }
    }
    
    Trapezoid(const Trapezoid& other) : vertices(other.vertices) {}
    Trapezoid& operator=(const Trapezoid& other) {
        if (this != &other) {
            vertices = other.vertices;
        }
        return *this;
    }
    
    Trapezoid(Trapezoid&& other) noexcept : vertices(std::move(other.vertices)) {}
    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }
    
    std::pair<double, double> getCenter() const override {
        return polygonCenter(vertices);
    }
    
    double getArea() const override {
        return polygonArea(vertices);
    }
    
    void printVertices(std::ostream& os) const override {
        os << "Трапеция: ";
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
                throw std::runtime_error("Ошибка чтения координат трапеции");
            }
            vertices.emplace_back(x, y);
        }
        
        if (!isValidTrapezoid()) {
            throw std::runtime_error("Некорректные координаты трапеции");
        }
    }
    
    operator double() const override {
        return getArea();
    }
    
    std::unique_ptr<Figure> clone() const override {
        return std::make_unique<Trapezoid>(*this);
    }
    
    bool operator==(const Figure& other) const override {
        const Trapezoid* ptr = dynamic_cast<const Trapezoid*>(&other);
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
    
    const std::vector<std::pair<double, double>>& getVertices() const { return vertices; }
};

#endif