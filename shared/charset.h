#ifndef AOC_2022_CHARSET_H
#define AOC_2022_CHARSET_H

typedef int * CharSet;

CharSet new_charset(void);

void add(const char *c, CharSet set);
void clear(CharSet set);
int has(const char *c, CharSet set);

#endif //AOC_2022_CHARSET_H
