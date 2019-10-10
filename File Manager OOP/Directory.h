//do NOT submit this file.
//do NOT modify this file.

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FSObject.h"
#include "File.h"
#include <typeinfo>
#include <iostream>
using namespace std;

//a directory in the file system
//it is an ABC
//all child (file/directory) names are unique
class Directory : public FSObject
{
public:
    //constructor
    //already completed
    Directory(string name, FSObject* parent) : FSObject(name, parent) {};

    //destructor
    //already completed
    virtual ~Directory() {};

    //add a child
    //add a new directory, with the given name, under this directory if isDir is true
    //add a new file, with the given name, under this directory if isDir is false
    //the new file's content should be simply empty, i.e., ""
    //to make sure the child name is unique 
    //you should first check to see if an existing child already has the same name
    //if yes, simply do nothing and return false 
    //if no, proceed to add the child, and return true
    virtual bool addChild(bool isDir, string name) = 0;

    //remove a child (can be either a file or directory) from this directory
    //if no child has the given name, simply do nothing and return false
    //otherwise, proceed with the removal and return true
    virtual bool removeChild(string name) = 0;

    //return the child of the given name
    //return NULL if no child has the given name
    virtual FSObject* getChild(string name) = 0;

    //return the child of the given index
    //return NULL if index is out-of-range
    //if there are n children, then a valid index is in [0, n-1]
    virtual FSObject* getChild(int i) = 0;
    
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
    virtual string list() = 0;

    //return the number of children this directory has
    virtual int getCount() = 0;
};

#endif