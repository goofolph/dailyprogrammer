#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int alphabet_len = 26;
const char ascii_alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                               'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                               's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const std::string morse_alphabet[] = {
    ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
    ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
    "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};
const std::string enable1 = "enable1.txt";

/* Translates word to smooshed morse code.

  param input word to be translated must be all lowercase
  returns smooshed translation
*/
std::string smorse(std::string input);

/* Optional bonus challenge 1.

Find the only sequence that's the code for 13 different words.
*/
void optional1(std::vector<std::pair<std::string, std::string>> translations);

/* Opional bonus challenge 2.

Find the only word that hase 15 dashes in a row.
*/
void optional2(std::vector<std::pair<std::string, std::string>> translations);

/* Opional bonus challenge 3.

Find the perfectly balanced codes of length 21.
*/
void optional3(std::vector<std::pair<std::string, std::string>> translations);

/* Opional bonus challenge 4.

Find the only 13-letter word that encodes to palindrome.
*/
void optional4(std::vector<std::pair<std::string, std::string>> translations);

/* Sorting function for vector of pairs comparing the morse element.
 */
bool sortbymorse(const std::pair<std::string, std::string>& a,
                 const std::pair<std::string, std::string>& b);

/* Checks if code is perfectly balanced.

  A code is perfectly balanced if it hase the same number of dots and dashes.
*/
bool isBalanced(std::string a);

/* Checks if string is palindrome. */
bool isPalindrome(std ::string a);

int main() {
  std::vector<std::pair<std::string, std::string>> translations;
  std::ifstream in;
  unsigned long dots = 0;    // count dots for final check from reddit source
  unsigned long dashes = 0;  // count dashes for final check from reddit source

  // translate example inputs
  std::string sos = smorse("sos");
  std::string daily = smorse("daily");
  std::string programmer = smorse("programmer");
  std::string bits = smorse("bits");
  std::string three = smorse("three");

  // check example outputs
  assert(sos == "...---...");
  assert(daily == "-...-...-..-.--");
  assert(programmer == ".--..-.-----..-..-----..-.");
  assert(bits == "-.....-...");
  assert(three == "-.....-...");

  // display examples
  std::cout << "sos => " << sos << std::endl;
  std::cout << "daily => " << daily << std::endl;
  std::cout << "programmer => " << programmer << std::endl;
  std::cout << "bits => " << bits << std::endl;
  std::cout << "three => " << three << std::endl;

  // read in enable1 word list and translate to smooshed
  in.open(enable1);
  for (std::string line; std::getline(in, line);) {
    // need to remove trailing \r if present (mostly for non windows)
    if (line[line.length() - 1] == '\r') {
      line.erase(line.length() - 1);
    }
    std::string smooshed = smorse(line);
    translations.push_back(std::make_pair(line, smooshed));
    // count dots and dashes for assertion check
    for (auto c : smooshed) {
      if (c == '.') {
        dots++;
      } else {
        dashes++;
      }
    }
  }
  in.close();

  // make sure proper totals of dots and dashes
  assert(dots == 2499157);
  assert(dashes == 1565081);

  optional1(translations);
  optional2(translations);
  optional3(translations);
  optional4(translations);
}

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
  for (size_t i = 0; i < sorted.size(); i++) {
    thirteen.clear();
    thirteen.push_back(sorted[i]);
    size_t j = i + 1;
    while (j < sorted.size() && sorted[i].second == sorted[j].second) {
      thirteen.push_back(sorted[j]);
      j++;
    }
    if (thirteen.size() == 13) {
      for (auto p : thirteen) {
        std::cout << p.first << " => " << p.second << std::endl;
      }
    } else {
      thirteen.clear();
    }
  }
}

bool sortbymorse(const std::pair<std::string, std::string>& a,
                 const std::pair<std::string, std::string>& b) {
  return (a.second < b.second);
}

void optional2(std::vector<std::pair<std::string, std::string>> translations) {
  std::cout << std::endl
            << "Optional 2: Only code with 15 consecutive dashes" << std::endl;
  for (auto p : translations) {
    if (p.second.find("---------------") != std::string::npos) {
      std::cout << p.first << " => " << p.second << std::endl;
    }
  }
}

void optional3(std::vector<std::pair<std::string, std::string>> translations) {
  std::cout << std::endl
            << "Optional 3: Perfectly balanced codes words of length 21"
            << std::endl;
  for (auto p : translations) {
    if (p.first.length() == 21 && isBalanced(p.second) == true) {
      std::cout << p.first << " => " << p.second << std::endl;
    }
  }
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
  for (auto p : translations) {
    if (p.first.length() == 13 && isPalindrome(p.second)) {
      std::cout << p.first << " => " << p.second << std::endl;
    }
  }
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
