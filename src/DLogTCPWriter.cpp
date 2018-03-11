/*
 * DLogTCPWriter.cpp
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#include "DLogTCPWriter.h"

//#define DLOG_TCP_DEBUG
#if defined(DLOG_TCP_DEBUG)
#define dbprintf(...)  Serial.printf(__VA_ARGS__)
#else
#define dbprintf(fmt, ...)
#endif

DLogTCPWriter::DLogTCPWriter(const char* host, uint16_t port) : _host(host), _port(port)
{
    _client.setTimeout(10000); // for logging we use a 10 second timeout
}

DLogTCPWriter::~DLogTCPWriter()
{
}

void DLogTCPWriter::write(const char* message)
{
    if (!_client.connected())
    {
        dbprintf("connecting to: %s:%u\n", _host.c_str(), _port);

        if (!_client.connect(_host.c_str(), _port))
        {
            dbprintf("connection failed: %s:%u\n", _host.c_str(), _port);
            return;
        }
    }

    _client.write(message);
    _client.flush();
}
