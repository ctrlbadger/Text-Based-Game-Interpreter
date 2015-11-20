#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
	std::ifstream FileStream;
	Text FindText;
	std::string FileString = "";
	FileStream.open("LawText.txt");
	bool FoundText = false;
	unsigned int Count = 0;


	if (!FileStream.is_open()) {
		std::cerr << "ERROR ERROR, DATA CORRUPTION\n DOGE DOGE DOGE DOGGGE DOGGE\n010101011001100010100101010101010010001001" << std::endl
			<< "We cant find LawText.txt" << std::endl << ">>> Press Enter To Continue<<<";
		std::cin.ignore();
	}


	do {
		std::getline(FileStream, FileString);
		if (isNum(FileString[0]) == true && isNum(FileString[1]) == true && FileString[2] != ':') {
			FindText.NameText = (10 * (FileString[0] - '0')) + (FileString[1] - '0');
			if (FindText.NameText == Directory) {
				FoundText = true;
			}

		}
		else if (isNum(FileString[0]) == true && FileString[1] != ':') {
			FindText.NameText = (FileString[0] - '0');
			if (FindText.NameText == Directory) {
				FoundText = true;
			}
		}
	} while (FoundText != true);


	std::getline(FileStream, FileString);
	do {
		FindText.TextRead = FindText.TextRead + "\n" + FileString;
		std::getline(FileStream, FileString);
	} while (FileString != "#");
	Count = 0;
	std::getline(FileStream, FileString);
	do {
		if (FileString[1] == ':') {
			FindText.DirAllocator[Count] = (FileString[0] - '0');
			FileString.erase(0, 2);
			FindText.DirText[Count] = FileString;
		}
		else {
			FindText.DirAllocator[Count] = (10 * (FileString[0] - '0')) + (FileString[1] - '0');
			FileString.erase(0, 3);
			FindText.DirText[Count] = FileString;
		}
		Count++;
		std::getline(FileStream, FileString);
	} while (FileString != "~");
	FileStream.close();
	return FindText;
}


int main() {
	// Note: You should include LawText.txt in the same directory as the executable plus the required dll file
	Text MainText;
	MainText = FindDialog(0);
	unsigned int Count = 0;
	unsigned int Answer = 0;
	do {

		std::cout << MainText.TextRead << std::endl << std::endl;
		for (Count = 0; MainText.DirText[Count] != ""; Count++) {
			std::cout << (Count + 1) << ": " << MainText.DirText[Count] << std::endl;
		}
		std::cout << "\n: ";
		std::cin >> Answer;
		MainText = FindDialog(MainText.DirAllocator[Answer - 1]);
	} while (true);
	return 1;
}
