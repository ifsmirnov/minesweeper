#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <utility>
#include <set>

typedef std :: set<std :: pair<int, int> > t_cells_list;
typedef unsigned t_coord;

std :: pair<bool, std :: pair<t_cells_list, t_cells_list> > determine (t_field, int);
std :: pair<int, int> getFreeNearby(const t_field&, t_coord, t_coord);

#endif
