//SUBMIT this file
//complete all the missing LLDirectory implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

#include "LLDirectory.h"
#include <typeinfo>
#include <iostream>
#include <string>

using namespace std;

//Linked-list directory
//it is a directory that is backed by a linked list
//you should read the Directory.h first to see what each member function should do

    //constructor
    //hint: remember to initialize all data members properly!
LLDirectory::LLDirectory(string name, FSObject* parent) : Directory(name, parent){
	head = NULL;
}

    //destructor
    //delete the whole linked list
    //avoid memory leak
LLDirectory::~LLDirectory(){
	LLNode* current = head;
	LLNode* next;
	while (current != NULL){
		next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
	next = nullptr;
	current = nullptr;
}

    //add a child
    //(please read Directory.h first)
    //for LLDirectory, when you add a child, always maintain the ascending lexicographical order of file/directory names
    //i.e. find a proper place to insert the new linked list node
    //we do not distinguish directories from files when we order them
    //e.g., if there are 3 files of names "a", "c", "A" and there are 3 directories of names "b", "e", "Z"
    //then they should be stored in the linked list in the following order
    //A [Z] a [b] c [e]
    //hint: for lexicographical ordering, please refer to the webpage for tips and info
    //hint: you need to create either a new LLDirectory or new File object here for adding a child
//add a child
//add a new directory, with the given name, under this directory if isDir is true
//add a new file, with the given name, under this directory if isDir is false
//the new file's content should be simply empty, i.e., ""
//to make sure the child name is unique
//you should first check to see if an existing child already has the same name
//if yes, simply do nothing and return false
//if no, proceed to add the child, and return true
bool LLDirectory::addChild(bool isDir, string name){
	LLNode* current = head;
	LLNode* current_2 = head;

	LLNode* check = head;
	LLNode* newNode = new LLNode;

	if (head == NULL){
		if(isDir){
			newNode->next = head;
			head = newNode;
			newNode->data = new LLDirectory(name, this);
			return true;
		}
		else if (!isDir){
			newNode->next = head;
			head = newNode;
			File* tmp = new File(name, this);
			tmp->setContent("");
			newNode->data = tmp;
			return true;
		}
	}

	while (check != NULL){
		if (check->data->getName() == name){
			return false;
		}
		else {
			check = check->next;
		}
	}

	while (current != NULL && name > current->data->getName()){
		current = current->next;
	}
	while (current_2->next != current){
		current_2 = current_2->next;
	}
	if (isDir){
			newNode->data = new LLDirectory(name, this);
			newNode->next = current;
			current_2->next =  newNode;
			return true;

	}
	else if (!isDir){
			File* tmp = new File(name, this);
			tmp->setContent("");
			newNode->data= tmp;
			newNode->next = current;
			current_2->next =  newNode;
			return true;
	}
	return false;
}

    //remove a child
    //avoid memory leak
bool LLDirectory::removeChild(string name){
	if (head == NULL){
		return false;
	}
	bool canRemove = false;

	LLNode* current = head;
	LLNode* p = nullptr;

	while (current != NULL){
		if (current->data->getName() == name){
			canRemove = true;
			break;
		}
		else{
			p = current;	// Advance both pointers
			current = current->next;
		}
	}

	if (current != NULL){
		if (canRemove){
			if (current == head){
				head = head->next;
			}
			else
				p->next = current->next;
			delete current;
		}
	}
	return canRemove;
}

    //return a child by name
//return the child of the given name
 //return NULL if no child has the given name
FSObject* LLDirectory::getChild(string name){
	LLNode* current = head;
	while (current != NULL){
		if (current->data->getName() == name){
			return current->data;
			break;
		}
		else{
			current = current->next;
		}
	}
	return NULL;
}

    //return a child by index
    //i.e. return the data in the i-th node in the linked list
    //0-th (first) node is the head node
//return the child of the given index
//return NULL if index is out-of-range
//if there are n children, then a valid index is in [0, n-1]
FSObject* LLDirectory::getChild(int i){
	LLNode* current = head;
	int position=0;
	while (current != NULL && position != i){
		++position;
		current = current->next;
	}
	return current->data;
}

    //return the string that represents the list of children in this directory
    //for LLDirectory, the order of the items is simply the linked list node order
    //i.e., data_in_head_node data_in_second_node data_in_third_node ...
    //if you refer to the example given in addChild, then the return value of this function would be simply
    //"A [Z] a [b] c [e]"
    //as you are supposed to make sure the children are in sorted order when we add a child in addChild,
    //no sorting/reordering needs to be done in this function
    //simply return "<empty>" if the directory is empty (i.e., has no child)
//return the string that represents the list of children in this directory
//the children must be listed in the order specified by the actual directory type
//(for that please see either LLDirectory.h or SADirectory.h)
//in the list, the directory names must be surrounded by a pair of square brackets, i.e., []
//on the other hand, the file names do not have any surrounding brackets
//e.g. if there are 3 directories named "a", "b", and "c"
//and if there are 3 files named "f1", "f2", and "f3"
//list() should return "[a] [b] [c] f1 f2 f3"
//(assume this order; the actual order will depend on the actual Directory type)
//notice that there is no extra spaces in the string at the beginning or at the end
//and that there is exactly one single space between the items
//see the sample output for more examples
string LLDirectory::list(){
	string output = "";
	LLNode* current = head;
	if (head == NULL)
		output = "<empty>";
	while (current != NULL){
		if(typeid(*(current->data)) == typeid(File)){
			string child = current->data->getName();
			output += child + " ";
		}
		else if(typeid(*(current->data)) == typeid(LLDirectory)){
			string child = current->data->getName();
			output += "[" + child + "] ";
		}
		current = current->next;
	}
	string keluar = "";
	for (int i=0; i<output.length()-1; ++i){
		keluar += output[i];
	}
	return keluar;
}

    //return the number of children
    //so count the number of nodes you have in the linked list
int LLDirectory::getCount(){
	LLNode* current = head;
	int num_node=0;
	while (current != NULL){
		current = current->next;
		++num_node;
	}
	return num_node;
}

