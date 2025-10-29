#include "func.h"

double Complex::abs() const{
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

double Complex::real() const { return real_; }

double Complex::imag() const { return imag_; }

Complex Complex::conjugate() const {
    return Complex(real_, -imag_);
}

Complex Complex::operator+() const {return *this;}

Complex Complex::operator-() const {
    return Complex(-real_, -imag_);
}

Complex& Complex::operator=(const double rhs){
    real_ = rhs;
    imag_ = 0.0;
    return *this;
}
Complex& Complex::operator=(const Complex& rhs){
    real_ = rhs.real_;
    imag_ = rhs.imag_;
    return *this;
}

Complex& Complex::operator+=(const Complex& rhs){
    real_ += rhs.real_;
    imag_ += rhs.imag_;
    return *this;
}
Complex& Complex::operator+=(const double rhs){
    real_ += rhs;
    return *this;
}

Complex& Complex::operator-=(const Complex& rhs){
    real_ -= rhs.real_;
    imag_ -= rhs.imag_;
    return *this;
}
Complex& Complex::operator-=(const double rhs){
    real_ -= rhs;
    return *this;
}

Complex& Complex::operator*=(const Complex& rhs){
    double new_real = real_ * rhs.real_ - imag_ * rhs.imag_;
    double new_imag = real_ * rhs.imag_ + imag_ * rhs.real_;
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}
Complex& Complex::operator*=(const double rhs){
    real_ *= rhs;
    imag_ *= rhs;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs){
    double mod = rhs.abs();
    double new_real = (real_ * rhs.real_ + imag_ * rhs.imag_)/(mod*mod);
    double new_imag = (-real_ * rhs.imag_ + imag_ * rhs.real_)/(mod*mod);
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}
Complex& Complex::operator/=(const double rhs){
    real_ /= rhs;
    imag_ /= rhs;
    return *this;
}

bool Complex::operator==(const Complex& rhs) const{
    return real_ == rhs.real_ && imag_ == rhs.imag_;
}
bool Complex::operator==(const double rhs) const{
    return real_ == rhs && imag_ == 0;
}

bool Complex::operator!=(const Complex& rhs) const{
    return real_ != rhs.real_ || imag_ != rhs.imag_;
}
bool Complex::operator!=(const double rhs) const{
    return real_ != rhs || imag_ != 0;
}

Complex operator+(const Complex& lhs, const Complex& rhs){
    return Complex(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
}
Complex operator+(const double lhs, const Complex& rhs){
    return Complex(lhs + rhs.real(), rhs.imag());
}
Complex operator+(const Complex& rhs, const double lhs){
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(const Complex& lhs, const Complex& rhs){
    return Complex(lhs.real() - rhs.real(), lhs.imag() - rhs.imag());
}
Complex operator-(const double lhs, const Complex& rhs){
    return Complex(lhs - rhs.real(), -rhs.imag());
}
Complex operator-(const Complex& rhs, const double lhs){
    return Complex(rhs.real() - lhs, rhs.imag());
}

Complex operator*(const Complex& lhs, const Complex& rhs){
    double new_real = lhs.real() * rhs.real() - lhs.imag() * rhs.imag();
    double new_imag = lhs.real() * rhs.imag() + lhs.imag()* rhs.real();
    return Complex(new_real, new_imag);
}
Complex operator*(const double lhs, const Complex& rhs){
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}
Complex operator*(const Complex& rhs, const double lhs){
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(const Complex& lhs, const Complex& rhs){
    double mod = rhs.abs();
    double new_real = lhs.real() * rhs.real() + lhs.imag() * rhs.imag();
    double new_imag = - lhs.real() * rhs.imag() + lhs.imag()* rhs.real();
    return Complex(new_real/(mod*mod), new_imag/(mod*mod));
}
Complex operator/(const double lhs, const Complex& rhs){
    double mod = rhs.abs();
    double new_real = lhs * rhs.real();
    double new_imag = - lhs * rhs.imag();
    return Complex(new_real/(mod*mod), new_imag/(mod*mod));
}
Complex operator/(const Complex& rhs, const double lhs){
    return Complex(rhs.real()/lhs, rhs.imag()/lhs);
}

bool operator==(const double lhs, const Complex& rhs){
    return lhs == rhs.real() && rhs.imag() == 0;
}
bool operator!=(const double lhs, const Complex& rhs){
    return lhs != rhs.real() || rhs.imag() != 0;
}

std::ostream& operator<<(std::ostream& output, Complex& rhs){
    const double r = rhs.real();
    const double i = rhs.imag();
    if(r!=0 && i!=0){
        if (i < 0){
            output << r << i << "i";
        }
        else if(i != 1){
            output << r << "+" << i << "i";
        }
        else{
            output << r << "+" << "i";
        }
    }
    else if(r!=0 && i==0){
        output << r;
    }
    else if(r==0 && i!=0){
        if(i != 1){
            output << i << "i";
        }
        else{
            output << "i";
        }
    }
    else{
        output << 0;
    }
    return output;
}

std::istream& operator>>(std::istream& input, Complex& rhs){
    char ch;
    double real_, imag_;
    input >> std::ws;

    if (input.peek() == 'i'){
        rhs = Complex(0, 1);
        return input;
    }
    if (input >> real_){
        if (input.peek() == 'i'){
            rhs = Complex(0, real_);
            return input;
        }
        else if(input.peek() == '+' || input.peek() == '-'){
            input >> ch;
            if (input.peek() == 'i'){
                rhs = Complex(real_, 1);
                return input;
            }
            if(input >> imag_){
                if(input.peek() == 'i'){
                    rhs = Complex(real_, imag_);
                    return input;
                }
            }
            else if(input.peek() == 'i'){
                rhs = Complex(real_, 1);
                return input;
            }
        }
        else{
            rhs = Complex(real_, 0);
            return input;
        }
    }
    
    input.setstate(std::ios::failbit);
    return input;
}