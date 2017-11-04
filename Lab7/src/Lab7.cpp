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
	cout <<"\nYour Message is:" << endl;
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
	cout << "\nYour message is:" << endl;
	cout << message << endl;
	cout << "Your message in morse code is:" << endl;
	cout << morse << endl;
}


//work on this
class MessageStack{
	private:
		vector<Message*>stackV;
	public:
		MessageStack(Message* obj);
		~MessageStack();
		void Push(Message* obj);
		void Pop();
		void print_stack();
};

MessageStack::MessageStack(Message* obj){
	stackV.push_back(obj);
}

MessageStack::~MessageStack(){
	//nothing to free here
}

void MessageStack::Push(Message* obj){
	stackV.push_back(obj);
}

void MessageStack::Pop(){
	int index = stackV.size();
	if(index<=1){
		cout << "\ncannot remove items from empty stack" << endl;
	}
	else{
	stackV.erase(stackV.begin()+index);
	}
}

void MessageStack::print_stack(){
	vector<Message*>::iterator iter;
    for(iter = stackV.begin(); iter != stackV.end(); iter++) {
	(*iter)->print_message();
	}
}

int main(void){
	int a = 0;
	int choice = 0;
	string msg;
	Message* M;
	Message* temp = new Message("start of stack...");
	MessageStack Stack(temp);
	while(a==0){
		cout << "which action would you like to preform?" << endl;
		cout << "1.) Enter Message" << endl;
		cout << "2.) Enter Message for Morse Code" << endl;
		cout << "3.) Delete from Stack" << endl;
		cout << "4.) Print stack" << endl;
		cout << "5.) Exit Program" << endl;
		cin >> choice;
		cin.ignore();
		switch(choice){
			case 1:
			{
			cout << "Please enter a message:" << endl;
			getline(cin,msg);
			M = new Message(msg);
			M->print_message();
			Stack.Push(M);
			}
			break;
			
			case 2:
			{
			cout << "Please enter a message to be translated into morse code:" << endl;
			getline(cin,msg);
			M = new MorseCodeMessage(msg);
			M->print_message();
			Stack.Push(M);
			}
			break;
			
			case 3:
			cout << "\nRemoving the last item on the stack..." << endl;
			Stack.Pop();
			break;
			
			case 4:
			cout << "\nPrinting the stack..." << endl;
			Stack.print_stack();
			break;
			
			case 5:
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
	
	




