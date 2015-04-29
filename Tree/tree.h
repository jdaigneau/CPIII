/* 
 * File:   tree.h
 * Author: jeremydaigneau
 *
 * Created on April 28, 2015, 10:08 PM
 */

#ifndef TREE_H
#define	TREE_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Node;
typedef Node* Node_ptr;

struct Node
{
	string word;
	list<int> line_numbers;
	int count;
	Node_ptr left;
	Node_ptr right;
};

class My_tree
{
public:
	My_tree();
	//insert a word from a line number
	void insert(const string& word, int line);
	list<int> search(const string& word);
        void inOrder(Node_ptr n);
        
        //int wordCount(ifstream& fin, string& words, string& word, vector<string> book);
       // int lineCount(ifstream& fin,);
        
	//given a word find out its count and line numbers??
	//destroy the whole tree
	//BIG 3 garbage
	//do we need to overload operators?? (as needed)


private:
	Node_ptr root;
	void insert_helper(Node_ptr& root, const string& word, int line);
	list<int> search_helper(Node_ptr root, const string& word) const;

};

#endif	/* TREE_H */

