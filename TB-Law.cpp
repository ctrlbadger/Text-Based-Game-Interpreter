#include <iostream>
#include <string>
#include <fstream>

struct Text {
	std::string TextRead = "";
	int NameText = 0;
	int  DirAllocator[7] = { 0,0,0,0,0,0,0 };
	std::string DirText[7] = { "","","","","","","" };

};


bool isNum(char String) {
	if (String == '0' || String == '1' || String == '2' || String == '3' || String == '4' || String == '5' || String == '6' || String == '7' || String == '8' || String == '9') {
		return true;
	}
	else {
		return false;
	}
}
/*
Text ClearText(Text ZeroText) {
ZeroText.NameText = 0;
ZeroText.TextRead = "";
for (unsigned int Count = 0; Count < 7; Count++) {
ZeroText.DirAllocator[Count] = 0;
ZeroText.DirText[Count] = "";
}
return ZeroText;
}
*/
Text FindDialog(int Directory) {
	// Used to read in files
	std::ifstream FileStream;
	// Stores the text read in from the file
	Text FindText;
	// Standard string used for storing a line from a file
	std::string FileString = "";
	// Open the file
	// Note: Store LawText.txt in the same folder as the executable
	FileStream.open("LawText.txt");
	// Used to check if the dialog we need has been found
	bool FoundText = false;
	// Used in for loops and checking that the program doesn't get errors, just counting really
	unsigned int Count = 0;

	// Checking if the file opened or not
	if (!FileStream.is_open()) {
		// Gives error message and tries to continue after enter is pressed
		std::cerr << "We cant find LawText.txt" << std::endl << ">>> Press Enter To Continue<<<";
		std::cin.ignore();
	}

	// This first do loop finds the piece of text by using the Directory argument 
	// to pinpoint specifically where in the file the text is
	do {
		// Read in a line of text
		std::getline(FileStream, FileString);
		// Checks that the line holds a 10 digit number and that it is not an option argument by checking there is no colon
		if (isNum(FileString[0]) == true && isNum(FileString[1]) == true && FileString[2] != ':') {
			// Recreates the string as an int
			// the (FileString[int] - '0') notation casts a char into its respective number changing '5' into 5
			FindText.NameText = (10 * (FileString[0] - '0')) + (FileString[1] - '0');
			// Checks if the Number we are looking for is equal to the number in file
			if (FindText.NameText == Directory) {
				FoundText = true;
			}

		}
		// Checks that the line holds a single digit number and is not an option
		else if (isNum(FileString[0]) == true && FileString[1] != ':') {
			// Changes a char number to an int
			FindText.NameText = (FileString[0] - '0');
			// Checks if the Number we are looking for is equal to the number in file
			if (FindText.NameText == Directory) {
				FoundText = true;
			}
		}
		
	} while (FoundText != true); // Exits if we have found the right number

	// Read in the first line of text
	std::getline(FileStream, FileString);
	// This second do loop reads in the text question
	do {
		// Adds a newline after every text line
		FindText.TextRead = FindText.TextRead + "\n" + FileString;
		// Read in line
		std::getline(FileStream, FileString);
	} while (FileString != "#"); // Exits once there is no more text

	// Read in the first option
	std::getline(FileStream, FileString);
	// Used in the array
	Count = 0;
	// Third do loop reads in the options and where they go and stores them in arrays
	do {
		// Checks if the line has a directory with a single number
		if (FileString[1] == ':') {
			// Uses the same casting system to cast char into int
			FindText.DirAllocator[Count] = (FileString[0] - '0');
			// Deletes the first two characters in the string to store as an option 
			FileString.erase(0, 2);
			FindText.DirText[Count] = FileString;
		}
		else {
			// Adds a two digit number as the director
			FindText.DirAllocator[Count] = (10 * (FileString[0] - '0')) + (FileString[1] - '0');
			// Deletes the first three characters in the string to store as ano option
			FileString.erase(0, 3);
			// Count is used as the allocator for the array
			FindText.DirText[Count] = FileString;
		}
		// Increment count to add another option
		Count++;
		// Read one line of the file
		std::getline(FileStream, FileString);
	} while (FileString != "~");
	// Close the file
	FileStream.close();
	// return the structure
	return FindText;
}


int main() {
	// Note: You should include LawText.txt in the same directory as the executable plus the required dll file
	Text MainText;
	// Gives back the first text and options to start the loop
	MainText = FindDialog(0);
	// Count used in for loop
	unsigned int Count = 0;
	// Answer used for storing input
	unsigned int Answer = 0;
	// Do loop outputs the text followed by the options then the user chooses an option which goes to another text
	do {
		// Show the text 
		// Note: Added two lines for formatting
		std::cout << MainText.TextRead << std::endl << std::endl;
		// Show the options
		for (Count = 0; MainText.DirText[Count] != ""; Count++) {
			// Note: Added one to count for ease of use
			std::cout << (Count + 1) << ": " << MainText.DirText[Count] << std::endl;
		}
		// Note: Newline for formatting
		std::cout << "\n: ";
		// Output the text
		std::cin >> Answer;
		// Start the whole process again using the entered answer
		MainText = FindDialog(MainText.DirAllocator[Answer - 1]);
	} while (true); // (Ctrl + Z) To break line
	return 1;
}
