// Lab6_strings.cpp
// This program shows some simple string examples, and asks for simple tasks.
// Reference: Lippman, section 3.2

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab6_strings.cpp -o Lab6_strings -std=c++11
//      or:  g++ Lab6_strings.cpp -o Lab6_strings -std=c++0x
// Some initialization methods and other things are not supported by the old standard. 

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	string s1, s2("Hello"), s3 = "World";
	cout << "\nEnter a word:" << endl;
	cin >> s1;
	cin.ignore();	// to consume the '\n' character. Otherwise, you may get issues with
					// the getline() below. Try commenting this out. Any issues?
	
	string s4(s1);
	
	cout << "s1:" << s1 << endl
		 << "s2:" << s2 << endl
		 << "s3:" << s3 << endl
		 << "s4:" << s4 << endl;
	
	s1 = s2 + s3;
	cout << s1 << endl;
	
//my examples
	cout << "Table 3.2 examples" << endl << endl;

	filebuf fp;
	fp.open("words.txt",std::ios::out);
	ostream os(&fp);
	cout << "writing s3: "<< s3 << " to the file words.txt" << endl;
	os << s3; //writes the string s3 to the file
	fp.close();
	fp.open("words.txt",std::ios::in);
	istream is(&fp);
	cout << "reading words.txt into s1" << endl;
	is >> s1; //copies what is in the file to string s1;
	fp.close();
	cout << "String s1 is now " << s1 << endl;
	
	fp.open("words.txt",std::ios::in);
	istream is2(&fp);
	getline(is2,s2);
	fp.close();
	cout << endl;
	cout << "copying words.txt into s2 using get line... " << endl 
	<< "s2 is now " << s2 << endl;
	
	if(!s1.empty()){
		cout << endl;
		cout << "s1 is not empty and contains:" << s1 << endl;
	}
	
	cout << endl;
	int i = 0;
	for(i = 0; i<s2.size();i++){
		cout << s2[i];
	}
	
	cout << endl;
	
	string s5("Test");
	string s6("Code");
	
	cout << "s5: " << s5 << " s6: " << s6 << " s5+s6: " << s5+s6 << endl;
	
	cout << "setting s5 = s6 .." << endl;
	s5 = s6;
	cout << "s5: " << s5 << " s6: " << s6 << endl;
	
	
	if(s5 == s6){
		cout << "s5 and s6 are equal!" << endl;
	}
	
	if(s1 != s5){
		cout << "s1 is not equal to s5" << endl;
	}
	string s7("ABCD");
	string s8("EFGH");
	if(s7>s8){
		cout << s7 << " > " << s8 << endl;
	}
	if(s7<s8){
		cout << s7 << " < " << s8 << endl;
	}
	if(s7>=s8){
		cout << s7 << " >= " << s8 << endl;
	}
	if(s7<=s8){
		cout << s7 << " <= " << s8 << endl;
	}
	

// ***********************************************************************
// Try all the operations in Table 3.2 using the strings above and
// using new strings that you may declare.
// Some of those operations have already been used, but write your
// own examples.
// ***********************************************************************

// -----------------------------------------------------------------------
	string line;
	cout << "\nEnter some text:" << endl;
	getline(cin, line);
	cout << line << endl;
	
	cout << "\nEnter some text, finish it with an &:" << endl;
	getline(cin, line, '&');	// the delimiter can be any character
	cout << line << endl;
	
	for(auto &c : line){
		if(islower(c)){
			c = toupper(c);
		}
		else if(isupper(c)){
			c = tolower(c);
		}
		if(isspace(c)){
			c = '.';
		}
	}
	cout << line << endl;
	
	

// ***********************************************************************
// Use a "Range for" (Lippman, page 93) and operations in table 3.3 to:
// 1) change the case of the letters in your input line above (upper to
//    lowercase and vice-versa).
// 2) Replace any whitespace with a dot ('.').
// Print the converted text.
// ***********************************************************************

	return 0;
}