//SUBMIT this file
//complete all the missing FSObject implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

#include "FSObject.h"
#include <string>
using namespace std;

//do NOT modify the following line of the destructor implementation, it is already completed
FSObject::~FSObject() {
}
;
//we still have to define it although it is pure virtual since the subclass object destruction will still need to use it

//add your code for FSObject::getPath below
string FSObject::getPath() {
	string output = "";
	if (parent == NULL) {
		return "\\";
	}
	FSObject* p = this;
	if ((p->parent != NULL) && (parent->name != "\\")) {
		output += parent->getPath();
		p = p->parent;
	}
	output += "\\" + name;
	return output;
}

