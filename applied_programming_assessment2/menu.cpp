//
//  menu.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 04/12/2023.
//
#include <iostream>
#include "menu.hpp"
#include "item.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

Menu::Menu(std::string filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filepath << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        
        std::replace(line.begin(), line.end(), ',', ' ');

        std::istringstream iss(line);

        char itemtype;
        std::string name;
        double price;
        int calories;
        bool shareable = false;
        bool twoForOne = false;
        double abv = 0.0;
        int volume = 0;

        //std::string temp;

        if (!(iss >> itemtype >> std::quoted(name) >> price >> calories)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }
        
        //iss >> itemtype >> std::quoted(name) >> price >> calories;

        if (itemtype == 'a') {
            
            char shareableChar, twoForOneChar;
            if (!(iss >> shareableChar >> twoForOneChar)) {
                std::cerr << "Error parsing appetizer: " << line << std::endl;
                continue;
            }
            shareable = (shareableChar == 'y');
            twoForOne = (twoForOneChar == 'y');
        } else if (itemtype == 'b') {
            if (!(iss >> volume >> abv)) {
                std::cerr << "Error parsing beverage: " << line << std::endl;
                continue;
            }
        }

        switch (itemtype) {
            case 'a':
                ItemsonMenu.push_back(new Appetiser(name, price, calories, shareable, twoForOne));
                break;

            case 'b':
                ItemsonMenu.push_back(new Beverage(name, price, calories, abv, volume));
                break;

            case 'm':
                ItemsonMenu.push_back(new MainCourse(name, price, calories));
                break;

            default:
                std::cerr << "Unknown menu item type: " << itemtype << " in line: " << line << std::endl;
                continue;
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

    int index = 1;  // Counter for item numbering

    for (const auto& item : ItemsonMenu) {
        if (item->getItemType() == itemType) {
            std::cout << item->toString() << std::endl;
        }
    }
}

std::string Menu::toString() const {
    std::stringstream result;
    result << "========== Menu By Cole Crawley ==========\n";

    for (const auto& item : ItemsonMenu) {
        result << item->toString() + "\n";
    }

    return result.str();
}

Menu::~Menu() {
    for (auto& item : ItemsonMenu) {
        delete item;
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


