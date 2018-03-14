/*
 * Log.cpp
 *
 * Copyright 2017 Christopher B. Liebman
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  Created on: Mar 2, 2018
 *      Author: chris.l
 */
#include "DLog.h"
#include "DLogWriter.h"

DLog& DLog::getLog()
{
    static DLog log;
    return log;
}

void DLog::begin(DLogWriter* writer)
{
    if (writer != nullptr)
    {
        _writers.push_back(writer);
    }
}

DLog::DLog() :
        _level(DLOG_LEVEL_INFO),
        _formatter(nullptr)
{
#ifdef ESP_PLATFORM
        _lock = xSemaphoreCreateRecursiveMutex();
#endif
}

DLog::~DLog()
{
    end();
}

void DLog::end()
{
    for(DLogWriter* w : _writers)
    {
        delete w;
    }
    _writers.clear();
    delete _formatter;
    _formatter = nullptr;
}

void DLog::setLevel(DLogLevel level)
{
    _level = level;
}

void DLog::setLevel(const char* name, DLogLevel level)
{
    _levels[name] = level;
}

void DLog::setPreFunc(DLogPrePost func)
{
    pre_func = func;
}

void DLog::setPostFunc(DLogPrePost func)
{
    post_func = func;
}

void DLog::setFormatter(DLogFormatter* formatter)
{
    lock();
    if (_formatter != nullptr)
    {
        delete _formatter;
    }
    _formatter = formatter;
    unlock();
}

void DLog::lock()
{
#if defined(ESP_PLATFORM)
    xSemaphoreTakeRecursive(_lock, portMAX_DELAY);
#endif
}

void DLog::unlock()
{
#if defined(ESP_PLATFORM)
    xSemaphoreGiveRecursive(_lock);
#endif
}

template <class F>
void DLog::print(const char* tag, DLogLevel level, F fmt, ...)
{
    //
    // if no writer method then just return, logging has not been started.
    //
    if (_writers.empty())
    {
        return;
    }

    DLogLevel limit = _level;
    if (_levels.find(tag) != _levels.end())
    {
        limit = _levels[tag];
    }

    if (level > limit)
    {
        return;
    }

    lock();

    _buffer.reset();

    if (_formatter == nullptr)
    {
        _formatter = new DLogFormatter();
    }

    _formatter->start(_buffer);

    if (pre_func)
    {
        pre_func(_buffer, level);
    }

    va_list ap;
    va_start(ap, fmt);
    _formatter->format(_buffer, tag, level, fmt, ap);
    va_end(ap);

    if (post_func)
    {
        post_func(_buffer, level);
    }

    _formatter->end(_buffer);

    for(DLogWriter* w : _writers)
    {
        w->write(_buffer.getBuffer());
    }
    unlock();
}

template void DLog::print<const char*>(const char* tag, DLogLevel level, const char* fmt, ...);
template void DLog::print<const __FlashStringHelper*>(const char* tag, DLogLevel level, const __FlashStringHelper* fmt, ...);

