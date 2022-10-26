/*
 * momory leak testing
 */

#include "../libpcre++/pcre++.h"
#include <vector>
#include <string>

int main()                                                                                                                  
{                                                                                                                           
        while ( true )                                                                                                      
        {                                                                                                                   
                pcrepp::Pcre r( "\\s*,\\s*", "g" );                                                                         
                std::vector<std::string> splits = r.split( "12,3" );                                                                  
        }                                                                                                                   
}     
