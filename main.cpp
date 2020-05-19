/*
 * File: main.cpp
 * Description: This program will create a decision tree for an animal guessing game.
 * Author: Ian Sanchez Munoz
 * Email: ians2913@student.vvc.edu
 */
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include "binary_tree.h"

const int BUFFER_IGNORE = 10000; // An arbitrarily large number used to clear the input buffer when it needs to be reset.

/* Removes the leading spaces from a string
 * @param s The string to fix
 */
void remove_leading_spaces(std::string& s)
{
	int count = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{
			count++;
		}
		else
		{
			break;
		}
	}
	if (count > 0)
	{
		s.erase(0, count);
	}
}

/* Creates a binary tree from data in a file
 * @param in The file in question
 * @return The completed binary tree
 */
Binary_tree read(std::ifstream& in)
{
	std::string data;
	int level;
	in >> level;
	std::getline(in, data);
	remove_leading_spaces(data);
	if (level == -1)
	{
		return Binary_tree();
	}
	Binary_tree left = read(in);
	Binary_tree right = read(in);
	return Binary_tree(data, left, right);
}

/* Writes out a binary tree to a file
 * @param out The file to write to
 * @param tree The tree to write out
 * @param level The current level on the binary tree
 */
void write(std::ofstream& out, const Binary_tree& tree, int level)
{
	if (tree.empty())
	{
		out << "-1" << '\n';
		return;
	}
	out << level << ' ' << tree.data() << '\n';
	write(out, tree.left(), level + 1);
	write(out, tree.right(), level + 1);
}

/* Determines whether to use a definite or indefinite article
 * @param entry The proceeding word
 * @return The appropriate article form
 */
std::string article(const std::string& entry)
{
	std::string article = "a";
	if (std::string("aeiou").find(entry[0]) != std::string::npos)
	{
		article = "an";
	}
	return article;
}

/* Prompts the user for a yes / no response
 * @param prompt The text that accompanies the prompt
 * @return The user's response
 */
char get_response(std::string prompt)
{
	char response;
	while (true)
	{
		std::cout << prompt;
		std::cin >> response;
		std::cin.clear();
		std::cin.ignore(BUFFER_IGNORE, '\n');
		response = std::tolower(response);
		if (response == 'y' || response == 'n')
		{
			break;
		}
		std::cout << "Not a valid response." << std::endl;
	}
	return response;
}

/* Prompts the user for any response 
 * @return The user's response
 */
std::string arbitrary_response()
{
	std::string response;
	std::getline(std::cin, response);
	return response;
}

int main(int argc,char **argv)
{
	// Grab the file
	std::string filename;
	std::ifstream datafile; 
	if (argc > 1)
	{
		filename = argv[1];
		datafile.open(filename);
		if (!datafile.is_open())
		{
			std::cout << "File not found." << std::endl;
			return 0;
		}
	}
	else
	{
		std::cout << "Please enter the name of the decision tree file." << std::endl;
		return 0;
	}

	// Read from the file
	Binary_tree root = read(datafile);
	datafile.close();

	// Initiate the decision game
	Binary_tree question_tree = root;
	std::string steps = "";
	bool done = false;
	while (!done)
	{
		Binary_tree left = question_tree.left();
		Binary_tree right = question_tree.right();
		if (left.empty() && right.empty())
		{
			// Reached a leaf node
			char response = get_response("Is it " + article(question_tree.data()) + " " +  question_tree.data() + "? (Y/N): ");
			if (response == 'y')
			{
				std::cout << "I guessed it!" << std::endl;
			}
			else
			{
				// Learn the new animal for future attempts
				std::cout << "I give up! What is it? ";
				std::string animal = arbitrary_response();
				std::cout << "Please give me a question that is true for " + article(animal) + " " + animal + " and false for " + article(question_tree.data()) + " " + question_tree.data() + "." << std::endl;
				std::string question = arbitrary_response();

				// Save the new question for future dialogue
				root.set(steps, question, Binary_tree(animal), Binary_tree(question_tree.data()));
			}
			response = get_response("May I try again? (Y/N): ");
			if (response == 'y')
			{
				question_tree = root;
				steps = "";
			}
			else
			{
				done = true;
			}
		}
		else
		{
			// Continue asking questions
			char response = get_response(question_tree.data() + " (Y/N): ");
			if (response == 'y')
			{
				question_tree = left;
				steps += "1";
			}
			else
			{
				question_tree = right;
				steps += "0";
			}
		}
	}

	// Write out the decision tree to the same file that it was read from
	std::ofstream outputfile(filename);
	write(outputfile, root, 0);
	outputfile.close();
	return 0;
}
