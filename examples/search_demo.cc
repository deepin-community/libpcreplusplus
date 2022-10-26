#include <string>
#include "../libpcre++/pcre++.h"

using namespace std;
using namespace pcrepp;

void usage();

int main(int argc, char *argv[]) {
  if(argc <2)
    usage();
  else {
    string search  = argv[1];

    Pcre expression(search, PCRE_GLOBAL | PCRE_CASELESS);

    string input;

    cout << "> ";
    while(getline(cin, input)) {
      if(expression.search(input) == true)
	cout << "true" << endl;
      else
	cout << "false" << endl;
      cout << "> ";
    }
  }
  return true;
}

void usage() {
  cout << endl
       << "Usage: search <search-for>\n"
       << "search must be a regular expression.\n"
       << "Every line on STDIN will then searched\n"
       << "for 'search-for'. If a match is found,\n"
       << "'true' will be printed, 'false' otherwise." << endl;
  exit(-1);
}
