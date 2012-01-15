#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>

#include "header.h"

void writeField (const t_field &field, std :: ostream& out)
{
	for (auto i: field)
	{
		for (auto j: i)
			if (j >= 0)
				out << j;
			else if (j == cMine)
				out << '*';
			else if (j == cUnopened)
				out << '.';
			else if (j == cUnknown)
				out << '?';
			else
				m_assert(0, Incorrect value in output);
		out << std :: endl;
	}
}

t_field readField (std :: istream& in)
{
	t_field field;
	std :: string s;
	while (in >> s)
	{
		field.push_back(std :: vector<int> (0));
		for (auto i: s)
			if (std :: isdigit(i))
				field.back().push_back(i - '0');
			else if (i == '*')
				field.back().push_back(cMine);
			else if (i == '.')
				field.back().push_back(cUnopened);
			else if (i == '?')
				field.back().push_back(cUnknown);
			else
				m_assert(0, Incorrect character in input);
	}
	return field;
}
