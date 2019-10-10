//do NOT submit this file.
//do NOT modify this file.

#ifndef SADIRECTORY_H
#define SADIRECTORY_H

#include "Directory.h"

const int DIR_SIZE = 8; //the maximum number of children a directory can have for SADirectory

//Static array directory
//it is a directory that is backed by a static array of pointers
//you should read the Directory.h first to see what each member function should do
class SADirectory : public Directory
{
public:
    //constructor
    //hint: remember to initialize all data members properly! C++ doesn't give default values to uninitialized data members
    SADirectory(string name, FSObject* parent);

    //destructor
    //delete all children
    //avoid memory leak
    virtual ~SADirectory();

    //add a child
    //(please read Directory.h first)
    //for SADirectory, you would also simply do nothing and return false
    //if the number of children is already at DIR_SIZE (i.e. no space to add anymore)
    //for SADirectory, when you add a child, always add it to the next empty slot of the array
    //e.g., if there are 3 children, they should occupy children[0], children[1], and children[2]
    //in other words, N children should occupy the first N slots of the array
    //the latest child should have the biggest index
    //hint: you need to create either a new SADirectory or new File object here for adding a child
    virtual bool addChild(bool isDir, string name);

    //remove a child
    //make sure the remaining N children occupy the first N slots of the array
    //so some moving of the elements may need to be performed
    //hint: need to delete a child to avoid memory leak
    virtual bool removeChild(string name);

    //return a child by name
    virtual FSObject* getChild(string name);

    //return a child by index
    virtual FSObject* getChild(int i);

    //return the string that represents the list of children in this directory
    //for SADirectory, the order of the items is simply the array element order
    //i.e., children[0] children[1] ... children[count-1]
    //in other words, the latest child always appears last
    //simply return "<empty>" if the directory is empty (i.e., has no child)
    virtual string list();

    //return the number of children
    virtual int getCount();

private:
    FSObject* children[DIR_SIZE]; //the array of child pointers
    //N children should always occupy the first N slots of the array

    int count; //number of children; should be 0 initially
};

#endif