#include <fstream>
#include <iostream>

#include "header.h"

using namespace std;

int main(int argc, char* argv[])
{
	std :: fstream in ("input.txt", std :: ios_base :: in);
	std :: fstream cout ("output.txt", std :: ios_base :: out);
	
	auto field = readField(in);
	writeField(field, cout);
	cout << endl;
	
	auto t = determine(field, 2);
	cout << (t.first ? "correct" : "incorrect") << endl;
	cout << "mines: ";
	for (auto i: t.second.first)
		cout << i.first + 1 << " " << i.second + 1 << ", ";
	cout << endl;
	cout << "empty: ";
	for (auto i: t.second.second)
		cout << i.first + 1 << " " << i.second + 1 << ", ";
	cout << endl;
	
	return 0;
}
