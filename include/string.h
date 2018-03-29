/*
 * Created by zxh on 2018/02/20 . All rights reserved.
 */

#ifndef YEQU_INCLUDE_STRING_H
#define YEQU_INCLUDE_STRING_H

#include <types.h>

/* copy n bytes of src to dest. */
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);

/* set N bytes of S to C. */
void *memset(void *s, int c, size_t n);

/* compare N bytes of S1 and S2. */
int memcmp(const void *s1, const void *s2, size_t n);

/* copy SRC to DEST. */
char *strcpy(char *dest, const char *src);

/* copy no more than N characters of SRC to DEST. */
char *strncpy(char *dest, const char *src, size_t n);
size_t strlcpy(char *dest, const char *src, size_t n);

/* append SRC onto DEST. */
char *strcat(char *dest, const char *src);

/* append no more than N characters of SRC to DEST */
char *strncar(char *dest, const char *src, size_t n);

/* compare S1 and S2. */
int strcmp(const char *s1, const char *s2);

/* compare N characters of S1 and S2. */
int strncmp(const char *s1, const char *s2, size_t n);

/* locate characters in string */
char *strchr(const char *s, char c);

/* calculates the length of string, excludeing the terminating null byte ('\0') */
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);

/* convert the interger D to s string and save the string in BUF */
void itoa(char *buf, int base, int d);

#endif /* YEQU_INCLUDE_STRING_H */
