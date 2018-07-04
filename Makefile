#
# Makefile for WordSmith Game 
#	written by Talia Chopra
# 

output: main.o Trie.o WordSmith.o
	g++ main.o Trie.o WordSmith.o -o output 

main.o: main.cpp
	g++ -c main.cpp

Trie.o: Trie.cpp Trie.h
	g++ -c Trie.cpp

WordSmith.o: WordSmith.cpp WordSmith.h
	g++ -c WordSmith.cpp

clean:
	rm *.o output
