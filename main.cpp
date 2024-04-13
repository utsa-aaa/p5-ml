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
    int num_posts = 0;
    int vocab_size = 0;
    map<string, int> word_freq;
    map<string, int> label_freq;
    map<std::pair<string, string>, int> c_with_w;

    float log_likehlihood(const string &word, const string &label){
        float log_val = 0;
        if (c_with_w.find({label, word}) != c_with_w.end()) {

                log_val =  log(c_with_w[{label, word}]/static_cast<float>(label_freq[label]));
  
            }
            //w not in data
            else if (word_freq.find(word) == word_freq.end()){
                log_val =  log(1.0/static_cast<float>(num_posts));
                
            }
            //both in training but not together
            else{
                log_val =  log(word_freq[word]/static_cast<float>(num_posts));

            }
            return log_val;
    }

    float log_total(string &content, const string &label){
        set<string> words = unique_words(content);
        double log_prior = log(static_cast<float>(label_freq[label]) /num_posts);
        double sum = log_prior;
        for (auto word: words){
            sum += log_likehlihood(word, label);
        }
        return sum;
    }


    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }
    map<float, string, std::greater<double>> classifier_map;
    std::pair<string, float> classify(string &content){
        classifier_map.clear();
        for (const auto &label : label_freq) {
            float logProb = log_total(content, label.first);
            if (classifier_map.find(logProb) == classifier_map.end()) { 
                classifier_map[logProb] = label.first;
                
            }
        }
        auto itr = classifier_map.begin();
        return {itr->second, itr->first};

    }

    public:
    void train(ifstream&fin, bool debug){
        if (debug){
            cout << "training data:" << endl;
        }
        std::vector<std::string> line;
        set<string> unique;
        while (read_csv_line(fin,line, ',')) {
            num_posts ++;
            string label = line[2];
            string content = line[3];
            if (debug){
                cout << "  label = " << label << ", content = " << content << endl;
            }

            //label not added yet
            if (label_freq.find(label) == label_freq.end()){
                label_freq[label] = 1;
            }
            else{
                label_freq[label]++;
            }

            unique.clear();
            unique = unique_words(content);
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
    cout << "trained on " << num_posts << " examples" << endl;
    if (debug){
        cout << "vocabulary size = " << vocab_size << endl;
    }
    cout << endl;

    if (debug){
        cout << "classes:" << endl;
        for (auto &label: label_freq){
            cout << "  " << label.first << ", " << label.second << " examples, log-prior = "
             << log(static_cast<float>(label.second) /num_posts) << endl;
        }
        cout << "classifier parameters:" << endl;
        for (auto &word_pair: c_with_w){
            cout << "  " << word_pair.first.first << ":" << word_pair.first.second << ", count = " << word_pair.second <<
            ", log-likelihood = " << log_likehlihood(word_pair.first.second, word_pair.first.first) << endl;
            
        }
    cout << endl;

    }

 }
    void test(ifstream&fin){
        cout <<  "test data:" << endl;
        std::vector<std::string> line;
        int performance = 0;
        int posts = 0;
        while (read_csv_line(fin,line, ',')) {
            string label = line[2];
            string content = line[3];
            auto guess = classify(content);
            cout << "  correct = " << label << ", predicted = " <<
            guess.first << ", log-probability score = " << guess.second << endl;
            cout << "  content = " << content << endl << endl;
            posts ++;
            if (guess.first == label){
                performance++;
            }

        }
        cout << "performance: " << performance << " / " << posts << " posts predicted correctly" << endl;

    }
};







int main(int argc, char **argv){
    cout.precision(3);
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
    if (argc == 4){
        training.train(fin1, true);
    }
    else{
        training.train(fin1, false);
    }

    csvstream testing_data(fin2);
    testing_data.getheader();

    training.test(fin2);

    

}










