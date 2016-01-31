#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  size_t frequency;
  char character;
} juuHeapNode;

typedef struct {
  size_t size;
  juuHeapNode* nodes;
} juuHeap;


size_t parentOfIndex(size_t i) {
  return (i - 1) / 2;
}

size_t leftChildOfIndex(size_t i) {
  return (2 * i + 1);
}

size_t rightChildOfIndex(size_t i) {
  return (2 * i + 2);
}

void juuHeap_insertNode(juuHeap* heap, char c, size_t frequency) {
  if (heap->size) {
    heap->nodes = realloc(heap->nodes, (heap->size + 1) * sizeof(juuHeapNode));
  } else {
    heap->nodes = calloc(1, sizeof(juuHeapNode));
  }

  juuHeapNode n;
  n.character = c;
  n.frequency = frequency;

  size_t index = (heap->size)++;

  while (index && n.frequency < heap->nodes[parentOfIndex(index)].frequency) {
    heap->nodes[index] = heap->nodes[parentOfIndex(index)];
    index = parentOfIndex(index);
  }

  heap->nodes[index] = n;
}

juuHeap* juuHeap_create() {
  juuHeap* heap = calloc(1, sizeof(juuHeap));
  heap->size = 0;
  return heap;
}

void juuHeap_inOrderTraversal(juuHeap* heap, size_t index) {
  if (leftChildOfIndex(index) < heap->size) {
    juuHeap_inOrderTraversal(heap, leftChildOfIndex(index));
  }

  juuHeapNode* n = &heap->nodes[index];
  printf("%c: %zu\n", n->character, n->frequency);

  if (rightChildOfIndex(index) < heap->size) {
    juuHeap_inOrderTraversal(heap, rightChildOfIndex(index));
  }
}

int main(int argc, char* argv[]) {
  const char* s = u8"fresh beer enjoyment";

  printf("%s\n", s);

  size_t frequencies[512] = {0};

  juuHeap* heap = juuHeap_create();

  for (size_t i = 0; i < strlen(s); ++i) {
    printf("%c: %hhx\n", s[i], s[i]);
    ++frequencies[(size_t) s[i]];
  }

  for (size_t j = 0; j < 512; ++j) {
    size_t frequency = frequencies[j];

    if (!frequency) {
      continue;
    }

    juuHeap_insertNode(heap, (char) j, frequency);
  }


  juuHeap_inOrderTraversal(heap, 0);

  free(heap->nodes);
  free(heap);

  return 0;
}

