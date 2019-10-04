#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
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

void interOptional1Thread(std::vector<std::string> inputs, int start,
                          int stop) {
  for (int i = start; i < stop && i < inputs.size(); i++) {
    std::string line = inputs[i];
    auto perms = smalpha(line);
    std::cout << line + " has " + std::to_string(perms.size()) +
                     " possible solutions\n";
  }
}

void interOptional1(std::vector<std::string> inputs) {
  std::cout << "Intermidiate Bonus 1" << std::endl << std::endl;
  int count = 1;

  int threadCount = std::thread::hardware_concurrency();

  std::thread **threads = new std::thread *[threadCount];
  int threadLines = inputs.size() / threadCount;
  if (threadCount * threadLines < inputs.size()) threadLines++;

  // used to measure elapsed time
  auto start = std::chrono::steady_clock::now();

  for (int i = 0; i < threadCount; i++) {
    int start = i * threadLines;
    int end = start + threadLines;
    std::thread *t = new std::thread(interOptional1Thread, inputs, start, end);
    threads[i] = t;
  }

  for (int i = 0; i < threadCount; i++) {
    threads[i]->join();
  }

  // for (auto i : inputs) {
  //  std::cout << "\r" << count << "/" << inputs.size() << std::endl;
  //  auto perms = smalpha(i);
  //  /*std::cout << i << " has " << perms.size() << " possible solutions"
  //            << std::endl;*/
  //  count++;
  // }

  // display elapsed time
  auto end = std::chrono::steady_clock::now();
  std::cout
      << "Elapsed time "
      << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
      << std::endl;

  delete[] threads;
}

void interOptional2() {}