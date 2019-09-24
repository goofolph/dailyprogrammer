#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "alphabet.h"
#include "smorseeasy.h"
#include "smorseinter.h"

const std::string enable1 = "enable1.txt";
const std::string inputs1000 = "smorse2-bonus1.in";

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

  //// EASY ////
  optional1(translations);
  optional2(translations);
  optional3(translations);
  optional4(translations);

  //// INTERMEDIATE ////
  std::cout << std::endl << "Intermidate:" << std::endl;
  bool used[alphabet_len] = {false};  // need this to start the sm_alpha, TODO:
                                      // make a wrapper for this.
  std::vector<std::pair<std::string, std::string>> examples;
  // examples given by challenge
  examples.push_back(
      std::make_pair(".--...-.-.-.....-.--........----.-.-..---.---.--.--.-.-.."
                     "..-..-...-.---..--.----..",
                     "wirnbfzehatqlojpgcvusyxkmd"));
  examples.push_back(
      std::make_pair(".----...---.-....--.-........-----....--.-..-.-..--.--..."
                     "--..-.---.--..-.-...--..-",
                     "wzjlepdsvothqfxkbgrmyicuna"));
  examples.push_back(
      std::make_pair("..-...-..-....--.---.---.---..-..--....-.....-..-.--.-.-."
                     "--.-..--.--..--.----..-..",
                     "uvfsqmjazxthbidyrkcwegponl"));
  for (auto p : examples) {
    bool found = false;  // check that example permutation is found
    auto solutions = sm_alpha(p.first, used);
    std::cout << "Got " << solutions.size() << " permutations for " << p.first
              << std::endl;
    for (auto s : solutions) {
      auto smo = smorse(s);
      if (s == p.second) {  // make sure that example output is in my outputs
        found = true;
      }
      assert(smo == p.first);  // assert that the smorse version matches
      // std::cout << s << std::endl;
    }
    assert(found);  // assert example output is found
  }

  std::vector<std::string> inputs;
  in.open(inputs1000);
  for (std::string line; std::getline(in, line);) {
    // need to remove trailing \r if present (mostly for non windows)
    if (line[line.length() - 1] == '\r') {
      line.erase(line.length() - 1);
    }
    inputs.push_back(line);
  }
  in.close();

  std::cout << inputs.size() << std::endl;

  interOptional1(inputs);
  // interOptional2();
}