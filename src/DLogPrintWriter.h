/*
 * DLogPrintWriter.h
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#ifndef DLOGPRINTWRITER_H_
#define DLOGPRINTWRITER_H_

#include "DLogWriter.h"

class DLogPrintWriter: public DLogWriter
{
public:
    DLogPrintWriter(Print& print);
    virtual ~DLogPrintWriter();

    virtual void write(const char* message);

private:
    Print& _print;
};

#endif /* DLOGPRINTWRITER_H_ */
