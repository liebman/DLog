/*
 * DLogLevelMap.h
 *
 *  Created on: Mar 14, 2018
 *      Author: chris.l
 */

#ifndef DLOGLEVELMAP_H_
#define DLOGLEVELMAP_H_
#include "WString.h"
#include "DLogLevel.h"
#include <stddef.h>

typedef struct dlog_level_entry
{
    char*     tag;
    DLogLevel level;
} DLogLevelEntry;

class DLogLevelMap
{
public:
    DLogLevelMap();
    virtual ~DLogLevelMap();

    template<class T>DLogLevel getLevel(T tag, DLogLevel default_level);
    template<class T>void setLevel(T tag, DLogLevel level);

private:
    size_t _level_entry_count; // count of items
    size_t _level_entry_max;   // max items that fit in current size
    DLogLevelEntry* _level_entries;

    template<class T>DLogLevelEntry* find(T tag);
    template<class T>void insert(T tag, DLogLevel level);
    int cmp(const char* a, const char* b);
    int cmp(const char* a, const __FlashStringHelper* b);

    char* dup(const char* src);
    char* dup(const __FlashStringHelper* src);
};

#endif /* DLOGLEVELMAP_H_ */
