/*
 * DLogBuffered.h
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#ifndef DLOGBUFFER_H_
#define DLOGBUFFER_H_

#include "Arduino.h"
#include <stdarg.h>

class DLogBuffer
{
public:
    DLogBuffer();
    virtual ~DLogBuffer();

    void reset();
    const char* getBuffer();

    template<class F>void printf(F fmt, ...);
    template<class F>void vprintf(F fmt, va_list ap);
    template<class T>void print(T str);

private:
    char* _buffer;
    int   _buffer_size;
    int   _len;

    int _vsnprintf(char* buf, size_t size, const char* fmt, va_list ap);
    int _vsnprintf(char* buf, size_t size, const __FlashStringHelper* fmt, va_list ap);
    char* _strcpy(char* buf, const char* src);
    char* _strcpy(char* buf, const __FlashStringHelper* src);
    int   _strlen(const char* s);
    int   _strlen(const __FlashStringHelper* s);
};

#endif /* DLOGBUFFER_H_ */
