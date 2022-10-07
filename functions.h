/*
 * functions.h
 *
 *  Created on: 25 Sep,2020
 *      Author: antec
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <map>
#include <vector>
#include "tree.h"
using namespace std;

class ReferenceAdvisor
{
public:
	Node* makeTree();
	void addReferenceInfo();
	void addUnitInfo();
	void addDictInfo();
	void userQuestions();
	bool searchTree(Node *root, string value);
	vector<string> findKeyWords(string question);


private:
	map<string,string> Refs;
	map<string, pair<string,string>> Units;
	map<int,string> dictionary;
};

//search the tree for a particular word
bool ReferenceAdvisor::searchTree(Node* root,string value)
{
	//find the word in the tree
	Node *temp = findNode(root,value);
	if( temp != NULL )
	{
	    return true;
    }

	return false;
}

//words to look for in questions
void ReferenceAdvisor::addDictInfo()
{
	//question types
    dictionary.emplace(1,"unit");
    dictionary.emplace(2,"contents");
    dictionary.emplace(3,"reference");
    dictionary.emplace(4,"belongs");
    dictionary.emplace(5,"include");
    dictionary.emplace(6,"good");

    //unit names
    dictionary.emplace(7,"Intelligent Systems");
    dictionary.emplace(8,"Computer Security");
    dictionary.emplace(9,"Databases");

    //references names
    dictionary.emplace(10,"Winston");
    dictionary.emplace(11,"Ginsberg");
    dictionary.emplace(12,"McNab");
    dictionary.emplace(13,"Kabay");
    dictionary.emplace(14,"Date");
    dictionary.emplace(15,"Hull");

    //descriptions
    dictionary.emplace(16,"advanced");
    dictionary.emplace(17,"basic");
    dictionary.emplace(18,"flexible");
    dictionary.emplace(19,"theoretical");
    dictionary.emplace(20,"valuable for knowledge systems");
    dictionary.emplace(21,"postgraduate");

}

//search question for key words
vector<string> ReferenceAdvisor::findKeyWords(string question)
{
	vector<string> result;

	for ( auto it = dictionary.begin(); it != dictionary.end(); it++ )
	{
		 //get Keywords in dictionary
		 size_t found = question.find(it->second);
		 if(found != string::npos)
		 {
		    result.push_back(it->second);
		 }
	}
    return result;
}

//accepts User Questions
void ReferenceAdvisor::userQuestions()
{
	//get user question
	Node * root = makeTree();
	string question;

	//allow for repeated user questions
	while(question != "finished")
	{

		cout << "Enter a Question to ask?" << endl;
		getline (cin,question);

		//find a unit
		if(question != "finished")
		{
			vector<string> temp;
			temp = findKeyWords(question);

			if(temp.size() == 0)
		    {
			   cout <<"Invalid question cannot answer" << endl;
			}
			else
			{

			    //is this a unit? (question 1) exclude other unit questions
			    if(temp[0] == "unit" &&( temp[1] != "belongs" &&  temp[1] != "good"))
			    {
				    if(temp.size() > 1)
				    {
				        if( searchTree(root,temp[1]))
				        {
                            cout << "Yes" << endl;
				        }
				        else
				        {
                            cout << "No" << endl;
				        }
				    }
				    else
				    {
					    cout << "No" << endl;
				    }
			   }

			   //unit contents question (question 2)
			   if(temp[0] == "contents")
			   {
                   if(temp.size() > 1)
                   {
                	   for ( auto it = Units.begin(); it != Units.end(); it++ )
                	   {
                		   if(it->first == temp[1])
                		   {
                	          cout <<"content = " << it->second.first << endl;
                	          cout <<"content = " << it->second.second << endl;
                		   }
                	   }
                   }
                   else
                   {
                	   cout << "No Content Available " << endl;
                   }
			   }

			   //reference question (question 3)
			   if(temp[0] == "reference")
			   {
			       if(temp.size() > 1)
			       {
			    	   Node *value = findNode(root,temp[1]);
			    	   if(value != NULL)
			    	   {
                           cout << "ref = " << value->child[0]->key << endl;
                           cout << "ref = " << value->child[1]->key << endl;
			    	   }
			       }
			       else
			       {
			           cout << "No References Available " << endl;
			       }
		      }

			  //question 4
			  if(temp[0] == "unit" && temp[1] == "belongs")
			  {
				  if(temp.size() == 3)
			      {
				      Node *value = findNode(root,temp[2]);
					  if(value != NULL)
					  {
			              cout << "unit = " << value->parent->key << endl;
				      }
				  }
				  else
				  {
				      cout << "No Unit contains reference " << endl;
				  }
			  }


			  //does reference include description (question 5)
			  if(temp[0] == "include")
			  {
				  if(temp.size() == 3)
			      {
					  for ( auto it = Refs.begin(); it != Refs.end(); it++ )
					  {
					      if(it->first == temp[1])
					      {
					    	  size_t found = it->second.find(temp[2]);
                              if(found != string::npos )
                              {
                                   cout << "Yes" << endl;
                              }
                              else
                              {
                            	  cout << "No" << endl;
                              }
					      }
					  }
				   }
				   else
				   {
				       cout << "No" << endl;
			       }
			   }


			   //question 6
			   if(temp[0] == "unit" && temp[1] == "good")
			   {
				    if(temp.size() == 4)
				    {
					    string description;

					    //get ref description
                        for ( auto it = Refs.begin(); it != Refs.end(); it++ )
                        {
                            if(temp[2] == it->first)
                            {
                                description = it->second;
                            }
                        }

                       //find units in the description
                       for ( auto it = Units.begin(); it != Units.end(); it++ )
                       {
                    	   size_t found = description.find(it->first);
                    	   if(found != string::npos )
                    	   {
                    	       cout << "unit = " << it->first << endl;
                    	   }
                       }
				   }
				   else
			       {
				        cout << "No Units available" << endl;
				   }
			   }

			}//end questions


		}
		cout << endl;
	}

	cout << "Reference Questioning finished" << endl;
	cout <<"Shutting down system" << endl;
}

//add unit info
void ReferenceAdvisor::addUnitInfo()
{
	Units.emplace("Intelligent Systems",make_pair("AI principles", "AI applications"));
	Units.emplace("Computer Security", make_pair("Security principles","Security programming"));
	Units.emplace("Databases", make_pair("Database principles","Database applications"));
}

//Add reference info to the database.
void ReferenceAdvisor::addReferenceInfo()
{
	Refs.emplace("Winston","suited for flexible of Intelligent Systems "
			     "presents basic for AI principles");
	Refs.emplace( "Ginsberg","good for postgraduate study in Intelligent Systems "
			     "includes advanced techniques of Intelligent Systems");
	Refs.emplace( "McNab","suited for flexible of security"
			     "includes advanced techniques of information security");
	Refs.emplace("Kabay","suited for flexible of network security and database security"
			     "includes theoretical foundations of network security"
			     "good for postgraduate study in security");
	Refs.emplace( "Date", "suited for flexible of database"
			"presents basic for database principles");
	Refs.emplace( "Hull","includes theoretical foundations of databases"
			"good for postgraduate study in Databases and Intelligent Systems");

}

//generates the directory
Node* ReferenceAdvisor::makeTree()
{
	//root
	Node *root = addNode("Units");

	//first level
	(root->child).push_back(addNode("Intelligent Systems"));
	(root->child).push_back(addNode("Computer Security"));
	(root->child).push_back(addNode("Databases"));

	//second level
	(root->child[0]->child).push_back(addNode("Winston"));
	(root->child[0]->child).push_back(addNode("Ginsberg"));
	(root->child[1]->child).push_back(addNode("McNab"));
	(root->child[1]->child).push_back(addNode("Kabay"));
	(root->child[2]->child).push_back(addNode("Date"));
	(root->child[2]->child).push_back(addNode("Hull"));

	return root;

}





#endif /* FUNCTIONS_H_ */
