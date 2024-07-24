#include <iostream>

using namespace std;

class shape {
    virtual double area() {} = 0;
}

class circle : pubic shape{
    private :
    int r;

    circle(int rad){
        r = rad;
    }

    public:
    double area() override{
        return 3.14 *r *r;
    }

    ~circle(){};
}

int main(){
    circle c(5);

    cout << "Area = " << c.area() << endl;

}

