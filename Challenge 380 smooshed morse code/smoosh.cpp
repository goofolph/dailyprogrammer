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
