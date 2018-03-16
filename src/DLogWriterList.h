/*
 * DLogLevelMap.h
 *
 *  Created on: Mar 14, 2018
 *      Author: chris.l
 */

#ifndef DLOGWRITERLIST_H_
#define DLOGWRITERLIST_H_

#include "DLogWriter.h"
#include <sys/types.h>

class DLogWriterList
{
public:
    DLogWriterList();
    virtual ~DLogWriterList();

    void addWriter(DLogWriter* writer);
    void write(const char* message);
    bool empty();

private:
    size_t       _writers_count; // count of items
    size_t       _writers_max;   // max items that fit in current size
    DLogWriter** _writers;
};

#endif /* DLOGWRITERLIST_H_ */
