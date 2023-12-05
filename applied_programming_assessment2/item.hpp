//
//  item.hpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 04/12/2023.
//

#ifndef item_hpp
#define item_hpp

#include <stdio.h>
#include <string>

class Item
{
public:
    Item(std::string name, double price, int calories);
    virtual ~Item();
    
    std::string getFoodName() const;
    double getFoodPrice() const;
    int getFoodCalories() const;
    
    virtual std::string toString() const = 0; // This is the pure virtual function that is meant to override in each child class
    
private:
    std::string name;
    double price;
    int calories;
    
};

class Appetiser : public Item
{
public:
    Appetiser(std::string name, double price, int calories, bool shareable, bool twoForOne);
    std::string toString() const override;
    
private:
    bool shareable;
    bool twoForOne;
    
};

class MainCourse : public Item
{
public:
    MainCourse(std::string name, double price, int calories);
    std::string toString() const override;
};

class Beverage : public Item
{
public:
    Beverage(std::string name, double price, int calories, double abv, int volume);
    std::string toString() const override;
    
private:
    double abv;
    int volume;
};






#endif /* item_hpp */
