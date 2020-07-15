#include <stdio.h>
#include <stdint.h>
#include <strings.h>

#define MAX 8192

typedef struct __attribute__((__packed__)) {
  char* str;
  uint32_t sum;
} Entry;

Entry list[MAX] = { { 0 } };

// Messy swap macros to be used in sorting
// Swap string
#define SSTR(a, b, c) (list[a].str = ((char*)((int64_t)list[b].str ^ (int64_t)list[c].str)))
// Swap int
#define SINT(a, b, c) (list[a].sum = (list[b].sum ^ list[c].sum))

uint32_t strsum(char* str) {
  uint32_t t = 0;

  // Iterate through str char-by-char and add int value of chars
  for (uint32_t i = 0; i <= strlen(str) + 1 && str[i] != '\0'; t += (uint32_t)str[i], i++);
  return t;
}

int main(int argc, char** argv) {
  if (MAX < argc) {
    fprintf(stderr, "Input arguments overflows max of %d\n", MAX);
    return 1;
  }
  
  // Iterate through args and call strsum() on each arg
  // Add sum of string to list along with string pointer
  for (uint32_t s = 1; argv[s] != NULL; s++) {
    list[s - 1].sum = strsum(argv[s]);
    list[s - 1].str = argv[s];
  }

  // Sucky sort
  for (uint32_t i = 0; i < MAX && list[i].str != NULL; i++) {
    for (uint32_t j = 0; j < MAX && list[j].str != NULL; j++) {
      if (list[j].sum > list[i].sum) {
        SINT(i, i, j);
        SINT(j, i, j);
        SINT(i, i, j);
        SSTR(i, i, j);
        SSTR(j, i, j);
        SSTR(i, i, j);
      }
    }
  }

  for (uint32_t c = 0; c < MAX && list[c].str != NULL; printf("%s\n", list[c].str), c++);

  return 0;
}
