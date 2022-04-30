/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    vector<vector<string>> list;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()){
        while (getline(wordsFile, word)){
            vector <string> group;
            bool flag=false;
            if (list.empty()){
                group.push_back(word);
                list.push_back(group);
            }
            else{
                for (unsigned i=0;i<list.size();i++){
                    if (d.homophones(list[i][0],word)){
                        list[i].push_back(word);
                        flag = true;
                        break;
                    }
                }
                if (!flag){
                    group.push_back(word);
                    list.push_back(group);
                }
            }
        }
    }
    wordsFile.close();
    for (unsigned i=0;i<list.size();i++){
        if (list[i].size() == 3){
            tuple<string, string, string> tup (list[i][0],list[i][1],list[i][2]);
            ret.push_back(tup);
        }
    }
    return ret;
}
