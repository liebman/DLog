/*
 * DLogLevelMap.cpp
 *
 *  Created on: Mar 14, 2018
 *      Author: chris.l
 */

#include "DLogWriterList.h"
#include <stdlib.h>

#define DLOG_WRITER_INCREMENT 2

DLogWriterList::DLogWriterList() : _writers_count(0), _writers_max(0), _writers(nullptr)
{
}

DLogWriterList::~DLogWriterList()
{
    if (_writers != nullptr)
    {
        for(size_t i = 0; i < _writers_count; ++i)
        {
            delete _writers[i];
        }
        free(_writers);
    }
}

void DLogWriterList::addWriter(DLogWriter* writer)
{
    // insure array is big enough.
    if (_writers_count == _writers_max)
    {
        size_t size = _writers_max + DLOG_WRITER_INCREMENT;
        DLogWriter** new_entries = (DLogWriter**)realloc((void*)_writers, size * sizeof(DLogWriter*));
        if (new_entries == nullptr)
        {
            writer->write("Failed to allocate memory for writer!");
            return;
        }

        _writers = new_entries;
        _writers_max = size;
    }

    _writers[_writers_count] = writer;
    ++_writers_count;
}

void DLogWriterList::write(const char* message)
{
    for(size_t i = 0; i < _writers_count ; ++i)
    {
        _writers[i]->write(message);
    }
}

bool DLogWriterList::empty()
{
    return _writers_count == 0;
}
