#include <string>
#include "../libpcre++/pcre++.h"

using namespace std;
using namespace pcrepp;

void usage();

int main(int argc, char *argv[]) {
  if(argc <3)
    usage();
  else {
    string search  = argv[1];
    string replace = argv[2];

    Pcre expression(search, "g");

    string input;

    cout << "> ";
    while(getline(cin, input)) {
      cout << expression.replace(input, replace) << endl;
      cout << "> ";
    }
  }
  return true;
}

void usage() {
  cout << endl
       << "Usage: replace <search-for> <replace-with>\n"
       << "search must be a regular expression.\n"
       << "Every line on STDIN will then searched\n"
       << "for 'search-for'. Every match will be replaced\n"
       << "with 'replace-with'." << endl;
  exit(-1);
}
