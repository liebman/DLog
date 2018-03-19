/*
 * DLogLevelMap.cpp
 *
 *  Created on: Mar 14, 2018
 *      Author: chris.l
 */

#include "DLogLevelMap.h"
#include "Arduino.h"
#include <string.h>
#include <stdlib.h>

#define DLOG_LEVEL_ENTRY_INCREMENT 5

DLogLevelMap::DLogLevelMap() : _level_entry_count(0), _level_entry_max(0), _level_entries(nullptr)
{
}

DLogLevelMap::~DLogLevelMap()
{
}

template<class T>
DLogLevel DLogLevelMap::getLevel(T tag, DLogLevel default_level)
{
    DLogLevelEntry* entry = find(tag);
    if (entry == nullptr)
    {
        return default_level;
    }

    return entry->level;
}

template DLogLevel DLogLevelMap::getLevel<const char*>(const char* tag, DLogLevel default_level);
template DLogLevel DLogLevelMap::getLevel<const __FlashStringHelper*>(const __FlashStringHelper* tag, DLogLevel default_level);

template<class T>
void DLogLevelMap::setLevel(T tag, DLogLevel level)
{
    DLogLevelEntry* entry = find(tag);
    if (entry != nullptr)
    {
        entry->level = level;
        return;
    }

    insert(tag, level);
}

template void DLogLevelMap::setLevel<const char*>(const char* tag, DLogLevel level);
template void DLogLevelMap::setLevel<const __FlashStringHelper*>(const __FlashStringHelper* tag, DLogLevel level);

template<class T>
DLogLevelEntry* DLogLevelMap::find(T tag)
{
    for(size_t i = 0; i < _level_entry_count; ++i)
    {
        if (cmp(_level_entries[i].tag, tag) == 0)
        {
            return &(_level_entries[i]);
        }
    }
    return nullptr;
}

template<class T>
void DLogLevelMap::insert(T tag, DLogLevel level)
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
    _level_entries[_level_entry_count].tag = dup(tag);
    _level_entries[_level_entry_count].level = level;
    ++_level_entry_count;
}

char* DLogLevelMap::dup(const char* str)
{
    return strdup(str);
}

char* DLogLevelMap::dup(const __FlashStringHelper* str)
{
    int size = strlen_P((PGM_P)str);
    char* snew = (char*)malloc(size+1);
    if (snew != nullptr)
    {
        strcpy_P(snew, (PGM_P)str);
    }

    return snew;
}

int DLogLevelMap::cmp(const char* a, const char* b)
{
    return strcmp(a, b);
}

int DLogLevelMap::cmp(const char* a, const __FlashStringHelper* b)
{
    return strcmp_P(a, (PGM_P)b);
}
