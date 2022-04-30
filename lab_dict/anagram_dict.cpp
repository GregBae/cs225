/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <unordered_map>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using namespace std;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream file(filename);
    string word;
    if (file.is_open()){
        while(getline(file,word)){
            dict[word].push_back(word);
            for (const pair<string,vector<string>>&key_val : dict){
                if (word!=key_val.first && isAnagram(word,key_val.first)){
                    dict[word].push_back(key_val.first);
                    dict[key_val.first].push_back(word);
                }
            }
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (unsigned i=0;i<words.size();i++){
        dict[words[i]].push_back(words[i]);
        for (const pair<string,vector<string>>&key_val : dict){
            if (words[i]!=key_val.first && isAnagram(words[i],key_val.first)){
                dict[words[i]].push_back(key_val.first);
                dict[key_val.first].push_back(words[i]);
            }
        }
    }
}

bool AnagramDict::isAnagram(const string word1, const string word2) const{
    if (word1.size()!=word2.size())
        return false;
    unordered_map<char,int>map1;
    unordered_map<char,int>map2;
    for (unsigned i=0;i<word1.size();i++){
        if(map1.find(word1[i]) == map1.end()){
            map1[word1[i]] = 1;
        }
        else{
            map1[word1[i]]++;
        }

        if(map2.find(word2[i]) == map2.end()){
            map2[word2[i]] = 1;
        }
        else{
            map2[word2[i]]++;
        }
    }
    return map1 == map2;
}
/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string comp = word;
    vector<string>res;
    if (dict.find(comp) == dict.end())
        return res;
    if (dict.at(comp).size()<2)
        return res;
    return dict.at(comp);


}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>>res;
    bool flag=false;
    for (const pair<string,vector<string>>&key_val : dict){
        if (key_val.second.size()>=2){
            vector<string>anagram = key_val.second;
            for (unsigned i=0;i<res.size();i++){
                if (isAnagram(res[i][0],anagram[0])){
                    flag = true;
                }
            }
            if (!flag){
                res.push_back(anagram);
            }
        }
        flag = false;
    }
    return res;
}
