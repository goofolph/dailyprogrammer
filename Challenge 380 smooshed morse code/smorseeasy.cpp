#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "alphabet.h"
#include "smorseeasy.h"

std::string smorse(std::string input) {
  std::string output;
  for (auto c : input) {
    for (int i = 0; i < alphabet_len; i++) {
      if (ascii_alphabet[i] == c) {
        output += morse_alphabet[i];
      }
    }
  }
  return output;
}

void optional1(std::vector<std::pair<std::string, std::string>> translations) {
  // make a copy of translations and sort them by morse
  std::vector<std::pair<std::string, std::string>> sorted(translations);
  std::sort(sorted.begin(), sorted.end(), sortbymorse);

  std::vector<std::pair<std::string, std::string>> thirteen;
  std::cout << std::endl
            << "Optional 1: Only code with exactly 13 inputs" << std::endl;
  bool success = false;
  for (size_t i = 0; i < sorted.size(); i++) {
    thirteen.clear();
    thirteen.push_back(sorted[i]);
    size_t j = i + 1;
    while (j < sorted.size() && sorted[i].second == sorted[j].second) {
      thirteen.push_back(sorted[j]);
      j++;
    }
    if (thirteen.size() == 13) {
      success = true;
      for (auto p : thirteen) {
        std::cout << p.first << " => " << p.second << std::endl;
      }
    } else {
      thirteen.clear();
    }
  }
  assert(success);
}

bool sortbymorse(const std::pair<std::string, std::string>& a,
                 const std::pair<std::string, std::string>& b) {
  return (a.second < b.second);
}

void optional2(std::vector<std::pair<std::string, std::string>> translations) {
  std::cout << std::endl
            << "Optional 2: Only code with 15 consecutive dashes" << std::endl;
  bool success = false;
  for (auto p : translations) {
    if (p.second.find("---------------") != std::string::npos) {
      std::cout << p.first << " => " << p.second << std::endl;
      success = true;
    }
  }
  assert(success);
}

void optional3(std::vector<std::pair<std::string, std::string>> translations) {
  std::cout << std::endl
            << "Optional 3: Perfectly balanced codes words of length 21"
            << std::endl;
  int count = 0;
  for (auto p : translations) {
    if (p.first.length() == 21 && isBalanced(p.second) == true) {
      std::cout << p.first << " => " << p.second << std::endl;
      count++;
    }
  }
  assert(count == 2);
}

bool isBalanced(std::string a) {
  int dots = 0;
  int dashes = 0;
  for (auto c : a) {
    switch (c) {
      case '.':
        dots++;
        break;
      case '-':
        dashes++;
        break;
      default:
        assert(false);
        break;
    }
  }
  return (dots == dashes);
}

void optional4(std::vector<std::pair<std::string, std::string>> translations) {
  std::cout << std::endl
            << "Optional 4: Only 13 letter word that's code is a palidrome"
            << std::endl;
  bool success = false;
  for (auto p : translations) {
    if (p.first.length() == 13 && isPalindrome(p.second)) {
      std::cout << p.first << " => " << p.second << std::endl;
      success = true;
    }
  }
  assert(success);
}

bool isPalindrome(std::string a) {
  size_t i = 0;
  size_t j = a.length() - 1;
  while (i < j) {
    if (a[i] != a[j]) {
      return false;
    }
    i++;
    j--;
  }
  return true;
}
