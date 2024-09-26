#ifndef _FILTER_CLIENT_H
#define _FILTER_CLIENT_H

#include "parse_filter.h"
#include "jack_client.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

template <typename T>
std::vector< std::vector<T> > parse_filter(const std::string& filename) {
  std::vector< std::vector<T> > sos_matrix;
  std::ifstream file(filename);
  std::string line;

  std::locale::global(std::locale::classic()); // Force "C" locale globally
  
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') {
      continue;  // Skip comments and empty lines
    }
    
    boost::char_separator<char> sep(" \t");
    boost::tokenizer< boost::char_separator<char> > tok(line,sep);
    std::vector<T> row;
    
    for (const auto& token : tok) {
      row.push_back(boost::lexical_cast<T>(token));
    }
        
    sos_matrix.push_back(std::move(row));
  }
    
  return sos_matrix;
}

#endif
