#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Text {
	std::string TextRead = "";
	int NameText = 0;
	std::vector<int>  DirAllocator = { 0, 0, 0, 0, 0 };
	std::vector<std::string> DirText = { "", "", "", "", "" };

};