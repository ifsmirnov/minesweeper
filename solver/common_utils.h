#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include <iostream>

#include "header.h"

void writeField (const t_field&, std :: ostream& = std :: cout);
t_field readField (std :: istream& = std :: cin);

#endif
