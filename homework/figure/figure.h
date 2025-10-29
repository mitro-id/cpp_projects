#ifndef FIGURE_H
#define FIGURE_H
#define PI 3.1415926535

#include <iostream>

class Figure{
public:
    //methods
    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    //destructor
    virtual ~Figure() = default;

    //operator=
    virtual Figure& operator=(const Figure& other){return *this;};

    //print
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);

protected:
    virtual void print(std::ostream& os) const = 0;
};


class Circle: public Figure{
private:
    double r_;

public:
    Circle(double r): r_(r){
        if(r <= 0) throw std::runtime_error("Incorrect radius value");
    }
    double area() const;
    double perimeter() const;

    Circle& operator=(const Circle& other) = default;
    Figure& operator=(const Figure& other) override;

protected:
    void print(std::ostream& os) const override;
};

class Rectangle: public Figure{
private:
    double a_, b_;

public:
    Rectangle(double a, double b): a_(a), b_(b){
        if(a_ <= 0 || b_ <= 0) throw std::runtime_error("Incorrect width or height");
    }
    double area() const;
    double perimeter() const;

    Rectangle& operator=(const Rectangle& other) = default;
    Figure& operator=(const Figure& other) override;

protected:
    void print(std::ostream& os) const override;
};

class Ellipse: public Figure{
private:
    double a_, b_;

public:
    Ellipse(double a, double b): a_(a), b_(b){
        if(a_ <= 0 || b_ <= 0) throw std::runtime_error("Incorrect width or height");
    }
    double area() const;
    double perimeter() const;

    Ellipse& operator=(const Ellipse& other) = default;
    Figure& operator=(const Figure& other) override;

protected:
    void print(std::ostream& os) const override;
};

#include "figure.tpp"

#endif