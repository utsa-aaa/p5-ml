#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.hpp"
#include "csvstream.hpp"
#include <map>
#include <set>
#include <cmath>

using namespace std;

class Classifier{
    private:
    int num_posts;
    int vocab_size;
    map<string, int> word_freq;
    map<string, int> label_freq;
    map<std::pair<string, string>, int> c_with_w;




    public:
    void train(ifstream&fin){
        std::vector<std::string> line;
        while (read_csv_line(fin,line, ',')) {
            num_posts ++;
            string label = line[2];
            string content = line[3];

            //label not added yet
            if (label_freq.find(label) == label_freq.end()){
                label_freq[label] = 1;
            }
            else{
                label_freq[label]++;
            }


            set<string> unique = unique_words(content);
            for (auto word: unique){
                if (word_freq.find(word) == word_freq.end()){
                    //word not in classifier yet
                    vocab_size++;
                    word_freq[word] = 1;
                }
                else{
                    word_freq[word]++;
                }
                //add to c_with_w
                std::pair<string, string> label_word_pair = make_pair(label, word);
                if (c_with_w.find(label_word_pair) == c_with_w.end()){
                    c_with_w[label_word_pair] = 1;
                }
                else{
                    c_with_w[label_word_pair]++;
                }
            
            }

        }

    }
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




int main(int argc, char **argv){
    if(argc<3 || argc>4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }
    if(argc==4 && strcmp(argv[3], "--debug")!=0){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
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

    
    training.train(fin1);

}












