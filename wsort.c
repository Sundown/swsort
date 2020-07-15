#include <stdio.h>
#include <strings.h>

#define MAX 8192

typedef unsigned int ui;
typedef long int li;

typedef struct __attribute__((__packed__)) {
  char* str;
  ui    sum;
} Entry;

Entry list[MAX] = { { 0 } };

// Messy swap macros to be used in sorting
// Swap string
#define SSTR(a, b, c) (list[a].str = ((char*)((li)list[b].str ^ (li)list[c].str)))
// Swap int
#define SINT(a, b, c) (list[a].sum = (list[b].sum ^ list[c].sum))

ui strsum(char* str) {
    ui t = 0;

    // Iterate through str char-by-char and add int value of chars
    for (ui i = 0; i <= strlen(str) + 1 && str[i] != '\0'; t += (ui)str[i], i++);
    return t;
}

int main(int argc, char** argv) {
  if (MAX < argc) {
    fprintf(stderr, "Input arguments overflows max of %d\n", MAX);
    return 1;
  }
  
  // Iterate through args and call strsum() on each arg
  // Add sum of string to list along with string pointer
  for (ui s = 1; argv[s] != NULL; s++) {
    list[s - 1].sum = strsum(argv[s]);
    list[s - 1].str = argv[s];
  }

  // Yucky sort
  for (ui i = 0; i < MAX && list[i].str != NULL; i++) {
    for (ui j = 0; j < MAX && list[j].str != NULL; j++) {
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

  for (ui c = 0; c < MAX && list[c].str != NULL; printf("%s\n", list[c].str), c++);

  return 0;
}
