#include <iostream>
#include <cstring>
#include <fstream>

const int ENG_ALPH_SZ = 26;

bool is_letter(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char to_lower(char c) {
  if (c >= 'A' && c <= 'Z') {
    return char(c - 'A' + 'a');
  } else {
    return c;
  }
}

bool includes_all(bool need[26], bool have[26]) {
    for (int i = 0; i < 26; ++i) {
      if (need[i] && !have[i]) {
        return false;
      }
    }
    return true;
}


int main(int argc, char** argv) {
  if (std::strcmp(argv[1], "--word") != 0 || std::strcmp(argv[3], "--file") != 0 || argc < 5) {
    std::cout << "error" << '\n';
  }

  const char* word = argv[2];
  const char* file = argv[4];

  bool need[ENG_ALPH_SZ];
  for (int i = 0; i < ENG_ALPH_SZ; ++i) need[i] = false;
  for (const char* p = word; *p; ++p) {
    if (is_letter(*p)) {
      need[to_lower(*p) - 'a'] = true;
    }
  }

  std::ifstream in;
  in.open(file, std::ios::binary);
  if (!in.is_open()) {
    std::cout << "failed to open\n";
  } else {
    bool have[ENG_ALPH_SZ]; for (int i = 0; i < ENG_ALPH_SZ; ++i) have[i] = false;
    int count = 0;

    char ch;
    while (in.get(ch)) {
      if (is_letter(ch)) {
        have[to_lower(ch) - 'a'] = true;
      } else {
        if (includes_all(need, have)) ++count;
        for (int i = 0; i < ENG_ALPH_SZ; ++i) have[i] = false;
      }
    }

    if (includes_all(need, have)) ++count;

    std::cout << count << '\n'; 
  }
  
  return 0;
}
