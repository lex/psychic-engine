#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "juuheap.h"

int main(int argc, char* argv[]) {
  const char* s = u8"fresh beer enjoyment";

  printf("%s\n", s);

  size_t frequencies[512] = {0};

  juuHeap* heap = juuHeap_create();

  // get the character frequencies
  for (size_t i = 0; i < strlen(s); ++i) {
    ++frequencies[(size_t) s[i]];
  }

  // push the frequencies to the heap
  for (size_t j = 0; j < 512; ++j) {
    size_t frequency = frequencies[j];

    if (!frequency) {
      continue;
    }

    juuHeap_insertNode(heap, (char) j, frequency);
  }

  kill_juuHeap(heap);

  return 0;
}

