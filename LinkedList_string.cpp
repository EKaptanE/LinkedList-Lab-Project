#include "LinkedList_string.h"
#include <stdexcept>

LinkedList::LinkedList():head(nullptr)
{
}

LinkedList::LinkedList(const LinkedList& other)
{
	if(other.head == nullptr){
		return;
	}
	this->head = new Node(other.head->data);
	Node* wc = this->head;
	Node* w = other.head->next;
	while (w != nullptr) {
		wc->next = new Node(w->data);
		w = w->next;
		wc = wc->next;
	}
}

LinkedList::~LinkedList()
{
	clear();
}

string& LinkedList::at(int index){
	if (index < 0 || index >=size()){
		throw out_of_range("Out of bond");
	}
	Node* walk = this->head;
	for (int i = 0; i < index; i++) {
		walk = walk->next;
	}
	return walk->data;
}

string& LinkedList::front(){
	if(this->head == nullptr){
		throw out_of_range("No data");
	}
	return this->head->data;
}

string& LinkedList::back(){

	if(this->head == nullptr){
		throw out_of_range("No data");
	}
	Node* last = this->head;
	while(last->next != nullptr){
		last = last->next;
	}
	return last->data;
}

void LinkedList::push_back(const string& value){
	if(this->head == nullptr){
		this->head = new Node(value);
		return;
	}
	Node* last = this->head;
	while(last->next != nullptr){
		last = last->next;
	}
	last->next = new Node(value);
}

void LinkedList::pop_back(){
	if(this->head == nullptr){
		throw out_of_range("No data");
	}
	if(this->head->next == nullptr){
		delete this->head;
		this->head = nullptr;
		return;
	}
	Node* h = nullptr;
	Node* n = this->head;
	while(n->next != nullptr){
		h = n;
		n = n->next;
	}
	delete n;
	h->next = nullptr;
}

void LinkedList::push_front(const string& value)
{
	Node* first = new Node(value);
    first->next = this->head;
    this->head = first;
}

void LinkedList::pop_front()
{
	if(this->head == nullptr){
		throw out_of_range("No data");
	}
	Node* first = this->head;
	this->head = head->next;
	delete first;
}

void LinkedList::insert_at(int index, const string& value){
	if(index < 0 || index > this->size()){
		throw out_of_range("Out of bond");
	}
	if(index == 0){
		push_front(value);
		return;
	}
	Node* walk = this->head;
	for(int i = 0; i < index-1; i++){
		walk = walk->next;
	}
	Node* temp = new Node(value);
	temp->next = walk->next;
	walk->next = temp;
}

void LinkedList::insert_after(int index, const string& val)
{
	if(index < 0 || index >= this->size()){
		throw out_of_range("Out of bond");
	}
	Node* walk = this->head;
	for(int i = 0; i < index ; i++){
		walk = walk->next;
	}
	Node* temp = new Node(val);
	temp->next = walk->next;
	walk->next = temp;
}

void LinkedList::erase_at(int index){
	if(index < 0 || index >= this->size()){
		throw out_of_range("Out of bond");
	}
	else if(this->head == nullptr){
		throw out_of_range("No data");
	}
	else if(index == 0){
		pop_front();
		return;
	}
	Node* walk = this->head;
	Node* temp;
	for(int i = 0; i < index - 1; i++){
		walk = walk->next;
	}
	temp = walk->next;
	walk->next = temp->next;
	delete temp;
}

void LinkedList::erase(const string& e)
{
	if(this->head == nullptr){
		throw out_of_range("No Data");
	}
	if(this->head->data == e){
		pop_front();
		return;
	}
	Node* h = this->head;
	while(h != nullptr && h->next != nullptr){
		if(h->next->data == e){
			Node* temp = h->next;
			h->next = temp->next;
			delete temp;
			return;
		}
		h = h->next;
	}
}

void LinkedList::clear()
{
	Node* walk = this->head;
	while (walk != nullptr){
		Node* temp = walk->next;
		delete walk;
		walk = temp;
	}
	this->head = nullptr;
}

int LinkedList::size() const
{
	int count = 0;
	Node* walk = this->head;
	while (walk!= nullptr){
		walk = walk->next;
		count++;
	}
	return count;
}

bool LinkedList::empty() const{
	return this->head == nullptr;
}

LinkedList& LinkedList::operator=(const LinkedList& lhs)
{
	if(this != &lhs){
		clear();
		Node* walk = lhs.head;
		while(walk != nullptr){
			push_back(walk->data);
			walk = walk->next;
		}
	}
	return *this;
}

bool LinkedList::operator==(const LinkedList& lhs) const
{
	Node* walkT = this->head;
	Node* walkL = lhs.head;

	while (walkT != nullptr && walkL != nullptr){
		if(walkT->data != walkL->data){
			return false;
		}
		walkT = walkT->next;
		walkL = walkL->next;
	}
	return walkT == nullptr && walkL == nullptr;
}

ostream& operator<<(ostream& out, const LinkedList& list){
	Node* walk = list.head;
	while(walk != nullptr){
		out << walk->data;
		if(walk->next != nullptr){
			out << " -> ";
		}
		walk = walk->next;
	}
	return out;
}

