#include <cassert>
#include <iostream>
#include <string>

const int alphabet_len = 26;
const char ascii_alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                               'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                               's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const std::string morse_alphabet[] = {
    ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
    ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
    "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};

std::string smorse(std::string input);

int main() {
  std::string sos = smorse("sos");
  std::string daily = smorse("daily");
  std::string programmer = smorse("programmer");
  std::string bits = smorse("bits");
  std::string three = smorse("three");

  assert(sos == "...---...");
  assert(daily == "-...-...-..-.--");
  assert(programmer == ".--..-.-----..-..-----..-.");
  assert(bits == "-.....-...");
  assert(three == "-.....-...");

  std::cout << "sos => " << sos << std::endl;
  std::cout << "daily => " << daily << std::endl;
  std::cout << "programmer => " << programmer << std::endl;
  std::cout << "bits => " << bits << std::endl;
  std::cout << "three => " << three << std::endl;
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
