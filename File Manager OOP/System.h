//do NOT submit this file.
//do NOT modify this file.

#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include "Directory.h"
using namespace std;

//The file system
//It is a template class where T is either SADirectory or LLDirectory for this assignment
//For simplicity, we won't use both SADirectory and LLDirectory in the same system, i.e.
//System<SADirectory> will only use SADirectory while System<LLDirectory> will only use LLDirectory
template <typename T>
class System
{
private:
    T* root; //the pointer that points to the root directory (i.e. the only top-level directory)

public:
    //constructor
    //initialize the root directory here
    //see FSObject.h for the properties of root
    System();

    //destructor
    //delete the root
    //avoid memory leak
    ~System();

    //return true if the given path is valid; return false otherwise
    //a path is valid if and only if the length of the path is at least 1 and the path starts with the slash character '\\'
    bool isValidPath(string path);

    //return the root pointer
    Directory* getRoot();

    //return the directory given the path
    //notice that the path here includes also the directory name
    //e.g. with path being "\\a\\b", you should return a pointer to the directory "b" under "a" which is under the root "\\"
    //return NULL if the path is invalid according to isValidPath
    //return NULL if there is no directory at the given path
    Directory* getDirectory(string path);

    //return the file given by the path and name
    //e.g. if path is "\\a" and name is "b", you should return the pointer to file "b" under "a" which is under the root "\\"
    //return NULL if the given path is invalid according to isValidPath
    //return NULL if the given path does not indicate an existing directory
    //(e.g., in our example, if "a" doesn't exist under root or is not a directory, return NULL)
    //return NULL if the child of the given name under the given path doesn't exist or is not a file
    //(e.g., in our example, if "b" doesn't exist under "\\a" or is not a file, return NULL)
    File* getFile(string path, string name);

    //add a new directory (of type T) of the given name to the given path, and return 0
    //e.g. if path is "\\a" and name is "b", you should create a new directory named "b" under "a" which is under the root "\\"
    //however, do nothing and return a negative number instead according to the following if applicable
    //return -1 if the given path is invalid according to isValidPath
    //return -2 if the given path does not indicate an existing directory
    //(e.g., in our example, if "a" doesn't exist under root or is not a directory, return NULL)
    //return -3 if the addChild function of the directory of the given path returns false
    int addDir(string path, string name);

    //add a new file of the given name to the given path, also set its content according to the parameter, and return 0
    //e.g. if path is "\\a" and name is "b", you should create a new file named "b" under "a" which is under the root "\\",
    //and set the content accordingly
    //however, do nothing and return a negative number instead according to the following if applicable
    //return -1 if the given path is invalid according to isValidPath
    //return -2 if the given path does not indicate an existing directory
    //(e.g., in our example, if "a" doesn't exist under root or is not a directory, return NULL)
    //return -3 if the addChild function of the directory of the given path returns false
    int addFile(string path, string name, string content);

    //return the string that represents the list of children in the directory specified in the given path
    //notice that the path here includes also the directory name (see getDirectory comment)
    //however, return "" instead if the given path is invalid according to isValidPath
    //or return "<nope>" instead if the given path does not indicate an existing directory
    //or return "<empty>" if the directory is empty (i.e., has no child)
    string list(string path);

    //remove the child of the given name under the given path, and return 0
    //however, do nothing and return a negative number instead according to the following if applicable
    //return -1 if the given path is invalid according to isValidPath
    //return -2 if the given path does not indicate an existing directory
    //return -3 if the removeChild function of the directory of the given path returns false
    int del(string path, string name);

    //move a child of the name fromName under the directory of path fromPath
    //to the directory of path toPath; the child will have the name toName at the destination
    //you should study the sample output carefully to see what is expected
    //if the source item (the fromName under fromPath) is a directory,
    //then all its children will also be moved accordingly
    //if the move is successful, return 0 at the end
    //however, do nothing and return a negative number instead according to the following if applicable
    //return -1 if any of the given fromPath and toPath is invalid according to isValidPath
    //return -2 if any of the fromPath directory and toPath directory is not an existing directory
    //for simplicity, you can assume there is NO other move failure scenario for this assignment
    //you can also assume that we will not try to move a directory to some subdirectory in itself
    //hint: you may use recursion
    int move(string fromPath, string fromName, string toPath, string toName);
};

#include "System.tpp"

#endif
