
#include <iostream>
#include <string>

#include "Trie.h"
using namespace std;

//constructor
Trie::Trie()
{
   for(int i = 0; i < ALPHABET_SIZE; i ++)
      children[i] = NULL;
   isEndOfWord = false;
}

//destructor
Trie::~Trie()
{
   for (int i = 0; i < ALPHABET_SIZE; i++)
      delete children[i];
}

//clears all data from the trie and reallocates children so that trie can continue to be used.
void Trie::clear()
{
   for (int i = 0; i < ALPHABET_SIZE; i++)
      delete children[i];
   for(int i = 0; i < ALPHABET_SIZE; i ++)
      children[i] = NULL;
}

//checks if a word exists in the trie
bool Trie::exists(string str)
{
   Trie *trieCrawler = this;
   for (int i = 0; i < str.length(); i++)
   {
      int index = str[i] - CASE;
      if (!trieCrawler->children[index])
         return false;
      
      trieCrawler = trieCrawler->children[index];
   }
   
   return (trieCrawler != NULL && trieCrawler->isEndOfWord);
}

//inserts a word into the trie
void Trie::insert(string str)
{
   
   Trie *trieCrawler = this;
   for (int i = 0; i < str.length(); i++)
   {
      int index = str[i] - CASE;
      if (!trieCrawler->children[index])
         trieCrawler->children[index] = new Trie;
      
      trieCrawler = trieCrawler->children[index];
   }
   
   trieCrawler->isEndOfWord = true;
}

//prints all contents of the trie in a list
void Trie::printTrie(deque<char> prefix)
{
   if (this->isEndOfWord)
      print(prefix);
   
   for (int i = 0; i < ALPHABET_SIZE; ++i)
   {
      if (this->children[i])
      {
         char indexChar = i + 'A';
         prefix.push_back(indexChar);
         this->children[i]->printTrie(prefix);
         prefix.pop_back();
      }
   }
}

//helper method for the printTrie() function
void Trie::print(deque<char> toPrint)
{
   while (!toPrint.empty())
   {
      char f = toPrint.front();
      toPrint.pop_front();
      f = tolower(f);
      cout << f ;
   }
   cout << ", ";
}


