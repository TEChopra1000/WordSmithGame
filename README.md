# WordSmithGame

##Overview

Welcome to Word Smith: a multiplayer, word-centric, mind-teaser game!

In this game you can challenge your friends and see who can come up with the most words,
from a collection of shuffled letters, in 2 minutes.

The rules of the game are as follows:
- When the game starts, each player must enter their first and last name
- A random word will be chosen from the english dictionary, the letters of this word will
  be shuffled, and the player will be shown the shuffled letters.
- In 2 minutes, the player must come up with as many words as he or she can using these
  letters.
- If a submitted word is a valid, english word, 2 points will be added to the player's
  score, and if an invalid word is submitted, 2 points will be deducted. If the player
correctly guess the word that was selected from the english dictionary before the letters
were shuffled (in the first step), he or she will be granted 10 points.
- At the end of 2 minutes, the player will be notified that time is up, what his or her
  final score is, and which player has scored the highest thus far in the round.
-  At this time a new player can join the game, or the same player can play again by
   entering "Y" when the game asks "would like to start a new game?".  If "N" is entered,
the round will terminate.

To start a game, use the following commands in your client:

WordSmith newGames; newGames.newRoundofGames();

To end a game, simply press “N” when prompted at the end of the first-round.


##Implementation The game was written in C++. A Trie data structure (prefix trees) was
used to store and search through an English dictionary, as well as to store and search
trough words submitted by players.


###Why Use a Trie?

Why use a trie? The cost for insertion and searching within a trie is O(k) where k is the
length of the word being inserted or searched for. Therefore, a trie can be used to store
an entire dictionary in relatively little time. Construction and searching can be complete
in a maximum of O(M) time where M is the largest word in the dictionary. Additionally,
when searching for a word we can either search with a single letter, a prefix, or the word
itself.

While other data structures such as hash tables may be viable alternatives, they do not
allow for prefix searching which makes the trie especially well suit for this application.
