#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
  size_t frequency;
  char character;
} juuHeapNode;

typedef struct {
  size_t size;
  juuHeapNode* nodes;
} juuHeap;

size_t parentOfIndex(size_t i);

size_t leftChildOfIndex(size_t i);

size_t rightChildOfIndex(size_t i);

juuHeap* juuHeap_create();

void kill_juuHeap(juuHeap* heap);

void juuHeap_insertNode(juuHeap* heap, char c, size_t frequency);

void juuHeap_inOrderTraversal(juuHeap *heap, size_t index);
