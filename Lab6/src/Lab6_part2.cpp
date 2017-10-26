#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class Signal{
	private:
		int length;
		vector<double>S;
		double average;
		double max_val;
		double getaverage();
		double getmax_val();
	public:
		Signal();
		Signal(int filenum);
		Signal(string filename);
		~Signal();
		void do_offset(double offset);
		void do_scale(double scale);
		void do_center();
		void do_normal();
		void do_stats();
		void print_to_file(string output);
		void sig_info();
		void operator+(double offset);
		void operator*(double scale);
};

// non - parametric constructor 
Signal::Signal(){
	S = {0};
	length = 0;
	average = 0;
	max_val = 0;
	
}
//parametric constructor 
Signal::Signal(int filenum){
	std::ifstream myfile;
	
	char filename[30];
	// uses file num to open a select file
	int n = sprintf(filename,"Raw_data_%02d.txt",filenum);
	myfile.open(filename);
	
	if(!myfile.is_open()){
		//checks to see if file was opened
		cout << "error file not opened" << endl;
	}
	
	//reads in all the values
	myfile >> length;
	myfile >> max_val;
	double x;
	for(int i = 0; i<length;i++){
	myfile >> x;
	S.push_back(x);
	}
	myfile.close(); // closes file
	average = getaverage(); // sets average member
}

//prarmetric constructor
Signal::Signal(string filename){
	std::ifstream myfile;
	//opens the file with the name set by the user
	myfile.open(filename);
	if(!myfile.is_open()){
		//checks to see if file can be opened
		cout << "error file not opened" << endl;
	}
	//reads in vlaues
	myfile >> length;
	myfile >> max_val;
	double x;
	for(int i = 0; i<length;i++){
		myfile >> x;
		S.push_back(x);
	}
	myfile.close();
	average = getaverage();
}

void Signal::operator+(double offset){
	int i = 0;
	for(i=0;i<length;i++){
		S[i] += offset; //add offset to each vector value
	}
}

void Signal::operator*(double scale){
	int i = 0;
	for(i=0;i<length;i++){
		S[i] *= scale; //multiply each vector value by scale
	}
}

//destructor
Signal::~Signal(){
	
}

//find the average
double Signal::getaverage(){
	double total = 0.0;
	for(int i = 0;i<=length;i++){
		total += S[i]; // totals all values in signal
	}
	if(length ==0){
		return 0; //handles empty vector
	}
	else{
	return(total/(double)length);
	}
}

void Signal::do_offset(double offset){
	this->operator+(offset); //use + operator to add offset
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_scale(double scale){
	this->operator*(scale); //use * operator to multiply 
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_center(){
	this->operator+((average*(-1))); //subtracts average from each vzlue
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_normal(){
	this->operator*((1/max_val)); //divides by max_value
	average = getaverage();
	max_val = getmax_val();
}
void Signal::do_stats(){
	//gets the current average and max_value
	average = getaverage();
	max_val = getmax_val();
	//displays the values
	cout << "Average: " << average << "maximum: " << max_val << endl;
}

void Signal::print_to_file(string filename){
	std::ofstream myfile; //  ofstrema so we can write to file	
	myfile.open(filename); // opens file
	if(!myfile.is_open()){
		//checks to see if file was opened 
		cout << "error file not opened" << endl;
	}
	myfile << length; // writes the length
	myfile << ' '; // writes a space char
	myfile << max_val; // writes the max value
	myfile << char(13) << char(10); // writes a new line
	for(int i = 0; i<length;i++){
		// writes the value and then a new line
		myfile << S[i] << char(13) << char(10);
		
	}
	myfile.close();
}

// gets the max value in the signal
double Signal::getmax_val(){
	double max = 0.0;
	//loop and compares each value to the previous lowest value
	for(int i=0; i<length; i++){ 
		if(S[i]>max){
			max = S[i];
		}
	}
	return (max);
}

// Prints the signal info
void Signal::sig_info(){ 
	cout << "Length: " << length << "Maximum: " << max_val << "Average: " << average << endl; 
}

int main(int argc, char* argv[]){
	int filenum = 0;
	
	int i = 1;
	Signal* sig1; // pointer of Signal type used for the program
	if(argc == 1){ // case for no command line arguments
		Signal sig;
		sig1 = &sig;
	}
	else{
		if((argv[i][0] == '-') && (argv[i][1] == 'n')){
			i++;
			if(argv[i] == NULL){ // makes sure a file num is after the -n 
				cout << "error!" << endl;
				return 0;
			}
			filenum = std::atoi(argv[i]);
			if(filenum <= 0){ // checks to make sure filenum is not 0 or less than 0
				cout << "error, file number cannot be negative" << endl;
				return 0;
			}
			Signal sig(filenum);
			sig1 = &sig;
		}
		else if((argv[i][0] == '-') && (argv[i][1] == 'f')){
			i++;
			if(argv[i] == NULL){ // checks to make sure there is a file name 
				cout << "error!" << endl;
				return 0;
			}
			string filename(argv[i]); // copies input file name into filename variable
			Signal sig(filename); // calls parametric constructor that handles filename
			sig1 = &sig; // sets the pointer to the adress of the signal created 
		}	
		else{ // case that handles wrong command line arguments
			cout << "error, incorrect command line inputs" << endl;
			return 0;
		}
	}
	int choice = 0;
	int j = 1;
	double offset = 0.0;
	double scale = 0.0;
	string output;
	while(j == 1){ // loop that reprints menu and allows new selection
		cout << "Please select a action to preform:" << endl
		<< "1.) Offset:" << endl
		<< "2.) Scale:" << endl
		<< "3.) Statistics:" << endl
		<< "4.) Center:" << endl
		<< "5.) Normalize:" << endl
		<< "6.) Print To File:" << endl
		<< "7.) Signal Info:" << endl
		<< "8.) Exit..." << endl;
		cin >> choice;
		
		switch(choice){
			case 1:
			offset = 0.0;
			cout << "please enter a value to offset the signal by:" ;
			cin >> offset;
			sig1->do_offset(offset);
			break;
			
			case 2:
			scale = 0.0;
			cout << "Please enter a value to scale the signal by:";
			cin >> scale; //read double from user
			sig1->do_scale(scale);
			break;
			
			case 3:
			cout << "Printing the statistics ..." << endl;
			sig1->do_stats();
			break;
			
			case 4:
			cout << "Centering the signal ..." << endl;
			sig1->do_center();
			break;
			
			case 5:
			cout << "Normalizing the signal ..." << endl;
			sig1->do_normal();
			break;
			
			case 6:
			cout << "Please enter the name of the output file:" << endl;
			cin >> output;
			//read string from user
			sig1->print_to_file(output);
			break;
			
			case 7:
			cout << "Printing the Signal Info ..." << endl;
			sig1->sig_info();
			break;
			
			case 8:
			cout << "Exiting the program ..." << endl;
			return 0;
			break;
			
			default:
			cout << "Error incorrect choice please choose again." << endl;
			break;
		}
	}
	return 0;
}
