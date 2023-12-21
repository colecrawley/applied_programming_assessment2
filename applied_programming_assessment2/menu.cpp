#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "utility.hpp"
#include "Itemlist.hpp"
#include "item.hpp"
#include "menu.hpp"
#include "order.hpp"
#include <cstdlib>
#include <map>
#include <algorithm>

Menu::Menu(std::string filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filepath << std::endl;
        return;
    }

    std::string line = "";

    while (std::getline(file, line)) {
        char itemtype = 'O';
        std::string name = "";
        double price = 0.0;
        int calories = 0;
        bool shareable = false;
        bool twoForOne = false;
        double abv = 0.0;
        int volume = 0;

        int counter = 0;
        std::string value = "";

        for (int i = 0; i <= line.size()-1; i++) {
            if (line[i] == ',' || i >= line.size()-1) {
                switch (counter) {
                    case 0: itemtype = value[0]; break;
                    case 1: name = value; break;
                    case 2: price = atof(value.c_str()); break;
                    case 3: calories = atoi(value.c_str()); break;
                    case 4: if(value == "y") {
                        shareable = true;} break;
                    case 5: if(value == "y") {
                        twoForOne = true;} break;
                    case 6: volume = atoi(value.c_str()); break;
                    case 7: abv = atof(value.c_str()); break;
                }

                value = "";
                counter += 1;
            } else {
                value += line[i];
            }
        }

        if (counter < 4) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }

        switch (itemtype) {
            case 'a':
            {
                //char shareableChar = ' ', twoForOneChar = ' ';
                //std::istringstream iss(name);
                //iss >> std::quoted(name) >> shareableChar >> twoForOneChar;
               // if (shareable  == "y");
                //twoForOne  == "y";
                //std::cout<<"taste the case:"<<shareable<<twoForOne;
                ItemsonMenu.push_back(new Appetiser(name, price, calories, shareable, twoForOne));
                break;
            }
            case 'b':
            {
                // Check for the presence of volume, abv, and discard remaining values
                if (volume >= 0 && abv >= 0.0) {
                    ItemsonMenu.push_back(new Beverage(name, price, calories, abv, volume));
                } else {
                    std::cerr << "Error parsing beverage: " << line << std::endl;
                    continue;
                }
                break;
            }

            case 'm':
            {
                ItemsonMenu.push_back(new MainCourse(name, price, calories));
                break;
            }

            default:
            {
                std::cerr << "Unknown menu item type: " << itemtype << " in line: " << line << std::endl;
                break;
            }
        }
    }

    file.close();
}







void Menu::printItemsByType(char itemType) const
{
    // Iterate through items and print only those of the specified type
    for (const auto& item : ItemsonMenu)
    {
        if (item->getItemType() == itemType)
        {
            std::cout << item->toString() << std::endl;
        }
    }
}

std::string Menu::toString() const {
    std::stringstream result;
    result << "========== Menu By Cole Crawley ==========\n";

    int itemNumber = 1;

    std::map<char, std::string> categories = {
        {'a', "Appetizers"},
        {'b', "Beverages"},
        {'m', "Main Course"}
    };

    for (const auto& categoryPair : categories) {
        char itemType = categoryPair.first;
        const std::string& category = categoryPair.second;

        result << "========== " << category << " ==========\n";

        for (const auto& item : ItemsonMenu) {
            if (item->getItemType() == itemType) {
                result << "(" << itemNumber << ") " << item->toString() << "\n";
                itemNumber++;
            }
        }
    }

    return result.str();
}




Menu::~Menu() {
    for (auto& item : ItemsonMenu) {
        delete item;
        item = nullptr;
    }
}

int Menu::getMenuSize() const {
    return static_cast<int>(ItemsonMenu.size());
}

Item* Menu::getItemOnMenu(int index) const {
    int itemNumber = 0;

    for (const auto& item : ItemsonMenu) {
        if (item->getItemType() == 'a') {
            if (index == itemNumber) {
                return item;
            }
            itemNumber++;
        }
    }

    for (const auto& item : ItemsonMenu) {
        if (item->getItemType() == 'b') {
            if (index == itemNumber) {
                return item;
            }
            itemNumber++;
        }
    }

    for (const auto& item : ItemsonMenu) {
        if (item->getItemType() == 'm') {
            if (index == itemNumber) {
                return item;
            }
            itemNumber++;
        }
    }

    return nullptr;
}



Item* Menu::findItemByName(const std::string &itemName) const
{

    
    /*std::string lowercaseFood = toLowerCase(itemName);
    for (const auto& item : ItemsonMenu)
    {
        std::string currentFoodName = toLowerCase(item->getFoodName());
        if (currentFoodName == lowercaseFood)
        {
            return item;
        }
    }
    
    return nullptr;*/
        
    std::string lowercaseFood = toLowerCase(itemName);

        int index = 1; // Starting item number

        for (const auto& item : ItemsonMenu)
        {
            std::string currentFoodName = toLowerCase(item->getFoodName());

            if (currentFoodName == lowercaseFood)
            {
                return item;
            }

            ++index; // Increment item number
        }

        return nullptr;
}



std::string Menu::toLowerCase(const std::string& str) const
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::vector<Item*> Menu::getItemsForReceipt() const
{
    return ItemsonMenu;
}

void Menu::sortByMenuPriceAscending() {
    sortItemsByPrice('a', true);  // 'a' for Appetizers
    sortItemsByPrice('b', true);  // 'b' for Beverages
    sortItemsByPrice('m', true);  // 'm' for Main Course
}

void Menu::sortByMenuDescending() {
    sortItemsByPrice('a', false);  // 'a' for Appetizers
    sortItemsByPrice('b', false);  // 'b' for Beverages
    sortItemsByPrice('m', false);  // 'm' for Main Course
}

void Menu::sortItemsByPrice(char itemType, bool ascending) {
    std::vector<Item*> categoryItems;

    // Extract items of the specified category
    for (const auto& item : ItemsonMenu) {
        if (item->getItemType() == itemType) {
            categoryItems.push_back(item);
        }
    }

    // Sort items in the category based on price
    std::sort(categoryItems.begin(), categoryItems.end(), [ascending](Item* a, Item* b) {
        return ascending ? a->getFoodPrice() < b->getFoodPrice() : a->getFoodPrice() > b->getFoodPrice();
    });

    // Update the main list with the sorted items
    int categoryIndex = 0;
    for (auto& item : ItemsonMenu) {
        if (item->getItemType() == itemType) {
            item = categoryItems[categoryIndex++];
        }
    }
}

