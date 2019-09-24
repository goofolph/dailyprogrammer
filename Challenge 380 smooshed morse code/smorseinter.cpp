#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "alphabet.h"
#include "smorseinter.h"

std::vector<std::string> smalpha(std::string smooshed) {
  bool used[alphabet_len] = {false};
  return sm_alpha(smooshed, used);
}

std::vector<std::string> sm_alpha(std::string smooshed,
                                  bool used[alphabet_len]) {
  std::vector<std::string> solutions;
  std::string solution;
  // std::cout << "Solving " << smooshed << std::endl;
  for (int i = 0; i < alphabet_len; i++) {
    solution.clear();
    // std::cout << "checking " << morse_alphabet[i] << " ";
    if (!used[i]) {
      // std::cout << "not used" << std::endl;
      if (smooshed.find(morse_alphabet[i]) == 0) {
        // std::cout << smooshed << " starts with " << morse_alphabet[i] <<
        // std::endl;
        solution += ascii_alphabet[i];
        std::string sub =
            smooshed.substr(morse_alphabet[i].length(), smooshed.length());
        if (sub.length() > 0) {
          bool usedCopy[alphabet_len];
          std::copy(used, used + alphabet_len, usedCopy);
          usedCopy[i] = true;
          std::vector<std::string> subSols = sm_alpha(sub, usedCopy);
          for (auto s : subSols) {
            std::string temp = solution + s;
            // std::cout << "Adding solution " << temp << std::endl;
            solutions.push_back(temp);
          }
        } else {
          solutions.push_back(solution);
        }
      }
    }
  }
  return solutions;
}

void interOptional1(std::vector<std::string> inputs) {
  std::cout << " Intermidiate Bonus 1" << std::endl << std::endl;
  auto start = std::chrono::steady_clock::now();
  int count = 1;
  for (auto i : inputs) {
    std::cout << "\r" << count << "/" << inputs.size() << std::endl;
    auto perms = smalpha(i);
    /*std::cout << i << " has " << perms.size() << " possible solutions"
              << std::endl;*/
    count++;
  }
  auto end = std::chrono::steady_clock::now();
  std::cout
      << "Elapsed time "
      << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
      << std::endl;
}

void interOptional2() {}