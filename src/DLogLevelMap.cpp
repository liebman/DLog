/*
 * DLogLevelMap.cpp
 *
 *  Created on: Mar 14, 2018
 *      Author: chris.l
 */

#include "DLogLevelMap.h"
#include <string.h>
#include <stdlib.h>

#define DLOG_LEVEL_ENTRY_INCREMENT 5

DLogLevelMap::DLogLevelMap() : _level_entry_count(0), _level_entry_max(0), _level_entries(nullptr)
{
}

DLogLevelMap::~DLogLevelMap()
{
}

DLogLevel DLogLevelMap::getLevel(const char* tag, DLogLevel default_level)
{
    DLogLevelEntry* entry = find(tag);
    if (entry == nullptr)
    {
        return default_level;
    }

    return entry->level;
}

void DLogLevelMap::setLevel(const char* tag, DLogLevel level)
{
    DLogLevelEntry* entry = find(tag);
    if (entry != nullptr)
    {
        entry->level = level;
        return;
    }

    insert(tag, level);
}

DLogLevelEntry* DLogLevelMap::find(const char* tag)
{
    for(int i = 0; i < _level_entry_count; ++i)
    {
        if (strcmp(tag, _level_entries[i].tag) == 0)
        {
            return &(_level_entries[i]);
        }
    }
    return nullptr;
}

void DLogLevelMap::insert(const char* tag, DLogLevel level)
{
    // insure array is big enough.
    if (_level_entry_count == _level_entry_max)
    {
        size_t size = _level_entry_max + DLOG_LEVEL_ENTRY_INCREMENT;
        DLogLevelEntry* new_entries = (DLogLevelEntry*)realloc((void*)_level_entries, size * sizeof(DLogLevelEntry));
        if (new_entries == nullptr)
        {
            //
            // we silently ignore level specification on allocation failure
            // TODO: do something other than silently fail
            //
            return;
        }
        _level_entries = new_entries;
        _level_entry_max = size;
    }
    _level_entries[_level_entry_count].tag = strdup(tag);
    _level_entries[_level_entry_count].level = level;
    ++_level_entry_count;
}
