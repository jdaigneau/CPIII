/* 
 * File:   main.cpp
 * Author: jeremydaigneau
 *
 * Created on April 26, 2015, 9:21 PM
 */

/*
 * 
 */

#include "tree.h"

using namespace std;

int main()
{
	My_tree index;
	vector<string> book;
	string words;
	string word;

	int count = 0;
	ifstream fin;

	fin.open("pg2600.txt");
	if(fin.fail())
	{
		cout << "bad stuff" << endl;
		exit(1);
	}
        
        while(getline(fin, words))
	{
            book.push_back(words);
            stringstream input_line(words);

            while(input_line >> word)
            {
                index.insert(word, count);
                count++;
            }
		       
	}
        
	cout << "There are " << count << " words." <<  endl;
	list<int> locations;
	list<int>::iterator p;
        int wordCount = 0;
	for(;;)
	{
		cout << "what word? : ";
		cin >> word;
		locations = index.search(word);
		for(p = locations.begin(); p!=locations.end();p++)
		{
			//cout << book[*p] << endl;
                        wordCount++;
		}
                cout << word << " appears " << wordCount << " times." << endl;
                wordCount = 0;
	}   
        
	return 0;
}



