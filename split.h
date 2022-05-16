//
// Created by xander on 5/15/22.
//

#ifndef _ASSESSMENT2_SPLIT_H
#define _ASSESSMENT2_SPLIT_H
#pragma once
#include <vector>
#include <string>
    static void split( std::string str, char separator, std::vector<std::string > &vec, bool skipEmptyStrings = true)
    {
        size_t s = 0;
        for (size_t i = 0; i < str.length(); i++)
        {
            if (str[i] != separator)
                continue;
            std::string xstr = str.substr(s, i -s);
            if (xstr.length() || !skipEmptyStrings)
                vec.push_back( xstr );

            s = i+1;
        }
        std::string xstr = str.substr(s);
        if (xstr.length())
            vec.push_back(  xstr );
    }


#endif //_ASSESSMENT2_SPLIT_H
