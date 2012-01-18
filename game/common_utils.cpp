#include <iostream>
#include <vector>

#include "header.h"

void writeField (const std :: vector<std :: vector<int> > &field, std :: ostream& out)
{
	for (auto i: field)
	{
		for (auto j: i)
			if (j > 0)
				out << j;
			else if (j == 0)
				out << ' ';
			else if (j == cMine)
				out << '*';
			else if (j == cUnopened)
				out << '.';
			else
				m_assert(0, Incorrect value in output);
		out << std :: endl;
	}
}
