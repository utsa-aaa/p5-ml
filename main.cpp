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
    //stores occurences of each word with each label
    map<std::pair<string, string>, int> c_with_w;

    float log_likehlihood(const string &word, const string &label){
        float log_val = 0;

        if (c_with_w.find({label, word}) != c_with_w.end()) {
            //if label and word found together in training
            log_val =  log(c_with_w[{label, word}]/static_cast<float>(label_freq[label]));
  
            }
            //word not in data
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
    //declare map to enable re-use, storing log probability for each string in content
    map<float, string, std::greater<double>> classifier_map;

    std::pair<string, float> classify(string &content){
        classifier_map.clear();

        for (const auto &label : label_freq) {
            float logProb = log_total(content, label.first);
            //if theres a tie, it takes the first one, which is alphabetically first
            if (classifier_map.find(logProb) == classifier_map.end()) { 
                classifier_map[logProb] = label.first;
                
            }
        }
        //largest element is first due to map sorting
        auto itr = classifier_map.begin();
        return {itr->second, itr->first};

    }

    public:
    void train(csvstream&data, bool debug){
        if (debug){
            cout << "training data:" << endl;
        }
        //declare set and map for reuse, storing unique words and content of each row
        set<string> unique;
        std::map<std::string, std::string> row;
        while (data >> row) {
            num_posts ++;
            if (debug){
                cout << "  label = " << row["tag"] << ", content = " << row["content"] << endl;
            }

            //label not added yet
            if (label_freq.find(row["tag"]) == label_freq.end()){
                label_freq[row["tag"]] = 1;
            }
            else{
                label_freq[row["tag"]]++;
            }

            unique.clear();
            //set of unique words for the row
            unique = unique_words(row["content"]);
            //add to frequency for each unique word in row
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
                std::pair<string, string> label_word_pair = make_pair(row["tag"], word);
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
    void test(csvstream &data){
        cout <<  "test data:" << endl;
        int performance = 0;
        int posts = 0;
        //map will store label and contents of each row
        std::map<std::string, std::string> row;
        while (data >> row) {
            // guess stores classification and lob probability of content
            auto guess = classify(row["content"]);
            cout << "  correct = " << row["tag"] << ", predicted = " <<
            guess.first << ", log-probability score = " << guess.second << endl;
            cout << "  content = " << row["content"] << endl << endl;
            posts ++;
            if (guess.first == row["tag"]){
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
    Classifier training;
    if (argc == 4){
        training.train(training_data, true);
    }
    else{
        training.train(training_data, false);
    }

    csvstream testing_data(fin2);
    training.test(testing_data);

    

}










