#include <stdio.h>
#include <stdlib.h>
#include "panic.hh"

void panic(const std::string& message) {
  fprintf(stderr, message.c_str());
  exit(42);
}

