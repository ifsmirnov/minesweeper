#include <fstream>
#include <iostream>

#include "header.h"

using namespace std;

int main(int argc, char* argv[])
{
	
	auto field = readField(cin);
// 	writeField(field, cout);
// 	cout << endl;
	
	auto t = determine(field, 3);
    if (!t.first) {
        cout << "UNSOLVABLE" << endl;
        return 0;
    }
// 	cout << (t.first ? "correct" : "incorrect") << endl;
	for (auto i: t.second.first)
        cout << "F " << i.first << " " << i.second << endl;
	for (auto i: t.second.second)
        cout << "C " << i.first << " " << i.second << endl;
	
	return 0;
}
