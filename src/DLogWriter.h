/*
 * DLogWriter.h
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#ifndef DLOGWRITER_H_
#define DLOGWRITER_H_

#include "Arduino.h"

class DLogWriter
{
public:
    DLogWriter();
    virtual ~DLogWriter();

    virtual void write(const char* message) = 0;
    virtual inline bool isList() {return false;}
    virtual void addWriter(DLogWriter* writer) {(void)writer;} // only called when isList() is true!
};

#endif /* DLOGWRITER_H_ */
