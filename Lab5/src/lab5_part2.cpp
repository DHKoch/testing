// Dalton Koch
// ECE 3220
// Lab 5
#include <iostream>
#include <cstring>
#include <fstream>
//#include <stdio.h>
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
		void print_to_file();
		void sig_info();
};

Signal::Signal(){
	
	std::ifstream myfile;
	myfile.open("Raw_data_01.txt");
	if(!myfile.is_open()){
		cout << "error file not opened" << endl;
	}
	
	myfile >> length;
	myfile >> max_val;
	raw_data = new double[length];
	for(int i = 0; i<length;i++){
		myfile >> raw_data[i];
	}
	myfile.close();
	average = getaverage();
}

Signal::Signal(int filenum){
	std::ifstream myfile;
	char filename[30];
	int n = sprintf(filename,"Raw_data_%02d.txt",filenum);
	myfile.open(filename);
	if(!myfile.is_open()){
		cout << "error file not opened" << endl;
	}
	myfile >> length;
	myfile >> max_val;
	raw_data = new double[length];
	for(int i = 0; i<length;i++){
		myfile >> raw_data[i];
	}
	myfile.close();
	average = getaverage();
}

Signal::Signal(char* filename){
	std::ifstream myfile;
	myfile.open(filename);
	if(!myfile.is_open()){
		cout << "error file not opened" << endl;
	}
	myfile >> length;
	myfile >> max_val;
	raw_data = new double[length];
	for(int i = 0; i<length;i++){
		myfile >> raw_data[i];
	}
	myfile.close();
	average = getaverage();
}

Signal::~Signal(){
	delete raw_data;
}

double Signal::getaverage(){
	double total = 0.0;
	for(int i = 0;i<=length;i++){
		total += raw_data[i];
	}
	return(total/(double)length);
}

void Signal::do_offset(double offset){
	for(int i=0; i<length; i++){
		raw_data[i] = raw_data[i] + offset;
	}
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_scale(double scale){
	for(int i=0; i<length; i++){
		raw_data[i] = raw_data[i] * scale;
	}
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_center(){
	for(int i=0; i<length; i++){
		raw_data[i] = raw_data[i] - average;
	}
	average = getaverage();
	max_val = getmax_val();
}

void Signal::do_normal(){
	for(int i=0; i<length; i++){
		raw_data[i] = raw_data[i] / max_val;
	}
	average = getaverage();
	max_val = getmax_val();
}
void Signal::do_stats(){
	average = getaverage();
	max_val = getmax_val();
	cout << "Average: " << average << "maximum: " << max_val << endl;
}

void Signal::print_to_file(){
	std::ofstream myfile;
	char filename[12] = "OutPut.txt";
	myfile.open(filename);
	if(!myfile.is_open()){
		cout << "error file not opened" << endl;
	}
	myfile << length;
	myfile << ' ';
	myfile << average;
	myfile << '\n';
	for(int i = 0; i<length;i++){
		myfile << raw_data[i];
		myfile << '\n';
	}
	myfile.close();
}

double Signal::getmax_val(){
	double max = 0.0;
	for(int i=0; i<length; i++){
		if(raw_data[i]>max){
			max = raw_data[i];
		}
	}
	return (max);
}

void Signal::sig_info(){
	cout << "Length: " << length << "Maximum: " << max_val << "Average: " << average << endl; 
}

int main(int argc, char* argv[]){
	int filenum = 0;
	char filename[30];
	int i = 1;
	Signal* sig1;
	
	if((argv[i][0] == '-') && (argv[i][1] == 'n')){
		i++;
		if(argv[i] == NULL){
			cout << "error!" << endl;
			return 0;
		}
		filenum = std::atoi(argv[i]);
		if(filenum <= 0){
			cout << "error, file number cannot be negative" << endl;
			return 0;
		}
		Signal sig(filenum);
		sig1 = &sig;
	}
	else if((argv[i][0] == '-') && (argv[i][1] == 'f')){
		i++;
		if(argv[i] == NULL){
			cout << "error!" << endl;
			return 0;
		}
		stpcpy(filename,argv[i]);
		Signal sig(filename);
		sig1 = &sig;
	}	
	else{
		Signal sig;
		sig1 = &sig;
	}
	int choice = 0;
	int j = 1;
	double offset = 0.0;
	double scale = 0.0;
	while(j == 1){
		cout << "Please select a action to preform:" << endl
		<< "1.) Offset:" << endl
		<< "2.) Scale:" << endl
		<< "3.) Statistics:" << endl
		<< "4.) Center:" << endl
		<< "5.) Normalize:" << endl
		<< "6.) Print Info:" << endl
		<< "7.) Exit..." << endl;
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
			cin >> offset;
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
			cout << "Printing to OutPut.txt ..." << endl;
			sig1->print_to_file();
			break;
			
			case 7:
			cout << "Exiting the program" << endl;
			return 0;
			break;
			
			default:
			cout << "Error incorrect choice please choose again." << endl;
			break;
		}
	}
	return 0;
}




