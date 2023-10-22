#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <map>
#include <algorithm>
#include "scanner.h"

using scanner::Token;
using scanner::scan;
using scanner::ScanningFailureException;

int main(int argc, char **argv) {
    std::string line;
    try {
    while (getline(std::cin, line)) {
      std::vector<Token> tokenLine = scan(line);

      for (auto &token : tokenLine) {
        std::cout << token << '\n';
      }
    }
  } catch (ScanningFailureException &f) {
    std::cerr << f.what() << std::endl;
    return 1;
  }
  
  return 0;
}
