/*
 * DLogLevel.h
 *
 *  Created on: Mar 10, 2018
 *      Author: chris.l
 */

#ifndef DLOGLEVEL_H_
#define DLOGLEVEL_H_


typedef enum dlog_level
{
    DLOG_LEVEL_NONE = 0,
    DLOG_LEVEL_ERROR,
    DLOG_LEVEL_WARNING,
    DLOG_LEVEL_INFO,
    DLOG_LEVEL_DEBUG,
    DLOG_LEVEL_TRACE,
    DLOG_LEVEL_MAX,
} DLogLevel;




#endif /* DLOGLEVEL_H_ */
