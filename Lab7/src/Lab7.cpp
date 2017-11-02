#include <iostream>

using namespace std;
char alphabet[26] = {'A','B','C','D','E','F''G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
string morseAlpha[26]= {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
	

class Message {
	private:
		
	protected:
		string message;
	public:
		Message();
		Message(string code);
		~Message();
		virtual void print_message();
}

Message::Message(){
	cout << "Please enter a message:" << endl;
	cin >> message;
	//need to add error check
}

Message::Message(string code){
	message = code;
	
}

Message::~Message(){
	//nothing to delete since using strings
}

void print_message(){
	cout << message << endl;
}

class MorseCodeMessage : public Message{
	private:
		
	public:
		void translate();
		void print_message();
}

class MessageStack{
	private:
		
	public:
		MessageStack(Message obj);
		~MessageStack();
		void Push(Message obj);
		void Pop();
		void print_stack();
}

int main(void){
	int a = 0;
	int choice = 0;
	while(a==0){
		cout << "which action would you like to preform?" << endl;
		cout << "1.) Enter Message" << endl;
		cout << "2.) Enter Morse Code Message" << endl;
		cout << "3.) Print Stack" << endl;
		cout << "4.) Exit Program" << endl;
		cin >> choice;
		switch(choice){
			case 1:
			break;
			
			case 2:
			break;
			
			case 3:
			break;
			
			case 4:
			break;
			
			default:
			cout << "Invalid choice! Please try again." << endl;
			break;
		}
	}
	return 0;
}
	
	




