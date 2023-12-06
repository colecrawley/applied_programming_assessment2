//
//  main.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 03/12/2023.
//

#include <iostream>
#include <vector>
#include <cstring>
#include "menu.hpp"
#include "item.hpp"
#include "Itemlist.hpp"

int main()
{
    
    Menu menu = Menu("/Users/colecrawley/Desktop/applied_programming_assessment2/applied_programming_assessment2/applied_programming_assessment2/menu.csv");
    
    std::cout << menu.toString();
    
    return 0;
}

