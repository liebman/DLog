/*
 * DLogLevelMap.h
 *
 *  Created on: Mar 14, 2018
 *      Author: chris.l
 */

#ifndef DLOGLEVELMAP_H_
#define DLOGLEVELMAP_H_

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

    DLogLevel getLevel(const char* tag, DLogLevel default_level);
    void setLevel(const char* tag, DLogLevel level);

private:
    size_t _level_entry_count; // count of items
    size_t _level_entry_max;   // max items that fit in current size
    DLogLevelEntry* _level_entries;

    DLogLevelEntry* find(const char* tag);
    void insert(const char* tag, DLogLevel level);
};

#endif /* DLOGLEVELMAP_H_ */
