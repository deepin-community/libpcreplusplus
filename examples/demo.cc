/*
 *
 *  This file  is part of the PCRE++ Class Library.
 *
 *  By  accessing  this software,  PCRE++, you  are  duly informed
 *  of and agree to be  bound  by the  conditions  described below
 *  in this notice:
 *
 *  This software product,  PCRE++,  is developed by Thomas Linden
 *  and  copyrighted (C) 2002  by  Thomas Linden,  with all rights 
 *  reserved.
 *
 *  There  is no charge for PCRE++ software.  You can redistribute
 *  it and/or modify it under the terms of the GNU  Lesser General
 *  Public License, which is incorporated by reference herein.
 *
 *  PCRE++ is distributed WITHOUT ANY WARRANTY, IMPLIED OR EXPRESS,
 *  OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE or that
 *  the use of it will not infringe on any third party's intellec-
 *  tual property rights.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with PCRE++.  Copies can also be obtained from:
 *
 *    http://www.gnu.org/licenses/lgpl.txt
 *
 *  or by writing to:
 *
 *  Free Software Foundation, Inc.
 *  59 Temple Place, Suite 330
 *  Boston, MA 02111-1307
 *  USA
 *
 *  Or contact:
 *
 *   "Thomas Linden" <tom@daemon.de>
 *
 *
 */


/* you need to include the pcre++ header file */
#include "../libpcre++/pcre++.h"
#include <iostream>

using namespace std;
using namespace pcrepp;

/* A typedef for a vector of strings (as returned by split() )*/
typedef std::vector<std::string> Array;

/* A typedef for a vector iterator */
typedef std::vector<std::string>::iterator ArrayIterator;

void regex() {
    /*
     * define a string with a regular expression
     */
    string expression = "([a-z]*) ([0-9]+)";

    /*
     * this is the string in which we want to search
     */
    string stuff = "hallo 11 robert";

    cout << "  searching in \"" << stuff << "\" for regex \""
	 << expression << "\":" << endl;

    /*
     * Create a new Pcre object, search case-insensitive ("i")
     */
    Pcre reg(expression, "i");
    
    /*
     * see if the expression matched
     */
    if(reg.search(stuff) == true) {

      /*
       * see if the expression generated any substrings
       */
      if(reg.matches() >= 1) {

	/*
	 * print out the number of substrings
	 */
	cout << "  generated " << reg.matches() << " substrings:" << endl;
	  
	/*
	 * iterate over the matched sub strings
	 */
	for(int pos=0; pos < reg.matches(); pos++) {
	  /* print out each substring */
	  cout << "  substring " << pos << ": " << reg[pos];   // also possible: reg.get_match(pos);
	  /* print out the start/end offset of the current substring
	   * within the searched string(stuff)
	   */
	  cout << " (start: " << reg.get_match_start(pos) << ", end: "
	       << reg.get_match_end(pos) << ")" << endl;
	}
      }
      else {
	/*
	 * we had a match, but it generated no substrings, for whatever reason
	 */
	cout << "   it matched, but there where no substrings." << endl;
      }
    }
    else {
      /*
       * no match at all
       */
      cout << "   didn't match." << endl;
    }
}



void replace() {
    /*
     * Sample of replace() usage
     */
    string orig = "Hans ist 22 Jahre alt. Er ist 8 Jahre älter als Fred.";
    cout << "   orig: " << orig << endl;

    /*
     * define a regex for digits (character class)
     */
    Pcre p(" ([0-9]+) ");

    /*
     * replace the 1st occurence of [0-9]+ with "zweiundzwanzig"
     */
    string n = p.replace(orig, " zweiundzwanzig($1) ");

    /*
     * prints out: "Hans ist zweiundzwanzig Jahre alt. Er ist 8 Jahre älter
     * als Fred."
     */
    cout << "   new: " << n << endl; 
}


