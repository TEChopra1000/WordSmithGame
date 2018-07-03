#include <time.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#ifndef WordSmith_h
#define WordSmith_h
#include "Trie.h"

class WordSmith
{
private:
   
   //Player Information
   void getPlayerName();
   void playerName() {player = playerFirstName + " " + playerLastName;}
   string playerFirstName;
   string playerLastName;
   string initialWordShuffled;
   
   //members and methods for time-calculations
   const static int GAME_TIME = 60;
   long startTime;
   long currentTime;
   long timeLeft;
   void startTimeCalc();
   bool checkTime();
   
   //members helper functions to load the dictionary
   static Trie dictionary;
   string initialWord;
   static long dictionarySize;
   static void loadDictTrie();
   
   //functions to randomly select and return X-letter word
   vector<string> XLetterWords;
   void pickRandXLetterWord();
   int numberofXLetterWords = 0;
   const int xLetters = 8;
   
   //helpers for returning shuffled word
   string selectDictWord();
   string returnShuffledWordUpper();
   
   //helpers and member to check words that are submitted
   Trie wordsSubmitted;
   bool checkWord(string submittedWord);
   bool isContainedIn(string playerStr, string gameLetters);
   
   //game-player functions
   void startGame();
   void wordSmithGame();
   void bestGame();
   
   //top player and score members and methods
   static string topScorePlayer;
   static int topScore;
   string player;
   int score = 0;
   
public:
   WordSmith();
   void newRoundofGames();
};

#endif /* WordSmith_h */

