/*
 * DLogBuffered.h
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#ifndef DLOGBUFFER_H_
#define DLOGBUFFER_H_

#include "Arduino.h"

class DLogBuffer
{
public:
    DLogBuffer();
    virtual ~DLogBuffer();

    void reset();
    const char* getBuffer();

    template<class F>void printf(F fmt, ...);
    template<class F>void vprintf(F fmt, va_list ap);

private:
    char* _buffer;
    int   _buffer_size;
    int   _len;

    int _vsnprintf(char* buf, int size, const char* fmt, va_list ap);
    int _vsnprintf(char* buf, int size, const __FlashStringHelper* fmt, va_list ap);
};

#endif /* DLOGBUFFER_H_ */
