#include <iostream>
#include <string>
#include <vector>

using namespace std;

string MorseCode[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
//char Alph[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
//char alph[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
string text = "abcdefghijklmnopqrstuvwxyz";
string TEXT = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
class Message{
	private:
		
	protected:
		string message;
	public:
		Message();
		Message(string code);
		~Message();
		virtual void print_message();
};

Message::Message(){
	string mess = "";
	while(mess == ""){
	cout << "Please enter a message less than 100 characters:" << endl;
	cin >> mess;
	}
	message = mess;
	//need to add error check
}

Message::Message(string code){
	message = code;
	
}

Message::~Message(){
	//nothing to delete since using strings
}

void Message::print_message(){
	cout << message << endl;
}

class MorseCodeMessage : public Message{
	private:
		string morse;
	public:
		MorseCodeMessage(string msg);
		string translate(string mes);
		virtual void print_message();
};

MorseCodeMessage::MorseCodeMessage(string msg) : Message(msg){
	translate(msg);
	morse = translate(msg);
}

string text_to_morse(char c){
	int index = text.find(c);
	if(index != -1){
		return MorseCode[index];
	}
	else{
		index = TEXT.find(c);
		if(index != -1){
			return MorseCode[index];
		}
		else{
			return " ";
		}
	}
}

string MorseCodeMessage::translate(string mes){
	string temp = "";
	int i = 0;
	for(i=0;i<mes.length();i++){
		if(mes[i] == ' '){
			temp += "/ ";
		}
		else{
			temp += text_to_morse(mes[i]);
			temp += " ";
		}
	}
	return temp;
}

void MorseCodeMessage::print_message(){
	cout << message << endl;
	cout << morse << endl;
}

/*

//work on this
class MessageStack{
	private:
		vector<Message*>stack;
	public:
		MessageStack(Message obj);
		~MessageStack();
		void Push(Message obj);
		void Pop();
		void print_stack();
}
*/

int main(void){
	int a = 0;
	int choice = 0;
	string msg;
	MorseCodeMessage* M;
	while(a==0){
		cout << "which action would you like to preform?" << endl;
		cout << "1.) Enter Message" << endl;
		cout << "2.) Print Stack" << endl;
		cout << "3.) Exit Program" << endl;
		cin >> choice;
		cin.ignore();
		switch(choice){
			case 1:{
			cout << "Please enter a message:" << endl;
			getline(cin,msg);
			MorseCodeMessage temp(msg);
			M = &temp;
			M->print_message();
			}
			break;
			
			case 2:
			cout << "here" << endl;
			break;
			
			case 3:
			cout << "Exiting Program..."<< endl;
			return 0;
			break;
		
			default:
			cout << "Invalid choice! Please try again." << endl;
			break;
		}
	}
	return 0;
}
	
	




