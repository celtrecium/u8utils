#include <stdio.h>
#include <string.h>
#include "u8utils.h"

void
test_u8char_compare (const u8codept_t a, const u8codept_t b)
{
  if (u8codept_compare (a, b))
    printf ("UTF8 characters '%.*s' and '%.*s' are equal\n",
            U8CODEPT_LEN, a,
            U8CODEPT_LEN, b);
  else
    printf ("UTF8 characters '%.*s' and '%.*s' aren't equal\n",
            U8CODEPT_LEN, a,
            U8CODEPT_LEN, b);
}

int
main (void)
{
  const char  *str    = "Привет, Мир!";
  const size_t u8slen = u8str_codepoints_count (str);

  char *ptr = (char*) str;
  size_t i;
  u8codept_t chbuff, a, b;

  printf ("UTF8 string length: %zu\n", u8slen);
  puts ("-----------------------");

  for (i = 0; i < u8slen; ++i)
    {
      ptr = u8str_next_char (ptr, &chbuff);
      printf ("[%zu] = \t'%.*s'\n", i, U8CODEPT_LEN, chbuff);
    }

  puts ("-----------------------");
  
  u8str_next_char ("Б", &a);
  u8str_next_char ("Ж", &b);

  test_u8char_compare (a, b);

  u8codept_copy (b, a);
  
  test_u8char_compare (a, b);

  return 0;
}
