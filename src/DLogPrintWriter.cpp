/*
 * DLogPrintWriter.cpp
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#include "DLogPrintWriter.h"

DLogPrintWriter::DLogPrintWriter(Print& print) : _print(print)
{
}

DLogPrintWriter::~DLogPrintWriter()
{
}

void DLogPrintWriter::write(const char* message)
{
    _print.write(message);
#if defined(ESP8266)
    _print.flush();
#endif
}
