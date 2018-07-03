

/*
 File: Trie.h
 Author: Talia Chopra
 Date: Winter 2018
 Partner: I worked alone
 Course: Intermediate Software Design in C++ (CS 2B), Foothill College, 2018
 
 Summary of File:
 This file contains the prototype for a trie data structure. This data
 structure can be used to store associative arrays such as strings and is
 useful for storing large quantities of such associative arrays with common
 prefixes, such as dictionaries. 
 */

#ifndef Trie_h
#define Trie_h
#include <string>
#include <deque>
using namespace std;

static const int ALPHABET_SIZE = 26;
static const char CASE = 'A';
static deque<char> nullDeque;

class Trie
{
   friend class WordSmith;
private:
   Trie* children[ALPHABET_SIZE];
   bool isEndOfWord;
   //helper for print Function
   void print(deque<char> toPrint);
   
public:
   Trie();
   ~Trie();
   void insert(string word);
   bool exists(string word);
   void clear();
   void printTrie(deque<char> prefix);
};

#endif /* Trie_h */


