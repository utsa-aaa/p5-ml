#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.hpp"
#include "Map.hpp"

using namespace std;

int main(int argc, char **argv){
    if(argc<3 || argc>4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    }
    if(argc==4 && strcmp(argv[3], "--debug")!=0){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    }

    string filename1 = argv[1];
    string filename2 = argv[2];
    ifstream fin1(filename1);
    ifstream fin2(filename2);
    if(!fin1.is_open()){
        cout << "Error opening file: " << filename1 << endl;
        return 1;
    }
    else if(!fin2.is_open()){
        cout << "Error opening file: " << filename2 << endl;
        return 1;
    }

}


