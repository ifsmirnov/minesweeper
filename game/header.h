#ifndef HEADER_H
#define HEADER_H

#define m_assert(expr, msg) if ( !(expr) ){std :: cerr << "Error: " << #msg << std :: endl; exit(1);}

#include <iostream>
#include <ctime>
#include <vector>

typedef unsigned coord;

const int cMine = -1;
const int cUnopened = -2;

const int cContinue = 0;
const int cWin = 1;
const int cLose = 2;

typedef std :: vector<std :: vector <char> > t_field;

#include "minesweeper.h"
#include "common_utils.h"


#endif
