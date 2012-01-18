#ifndef HEADER_H
#define HEADER_H

#define m_assert(expr, msg) if ( !(expr) ){std :: cerr << "Error: " << #msg << std :: endl; exit(1);}

#include <iostream>
#include <ctime>

typedef unsigned coord;

const int cMine = -1;
const int cUnopened = -2;

#include "minesweeper.h"
#include "common_utils.h"


#endif
