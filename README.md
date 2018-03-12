# DLog - an extensible debug logging system

DLog is a robust, extensible debug logging system supporting multiple log destinations. While it's mainly
intended for ESP8266 and ESP32 it may work on others if sufficient C++ STL support is included.

[![Build Status](https://travis-ci.org/liebman/DLog.svg?branch=master)](https://travis-ci.org/liebman/DLog)

### Features

 * Multiple "writers" allow output to Serial and Network destinations
 * Configurable format.

### Implemnented Writers

 * `DLogPrintWriter` - sends log lines to any object inheriting from `Print`.
 * `DLogTCPWriter` - sends log lines to remote systems.

### Future Writers

 * `DLogUDPWriter` - send log lines to remote systems via UDP
 * `DLogSyslogWriter` - send log lines to syslog
 * `DLogESWriter` - send log lines to Elastic Search
