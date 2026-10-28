#include <cctype>
#include <cstring>
#include <iostream>

const int error = 1;
const int initial_buffer = 8;

namespace kazbanov {
  char* removeLatin(char* dest, const char* src)
  {
    size_t idx = 0;
    for (size_t i = 0; src[i] != '\0'; i++) {
      if (!std::isalpha(static_cast< unsigned char >(src[i]))) {
        dest[idx++] = src[i];
      }
    }
    dest[idx] = '\0';
    return dest;
  }

  char* removeVowel(char* dest, const char* src)
  {
    size_t idx = 0;
    for (size_t i = 0; src[i] != '\0'; i++) {
      if (!std::strchr("aeiouAEIOU", src[i])) {
        dest[idx++] = src[i];
      }
    }
    dest[idx] = '\0';
    return dest;
  }
}

int main()
{
  size_t size = 0;
  size_t max_size = initial_buffer;
  char* buffer = nullptr;
  try {
    buffer = new char[max_size];
  } catch (...) {
    std::cerr << "Error\n";
    return error;
  }
  char ch = '\0';
  while (std::cin.get(ch) && ch != '\n') {
    if (size + 1 >= max_size) {
      const size_t new_max_size = max_size * 2;
      char* new_buffer = nullptr;
      try {
        new_buffer = new char[new_max_size];
      } catch (...) {
        delete[] buffer;
        std::cerr << "Error\n";
        return error;
      }
      for (size_t i = 0; i < size; i++) {
        new_buffer[i] = buffer[i];
      }
      delete[] buffer;
      buffer = new_buffer;
      max_size = new_max_size;
    }
    buffer[size++] = ch;
  }
  buffer[size] = '\0';

  if (size == 0) {
    std::cerr << "Error\n";
    delete[] buffer;
    return error;
  }

  char* result = nullptr;
  try {
    result = new char[size + 1];
  } catch (...) {
    std::cerr << "Error\n";
    delete[] buffer;
    return error;
  }

  std::cout << kazbanov::removeLatin(result, buffer) << "\n";
  std::cout << kazbanov::removeVowel(result, buffer) << "\n";

  delete[] buffer;
  delete[] result;

  return 0;
}
