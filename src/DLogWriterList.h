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

class DLogWriterList : public DLogWriter
{
public:
    DLogWriterList();
    virtual ~DLogWriterList();

    virtual void write(const char* message);
    virtual inline bool isList() {return true;}
    virtual void addWriter(DLogWriter* writer);

private:
    size_t       _writers_count; // count of items
    size_t       _writers_max;   // max items that fit in current size
    DLogWriter** _writers;
};

#endif /* DLOGWRITERLIST_H_ */
