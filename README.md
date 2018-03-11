# DLog - an extensible debug logging system

DLog is a robust, extensible debug logging system supporting multiple log destinations.

### Features

 * Multiple "writers" allow output to Serial and Network destinations
 * Configurable format.

### Implemnented Writers 

 * `DLogPrintWriter` - sends log lines to any object inheriting from `Print`.
 * `DLogTCPWriter` - sends log lines to remote systems.

## Future Writers

 * `DLogUDPWriter` - send log lines to remote systems via UDP
 * `DLogSyslogWriter` - send log lines to syslog
 * `DLogESWriter` - send log lines to Elastic Search
