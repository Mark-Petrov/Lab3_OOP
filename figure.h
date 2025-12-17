#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>

class Figure {
public:
    virtual ~Figure() = default;
    
    virtual std::pair<double, double> getCenter() const = 0;
    
    virtual double getArea() const = 0;
    
    virtual void printVertices(std::ostream& os) const = 0;
    
    virtual void readFromStream(std::istream& is) = 0;
    
    virtual operator double() const = 0;
    
    virtual std::unique_ptr<Figure> clone() const = 0;
    
    virtual bool operator==(const Figure& other) const = 0;
    virtual bool operator!=(const Figure& other) const {
        return !(*this == other);
    }
    
protected:
    double distance(const std::pair<double, double>& p1, 
                   const std::pair<double, double>& p2) const {
        double dx = p1.first - p2.first;
        double dy = p1.second - p2.second;
        return std::sqrt(dx*dx + dy*dy);
    }
    
    double polygonArea(const std::vector<std::pair<double, double>>& vertices) const {
        if (vertices.size() < 3) return 0.0;
        
        double area = 0.0;
        int n = vertices.size();
        
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += vertices[i].first * vertices[j].second;
            area -= vertices[j].first * vertices[i].second;
        }
        
        return std::abs(area) / 2.0;
    }
    
    std::pair<double, double> polygonCenter(const std::vector<std::pair<double, double>>& vertices) const {
        double sumX = 0.0, sumY = 0.0;
        for (const auto& v : vertices) {
            sumX += v.first;
            sumY += v.second;
        }
        return {sumX / vertices.size(), sumY / vertices.size()};
    }
};

// Перегрузка оператора вывода
inline std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.printVertices(os);
    return os;
}

// Перегрузка оператора ввода
inline std::istream& operator>>(std::istream& is, Figure& figure) {
    figure.readFromStream(is);
    return is;
}

#endif