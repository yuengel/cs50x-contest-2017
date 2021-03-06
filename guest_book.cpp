/**************
* Oscar Yuengel
* 
* Given an array of hotel rooms and their occupancy,
* returns whether a group can be booked in consecutive rooms.
************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cctype>

#include "helpers.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

int main() {

	cout << "This program determines whether a group can book hotel rooms contiguously.\n\n";

	string str;
	unsigned int floors = 0, rooms = 0;
	bool correctInput = false;

	// Prompts user for hotel size and reprompts in case of improper input
	do {
	 	cout << "Enter two integers representing the number of floors\n"
	 		 << "and number of rooms per floor:\n";

		getline(cin, str, '\n');
		bool hasOnlyIntegers = true;
		
		for (auto it = str.begin(), itEnd = str.end(); it != itEnd; ++it) {
			if (!isspace(*it) && !isdigit(*it)) {
				cout << "The input must only contain valid input.\n"; 
				hasOnlyIntegers = false;
				break;
			}
		}

		if (!hasOnlyIntegers)
			continue;

		vector<string> v = my::tokenize(str, " ");

		if (v.size() != 2) {
			cout << "The input must contain exactly two integers.\n";
			continue;
		}

		try {
			floors = my::stoi(v[0]);
			rooms = my::stoi(v[1]);
		}
		catch (std::exception& e) {
			cout << "The input must contain integers less than INT_MAX.\n";
			continue;
		}
		
		if (floors == 0 || rooms == 0)
			cout << "The input must contain non-zero integers.\n";
		else
			correctInput = true; // loop exit

	} while (!correctInput);

	cout << "Enter the hotel's occupancy line by line.\n"
		 << "1 indicates a room is full, and 0 indicates a room is empty.\n";

	bool hotel[floors][rooms];

	// Prompts user for array of hotel rooms and reprompts in case of improper input
	for (unsigned int i = 0; i < floors; ++i) {
		do {
			cout << "Floor " << i + 1 << ": ";
			getline(cin, str, '\n');

			if (str.length() != rooms) {
				cout << "Each line of input must contain precisely " << rooms << " entries.\n";
				correctInput = false;
				continue;
			}

			for (auto it = str.begin(), itEnd = str.end(); it != itEnd; ++it) {
				if (*it != '1' && *it != '0') {
					correctInput = false;
					cout << "The input must only contain 0s and 1s.\n";
					break;
				} 
				
				if (*it == '1') {
					correctInput = true;
					hotel[i][distance(str.begin(), it)] = true;
				}
				else {
					correctInput = true;
					hotel[i][distance(str.begin(), it)] = false;
				}
			}
		} while (!correctInput);
	}

	unsigned int groupSize = 0;

	// Prompts user for group size but assumes positive integer input
	do {
		cout << "Enter the number of rooms the group requires.\n";
		cin >> groupSize;

		if (groupSize == 0)
			cout << "The group size must be non-zero.\n";

	} while (groupSize <= 0);

	if (groupSize > rooms) {
		cout << "0\n";  // indicating no block was found
		return 0;
	}

	// Scan hotel for groupSize contiguous block of rooms
	for (unsigned int i = 0; i < floors; ++i) {
		unsigned int emptyRooms = 0;

		for (unsigned int j = 0; j < rooms; ++j) {
			if (!hotel[i][j]) {
				emptyRooms++;

				if (emptyRooms == groupSize) {
					cout << "1\n";  // indicating a block was found
					return 0;
				}
			}
			else
				emptyRooms = 0;
		}
	}

	cout << "0\n";  // indicating no block was found

	return 0;
}