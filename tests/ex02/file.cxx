#ifndef __file_h__
#define __file_h__

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

namespace utils {
bool isFileNull(const char* file, const char* mode = "r") {
  FILE* fp = std::fopen(file, mode);
  if (fp == NULL) {
    std::printf("can not open file! \n");
    return true;
  }
  int ch = std::fgetc(fp);
  fclose(fp);
  if (ch == EOF) return true;
  return false;
}
}  // namespace utils
#endif
