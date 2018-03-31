/*
 * Created by zxh on 2018/02/21 . All rights reserved.
 */

#include <string.h>

/* memcpy() overlapping areas may produce undefined behavior.
 * so use memmove() instead
 */
void *memmove(void *dest, const void *src, size_t n)
{
        const char *s;
        char *d;

        s = src;
        d = dest;
        if (s < d && s + n > d) {
                s += n;
                d += n;
                while (n-- > 0)
                        *--d = *s++;
        } else {
                while (n-- > 0)
                        *d++ = *s++;
        }
 
        return dest;
}

void *memcpy(void *dest, const void *src, size_t n)
{
        return memmove(dest, src, n);
}

void *memset(void *s, int c, size_t n)
{
        char *p;
        int m;

        p = s;
        m = n;
        while (--m >= 0)
                *p++ = c;

        return s;
}

unsigned short *memsetw(unsigned short *s, unsigned short c, size_t n)
{
	unsigned short *p = (unsigned short *)s;
	while (--n >= 0)
		*p++ = c;
	return s;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
        const uint8_t *v1 = (const uint8_t *)s1;
        const uint8_t *v2 = (const uint8_t *)s2;

        while (n-- > 0) {
                if (*v1 != *v2)
                        return (int)*v1 -(int)*v2;
                v1++;
                v2++;
        }

        return 0;
}


size_t strlen(const char *s)
{
        size_t n;

        for (n = 0; *s != '\0'; s++)
                n++;
        return n;
}

size_t strnlen(const char *s, size_t n)
{
        size_t m;
        for (m = 0; n > 0 && *s != '\0'; s++, n--)
                m++;
        return m;
}

char *strcpy(char *dest, const char *src)
{
        char *ret;

        ret = dest;
        while ((*dest++ = *src++) != '\0')
                /* do nothing */;
        return ret;
}

char *strncpy(char *dest, const char *src, size_t n)
{
        size_t i;
        char *ret;

        ret = dest;
        for (i = 0; i < n; i++) {
                *dest++ = *src;
                /* if strlen(src) < n, null-pad DEST out to N characters. */
                if (*src != '\0')
                        src++;
        }
        return ret;
}

size_t strlcpy(char *dest, const char *src, size_t n)
{
        char *p;

        p = dest;
        if (n > 0) {
                while (--n > 0 && *src != '\0')
                        *p++ = *src++;
                *p = '\0';
        }
        return dest - p;
}

int strcmp(const char *s1, const char *s2)
{
        while (*s1 && *s1 == *s2) {
                s1++;
                s2++;
        }
        return (int)((unsigned char)*s1 - (unsigned char)*s2);
}

int strncmp(const char *s1, const char *s2, size_t n)
{
        while (n > 0 && *s1 && *s1 == *s2) {
                n--;
                s1++;
                s2++;
        }
        if (n == 0)
                return 0;
        else
                return (int)((unsigned char)*s1 - (unsigned char)*s2);
}

char *strchr(const char *s, char c)
{
        for ( ; *s; s++) {
                if (*s == c)
                        return (char *)s;
        }
        return 0;
}
