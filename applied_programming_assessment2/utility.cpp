//
//  utility.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 16/12/2023.
//

#include "utility.hpp"
#include <algorithm>

std::string toLowerCase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
