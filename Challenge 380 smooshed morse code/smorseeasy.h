#pragma once

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
