/*
 * Log.h
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

#ifndef DLOG_H_
#define DLOG_H_

#include "Print.h"
#include <stdarg.h>

#include "DLogLevel.h"
#include "DLogFormatter.h"
#include "DLogBuffer.h"
#include "DLogWriter.h"
#include "DLogWriterList.h"
#include "DLogLevelMap.h"

#define LOG_MAX_SIZE 80
#define LOG_LEVEL_DEFAULT LOG_LEVEL_INFO

#if defined(ESP8266) || defined(ESP_PLATFORM)
// these have support for std::function so we can use object methods as pre/post functions
#include <functional>
typedef std::function<void(DLogBuffer& buffer, DLogLevel level)> DLogPrePost;
#else
// default to no std::function support! (like avr currently)
typedef void (*DLogPrePost)(DLogBuffer& buffer, DLogLevel level);
#endif

class DLog
{
public:
    static DLog& getLog();
    void begin(DLogWriter* writer);
    void end();

    void setLevel(DLogLevel level);
    template<class T> void setLevel(T name, DLogLevel level);
    void setPreFunc(DLogPrePost func);
    void setPostFunc(DLogPrePost func);
    void setFormatter(DLogFormatter* formatter);

    template <class T, class F, typename... Args> void error(T tag, F fmt, Args... args) {
        print(tag, DLOG_LEVEL_ERROR, fmt, args...);
    }

    template <class T, class F, typename... Args> void warning(T tag, F fmt, Args... args) {
        print(tag, DLOG_LEVEL_WARNING, fmt, args...);
    }

    template <class T, class F, typename... Args> void info(T tag, F fmt, Args... args) {
        print(tag, DLOG_LEVEL_INFO, fmt, args...);
    }

    template <class T, class F, typename... Args> void debug(T tag, F fmt, Args... args) {
        print(tag, DLOG_LEVEL_DEBUG, fmt, args...);
    }

    template <class T, class F, typename... Args> void trace(T tag, F fmt, Args... args) {
        print(tag, DLOG_LEVEL_TRACE, fmt, args...);
    }

    // we don't allow copying this guy!
    DLog(const DLog&)            = delete;
    DLog& operator=(const DLog&) = delete;

private:
#if defined(ESP_PLATFORM)
    SemaphoreHandle_t                _lock;
#endif
    DLogBuffer                       _buffer;
    DLogLevel                        _level;      // default log level

    DLogLevelMap*                    _levels;
    DLogWriter*                      _writers;
    DLogFormatter*                   _formatter;

    DLogPrePost pre_func;
    DLogPrePost post_func;

    DLog();
    virtual ~DLog();

    void lock();
    void unlock();

    template <class T, class F> void print(T tag, DLogLevel level, F fmt, ...);
};

#endif /* DLOG_H_ */
