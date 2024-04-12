#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.hpp"
#include "csvstream.hpp"
#include <map>
#include <set>

using namespace std;

class Classifier{
    public:
    int num_posts;
    int vocab_size;
    map<string, int> word_freq;
    map<string, int> label_freq;
    map<std::pair<string, string>, int> c_with_w;
    //one more - for each label c and word w, 
    //the number of posts with label c that contain w
    //idk how to do that one

    
};
 set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }

void train(Classifier &training_class, ifstream&fin){
    std::vector<std::string> line;
    while (read_csv_line(fin,line, ',')) {
        training_class.num_posts ++;
        string label = line[2];
        string content = line[3];

        //label not added yet
        if (training_class.label_freq.find(label) == training_class.label_freq.end()){
             training_class.label_freq[label] = 1;
        }
        else{
            training_class.label_freq[label]++;
        }


        set<string> unique = unique_words(content);
        for (auto word: unique){
            if (training_class.word_freq.find(word) == training_class.word_freq.end()){
                //word not in classifier yet
                training_class.vocab_size++;
                training_class.word_freq[word] = 1;
            }
            else{
                 training_class.word_freq[word]++;
            }
            //add to c_with_w
            std::pair<string, string> label_word_pair = make_pair(label, word);
            if (training_class.c_with_w.find(label_word_pair) == training_class.c_with_w.end()){
                 training_class.c_with_w[label_word_pair] = 1;
            }
            else{
            training_class.c_with_w[label_word_pair]++;
            }
        
        }

    }

}


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

    csvstream training_data(fin1);
    training_data.getheader();
    Classifier training;

    //make function train
    train(training, fin1);

}


    // tuirn each content to set
    //adjust classifier


