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

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream word_file(filename);
    string line;
    if (word_file.is_open()) {
        while (getline(word_file, line)) {
            vector<string> anagrams = get_anagrams(line);
            if (std::find(anagrams.begin(), anagrams.end(), line) == anagrams.end()) {
                string w = line;
                std::sort(w.begin(), w.end());
                dict[w].push_back(line);
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
    for (string word: words) {
        vector<string> anagrams = get_anagrams(word);
        if (std::find(anagrams.begin(), anagrams.end(), word) == anagrams.end()) {
            string w = word;
            std::sort(w.begin(), w.end());
            dict[w].push_back(word);
        }
    }
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
    string w = word;
    std::sort(w.begin(), w.end());
    if (dict.find(w) == dict.end()) { return vector<string>(); }
    if (std::find(dict.at(w).begin(), dict.at(w).end(), word) == dict.at(w).end()) {
        return vector<string>();
    }
    return dict.at(w);
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
    vector<vector<string>> out;
    for (auto anagrams: dict) {
        if (anagrams.second.size() > 1) {
            out.push_back(anagrams.second);
        }
    }
    return out;
}
