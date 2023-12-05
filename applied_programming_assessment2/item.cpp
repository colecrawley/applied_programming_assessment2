//
//  item.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 04/12/2023.
//

#include "item.hpp"

Item::Item(std::string name, double price, int calories) : name(name), price(price), calories(calories) {}

Item::~Item() {}

std::string Item::getFoodName() const
{
    return name;
}

double Item::getFoodPrice() const
{
    return price;
}

int Item::getFoodCalories() const
{
    return calories;
}

Appetiser::Appetiser(std::string name, double price, int calories, bool shareable, bool twoForOne) : Item(name, price, calories), shareable(shareable), twoForOne(twoForOne) {}

std::string Appetiser::toString() const
{
    std::string result = getFoodName() + ": $" + std::to_string(getFoodPrice()) + ", " + std::to_string(getFoodCalories()) + " calories";
    
    switch (shareable + 2 * twoForOne)
    {
        case 0: break; //doesn't apply
        case 1: result += " (shareable)"; break; // only shareable meals
        case 2: result += " (2-4-1)"; break; // only 2-4-1 meals
        case 3: result += " (shareable) (2-4-1)"; break; // both shareable and 2-4-1 meals
    }
    
    return result;
    
    
}

MainCourse::MainCourse(std::string name, double price, int calories) : Item(name, price, calories) {}

std::string MainCourse::toString() const
{
    return getFoodName() + ": $" + std::to_string(getFoodPrice()) + ": " + std::to_string(getFoodCalories()) + " calories";
}

Beverage::Beverage(std::string name, double price, int calories, double abv, int volume) : Item(name, price, calories), abv(abv), volume(volume) {}

std::string Beverage::toString() const
{
    std::string result = getFoodName() + ": $" + std::to_string(getFoodPrice()) + ": " + std::to_string(getFoodCalories()) + " calories";
    
    result += " (Beverage)";
    result += ", " + std::to_string(volume) + "ml, " + std::to_string(abv) + "% abv";
    return result;
}
