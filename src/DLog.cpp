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
#include "DLogLevelMap.h"
#include "DLogWriterList.h"
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
        if (_writers == nullptr)
        {
            // just a single writer.
            _writers = writer;
        }
        else if (_writers->isList())
        {
            // we already have a writer list so just add
            ((DLogWriterList*)_writers)->addWriter(writer);
        }
        else
        {
            // Swap the single writer with a writer list
            DLogWriterList* list = new DLogWriterList();
            list->addWriter(_writers);
            list->addWriter(writer);
            _writers = list;
        }
    }
}

DLog::DLog() :
        _level(DLOG_LEVEL_INFO),
        _levels(nullptr),
        _writers(),
        _formatter(nullptr),
        pre_func(nullptr),
        post_func(nullptr)
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
    if (_formatter != nullptr)
    {
        delete _formatter;
        _formatter = nullptr;
    }

    if (_writers != nullptr)
    {
        delete _writers;
        _writers = nullptr;
    }
}

void DLog::setLevel(DLogLevel level)
{
    _level = level;
}

template<class T>
void DLog::setLevel(T tag, DLogLevel level)
{
    if (_levels == nullptr)
    {
        _levels = new DLogLevelMap();
    }
    _levels->setLevel(tag, level);
}

template void DLog::setLevel<const char*>(const char* tag, DLogLevel level);
template void DLog::setLevel<const __FlashStringHelper*>(const __FlashStringHelper* tag, DLogLevel level);

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

template <class T, class F>
void DLog::print(T tag, DLogLevel level, F fmt, ...)
{
    if (_writers == nullptr)
    {
        return;
    }


    DLogLevel limit = _level;
    if (_levels != nullptr)
    {
        limit = _levels->getLevel(tag, _level);
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

    _writers->write(_buffer.getBuffer());

    unlock();
}

template void DLog::print<const char*, const char*>(const char* tag, DLogLevel level, const char* fmt, ...);
template void DLog::print<const char*, const __FlashStringHelper*>(const char* tag, DLogLevel level, const __FlashStringHelper* fmt, ...);
template void DLog::print<const __FlashStringHelper*, const char*>(const __FlashStringHelper* tag, DLogLevel level, const char* fmt, ...);
template void DLog::print<const __FlashStringHelper*, const __FlashStringHelper*>(const __FlashStringHelper* tag, DLogLevel level, const __FlashStringHelper* fmt, ...);
