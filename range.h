#pragma once
#include "iterobject.h"
#define REVERSE_RANGE_IMPLEMENTED

IterObject inline Range(int end) {
  return IterObject(end);
}

IterObject inline Range(int start, int end) {
  return {start, end};
}

IterObject inline Range(int start, int end, int step) {
  return {start, end, step};
}