//do NOT submit this file.
//do NOT modify this file.

#ifndef FILE_H
#define FILE_H

#include "FSObject.h"

//a file in the file system
//it can be used to store some string content
class File : public FSObject
{
private:
    string content; //the string content

public:
    //constructor
    File(string name = "", FSObject* parent = NULL) : FSObject(name, parent) {}

    //return the content
    //already completed
    string getContent() { return content; }

    //set the content
    //already completed
    void setContent(string content) { this->content = content; }

    //note: there is no File.cpp file - the class is already completed
};

#endif