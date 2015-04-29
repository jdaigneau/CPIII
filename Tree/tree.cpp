#include "tree.h"

My_tree::My_tree()
{
	root = NULL;
}

void My_tree::insert(const string& word, int line)
{
	//cout<<"Calling insert with " << word <<":" << line << endl;
	insert_helper(root, word, line);

}

void My_tree::insert_helper(Node_ptr& root, const string& word, int line)
{
	Node_ptr temp;
	//cout << "\tCalling insert_helper with " << word << ":" << line << endl;

	if(root == NULL)
	{
		temp = new Node;
		temp->word = word;
		temp->line_numbers.push_back(line);
		temp->count = 1;
		temp->left = NULL;
		temp->right = NULL;
		root = temp;
	}
	else if(word < root->word)
	{
		//cout << "\t\tLEFT" << endl;
		insert_helper(root->left, word, line);
	}
	else if(word > root->word)
	{
		//cout << "\t\tRIGHT" << endl;
		insert_helper(root->right, word, line);
	}
	else
	{
		//cout << "\t\tMATCH" << endl;
		root->count++;
		if(line != root->line_numbers.back())
		{
			root->line_numbers.push_back(line);
		}
	}
}

list<int> My_tree::search(const string& word)
{
	return search_helper(root, word);
}

list<int> My_tree::search_helper(Node_ptr root, const string& word) const
{
	if(root == NULL)
	{
		return list<int>();
	}
	else if(word < root->word)
	{
		return search_helper(root->left, word);
	}
	else if(word > root->word)
	{
		return search_helper(root->right, word);
	}
	else
	{
		return root->line_numbers;
	}
}

/*void My_tree::inOrder(Node_ptr n)
{
   if ( n ) {
       inOrder(n->left());
       cout << n->root << " ";
       inOrder(n->right());
    } 
}*/
   
