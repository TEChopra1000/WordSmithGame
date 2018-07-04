#include <iostream>
#include <fstream>
#include "WordSmith.h"
using namespace std;

Trie WordSmith::dictionary;
long WordSmith::dictionarySize = 0;
string WordSmith::topScorePlayer;
int WordSmith::topScore = 0;

WordSmith::WordSmith()
{
   loadDictTrie();
}

//////////Play Game Functions/////////////
/*The method will being a new round.
 Each round can keep track of the score of multiple players, as well
 as the highest score in the round.*/
void WordSmith::newRoundofGames()
{
   
   string startNewGame;
   cout << "Would you like to start a new game? (Y/N): ";
   cin >> startNewGame;
   while (startNewGame == "Y" || startNewGame == "y")
   {
      wordsSubmitted.clear();  //reset trie of words submitted
      score = 0; //reset the score
      getPlayerName();
      startGame();
      startTimeCalc();
      while(checkTime())
         wordSmithGame();
      bestGame();
      cout << "Would you like to start a new game? (Y/N): ";
      cin >> startNewGame;
   }
}

/*collects a first and last name from the player*/
void WordSmith::getPlayerName()
{
   cout << "Please enter your First Name: ";
   cin >> playerFirstName;
   cout << "Please enter your Last Name: ";
   cin >> playerLastName;
   playerName();
}

/* Starts a single game. Will prompt the player to begin by printing out a
 shuffled word.*/
void WordSmith::startGame()
{
   
   string shuffledWord;
   cout << "Welcome to WordSmithTM - Your letters are: ";
   initialWordShuffled = returnShuffledWordUpper();
   for (int i=0;i<initialWordShuffled.length();i++)
   {
      cout << initialWordShuffled[i] << " ";
   }
   cout << endl;
   cout << "You have " << GAME_TIME << " seconds to form as many words as you"
   << " can with those letters.\n" ;
   cout << "Your current score is: " << score << endl;
}

/*a single player game-play function, which prompts the player to enter
 a word, checks if there is any time left int he game, checks if the word
 is in the dictionary, and awards points appropriately.*/
void WordSmith::wordSmithGame()
{
   string wordEntry;
   
   cout << "Enter Your Word Here: ";
   cin >> wordEntry;
   
   if (!checkTime())
   {
      cout <<
      "Sorry! You ran out of time. Your total score in this game is: ";
      cout << score << endl;
      cout << "The bonus word was: " << initialWord << endl;
      return;
   }
   
   for (int i = 0; i < wordEntry.length(); i++)
   {
      wordEntry[i]=toupper(wordEntry[i]);
   }
   
   if(wordEntry == initialWord && !wordsSubmitted.exists(wordEntry))
   {
      score += 10;
      wordsSubmitted.insert(wordEntry);
      cout << "YESSS!!! Way to go - You got the 10 point bonus word!\n";
   }
   else if(checkWord(wordEntry))
   {
      score += wordEntry.length();
      wordsSubmitted.insert(wordEntry);
      cout << "YES! ";
   }
   else
   {
      if(dictionary.exists(wordEntry) && !isContainedIn(wordEntry, initialWord))
         cout << "Word includes invalid letters. -2 penalty\n";
      else if (wordsSubmitted.exists(wordEntry))
         cout << "Word already submitted! -2 penalty.\n";
      else
         cout << "That isn't a valid word. -2 penalty.\n";
      score -= 2;
      
   }
   cout << "Your current score is: " << score << " and you have " << timeLeft
   << " seconds left.\n";
   cout << "Your letters are: " ;
   for (int i=0;i<initialWordShuffled.length();i++)
   {
      cout << initialWordShuffled[i] << " ";
   }
   cout << endl;
   
   cout << "Your words so far: ";
   wordsSubmitted.printTrie(nullDeque);
   cout << endl;
}

//prints the player with the best score in a single round.
void WordSmith::bestGame()
{
   if (score > topScore && score > 0)
   {
      topScorePlayer = player;
      topScore = score;
   }
   
   if (topScore == 0)
   {
      cout << "There is no top score yet!" << endl;
      return;
   }
   
   cout << "The best score so far: " << WordSmith::topScore <<
   ". The player: " << WordSmith::topScorePlayer << "." << endl;
   cout << "Thank you for Playing!\n";
   return;
}


//voidSmith helpder
bool WordSmith::checkWord(string submittedWord)
{
   return (!wordsSubmitted.exists(submittedWord)
           && dictionary.exists(submittedWord)
           && isContainedIn(submittedWord, initialWord));
}

/*checkWord() helper, makes sure letters submitted by the player
were in original letters (of the shuffled word)
given at the beginning of the game*/
bool WordSmith::isContainedIn(string playerStr, string gameLetters)
{
   int availableLetterCounts[256]; // Num pats in a byte
   for (int i = 0; i < 256; i++) {
      availableLetterCounts[i] = 0;
   }
   for (int i = 0; i < gameLetters.length(); i++) {
      int j = toupper(gameLetters[i]);
      availableLetterCounts[j]++;
   }
   for (int i = 0; i < playerStr.length(); i++) {
      int j = toupper(playerStr[i]);
      if (availableLetterCounts[j]-- <= 0)
         return false;
   }
   return true;
}


//////////Time Calculations/////////////

void WordSmith::startTimeCalc()
{
   startTime = time(NULL);
}

bool WordSmith::checkTime()
{
   long timePassed;
   currentTime = time(NULL);
   timePassed = currentTime - startTime;
   timeLeft = GAME_TIME - timePassed;
   if (timePassed < GAME_TIME)
      return true;
   else
      return false;
}

//////////Prepare Dictionary/////////////

void WordSmith::loadDictTrie()
{
   static bool firstTime = true;
   if (!firstTime) return;
   firstTime = false;
   string word;
   ifstream infile("dictionary.txt");
   if (!infile)
   {
      cout << "couldn't open dictionary.txt for input.\n";
      exit(1);
   }
   
   while(getline(infile, word))
   {
      dictionarySize++;
      for (int i = 0;i<word.length();i++)
      {
         word[i]=toupper(word[i]);
      }
      dictionary.insert(word);
   }
}


//////Prepare Shuffled Word for Start of Game//////////

void WordSmith::pickRandXLetterWord()
{
   string word;
   ifstream newInfile("dictionary.txt");
   if (!newInfile)
   {
      cout << "couldn't open myInputFile.txt for input.\n";
      exit(1);
   }
   
   while(getline(newInfile, word))
   {
      if(word.length() == xLetters)
      {
         XLetterWords.push_back(word);
         numberofXLetterWords++;
      }
   }
}

string WordSmith::selectDictWord()
{
   pickRandXLetterWord();
   srand((unsigned) time(NULL));
   int randInt;
   randInt = rand() % numberofXLetterWords-1;
   if (randInt > 0 && randInt < dictionarySize)
   {
      initialWord = XLetterWords[randInt];
      for (int i = 0;i<initialWord.length();i++)
      {
         initialWord[i]=toupper(initialWord[i]);
      }
      return XLetterWords[randInt];
   }
   else
      exit(1);
   
}

string WordSmith::returnShuffledWordUpper()
{
   string wordToReturn;
   wordToReturn = selectDictWord();
   random_shuffle(wordToReturn.begin(), wordToReturn.end());
   for (int i = 0;i<wordToReturn.length();i++)
   {
      wordToReturn[i]=toupper(wordToReturn[i]);
   }
   return wordToReturn;
}



