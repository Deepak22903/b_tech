#include <iostream>

using namespace std;

class shape {
    virtual double area() = 0;
};

class circle : public shape{
    private :
    int r;

    public:

    circle(int rad){
        r = rad;
    }

    public:
    double area() override{
        return 3.14 *r *r;
    }

    ~circle(){};
};

class square : public shape{
    private:
    int side;

    public :

    square(int s){
        side = s;
    }

    double area() override {
        return side * side;
    }

    ~square(){};

};

int main(){
    circle c(5);
    square s(5);
    cout << "Area of square = " << s.area() << endl;

    cout << "Area = " << c.area() << endl;

    return 0;

}

