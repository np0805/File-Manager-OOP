//SUBMIT this file
//complete all the missing System implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

//   T* root; //the pointer that points to the root directory (i.e. the only top-level directory)

//The file system
//It is a template class where T is either SADirectory or LLDirectory for this assignment
//For simplicity, we won't use both SADirectory and LLDirectory in the same system, i.e.
//System<SADirectory> will only use SADirectory while System<LLDirectory> will only use LLDirectory

//constructor
//initialize the root directory here
//see FSObject.h for the properties of root
template<typename T>
System<T>::System() :
		root(new T("\\", NULL)) {
}

//destructor
//delete the root
//avoid memory leak
template<typename T>
System<T>::~System() {
	delete root;
}

//return true if the given path is valid; return false otherwise
//a path is valid if and only if the length of the path is at least 1 and the path starts with the slash character '\\'
template<typename T>
bool System<T>::isValidPath(string path) {
	if (path[0] == '\\' && path.size() >= 1)
		return true;
	return false;
}

//return the root pointer
template<typename T>
Directory* System<T>::getRoot() {
	return root;
}

//return the directory given the path
//notice that the path here includes also the directory name
//e.g. with path being "\\a\\b", you should return a pointer to the directory "b" under "a" which is under the root "\\"
//return NULL if the path is invalid according to isValidPath
//return NULL if there is no directory at the given path
template<typename T>
Directory* System<T>::getDirectory(string path) {
	if (!isValidPath(path)) {
		return NULL;
	} else {
		string output = "";
		T* p = root;
		if (path.length() == 1) {
			return root;
		}
		for (unsigned int a = 1; a < path.length(); ++a) {
			if (path[a] == '\\') {
				p = dynamic_cast<T*>(p->getChild(output));
				if (p == NULL) {
					return NULL;
				}
				output.clear();
			} else {
				output += path[a];
			}
		}
		p = dynamic_cast<T*>(p->getChild(output));
		if (p != NULL) {
			return p;
		}
	}
	return NULL;
}

//return the file given by the path and name
//e.g. if path is "\\a" and name is "b", you should return the pointer to file "b" under "a" which is under the root "\\"
//return NULL if the given path is invalid according to isValidPath
//return NULL if the given path does not indicate an existing directory
//(e.g., in our example, if "a" doesn't exist under root or is not a directory, return NULL)
//return NULL if the child of the given name under the given path doesn't exist or is not a file
//(e.g., in our example, if "b" doesn't exist under "\\a" or is not a file, return NULL)
template<typename T>
File* System<T>::getFile(string path, string name) {
	if (!isValidPath(path))
		return NULL;
	if (getDirectory(path) == NULL)
		return NULL;
	if (getDirectory(path)->getChild(name) == NULL)
		return NULL;
	if (typeid(*(getDirectory(path)->getChild(name))) == typeid(File)) {
		File* p = dynamic_cast<File*>(getDirectory(path)->getChild(name));
		if (p != NULL)
			return p;
	} else
		return NULL;
	//return NULL if the given path does not indicate an existing directory
}

//add a new directory (of type T) of the given name to the given path, and return 0
//e.g. if path is "\\a" and name is "b", you should create a new directory named "b" under "a" which is under the root "\\"
//however, do nothing and return a negative number instead according to the following if applicable
//return -1 if the given path is invalid according to isValidPath
//return -2 if the given path does not indicate an existing directory
//(e.g., in our example, if "a" doesn't exist under root or is not a directory, return NULL)
//return -3 if the addChild function of the directory of the given path returns false
template<typename T>
int System<T>::addDir(string path, string name) {
	if (!isValidPath(path)) {
		return -1;
	} else if (getDirectory(path) == NULL) {
		return -2;
	} else if (getDirectory(path)->addChild(true, name))
		return 0;
	else
		return -3;
}

//add a new file of the given name to the given path, also set its content according to the parameter, and return 0
//e.g. if path is "\\a" and name is "b", you should create a new file named "b" under "a" which is under the root "\\",
//and set the content accordingly
//however, do nothing and return a negative number instead according to the following if applicable
//return -1 if the given path is invalid according to isValidPath
//return -2 if the given path does not indicate an existing directory
//(e.g., in our example, if "a" doesn't exist under root or is not a directory, return NULL)
//return -3 if the addChild function of the directory of the given path returns false
template<typename T>
int System<T>::addFile(string path, string name, string content) {
	if (!isValidPath(path))
		return -1;
	else if (getDirectory(path) == NULL)
		return -2;
	if (getDirectory(path)->addChild(false, name)) {
		getFile(path, name)->setContent(content);
		return 0;
	}
	else
		return -3;
}

//return the string that represents the list of children in the directory specified in the given path
//notice that the path here includes also the directory name (see getDirectory comment)
//however, return "" instead if the given path is invalid according to isValidPath
//or return "<nope>" instead if the given path does not indicate an existing directory
//or return "<empty>" if the directory is empty (i.e., has no child)
template<typename T>
string System<T>::list(string path) {
	if (!isValidPath(path))
		return "";
	else if (getDirectory(path) == NULL)
		return "<nope>";
	else if (getDirectory(path)->getCount() == 0)
		return "<empty>";
	return getDirectory(path)->list();
}

//remove the child of the given name under the given path, and return 0
//however, do nothing and return a negative number instead according to the following if applicable
//return -1 if the given path is invalid according to isValidPath
//return -2 if the given path does not indicate an existing directory
//return -3 if the removeChild function of the directory of the given path returns false
template<typename T>
int System<T>::del(string path, string name) {
	if (!isValidPath(path))
		return -1;
	if (getDirectory(path) == NULL)
		return -2;
	if (getDirectory(path)->removeChild(name))
		return 0;
	else
		return -3;
}

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
template<typename T>
int System<T>::move(string fromPath, string fromName, string toPath,
		string toName) {
	if (!isValidPath(fromPath) && !isValidPath(toPath))
		return -1;
	else if (getDirectory(fromPath) == NULL && getDirectory(toPath) == NULL)
		return -2;
	if (typeid(*(getDirectory(fromPath)->getChild(fromName))) == typeid(File)) {
		this->addFile(toPath, toName,
				getFile(fromPath, fromName)->getContent());
		this->del(fromPath, fromName);
		return 0;
	} else {
		Directory* p = dynamic_cast<Directory*>(getDirectory(fromPath)->getChild(fromName));
		if(p != NULL){
			if (p->getCount() == 0) {
				this->addDir(toPath, toName);
				this->del(fromPath, fromName);
				return 0;
			} else {
				this->addDir(toPath, toName);
				int count = p->getCount();
				for (int i = 0; i < count; ++i) {
					string fpath1 = p->getPath();
					string fname1 = p->getChild(0)->getName();

					string tpath1 = getDirectory(toPath)->getChild(toName)->getPath();
					string tname1 = p->getChild(0)->getName();

					move(fpath1, fname1, tpath1, tname1);
				}
				this->del(fromPath, fromName);
			}
		}
		p = nullptr;
	}
	return 0;
}
