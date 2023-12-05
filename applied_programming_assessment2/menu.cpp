//
//  menu.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 04/12/2023.
//

#include "menu.hpp"
#include <fstream>
#include <sstream>
#include <string>

Menu::Menu(std::string filepath)
{
    std::ifstream file(filepath);
    
    if (file.is_open())
    {
        std::string line;
        
        while (getline(file,line))
        {
            std::istringstream iss(line);
            
            std::string itemtype;
            std::string name;
            double price;
            int calories;
            bool shareable = false;
            bool twForOne = false;
            double abv = 0.0;
            int volume = 0;
            
            iss >> itemtype >> name >> price >> calories;
            
            
            if (itemtype == "app")
            {
                iss >> shareable >> twForOne;
                ItemsonMenu.push_back(new Appetiser(name, price, calories, shareable, twForOne));
            }
            else if (itemtype == "main")
            {
                ItemsonMenu.push_back(new MainCourse(name, price, calories));
            }
            else if (itemtype == "bev")
            {
                iss >> volume >> abv;
                ItemsonMenu.push_back(new Beverage(name, price, calories, volume, abv));
            }
        }
        
        file.close();
    }
}
