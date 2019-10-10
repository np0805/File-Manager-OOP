//do NOT submit this file.
//you may modify it to test your own test cases.
//however, make sure that your code can be compiled with the unmodified version of this file.

#include <iostream>
#include "System.h"
#include "SADirectory.h"
#include "LLDirectory.h"

using namespace std;

int main()
{
    cout << boolalpha;

    {
        cout << "Testing SADirectory below..." << endl << endl;

        cout << "================= Test 1 =================" << endl;
        Directory* r = new SADirectory("\\", NULL);
        cout << r->addChild(true, "a") << endl;
        cout << r->addChild(true, "b") << endl;
        cout << r->addChild(false, "f1") << endl;
        cout << r->addChild(false, "f2") << endl;
        cout << r->addChild(false, "f3") << endl;
        cout << r->addChild(true, "c") << endl;
        cout << r->addChild(true, "c") << endl;
        string s = r->list();
        cout << r->list() << endl;
        if(s != "[a] [b] f1 f2 f3 [c]")
            cout << "Format/output is incorrect! Please check carefully. \nYour output= <" << s << "> \nExpected=    <" << "[a] [b] f1 f2 f3 [c]" << ">" << endl;

        cout << "================= Test 2 =================" << endl;
        cout << r->removeChild("b") << endl;
        cout << r->removeChild("nope") << endl;
        cout << r->list() << endl;

        cout << "================= Test 3 =================" << endl;
        cout << r->getPath() << endl;

        cout << "================= Test 4 =================" << endl;
        cout << (r->getChild("nope")==NULL?"NULL":r->getChild("nope")->getName()) << endl;
        cout << (r->getChild("c")==NULL?"NULL":r->getChild("c")->getName()) << endl;

        cout << "================= Test 5 =================" << endl;
        Directory* c = dynamic_cast<Directory*>(r->getChild("c"));
        cout << c->addChild(true, "ca") << endl;
        cout << c->addChild(true, "cn") << endl;
        cout << c->addChild(false, "cf1") << endl;
        cout << c->list() << endl;

        cout << "================= Test 6 =================" << endl;
        cout << c->getPath() << endl;
        cout << c->getChild("cn")->getPath() << endl;
        cout << c->getChild("cf1")->getPath() << endl;

        cout << "================= Test 7 =================" << endl;
        delete r;
        cout << "SADirectory deleted. I shall make sure there is no memory leak." << endl;

        cout << "================= Test 8 =================" << endl;
        System<SADirectory>* system = new System<SADirectory>;
        cout << system->isValidPath("") << endl;
        cout << system->isValidPath("c") << endl;
        cout << system->isValidPath("\\") << endl;
        cout << system->isValidPath("\\c") << endl;
        cout << system->isValidPath("\\c\\cn") << endl;
        cout << system->isValidPath("\\c\\nope") << endl;

        cout << "================= Test 9 =================" << endl;
        cout << system->addDir("\\", "a") << endl;
        cout << system->addDir("\\", "b") << endl;
        cout << system->addFile("\\", "f1", "hi") << endl;
        cout << system->addFile("\\", "f2", "hello") << endl;
        cout << system->addFile("\\", "f3", "howdy") << endl;
        cout << system->addDir("\\", "c") << endl;
        cout << system->addDir("\\", "c") << endl;
        cout << "In \\ : " << system->list("\\") << endl;

        cout << "================= Test 10 =================" << endl;
        cout << system->del("\\", "b") << endl;
        cout << system->del("\\", "nope") << endl;
        cout << "In \\ : " << system->list("\\") << endl;

        cout << "================= Test 11 =================" << endl;
        cout << (system->getDirectory("\\")==NULL?"NULL":"\\") << endl;
        cout << (system->getDirectory("\\c")==NULL?"NULL":"c") << endl;
        cout << (system->getDirectory("\\nope")==NULL?"NULL":"nope") << endl;

        cout << "================= Test 12 =================" << endl;
        cout << system->getDirectory("\\")->getPath() << endl;
        cout << system->getDirectory("\\c")->getPath() << endl;

        cout << "================= Test 13 =================" << endl;
        cout << system->addDir("\\c", "ca") << endl;
        cout << system->addDir("\\c", "cn") << endl;
        cout << system->addFile("\\c", "cf1", "yo") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        cout << (system->getFile("\\c", "cfnope")?"nope":"NULL") << endl;
        cout << system->getFile("\\c", "cf1")->getContent() << endl;
        system->getFile("\\c", "cf1")->setContent("yoooooooo");
        cout << system->getFile("\\c", "cf1")->getContent() << endl;

        cout << "================= Test 14 =================" << endl;
        cout << system->getDirectory("\\c\\cn")->getPath() << endl;
        cout << system->getFile("\\c", "cf1")->getPath() << endl;

        cout << "================= Test 15 =================" << endl;
        cout << "In \\ : " << system->list("\\") << endl;
        cout << "In \\a : " << system->list("\\a") << endl;
        cout << "In \\b : " << system->list("\\b") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        //eror nope --> empty
        cout << "In \\c\\cn : " << system->list("\\c\\cn") << endl;
        cout << "Move result = " << system->move("\\","f2","\\c","f2") << endl;
        cout << "In \\ : " << system->list("\\") << endl;
        cout << "In \\a : " << system->list("\\a") << endl;
        cout << "In \\b : " << system->list("\\b") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        // eror nope --> empty
        cout << "In \\c\\cn : " << system->list("\\c\\cn") << endl;

        cout << "================= Test 16 =================" << endl;
        //error -2
        cout << system->addFile("\\c\\cn","cnf","so deep!") << endl;
//        cout<<system->getFile("\\c\\cn", "cnf")->getPath()<<endl;
        cout << "In \\ : " << system->list("\\") << endl;
        cout << "In \\a : " << system->list("\\a") << endl;
        cout << "In \\b : " << system->list("\\b") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        //eror
        cout << "In \\c\\cn : " << system->list("\\c\\cn") << endl;
        //eror
        cout << "In \\a\\c : " << system->list("\\a\\c") << endl;
        cout << "In \\a\\c\\cn : " << system->list("\\a\\c\\cn") << endl;
        cout << system->getFile("\\c\\cn", "cnf")->getPath() << endl;
        cout << "Move result = " << system->move("\\","c","\\a","c") << endl;
        cout << "In \\ : " << system->list("\\") << endl;
        cout << "In \\a : " << system->list("\\a") << endl;
        cout << "In \\b : " << system->list("\\b") << endl;
        //eror
        cout << "In \\c : " << system->list("\\c") << endl;
        cout << "In \\c\\cn : " << system->list("\\c\\cn") << endl;
        cout << "In \\a\\c : " << system->list("\\a\\c") << endl;
        //eror
        cout << "In \\a\\c\\cn : " << system->list("\\a\\c\\cn") << endl;
        cout << system->getFile("\\a\\c\\cn", "cnf")->getPath() << endl;

        cout << "================= Test 17 =================" << endl;
        delete system;
        cout << "System deleted. I shall make sure there is no memory leak." << endl;

        cout << "==========================================" << endl;
        cout << endl;
        cout << endl;
    }

    {
        cout << "Testing LLDirectory below..." << endl << endl;

        cout << "================= Test 1 =================" << endl;
        Directory* r = new LLDirectory("\\", NULL);
        cout << r->addChild(true, "a") << endl;
        cout << r->addChild(true, "b") << endl;
        cout << r->addChild(false, "f1") << endl;
        cout << r->addChild(false, "f2") << endl;
        cout << r->addChild(false, "f3") << endl;
        cout << r->addChild(true, "c") << endl;
        cout << r->addChild(true, "c") << endl;
        cout << r->addChild(true, "z") << endl;
        string s = r->list();
        cout << r->list() << endl;
        if(s != "[a] [b] [c] f1 f2 f3 [z]")
            cout << "Format/output is incorrect! Please check carefully. \nYour output= <" << s << "> \nExpected=    <" << "[a] [b] [c] f1 f2 f3 [z]" << ">" << endl;

        cout << "================= Test 2 =================" << endl;
        cout << r->removeChild("b") << endl;
        cout << r->removeChild("nope") << endl;
        cout << r->list() << endl;

        cout << "================= Test 3 =================" << endl;
        cout << r->getPath() << endl;

        cout << "================= Test 4 =================" << endl;
        cout << (r->getChild("nope")==NULL?"NULL":r->getChild("nope")->getName()) << endl;
        cout << (r->getChild("c")==NULL?"NULL":r->getChild("c")->getName()) << endl;

        cout << "================= Test 5 =================" << endl;
        Directory* c = dynamic_cast<Directory*>(r->getChild("c"));
        cout << c->addChild(true, "ca") << endl;
        cout << c->addChild(true, "cn") << endl;
        cout << c->addChild(false, "cf1") << endl;
        cout << c->list() << endl;

        cout << "================= Test 6 =================" << endl;
        cout << c->getPath() << endl;
        cout << c->getChild("cn")->getPath() << endl;
        cout << c->getChild("cf1")->getPath() << endl;

        cout << "================= Test 7 =================" << endl;
        delete r;
        cout << "LLDirectory deleted. I shall make sure there is no memory leak." << endl;

        cout << "================= Test 8 =================" << endl;
        System<LLDirectory>* system = new System<LLDirectory>;
        cout << system->isValidPath("") << endl;
        cout << system->isValidPath("c") << endl;
        cout << system->isValidPath("\\") << endl;
        cout << system->isValidPath("\\c") << endl;
        cout << system->isValidPath("\\c\\cn") << endl;
        cout << system->isValidPath("\\c\\nope") << endl;

        cout << "================= Test 9 =================" << endl;
        cout << system->addDir("\\", "a") << endl;
        cout << system->addDir("\\", "b") << endl;
        cout << system->addFile("\\", "f1", "hi") << endl;
        cout << system->addFile("\\", "f2", "hello") << endl;
        cout << system->addFile("\\", "f3", "howdy") << endl;
        cout << system->addDir("\\", "c") << endl;
        cout << system->addDir("\\", "c") << endl;
        cout << "In \\ : " << system->list("\\") << endl;

        cout << "================= Test 10 =================" << endl;
        cout << system->del("\\", "b") << endl;
        cout << system->del("\\", "nope") << endl;
        cout << "In \\ : " << system->list("\\") << endl;

        cout << "================= Test 11 =================" << endl;
        cout << (system->getDirectory("\\")==NULL?"NULL":"\\") << endl;
        cout << (system->getDirectory("\\c")==NULL?"NULL":"c") << endl;
        cout << (system->getDirectory("\\nope")==NULL?"NULL":"nope") << endl;

        cout << "================= Test 12 =================" << endl;
        cout << system->getDirectory("\\")->getPath() << endl;
        cout << system->getDirectory("\\c")->getPath() << endl;

        cout << "================= Test 13 =================" << endl;
        cout << system->addDir("\\c", "ca") << endl;
        cout << system->addDir("\\c", "cn") << endl;
        cout << system->addFile("\\c", "cf1", "yo") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        cout << (system->getFile("\\c", "cfnope")?"nope":"NULL") << endl;
        cout << system->getFile("\\c", "cf1")->getContent() << endl;
        system->getFile("\\c", "cf1")->setContent("yoooooooo");
        cout << system->getFile("\\c", "cf1")->getContent() << endl;

        cout << "================= Test 14 =================" << endl;
        cout << system->getDirectory("\\c\\cn")->getPath() << endl;
        cout << system->getFile("\\c", "cf1")->getPath() << endl;

        cout << "================= Test 15 =================" << endl;
        cout << "In \\ : " << system->list("\\") << endl;
        cout << "In \\a : " << system->list("\\a") << endl;
        cout << "In \\b : " << system->list("\\b") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        // eror
        cout << "In \\c\\cn : " << system->list("\\c\\cn") << endl;
        //move
        cout << "Move result = " << system->move("\\","f2","\\c","f2") << endl;
        cout << "In \\ : " << system->list("\\") << endl;
        cout << "In \\a : " << system->list("\\a") << endl;
        cout << "In \\b : " << system->list("\\b") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        // eror
        cout << "In \\c\\cn : " << system->list("\\c\\cn") << endl;

        cout << "================= Test 16 =================" << endl;
        cout << system->addFile("\\c\\cn","cnf","so deep!") << endl;
        cout << "In \\ : " << system->list("\\") << endl;
        cout << "In \\a : " << system->list("\\a") << endl;
        cout << "In \\b : " << system->list("\\b") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        cout << "In \\c\\cn : " << system->list("\\c\\cn") << endl;
        cout << "In \\a\\c : " << system->list("\\a\\c") << endl;
        cout << "In \\a\\c\\cn : " << system->list("\\a\\c\\cn") << endl;
//        cout<<"asd";
        cout << system->getFile("\\c\\cn", "cnf")->getPath() << endl;
//        cout<<"asdsfa";
        cout << "Move result = " << system->move("\\","c","\\a","c") << endl;
        //eror belom di move
        cout << "In \\ : " << system->list("\\") << endl;
        //eror belom di move
        cout << "In \\a : " << system->list("\\a") << endl;
        cout << "In \\b : " << system->list("\\b") << endl;
        cout << "In \\c : " << system->list("\\c") << endl;
        cout << "In \\c\\cn : " << system->list("\\c\\cn") << endl;
        cout << "In \\a\\c : " << system->list("\\a\\c") << endl;
        cout << "In \\a\\c\\cn : " << system->list("\\a\\c\\cn") << endl;
        //eror soalnya move belom diimplement
        cout << system->getFile("\\a\\c\\cn", "cnf")->getPath() << endl;

        cout << "================= Test 17 =================" << endl;
        delete system;
        cout << "System deleted. I shall make sure there is no memory leak." << endl;

        cout << "===========================================" << endl;
        cout << endl;
        cout << endl;
    }

    return 0;
}
