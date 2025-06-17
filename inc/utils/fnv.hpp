#pragma once

#include <cstdint>

namespace utils::fnv {
  constexpr uint32_t hash(const char* str) {
    auto value = 0x811c9dc5;

    while (*str) {
      value ^= *str++;
      value *= 0x1000193;
    }

    return value;
  }
}
