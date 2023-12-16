//
//  item.hpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 04/12/2023.
//

#ifndef ITEM_HPP
#define ITEM_HPP
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
    virtual char getItemType() const = 0;
    
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
    virtual std::string toString() const override;
    char getItemType() const override {return 'a';}
    bool getFoodShareable();
    bool getFoodTwoForOne();
    
private:
    bool shareable;
    bool twoForOne;
    
};

class MainCourse : public Item
{
public:
    MainCourse(std::string name, double price, int calories);
    virtual std::string toString() const override;
    char getItemType() const override {return 'm';}
};

class Beverage : public Item
{
public:
    Beverage(std::string name, double price, int calories, double abv, int volume);
    virtual std::string toString() const override;
    char getItemType() const override {return 'b';}
    int getFoodVolume() const;
    double getFoodABV() const;
    
    
    
private:
    double abv;
    int volume;
};


#endif /* ITEM_HPP*/
