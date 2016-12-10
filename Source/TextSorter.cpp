// Text Sorter v.0.3.0
// M. H. Beals (2016) Text Sorter v.0.3.0 [Software]
// Available at https://github.com/mhbeals/Textsorter

// MIT License

// Copyright(c) 2016 M.H.Beals

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "stdafx.h"
#include <direct.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int countery = 1800; // set start year variable
int countere = 1900; // set end year variable
int counter = 1; // set month variable

void createdir() // create directories
{
	int counteryt = countery; // set year variable for loop
	int countert = counter; // set month variable for loop

	while (counteryt <= countere) // while year is less than or equal to end year
	{
		ostringstream oss;
		oss << counteryt; // set directory name
		_mkdir(oss.str().c_str()); // make year directory
		int countert = counter; // reset month counter
		while (countert <= 9) // while month is less than 10 (October)
		{
			ostringstream oss;
			oss << counteryt << "/0" << countert; // set directory name
			_mkdir(oss.str().c_str()); // make month directory
			countert++; // increase month counter
		}
		while (countert <= 12) // while month is after 9 (September)
		{
			ostringstream oss;
			oss << counteryt << "/" << countert; // set directory name
			_mkdir(oss.str().c_str()); // make month directory
			countert++; // increase month counter
		}
		counteryt++; // increase year counter
	}
}

void movefiles()
{
	ofstream myfile;
	myfile.open("movefiles.bat", std::ofstream::out); // overwrite or create batch file

	int counteryt = countery; // reset year counter for loop

	while (counteryt <= countere) // while year is less than or equal to end year
	{
		int countert = counter; // reset month counter
		while (countert <= 9) // while month is before October
		{
			ofstream myfile;
			myfile.open("movefiles.bat", ios::out | ios::app); // open batch file and append next line
			myfile << "move " << counteryt << "\\" << counteryt << ".0" << countert << "* " << counteryt << "\\0" << countert << "\\" << "\n"; // create entry for moving text files
			countert++; // increase month counter
		}
		while (countert <= 12) // while month is after September
		{
			ofstream myfile; 
			myfile.open("movefiles.bat", ios::out | ios::app); // open batch file and append next line
			myfile << "move " << counteryt << "\\" << counteryt << "." << countert << "* " << counteryt << "\\" << countert << "\\" << "\n"; // create entry for moving text files
			countert++; // increase month counter
		}
		counteryt++; // increase year counter
	}
	system("movefiles"); // run batch file
}

int main()
{
	
	cout << "What is your starting year? ";
	cin >> countery; //set starting year
	cout << "What is your ending year? ";
	cin >> countere; //set ending year

	createdir(); // create directories
	movefiles(); // move files
	system("pause"); // wait for user
	system("del movefiles.bat"); // delete temporary batch file
	return 0;
}