// Dalton Koch
// ECE 3220
// Lab 5
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

class Signal{
	private:
		int length;
		double *raw_data;
		double average;
		double max_val;
		double getaverage();
		double getmax_val();
	public:
		Signal();
		Signal(int filenum);
		Signal(char* filename);
		~Signal();
		void do_offset(double offset);
		void do_scale(double scale);
		void do_center();
		void do_normal();
		void do_stats();
		void print_to_file(char* output);
		void sig_info();
};

// non - parametric constructor 
Signal::Signal(){
	//ifstream so we can read from file
	std::ifstream myfile;
	myfile.open("Raw_data_01.txt");
	if(!myfile.is_open()){
		//checkss to see if file was opened
		cout << "error file not opened" << endl;
	}
	
	myfile >> length; // reads in the length
	myfile >> max_val; // reads in the max value
	raw_data = new double[length]; // creates a new array of doubles
	for(int i = 0; i<length;i++){
		//reads in each value into the array
		myfile >> raw_data[i];
	}
	myfile.close(); // close file
	average = getaverage(); // set average member
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
	raw_data = new double[length];
	for(int i = 0; i<length;i++){
		myfile >> raw_data[i];
	}
	myfile.close(); // closes file
	average = getaverage(); // sets average member
}

//prarmetric constructor
Signal::Signal(char* filename){
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
	raw_data = new double[length];
	for(int i = 0; i<length;i++){
		myfile >> raw_data[i];
	}
	myfile.close();
	average = getaverage();
}

//destructor
Signal::~Signal(){
	delete raw_data;
}

//find the average
double Signal::getaverage(){
	double total = 0.0;
	for(int i = 0;i<=length;i++){
		total += raw_data[i]; // totals all values in signal
	}
	return(total/(double)length);
}

void Signal::do_offset(double offset){
	for(int i=0; i<length; i++){
		//adds the offset to each value in signal
		raw_data[i] = raw_data[i] + offset;
	}
	//sets new average and max_val
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_scale(double scale){
	for(int i=0; i<length; i++){
		//multiplies each value in signal by scale
		raw_data[i] = raw_data[i] * scale;
	}
	//sets new average and max_val
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_center(){
	for(int i=0; i<length; i++){
		//makes it to where the new average is 0
		raw_data[i] = raw_data[i] - average;
	}
	//sets new average and max_val
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_normal(){
	for(int i=0; i<length; i++){
		//makes it to where each values is less than 1 or greater than -1
		raw_data[i] = raw_data[i] / max_val;
	}
	//sets new average and max_val
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

void Signal::print_to_file(char* filename){
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
		myfile << raw_data[i] << char(13) << char(10);
		
	}
	myfile.close();
}

// gets the max value in the signal
double Signal::getmax_val(){
	double max = 0.0;
	//loop and compares each value to the previous lowest value
	for(int i=0; i<length; i++){ 
		if(raw_data[i]>max){
			max = raw_data[i];
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
	char filename[30];
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
			stpcpy(filename,argv[i]); // copies input file name into filename variable
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
	char output[30];
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
			cin >> scale;
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
			if(output == NULL){ // error check for file name
				cout << "error name cannot be null, please try again" << endl;
				break;
			}
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
