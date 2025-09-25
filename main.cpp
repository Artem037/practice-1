#include <iostream>
#include <cstring>
#include <fstream>

const int kEnglishAlphSize = 26;

bool IsLetter(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char ToLower(char c) {
  if (c >= 'A' && c <= 'Z') {
    return char(c - 'A' + 'a');
  } else {
    return c;
  }
}

bool IncludesAll(const bool need[kEnglishAlphSize], const bool have[kEnglishAlphSize]) {
    for (int i = 0; i < kEnglishAlphSize; ++i) {
      if (need[i] && !have[i]) {
        return false;
      }
    }
    return true;
}


int main(int argc, char** argv) {
  if (argc < 5) {
    std::cerr << "error\n";

    return 0;
  }

  const char* word = nullptr;
  const char* file = nullptr;

  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--word") == 0 && i + 1 < argc) {
      word = argv[i + 1];
      ++i;
    } else if (std::strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
      file = argv[i + 1];
      ++i;
    }
  }

  if (!word || !file) {
    std::cerr << "error: no word or file argument\n";

    return 0;
  }

  bool need[kEnglishAlphSize];
  for (int i = 0; i < kEnglishAlphSize; ++i) {
    need[i] = false;
  }
  for (const char* p = word; *p; ++p) {
    if (IsLetter(*p)) {
      need[ToLower(*p) - 'a'] = true;
    }
  }

  std::ifstream in;
  in.open(file, std::ios::binary);
  if (!in.is_open()) {
    std::cout << "failed to open\n";
  } else {
    bool have[kEnglishAlphSize]; 
    for (int i = 0; i < kEnglishAlphSize; ++i) {
      have[i] = false;
    }
    int count = 0;

    char ch;
    while (in.get(ch)) {
      if (IsLetter(ch)) {
        have[ToLower(ch) - 'a'] = true;
      } else {
        if (IncludesAll(need, have)) {
          ++count;
        }
        for (int i = 0; i < kEnglishAlphSize; ++i) {
          have[i] = false;
        }
      }
    }

    if (IncludesAll(need, have)) {
      ++count;
    }

    std::cout << count << '\n'; 
  }
  
  return 0;
}
