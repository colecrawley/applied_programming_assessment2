#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "utility.hpp"
#include "Itemlist.hpp"
#include "item.hpp"
#include "menu.hpp"
#include <cstdlib>

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







void Menu::printItemsByType(char itemType) const {
    std::string category;

    switch (itemType) {
        case 'a':
            category = "Appetisers";
            break;
        case 'm':
            category = "Main dishes";
            break;
        case 'b':
            category = "Beverages";
            break;
        default:
            std::cerr << "Invalid item type: " << itemType << std::endl;
            return;
    }

    std::cout << category << std::endl;

    for (const auto& item : ItemsonMenu) {
        if (item->getItemType() == itemType) {
            std::cout << item->toString() << std::endl;
        }
    }
}

std::string Menu::toString() const {
    std::stringstream result;
    result << "========== Menu By Cole Crawley ==========\n";
    
    int itemNumber = 1;

    for (const auto& item : ItemsonMenu) {
        result << itemNumber << ".) " << item->toString() << "\n";
        itemNumber++;
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
    if (index >= 0 && index < getMenuSize()) {
        return ItemsonMenu[index];
    } else {
        return nullptr;
    }
}

Item* Menu::findItemByName(const std::string &itemName) const
{
    
    std::string lowercaseFood = toLowerCase(itemName);
    for (const auto& item : ItemsonMenu)
    {
        std::string currentFoodName = toLowerCase(item->getFoodName());
        if (currentFoodName == lowercaseFood)
        {
            return item;
        }
    }
    
    return nullptr;
}
