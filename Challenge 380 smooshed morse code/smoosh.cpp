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
Translated pairs must be sorted by morse.
*/
std::vector<std::pair<std::string, std::string>> optional1(
    std::vector<std::pair<std::string, std::string>> sortedTranslations);

/* Opional bonus challenge 2.

Find the only word that hase 15 dashes in a row.
*/
std::pair<std::string, std::string> optional2(
    std::vector<std::pair<std::string, std::string>> translations);

/* Opional bonus challenge 3.

Find the perfectly balanced codes of length 21.
*/
std::vector<std::pair<std::string, std::string>> optional3(
    std::vector<std::pair<std::string, std::string>> translations);

/* Opional bonus challenge 4.

Find the only 13-letter word that encodes to palindrome.
*/
std::vector<std::pair<std::string, std::string>> optional4(
    std::vector<std::pair<std::string, std::string>> translations);

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

  // make a copy of translations and sort them by morse
  std::vector<std::pair<std::string, std::string>> sorted(translations);
  std::sort(sorted.begin(), sorted.end(), sortbymorse);

  // optional 1
  auto thirteen = optional1(sorted);
  std::cout << std::endl
            << "Optional 1: Only code with exactly 13 inputs" << std::endl;
  for (auto p : thirteen) {
    std::cout << p.first << " => " << p.second << std::endl;
  }

  // optional 2
  std::cout << std::endl
            << "Optional 2: Only code with 15 consecutive dashes" << std::endl;
  auto dashes15 = optional2(translations);
  std::cout << dashes15.first << " => " << dashes15.second << std::endl;

  // optional 3
  std::cout << std::endl
            << "Optional 3: Perfectly balanced codes words of length 21"
            << std::endl;
  auto balanced = optional3(translations);
  for (auto pair : balanced) {
    std::cout << pair.first << " => " << pair.second << std::endl;
  }

  // optional 4
  std::cout << std::endl
            << "Optional 4: Only 13 letter word that's code is a palidrome"
            << std::endl;
  auto palindrome = optional4(translations);
  for (auto pair : palindrome) {
    std::cout << pair.first << " => " << pair.second << std::endl;
  }
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

std::vector<std::pair<std::string, std::string>> optional1(
    std::vector<std::pair<std::string, std::string>> sorted) {
  std::vector<std::pair<std::string, std::string>> thirteen;

  for (int i = 0; i < sorted.size(); i++) {
    thirteen.clear();
    thirteen.push_back(sorted[i]);
    int j = i + 1;
    while (j < sorted.size() && sorted[i].second == sorted[j].second) {
      thirteen.push_back(sorted[j]);
      j++;
    }
    if (thirteen.size() == 13) {
      return thirteen;
    } else {
      thirteen.clear();
    }
  }

  return thirteen;
}

bool sortbymorse(const std::pair<std::string, std::string>& a,
                 const std::pair<std::string, std::string>& b) {
  return (a.second < b.second);
}

std::pair<std::string, std::string> optional2(
    std::vector<std::pair<std::string, std::string>> translations) {
  std::pair<std::string, std::string> found;
  for (auto pair : translations) {
    if (pair.second.find("---------------") != std::string::npos) {
      found = pair;
    }
  }
  return found;
}

std::vector<std::pair<std::string, std::string>> optional3(
    std::vector<std::pair<std::string, std::string>> translations) {
  std::vector<std::pair<std::string, std::string>> balanced;
  for (auto pair : translations) {
    if (pair.first.length() == 21 && isBalanced(pair.second) == true) {
      balanced.push_back(pair);
    }
  }
  return balanced;
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

std::vector<std::pair<std::string, std::string>> optional4(
    std::vector<std::pair<std::string, std::string>> translations) {
  std::vector<std::pair<std::string, std::string>> palindromes;
  for (auto pair : translations) {
    if (pair.first.length() == 13 && isPalindrome(pair.second)) {
      palindromes.push_back(pair);
    }
  }
  return palindromes;
}

bool isPalindrome(std::string a) {
  int i = 0;
  int j = a.length() - 1;
  while (i < j) {
    if (a[i] != a[j]) {
      return false;
    }
    i++;
    j--;
  }
}
