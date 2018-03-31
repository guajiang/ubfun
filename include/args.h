/*
 * Created by zxh on 2017/07/30 . All rights reserved.
 */

#ifndef YEQU_INCLUDE_ARGS_H
#define YEQU_INCLUDE_ARGS_H

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif

#define va_start(ap, param)	__builtin_va_start(ap, param)
#define va_end(ap)		__builtin_va_end(ap)
#define va_arg(ap, type)	__builtin_va_arg(ap, type)

#endif /* YEQU_INCLUDE_ARGS_H */
