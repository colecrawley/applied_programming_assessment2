//
//  item.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 04/12/2023.
//

#include "item.hpp"
#include "menu.hpp"
#include "Itemlist.hpp"
#include <sstream>

Item::Item(std::string name, double price, int calories) : name(name), price(price), calories(calories) {}

std::string Item::toString() const
{
    std::stringstream result;
    result << getFoodName() << ": $" << getFoodPrice() << ", " << getFoodCalories() << " calories";
    
    return result.str();
}

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
    std::stringstream result;
    
    result << Item::getFoodName() << ": $" << Item::getFoodPrice() << ", " << Item::getFoodCalories() << " calories";
    
    //result << Item::toString() << " (Appetiser)";
    
    //result << " (Appetiser)";
    
    if (shareable)
    {
        result << " (shareable)";
    }
    if (twoForOne)
    {
        result << " (twoForOne)";
    }
    
    
    /*switch (shareable + 2 * twoForOne)
    {
        case 0: break; //doesn't apply
        case 1: result += " (shareable)"; break; // only shareable meals
        case 2: result += " (2-4-1)"; break; // only 2-4-1 meals
        case 3: result += " (shareable) (2-4-1)"; break; // both shareable and 2-4-1 meals
    }*/
    
    return result.str();
    
    
};

MainCourse::MainCourse(std::string name, double price, int calories) : Item(name, price, calories) {}

std::string MainCourse::toString() const
{
    std::stringstream result;
    
    result << Item::getFoodName() << ": $" << Item::getFoodPrice() << ", " << Item::getFoodCalories() << " calories";
    
    //return Item::toString() + " (MainCourse)";
    return result.str();
}

Beverage::Beverage(std::string name, double price, int calories, double abv, int volume) : Item(name, price, calories), abv(abv), volume(volume) {}

std::string Beverage::toString() const
{
    std::stringstream result;
    
    result << getFoodName() << ": $" + std::to_string(getFoodPrice()) << ": " << std::to_string(getFoodCalories()) << " calories";
    
    //std::stringstream result;
    //result << Item::toString() << " (Beverage), " << volume << "ml, " << abv << "% abv";
    
    /*result += " (Beverage)";
    result += ", " + std::to_string(volume) + "ml, " + std::to_string(abv) + "% abv";*/
    
    return result.str();
}
