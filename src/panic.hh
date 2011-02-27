#ifndef PANIC_H
#define PANIC_H

#include <string>

void panic(const std::string&) __attribute__((noreturn));

#endif
