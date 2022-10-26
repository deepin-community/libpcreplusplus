#include "../libpcre++/pcre++.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
using namespace pcrepp;

class failure {
private:
  string message;

public:
  failure(const string& msg) {
    message = msg;
  }

  string what() {
    return message;
  }
};

map<string, vector<string> > read_data(const char* file) {
  ifstream data(file);
  if(data) {
    vector<string> content;
    map<string, vector<string> > hash;
    string line, regex;
    char zeichen;
    bool is_regex=false;
    Pcre find_end("\\/[gimsxADEGIMNSUX8L\\+]{0,2}$");
    while (data) {
      data.get(zeichen);
      if(zeichen == '\n') {
	if(line[0] == '/') {
	  regex = line;
	  if(find_end.search(line))
	    is_regex = false;
	  else
	    is_regex = true;
	}
	else if(is_regex) {
          regex += "\n" + line;
	  if(find_end.search(line))
	    is_regex = false;
	  else
	    is_regex = true;
	}
	else if(line[0] == ' ') {
	  line.replace(0, 4, ""); // remove leading whitespaces
	  content.push_back(line);
	}
	else if(line.empty()) {
	  hash[regex] = content;
	  content.clear();
	}
	line = "";
      }
      else
	line += zeichen;
    }
    data.close();
    return hash;
  }
  else {
    throw failure("Could not open file " + string(file));
  }
}



int main(int argc, char *argv[]) {
  try {
    if(argc < 2)
      throw failure("Usage: " + string(argv[0]) + " <datafile>");
    else {
      map<string, vector<string> > hash = read_data(argv[1]);
      typedef map<string, vector<string> >::iterator map_iter;
      typedef vector<string>::iterator vec_iter;
      Pcre *reg;
      string expression, flags;
      for(map_iter mp = hash.begin(); mp != hash.end(); ++mp) {
	string regex = mp->first;
	vector<string> content = mp->second;
	unsigned int pos = regex.find_last_of("/", string::npos);
	if (pos == regex.size()) {
	  flags = "";
	  expression = regex.substr(1, regex.size() - 1);
	}
	else {
	  flags = regex.substr(pos + 1, regex.size());
	  expression = regex.substr(1, pos - 1);
	}

	cout << "/" << expression << "/" << flags << endl;

	try {
	  if(flags.empty())
	    reg = new Pcre(expression);
	  else {
	    reg = new Pcre(expression, flags);
	    flags = "";
	  }
	}
	catch(Pcre::exception &e) {
	  cout << e.what() << endl;
	  continue;
	}
	
	for(vec_iter vp = content.begin(); vp != content.end(); ++vp) {
	  string data = *vp;
	  if(reg->search(data))
	    cout << "   1:   ";
	  else
	    cout << "   0:   ";
	  cout << data << endl;
	}
	cout << endl;

	delete reg;
      }
    }
  }
  catch(exception &e) {
    cerr << e.what() << endl;
    return 1;
  }
  catch(failure &f) {
    cerr << f.what() << endl;
    return 1;
  }
  catch(...) {
    cerr << "unknown failure" << endl;
    return 1;
  }

  return 0;
}
