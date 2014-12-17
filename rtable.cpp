#include "rtable.h"

RTableWrapper::RTableWrapper() :
    _table(new RTable)
{
}

RTableWrapper::~RTableWrapper()
{
    delete _table;
}
