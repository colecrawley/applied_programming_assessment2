//
//  menu.hpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 04/12/2023.
//

#ifndef MENU_HPP
#define MENU_HPP

#include <stdio.h>
#include <vector>
#include "Itemlist.hpp"
#include "order.hpp"

class Item;

class Menu : public ItemList
{
public:
    Menu(std::string filepath);
    virtual std::string toString() const override; //this is to display the menu
    std::string toLowerCase(const std::string& str) const;
    std::vector<Item*> getItemsForReceipt() const;
    
    void printItemsByType(char itemType) const;
    //void sortByPrice() const;
    Item* getItemOnMenu(int index) const;
    int getMenuSize() const;
    Item* findItemByName (const std::string& itemName) const;
    std::vector<Item*> filterItemsByType(char itemtype) const; //has to be char type based on brief
    //void sortMenuByPrice();
    void sortByMenuPriceAscending();
    void sortByMenuDescending();
    ~Menu(); // desctructor
    
private:
    std::vector<Item*> ItemsonMenu;
    void sortItemsByPrice(char itemType, bool ascending);
};

#endif /* MENU_HPP */
