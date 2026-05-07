/**
 *   @file: word-count.cc
 * @author: Nathaniel Fitch
 *   @date: 09/19/2023
 *  @brief: Allows for input to be read, it will tell you the amount of words and sentenced you typed and also average words per sentence, if there are sentences.
 *           The software ends when it sees "@@@".
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main(){

cout << "Type a Paragraph: " << endl; // Tells user to start typing

double sentence_count = 0; // Declaring Variables
double word_count = 0;
string grab; // Variable for grabbing words, sentence enders (! ? .), and spaces (' ')
cin >> grab; // checks to see if first word is @@@

while (grab != "@@@") { // If first word is @@@ ends immediatley
    cin >> grab; // Grabs word
    char character = grab.at(grab.length() - 1); // 
    if (grab == "@@@") // will repeat until this is true
    {
        word_count = word_count + 1; // Final word happens before this line of code, so add + 1 for current word.
        if (sentence_count == 0) {
            cout << "Word Count: " << word_count << endl; // If sentences = 0 output
            cout << "Sentence Count: " << sentence_count << endl; // If sentences = 0 output
            cout << "You did not enter any sentences" << endl; // If sentences = 0
            exit(0);
        }
        else{
            double average_count = word_count / sentence_count; // Calculates Average words in a sentence
            cout << "Word Count: " << word_count << endl; // Final Output
            cout << "Sentence Count: " << sentence_count << endl; // Final Output
            cout << "Average Words per Sentence: " << fixed << setprecision(1) << average_count << endl;
            exit(0);
        }
    }
    
    if(character == '!' || character == '?' || character == '.') { // Checks for sentence enders
        sentence_count = sentence_count + 1; // adds sentence count
        word_count = word_count + 1; // adds the last word of the sentence
    }
    else {
        word_count = word_count + 1; // If its not a sentence ender
}
}
cout << "Word Count: " << word_count << endl; // Output for if first word is @@@
cout << "Sentence Count: " << sentence_count << endl; // Output for if first word is @@@
cout << "You did not input any text" << endl;
}