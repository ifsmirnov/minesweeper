#ifndef HEADER_H
#define HEADER_H

#define m_assert(expr, msg) if (! (expr) ) {std :: cerr << #msg << std :: endl << __FILE__ << ", line #" << __LINE__ << std :: endl; exit(1);}

#include "const.h"
#include "common_utils.h"
#include "backtrack.h"


#endif
