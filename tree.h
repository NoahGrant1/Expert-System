/*
 * tree.h
 *
 *  Created on: 11 Sep,2020
 *      Author: antec
 */

#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <queue>
using namespace std;

//Node for non binary tree
struct Node
{
    string key;
    vector<Node *>child;
    Node * parent;
};


Node *findNode(Node *root, string word)
{
	if (root==NULL)
	{
	    return root;
	}

	//search using breadth first
	queue<Node *> next;
    next.push(root);
    root->parent = NULL;

	while (!next.empty())
	{
	    int n = next.size();

	    // If this node has children
	    while (n > 0)
	    {
	        // Dequeue an item from queue and print it
	        Node * current = next.front();

	        //get parent node
	        Node * temp = next.front();
	        next.pop();

	        if(current->key == word)
	        {
	        	return current;
	        }

	        // Enqueue all children of the dequeued item
	        for (unsigned int i=0; i<current->child.size(); i++)
	        {
	        	//assign parent node and queue child
	        	current->child[i]->parent = temp;
	            next.push(current->child[i]);
	        }
	        n--;
	     }
	 }
	 return NULL;
}

//Add a new node to the tree
Node *addNode(string key)
{
    Node *temp = new Node;
    temp->key = key;
    return temp;
}

//print the tree in a breadth first search manor
void printTree(Node * root)
{
    if (root==NULL)
    {
        return;
    }

    // Standard level order traversal code
    // using queue
    queue<Node *> next;  // Create a queue
    next.push(root); // Enqueue root
    while (!next.empty())
    {
        int n = next.size();

        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            Node * current = next.front();
            next.pop();
            cout << current->key << ", ";

            // Enqueue all children of the dequeued item
            for (unsigned int i=0; i<current->child.size(); i++)
            {
                next.push(current->child[i]);
            }
            n--;
        }

        cout << endl; // Print new line between two levels
    }
}




#endif /* TREE_H_ */
