#include <fstream>
#include <iostream>

#include "header.h"

using namespace std;

int main(int argc, char* argv[])
{
	std :: fstream in ("input.txt", std :: ios_base :: in);
	
	auto field = readField(in);
	writeField(field);
	
	auto t = determine(field, 3);
	cout << t.first << endl;
	cout << "mines: ";
	for (auto i: t.second.first)
		cout << i.first << " " << i.second << ", ";
	cout << endl;
	cout << "empty: ";
	for (auto i: t.second.second)
		cout << i.first << " " << i.second << ", ";
	cout << endl;
	
	return 0;
}
