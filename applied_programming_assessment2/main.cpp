//
//  main.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 15/12/2023.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "menu.hpp"

int main() {
    Menu menu("/Users/colecrawley/Desktop/applied_programming_assessment2/applied_programming_assessment2/applied_programming_assessment2/menu.csv");

    std::cout << menu.toString() << std::endl;

    return 0;
}
