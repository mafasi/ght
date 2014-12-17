#ifndef RTABLE_H
#define RTABLE_H

#include "precomp.h"

class RTableEntry
{
    double r;
    double beta;
};

typedef std::vector<RTableEntry> RTableEntryList;
typedef std::map<double, RTableEntryList> RTable;

class RTableWrapper
{

public:
    RTableWrapper();
    ~RTableWrapper();

    void add(double index, RTableEntry entry);

    RTableEntryList lookup(double index);
    RTableEntry lookup(double index, RTableEntry entry);

    RTable* _table;
};

#endif // RTABLE_H
