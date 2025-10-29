#ifndef FIGURE_TPP
#define FIGURE_TPP
#include "figure.h"
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.print(os);
    return os;
}

double Circle::area() const{
    return PI * r_ * r_;
}

double Circle::perimeter() const{
    return 2 * PI * r_;
}

Figure& Circle::operator=(const Figure& other){
    const Circle* figure = dynamic_cast<const Circle*>(&other);
    if(!figure){
        throw std::bad_cast();
    }
    return operator=(*figure);
}

void Circle::print(std::ostream& os) const{
    os << "Circle info: \nr = " << r_ << "\narea = " << area() << "\nperimeter = " << perimeter() << std::endl;
}

double Rectangle::area() const{
    return a_ * b_;
}

double Rectangle::perimeter() const{
    return 2 * (a_ + b_);
}

Figure& Rectangle::operator=(const Figure& other){
    const Rectangle* figure = dynamic_cast<const Rectangle*>(&other);
    if(!figure){
        throw std::bad_cast();
    }
    return operator=(*figure);
}

void Rectangle::print(std::ostream& os) const{
    os << "Rectangle info: \na, b = " << a_ << ", "<< b_ << "\narea = " << area() << "\nperimeter = " << perimeter() << std::endl;
}

double Ellipse::area() const{
    return PI * a_ * b_;
}

double Ellipse::perimeter() const{
    return PI * sqrt(2 * (a_ * a_ + b_ * b_));
}

Figure& Ellipse::operator=(const Figure& other){
    const Ellipse* figure = dynamic_cast<const Ellipse*>(&other);
    if(!figure){
        throw std::bad_cast();
    }
    return operator=(*figure);
}

void Ellipse::print(std::ostream& os) const{
    os << "Ellipse info: \na, b = " << a_ << ", "<< b_ << "\narea = " << area() << "\nperimeter = " << perimeter() << std::endl;
}

#endif
