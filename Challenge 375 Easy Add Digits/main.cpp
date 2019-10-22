#include <cassert>
#include <climits>
#include <iomanip>
#include <iostream>

/**
 * Increments each digit in a number.
 *
 * Ex. 10 -> 21 and 89 -> 910
 *
 *
 * param in input number
 * returns in with each digit incremented.
 */
long long incDigits(long long in);

/**
 * Increments each digit in a number.
 *
 * Ex. 10 -> 21 and 89 -> 910
 *
 *
 * param in input number
 * returns in with each digit incremented.
 */
long long incDigitsRec(long long in);

/**
 * Counts the number of base10 digits in a number.
 *
 * param in input nunber
 * returns number of base10 digits from in
 */
int countDigits(long long in);

int main(int argc, char** argv) {
  long long val;
  long long solution;
  long long result;

  // tests
  val = 366496LL;
  solution = 4775107LL;
  result = incDigits(val);
  std::cout << val << " => " << result << std::endl;
  assert(result == 4775107LL);
  result = incDigits(val);
  std::cout << val << " => " << result << std::endl;
  assert(result == solution);

  val = 12345LL;
  solution = 23456LL;
  result = incDigits(val);
  std::cout << val << " => " << result << std::endl;
  assert(result == solution);

  val = 7890LL;
  solution = 89101LL;
  result = incDigits(val);
  std::cout << val << " => " << result << std::endl;
  assert(result == solution);

  val = 1234567890LL;
  solution = 23456789101LL;
  result = incDigits(val);
  std::cout << val << " => " << result << std::endl;
  assert(result == solution);

  val = 366496LL;
  solution = 4775107LL;
  result = incDigits(val);
  std::cout << val << " => " << result << std::endl;
  assert(result == solution);

  return 0;
}

long long incDigits(long long num) {
  int digits = countDigits(num);  // cound digits
  long long result = 0;           // final result
  for (auto i = 1; i <= digits; i++) {
    // amount to divide by to get current digit from left to right
    long long p = pow(10, digits - i);
    long long digit = (num / p) % 10 + 1;  // current digit

    if (digit < 10)  // if new digit is < 10 mult by 10
      result *= 10;
    else  // otherwise mult by 100 instead
      result *= 100;
    result += digit;  // add new digit
  }
  return result;
}

int countDigits(long long in) {
  int count = 0;  // number of digits
  while (in > 0) {
    in = in / 10;  // remove right most digit
    count++;
  }
  return count;
}

long long incDigitsRec(long long num) {
  if (num < 10) return num + 1;
  long long next = num % 10 + 1;
  long long prev = incDigitsRec(num / 10);
  if (next == 10)
    return prev * 100 + next;
  else
    return prev * 10 + next;
}
