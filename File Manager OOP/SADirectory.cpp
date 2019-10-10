//SUBMIT this file
//complete all the missing SADirectory implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

#include "SADirectory.h"
#include <typeinfo>
#include <iostream>
#include <string>

using namespace std;

//Static array directory
//it is a directory that is backed by a static array of pointers
//you should read the Directory.h first to see what each member function should do

    //constructor
    //hint: remember to initialize all data members properly! C++ doesn't give default values to uninitialized data members
SADirectory::SADirectory(string name, FSObject* parent) : Directory(name, parent){
	count = 0;
	for (int i = 0; i < DIR_SIZE; ++i){
		children[i] = nullptr;
	}
}

    //destructor
    //delete all children
    //avoid memory leak
SADirectory::~SADirectory(){
	for (int i = 0; i < this->count; ++i){
		delete children[i];
		children[i] = nullptr;
	}
}

    //add a child
    //(please read Directory.h first)
    //for SADirectory, you would also simply do nothing and return false
    //if the number of children is already at DIR_SIZE (i.e. no space to add anymore)
    //for SADirectory, when you add a child, always add it to the next empty slot of the array
    //e.g., if there are 3 children, they should occupy children[0], children[1], and children[2]
    //in other words, N children should occupy the first N slots of the array
    //the latest child should have the biggest index
    //hint: you need to create either a new SADirectory or new File object here for adding a child

//add a child
//add a new directory, with the given name, under this directory if isDir is true
//add a new file, with the given name, under this directory if isDir is false
//the new file's content should be simply empty, i.e., ""
//to make sure the child name is unique
//you should first check to see if an existing child already has the same name
//if yes, simply do nothing and return false
//if no, proceed to add the child, and return true
bool SADirectory::addChild(bool isDir, string name){
	for (int i=0; i<count; ++i){
		if (children[i]->getName() == name){
			return false;
		}
	}
	if (count == DIR_SIZE){
		return false;
	}
	else{
		if (isDir){
			children[count++] = new SADirectory(name, this);
			return true;
		}
		else if (!isDir){
			File* tmp = new File(name, this);
			tmp->setContent("");
			children[count++] = tmp;
			return true;
		}
	}
	return false;
}

    //remove a child
    //make sure the remaining N children occupy the first N slots of the array
    //so some moving of the elements may need to be performed
    //hint: need to delete a child to avoid memory leak
bool SADirectory::removeChild(string name){
	int place;
	bool canRemove = false;
	if (count==0){
		return false;
	}
	for (int i=0; i<count; ++i){
		if (children[i]->getName() == name){
			place = i;
			canRemove = true;
		}
	}
	if (canRemove){
		delete children[place];
		for (int i=place; i<count-1; ++i){
			children[i] = children[i+1];
		}
		children[count-1] = nullptr;
		--count;
	}
	return canRemove;
}


    //return a child by name
FSObject* SADirectory::getChild(string name){
	for (int i=0; i<count; ++i){
		if (children[i]->getName() == name)
			return children[i];
	}
	return NULL;
}

    //return a child by index
//return the child of the given index
//return NULL if index is out-of-range
//if there are n children, then a valid index is in [0, n-1]
FSObject* SADirectory::getChild(int i){
	if (i>=0 && i<count)
		return children[i];
	return NULL;
}

    //return the string that represents the list of children in this directory
    //for SADirectory, the order of the items is simply the array element order
    //i.e., children[0] children[1] ... children[count-1]
    //in other words, the latest child always appears last
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
string SADirectory::list(){
	string output = "";
	if (count==0)
		return "<empty>";
	for (int i=0; i<count; ++i){
		if(typeid(*children[i]) == typeid(File)){
			output += children[i]->getName() + " ";
		}
		else if(typeid(*children[i]) == typeid(SADirectory)){
			output += "[" + children[i]->getName() + "] ";
		}
	}
	string keluar = "";
	for (int i=0; i<output.length()-1; ++i){
		keluar += output[i];
	}
	return keluar;
}

    //return the number of children
int SADirectory::getCount(){
	return count;
}
