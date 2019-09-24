#pragma once

/* Wrapper function for sm_alpha.
 */
std::vector<std::string> smalpha(std::string smooshed);

/* Given smooshed morse permutation of alphabet find possible original outputs.

  param smooshed morse code to unsmoosh to alphabet permutation
  param used array of used alphabets, must be filled with false initially
  returns list of all permutations containing that substring restricted to
    unused characters
*/
std::vector<std::string> sm_alpha(std::string smooshed,
                                  bool used[alphabet_len]);

/* Optional Bonus 1 How fast to find output of 1000 inputs.
 */
void interOptional1(std::vector<std::string> inputs);

/* Optional Bonus 2 Find valid input with fewest possible outputs.
 */
void interOptional2();