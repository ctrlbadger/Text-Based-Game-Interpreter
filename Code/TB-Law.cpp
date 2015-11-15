#include "TB-Law.h"



int main() {
	// Note: You should include LawText.txt in the same directory as the executable
	std::string FileName = "LawText.txt";
	// This is where we hold all text that the game plays
	std::vector<Text> VecText;
	// Count is used for making sure I dont get errors
	unsigned int Count = 0;
	// This is used for all operations with the file
	std::fstream File;
	// Used to store the Strings as we read them into the file
	std::string StrLine = "";
	// "Option" is for entering the directorys of text
	std::string Mode = "Text";
	//
	bool OptionMode = true;
	File.open(FileName);
	if (!File.is_open()) {
		
		std::cerr << "ERROR ERROR, DATA CORRUPTION\n DOGE DOGE DOGE DOGGGE DOGGE\n010101011001100010100101010101010010001001" << std::endl;
		std::cin.ignore();
		return -1;
	}
	char DirectoryNum;
	while (std::getline(File, StrLine)) {
		if (StrLine == "0" || StrLine == "1" || StrLine == "2" || StrLine == "3" || StrLine == "4" || StrLine == "5" || StrLine == "6" || StrLine == "7" || StrLine == "8" || StrLine == "9" ) {
			VecText.push_back(Text());
			VecText[Count].NameText = atoi(StrLine.c_str());
			Mode = "Text";
		}
		else if (Mode == "Text" && StrLine != "#") {
			VecText[Count].TextRead += StrLine;
		}
		else if (Mode == "Option") {
			OptionMode = true;
			int OptionCount = 0;
			do {
				
				if (StrLine == "~") {
					Count++;
					OptionMode = false;
				}
				else {
					DirectoryNum = StrLine[0];
					StrLine.erase(0, 1);
					VecText[Count].DirAllocator[OptionCount] = (DirectoryNum - '0');
					VecText[Count].DirText[OptionCount] = StrLine;

					std::getline(File, StrLine);
					OptionCount++;
				}
			} while (OptionMode);
			Mode = "Text";
		}
		else if (Mode == "Text" && StrLine == "#") {
			Mode = "Option";
		}
	}
	// End Of Game
	Count = 0;
	unsigned int DirCount = 0;
	int Answer;
	std::vector<int>  DirAllocatorCount(5);
	do {
		// This shows the text in the file
		std::cout << VecText[Count].TextRead << std::endl;
		for (DirCount = 0; VecText[Count].DirAllocator.size() > DirCount  && VecText[Count].DirAllocator[DirCount] != 0; DirCount++) {
			std::cout << (DirCount + 1) << ": " << VecText[Count].DirText[DirCount] << std::endl;
			DirAllocatorCount[DirCount] = VecText[Count].DirAllocator[DirCount];
		}
		std::cout << ": ";
		std::cin >> Answer;
		Count = Answer -= 1;
	} while (true);
}