void replace_multi() {
  /*
   * Sample of replace() usage with multiple substrings
   */
  string orig = " 08:23 ";
  cout << "   orig: " << orig << endl;
  
  /*
   * create regex which, if it matches, creates 3 substrings
   */
  Pcre reg(" ([0-9]+)(:)([0-9]+) ", "sig");

  /*
   * remove $2 (":")
   * re-use $1 ("08") and $3 ("23") in the replace string
   */
  string n  = reg.replace(orig, "$1 Stunden und $3 Minuten");

  /*
   * prints the result: "08 Stunden und 23 Minuten"
   */
  cout << "   new:  " << n  << endl;
}


void normalize() {
  /*
   * another sample to check if normalizing using replace() works
   */
  string orig = "Heute   ist ein  schoener  Tag        gell?";
  cout << "   orig: " << orig << endl;

  /*
   * create regex for normalizing whitespace
   */
  Pcre reg("[\\s]+", "gs");

  /*
   * do the normalizing process
   */
  string n = reg.replace(orig, " ");

  /*
   * prints the result, should be: "Heute ist ein schoener Tag , gell?"
   */
  cout << "   new:  " << n  << endl;
}


void split() {
  /*
   * Sample of split() usage
   */
      string sp_orig = "was21willst2387461du3alter!";
      cout << "   orig: " << sp_orig << endl;

      /*
       * define a regex for digits (character class)
       */
      string delimiter = "[0-9]+";

      /*
       * new Pcre object, match globally ("g" flag)
       */
      Pcre S(delimiter, "g");

      /*
       * split "was21willst2387461du3alter!" by digits
       */
      Array splitted = S.split(sp_orig);
      
      /*
       * iterate over the resulting list
       */
      cout << "   splitted: ";
      for(ArrayIterator A = splitted.begin(); A != splitted.end(); ++A)
	cout << *A << " ";
      cout << endl;
}


void ex() {
  /*
   * Pcre::exception Test
   */
  
  /*
   * this will generate only one substring, "This"
   */
  Pcre ex("([a-z]+)", "i");
  if(ex.search("This is a test.")) {
    cout << "  trying to access a non-existing substring:" << endl;
    cout << "  substring 2: " << ex.get_match(1) << endl; 
  }
}


void mycopy() {
  /*
   * Sample use of copy contsructor and operator=
   */
    cout << "  initializing reg1(([a-z]+?)" << endl;
    Pcre reg1("^([a-z]+?)");

    /*
     * create an empty Pcre objects
     */
    Pcre reg2;
    
    /*
     * copy reg1 to reg2 (operator=)
     */
    cout << "  copying reg1 to new Pcre object reg2" << endl;
    reg2 = reg1;

    /*
     * using the copy constructor to initialize the 3rd object
     */
    cout << "  creating a new Pcre object reg3 from reg2" << endl;
    Pcre reg3(reg2);

    /*
     * doing regular stuff on reg3
     */
    if(reg3.search("anton"))
      cout << "  string 'anton' matched using reg3 object" << endl;
}

void multisearch() {
  Pcre reg("([^\\n]+\\n)");
  string str = "\nline1\nline2\nline3\n";
  size_t pos = 0;

  while (pos <= str.length()) {
    if( reg.search(str, pos)) {
      pos = reg.get_match_end(0);
      cout << "   pos: " << pos << " match: " << reg.get_match(0);
    }
    else
      break;
  }
}

int main() {
  /* 
   * the Pcre class throws errors via exceptions
   */
  try {
    cout << endl << "SEARCH() sample:" << endl;
    regex();

    cout << endl << "REPLACE() sample:" << endl;
    replace();

    cout << endl << "Multiple REPLACE() sample:" << endl;
    replace_multi();

    cout << endl << "Normalizing REPLACE() sample:" << endl;
    normalize();

    cout << endl << "SPLIT() sample:" << endl;
    split();

    cout << endl << "COPY+Operator sample:" << endl;
    mycopy();

    cout << endl << "Multi line search test:" << endl;
    multisearch();

    cout << endl << "Pcre::exception test:" << endl;
    ex();

    exit(0);
  }
  catch (Pcre::exception &E) {
    /*
     * the Pcre class has thrown an exception
     */
    cerr << "Pcre++ error: " << E.what() << endl;
    exit(-1);
  }
  exit(0);
}
  
