//do NOT submit this file.
//do NOT modify this file.

#ifndef LLDIRECTORY_H
#define LLDIRECTORY_H

#include "Directory.h"

//Linked-list directory
//it is a directory that is backed by a linked list
//you should read the Directory.h first to see what each member function should do
class LLDirectory : public Directory
{
public:
    //constructor
    //hint: remember to initialize all data members properly!
    LLDirectory(string name, FSObject* parent);

    //destructor
    //delete the whole linked list
    //avoid memory leak
    virtual ~LLDirectory();

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
    virtual bool addChild(bool isDir, string name);

    //remove a child
    //avoid memory leak
    virtual bool removeChild(string name);

    //return a child by name
    virtual FSObject* getChild(string name);

    //return a child by index
    //i.e. return the data in the i-th node in the linked list
    //0-th (first) node is the head node
    virtual FSObject* getChild(int i);

    //return the string that represents the list of children in this directory
    //for LLDirectory, the order of the items is simply the linked list node order
    //i.e., data_in_head_node data_in_second_node data_in_third_node ...
    //if you refer to the example given in addChild, then the return value of this function would be simply
    //"A [Z] a [b] c [e]"
    //as you are supposed to make sure the children are in sorted order when we add a child in addChild,
    //no sorting/reordering needs to be done in this function
    //simply return "<empty>" if the directory is empty (i.e., has no child)
    virtual string list();

    //return the number of children
    //so count the number of nodes you have in the linked list
    virtual int getCount();

private:
    struct LLNode
    {
        LLNode* next; //the next pointer
        FSObject* data; //the data pointer that points to the child, i.e., either a File or a LLDirectory
    }; //this is the linked list node structure you should use for the linked list

    LLNode* head; //the pointer that points to the head node of the linked list of children
    //it should be NULL initially
    //notice that the linked list should have exactly N nodes
    //(including the head node) when there are N items (children)
};

#endif