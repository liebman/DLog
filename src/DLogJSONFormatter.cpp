/*
 * DLogJsonFormater.cpp
 *
 *  Created on: Mar 12, 2018
 *      Author: chris.l
 */

#include <DLogJSONFormatter.h>

DLogJSONFormatter::DLogJSONFormatter(DLogJSONFunc json_func, bool pretty) : _json_func(json_func), _pretty(pretty)
{
    _pre_line  = pretty ? "  " : "";
    _post_line = pretty ? "\n" : "";
}

DLogJSONFormatter::DLogJSONFormatter(DLogJSONFunc json_func) : DLogJSONFormatter(json_func, false)
{
}

DLogJSONFormatter::DLogJSONFormatter(bool pretty) : DLogJSONFormatter(nullptr, pretty)
{
}

DLogJSONFormatter::DLogJSONFormatter() : DLogJSONFormatter(nullptr, false)
{
}

DLogJSONFormatter::~DLogJSONFormatter()
{
}

void DLogJSONFormatter::start(DLogBuffer& buffer)
{
    buffer.printf(F("{%s"), _post_line);
}

void DLogJSONFormatter::startContents(DLogBuffer& buffer, const char* tag, DLogLevel level)
{
    buffer.printf(F("%s\"name\":\"%s\",%s"), _pre_line, tag, _post_line);
    buffer.printf(F("%s\"level\":\"%c\",%s"), _pre_line, levels[level], _post_line);
    buffer.printf(F("%s\"message\":\""), _pre_line);
}

void DLogJSONFormatter::endContents(DLogBuffer& buffer, const char* tag, DLogLevel level)
{
    (void)tag;
    (void)level;
    buffer.printf(F("\""));
    if (_json_func)
    {
        buffer.printf(F(",%s"), _post_line);
        _json_func(buffer, _pre_line, _post_line);
    }
}

void DLogJSONFormatter::format(DLogBuffer& buffer, const char* tag, DLogLevel level, const char* fmt, va_list ap)
{
    startContents(buffer, tag, level);
    buffer.vprintf(fmt, ap);
    endContents(buffer, tag, level);
}

void DLogJSONFormatter::format(DLogBuffer& buffer, const char* tag, DLogLevel level, const __FlashStringHelper* fmt, va_list ap)
{
    startContents(buffer, tag, level);
    buffer.vprintf(fmt, ap);
    endContents(buffer, tag, level);
}

void DLogJSONFormatter::end(DLogBuffer& buffer)
{
   buffer.printf(F("%s}\n"), _post_line);
}

