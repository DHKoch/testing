// Lab6_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab6_vectors.cpp -o Lab6_vectors -std=c++11
//      or:  g++ Lab6_vectors.cpp -o Lab6_vectors -std=c++0x
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	vector<int> ivec1(5), ivec2;
	vector<double> dvec1{5.1}, dvec2(5,1.5);
	vector<string> svec1 = {"hello", "world"};
	// vector<myClass> myCvec;	// you can have vectors of objects
	// in general: vector<Type> vec;	// vector is a "template"

	for(int i = 0; i < ivec1.size(); i++)
		cout << ivec1[i] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:ivec1)	// This is equivalent to the above for loop
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec2)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:svec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
	cout << "Original size: " << ivec2.size() << endl;
	ivec2.push_back(50);
	cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
// ***********************************************************************
// Try all the ways to initialize a vector shown in Table 3.4. Use the
// vectors above and/or declare new vectors.
// Some of those operations have already been used, but write your
// own examples.

// Do exercises 3.14 and 3.15 from Lippman (page 102)

// Try all the vector operations shown in table 3.5. Use the vectors above
// or define new ones. Try different types.
// ***********************************************************************

	vector<int> v1;
	vector<int> v2(v1);
	vector<int> v3 = v1;
	vector<int> v4(5,2);
	vector<int> v5(5);
	vector<int> v6{1,2,3,4,5,6};
	vector<int> v7 = {7,8,9,0};
	
	cout << "exercise 3.14..." << endl;
	string x;
	int a = 0;
	int i = 0;
	while(i<5){
		cout << "enter a number: " << endl;
		cin >> x;
		sscanf(x.c_str(), "%d" , &a);
		v1.push_back(a);
		i++;
	}
	cout << endl;
	cout << "printing out the values of the vector..." << endl;
	for(i = 0;i<v1.size();i++){
		cout << v1.at(i) << endl;
	}
	
	cout << "exercise 3.15..." << endl << endl;
	vector<string> v9;
	string y;
	i = 0;
	while(i<5){
		cout << "enter a string: " << endl;
		cin >> y;
		v9.push_back(y);
		i++;
	}
	for(i = 0;i<v9.size();i++){
		cout << v9.at(i) << endl;
	}
	
	cout << "Table 3.5 functions" << endl;
	vector<string> v10;
	if(v10.empty()){
		cout << "vector v10 is empty" << endl;
	}
	if(!v9.empty()){
		cout << "vector v9 is not empty" << endl;
	}
	cout << "the size of the vector v9 is: " << v9.size() << endl;
	cout << "the third value in the vector v9 is: " << v9[3] << endl;
	cout << endl;
	cout << "setting v10 equal to v9 ..." << endl;
	v10 = v9;
	cout << "v9 is:" << endl;
	for(i = 0;i<v9.size();i++){
		cout << v9.at(i) << endl;
	}
	cout << endl;
	cout << "v10 is:" << endl;
	for(i = 0;i<v10.size();i++){
		cout << v10.at(i) << endl;
	}
	if(v10 == v9){
		cout << "v10 and v9 are equal!" << endl << endl;
	}
	if(v1 != v7){
		cout << "v1 is not wqual to v7" << endl;
	}
	vector<int> vA = {1,2,3};
	vector<int> vB = {4,3,2};
	if(vA>vB){
		cout << "vA > vB" << endl;
	}
	if(vA<vB){
		cout << "vA < vB" << endl;
	}
	if(vA<=vB){
		cout << "vA <= vB" << endl;
	}
	if(vA>=vB){
		cout << "vA >= vB" << endl;
	}
	
	return 0;
}