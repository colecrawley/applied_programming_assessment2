//
//  menu.hpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 04/12/2023.
//

#ifndef menu_hpp
#define menu_hpp

#include <stdio.h>
#include <vector>
#include "item.hpp"
#include <string> //could remove if there are errors with this and change itemtype back to char

class Menu
{
public:
    Menu(std::string filepath);
    std::string toString() const; //this is to display the menu
    
    Item* getItemOnMenu(int index) const;
    int getMenuSize() const;
    Item* findItemByName (const std::string& itemName) const;
    std::vector<Item*> filterItemsByType(std::string itemtype) const; //could change to char if there are any errors
    
private:
    std::vector<Item*> ItemsonMenu;
    
};

#endif /* menu_hpp */
