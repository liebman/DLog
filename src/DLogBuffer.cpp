/*
 * DLogBuffered.cpp
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#include "DLogBuffer.h"

//#define DLOG_BUFFER_DEBUG
#if defined(DLOG_BUFFER_DEBUG)
#define dbprintf(fmt, ...)  Serial.printf(fmt, __VA_ARGS__)
#else
#define dbprintf(fmt, ...)
#endif

#if defined ESP8266
//
// Issues with PROGMEM and templates in gcc force us to redefine F()
// keep these strings in flash
#undef F
#define F(s) (s)
#endif

#define DLOG_BUFFER_INCREMENT 80

DLogBuffer::DLogBuffer()
{
    _len         = 0;
    _buffer_size = DLOG_BUFFER_INCREMENT;
    _buffer      = (char*)malloc(_buffer_size);
    _buffer[0]   = '\0';
}

DLogBuffer::~DLogBuffer()
{
    free(_buffer);
}

void DLogBuffer::reset()
{
    _len = 0;
    _buffer[0] = '\0';
}

const char* DLogBuffer::getBuffer()
{
    return _buffer;
}

template<class F>
void DLogBuffer::printf(F fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}

template void DLogBuffer::printf<const char*>(const char* fmt, ...);
template void DLogBuffer::printf<const __FlashStringHelper*>(const __FlashStringHelper* fmt, ...);

template<class F>
void DLogBuffer::vprintf(F fmt, va_list ap)
{
    va_list ap2;
    va_copy(ap2, ap);

    int available =  _buffer_size-_len;

    dbprintf("buffer_size: %d len: %d available: %d\n", _buffer_size, _len, available);

    int size = _vsnprintf(_buffer+_len, available, fmt, ap) + 1; // include the '\0' in size

    dbprintf("size: %d\n", size);

    if (size > available)
    {
        int newsize = _buffer_size + ((size - _buffer_size) > DLOG_BUFFER_INCREMENT ? size+1 : DLOG_BUFFER_INCREMENT);

        dbprintf("newsize: %d\n", newsize);

        char* newbuf = (char*)realloc(_buffer, newsize);

        if (newbuf == nullptr)
        {
            return;
        }

        _buffer      = newbuf;
        _buffer_size = newsize;
        available    = _buffer_size-_len;

        dbprintf("new available: %d\n", available);

        _vsnprintf(_buffer+_len, available, fmt, ap2);
        va_end(ap2);
    }
    _len += size-1; // exclude the '\0' from _len

    dbprintf("buffer: '%s'\n", _buffer);
}

template void DLogBuffer::vprintf<const char*>(const char* fmt, va_list ap);
template void DLogBuffer::vprintf<const __FlashStringHelper*>(const __FlashStringHelper* fmt, va_list ap);

int DLogBuffer::_vsnprintf(char* buf, size_t size, const char* fmt, va_list ap)
{
    return vsnprintf(buf, size, fmt, ap);
}

int DLogBuffer::_vsnprintf(char* buf, size_t size, const __FlashStringHelper* fmt, va_list ap)
{
    PGM_P fmt_p = reinterpret_cast<PGM_P>(fmt);
#ifdef ARDUINO_ARCH_NRF5
#define vsnprintf_P(s, n, f, ap) vsnprintf((s), (n), (f), (ap))
#endif

    return vsnprintf_P(buf, size, fmt_p, ap);
}
