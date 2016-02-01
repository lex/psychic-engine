#include "juuheap.h"

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
  if (heap->size > 0) {
    // allocate more memory
    heap->nodes = realloc(heap->nodes, (heap->size + 1) * sizeof(juuHeapNode));
  } else {
    // allocat initial memory
    heap->nodes = calloc(1, sizeof(juuHeapNode));
  }

  juuHeapNode n;
  n.character = c;
  n.frequency = frequency;

  size_t index = (heap->size)++;

  // keep the heap in shape
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

void kill_juuHeap(juuHeap* heap) {
  // release all used memory
  free(heap->nodes);
  free(heap);
}
