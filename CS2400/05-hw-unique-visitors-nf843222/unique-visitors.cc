/**
 *   @file: unique-visitors.cc
 * @author: Nathaniel Fitch
 *   @date: 11/2/23
 *  @brief: Program will read file and store unique ip addresses into an array. It will then output information to another
 * 			file. The information includes, "Unique Ip-Addresses", "Total visitors count", and "Unique Visitor count"
 */

#include <iostream>
#include <fstream>
#include <iomanip> // All include statements
#include <cstdlib>
#include <vector>
using namespace std;

ifstream inStream; // sets inStream ready for use
ofstream outStream; // sets outStream ready for use
void checkInVector(vector<string> &IPAddresses, int currentX); // function for seeing if IP Address is already in vector
void gatherCURRENTIP(string TotalIP, vector<string>IPAddresses, string websiteName, string seperator); // Gets the vector ready using all the information to output to a file.

int main(int argc, char const *argv[]) {
	string websiteName;
	string seperator;
	string TotalIP;
	vector <string> IPAddresses;	// Variables lines 22-25
	inStream.open(argv[1]);			// Opens input file
	outStream.open(argv[2]);		// Opens output file
	for(int x = 0; x < 4; x++){  	// Starts the function to get vector ready, does 4 times... one for each of the websites.
		gatherCURRENTIP(TotalIP, IPAddresses, websiteName, seperator);
	}
}
void checkInVector(vector<string> &IPAddresses, int currentX){	// For seeing if IP Address is already in vector
	int x = currentX;
	for (size_t y = x + 1; y < IPAddresses.size(); y++){
	if (IPAddresses.at(x) == IPAddresses.at(y)){
		IPAddresses.erase(IPAddresses.begin() + y);		// It grabs an IP address then checks the remainging ones. If it finds it again, it will delete it.
		y--;
	}
	}
}
void gatherCURRENTIP(string TotalIP, vector<string>IPAddresses, string websiteName, string seperator){ // Function for setting up Vector and sending info to output
	string current = "";
	int visitCounter = 0;
	getline(inStream, websiteName);
	getline(inStream, TotalIP);			// All getlines for the website name, ip addresses, and the seperators.
	getline(inStream, seperator);
	IPAddresses.push_back(websiteName);		// Puts Name of website into the first slot of the Vector
	for(size_t x = 0; x < TotalIP.length(); x++){	// Repeats for the entire IP addresses length
		if (TotalIP.at(x) != ' '){
			current = current + TotalIP.at(x);	// gets the IP address ready for putting into vector
		}
		else {
			if (TotalIP.at(x) == ' ' || TotalIP.at(x) == '\n'){
				IPAddresses.push_back(current); // Puts into vector
				visitCounter++;  
				current = "";
			}
		}
	}
	if(TotalIP.at(TotalIP.length()-1) <= '9' || TotalIP.at(TotalIP.length()-1) >= '0'){	// This is for the last IP Address, because it doesn't end in a new line or space
			IPAddresses.push_back(current);
		}
	for (size_t z = 0; z < IPAddresses.size(); z++){	// Input file sometimes had two spaces instead of one, so this gets rid of any spots that are empty.
		if (IPAddresses.at(z) == ""){
		IPAddresses.erase(IPAddresses.begin() + z);
		visitCounter--;
		}
	}
	for (size_t x = 1; x < IPAddresses.size(); x++){	// This will start the checkInvector function, to see if there are repeats.
		int currentX = x;
		checkInVector(IPAddresses, currentX);
	}
	visitCounter++;			// Adds +1 to the visiter count for the last IP Addresses in list that couldn't be counted.
	websiteName = "";
	current = "";			// Lines 74-76, resets variables used
	TotalIP = "";
	outStream << IPAddresses.at(0) << " | Number of Visitors: " << visitCounter << " | Unique Visitors: " << IPAddresses.size() - 1 << endl;	// Outputs basic info
	for(size_t y = 1; y < IPAddresses.size(); y++){
		outStream << "     " << IPAddresses.at(y) << endl;			// outputs all unique IP Addresses on seperate lines
	}
	outStream << endl;	// Adds an additional space so its easier to read.
}
 /// main