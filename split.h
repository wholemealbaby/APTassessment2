#ifndef _ASSESSMENT2_SPLIT_H
#define _ASSESSMENT2_SPLIT_H
#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

static void split( std::string str, std::string separator, std::vector<std::string > &vec, bool skipEmptyStrings)
    {
    // fist index in the string that hasn't been check so far
    size_t substr_index = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str.substr(i, separator.length()) == separator)
        {
            string subStr = str.substr(substr_index, i-substr_index);
            if (subStr.length() || !skipEmptyStrings)
            {
                vec.push_back(subStr);
            }
            substr_index = i+separator.length();
        }

    }
    string subStr = str.substr(substr_index, str.length()-substr_index);
            if (subStr.length())
            {
                vec.push_back(subStr);
            }
    }


#endif //_ASSESSMENT2_SPLIT_H
