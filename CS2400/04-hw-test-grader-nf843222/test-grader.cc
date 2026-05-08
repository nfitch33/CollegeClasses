/**
 *   @file: test-grader.cc
 * @author: Nathaniel Fitch
 *   @date: 10/23/2023
 *  @brief: Allows the user to put in information using a file to determine what each student got for answers on an exam and what there score was including letter grade.
 * 			Also the program will state what the average was and who of the students got the best score and what the score was.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>  // All the include statements
#include <fstream>
using namespace std;

ifstream inStream;
ofstream outStream;
int x = 0, y = 0, z = 0, A = 0, C = 0; // All integers that were used throughout the whole program, used for counting mostly.
double getScore(string answers, string key); // Gets the percentage
char getLetter(double percent); // Gets the letter grade
void report(string first_name, string last_name, string answers, string key, double percent, char letter, ofstream &outStream); // Function for making output look nice
string all, key, first_name, last_name, answers, info; // All the strings used throughout the whole system.

int main(int argc, char const *argv[])
{
	double bestScore = 0.0;
	int R = 0;
	string characters;
	double calculate = 0.0;
	inStream.open(argv[1]);    // Opens the exam.txt file
	getline(inStream, key);
	outStream.open(argv[2]); // Opens the report.txt file
	while (inStream) // While file is open
	{
		getline(inStream, all);  // grabs each line individually.
		if (all != " ")
		{
			while (x != 1) // Waits until it sees the first space, then up to it becomes first name
			{
				if (all.at(y) != (' '))
				{
					first_name = first_name + all.at(y);
					y++;
				}
				else
				{
					x++;
					y++;
				}
			}
			while (x != 2) // Waits until it sees the second space, then up to it becomes last name
			{
				if (all.at(y) != (' '))
				{
					last_name = last_name + all.at(y);
					y++;
				}
				else
				{
					x++;
					y++;
				}
			}
			while (y != all.length()) // Everything else becomes the students answers
			{
				answers = answers + all.at(y);
				y++;
			}
			while (A != answers.length()) // Converts any spaces for the answers into "-"
			{
				if (answers.at(z) == ' ')
				{
					answers.at(z) = '-';
					z++;
				}
				else
				{
					answers.at(z) = toupper(answers.at(z)); // Changes all the answers to Upper case
					z++;
				}
				A++;
			}
			double percent = getScore(answers, key); // Converts answers into a percentage
			char letter = getLetter(percent); // Converts percentage into a letter grade
			report(first_name, last_name, answers, key, percent, letter, outStream); // Makes the output look nice
			if (percent > bestScore) // This is for labeling who had the best scores.
			{
				bestScore = percent;
				characters = first_name + " " + last_name;
			}
			else if (percent == bestScore) // If there was a tie, they would add the name here
			{
				characters = characters + "\n" + first_name + " " + last_name;
			}
			calculate = calculate + percent; // Adds all the percentages together
			first_name = "";  // Next few lines reset the variables so they can be used again
			last_name = "";
			answers = "";
			x = 0;
			y = 0;
			z = 0;
			A = 0;
			R++;
		}
	}
	calculate = calculate / (R - 1); // Gets average for student answers // R-1 is for the repeated part with Abraham Lincoln test
	char finalLetter = getLetter(calculate); // Grabs one more letter of the average grade
	outStream << "Class Average: " << fixed << setprecision(1) << calculate << "% " << finalLetter << endl; // outputs the class average and who had
	outStream << "-----------------------------------------------------" << endl;                           // the highest using the next couple of lines
	outStream << "Students with the highest grade (" << bestScore << "%):" << endl;
	outStream << characters;
	return 0;
}

double getScore(string answers, string key) // Determines the percentage
{
	double B = 0.0;
	for (int x = 0; x < key.length() - 1; x++)
	{
		if (answers.at(x) == key.at(x)) // Sees if the answer = the key
		{
			B++;
		}
	}
	B = B / (key.length() - 1);
	B = B * 100;
	return B;
}
char getLetter(double percent) // Gets letter for the percentages
{
	char letter;
	if (percent >= 90) // Standard if statements to see what the letter  will be.
	{
		letter = 'A';
	}
	else if (percent < 90 && percent >= 80)
	{
		letter = 'B';
	}
	else if (percent < 80 && percent >= 70)
	{
		letter = 'C';
	}
	else if (percent < 70 && percent >= 60)
	{
		letter = 'D';
	}
	else
	{
		letter = 'F';
	}
	return letter; // Returns the letter
}
// This is the format that outputs into the report. It also makes sure the questions stay 5 questions long the proceed to the new line.
void report(string first_name, string last_name, string answers, string key, double percent, char letter, ofstream &outStream)
{
	outStream << endl;
	outStream << last_name << ", " << first_name << endl;
	outStream << "-----------------------------------------------------" << endl; // Makes the output nice and neat
	outStream << "Answers, correct in parenthesis" << endl;
	int P = 0;
	int num = 0;
	for (int J = 0; J < (answers.length()); J++)
	{
		if (P == num % 5)  // Makes sure there are only 5 questions per line.
		{
			outStream << "\n"
					  << fixed << setw(2) << J + 1 << ":" << " " << answers.at(J) << "(" << key.at(J) << ")   "; // If the code has reached 5 questions in a row
			num++;
		}
		else
		{
			outStream << fixed << setw(2) << J + 1 << ":" << " " << answers.at(J) << "(" << key.at(J) << ")   "; // If code has not reached 5 questions in one row.
			num++;
		}
	}
	outStream << endl;
	outStream << endl;
	outStream << "Score: " << fixed << setprecision(1) << percent << "%" // adds the percentage and letter grade at the end of the person's report
			  << " " << letter << endl;
	outStream << "-----------------------------------------------------" << endl;
	return;
}