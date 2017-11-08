#include <iostream>
#include <string>
#include <vector>

using namespace std;
//used a look up tables
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
		virtual void print_message(); //redefined later
};

Message::Message(){
	string mess = "";
	while(mess == ""){
	cout << "Please enter a message less than 100 characters:" << endl;
	cin >> mess; //read in input string from user
	cin.ignore();
	}
	message = mess; //set user input to message
	
}

Message::Message(string code){
	message = code; //sets user input to the message
	
}

Message::~Message(){
	//nothing to delete since using strings
}

void Message::print_message(){ //only prints the message in plain text
	cout <<"\nYour Message is:" << endl;
	cout << message << endl;
}

//derived class
class MorseCodeMessage : public Message{
	private:
		string morse;
	public:
		MorseCodeMessage(string msg);
		string translate(string mes);
		virtual void print_message();
};

MorseCodeMessage::MorseCodeMessage(string msg) : Message(msg){ //base constructor is called first
	translate(msg); //translates string
	morse = translate(msg); //sets translated string to morse data member
}

string text_to_morse(char c){
	int index = text.find(c); //finds the postion of the character in look up table
	if(index != -1){//if it exists return the corresponding morse code character
		return MorseCode[index];
	}
	else{//if not in text search uppercase text
		index = TEXT.find(c);
		if(index != -1){
			return MorseCode[index];
		}
		else{//if not in either table return space
			return " ";
		}
	}
}

string MorseCodeMessage::translate(string mes){
	string temp = "";
	int i = 0;
	for(i=0;i<mes.length();i++){
		if(mes[i] == ' '){//if 'space' replace with /
			temp += "/ ";
		}
		else{
			temp += text_to_morse(mes[i]);//takes each character and converts
			temp += " ";//adds a space so it is easy to read
		}
	}
	return temp; //morse message is returned
}

void MorseCodeMessage::print_message(){//prints both plain text and morse
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
	stackV.push_back(obj); //pushes object pointer onto stack
}

MessageStack::~MessageStack(){
	
}

void MessageStack::Push(Message* obj){
	stackV.push_back(obj); //places message pointer onto stack
}

void MessageStack::Pop(){
	int index = stackV.size();
	index -= 1; //index is the last spot in the vector
	if(index<=1){ //if nothing has been added to stack
		cout << "\ncannot remove items from empty stack" << endl;
	}
	else{//erases last spont in vector
	stackV.erase(stackV.begin()+index);
	}
}

void MessageStack::print_stack(){
	int i = 0;
	//loops from end of stack to beginning and prints each message
	for(i = stackV.size()-1;i>=0;i--){
		stackV[i]->print_message();
	}
	
}

int main(void){
	int a = 0;
	int choice = 0;
	string msg;
	Message* M;
	Message* temp = new Message("start of stack..."); //starting point for the stack
	MessageStack Stack(temp); //used to create the stack
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
			case 1: //choice for normal message
			{
			cout << "Please enter a message:" << endl;
			getline(cin,msg); //read in message from user
			M = new Message(msg); //set pointer to new message
			M->print_message(); //prints message
			Stack.Push(M); //places message on the stack
			}
			break;
			
			case 2:
			{
			cout << "Please enter a message to be translated into morse code:" << endl;
			getline(cin,msg);
			M = new MorseCodeMessage(msg); //sets Morse code message to the message pointer, dynamic binding
			M->print_message();
			Stack.Push(M); //places MorseCodeMessage object on the stack
			}
			break;
			
			case 3:
			cout << "\nRemoving the last item on the stack..." << endl;
			Stack.Pop(); //removes last item from the stack
			break;
			
			case 4:
			cout << "\nPrinting the stack..." << endl;
			Stack.print_stack(); //prints all item in the stack
			break;
			
			case 5:
			cout << "Exiting Program..."<< endl;
			return 0; //exits program
			break;
		
			default: //catchees any incorrect input
			cout << "Invalid choice! Please try again." << endl;
			break;
		}
	}
	return 0;
}
	
	




