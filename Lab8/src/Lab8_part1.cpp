// L13_Ex1_ABC.cpp
// By Luis Rivera

// Compile using the flag  -std=c++11  or  -std=c++0x
// Example: g++ L13_Ex1_ABC.cpp -o L13_Ex1_ABC -std=c++11
//      or: g++ L13_Ex1_ABC.cpp -o L13_Ex1_ABC -std=c++0x

#include <iostream>
#include <cmath>
using namespace std;

class BaseConic {
	protected:
		double x;
		double y;

	public:
		// Notice the default values. They don't need to be 0
		BaseConic(double x0 = 0, double y0 = 0){x = x0; y = y0;}
		virtual ~BaseConic(){};
		void Move(double nx, double ny){x = nx; y = ny;}
		virtual double Area() = 0; // a pure virtual function ==> ABC
		virtual void Resize();
		virtual void display() = 0;
		
};

void BaseConic::Resize(){
	cout << "Base Conic cannot be resized" << endl;
}

class Ellipse : public BaseConic {
	private:
		double a; 	// semi-major axis
		double b; 	// semi-minor axis
		double angle; // orientation angle

	public:
		Ellipse(double x0, double y0, double a0, double b0, double an0);
		~Ellipse(){}
		virtual void Resize(double na, double nb){a = na; b = nb;}
		virtual double Area() {return 3.1416*a*b;}
		void Rotate(double nang){angle += nang;}
		virtual void display();
		void Verticies();
};

// Notice the default values. Those are used if no parameter is given when
// an object is created.
// Notice how the BaseConic constructor can be called. If other constructors where defined,
// those could be used instead.
Ellipse::Ellipse(double x0=0,double y0=0,double a0=0,double b0=0,double an0=0) : BaseConic(x0,y0) {
	// x and y are set in the BaseConic constuctor
	a = a0;
	b = b0;
	angle = an0;
}

void Ellipse::Verticies(){
	double v1x = x + a*cos(angle);
	double v1y = y + a*sin(angle);
	double v2x = x - a*cos(angle);
	double v2y = y - a*sin(angle);
	double v3x = x + b*sin(angle);
	double v3y = y + b*cos(angle);
	double v4x = x - b*sin(angle);
	double v4y = y - b*cos(angle);
	cout << "Right Vertex: " << "(" << v1x << "," << v1y << ")" << endl;
	cout << "Left Vertex: " << "(" << v2x << "," << v2y << ")" << endl;
	cout << "Top Vertex: " << "(" << v3x << "," << v3y << ")" << endl;
	cout << "Bottom Vertex: " << "(" << v4x << "," << v4y << ")" << endl;
}

void Ellipse::display() {
	cout << "x = " << x << ", y = " << y << ", a = " << a << ", b = " << b
		 << ", angle = " << angle << ", Area = " << this->Area() << endl;
}

class Circle : public BaseConic {
	private:
		double r; 	// radius
		
	public:
		virtual double Area() {return 3.1416*r*r;}
		virtual void Resize(double nr){r = nr;}
		Circle(double x0=0,double y0=0,double r0=0) : BaseConic(x0,y0){r = r0;}
		virtual void display();
		void Inside(double xp, double yp);
};

void Circle::Inside(double xp, double yp){
	double temp_xp = pow(xp,2);
	double temp_yp = pow(yp,2);
	double temp = pow(xp+yp,0.5);
	if(temp < r){
		cout << "the point (" << xp << "," << yp << ") is inside the circle" << endl;
	}
	else{
		cout << "the point (" << xp << "," << yp << ") is NOT inside the circle" << endl;
	}
}

void Circle::display() {
	cout << "x = " << x << ", y = " << y << ", r = " << r 
		 << ", Area = " << this->Area() << endl;
}

int main(){
	//BaseConic b0;	// not possible to create an object of the ABC
	Ellipse e0, e1(1), e2(2,3), e3(4,5,6), e4(7,8,9,10), e5(0.1,0.2,0.3,0.4,0.5);
	Circle c0, c1(2,-1,5);
	
	// You CAN "skip" input parameters, so the corresponding variables are left with
	// the default values. Use the new standard -std=c++11 or -std=c++0x when compiling.
	Ellipse e6({},2), e7({},{},4,3);
	Circle c2({},{},2.5);
	
	e0.display();	e1.display();	e2.display();	e3.display();
	e4.display();	e5.display();	e6.display();	e7.display();
	cout << "------------------------------------------------------------------" << endl;
	c0.display();	c1.display();	c2.display();
	
	cout << "------------------------------------------------------------------" << endl;
	
	// You CAN use ABC pointers and references
	BaseConic *bptr1 = &e4;
	BaseConic *bptr2 = new Ellipse(1,1,2,3,0.5);
	BaseConic &bref1 = e5;
	bptr1->display();
	bptr2->display();
	bref1.display();
	
	cout << "------------------------------------------------------------------" << endl;	
	BaseConic *bptr3 = &c1;
	BaseConic *bptr4 = new Circle(-3,{},1);
	BaseConic &bref2 = c2;
	bptr3->display();
	bptr4->display();
	bref2.display();
	
	delete bptr2;
	delete bptr4;
	
	//new stuff added
	Ellipse T(0,0,2,3,0);
	T.Verticies();
	return 0;
	
}