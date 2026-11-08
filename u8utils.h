/*
 * This file is part of u8utils.
 *
 * libu8string is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libu8string is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libu8string. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#ifndef U8UTILS_H
#define U8UTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Always null-terminated sequence */
#define U8CODEPT_LEN 5
typedef char u8codept_t[U8CODEPT_LEN];

static inline size_t
cstr_get_first_utf8char_len (const unsigned char *ptr)
{
  const unsigned char U8_CODEPT_4B = 0xF0;
  const unsigned char U8_CODEPT_3B = 0xE0;
  const unsigned char U8_CODEPT_2B = 0xC0;
  const unsigned char U8_CODEPT_1B = 0x7F;

  if      (ptr[0] <= U8_CODEPT_1B)                  return 1;
  else if ((ptr[0] & U8_CODEPT_4B) == U8_CODEPT_4B) return 4;
  else if ((ptr[0] & U8_CODEPT_3B) == U8_CODEPT_3B) return 3;
  else if ((ptr[0] & U8_CODEPT_2B) == U8_CODEPT_2B) return 2;

  return 0;
}

static inline bool
u8codept_copy (u8codept_t dest, const u8codept_t src)
{
  if (!dest || !src)
    return false;

  memcpy (dest, src, U8CODEPT_LEN);

  return true;
}

static inline bool
u8codept_compare (const void *first, const void *second)
{
  if (!first || !second)
    return false;

  return !strncmp (first, second, U8CODEPT_LEN);
}

static inline size_t
u8str_codepoints_count (const char *string)
{
  size_t length = 0;
  size_t i;

  for (i = 0; string[i]; ++length)
    i += cstr_get_first_utf8char_len ((unsigned char*) string + i);

  return length;
}

static inline char*
u8str_next_codepoint (const char *src, u8codept_t *buff)
{
  const size_t offset = cstr_get_first_utf8char_len ((unsigned char*) src);

  if (offset == 0)
    return NULL;

  memset (buff, 0, U8CODEPT_LEN);
  memcpy (buff, src, offset);

  return (char*) src + offset;
}

#endif  /* U8UTILS_H */
