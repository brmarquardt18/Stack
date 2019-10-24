/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
#include <string>
// you may include more libraries as needed

using namespace std;

ProducerConsumer::ProducerConsumer(){
	queueFront = -1;
	queueEnd = -1;
}

bool ProducerConsumer::isEmpty(){
	return(queueEnd == -1 && queueFront -1);
}

bool ProducerConsumer::isFull(){
	return ((queueEnd + 1)%SIZE == queueFront);
}

void ProducerConsumer::enqueue(string player){
	if(isFull()){
		cout << "Queue full, cannot add new item" << endl;
		return;
	}
	else if(isEmpty()){
		queueEnd = queueFront = 0;
	}
	else{
		queueEnd = (queueEnd + 1) % SIZE;
	}
	queue[queueEnd] = player;
}

void ProducerConsumer::dequeue(){
	if(isEmpty()){
		cout << "Queue empty, cannot dequeue an item" << endl;
		queueEnd = queueFront = -1;
	}
	else if(queueEnd == queueFront){
		queueEnd = queueFront = -1;
	}
	else{
		queueFront = (queueFront + 1) % SIZE;
	}
}

int ProducerConsumer::queueSize(){
	if(isEmpty()){
		return 0;
	}
	else{
		return (queueEnd -queueFront + SIZE) % SIZE + 1;
	}
}

string ProducerConsumer::peek(){
	if(isEmpty()){
		cout << "Queue empty, cannot peek" << endl;
		return "";
	}
	else{
		return queue[queueFront];
	}
}
/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "Choose an option:" << endl;
  cout << "1. Producer (Produces items into the queue)" << endl;
	cout << "2. Consumer (Consumes items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer p;
	string input = "";
	while(stoi(input) != 3){
		menu();
		getline(cin,input);
		switch(stoi(input)){
			case 1:
			{
			string item;
			string num;
			cout << "Enter the number of items to be produced:" << endl;
			getline(cin,num);
			for(int i = 0; i < stoi(num); i++){
				cout << "Item " << "Item" << i+1 << ":" << endl;
				getline(cin,item);
				p.enqueue(item);
			}
			break;
			}
			case 2:
			{
				int num;
				cout << "Enter the number of items to be consumed:" << endl;
				cin >> num;
				if(num > p.queueSize()){
					num = p.queueSize();
				}
				for(int j = 0; j < p.queueSize(); j++){
					p.dequeue();
				}
				break;
			}
			case 3:
			{
				cout << "Number of items in the queue: ";
				cout << p.queueSize();
				break;
			}
		}
	}
}