//task functions

Node* LinkedList::findMiddleNode(){
	if(this->head == nullptr){
		throw out_of_range ("No data");
	}
	Node* walk = this->head;
	Node* twoWalk = this->head;

	while(twoWalk != nullptr && twoWalk->next != nullptr){
		walk = walk->next;
		twoWalk = twoWalk->next->next;
	}
	return walk;
}

Node* LinkedList::getSmallestNode(){
	if (this->head == nullptr){
		throw out_of_range ("No data");
	}

	Node* smallest = this->head;
	Node* n = this->head->next;

	while(n != nullptr){
		if(n-> data < smallest->data){
			smallest = n;
		}
		n = n->next;
	}
	return smallest;
}

void LinkedList::moveSmallestToFront(){
	if(this->head == nullptr || this->head->next == nullptr){
		return;
	}
	Node* smallest = this->head;
	Node* prevSmallest = nullptr;
	Node* h = this->head;
	Node* n = this->head->next;

	while(n != nullptr){
		if(n->data < smallest->data){
			smallest = n;
			prevSmallest = h;
		}
		h = n;
		n = n->next;
	}
	if (prevSmallest != nullptr){
		prevSmallest->next = smallest->next;
		smallest->next = this->head;
		this->head = smallest;
	}
}

//menu function (also task but little modified)
void menu(LinkedList& list){
	string choice;

	cout << "Welcome to the Linked List Program! \nMenu: " << endl;

	while (choice != "x" && choice != "X"){
		cout << "1. Add an element\n2. Remove an element by value\n3. Access an element at index\n4. Insert an element at index\n5. Insert an element after index\n6. Remove an element at index\n7. Print the linked list\n8. Print the size of the linked list\n9. Check if the linked list is empty\n10. Clear the linked list\n11. Print the middle node\n12. Print the smallest node\n13. Move smallest node to front\nx. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		
		if(choice == "x" || choice == "X"){
			break;
		}
		if (choice == "1"){
			string value;
			cout << "Enter value: ";
			getline(cin >> ws, value);
			list.push_back(value);
			cout << "Operation successfully performed." << endl;
		}
		else if (choice == "2"){
			string value;
			cout << "Enter value to remove: ";
			cin >> value;
			try{
				list.erase(value);
				cout << "Value successfully removed from list." << endl;
			}
			catch (const out_of_range& err){
				cout << "Error: " << err.what() << endl;
			}
			
		}
		else if (choice == "3"){
			int index;
			cout << "Enter index to access: ";
			cin >> index;
			try{
				string value = list.at(index);
				cout << "Value at index " << index << " is: " << value << "." << endl;
			}
			catch(const out_of_range& err){
				cout << "Error: " << err.what() << endl;
			}
		}
		else if (choice == "4"){
			int index;
			cout << "Enter index to insert: ";
			cin >> index;
			string value;
			cout << "Enter value to insert: ";
			cin >> value;
			try{
				list.insert_at(index, value);
				cout << "Value successfully added." << endl;
			}
			catch (const out_of_range& err){
				cout << "Error: " << err.what() << endl;
			}
		}
		else if (choice == "5"){
			int index;
			cout << "Enter index to insert after: ";
			cin >> index;
			string value;
			cout << "Enter value to insert after: ";
			cin >> value;
			try{
				list.insert_after(index, value);
				cout << "Value successfully added." << endl;
			}
			catch (const out_of_range& err){
				cout << "Error: " << err.what() << endl;
			}
		
		}
		else if (choice == "6"){
			int index;
			cout << "Enter index to remove: ";
			cin >> index;
			try{
				list.erase_at(index);
				cout << "Value successfully removed." << endl;
			}
			catch(const out_of_range& err){
				cout << "Error: " << err.what() << endl;
			}
		}
		else if (choice == "7"){
			cout << list << endl;
		}
		else if (choice == "8"){
			cout << "Size of LinkedList is: " << list.size() << endl;
		}
		else if (choice == "9"){
			cout << "Linked list is ";
			if(list.empty()){
				cout << "empty." << endl;
			}
			else{
				cout << "not empty." << endl;
			}
		}
		else if (choice == "10"){
			list.clear();
			cout << "LinkedList successfuly cleared." << endl;
		}
		else if (choice == "11"){
			try{
				Node* mid = list.findMiddleNode();
				cout << "Middle node's value is: " << mid->data << endl;
			}
			catch(const out_of_range& err){
				cout << "Error: " << err.what() << endl;
			}
		}
		else if (choice == "12"){
			try{
				Node* smallest = list.getSmallestNode();
				cout << "Smallest node's value is: " << smallest->data << endl;
			}
			catch (const out_of_range& err){
				cout << "Error: " << err.what() << endl;
			}
		}
		else if (choice == "13"){
			list.moveSmallestToFront();
			cout << "Smallest node successfully moved to the front." << endl;
		}
		else{
			cout << "Wrong Input, try again" << endl;
		}
	}
	cout << "Exiting..." << endl;
}

int main(){
    LinkedList l;
    menu(l);
    return 0;
}