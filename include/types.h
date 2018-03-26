/*
 * Created by zxh on 2018/02/20 . All rights reserved.
 */

#ifndef YEQU_INCLUDE_TYPES_H
#define YEQU_INCLUDE_TYPES_H

typedef signed char             int8_t;
typedef unsigned char           uint8_t;
typedef short                   int16_t;
typedef unsigned short          uint16_t;
typedef int                     int32_t;
typedef unsigned int            uint32_t;
typedef long long               int64_t;
typedef unsigned long long      uint64_t;

typedef uint32_t                uintptr_t;
typedef int32_t                 intptr_t;
typedef uint32_t                size_t;
typedef int32_t                 ssize_t;

typedef uint8_t                 bool;
#define TRUE                    ((bool) 1)
#define FALSE                   ((bool) 0)

#define NULL                    ((void *) 0)

#endif /* YEQU_INCLUDE_TYPES_H */
