//do NOT submit this file.
//do NOT modify this file.

#ifndef FSOBJECT_H
#define FSOBJECT_H

#include <string>
using namespace std;

//File System Object
class FSObject
{
private:
    string name; //name
    //the file name or the directory name
    //if this is the root (i.e. root directory), then the name will be exactly \ (a single slash)
    //notice that in your code you usually need to write \\ instead of \
    //for this assignment, except for the root's, you can assume the name has only uppercase alphabets, lowercase alphabets, and numbers

    FSObject* parent; //pointer to the parent FSObject
    //in this assignment, the parent is either SADirectory* or LLDirectory*
    //or NULL if this is the root, because root is the only top-level directory

public:
    //default constructor
    //already completed
    FSObject() : name(""), parent(NULL) { } ;

    //constructor
    //already completed
    FSObject(string name, FSObject* parent) : name(name), parent(parent) { } ;

    //destructor
    //it is forced to be a pure virtual function so that FSObject becomes an ABC
    virtual ~FSObject() = 0;

    //return the name
    //already completed
    string getName() { return name; }

    //return the parent
    //already completed
    FSObject* getParent() { return parent; };

    //return the file system path of this object
    //you need to implement it in the cpp file
    string getPath();
};



#endif