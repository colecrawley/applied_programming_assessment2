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
#include "Itemlist.hpp"

class Item;

class Menu : public ItemList
{
public:
    Menu(std::string filepath);
    virtual std::string toString() const override; //this is to display the menu
    
    void printItemsByType(char itemType) const;
    Item* getItemOnMenu(int index) const;
    int getMenuSize() const;
    Item* findItemByName (const std::string& itemName) const;
    std::vector<Item*> filterItemsByType(char itemtype) const; //has to be char type based on brief
    ~Menu(); // desctructor 
    
private:
    std::vector<Item*> ItemsonMenu;
    
};

#endif /* menu_hpp */
